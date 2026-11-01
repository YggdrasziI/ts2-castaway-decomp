/*
 * Unit 0x02053204-0x02053408: a file factory (Unk02053204, vtable 0x020BA258)
 * that maps the file ids to kinds (negative ids give 16, the lot blocks
 * 0x100FF-0x10109 and a run of negative ids give 3000, 0x102FF gives 3002,
 * others 1) and creates the file of a kind: Unk02095bf4 for 2000, the lot file
 * Unk0205356c for 3000, the plain file class Unk020533d8 (vtable 0x020BA238)
 * for 3002.
 *
 * Bounds: hypothesis. Before 0x02053204 is unit_02052814.cpp (no call to or
 * from this code); the destructors this file emits (factory D0, then D1 / D0 of
 * Unk020533d8) close it, as in unit_02095BF4.cpp; 0x02053408
 * starts the lot file class. `.data` is the two vtables. The factory D1 in
 * the vtable is the kept copy 0x02002128 of unit_02001FDC.cpp. Real file name
 * unknown.
 */

#include "game/unk_file.h"

class Unk02095bf4 : public Unk0209487c {
public:
    Unk02095bf4(void *data);
    ~Unk02095bf4();

    int unk3c[11];
};

/* The lot file (unit_02053408.cpp). */
class Unk0205356c : public Unk0209487c {
public:
    Unk0205356c(void *data);
    ~Unk0205356c();

    void *header;
    void *rooms;
    int unk44;
    void *records;
    void *records2;
};

class Unk02095c74Base {
public:
    virtual ~Unk02095c74Base() {}
    virtual int func_02095c74(int id) = 0;
    virtual Unk0209487c *func_02095cd0(void *data, int kind) = 0;
};

class Unk02053204 : public Unk02095c74Base {
public:
    int func_02095c74(int id);
    Unk0209487c *func_02095cd0(void *data, int kind);
};

/*
 * A file of the kind 3002: the file class alone. Defined after the factory, so the vtables
 * come out in the original order (this class first).
 * The destructor is written out for D1 before D0.
 */
class Unk020533d8 : public Unk0209487c {
public:
    Unk020533d8(void *data) : Unk0209487c(data) {}
    ~Unk020533d8() {}
};

int Unk02053204::func_02095c74(int id) {
    if (id < 0) {
        return 0x10;
    }
    switch (id) {
    case (int)0xfffefef7:
    case (int)0xfffefefa:
    case (int)0xfffefefb:
    case (int)0xfffefefc:
    case (int)0xfffefefe:
    case (int)0xfffefeff:
    case (int)0xfffeff00:
    case (int)0xfffeff01:
    case 0x100ff:
    case 0x10100:
    case 0x10101:
    case 0x10102:
    case 0x10104:
    case 0x10105:
    case 0x10106:
    case 0x10109:
        return 3000;
    case 0x102ff:
        return 3002;
    }
    return 1;
}

Unk0209487c *Unk02053204::func_02095cd0(void *data, int kind) {
    Unk0209487c *file;
    switch (kind) {
    case 2000:
        file = new Unk02095bf4(data);
        break;
    case 3000:
        file = new Unk0205356c(data);
        break;
    case 3002:
        file = new Unk020533d8(data);
        break;
    default:
        return 0;
    }
    return file;
}
