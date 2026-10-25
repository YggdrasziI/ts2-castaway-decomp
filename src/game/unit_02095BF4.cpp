/*
 * Unit 0x02095BF4-0x02095D1C: a resource file class (Unk02095bf4, 0x68 bytes)
 * derived from the file class Unk0209487c, and a factory (Unk02095c74) that maps
 * the file ids 100000-100010 to the kind 2000 (negative ids give 16, others 1) and
 * creates an Unk02095bf4 for the kind 2000.
 *
 * Bounds: hypothesis. Before 0x02095BF4 come the destructors of the class with
 * vtable data_020bd454; 0x02095D1C starts unit_02095D1C.cpp. Nothing references
 * the factory vtable data_020bd474: it is emitted with the factory's first virtual
 * function. The implicit factory destructors (D0, then D1) close the file. Real
 * file name unknown.
 */

#include "game/unk_file.h"

class Unk02095bf4 : public Unk0209487c {
public:
    Unk02095bf4(void *data);
    ~Unk02095bf4();

    int unk3c[11];
};

class Unk02095c74Base {
public:
    virtual ~Unk02095c74Base() {}
    virtual int func_02095c74(int id) = 0;
    virtual Unk0209487c *func_02095cd0(void *data, int kind) = 0;
};

class Unk02095c74 : public Unk02095c74Base {
public:
    int func_02095c74(int id);
    Unk0209487c *func_02095cd0(void *data, int kind);
};

Unk02095bf4::Unk02095bf4(void *data) : Unk0209487c(data) {
    unk3c[0] = 0;
    unk3c[1] = 0;
    unk3c[2] = 0;
    unk3c[3] = 0;
    unk3c[4] = 0;
    unk3c[5] = 0;
    unk3c[6] = 0;
    unk3c[7] = 0;
    unk3c[8] = 0;
    unk3c[9] = 0;
    unk3c[10] = 0;
}

Unk02095bf4::~Unk02095bf4() {}

int Unk02095c74::func_02095c74(int id) {
    if (id < 0) {
        return 0x10;
    }
    switch (id) {
    case 100000:
    case 100001:
    case 100002:
    case 100003:
    case 100004:
    case 100005:
    case 100006:
    case 100007:
    case 100008:
    case 100009:
    case 100010:
        return 2000;
    }
    return 1;
}

Unk0209487c *Unk02095c74::func_02095cd0(void *data, int kind) {
    if (kind == 2000) {
        return new Unk02095bf4(data);
    }
    return 0;
}
