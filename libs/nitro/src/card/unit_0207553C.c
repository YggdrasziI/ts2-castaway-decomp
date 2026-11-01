/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* NitroSDK CARD: on the pulled-out notification (0x11) runs the user hook once and terminates
 * unless it declines; any other command panics. */

extern void OS_Terminate(void);
extern void func_020754b4(void);
extern int data_020c5060;
extern int (*data_020c5064)(void);

void func_0207553c(int arg0, int arg1) {
    if ((arg1 & 0x3f) == 0x11) {
        if (data_020c5060 != 0) return;
        data_020c5060 = 1;
        {
            int (*fn)(void) = data_020c5064;
            int r = 1;
            if (fn != 0) r = fn();
            if (r != 0) func_020754b4();
        }
    } else {
        OS_Terminate();
    }
}
