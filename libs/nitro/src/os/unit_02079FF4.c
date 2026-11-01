/* NitroSDK interrupt masks. Part of a file; rewritten from fingerprints of khdays (CC0). */

/* The link strips unused code; some of these have no caller in this ROM. */
#pragma force_active on
#define REG_IME (*(volatile unsigned short*)0x04000208)
#define REG_IE (*(volatile unsigned int*)0x04000210)
#define REG_IF (*(volatile unsigned int*)0x04000214)

static inline unsigned int DisableIme(void) {
    unsigned int old = REG_IME;
    REG_IME = 0;
    return old;
}

static inline void RestoreIme(unsigned int state) {
    (void)REG_IME;
    REG_IME = (unsigned short)state;
}

unsigned int OS_SetIrqMask(unsigned int mask) {
    unsigned int enabled = DisableIme();
    unsigned int last = REG_IE;
    REG_IE = mask;
    RestoreIme(enabled);
    return last;
}

unsigned int OS_EnableIrqMask(unsigned int mask) {
    unsigned int enabled = DisableIme();
    unsigned int last = REG_IE;
    REG_IE = last | mask;
    RestoreIme(enabled);
    return last;
}

unsigned int OS_DisableIrqMask(unsigned int mask) {
    unsigned int enabled = DisableIme();
    unsigned int last = REG_IE;
    REG_IE = last & ~mask;
    RestoreIme(enabled);
    return last;
}

unsigned int OS_ResetRequestIrqMask(unsigned int mask) {
    unsigned int enabled = DisableIme();
    unsigned int last = REG_IF;
    REG_IF = mask;
    RestoreIme(enabled);
    return last;
}
