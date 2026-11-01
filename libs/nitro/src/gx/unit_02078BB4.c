/* NitroSDK; khdays (CC0) per-function sources, merged in reverse address order. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/os.h"
#define offsetof(type, member) ((u32)&(((type *)0)->member))

asm void GXi_NopClearFifo128_ (register void *pDest);

asm void GXi_NopClearFifo128_ (register void *pDest)
{
	mov r1, #0
	mov r2, #0
	mov r3, #0
	mov r12, #0
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	stmia r0, {r1 - r3, r12}
	bx lr
}
