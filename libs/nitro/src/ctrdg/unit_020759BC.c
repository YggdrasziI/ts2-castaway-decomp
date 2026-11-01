/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* NitroSDK CTRDG: clears the common work and takes a lock id. */

extern void func_020759fc(const void *src, void *dst, unsigned ctrl);
extern int OS_GetLockID(void);

extern struct { char _pad[2]; unsigned short lockid; } data_020c506c;

void func_020759bc(void) {
    int zero = 0;
    func_020759fc(&zero, &data_020c506c, 0x05000001);
    data_020c506c.lockid = (unsigned short)OS_GetLockID();
}
