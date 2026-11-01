/* NitroSystem: position of a stream in milliseconds; written from the ROM. File bounds are a hypothesis. */
#pragma force_active on

typedef unsigned long long u64;

typedef struct {
    unsigned char pad[0xc4];
    unsigned short rate;
    unsigned char pad2[0x96];
    unsigned int samples;
} Stream;

unsigned int func_0209e520(Stream **handle) {
    Stream *s = *handle;
    if (s == 0) {
        return 0;
    }
    return (u64)s->samples * (u64)1000 / (u64)s->rate;
}
