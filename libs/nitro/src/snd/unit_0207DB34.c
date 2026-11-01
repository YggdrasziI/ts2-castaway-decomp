/* NitroSDK; khdays (CC0) per-function source, retyped for this ROM. File bounds are a hypothesis. */
#pragma force_active on
/* NitroSDK func_0207db34: append an already filled command slot to the sound
   driver's reserved list, under an interrupt lock so the ARM7 flush path cannot
   observe a half-linked list. SND_FlushCommand later hands reservedHead to the ARM7
   over PXI and clears both list pointers. Ghidra carries the semantic name;
   the build symbol stays func_0207db34. */

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

typedef struct SNDCommand {
    struct SNDCommand *next;
    unsigned int id;
    unsigned int arg[4];
} SNDCommand;

typedef struct SNDCommandMgr {
    SNDCommand *freeHead;
    unsigned int processedTag;
    SNDCommand *reservedHead;
    SNDCommand *reservedTail;
    SNDCommand *freeTail;
    unsigned int unk14;
    int sentRingIndex;
    int sentBlockCount;
    unsigned int nextTag;
} SNDCommandMgr;

extern SNDCommand *data_020c5bb8;
extern SNDCommand *data_020c5bb4;

void func_0207db34(SNDCommand *command) {
    SNDCommand *tail;
    int state;

    state = OS_DisableInterrupts();
    tail = data_020c5bb8;
    /* The tail store is written into both arms on purpose: hoisting it below the
       if/else creates a merge point at which mwcc rematerialises the work-area
       address, costing one extra ldr. Duplicated, it emits the ROM's predicated
       streq/strne pair with the base kept live in r1. */
    if (tail == 0) {
        data_020c5bb8 = command;
        data_020c5bb4 = command;
    } else {
        tail->next = command;
        data_020c5bb8 = command;
    }
    command->next = 0;
    OS_RestoreInterrupts(state);
}
