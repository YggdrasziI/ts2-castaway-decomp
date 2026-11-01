/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* Fires the one-shot callback parked at data_020c7758+0x20: clears the pending flag at
 * +0x1c, takes the callback and its stashed argument at +0x24, clears the callback slot
 * and calls it with (a, arg).  Does nothing when no callback is installed. */
extern int data_020c7758[];

void func_02080028(int a) {
    int flag = data_020c7758[0];
    void (*fn)(int, int) = (void (*)(int, int))data_020c7758[1];
    int arg = data_020c7758[2];
    if (flag != 0) {
        data_020c7758[0] = 0;
    }
    if (fn == 0) {
        return;
    }
    data_020c7758[1] = 0;
    fn(a, arg);
}
