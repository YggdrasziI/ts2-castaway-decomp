/*
 * Unit 0x020A4C0C-0x020A4E60: a byte stream over a fixed buffer, one write position (`size`) and
 * one read position. Bit 0 of `flags` is never set here, bit 2 records a failed access. Bounds:
 * hypothesis (the constructor starts it; the next function computes a CRC on a save header; no
 * data). Layouts come from the code; all names are placeholders. Real file name unknown.
 */
typedef unsigned char u8;
typedef unsigned long u32;

class Unk020a4c0c {
public:
    Unk020a4c0c(int capacity);

    u8 *buffer;
    int capacity;
    int size;
    int pos;
    u32 flags;
};

extern "C" {
u8 *func_020a4c60(Unk020a4c0c *p, int n, bool clear);
u8 *func_020a4ce0(Unk020a4c0c *p, int n);
}

Unk020a4c0c::Unk020a4c0c(int capacity) : buffer(0), capacity(0), size(0), pos(0), flags(0) {
    if (capacity > 0) {
        this->capacity = capacity;
        buffer = new u8[capacity];
    }
}

extern "C" void func_020a4c4c(Unk020a4c0c *p) {
    p->size = 0;
    p->pos = 0;
    p->flags = 0;
}

extern "C" u8 *func_020a4c60(Unk020a4c0c *p, int n, bool clear) {
    if (!(p->flags & 5) && n >= 0) {
        int start = p->size;
        if (start + n <= p->capacity) {
            p->size = start + n;
            if (clear) {
                for (int i = 0; i < n; i++) {
                    p->buffer[start + i] = 0;
                }
            }
            return p->buffer + start;
        }
    }
    p->flags |= 4;
    return 0;
}

extern "C" u8 *func_020a4ce0(Unk020a4c0c *p, int n) {
    if (!(p->flags & 5) && n >= 0) {
        int start = p->pos;
        if (start + n <= p->size) {
            p->pos = start + n;
            return p->buffer + start;
        }
    }
    p->flags |= 4;
    return 0;
}

extern "C" void func_020a4d2c(Unk020a4c0c *p, int shift) {
    if (shift < 0 || shift > 4) {
        p->flags |= 4;
        return;
    }
    int align = 1 << shift;
    int rest = p->pos & (align - 1);
    if (rest > 0) {
        func_020a4ce0(p, align - rest);
    }
}

extern "C" void func_020a4d78(Unk020a4c0c *p, int shift) {
    if (shift < 0 || shift > 4) {
        p->flags |= 4;
        return;
    }
    int align = 1 << shift;
    int rest = p->size & (align - 1);
    if (rest > 0) {
        func_020a4c60(p, align - rest, true);
    }
}

extern "C" int func_020a4dc4(Unk020a4c0c *p, const u8 *src, int n) {
    u8 *dst = func_020a4c60(p, n, false);
    if (dst == 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        dst[i] = *src++;
    }
    return n;
}

extern "C" int func_020a4e14(Unk020a4c0c *p, u8 *dst, int n) {
    const u8 *src = func_020a4ce0(p, n);
    if (src == 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        *dst++ = src[i];
    }
    return n;
}
