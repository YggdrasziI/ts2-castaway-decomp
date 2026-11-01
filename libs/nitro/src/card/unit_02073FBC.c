/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on


#define func_0200e068 func_02073ff8

extern int data_020c4784;
extern void OS_Terminate(void);
int func_02073ff8(void);
void CARD_CheckEnabled(void);
void func_02073fbc(int seed);

int func_02073ff8(void) {
    return data_020c4784;
}

void CARD_CheckEnabled(void) {
    if (func_02073ff8() == 0) {
        OS_Terminate();
    }
}

void func_02073fbc(int seed) {
    data_020c4784 = seed;
}
