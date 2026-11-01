/* NitroSystem; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef unsigned long long u64;
extern u32 func_0207dfc8(void);
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern int func_0207d850(u32 tag);
extern void func_0209a9c4(void *p);
extern void NNSi_SndFaderUpdate(void *f);
extern int NNSi_SndFaderGet(void *f);
extern int NNSi_SndFaderIsFinished(void *f);
extern void SND_SetPlayerVolume(int no, int vol);
extern void func_0209aad0(void *p);
extern void SND_StartPreparedSeq(int no);
extern char data_020d47fc[];
extern const short data_020b335c[];
typedef struct { char a[0x20]; unsigned char volume; } Player;
typedef struct { void *l; Player *player; char a[0x14]; char fader[0x10]; unsigned char status, startFlag, c, prepareFlag; u32 tag; char d[8]; unsigned char no; char e; short volume; unsigned char initVolume, extVolume; } Seq;
static inline short Db(int s) { return data_020b335c[s]; }
void func_0209adf4(void)
{
    Seq *s;
    Seq *next;
    u32 status;
    int fader;
    status = func_0207dfc8();
    for (s = NNS_FndGetNextListObject(data_020d47fc, 0); s != 0; s = next) {
        next = NNS_FndGetNextListObject(data_020d47fc, s);
        if (!s->startFlag) {
            if (func_0207d850(s->tag)) {
                s->startFlag = 1;
            }
        }
        if (s->startFlag) {
            if ((status & (1 << s->no)) == 0) {
                func_0209a9c4(s);
                continue;
            }
        }
        NNSi_SndFaderUpdate(s->fader);
        fader = Db(s->initVolume) + Db(s->extVolume) + Db(s->player->volume) + Db(NNSi_SndFaderGet(s->fader) >> 8);
        if (fader < -723) fader = -723;
        else if (fader > 0) fader = 0;
        if (fader != s->volume) {
            SND_SetPlayerVolume(s->no, fader);
            s->volume = (short)fader;
        }
        if (s->status == 2) {
            if (NNSi_SndFaderIsFinished(s->fader)) {
                func_0209aad0(s);
            }
        }
        if (s->prepareFlag) {
            SND_StartPreparedSeq(s->no);
            s->prepareFlag = 0;
        }
    }
}
