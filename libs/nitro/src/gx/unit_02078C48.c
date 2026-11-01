/* NitroSDK; built from khdays (CC0) per-function sources. File bounds are a hypothesis. */
#pragma force_active on

#include "sdk/types.h"
#include "sdk/mi.h"
#include "sdk/os.h"
#define reg_G3X_DISP3DCNT       (*(REGType16v *)REG_DISP3DCNT_ADDR)
#define reg_G2_BG0CNT           (*(REGType16v *)REG_BG0CNT_ADDR)
#define reg_G2_BG0OFS           (*(REGType32v *)REG_BG0OFS_ADDR)
#define reg_G3X_CLEAR_COLOR     (*(REGType32v *)REG_CLEAR_COLOR_ADDR)
#define reg_G3X_CLEAR_DEPTH     (*(REGType16v *)REG_CLEAR_DEPTH_ADDR)
#define reg_G3X_CLRIMAGE_OFFSET (*(REGType16v *)REG_CLRIMAGE_OFFSET_ADDR)
#define reg_G3X_FOG_COLOR       (*(REGType32v *)REG_FOG_COLOR_ADDR)
#define reg_G3X_FOG_OFFSET      (*(REGType16v *)REG_FOG_OFFSET_ADDR)
#define reg_G3_POLYGON_ATTR     (*(REGType32v *)REG_POLYGON_ATTR_ADDR)
#define reg_G3_TEXIMAGE_PARAM   (*(REGType32v *)REG_TEXIMAGE_PARAM_ADDR)
#define reg_G3_SHININESS        (*(REGType32v *)REG_SHININESS_ADDR)
#define reg_G3_END_VTXS         (*(REGType32v *)REG_END_VTXS_ADDR)
#define reg_G3X_GXSTAT          (*(REGType32v *)REG_GXSTAT_ADDR)
#define reg_G3X_ALPHA_TEST_REF  (*(REGType16v *)REG_ALPHA_TEST_REF_ADDR)
#define GX_DMA_NOT_USE          ((u32) ~0)
#define G3OP_MTX_MODE           0x10
#define G3OP_TEXPLTT_BASE       0x2b
typedef enum { GX_SHADING_TOON = 0, GX_SHADING_HIGHLIGHT = 1 } GXShading;
typedef enum { GX_FIFOINTR_COND_DISABLE = 0, GX_FIFOINTR_COND_UNDERHALF = 1, GX_FIFOINTR_COND_EMPTY = 2 } GXFifoIntrCond;
typedef enum { GX_POLYGONMODE_MODULATE = 0 } GXPolygonMode;
typedef enum { GX_CULL_ALL = 0, GX_CULL_FRONT = 0x40, GX_CULL_BACK = 0x80, GX_CULL_NONE = 0xc0 } GXCull;
typedef enum { GX_TEXFMT_NONE = 0 } GXTexFmt;
typedef enum { GX_TEXGEN_NONE = 0 } GXTexGen;
typedef enum { GX_TEXSIZE_S8 = 0 } GXTexSizeS;
typedef enum { GX_TEXSIZE_T8 = 0 } GXTexSizeT;
typedef enum { GX_TEXREPEAT_NONE = 0 } GXTexRepeat;
typedef enum { GX_TEXFLIP_NONE = 0 } GXTexFlip;
typedef enum { GX_TEXPLTTCOLOR0_USE = 0 } GXTexPlttColor0;
#define GX_LIGHTMASK_NONE 0
#define GX_POLYGON_ATTR_MISC_NONE 0
extern u32 data_020bcb74;
#define GXi_DmaId data_020bcb74
extern void G3X_ClearFifo(void);
extern void G3X_InitMtxStack(void);
extern void G3X_InitTable(void);
extern void G3X_ResetMtxStack_2(void);
extern void func_02079860(u32 dmaNo, void *dest, u32 data, u32 size, MIDmaCallback callback, void *arg);
extern void func_02079a2c(u32 dmaNo, void *dest, u32 data, u32 size);
extern void INITi_CpuClear32_0x01ff86fc(u32 data, void *destp, u32 size);
static inline BOOL G3X_IsGeometryBusy(void)
{
    return (BOOL)(reg_G3X_GXSTAT & REG_G3X_GXSTAT_GE_MASK);
}
static inline void G3_End(void)
{
    reg_G3_END_VTXS = 0;
}
static inline void G3X_ResetListRamOverflow(void)
{
    reg_G3X_DISP3DCNT |= REG_G3X_DISP3DCNT_GO_MASK;
}
static inline void G3X_ResetLineBufferUnderflow(void)
{
    reg_G3X_DISP3DCNT |= REG_G3X_DISP3DCNT_RO_MASK;
}
static inline void G3X_SetShading(GXShading shading)
{
    reg_G3X_DISP3DCNT = (u16)((reg_G3X_DISP3DCNT & ~(REG_G3X_DISP3DCNT_THS_MASK |
                                                     REG_G3X_DISP3DCNT_RO_MASK |
                                                     REG_G3X_DISP3DCNT_GO_MASK)) |
                              (shading << REG_G3X_DISP3DCNT_THS_SHIFT));
}
static inline void G3X_AntiAlias(BOOL enable)
{
    if (enable) {
        reg_G3X_DISP3DCNT = (u16)(reg_G3X_DISP3DCNT &
                                  ~(REG_G3X_DISP3DCNT_RO_MASK | REG_G3X_DISP3DCNT_GO_MASK) |
                                  REG_G3X_DISP3DCNT_AAE_MASK);
    } else {
        reg_G3X_DISP3DCNT = (u16)(reg_G3X_DISP3DCNT &
                                  ~(REG_G3X_DISP3DCNT_RO_MASK | REG_G3X_DISP3DCNT_GO_MASK |
                                    REG_G3X_DISP3DCNT_AAE_MASK));
    }
}
static inline void G3X_AlphaTest(BOOL enable, int ref)
{
    if (enable) {
        reg_G3X_DISP3DCNT = (u16)(reg_G3X_DISP3DCNT &
                                  ~(REG_G3X_DISP3DCNT_RO_MASK | REG_G3X_DISP3DCNT_GO_MASK) |
                                  REG_G3X_DISP3DCNT_ATE_MASK);
        reg_G3X_ALPHA_TEST_REF = (u16)ref;
    } else {
        /* the 16-bit mask (a second pool word) is this SDK's spelling; a 32-bit ~mask would be
         * derived from SetShading's by `sub #2` */
        reg_G3X_DISP3DCNT = (u16)(reg_G3X_DISP3DCNT &
                                  (u16)~(REG_G3X_DISP3DCNT_RO_MASK | REG_G3X_DISP3DCNT_GO_MASK |
                                         REG_G3X_DISP3DCNT_ATE_MASK));
    }
}
static inline void G3X_ResetMtxStackOverflow(void)
{
    reg_G3X_GXSTAT |= REG_G3X_GXSTAT_SE_MASK;
}
static inline void G3X_SetFifoIntrCond(GXFifoIntrCond cond)
{
    reg_G3X_GXSTAT = ((reg_G3X_GXSTAT & ~REG_G3X_GXSTAT_FI_MASK) |
                      (cond << REG_G3X_GXSTAT_FI_SHIFT));
}
static inline void G2_SetBG0Priority(int priority)
{
    reg_G2_BG0CNT = (u16)((reg_G2_BG0CNT & ~REG_G2_BG0CNT_PRIORITY_MASK) | priority);
}
static inline void G3_Direct1(int op, u32 param0)
{
    *(REGType32v *)(REG_MTX_MODE_ADDR + ((op - G3OP_MTX_MODE) * 4)) = param0;
}
static inline void G3_PolygonAttr(int light, GXPolygonMode polyMode, GXCull cullMode, int polygonID, int alpha, int misc)
{
    reg_G3_POLYGON_ATTR = (u32)(light | (polyMode << REG_G3_POLYGON_ATTR_PM_SHIFT) | cullMode |
                                (polygonID << REG_G3_POLYGON_ATTR_ID_SHIFT) |
                                (alpha << REG_G3_POLYGON_ATTR_ALPHA_SHIFT) | misc);
}
static inline void G3_TexImageParam(GXTexFmt texFmt, GXTexGen texGen, GXTexSizeS s, GXTexSizeT t,
                                    GXTexRepeat repeat, GXTexFlip flip, GXTexPlttColor0 pltt0, u32 addr)
{
    reg_G3_TEXIMAGE_PARAM = (u32)(texFmt | texGen | s | t | repeat | flip | pltt0 | (addr >> 3));
}
#define G2_BLENDTYPE_FADEIN  0x0080
#define G2_BLENDTYPE_FADEOUT 0x00c0
extern void GXi_NopClearFifo128_(volatile unsigned int *fifo);
#define reg_G3_MTX_MODE       (*(REGType32v *)0x4000440)
#define reg_G3_MTX_POP        (*(REGType32v *)0x4000448)
#define reg_G3_MTX_IDENTITY   (*(REGType32v *)0x4000454)
extern int G3X_GetMtxStackLevelPV(int *level);
extern int G3X_GetMtxStackLevelPJ(int *level);

void G3X_Init (void)
{

	G3X_ClearFifo();
	G3_End();

	while ( G3X_IsGeometryBusy()) {
	}

	reg_G3X_DISP3DCNT = 0;
	reg_G3X_GXSTAT = 0;
	reg_G2_BG0OFS = 0;

	G3X_ResetListRamOverflow();
	G3X_ResetLineBufferUnderflow();
	G3X_SetShading(GX_SHADING_TOON);
	G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);

	G3X_ResetMtxStackOverflow();
	G3X_SetFifoIntrCond(GX_FIFOINTR_COND_EMPTY);
	G3X_InitMtxStack();

	reg_G3X_CLEAR_COLOR = 0;
	reg_G3X_CLEAR_DEPTH = 0x7fff;
	reg_G3X_CLRIMAGE_OFFSET = 0;
	reg_G3X_FOG_COLOR = 0;
	reg_G3X_FOG_OFFSET = 0;

	G2_SetBG0Priority(0);
	G3X_InitTable();
	G3_PolygonAttr(GX_LIGHTMASK_NONE, GX_POLYGONMODE_MODULATE, GX_CULL_BACK, 0, 31, GX_POLYGON_ATTR_MISC_NONE);

	G3_TexImageParam(GX_TEXFMT_NONE,
	                 GX_TEXGEN_NONE,
	                 GX_TEXSIZE_S8, GX_TEXSIZE_T8, GX_TEXREPEAT_NONE, GX_TEXFLIP_NONE, GX_TEXPLTTCOLOR0_USE, 0);

	G3_Direct1(G3OP_TEXPLTT_BASE, 0);
}

void G3X_ClearFifo(void) {
    GXi_NopClearFifo128_((volatile unsigned int *)0x4000400);
    while (*(volatile unsigned int *)0x4000600 & 0x8000000) {
        ;
    }
}

void G3X_InitMtxStack(void) {
    volatile unsigned int *gxstat = (volatile unsigned int *)0x4000600;
    int levelPV;
    int levelPJ;

    *gxstat = *gxstat | 0x8000;

    while (G3X_GetMtxStackLevelPV(&levelPV) != 0) {}
    while (G3X_GetMtxStackLevelPJ(&levelPJ) != 0) {}

    reg_G3_MTX_MODE = 3;
    reg_G3_MTX_IDENTITY = 0;
    reg_G3_MTX_MODE = 0;

    if (levelPJ != 0) {
        reg_G3_MTX_POP = levelPJ;
    }

    reg_G3_MTX_IDENTITY = 0;
    reg_G3_MTX_MODE = 2;
    reg_G3_MTX_POP = levelPV;
    reg_G3_MTX_IDENTITY = 0;
}

void G3X_SetClearColor(unsigned color, unsigned alpha, unsigned depth,
                       unsigned polygonID, int fog) {
    unsigned v = color | (alpha << 16) | (polygonID << 24);
    if (fog != 0) {
        v |= 0x8000;
    }
    *(volatile unsigned *)0x04000350 = v;
    *(volatile unsigned short *)0x04000354 = (unsigned short)depth;
}

void G3X_InitTable (void)
{
	int i;

	if (GXi_DmaId != GX_DMA_NOT_USE) {
		func_02079860(GXi_DmaId, (void *)REG_EDGE_COLOR_0_L_ADDR, 0, 16, NULL, NULL);
		func_02079a2c(GXi_DmaId, (void *)REG_FOG_TABLE_0_ADDR, 0, 96);
	} else {
		MI_CpuFill32((void *)REG_EDGE_COLOR_0_L_ADDR, 0, 16);
		MI_CpuFill32((void *)REG_FOG_TABLE_0_ADDR, 0, 96);
	}

	for (i = 0; i < 32; ++i) {
		reg_G3_SHININESS = 0;
	}
}

int G3X_GetMtxStackLevelPV(int *level) {
    if ((*(volatile unsigned *)0x04000600 & 0x4000) != 0) {
        return -1;
    }
    *level = (*(volatile unsigned *)0x04000600 & 0x1f00) >> 8;
    return 0;
}

int G3X_GetMtxStackLevelPJ(int *level) {
    if ((*(volatile unsigned *)0x04000600 & 0x4000) != 0) {
        return -1;
    }
    *level = (*(volatile unsigned *)0x04000600 & 0x2000) >> 13;
    return 0;
}
