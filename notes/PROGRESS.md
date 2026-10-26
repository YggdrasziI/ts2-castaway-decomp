# Progress log

| Date | Commit | Matched code | Matched functions | Files complete | Milestone |
|---|---|---|---|---|---|
| 2026-10-25 | 3063d8c | 0 / 720812 bytes (0 %) | 0 / 4553 | 0 / 0 | Setup done: dsd setup for eur, all-assembly build rebuilds the original ROM (identical with the owner's ARM7 BIOS), private repository and build image, CI green, Ghidra project synced |
| 2026-10-26 | 1a75823 | 49556 / 720836 bytes (6.87 %; fuzzy 8.20 %, linked 2.92 %) | 620 / 4557 | 39 / 89 | Step 6 under way: engine block delinked from 0x0208D304 to 0x0209A740 (resource files, heap, math, input, object entries and managers, text, fonts) and the pie menu |
| 2026-10-26 | 6dfd7af | 52912 / 720836 bytes (7.34 %; fuzzy 8.87 %, linked 2.92 %) | 660 / 4557 | 39 / 90 | Texture manager unit: engine block delinked from 0x0208C050 to 0x0209A740 |
| 2026-10-26 | 0a6dcdd | 53128 / 720836 bytes (7.37 %; fuzzy 8.94 %, linked 2.92 %) | 666 / 4557 | 39 / 92 | Transform set unit: engine block delinked from 0x0208BE3C to 0x0209A740 |
| 2026-10-26 | f893a1c | 56080 / 720836 bytes (7.78 %; fuzzy 9.31 %, linked 3.46 %) | 700 / 4557 | 43 / 94 | Interface class, object pool and transform set units complete: engine block delinked from 0x0208B41C to 0x0209A740 |
| 2026-10-26 | 34409cd | 61464 / 720836 bytes (8.53 %; fuzzy 10.05 %, linked 3.79 %) | 760 / 4557 | 46 / 98 | Model, model library, pool object and element set units: engine block delinked from 0x02089F38 to 0x0209A740 |
| 2026-10-26 | 3408752 | 62892 / 720836 bytes (8.72 %; fuzzy 10.25 %, linked 3.99 %) | 766 / 4557 | 47 / 99 | Camera unit complete: engine block delinked from 0x020899A4 to 0x0209A740 |
| 2026-10-26 | c01b862 | 63372 / 720836 bytes (8.79 %; fuzzy 10.31 %, linked 4.05 %) | 770 / 4557 | 48 / 101 | Animation unit complete: engine block delinked from 0x020897C0 to 0x0209A740 |
| 2026-10-26 | e3d0c0c | 65564 / 720836 bytes (9.10 %; fuzzy 10.62 %, linked 4.36 %) | 782 / 4557 | 49 / 102 | First ITCM unit complete (element set functions 0x01FF9098-0x01FF9924) |
| 2026-10-26 | 5565f52 | 66012 / 720836 bytes (9.16 %; fuzzy 10.86 %, linked 4.36 %) | 792 / 4557 | 49 / 104 | ITCM animation sampling unit (10 of 11 functions) |
| 2026-10-26 | 8e32e70 | 66420 / 720836 bytes (9.21 %; fuzzy 10.92 %, linked 4.41 %) | 797 / 4557 | 50 / 105 | ITCM model unit complete (geometry FIFO send 0x01FF8BEC-0x01FF8D84) |
| 2026-10-26 | 77245b0 | 66652 / 720836 bytes (9.25 %; fuzzy 11.03 %, linked 4.41 %) | 799 / 4557 | 50 / 105 | ITCM model matrix unit (2 of 3 functions) |
| 2026-10-26 | fddcfcd | 67712 / 720836 bytes (9.39 %; fuzzy 11.31 %, linked 4.41 %) | 803 / 4557 | 50 / 106 | ITCM pool drawing unit (4 of 5 functions) |
| 2026-10-26 | 26b91b1 | 67712 / 720836 bytes (9.39 %; fuzzy 11.34 %, linked 4.41 %) | 803 / 4557 | 50 / 106 | Pool draw order sort added to the ITCM pool drawing unit |
