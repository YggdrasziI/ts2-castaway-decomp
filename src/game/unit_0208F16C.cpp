/*
 * Unit 0x0208F16C-0x0208F8B0: a font (Unk0208f16c) implementing the font interface
 * of the text layout (Unk02092830Font, include/game/unk_text.h). It keeps the
 * glyph file (Unk02095140) and reads its metrics from a data tree file
 * (Unk02096348): the characters of "FontMetrics.Characters.String", sorted by code,
 * then per "Character" node its "Char", break flags ("AlwaysBreak", "CanBreak",
 * "Whitespace") and "Kerning", and the "Dimensions" node ("Width", "Height",
 * "Baseline"). Characters are found by binary search.
 *
 * Bounds: hypothesis. Before 0x0208F16C lie the other font class (vtable
 * 0x020BD0F4, code from 0x0208E570) and the interface destructor 0x0208F168 it
 * emits; 0x0208F8B0 starts unit_0208F8B0.cpp. The strings, the vtable and this
 * file's copy of the interface vtable (0x020BD240, references go to the first copy,
 * 0x020BD130) are only used here. Real file name unknown.
 * Not complete although every function matches: this file also emits the
 * interface destructors (multiply-definable), whose kept copies are
 * _ZN15Unk02092830FontD1Ev (0x0208F168, other font's file) and
 * _ZN15Unk02092830FontD0Ev (0x0201B92C). While those are assembly, the link clashes
 * (same name) or keeps this file's copies in .text (other name). A trial link with
 * the clash avoided placed the strings and both vtables as in the ROM
 * (notes/MATCHING.md, unsolved patterns). objdiff scores .data low because each
 * string literal is its own section.
 */

#include "game/unk_datatree.h"
#include "game/unk_resource.h"
#include "game/unk_font.h"
#include "game/unk_text.h"

extern "C" {
u32 func_0209a418(const u8 *str, u32 ch);
u32 func_0209a550(const u8 *str);
int func_0209a5d8(const u8 *str, int *length);
}

Unk0208f16c::Unk0208f16c() {
    entries = 0;
    count = 0;
    file = 0;
    width = 0;
    height = 0;
    baseline = 0;
}

Unk0208f16c::~Unk0208f16c() {
    func_38();
}

void Unk0208f16c::func_08(Unk02095140 *file, Unk02096348 *script) {
    Unk02095140Header *header;

    if (file == 0) {
        return;
    }
    if (this->file != 0) {
        func_38();
    }
    if (!file->func_02094f88() || script == 0) {
        return;
    }
    if (!script->func_02094f88()) {
        return;
    }
    header = file->func_02095180();
    this->file = file;
    file->func_02094f9c();
    count = header->count;
    width = header->width << 3;
    height = header->height << 3;
    entries = new Unk0208f16cEntry[count];
    func_0208f2c8(script);
    func_0208f3a4(script);
}

void Unk0208f16c::func_0208f2c8(Unk02096348 *script) {
    int key;
    const u8 *s;
    int n;
    int i;
    int c;
    int prev;
    int len;

    key = script->func_0209645c((const u32 *)"FontMetrics.Characters.String", -1);
    if (!script->func_02096538(key, 0)) {
        return;
    }
    s = script->func_02096564(key);
    n = func_0209a418(s, 0);
    if (n < count) {
        count = n;
    }
    len = 0;
    prev = -1;
    for (i = 0; (c = func_0209a5d8(s, &len)) != 0 && i < n; i++) {
        if (c <= prev) {
            return;
        }
        prev = c;
        entries[i].code = c;
        entries[i].flags = 0;
        s += len;
    }
}

void Unk0208f16c::func_0208f3a4(Unk02096348 *script) {
    Unk0209674c root = script->func_02096980();
    int i;

    for (i = 0; i < root.func_020967ec(); i++) {
        Unk0209674c child = root.func_02096774(i);
        if (child.func_0209683c((const u32 *)"Character")) {
            func_0208f464(script, child);
        } else if (child.func_0209683c((const u32 *)"Dimensions")) {
            func_0208f5ec(script, child);
        }
    }
}

void Unk0208f16c::func_0208f464(Unk02096348 *script, const Unk0209674c &node) {
    Unk0208f16cEntry *entry = 0;
    int flags = 0;
    int kerning = 0;
    int i;

    for (i = 0; i < node.func_020967ec(); i++) {
        Unk0209674c child = node.func_02096774(i);
        int index = child.func_0209688c();
        if (child.func_0209683c((const u32 *)"Char")) {
            const u8 *s = script->func_02096564(index);
            if (s != 0) {
                entry = &entries[func_1c(func_0209a550(s))];
            }
        } else if (child.func_0209683c((const u32 *)"AlwaysBreak")) {
            if (script->func_020965c8(index)) {
                flags |= 4;
            }
        } else if (child.func_0209683c((const u32 *)"CanBreak")) {
            if (script->func_020965c8(index)) {
                flags |= 2;
            }
        } else if (child.func_0209683c((const u32 *)"Whitespace")) {
            if (script->func_020965c8(index)) {
                flags |= 1;
            }
        } else if (child.func_0209683c((const u32 *)"Kerning")) {
            kerning = script->func_02096574(index);
        }
    }
    if (entry != 0) {
        entry->flags = flags;
        entry->kerning = kerning;
    }
}

void Unk0208f16c::func_0208f5ec(Unk02096348 *script, const Unk0209674c &node) {
    int i;

    for (i = 0; i < node.func_020967ec(); i++) {
        Unk0209674c child = node.func_02096774(i);
        int index = child.func_0209688c();
        if (child.func_0209683c((const u32 *)"Width")) {
            width = script->func_02096574(index);
        } else if (child.func_0209683c((const u32 *)"Height")) {
            height = script->func_02096574(index);
        } else if (child.func_0209683c((const u32 *)"Baseline")) {
            baseline = script->func_02096574(index);
        }
    }
}

void Unk0208f16c::func_38() {
    if (entries != 0) {
        delete[] entries;
    }
    entries = 0;
    if (file != 0) {
        file->func_02094fb8();
    }
    file = 0;
}

int Unk0208f16c::func_1c(u32 c) {
    int lo;
    int hi;
    int mid;

    if (entries == 0) {
        return 0;
    }
    lo = 0;
    hi = count - 1;
    while (lo <= hi) {
        mid = (lo + hi) >> 1;
        if (c == entries[mid].code) {
            return mid;
        }
        if (c < entries[mid].code) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return 0;
}

int Unk0208f16c::func_18(u32 c) {
    return width - entries[func_1c(c)].kerning;
}

int Unk0208f16c::func_20(const char *str) {
    int total = 0;
    int len = 0;
    u32 c;

    while ((c = func_0209a5d8((const u8 *)str, &len)) != 0) {
        total += func_18(c);
        str += len;
    }
    return total;
}

bool Unk0208f16c::func_28(u32 c) {
    return (entries[func_1c(c)].flags & 2) != 0;
}

bool Unk0208f16c::func_2c(u32 c) {
    return (entries[func_1c(c)].flags & 4) != 0;
}

bool Unk0208f16c::func_30(u32 c) {
    return (entries[func_1c(c)].flags & 1) != 0;
}

int Unk0208f16c::func_0c(u32 c) {
    return 0;
}

int Unk0208f16c::func_10(u32 c) {
    return 0;
}

int Unk0208f16c::func_14(u32 c) {
    return baseline;
}

int Unk0208f16c::func_24() {
    return height;
}

Unk02095140 *Unk0208f16c::func_34() {
    return file;
}
