/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* NitroSDK CTRDG: on the pulled-out notification (0x11) runs the user hook once and terminates when
 * it asks to. */

extern void OS_Terminate(void);
extern void CTRDG_TerminateForPulledOut(void);
extern int data_020c507c;
extern int (*data_020c5080)(void);

void func_02075a3c(int param_1, unsigned param_2) {
    if ((param_2 & 0x3f) == 0x11) {
        int result;
        int (*fn)(void);
        if (data_020c507c != 0) return;
        result = 0;
        fn = data_020c5080;
        if (fn != 0) result = fn();
        if (result != 0) CTRDG_TerminateForPulledOut();
        data_020c507c = 1;
    } else {
        OS_Terminate();
    }
}
