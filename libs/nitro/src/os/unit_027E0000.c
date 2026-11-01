/*
 * DTCM data-only unit 0x027E0000-0x027E0080: a table of 22 code addresses followed by two
 * zero words, then 32 bytes of .bss. The file it belongs to and the types are unknown.
 */
#pragma force_active on

extern void func_02079fbc(void);
extern void func_02079ed0(void);
extern void func_02079ec0(void);
extern void func_02079eb0(void);
extern void func_02079ea0(void);
extern void func_02079f10(void);
extern void func_02079f00(void);
extern void func_02079ef0(void);
extern void func_02079ee0(void);

void (*data_027e0000[24])(void) = {
    func_02079fbc,
    func_02079fbc,
    func_02079fbc,
    func_02079ed0,
    func_02079ec0,
    func_02079eb0,
    func_02079ea0,
    func_02079fbc,
    func_02079f10,
    func_02079f00,
    func_02079ef0,
    func_02079ee0,
    func_02079fbc,
    func_02079fbc,
    func_02079fbc,
    func_02079fbc,
    func_02079fbc,
    func_02079fbc,
    func_02079fbc,
    func_02079fbc,
    func_02079fbc,
    func_02079fbc,
    0,
    0,
};

unsigned char data_027e0060[32];
