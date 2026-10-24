#!/usr/bin/env python3
"""Sync the Ghidra project with the dsd config, without the Ghidra GUI.

dsd-ghidra's SyncDsd.java asks for config.yaml in a file chooser, so it only runs in
the GUI. This script writes a headless copy of the installed script (same code, the
chooser replaced by the first script argument) to a temporary folder and runs it with
Ghidra's analyzeHeadless on the imported ROM. Nothing from dsd-ghidra is stored in
this repository. Setup and paths: notes/GHIDRA.md.

Usage:
  python tools/ghidra_sync.py              # sync config/eur/arm9/config.yaml
  python tools/ghidra_sync.py --dry-run    # report what would change, change nothing
  python tools/ghidra_sync.py --ghidra <install dir> --project <project dir>
"""

import argparse
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GHIDRA_VERSION = "11.2.1"
DEFAULT_GHIDRA = r"E:\Projets\Github\Decomp\Tools\Ghidra\ghidra_11.2.1_PUBLIC"
DEFAULT_PROJECT = r"E:\Projets\Dev\ts2-castaway-ghidra"
PROJECT_NAME = "ts2c_eur"
PROGRAM = "baserom_ts2c_eur.nds"

CHOOSER = re.compile(
    r"DsdConfigChooser dsdConfigChooser = new DsdConfigChooser\(.*?"
    r"dryRun = dsdConfigChooser\.isDryRun\(\);",
    re.S,
)
HEADLESS = """String[] scriptArgs = getScriptArgs();
        File file = new File(scriptArgs[0]);
        dryRun = scriptArgs.length > 1 && scriptArgs[1].equals("dry");"""


def installed_script():
    appdata = os.environ.get("APPDATA", "")
    path = os.path.join(appdata, "ghidra", f"ghidra_{GHIDRA_VERSION}_PUBLIC", "Extensions",
                        "dsd-ghidra", "ghidra_scripts", "SyncDsd.java")
    if not os.path.isfile(path):
        sys.exit(f"dsd-ghidra not installed: {path} not found (see notes/GHIDRA.md)")
    return path


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--version", default="eur", help="game version (default: %(default)s)")
    parser.add_argument("--ghidra", default=DEFAULT_GHIDRA, help="Ghidra install dir")
    parser.add_argument("--project", default=DEFAULT_PROJECT, help="Ghidra project dir")
    parser.add_argument("--dry-run", action="store_true", help="change nothing")
    args = parser.parse_args()

    source = open(installed_script(), encoding="utf-8").read()
    patched, count = CHOOSER.subn(HEADLESS, source)
    if count != 1:
        sys.exit("SyncDsd.java changed: the file chooser block was not found")
    patched = patched.replace("public class SyncDsd ", "public class SyncDsdHeadless ")
    # The chooser's package is not on the temporary script path: drop the import and
    # inline its one constant (the key under which the last config path is saved).
    patched = patched.replace("import dialog.DsdConfigChooser;\n", "")
    patched = patched.replace("DsdConfigChooser.LAST_CONFIG_KEY", '"DsdConfigChooserLastConfig"')
    if "DsdConfigChooser" in patched.replace('"DsdConfigChooserLastConfig"', ""):
        sys.exit("SyncDsd.java changed: another DsdConfigChooser use was found")

    config = os.path.join(ROOT, "config", args.version, "arm9", "config.yaml")
    headless = os.path.join(args.ghidra, "support", "analyzeHeadless.bat")
    with tempfile.TemporaryDirectory() as tmp:
        with open(os.path.join(tmp, "SyncDsdHeadless.java"), "w", encoding="utf-8") as f:
            f.write(patched)
        cmd = [headless, args.project, PROJECT_NAME, "-process", PROGRAM, "-noanalysis",
               "-scriptPath", tmp, "-postScript", "SyncDsdHeadless.java", config]
        if args.dry_run:
            cmd.append("dry")
        out = subprocess.run(cmd, capture_output=True, text=True)
    log = out.stdout + out.stderr
    for line in log.splitlines():
        if "SyncDsdHeadless" in line or "ERROR" in line or "REPORT" in line:
            print(line.strip())
    return 0 if out.returncode == 0 and "ERROR" not in log else 1


if __name__ == "__main__":
    sys.exit(main())
