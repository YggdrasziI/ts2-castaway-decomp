/*
 * Unit 0x02054330-0x02054734: the bulb object Unk020bfc68 (one static object
 * data_020bfc68, 0x18 bytes). Set from an object definition that has a bulb
 * (key 0xB7324824) whose id (key 0x798B86AC) is a known definition not yet in
 * the inventory, it adds that bulb to the inventory and shows a two-frame
 * sprite from the archive file of hash 0x926D551E. Each update, a touch near
 * (0x85, 0x0F) gives the bulb to the main game state; while the bulb is in the
 * inventory once, the sprite blinks every 21 updates and plays
 * "GROUP_SE_COMMON SE_BULB" up to six times; otherwise the sprite is reset and
 * the object stops when the player has flag 0x20.
 *
 * Bounds: hypothesis. The constructor 0x02054330 opens the range; it is the
 * only function of the static initializer 0x020AD1FC, which comes before that
 * of the inventory lists (0x020AD210, code from 0x02054734). The code before
 * 0x02054330 (from 0x0205359C) has no static initializer and is not delinked
 * yet. `.data` is the sound name, `.bss` the object. Real file name unknown.
 *
 * Functions other than the constructor keep C linkage: other files call them
 * by their addresses.
 */

#include "game/unk_archive.h"
#include "game/unk_oam.h"

/* An object definition: only the id at 0x0C is used here. */
struct Unk0205cf00 {
    int unk0[3];
    int unkc;
};

/* The object definition database (unit_0205F16C.cpp). */
struct Unk020c3fc4;

/* The player (data_020c43a8). */
struct Unk020c43a8;

/* The system (data_020d6240): only the fields used here. */
struct Unk020d6240 {
    int unk0;
    void *input;
    int unk8[3];
    Unk02093648 *archive;
};

/* The main game state (unit_0206BCE0.cpp): only the function used here. */
class Unk0206bcf0 {
public:
    bool func_0206f3e8(Unk0205cf00 *def, int b, int c, u8 d);
};

class Unk020bfc68 {
public:
    Unk020bfc68();

    Unk0208f8b0 *sprite;
    int unk4;
    Unk0205cf00 *def;
    u16 timer;
    u16 sounds;
    u32 hash;
    bool active;
    bool shown;
};

/* An inventory entry (unit_02054AB4.cpp). */
struct Unk02054dc4 {
    Unk0205cf00 *def;
    int count;
};

extern Unk020c3fc4 data_020c3fc4;
extern Unk020c43a8 data_020c43a8;
extern Unk020d6240 data_020d6240;
extern unsigned char data_020bfc9c[];

int *func_02097a4c();

extern "C" {

Unk020d6240 *func_020a18e4();
bool func_0206757c(Unk020c43a8 *p, int mask);
bool func_020a075c(void *input, int index);
Unk0206bcf0 *func_0206bce0();
void *func_020a2994();
u32 func_0209a32c(const u32 *str, u32 last, u32 end);
int func_020a2ce8(void *sound, u32 hash, int volume, int unk);
int func_0205d340(Unk0205cf00 *def, u32 key);
int func_0205d1b4(Unk0205cf00 *def, u32 key);
int func_0205f6a4(Unk020c3fc4 *db, int id);
Unk0205cf00 *func_0205f6f8(Unk020c3fc4 *db, int id);
Unk02054dc4 *func_02054dc4(void *p, Unk0205cf00 *def, int a);
int func_02054c1c(void *p, Unk0205cf00 *def, int a);

void func_02054360(Unk020bfc68 *p);
int func_020543d4(Unk020bfc68 *p);
int func_0205465c(Unk020bfc68 *p, Unk0205cf00 *def, bool a);

}

Unk020bfc68 data_020bfc68;

Unk020bfc68::Unk020bfc68() {
    sprite = 0;
    def = 0;
    timer = 0;
    hash = 0x926d551e;
    active = false;
    shown = false;
}

void func_02054360(Unk020bfc68 *p) {
    if (!p->shown) {
        return;
    }
    Unk020916a4::func_02091820()->func_02091c68(p->sprite);
    p->sprite = 0;
    p->shown = false;
    Unk02093648 *archive = func_020a18e4()->archive;
    archive->func_02093c58(archive->func_02093e9c(p->hash));
    if (func_0206757c(&data_020c43a8, 0x20)) {
        p->active = false;
    }
}

static inline int func_wrapped(int frame) {
    return frame != 0;
}

int func_020543d4(Unk020bfc68 *p) {
    if (p->active) {
        if (!p->shown) {
            Unk02093648 *archive = func_020a18e4()->archive;
            Unk02095140 *file = (Unk02095140 *)archive->func_02093a9c(archive->func_02093e9c(p->hash));
            Unk020916a4 *oam = Unk020916a4::func_02091820();
            p->sprite = oam->func_020919e4((int)file, 0x3c);
            if (p->sprite != 0) {
            p->sprite->func_0208fb98(0xc);
            p->sprite->func_0208fb80(0xa);
            p->sprite->unk0 = 0x7b000;
            p->sprite->unk4 = 0x5000;
            p->sprite->func_0208faac(0);
            oam->func_0209201c(file, 0, 0, 0xc0, 0x10);
            oam->func_0209185c(true);
            p->timer = 0;
            p->sounds = 6;
            p->shown = true;
            } else {
                return 0;
            }
        }
        if (func_020a075c(data_020d6240.input, 1)) {
            int dx = 0x85 - func_02097a4c()[0];
            int dy = 0xf - func_02097a4c()[1];
            if (dx * dx + dy * dy < 400 && func_0206bce0()->func_0206f3e8(p->def, 1, 1, 1)) {
                func_02054360(p);
                return 1;
            }
        }
        Unk02054dc4 *e = func_02054dc4(data_020bfc9c, p->def, 0);
        if (e != 0 && e->count == 1) {
            p->timer++;
            if (p->timer > 20) {
                p->timer = 0;
                int frame = p->sprite->func_0208faa4() + 1;
                if (frame >= p->sprite->func_0208fa84()) {
                    frame = 0;
                }
                p->sprite->func_0208faac(frame);
                if (func_wrapped(frame) && p->sounds != 0) {
                    p->sounds--;
                    void *sound = func_020a2994();
                    func_020a2ce8(sound, func_0209a32c((const u32 *)"GROUP_SE_COMMON SE_BULB", 0, 0), 0x7f, 0);
                }
            }
            return 0;
        }
        p->sprite->func_0208faac(0);
        if (func_0206757c(&data_020c43a8, 0x20)) {
            p->active = false;
            func_02054360(p);
        }
    }
    return 0;
}

static inline bool func_known(Unk020c3fc4 *db, int id) {
    return func_0205f6a4(db, id) != -1;
}

int func_0205465c(Unk020bfc68 *p, Unk0205cf00 *def, bool a) {
    if (def != 0 && func_0205d340(def, 0xb7324824)) {
        Unk020c3fc4 *db = &data_020c3fc4;
        int id = func_0205d1b4(def, 0x798b86ac);
        if (id != 0 && func_known(db, id)) {
            Unk0205cf00 *bulb = func_0205f6f8(&data_020c3fc4, id);
            if (func_02054dc4(data_020bfc9c, bulb, 0) == 0) {
                func_02054c1c(data_020bfc9c, bulb, 0);
                if (!a) {
                    func_02054360(p);
                }
                p->def = bulb;
                p->active = a;
                return 1;
            }
        }
    }
    return 0;
}
