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
| 2026-10-26 | 03ab275 | 69748 / 720836 bytes (9.68 %; fuzzy 11.62 %, linked 4.70 %) | 811 / 4557 | 51 / 107 | ITCM transform set unit (complete) |
| 2026-10-26 | 46faa29 | 71276 / 720836 bytes (9.89 %; fuzzy 11.84 %, linked 4.91 %) | 816 / 4557 | 52 / 107 | ITCM VRAM transfer unit (complete) |
| 2026-10-26 | 2212dff | 73880 / 720836 bytes (10.25 %; fuzzy 12.01 %, linked 5.33 %) | 825 / 4557 | 56 / 109 | Whole ITCM delinked: start of the ITCM (EA, NitroSDK DMA and IRQ), animation unit complete |
| 2026-10-26 | de7adb4 | 75112 / 720836 bytes (10.42 %; fuzzy 12.41 %, linked 5.33 %) | 834 / 4557 | 56 / 111 | Palette set unit (9 / 14 functions at 100 %, the rest above 88 %) |
| 2026-10-26 | 0d09c35 | 76740 / 720836 bytes (10.65 %; fuzzy 12.77 %, linked 5.33 %) | 851 / 4557 | 56 / 113 | Texture coordinate animation unit (17 / 21 functions at 100 %) and the software floating-point runtime named |
| 2026-10-26 | 1ef3246 | 78400 / 720836 bytes (10.88 %; fuzzy 13.04 %, linked 5.33 %) | 865 / 4557 | 56 / 114 | Pool object resource unit (14 / 15 functions at 100 %) |
| 2026-10-26 | 53a6001 | 78984 / 720836 bytes (10.96 %; fuzzy 13.25 %, linked 5.33 %) | 870 / 4557 | 56 / 115 | Pool effect unit (5 / 7 functions and the data at 100 %) |
| 2026-10-26 | a634537 | 81608 / 720836 bytes (11.32 %; fuzzy 13.75 %, linked 5.33 %) | 887 / 4557 | 56 / 117 | Game state (6 / 7 functions and its vtable data at 100 %) and item catalog (11 / 12) units |
| 2026-10-26 | a7745f8 | 82032 / 720836 bytes (11.38 %; fuzzy 13.81 %, linked 5.33 %) | 893 / 4557 | 56 / 118 | Game state id 1 unit (6 / 6 functions and its data at 100 %, waiting on the first base vtable copy to link) |
| 2026-10-26 | b8f5f15 | 84820 / 720836 bytes (11.77 %; fuzzy 14.20 %, linked 5.33 %) | 907 / 4557 | 56 / 119 | Game state id 2 unit (14 / 14 functions at 100 %, phases by pointer to member; `__ptmf_null` named) |
| 2026-10-26 | 0bc1a94 | 86444 / 720836 bytes (11.99 %; fuzzy 14.42 %, linked 5.33 %) | 919 / 4557 | 56 / 121 | Game state id 4 unit (12 / 12 functions at 100 %), the last state of block 1 |
| 2026-10-27 | 356948b | 92848 / 720836 bytes (12.88 %; fuzzy 16.56 %, linked 5.33 %) | 965 / 4557 | 56 / 121 | Main game state unit written (46 / 56 functions and its data at 100 %; holds the first base vtable copy the other states wait on) |
| 2026-10-27 | 90457db | 94956 / 720836 bytes (13.17 %; fuzzy 16.79 %, linked 5.52 %) | 978 / 4557 | 57 / 123 | Timed queue unit (11 / 11 functions, complete) |
| 2026-10-27 | 2dd78e6 | 95288 / 720836 bytes (13.22 %; fuzzy 16.84 %, linked 5.57 %) | 983 / 4557 | 58 / 124 | Sorted set unit (5 / 5 functions, complete) |
| 2026-10-27 | 2118f87 | 95636 / 720836 bytes (13.27 %; fuzzy 16.89 %, linked 5.62 %) | 986 / 4557 | 59 / 125 | Main-screen object entry unit (3 / 3 functions, complete) |
| 2026-10-27 | a37ac53 | 97812 / 720836 bytes (13.57 %; fuzzy 17.65 %, linked 5.62 %) | 1005 / 4557 | 59 / 126 | Camera controller unit written (19 / 21 functions at 100 %) |
| 2026-10-27 | a983432 | 102436 / 720836 bytes (14.21 %; fuzzy 18.68 %, linked 5.62 %) | 1033 / 4557 | 59 / 127 | Sim unit written (28 / 32 functions at 100 %) |
| 2026-10-27 | 7c036e4 | 112724 / 720836 bytes (15.64 %; fuzzy 20.63 %, linked 5.62 %) | 1098 / 4557 | 59 / 128 | Player unit written (65 / 75 functions at 100 %) |
| 2026-10-27 | 1528692 | 113068 / 720836 bytes (15.69 %; fuzzy 20.70 %, linked 5.62 %) | 1104 / 4557 | 59 / 130 | Outfit unit written (6 / 7 functions at 100 %) |
| 2026-10-27 | 2d11c66 | 114220 / 720836 bytes (15.85 %; fuzzy 20.86 %, linked 5.78 %) | 1118 / 4557 | 60 / 131 | Icon set unit (14 / 14 functions, complete) |
| 2026-10-27 | 2db45d2 | 114532 / 720836 bytes (15.89 %; fuzzy 20.90 %, linked 5.82 %) | 1128 / 4557 | 61 / 132 | Object animation archive unit (10 / 10 functions, complete) |
| 2026-10-27 | 58d8e07 | 115796 / 720836 bytes (16.06 %; fuzzy 21.10 %, linked 5.82 %) | 1141 / 4557 | 61 / 133 | Played animation unit written (13 / 14 functions at 100 %) |
| 2026-10-27 | 962673d | 123932 / 720836 bytes (17.19 %; fuzzy 22.23 %, linked 6.95 %) | 1186 / 4557 | 62 / 134 | Action handler unit (45 / 45 functions, complete) |
| 2026-10-27 | cdf7bf7 | 128628 / 720836 bytes (17.84 %; fuzzy 22.88 %, linked 7.60 %) | 1231 / 4557 | 63 / 135 | Visible object unit (45 / 45 functions, complete) |
| 2026-10-27 | 11c7569 | 129068 / 720836 bytes (17.91 %; fuzzy 23.19 %, linked 7.60 %) | 1242 / 4557 | 63 / 136 | Object resource unit written (11 / 14 functions at 100 %) |

| 2026-10-28 | b99637b | 131512 / 720836 bytes (18.24 %; fuzzy 23.56 %, linked 7.60 %) | 1262 / 4557 | 63 / 137 | Scene object manager unit written (18 / 19 functions at 100 %) |
| 2026-10-28 | bd700f4 | 132108 / 720836 bytes (18.33 %; fuzzy 23.79 %, linked 7.60 %) | 1274 / 4557 | 63 / 138 | Object definition database unit written (12 / 14 functions at 100 %) |
| 2026-10-28 | 1d85dfa | 136952 / 720836 bytes (19.00 %; fuzzy 24.64 %, linked 7.60 %) | 1320 / 4557 | 63 / 140 | Scene object unit written (46 / 49 functions at 100 %) |
| 2026-10-28 | 566fd71 | 139308 / 720836 bytes (19.33 %; fuzzy 25.14 %, linked 7.60 %) | 1341 / 4557 | 63 / 141 | Object definition record unit written (20 / 23 functions at 100 %) |
| 2026-10-28 | 945434c | 140304 / 720836 bytes (19.46 %; fuzzy 25.28 %, linked 7.67 %) | 1352 / 4557 | 64 / 141 | Parameter reader units written (11 / 11 functions at 100 %, one unit complete) |
| 2026-10-28 | 0868e43 | 148772 / 720836 bytes (20.64 %; fuzzy 26.61 %, linked 7.67 %) | 1399 / 4557 | 64 / 142 | Script command table unit written (47 / 49 functions at 100 %) |
| 2026-10-28 | 2da285d | 152200 / 720836 bytes (21.11 %; fuzzy 27.38 %, linked 7.60 %) | 1415 / 4557 | 62 / 142 | Parameter reader units merged; weather effects unit written (16 / 18 functions at 100 %) |
| 2026-10-29 | 8167947 | 152356 / 720836 bytes (21.14 %; fuzzy 27.56 %, linked 7.60 %) | 1418 / 4557 | 62 / 144 | Object groups unit written (3 / 7 functions at 100 %) |
| 2026-10-29 | d340d6f | 153176 / 720836 bytes (21.25 %; fuzzy 27.75 %, linked 7.60 %) | 1428 / 4557 | 62 / 145 | Map cell and tile layer unit written (10 / 14 functions at 100 %) |
| 2026-10-29 | c52b08a | 156252 / 720836 bytes (21.68 %; fuzzy 28.18 %, linked 8.02 %) | 1453 / 4557 | 63 / 145 | World unit written, complete (25 / 25 functions) |
| 2026-10-29 | 34d9d19 | 161508 / 720836 bytes (22.41 %; fuzzy 29.42 %, linked 8.02 %) | 1487 / 4556 | 63 / 146 | Lot unit written (34 / 39 functions at 100 %) |
| 2026-10-29 | 72dd10b | 161876 / 720836 bytes (22.46 %; fuzzy 29.42 %, linked 8.02 %) | 1490 / 4556 | 63 / 146 | Tile flag functions matched with a u32 tile index (13 / 14 functions at 100 %) |
| 2026-10-29 | 313b944 | 165152 / 720836 bytes (22.91 %; fuzzy 29.92 %, linked 8.02 %) | 1505 / 4556 | 63 / 147 | Survival guide animation unit written (15 / 16 functions at 100 %) |
| 2026-10-29 | 676cbb2 | 166880 / 720836 bytes (23.15 %; fuzzy 30.16 %, linked 8.26 %) | 1524 / 4556 | 64 / 148 | Inventory server unit complete (19 functions) |
| 2026-10-29 | aa43956 | 168876 / 720836 bytes (23.43 %; fuzzy 30.43 %, linked 8.54 %) | 1541 / 4556 | 66 / 150 | Inventory lists and bulb object units complete (12 and 4 functions) |
| 2026-10-29 | e22bba7 | 171464 / 720836 bytes (23.79 %; fuzzy 30.79 %, linked 8.90 %) | 1561 / 4556 | 67 / 152 | Ambient sound list unit complete (18 functions) |
| 2026-10-29 | e93c1cc | 172972 / 720836 bytes (24.00 %; fuzzy 31.26 %, linked 8.90 %) | 1568 / 4556 | 67 / 154 | Recipe unit written (7 / 10 functions at 100 %) |
| 2026-10-29 | 334da25 | 173892 / 720836 bytes (24.12 %; fuzzy 31.39 %, linked 8.95 %) | 1583 / 4556 | 68 / 154 | Lot file unit complete (10 functions), file factory unit written (5 / 5 functions at 100 %) |
| 2026-10-29 | 0fb9475 | 175708 / 720836 bytes (24.38 %; fuzzy 31.76 %, linked 8.95 %) | 1596 / 4556 | 68 / 156 | Slider widget unit written (13 / 14 functions at 100 %) |
| 2026-10-29 | 3dbd0c6 | 177400 / 720836 bytes (24.61 %; fuzzy 31.99 %, linked 8.95 %) | 1611 / 4556 | 68 / 157 | Panel widget unit written (15 / 15 functions at 100 %) |
| 2026-10-29 | 3d31301 | 181160 / 720836 bytes (25.13 %; fuzzy 32.59 %, linked 8.95 %) | 1637 / 4556 | 68 / 158 | Button widget unit written (27 / 28 functions at 100 %) |
| 2026-10-29 | ddd10e9 | 182636 / 720836 bytes (25.34 %; fuzzy 32.79 %, linked 8.95 %) | 1649 / 4556 | 68 / 159 | Gauge widget unit written (12 / 12 functions at 100 %) |
| 2026-10-29 | d91bdd9 | 183368 / 720836 bytes (25.44 %; fuzzy 33.02 %, linked 8.95 %) | 1663 / 4556 | 68 / 160 | Animated sprite widget unit written (15 / 18 functions at 100 %) |
| 2026-10-29 | e85ba89 | 185224 / 720836 bytes (25.70 %; fuzzy 33.36 %, linked 8.95 %) | 1676 / 4556 | 68 / 161 | Image element unit written (13 / 14 functions at 100 %) |
| 2026-10-29 | 2e4baf1 | 185892 / 720836 bytes (25.79 %; fuzzy 33.45 %, linked 9.05 %) | 1685 / 4556 | 69 / 163 | Sprite meter unit complete (9 functions) |
| 2026-10-29 | 345ea36 | 190904 / 720836 bytes (26.48 %; fuzzy 34.20 %, linked 9.05 %) | 1715 / 4556 | 69 / 165 | Key unit written (31 / 32 functions at 100 %) |
| 2026-10-29 | 529bcfd | 192876 / 720836 bytes (26.76 %; fuzzy 34.94 %, linked 9.05 %) | 1727 / 4556 | 69 / 164 | Keyboard screen unit written (12 / 16 functions at 100 %) |
| 2026-10-29 | 55cc8dc | 196092 / 720836 bytes (27.20 %; fuzzy 35.68 %, linked 9.05 %) | 1762 / 4556 | 69 / 164 | Paged screen unit written (35 / 38 functions at 100 %) |
| 2026-10-29 | 4f5b00d | 200680 / 720836 bytes (27.84 %; fuzzy 37.36 %, linked 9.05 %) | 1785 / 4556 | 69 / 166 | Menu screen unit written (23 / 27 functions at 100 %) |
| 2026-10-29 | 457ca18 | 202028 / 720836 bytes (28.03 %; fuzzy 37.68 %, linked 9.05 %) | 1801 / 4556 | 69 / 167 | Small screen unit written (16 / 19 functions at 100 %) |
| 2026-10-29 | a2d8ccd | 204852 / 720836 bytes (28.42 %; fuzzy 37.68 %, linked 9.05 %) | 1808 / 4556 | 69 / 167 | Screen open / close tests matched (7 functions) |
| 2026-10-29 | 60caf35 | 205648 / 720836 bytes (28.53 %; fuzzy 37.90 %, linked 9.05 %) | 1816 / 4556 | 69 / 168 | Page unit written (8 / 9 functions at 100 %) |
| 2026-10-29 | ee3567b | 206208 / 720836 bytes (28.61 %; fuzzy 38.07 %, linked 9.05 %) | 1823 / 4556 | 69 / 170 | Page 1 unit written (7 / 8 functions at 100 %) |
| 2026-10-29 | 7b35431 | 207960 / 720836 bytes (28.85 %; fuzzy 38.64 %, linked 9.05 %) | 1849 / 4556 | 69 / 173 | Pages 0, 2 and 3 written (26 / 29 functions at 100 %) |
| 2026-10-29 | 6abea0a | 209432 / 720836 bytes (29.05 %; fuzzy 38.84 %, linked 9.05 %) | 1867 / 4556 | 69 / 173 | Page base unit written (18 / 18 functions at 100 %) |
| 2026-10-29 | 224fb3d | 209432 / 720836 bytes (29.05 %; fuzzy 38.84 %, linked 9.05 %) | 1867 / 4556 | 69 / 173 | Page base inline slots named (page vtables 97.7 %) |
| 2026-10-29 | c1dfb2a | 213808 / 720836 bytes (29.66 %; fuzzy 39.45 %, linked 9.65 %) | 1897 / 4556 | 70 / 174 | Page owner unit complete; screens' abstract root (page vtables 100 %) |
| 2026-10-29 | 5e8cb8c | 219792 / 720836 bytes (30.49 %; fuzzy 40.75 %, linked 9.65 %) | 1921 / 4556 | 70 / 175 | Outfit screen unit (24 / 25 functions, constructor 98.34 %) |
| 2026-10-29 | e0c081d | 223740 / 720836 bytes (31.04 %; fuzzy 41.90 %, linked 9.65 %) | 1939 / 4556 | 70 / 176 | Save slot screen unit (18 / 19 functions, constructor 98.64 %) |
| 2026-10-29 | e624b23 | 225700 / 720836 bytes (31.31 %; fuzzy 42.38 %, linked 9.65 %) | 1956 / 4556 | 70 / 177 | Needs screen unit (17 / 18 functions, constructor 99.39 %) |
| 2026-10-29 | cac5945 | 226052 / 720836 bytes (31.36 %; fuzzy 42.43 %, linked 9.70 %) | 1963 / 4556 | 71 / 179 | Screen base unit complete (7 / 7 functions) |
| 2026-10-29 | b93194b | 230040 / 720836 bytes (31.91 %; fuzzy 43.90 %, linked 9.70 %) | 1984 / 4556 | 71 / 179 | Item list screen unit (21 / 26 functions, constructor 98.43 %) |
| 2026-10-29 | 7a6cbc3 | 232348 / 720836 bytes (32.23 %; fuzzy 44.40 %, linked 9.71 %) | 2002 / 4556 | 71 / 180 | Text pager screen unit (17 / 18 functions, constructor 98.32 %) |
| 2026-10-29 | 00b0d91 | 235276 / 720836 bytes (32.64 %; fuzzy 45.78 %, linked 9.71 %) | 2025 / 4556 | 71 / 181 | Object list screen unit (23 / 26 functions, constructor 97.78 %) |
| 2026-10-29 | 09acf7a | 240568 / 720836 bytes (33.37 %; fuzzy 47.36 %, linked 9.71 %) | 2051 / 4556 | 71 / 181 | Tabbed object list screen unit (26 / 29 functions, constructor 98.62 %) |
| 2026-10-30 | 1c0de92 | 246196 / 720836 bytes (34.15 %; fuzzy 48.53 %, linked 9.71 %) | 2073 / 4556 | 71 / 181 | Object text screen unit (22 / 23 functions, constructor 98.98 %) |
| 2026-10-30 | 171eb4d | 250104 / 720836 bytes (34.70 %; fuzzy 50.78 %, linked 9.71 %) | 2092 / 4556 | 71 / 183 | Object detail screen unit (19 / 25 functions, lowest 92.20 %) |
| 2026-10-30 | 0dff7d9 | 252520 / 720836 bytes (35.03 %; fuzzy 51.80 %, linked 9.71 %) | 2111 / 4556 | 71 / 184 | Paged text screen unit (19 / 21 functions, constructor 98.46 %) |
| 2026-10-30 | 563e614 | 254272 / 720836 bytes (35.27 %; fuzzy 52.47 %, linked 9.71 %) | 2121 / 4556 | 71 / 185 | Recipe screen unit (10 / 12 functions, constructor 99.81 %) |
| 2026-10-30 | 9696c1f | 257752 / 720836 bytes (35.76 %; fuzzy 53.52 %, linked 9.71 %) | 2144 / 4556 | 71 / 186 | Category screen unit (23 / 25 functions, constructor 89.76 %) |
| 2026-10-30 | 4c02027 | 260276 / 720836 bytes (36.11 %; fuzzy 54.21 %, linked 9.71 %) | 2164 / 4556 | 71 / 187 | Object text screen unit (20 / 21 functions, constructor 98.96 %) |
| 2026-10-30 | 847fcaf | 268600 / 720836 bytes (37.26 %; fuzzy 55.41 %, linked 9.71 %) | 2199 / 4556 | 71 / 188 | Survival guide unit (35 / 36 functions, `func_020299ec` 96.22 %) |
| 2026-10-30 | 4e1ec9a | 270560 / 720836 bytes (37.53 %; fuzzy 55.77 %, linked 9.71 %) | 2221 / 4556 | 71 / 189 | Transition unit (22 / 23 functions, `func_02027644` 99.45 %) |
| 2026-10-30 | 2d4e7fc | 274376 / 720836 bytes (38.06 %; fuzzy 57.41 %, linked 9.71 %) | 2243 / 4556 | 71 / 191 | Paint screen unit (22 / 32 functions, `.text` fuzzy 97.28 %) |
| 2026-10-30 | db918bb | 275720 / 720836 bytes (38.25 %; fuzzy 57.66 %, linked 9.71 %) | 2260 / 4556 | 71 / 192 | Touch view screen unit (17 / 18 functions, constructor 94.69 %) |
| 2026-10-30 | ce82fc5 | 280824 / 720836 bytes (38.96 %; fuzzy 58.66 %, linked 9.71 %) | 2286 / 4556 | 71 / 193 | Survival guide map unit (26 / 28 functions, `.text` fuzzy 99.85 %) |
| 2026-10-30 | 8924d3d | 286440 / 720836 bytes (39.74 %; fuzzy 60.69 %, linked 9.71 %) | 2322 / 4556 | 71 / 194 | Live mode screen unit (36 / 54 functions, `.text` fuzzy 98.91 %) |
| 2026-10-30 | 483532a | 287832 / 720836 bytes (39.93 %; fuzzy 60.88 %, linked 9.89 %) | 2341 / 4556 | 72 / 196 | Keyboard screen unit (complete, 18 functions) |
| 2026-10-30 | de8550a | 289500 / 720836 bytes (40.16 %; fuzzy 61.11 %, linked 10.12 %) | 2361 / 4556 | 73 / 197 | Credits screen unit (complete, 20 functions) |
| 2026-10-31 | cfd3aa5 | 293264 / 720836 bytes (40.68 %; fuzzy 61.77 %, linked 10.12 %) | 2385 / 4556 | 73 / 196 | Conversation balloon unit (24 / 25 functions, `.text` fuzzy 99.64 %) |
| 2026-10-31 | 64644c8 | 293544 / 720836 bytes (40.72 %; fuzzy 61.81 %, linked 10.16 %) | 2391 / 4556 | 75 / 198 | Telescope and treasure map microgame units (complete, 6 functions) |
| 2026-10-31 | b43e3c5 | 294396 / 720836 bytes (40.84 %; fuzzy 61.93 %, linked 10.28 %) | 2399 / 4556 | 76 / 200 | Microgame base unit (complete, 8 functions) |
| 2026-10-31 | e8937e6 | 295972 / 720836 bytes (41.06 %; fuzzy 63.58 %, linked 10.28 %) | 2419 / 4556 | 76 / 201 | Spear fishing unit (20 / 52 functions, `.text` fuzzy 98.38 %) |

| 2026-10-31 | 0e1f9b1 | 299352 / 720836 bytes (41.53 %; fuzzy 64.05 %, linked 10.75 %) | 2432 / 4556 | 77 / 203 | Instrument microgame unit (complete, 13 functions) |
| 2026-10-31 | fc0d85f | 299796 / 720836 bytes (41.59 %; fuzzy 64.12 %, linked 10.81 %) | 2436 / 4556 | 78 / 205 | Icon View screen unit (complete, 4 functions) |
| 2026-10-31 | fb21e6c | 302148 / 720836 bytes (41.92 %; fuzzy 65.09 %, linked 10.81 %) | 2448 / 4556 | 78 / 205 | Jam microgame unit (12 / 21 functions, `.text` fuzzy 99.36 %) |
| 2026-10-31 | 98a1b54 | 307948 / 720836 bytes (42.72 %; fuzzy 67.46 %, linked 10.81 %) | 2485 / 4556 | 78 / 206 | Rod fishing unit (37 / 50 functions, `.text` fuzzy 98.25 %) |
| 2026-10-31 | ad62980 | 309968 / 720836 bytes (43.00 %; fuzzy 67.88 %, linked 10.81 %) | 2503 / 4556 | 78 / 207 | Shared fishing units (18 / 21 functions, `.text` fuzzy 99.2 %) |
| 2026-10-31 | 29e785a | 311892 / 720836 bytes (43.27 %; fuzzy 69.27 %, linked 10.81 %) | 2527 / 4556 | 78 / 208 | Fire microgame unit (24 / 33 functions, `.text` fuzzy 97.81 %) |
| 2026-10-31 | 21c177a | 312624 / 720836 bytes (43.37 %; fuzzy 69.37 %, linked 10.91 %) | 2542 / 4556 | 79 / 210 | Fish base unit, complete (15 / 15 functions) |
| 2026-10-31 | 53d608c | 313120 / 720836 bytes (43.44 %; fuzzy 69.44 %, linked 10.98 %) | 2547 / 4556 | 80 / 211 | Sprite animation unit, complete (5 / 5 functions) |
| 2026-10-31 | 7b13d34 | 315520 / 720836 bytes (43.77 %; fuzzy 70.91 %, linked 10.98 %) | 2585 / 4556 | 80 / 212 | Collecting microgame unit (38 / 57 functions, `.text` fuzzy 95.99 %) |
| 2026-10-31 | ae1fde8 | 316484 / 720836 bytes (43.91 %; fuzzy 71.05 %, linked 11.11 %) | 2602 / 4556 | 81 / 212 | Scene element unit, complete (17 / 17 functions) |
| 2026-10-31 | e90bba8 | 316800 / 720836 bytes (43.95 %; fuzzy 71.31 %, linked 11.11 %) | 2608 / 4556 | 81 / 214 | Tool use action unit (6 / 9 functions, `.text` 97.20 %) |
| 2026-10-31 | 9f7c053 | 318600 / 720836 bytes (44.20 %; fuzzy 71.62 %, linked 11.32 %) | 2622 / 4556 | 82 / 216 | Upgrade action units: "Action Upgrade" complete (6 / 6 functions), "Action Upgrade Indirectly" 8 / 9 |
| 2026-10-31 | d53c8fd | 319816 / 720836 bytes (44.37 %; fuzzy 71.79 %, linked 11.49 %) | 2634 / 4556 | 83 / 217 | Sleep action unit, complete (12 / 12 functions) |
| 2026-10-31 | 11e20d2 | 319996 / 720836 bytes (44.39 %; fuzzy 71.82 %, linked 11.51 %) | 2643 / 4556 | 84 / 218 | Simple Slave action unit, complete (9 / 9 functions) |
| 2026-10-31 | 85c6a5f | 320908 / 720836 bytes (44.52 %; fuzzy 71.94 %, linked 11.51 %) | 2659 / 4556 | 84 / 219 | Sim Animation unit, all at 100 %, not complete (base D1 kept far) |
| 2026-10-31 | c2a7a97 | 321036 / 720836 bytes (44.54 %; fuzzy 72.06 %, linked 11.51 %) | 2663 / 4556 | 84 / 220 | ShakeTree action unit (4 / 5 functions, `.text` 99.79 %) |
| 2026-10-31 | 1340482 | 321172 / 720836 bytes (44.56 %; fuzzy 72.18 %, linked 11.51 %) | 2668 / 4556 | 84 / 221 | Abstract action unit (5 / 6 functions, `.text` 99.85 %) |
| 2026-10-31 | 32aec6a | 322180 / 720836 bytes (44.70 %; fuzzy 72.57 %, linked 11.51 %) | 2677 / 4556 | 84 / 222 | Interaction base unit (9 / 11 functions, `.text` 99.84 %) |
| 2026-10-31 | cdb51dc | 322592 / 720836 bytes (44.75 %; fuzzy 72.63 %, linked 11.57 %) | 2684 / 4556 | 85 / 223 | Change clothing action unit (complete, 7 / 7 functions) |
| 2026-10-31 | 89005ed | 323656 / 720836 bytes (44.90 %; fuzzy 72.77 %, linked 11.72 %) | 2703 / 4556 | 86 / 224 | Action list unit (complete, 19 / 19 functions) |
| 2026-10-31 | aa4c0d0 | 326364 / 720836 bytes (45.28 %; fuzzy 73.15 %, linked 12.22 %) | 2709 / 4556 | 88 / 225 | Action pool and factory unit (complete, 6 / 6 functions); sim animation unit complete |
| 2026-10-31 | a22de27 | 329112 / 720836 bytes (45.66 %; fuzzy 73.34 %, linked 12.53 %) | 2719 / 4556 | 90 / 226 | Base action unit (complete, 8 / 8 functions); abstract action unit complete |
| 2026-11-01 | ad4b8cf | 330640 / 720836 bytes (45.87 %; fuzzy 73.55 %, linked 12.75 %) | 2731 / 4556 | 91 / 227 | Play Microgame action unit (complete, 11 / 11 functions) |
| 2026-11-01 | ebf2e78 | 331244 / 720836 bytes (45.95 %; fuzzy 73.64 %, linked 12.83 %) | 2742 / 4556 | 92 / 228 | Play Instrument action unit (complete, 11 / 11 functions) |
| 2026-11-01 | 0800a12 | 331880 / 720836 bytes (46.04 %; fuzzy 73.72 %, linked 12.92 %) | 2751 / 4556 | 93 / 229 | Plant Seed action unit (complete, 9 / 9 functions) |
| 2026-11-01 | 6ed8b6a | 332820 / 720836 bytes (46.17 %; fuzzy 73.85 %, linked 13.05 %) | 2760 / 4556 | 94 / 230 | Place Object action unit (complete, 9 / 9 functions) |
| 2026-11-01 | 6f7fff4 | 333652 / 720836 bytes (46.29 %; fuzzy 73.97 %, linked 13.16 %) | 2768 / 4556 | 95 / 231 | Action Pickup unit (complete, 8 / 8 functions) |
| 2026-11-01 | 66353c1 | 335796 / 720836 bytes (46.58 %; fuzzy 74.37 %, linked 13.16 %) | 2784 / 4556 | 95 / 232 | Move actions unit, 16 of 17 functions |
| 2026-11-01 | db53064 | 337464 / 720836 bytes (46.82 %; fuzzy 74.60 %, linked 13.39 %) | 2797 / 4556 | 96 / 233 | Motive Failure action unit (complete, 13 / 13 functions) |
| 2026-11-01 | 222d596 | 337780 / 720836 bytes (46.86 %; fuzzy 74.64 %, linked 13.44 %) | 2805 / 4556 | 97 / 234 | Action Interact unit (complete, 8 / 8 functions) |
| 2026-11-01 | 868eae6 | 338108 / 720836 bytes (46.90 %; fuzzy 74.69 %, linked 13.48 %) | 2814 / 4556 | 98 / 235 | Immediate action unit (complete, 9 / 9 functions) |
| 2026-11-01 | b2f8838 | 338980 / 720836 bytes (47.03 %; fuzzy 74.81 %, linked 13.60 %) | 2823 / 4556 | 99 / 236 | Give Gift action unit (complete, 9 / 9 functions) |
| 2026-11-01 | 16b96c4 | 339232 / 720836 bytes (47.06 %; fuzzy 74.84 %, linked 13.64 %) | 2833 / 4556 | 100 / 237 | Display Task Reminder action unit (complete, 10 / 10 functions) |
| 2026-11-01 | 30f6620 | 341184 / 720836 bytes (47.33 %; fuzzy 75.11 %, linked 13.91 %) | 2847 / 4556 | 101 / 238 | Dig or Dive action unit (complete, 14 / 14 functions) |
