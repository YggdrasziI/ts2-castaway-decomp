/*
 * Sorted set of unit_0206B630.cpp (Unk0206b630): up to 0x500 ints kept in
 * ascending order, searched by bisection, saved as one raw block. The game
 * settings (data_020d60c8) point to one. All names are placeholders.
 */
#ifndef GAME_UNK_SORTEDSET_H
#define GAME_UNK_SORTEDSET_H

struct Unk020a4c4c;

class Unk0206b630 {
public:
    Unk0206b630() {
        count = 0;
        for (int i = 0; i < 0x500; i++) {
            values[i] = 0;
        }
    }

    bool func_0206b630(int value);
    bool func_0206b6bc(int value);
    int func_0206b6e8(int value);
    void func_0206b73c(Unk020a4c4c *save);
    void func_0206b75c(Unk020a4c4c *save);

    int values[0x500];
    int count;
};

#endif
