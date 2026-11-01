/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
struct Thread02001ff0 {
    char _0[0x64];
    int field_64;
    struct Thread02001ff0 *next;
};

struct Globals02001ff0 {
    char _0[0x8];
    struct Thread02001ff0 *list;
};

extern struct Globals02001ff0 ThreadInfo;

void *func_0207a824(void)
{
    struct Thread02001ff0 *t = ThreadInfo.list;
    while (t != 0 && t->field_64 != 1)
        t = t->next;
    return t;
}
