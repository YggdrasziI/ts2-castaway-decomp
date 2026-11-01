/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern void MI_DmaCopy16(int ch, const void *src, void *dst, unsigned int len);
extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int len);
extern int data_020bcb74[];
void GX_LoadBGPltt(const void *src, unsigned int offset, unsigned int len);
void GXS_LoadBGPltt(const void *src, unsigned int offset, unsigned int len);
void GX_LoadOBJPltt(const void *src, unsigned int offset, unsigned int len);
void GXS_LoadOBJPltt(const void *src, unsigned int offset, unsigned int len);

void GX_LoadBGPltt(const void *src, unsigned int offset, unsigned int len) {
    if (data_020bcb74[0] != -1 && len > 0x1c) {
        MI_DmaCopy16(data_020bcb74[0], src, (void *)(offset + 0x5000000), len);
        return;
    }
    MIi_CpuCopy16(src, (void *)(offset + 0x5000000), len);
}

void GXS_LoadBGPltt(const void *src, unsigned int offset, unsigned int len) {
    if (data_020bcb74[0] != -1 && len > 0x1c) {
        MI_DmaCopy16(data_020bcb74[0], src, (void *)(offset + 0x400 + 0x5000000), len);
        return;
    }
    MIi_CpuCopy16(src, (void *)(offset + 0x400 + 0x5000000), len);
}

void GX_LoadOBJPltt(const void *src, unsigned int offset, unsigned int len) {
    if (data_020bcb74[0] != -1 && len > 0x1c) {
        MI_DmaCopy16(data_020bcb74[0], src, (void *)(offset + 0x200 + 0x5000000), len);
        return;
    }
    MIi_CpuCopy16(src, (void *)(offset + 0x200 + 0x5000000), len);
}

void GXS_LoadOBJPltt(const void *src, unsigned int offset, unsigned int len) {
    if (data_020bcb74[0] != -1 && len > 0x1c) {
        MI_DmaCopy16(data_020bcb74[0], src, (void *)(offset + 0x600 + 0x5000000), len);
        return;
    }
    MIi_CpuCopy16(src, (void *)(offset + 0x600 + 0x5000000), len);
}
