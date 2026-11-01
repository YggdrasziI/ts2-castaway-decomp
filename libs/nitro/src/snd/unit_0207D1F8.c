/* NitroSDK sound command wrappers. Written from the ROM, compared with khdays (CC0). File bounds
 * are a hypothesis. Functions are emitted in reverse source order. */
#pragma force_active on

#include "sdk/types.h"

extern char *func_0207db7c(int wait);
extern void func_0207db34(char *cmd);
extern void func_0207dec4(int id);

void func_0207d1f8(u32 id, u32 arg0, u32 arg1, u32 arg2, u32 arg3);
void SNDi_SetTrackParam(int player, u32 trackMask, u32 param, u32 value, int size);
void SNDi_SetPlayerParam(int player, u32 param, u32 value, int size);

void SND_StopSeq(int player)
{
    func_0207d1f8(1, player, 0, 0, 0);
}

void SND_PrepareSeq(u32 a, u32 b, u32 c, u32 d)
{
    func_0207d1f8(2, a, b, c, d);
}

void SND_StartPreparedSeq(int player)
{
    func_0207d1f8(3, player, 0, 0, 0);
}

void func_0207d528(int player, u32 value)
{
    SNDi_SetPlayerParam(player, 0x1a, value, 2);
}

void SND_SetPlayerVolume(int player, u32 value)
{
    SNDi_SetPlayerParam(player, 6, value, 2);
}

void SND_SetPlayerChannelPriority(int player, u32 value)
{
    SNDi_SetPlayerParam(player, 4, value, 1);
}

void func_0207d4d0(int player, u32 trackMask, u32 value)
{
    SNDi_SetTrackParam(player, trackMask, 0xa, value, 2);
}

void func_0207d4a8(int player, u32 trackMask, u32 value)
{
    SNDi_SetTrackParam(player, trackMask, 0xc, value, 2);
}

void SND_SetTrackAllocatableChannel(u32 a, u32 b, u32 c)
{
    func_0207d1f8(9, a, b, c, 0);
}

void SND_StartTimer(u32 a, u32 b, u32 c, u32 d)
{
    func_0207d1f8(0xc, a, b, c, d);
}

void SND_StopTimer(u32 chMask, u32 capMask, u32 alarmMask, u32 reserved)
{
    int i;
    u32 mask = alarmMask;

    for (i = 0; i < 8 && mask != 0; i++, mask >>= 1) {
        if (mask & 1) {
            func_0207dec4(i);
        }
    }
    func_0207d1f8(0xd, chMask, capMask, alarmMask, reserved);
}

void SND_UnlockChannel(u32 a, u32 b)
{
    func_0207d1f8(0x1b, a, b, 0, 0);
}

void SND_SetChannelVolume(u32 a, u32 b, u32 c)
{
    func_0207d1f8(0x14, a, b, c, 0);
}

void SND_InvalidateSeqData(u32 start, u32 end)
{
    func_0207d1f8(0x1e, start, end, 0, 0);
}

void SND_InvalidateBankData(u32 start, u32 end)
{
    func_0207d1f8(0x1f, start, end, 0, 0);
}

void SND_InvalidateWaveData(u32 start, u32 end)
{
    func_0207d1f8(0x20, start, end, 0, 0);
}

void SND_SetOutputSelector(u32 a, u32 b, u32 c, u32 d)
{
    func_0207d1f8(0x19, a, b, c, d);
}

void SNDi_SetPlayerParam(int player, u32 param, u32 value, int size)
{
    func_0207d1f8(6, player, param, value, size);
}

void SNDi_SetTrackParam(int player, u32 trackMask, u32 param, u32 value, int size)
{
    func_0207d1f8(7, player | (size << 24), trackMask, param, value);
}

void func_0207d1f8(u32 id, u32 arg0, u32 arg1, u32 arg2, u32 arg3)
{
    char *cmd = func_0207db7c(1);

    if (cmd == NULL) {
        return;
    }
    *(u32 *)(cmd + 4) = id;
    *(u32 *)(cmd + 8) = arg0;
    *(u32 *)(cmd + 0xc) = arg1;
    *(u32 *)(cmd + 0x10) = arg2;
    *(u32 *)(cmd + 0x14) = arg3;
    func_0207db34(cmd);
}
