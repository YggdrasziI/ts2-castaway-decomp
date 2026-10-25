/*
 * Unit 0x0209A32C-0x0209A740: string helpers. Hashes of strings read a word at a
 * time (h = rotl(h, 5) * 31 + c), word-wise string equality, and UTF-8 decoding
 * (lead-byte test, one character, a whole string).
 *
 * Bounds: hypothesis. Before 0x0209A32C lies unit_0209A11C.cpp (a bit set); the end
 * is the end of the engine block, where NitroSystem code starts (notes/SPLITS.md).
 * The functions only call each other. func_0209a32c is called from many
 * static initializers (hashed string constants). Real file name unknown.
 */

typedef unsigned long u32;
typedef unsigned char u8;

u32 func_0209a418(const u8 *str, u32 ch);
u32 func_0209a5d8(const u8 *str, int *length);

u32 func_0209a32c(const u32 *str, u32 last, u32 end) {
    u32 word;
    u32 c;
    u32 hash;
    u32 i;
    u32 skip;

    if (str == 0) {
        return 0;
    }
    hash = 0;
    i = 0;
    skip = 0;
    if (last != 0) {
        u32 length = func_0209a418((const u8 *)str, end);
        if (last < length) {
            skip = length - last;
        }
    }
    for (;;) {
        word = *str;
        c = word & 0xff;
        if (c == 0) {
            break;
        }
        while (c != 0) {
            if (i >= skip) {
                if (c == end) {
                    return hash;
                }
                hash = ((hash << 5) + (hash >> 27)) * 31;
                hash += c;
            }
            word >>= 8;
            i++;
            c = word & 0xff;
        }
        if ((i & 3) != 0) {
            break;
        }
        str++;
    }
    return hash;
}

u32 func_0209a3c4(u32 hash, const u32 *str) {
    u32 word;
    u32 i;
    u32 c;

    if (str == 0) {
        return hash;
    }
    i = 0;
    for (;;) {
        word = *str;
        c = word & 0xff;
        if (c == 0) {
            return hash;
        }
        while (c != 0) {
            hash = ((hash << 5) + (hash >> 27)) * 31;
            hash += c;
            word >>= 8;
            i++;
            c = word & 0xff;
        }
        if ((i & 3) != 0) {
            break;
        }
        str++;
    }
    return hash;
}

u32 func_0209a418(const u8 *str, u32 ch) {
    u32 count;
    int length;
    u32 value;

    if (str == 0) {
        return 0;
    }
    count = 0;
    while (*str != 0) {
        value = func_0209a5d8(str, &length);
        if (value == ch) {
            return count;
        }
        count++;
        str += length;
    }
    return count;
}

int func_0209a474(const u32 *a, const u32 *b) {
    u32 diff;
    int more;
    u32 word;

    if (a == 0 || b == 0) {
        return 0;
    }
    diff = 0;
    more = 1;
    while (diff == 0 && more) {
        word = *a;
        diff = word ^ *b;
        if ((word & 0xff) == 0) {
            more = 0;
            diff <<= 24;
        } else if ((word & 0xff00) == 0) {
            more = 0;
            diff <<= 16;
        } else if ((word & 0xff0000) == 0) {
            more = 0;
            diff <<= 8;
        } else if ((word & 0xff000000) == 0) {
            more = 0;
        }
        a++;
        b++;
    }
    return diff == 0;
}

int func_0209a510(const u8 *str) {
    u8 c;

    while ((c = *str) != 0) {
        if ((c & 0xe0) == 0xc0 || (c & 0xf0) == 0xe0 || (c & 0xf8) == 0xf0) {
            return 1;
        }
        str++;
    }
    return 0;
}

u32 func_0209a550(const u8 *str) {
    u8 c;
    u32 value;
    int length;
    int mask;
    int shift;

    c = *str;
    value = 0;
    if ((c & 0x80) == 0) {
        return c & 0x7f;
    }
    if ((c & 0xe0) == 0xc0) {
        length = 2;
    } else if ((c & 0xf0) == 0xe0) {
        length = 3;
    } else {
        length = 4;
    }
    shift = (length - 1) * 6;
    mask = 0xff >> (length + 1);
    while (length-- != 0) {
        value += (*str++ & mask) << shift;
        mask = 0x3f;
        shift -= 6;
    }
    return value;
}

u32 func_0209a5d8(const u8 *str, int *length) {
    u8 c;
    u32 value;
    int n;
    int shift;
    int mask;

    c = *str;
    value = 0;
    if ((c & 0x80) == 0) {
        *length = 1;
        return c & 0x7f;
    }
    if ((c & 0xe0) == 0xc0) {
        n = 2;
    } else if ((c & 0xf0) == 0xe0) {
        n = 3;
    } else {
        n = 4;
    }
    shift = (n - 1) * 6;
    mask = 0xff >> (n + 1);
    *length = n;
    while (n-- != 0) {
        value += (*str++ & mask) << shift;
        mask = 0x3f;
        shift -= 6;
    }
    return value;
}

int func_0209a670(const u8 *str, u32 *out, int max) {
    u8 c;
    int n;
    int mask;
    u32 value;
    int count;
    int shift;

    c = *str;
    count = 0;
    while (c != 0) {
        if ((c & 0x80) == 0) {
            value = c;
            n = 1;
            str++;
        } else if ((c & 0xe0) == 0xc0) {
            n = 2;
        } else if ((c & 0xf0) == 0xe0) {
            n = 3;
        } else {
            n = 4;
        }
        if (n > 1) {
            shift = (n - 1) * 6;
            mask = 0xff >> (n + 1);
            value = 0;
            while (n-- != 0) {
                value += (*str++ & mask) << shift;
                mask = 0x3f;
                shift -= 6;
            }
        }
        count++;
        *out++ = value;
        if (count >= max) {
            break;
        }
        c = *str;
    }
    return count;
}
