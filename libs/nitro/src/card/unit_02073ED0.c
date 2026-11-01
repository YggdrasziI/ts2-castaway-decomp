/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern int *data_020c4800;
extern void func_020741ac(int id, int resource);
extern void func_0207a2d4(int id);
extern void func_0207a2b8(int id);
extern void func_02074108(int id, int resource);
int func_02073f44(void);
int func_02073f30(void);
void func_02073f10(int id);
void func_02073ef0(int id);
void func_02073ee0(int id);
void func_02073ed0(int id);

int func_02073f44(void) {
    return (*(int *)((int)&data_020c4800 + 0x114) & 4) == 0;
}

int func_02073f30(void) {
    return *data_020c4800;
}

void func_02073f10(int id) {
    func_020741ac(id, 1);
    func_0207a2d4(id);
}

void func_02073ef0(int id) {
    func_0207a2b8(id);
    func_02074108(id, 1);
}

void func_02073ee0(int id) {
    func_020741ac(id, 2);
}

void func_02073ed0(int id) {
    func_02074108(id, 2);
}
