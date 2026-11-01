/*
 * Unit 0x020A0014-0x020A03E0: the table of game texts (0x108 bytes): the text archive, the
 * text file of the language and a buffer for formatted numbers. The ids from 10000 to 10040
 * are not in the file: they print a number. Bounds: hypothesis (between the game settings
 * object, whose language it reads, and the input state; `.data` holds the archive path, the
 * fallback text, the separators and the number formats). Layouts come from the code; all
 * names are placeholders. Real file name unknown.
 */
#include "game/unk_archive.h"

typedef char *va_list;
#define va_start(ap, parm) \
    ((ap) = (va_list)((((int)&(parm)) & ~3) + 4))

class Unk02095df0 : public Unk0209487c {
public:
    int func_02095ef8(int id);
    const char *func_02095f58(int index);
};

class Unk020a0014 {
public:
    Unk020a0014(const u32 *name);
    ~Unk020a0014();

    Unk02093648 *archive;
    Unk02095df0 *file;
    char buffer[0x100];
};

struct Unk020d60c8;

extern "C" {
int func_0209f0a4(Unk020d60c8 *settings);
int func_0208299c(char *buf, int size, const char *fmt, va_list args);
const char *func_020a0134(Unk020a0014 *o, int n);
void func_020a0104(Unk020a0014 *o, const char *fmt, ...);
extern Unk020d60c8 data_020d60c8;
}

Unk020a0014::Unk020a0014(const u32 *name) {
    archive = 0;
    file = 0;
    archive = new Unk02093648("ROM_Euro/source/archives/text.nitro_archive");
    archive->func_02094df4();
    file = (Unk02095df0 *)archive->func_02093c18(name);
}

Unk020a0014::~Unk020a0014() {
    archive->func_02093c3c(file);
    delete archive;
}

extern "C" const char *func_020a00a0(Unk020a0014 *o, u32 id) {
    const u32 base = 10000;
    if (id >= base && id < base + 0x29) {
        return func_020a0134(o, id - base);
    }
    if (o->file != 0) {
        const char *text = o->file->func_02095f58(o->file->func_02095ef8(id));
        if (text != 0) {
            return text;
        }
    }
    return "undefined";
}

extern "C" void func_020a0104(Unk020a0014 *o, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    func_0208299c(o->buffer, 0x100, fmt, args);
}

/*
 * All functions at 100 %, not complete: the empty string lands first in `.data` (the original
 * has ".", the no-break space, "", ",": its pointers are swapped in the pool too). Moving the
 * separator switch to an inline fixes `.data` but swaps r7 / r8 here (99.24 %, declaration
 * and assignment forms tried).
 */
extern "C" const char *func_020a0134(Unk020a0014 *o, int n) {
    bool negative = n < 0;
    if (negative) {
        n = -n;
    }
    int millions = n / 1000000;
    n -= millions * 1000000;
    int thousands = n / 1000;
    int units = n - thousands * 1000;
    const char *sep;
    const char *sign = "";
    switch (func_0209f0a4(&data_020d60c8)) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        sep = ".";
        break;
    case 1:
        sep = " ";
        break;
    case 7:
        sep = sign;
        break;
    case 0:
    default:
        sep = ",";
        break;
    }
    if (negative) {
        switch (func_0209f0a4(&data_020d60c8)) {
        case 1:
            sign = "-\xc2\xa0";
            break;
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        default:
            sign = "-";
            break;
        }
    }
    switch (func_0209f0a4(&data_020d60c8)) {
    case 1:
    case 3:
    case 4:
    case 6:
        if (millions != 0) {
            func_020a0104(o, "%s%d%s%03d%s%03d", sign, millions, sep, thousands, sep, units);
        } else if (thousands != 0) {
            func_020a0104(o, "%s%d%s%03d", sign, thousands, sep, units);
        } else {
            func_020a0104(o, "%s%d", sign, units);
        }
        break;
    case 5:
        if (millions != 0) {
            func_020a0104(o, "%s%d%s%03d%s%03d", sign, millions, sep, thousands, sep, units);
        } else if (thousands != 0) {
            func_020a0104(o, "%s%d%s%03d", sign, thousands, sep, units);
        } else {
            func_020a0104(o, "%s0%d", sign, units);
        }
        break;
    case 0:
    case 2:
    case 7:
    default:
        if (millions != 0) {
            func_020a0104(o, "%s%d%s%03d%s%03d", sign, millions, sep, thousands, sep, units);
        } else if (thousands != 0) {
            func_020a0104(o, "%s%d%s%03d", sign, thousands, sep, units);
        } else {
            func_020a0104(o, "%s%d", sign, units);
        }
        break;
    }
    return o->buffer;
}
