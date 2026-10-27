/*
 * Object resource manager of unit_02060274.cpp (Unk020c409c, the static
 * object data_020c409c): the files of "object_resources.nitro_archive"
 * grouped by object definition, loaded and released per group. Layout from
 * the code; all names are placeholders.
 */
#ifndef GAME_UNK_OBJRES_H
#define GAME_UNK_OBJRES_H

#include "game/unk_archive.h"

/* The files of one object definition (10 bytes). */
struct Unk020605fc {
    Unk020605fc() : first(0), count(0), id(-1), refs(0), flags(0) {}

    s16 first;
    s16 count;
    s16 id;
    s16 refs;
    /*
     * Hypothesis: volatile. The original tests the flags and reads them again
     * for the update (func_020606e0, func_020608d8); volatile reproduces that.
     */
    volatile s16 flags;
};

/* One file of a group: its index in the archive and its texture id. */
struct Unk020605ec {
    Unk020605ec() : index(-1), tex(-1) {}

    s16 index;
    s16 tex;
};

class Unk020c409c {
public:
    Unk020c409c();
    ~Unk020c409c();

    int texFirst;
    int texCount;
    /*
     * Hypothesis: volatile, as Unk02093648::count. The search loop of
     * func_020606a0 reads it again at each test (89 % -> 100 %).
     */
    volatile int groupCount;
    Unk020605fc *groups;
    Unk020605ec *entries;
    int unk14;
    Unk02093648 *resources;
    Unk02093648 *locked;
    bool keep;
};

extern Unk020c409c data_020c409c;

#endif
