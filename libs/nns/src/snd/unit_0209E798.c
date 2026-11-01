/* NitroSystem fader (khdays cites fader.c). Rewritten from fingerprints of khdays (CC0). */

/* The link strips unused code; some of these have no caller in this ROM. */
#pragma force_active on
typedef struct NNSSndFader {
    int origin;
    int target;
    int counter;
    int frame;
} NNSSndFader;

void NNSi_SndFaderInit(NNSSndFader* fader) {
    fader->origin = fader->target = 0;
    fader->counter = fader->frame = 0;
}

int NNSi_SndFaderGet(const NNSSndFader* fader);

void NNSi_SndFaderSet(NNSSndFader* fader, int target, int frame) {
    fader->origin = NNSi_SndFaderGet(fader);
    fader->target = target;
    fader->frame = frame;
    fader->counter = 0;
}

int NNSi_SndFaderGet(const NNSSndFader* fader) {
    long long value;

    if (fader->counter >= fader->frame) {
        return fader->target;
    }
    value = (fader->target - fader->origin) * fader->counter / fader->frame + fader->origin;
    return (int)value;
}

void NNSi_SndFaderUpdate(NNSSndFader* fader) {
    if (fader->counter < fader->frame) {
        fader->counter++;
    }
}

int NNSi_SndFaderIsFinished(const NNSSndFader* fader) {
    return fader->counter >= fader->frame ? 1 : 0;
}
