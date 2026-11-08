/*
 * Unit 0x0205359C-0x02054330: a recipe read from an object definition
 * (Unk0205367c, 0x2C bytes): up to five ingredients (keys 0xFCA7EA3A-0xFCA7EA3E)
 * with the count of each, a result (key 0x3C8AC2D9) and an alternative result
 * (key 0xE66202A7), and per item a flag (keys 0xA92942D5-0xA92942D9,
 * 0x9E0D169E) cleared once the item is in the collection. The functions test
 * whether the inventory holds the ingredients, consume them and give the
 * result, and place the item icons, counts and plus signs of a recipe panel.
 * func_0205359c adds the two items of a definition (keys 0xF7D71823,
 * 0x617D8B84) that are not in the inventory yet.
 *
 * Bounds: hypothesis. No static initializer marks this file. Before 0x0205359C
 * comes the lot file class (unit_02053408.cpp, which ends with its
 * destructors), with no call to or from this code; 0x02054330 starts
 * unit_02054330.cpp. `.rodata` is the three key tables (0x020AEF70-0x020AEFA4,
 * only used here; unit_020582E0.cpp follows). Real file name unknown.
 *
 * All functions keep C linkage: other files call them by their addresses.
 */

#include "game/unk_archive.h"
#include "game/unk_oam.h"
#include "game/unk_script.h"

/* An object definition: only the id at 0x0C and the script at 0x10 are used here. */
struct Unk0205cf00 {
    int unk0[3];
    int unkc;
    Unk020956f8 *script;
};

/* The object definition database (unit_0205F16C.cpp). */
struct Unk020c3fc4;

/* The collection: a sorted set of ints (unit_0206B630.cpp). */
class Unk0206b630 {
public:
    bool func_0206b6bc(int value);
};

/* The game settings (data_020d60c8): only the field used here. */
struct Unk020d60c8 {
    int unk0;
    Unk0206b630 *collection;
};

/* The system (data_020d6240): only the field used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    int unk8[3];
    Unk02093648 *archive;
};

/* An inventory entry (unit_02054AB4.cpp). */
struct Unk02054dc4 {
    Unk0205cf00 *def;
    int count;
};

/* A sprite. */
struct Unk020a7c90;

/* The sprites of a recipe panel. */
struct Unk02053bf8 {
    Unk020a7c90 *icons[6];
    Unk020a7c90 *counts[5];
    Unk020a7c90 *plus[4];
    Unk020a7c90 *arrow;
};

/* A screen position. */
struct Unk02053ef8 {
    int x;
    int y;
};

struct Unk0205367c {
    Unk0205cf00 *def;
    Unk0205cf00 *items[6];
    u8 counts[5];
    bool flags[6];
    Unk0205cf00 *result;
};

extern Unk020c3fc4 data_020c3fc4;
extern Unk020d60c8 data_020d60c8;
extern unsigned char data_020bfc9c[];
extern const int data_020ae7cc[];

extern "C" {

Unk020d6240 *func_020a18e4();
int func_0205d134(Unk0205cf00 *def, int key);
int func_0205d1b4(Unk0205cf00 *def, int key);
bool func_0205d340(Unk0205cf00 *def, int key);
int func_0205d39c(Unk0205cf00 *def, int key);
int func_0205f6a4(Unk020c3fc4 *db, int id);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
int func_02054c1c(void *p, Unk0205cf00 *def, int a);
void func_02054cf0(void *p, Unk02054dc4 *e, int a);
Unk02054dc4 *func_02054dc4(void *p, Unk0205cf00 *def, int a);
u32 func_0206446c(int key);
int func_020644b0(int key);
int func_020644bc(int key);
void func_0203c254(int value, int index, int a);
void func_020a6980(Unk020a7c90 *s, u32 hash);
void func_020a69ac(Unk020a7c90 *s, int palette);
void func_020a7c90(Unk020a7c90 *s, int x);
int func_020a7ca4(Unk020a7c90 *s);
void func_020a7cac(Unk020a7c90 *s, int y);
void func_020a7cf0(Unk020a7c90 *s, bool show);
int func_020a7d44(Unk020a7c90 *s);

bool func_0205359c(Unk0205cf00 *def);
Unk0205367c *func_0205367c(Unk0205367c *t, Unk0205cf00 *def);
int func_02053914(Unk0205367c *t);
bool func_02053940(Unk0205367c *t);
void func_020539b0(Unk0205367c *t);
int func_02053b84(Unk0205367c *t);
Unk0205cf00 *func_02053bd8(Unk0205367c *t, int index);
Unk0205cf00 *func_02053be4(Unk0205367c *t);
void func_02053bf8(Unk02053bf8 *ui, Unk0205367c *t, Unk02053ef8 *pos, bool plus);
void func_02053ef8(Unk02053bf8 *ui, Unk0205367c *t, Unk02053ef8 *pos, bool plus);

}

/* A pixel value as 20.12 fixed point, rounded. */
#define FX32(v) ((int)((v) > 0 ? (v) * 4096 + 0.5f : (v) * 4096 - 0.5f))

static inline bool func_known(Unk020c3fc4 *db, int id) {
    return func_0205f6a4(db, id) != -1;
}

/*
 * 98.93 %: the original keeps the database in r7, the inventory in r8 and the
 * id / item in r6 (ours r8, r6, r7). Tried: database and inventory locals in
 * every declaration order, the id declared before the loop, inline helpers
 * for the lookup and for the addition.
 */
bool func_0205359c(Unk0205cf00 *def) {
    if (def == 0) {
        return false;
    }
    int keys[2] = {0xf7d71823, 0x617d8b84};
    int n = 0;
    for (int i = 0; i < 2; i++) {
        int id = func_0205d1b4(def, keys[i]);
        if (id != 0 && func_known(&data_020c3fc4, id)) {
            Unk0205cf00 *item = func_0205f6f8(&data_020c3fc4, id);
            if (func_02054dc4(data_020bfc9c, item, 0) == 0) {
                func_02054c1c(data_020bfc9c, item, 1);
                n++;
            }
        }
    }
    return n > 0;
}

/*
 * 99.46 %: in the last loop the original keeps the id in r8 and the counter in
 * r9 (ours swapped). Tried: a new or reused id local, the counter declared
 * outside the loop, the operands of the special id test swapped, the ids
 * array read at each use.
 */
Unk0205367c *func_0205367c(Unk0205367c *t, Unk0205cf00 *def) {
    t->def = def;
    int countKeys[5] = {0xfca7ea3a, 0xfca7ea3b, 0xfca7ea3c, 0xfca7ea3d, 0xfca7ea3e};
    int flagKeys[6] = {0xa92942d5, 0xa92942d6, 0xa92942d7, 0xa92942d8, 0xa92942d9, 0x9e0d169e};
    int ids[6];
    u32 n = 0;
    for (int i = 0; i < 6; i++) {
        t->flags[i] = func_0205d1b4(def, flagKeys[i]) != 0;
    }
    for (u32 i = 0; i < 5; i++) {
        int id = func_0205d1b4(def, countKeys[i]);
        if (id == 0) {
            continue;
        }
        bool found = false;
        for (u32 j = 0; j < n && !found; j++) {
            if (id == ids[j]) {
                t->counts[j]++;
                found = true;
            }
        }
        if (!found) {
            t->counts[n] = 1;
            ids[n] = id;
            n++;
        }
    }
    for (; n < 5; n++) {
        ids[n] = 0;
    }
    Unk020c3fc4 *db = &data_020c3fc4;
    ids[5] = func_0205d1b4(def, 0x3c8ac2d9);
    t->result = 0;
    int id = func_0205d1b4(def, 0xe66202a7);
    if (id != 0 && func_known(db, id)) {
        t->result = func_0205f6f8(db, id);
    }
    int special = func_0205d1b4(def, 0xe3c88ec6);
    Unk0206b630 *collection = data_020d60c8.collection;
    for (u32 i = 0; i < 6; i++) {
        id = ids[i];
        if (id != 0 && func_known(db, id)) {
            t->items[i] = func_0205f6f8(db, id);
            if (id == special) {
                t->flags[i] = true;
            }
            if (t->flags[i]) {
                t->flags[i] = !collection->func_0206b6bc(t->items[i]->unkc);
            }
        } else {
            t->items[i] = 0;
        }
    }
    return t;
}

int func_02053914(Unk0205367c *t) {
    int n = 0;
    for (int i = 0; i < 5; i++) {
        if (t->items[i] != 0) {
            n++;
        }
    }
    return n;
}

bool func_02053940(Unk0205367c *t) {
    for (u32 i = 0; i < 5 && t->items[i] != 0; i++) {
        Unk02054dc4 *e = func_02054dc4(data_020bfc9c, t->items[i], 0);
        if (e == 0) {
            return false;
        }
        if (e->count < t->counts[i]) {
            return false;
        }
    }
    return true;
}

void func_020539b0(Unk0205367c *t) {
    if (!func_02053940(t)) {
        return;
    }
    for (u32 i = 0; i < 5 && t->items[i] != 0; i++) {
        for (u32 j = 0; j < t->counts[i]; j++) {
            if (!func_0205d340(t->items[i], 0x1e1a6a8c)) {
                Unk02054dc4 *e = func_02054dc4(data_020bfc9c, t->items[i], 0);
                if (e != 0) {
                    func_02054cf0(data_020bfc9c, e, 0);
                }
            }
        }
    }
    Unk0205cf00 *out = t->items[5];
    if (func_0205d340(out, 0x891a34ba)) {
        func_02054c1c(data_020bfc9c, out, 0xff);
        Unk02054dc4 *e = func_02054dc4(data_020bfc9c, out, 0);
        if (func_0205d340(out, data_020ae7cc[9]) || func_0205d340(out, data_020ae7cc[8])) {
            e->count = func_0205d134(out, 0x2b3e6dd7) + 1;
        }
    } else {
        func_02054c1c(data_020bfc9c, out, 0);
    }
    if (out->script->func_020957ec(0x52821629)) {
        func_0205d39c(out, 0x52821629);
    }
    Unk02054dc4 *e = func_02054dc4(data_020bfc9c, t->def, 0);
    if (e == 0) {
        return;
    }
    if (!func_0205d340(out, 0x3d9aefc0)) {
        e->count = 2;
        return;
    }
    func_02054cf0(data_020bfc9c, e, 0);
}

int func_02053b84(Unk0205367c *t) {
    u32 i;
    Unk0205cf00 *item;
    for (i = 0; i < 5 && (item = t->items[i]) != 0; i++) {
        if (func_0205d340(item, 0x1e1a6a8c)) {
            return item->unkc;
        }
    }
    return 0;
}

Unk0205cf00 *func_02053bd8(Unk0205367c *t, int index) {
    return t->items[index];
}

Unk0205cf00 *func_02053be4(Unk0205367c *t) {
    Unk0205cf00 *def = t->result;
    if (def == 0) {
        def = t->items[5];
    }
    return def;
}

void func_02053bf8(Unk02053bf8 *ui, Unk0205367c *t, Unk02053ef8 *pos, bool plus) {
    int key9 = data_020ae7cc[9];
    int key8 = data_020ae7cc[8];
    for (u32 i = 0; i < 6; i++) {
        if (ui->icons[i] == 0) {
            continue;
        }
        if (func_02053bd8(t, i) == 0) {
            func_020a7cf0(ui->icons[i], false);
            continue;
        }
        int icon;
        if (t->flags[i]) {
            icon = 0x1a004;
        } else {
            icon = func_0205d134(func_02053bd8(t, i), 0x9d5bba8e);
            if (icon == -1) {
                func_020a7cf0(ui->icons[i], false);
                continue;
            }
        }
        u32 map = func_0206446c(icon);
        int palette = func_020644bc(icon);
        int bank = func_020644b0(icon);
        if (map != 0) {
            int index = func_020a18e4()->archive->func_02093e9c(map);
            if (index != -1) {
                func_020a6980(ui->icons[i], map);
                func_020a69ac(ui->icons[i], palette);
                Unk0209487c *file = func_020a18e4()->archive->func_02093a9c(index);
                Unk020916a4 *oam = Unk020916a4::func_02091830();
                oam->func_0209201c((Unk02095140 *)file, palette, bank << 4, func_020a7d44(ui->icons[i]) << 4, 0x10);
                func_020a18e4()->archive->func_02093c3c(file);
            } else {
                func_020a7cf0(ui->icons[i], false);
                continue;
            }
        }
        Unk0205cf00 *item = func_02053bd8(t, i);
        if ((func_0205d340(item, key9) || func_0205d340(item, key8)) && !t->flags[i]) {
            Unk02054dc4 *e = func_02054dc4(data_020bfc9c, item, 0);
            int n;
            if (e != 0) {
                n = e->count - 1;
            } else {
                n = func_0205d134(item, 0x2b3e6dd7);
            }
            if (i == 5) {
                n = func_0205d134(item, 0x2b3e6dd7);
            }
            func_0203c254(n, func_020a7d44(ui->icons[i]), 0);
        }
        func_020a7cf0(ui->icons[i], true);
    }
    for (u32 i = 0; i < 5; i++) {
        if (func_02053bd8(t, i) != 0) {
            func_020a7cf0(ui->counts[i], true);
        } else {
            func_020a7cf0(ui->counts[i], false);
        }
    }
    if (plus) {
        for (u32 i = 0; i < 4; i++) {
            if (func_02053bd8(t, i + 1) != 0) {
                func_020a7cf0(ui->plus[i], true);
            } else {
                func_020a7cf0(ui->plus[i], false);
            }
        }
    }
    func_02053ef8(ui, t, pos, plus);
}

/*
 * 92.26 %: the original neither folds offset = dy - 0x20 (it reloads dy) nor
 * strength-reduces y0 * 4096 in the row loop, so its frame is 0x30 bytes with
 * y0 at 0xC; ours folds the first, keeps y0 * 4096 as a spilled induction
 * value (frame 0x34) and the registers of the inner loop differ. Tried: the
 * declaration orders, a local struct for the layout, volatile y0, the
 * increments in the for statement, other loop forms, an inline conversion
 * function. The pixel offsets 1, 0x1A, 0xC, 0x32 and 0x24 are locals: the
 * original converts them at run time (_fflt), which a literal would fold.
 */
void func_02053ef8(Unk02053bf8 *ui, Unk0205367c *t, Unk02053ef8 *pos, bool plus) {
    u32 index;
    int colX;
    int dy;
    int resultY;
    int x0;
    int countY;
    int countX;
    int dx;
    int y0;
    int c;
    int offset;
    int n;
    int rows;
    int x;
    u32 cols;
    int arrowY;
    int arrowX;
    u32 y;
    int rowX;
    int r;
    int plusY;
    n = func_02053914(t);
    dy = 0x16;
    rows = 2;
    offset = dy - 0x20;
    x0 = 0x20;
    y0 = 0x12;
    dx = 0x2d;
    cols = 3;
    arrowX = 0x9f;
    switch (n) {
    case 1:
        rows = 1;
        cols = 1;
        x0 += 0x28;
        dx += 0x10;
        offset -= 8;
        y0 = 0x24;
        arrowX = 0x75;
        break;
    case 2:
        cols = rows;
        x0 += 0xa;
        dx += 0x10;
        offset -= 8;
        rows = 1;
        y0 = 0x24;
        arrowX = 0x8d;
        break;
    case 3:
        rows = 1;
        y0 = 0x24;
        break;
    case 4:
        cols = rows;
        x0 += 8;
        dx += 8;
        offset -= 4;
        dy += 4;
        arrowX = 0xa2;
        break;
    }
    countX = 1;
    countY = 0x1a;
    plusY = 0xc;
    arrowY = 0x32;
    resultY = 0x24;
    index = 0;
    for (r = 0, rowX = 0; r < rows; r++) {
        y = pos->y + FX32(y0);
        colX = 0;
        for (c = 0; c < cols && index < 5;) {
            if (func_02053bd8(t, index) == 0) {
                index++;
                continue;
            }
            x = pos->x + FX32(x0 + colX + rowX);
            func_020a7c90(ui->icons[index], x);
            func_020a7cac(ui->icons[index], y);
            func_020a7c90(ui->counts[index], x + FX32(countX));
            func_020a7cac(ui->counts[index], y + FX32(countY));
            if (index > 0 && plus) {
                func_020a7c90(ui->plus[index - 1], x + FX32(offset));
                func_020a7cac(ui->plus[index - 1], y + FX32(plusY));
            }
            c++;
            colX += dx;
            index++;
        }
        y0 += 0x25;
        rowX += dy;
    }
    if (!plus) {
        return;
    }
    func_020a7c90(ui->arrow, pos->x + FX32(arrowX));
    func_020a7cac(ui->arrow, pos->y + FX32(arrowY));
    func_020a7c90(ui->icons[5], func_020a7ca4(ui->arrow) + 0x10000);
    func_020a7cac(ui->icons[5], pos->y + FX32(resultY));
}
