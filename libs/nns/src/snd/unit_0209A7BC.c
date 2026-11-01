/* NitroSystem SND: library initialisation; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef struct {
    void (*func)(void *arg);
    void *arg;
} Callback;

extern int data_020d47c8;
extern Callback data_020d47cc;
extern Callback data_020d47d8;
extern signed char data_020d47c0;
extern int data_020d47c4;

extern void func_0209a74c(void *arg);
extern void func_0209a740(void *arg);
extern void SND_Init(void);
extern void func_0207f464(Callback *c);
extern void func_0207f44c(Callback *c);
extern void func_0209a864(void);
extern void NNSi_SndCaptureInit(void);
extern void NNSi_SndPlayerInit(void);

void func_0209a7bc(void) {
    if (data_020d47c8) {
        return;
    }
    data_020d47c8 = 1;
    SND_Init();
    data_020d47cc.func = func_0209a74c;
    data_020d47cc.arg = 0;
    data_020d47d8.func = func_0209a740;
    data_020d47d8.arg = 0;
    func_0207f464(&data_020d47cc);
    func_0207f44c(&data_020d47d8);
    func_0209a864();
    NNSi_SndCaptureInit();
    NNSi_SndPlayerInit();
    data_020d47c0 = -1;
    data_020d47c4 = 1;
}
