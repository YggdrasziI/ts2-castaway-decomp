/*
 * Unit 0x020A5948-0x020A5CCC: starts the microgames by hash from their archive (the strings at
 * 0x020BDA48-0x020BDACC) and reports their result to the "OnSuccess" / "OnFailure" script of an
 * object definition. Bounds: hypothesis (0x020A5CCC starts the microgame base class; `.bss` is
 * the state, addressed from one anchor). All names are placeholders. Real file name unknown.
 */
#include "game/unk_action.h"
#include "game/unk_archive.h"
#include "game/unk_microgame.h"
#include "game/unk_script.h"

struct Unk020a5948App {
    u8 unk0[8];
    u32 flags;
};

extern "C" {
Unk020a5ccc *func_0200cec8(Unk02093648 *file, void *args, int n);
Unk020a5ccc *func_0200ed88(Unk02093648 *file, void *args, int n);
Unk020a5ccc *func_02012574(Unk02093648 *file, void *args, int n);
Unk020a5ccc *func_02015408(Unk02093648 *file, void *args, int n);
Unk020a5ccc *func_0201a2c8(Unk02093648 *file, void *args, int n);
Unk020a5ccc *func_0201b648(Unk02093648 *file, void *args, int n);
Unk020a5ccc *func_02011524(Unk02093648 *file, void *args, int n);
Unk020a5ccc *func_0201b5bc(Unk02093648 *file, void *args, int n);
Unk020a5ccc *func_02013f58(Unk02093648 *file, void *args, int n);
void func_020897b4(const char *format, ...);
u32 func_0209a3c4(u32 hash, const char *str);
void func_0205d39c(Unk0205cf00 *def, u32 key);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
int func_020a5d7c(Unk020a5ccc *game);
bool func_020a5cb0();
extern u8 data_020c3fc4[];
extern Unk020a5948App data_020d60c8;
extern const char *data_020bda44;
}

const char *data_020bda44 = "ROM_Euro/source/archives/microgames.nitro_archive";

struct Unk020a5948State {
    u32 key;
    Unk02093648 *archive;
    Unk020a5ccc *game;
};

static Unk020a5948State data_020d7100;

extern "C" Unk020a5ccc *func_020a5948(u32 key, void *args, int n) {
    switch ((int)key) {
    case 0x296db2dc:
        return func_0200cec8(data_020d7100.archive, args, n);
    case 0x6b5b96cd:
        return func_0200ed88(data_020d7100.archive, args, n);
    case 0xa97f6dcd:
        return func_02012574(data_020d7100.archive, args, n);
    case 0x22d40351:
        return func_02015408(data_020d7100.archive, args, n);
    case 0x5e691f68:
        return func_0201a2c8(data_020d7100.archive, args, n);
    case 0x99a2c231:
        return func_0201b648(data_020d7100.archive, args, n);
    case 0xd5f176e9:
        return func_02011524(data_020d7100.archive, args, n);
    case 0x2747b360:
        return func_0201b5bc(data_020d7100.archive, args, n);
    case 0x5fc7c74d:
        return func_02013f58(data_020d7100.archive, args, n);
    }
    func_020897b4("Unable to find micro game with identifier %d", key);
    return 0;
}

extern "C" int func_020a5ab8() {
    int result = data_020d7100.game->func_08();
    Unk0205cf00 *def = func_0205f6f8(data_020c3fc4, 0xb5dce8a4);
    u32 key = func_0209a3c4(data_020d7100.key, result == 1 ? ".OnSuccess" : ".OnFailure");
    if (def->script->func_020957ec(key) != 0) {
        func_0205d39c(def, key);
    }
    return func_0205d1b4(def, func_0209a3c4(data_020d7100.key, "Duration"));
}

extern "C" bool func_020a5b58(u32 key, void *args, int n) {
    if (func_020a5cb0() == true) {
        return false;
    }
    data_020d7100.archive = new Unk02093648(data_020bda44);
    if (data_020d7100.archive == 0) {
        return false;
    }
    data_020d7100.archive->func_02094df4();
    Unk020a5ccc *game = func_020a5948(key, args, n);
    data_020d7100.game = game;
    data_020d7100.key = key;
    return func_020a5cb0() == true;
}

static inline bool func_running() {
    if (data_020d60c8.flags & 1) {
        return true;
    }
    return false;
}

extern "C" int func_020a5bec() {
    if (!func_020a5cb0()) {
        return 0;
    }
    bool running = func_running();
    if (running == false) {
        return 1;
    }
    return func_020a5d7c(data_020d7100.game);
}

extern "C" int func_020a5c38() {
    if (!func_020a5cb0()) {
        return 0;
    }
    int result = func_020a5ab8();
    delete data_020d7100.game;
    data_020d7100.game = 0;
    data_020d7100.key = 0;
    delete data_020d7100.archive;
    data_020d7100.archive = 0;
    return result;
}

extern "C" bool func_020a5cb0() {
    return data_020d7100.game != 0;
}
