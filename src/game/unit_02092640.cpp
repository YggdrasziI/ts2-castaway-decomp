/*
 * Unit 0x02092640-0x02092704: an iterator (Unk02092640) over the 40-byte entries
 * of one of two entry managers (func_02091820 / func_02091830 return them). It keeps
 * the first and the current entry and two halfwords; the second one selects the
 * manager. An entry counts while func_0208fd2c accepts it.
 *
 * Bounds: hypothesis. Before 0x02092640 lies the manager code (0x02092554 sets up
 * its 128 entries); 0x02092704 starts unit_02092704.cpp. Real file name unknown.
 */

typedef unsigned short u16;

extern "C" {
void *func_02091820(void);
void *func_02091830(void);
void *func_0209250c(void *manager, void *entry);
int func_0208fd2c(void *entry);
}

class Unk02092640 {
public:
    Unk02092640();
    Unk02092640(void *entry, int unk8, int unkA);
    void func_0209266c();
    void *func_02092678();
    bool func_020926d4();
    u16 func_020926fc();

    void *first;
    void *cur;
    u16 unk8;
    u16 unkA;
};

Unk02092640::Unk02092640() {
    first = 0;
    cur = 0;
    unk8 = 0;
    unkA = 0;
}

Unk02092640::Unk02092640(void *entry, int unk8, int unkA) {
    first = entry;
    cur = entry;
    this->unk8 = unk8;
    this->unkA = unkA;
}

void Unk02092640::func_0209266c() {
    cur = first;
}

void *Unk02092640::func_02092678() {
    void *e = cur;

    if (e == 0) {
        return 0;
    }
    if (unkA != 0) {
        cur = func_0209250c(func_02091820(), e);
    } else {
        cur = func_0209250c(func_02091830(), e);
    }
    if (func_0208fd2c(e)) {
        return e;
    }
    return 0;
}

bool Unk02092640::func_020926d4() {
    bool r = false;

    if (cur != 0) {
        if (func_0208fd2c(cur)) {
            r = true;
        }
    }
    return r;
}

u16 Unk02092640::func_020926fc() {
    return unk8;
}
