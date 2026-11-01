/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on



extern void *func_0209ee80(void *hh, void *end, int opt);
extern void *func_0209ea7c();
void *func_0209ed0c(unsigned int start, unsigned int size, int opt);
void *func_0209ed00();

void *func_0209ed0c(unsigned int start, unsigned int size, int opt)
{
    unsigned int end = size + start;
    unsigned int aligned_start = start + 3;
    end &= ~3u;
    aligned_start &= ~3u;
    if (aligned_start > end) goto fail;
    if ((end - aligned_start) >= 0x30) goto ok;
fail:
    return (void *)0;
ok:
    return func_0209ee80((void *)aligned_start, (void *)end, opt);
}

void *func_0209ed00() {
    return func_0209ea7c();
}
