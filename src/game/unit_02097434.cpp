/*
 * Unit 0x02097434-0x02097A58: touch screen state. One static object
 * (data_020c8068) keeps the current, pressed and released points, the drag
 * movement and tap counters; it is updated once per frame from the touch panel
 * driver and read through the query functions below.
 *
 * Screen argument of the queries: 0 = either screen, 1 = only while bit 0x20 is set
 * (the touch screen is the upper one: POWCNT1 bit 15 clear), 2 = only while it is
 * clear.
 *
 * Bounds: hypothesis. Before 0x02097434, func_020973bc initialises other objects
 * (data_020c8034...), built by __sinit_020ae310; from 0x02097A58 come fixed-point
 * helpers (hardware square root, arc cosine). __sinit_020ae33c builds the object,
 * data_020bd570 holds the drag and double-tap thresholds. Real file name unknown.
 */

typedef unsigned short u16;
typedef unsigned long u32;

struct Unk02097434Sample {
    u16 x;
    u16 y;
    u16 touch;
    u16 invalid;
};

struct Unk020bd570 {
    int tapFrames;
    int dragDistance;
};

class Unk020c8068 {
public:
    Unk020c8068() {
        x = 0;
        y = 0;
        pressX = 0;
        pressY = 0;
        releaseX = 0;
        releaseY = 0;
        lastX = 0;
        lastY = 0;
        moveX = 0;
        moveY = 0;
        distance = 0;
        taps = 0;
        held = 0;
        idle = 0;
    }

    u32 flags;
    int x;
    int y;
    int pressX;
    int pressY;
    int releaseX;
    int releaseY;
    int lastX;
    int lastY;
    int moveX;
    int moveY;
    int distance;
    int taps;
    int held;
    int idle;
};

extern "C" void func_0207eaec();
extern "C" void func_0207ea6c(Unk02097434Sample *sample);
extern "C" void func_0207eb8c(void *param);
extern "C" int func_0207ecd4(void *param);
extern "C" void func_0207ed80();
extern "C" int func_02097a6c(long long x);

Unk020bd570 data_020bd570 = {0x10, 0x40};
Unk020c8068 data_020c8068;

static inline bool func_screen(int screen) {
    if (screen == 0) {
        return true;
    }
    if (screen == 1 && (data_020c8068.flags & 0x20)) {
        return true;
    }
    if (screen == 2 && !(data_020c8068.flags & 0x20)) {
        return true;
    }
    return false;
}

bool func_0209774c(int screen);
bool func_02097840(int screen);
bool func_020978dc(int screen);
bool func_02097950(int screen);
bool func_020979c4(int screen);

void func_02097434() {
    char param[8];

    func_0207ed80();
    if (func_0207ecd4(param) == 0) {
        return;
    }
    func_0207eb8c(param);
}

void func_02097464() {
    Unk02097434Sample sample;
    u32 old;
    u32 upper;

    func_0207eaec();
    func_0207ea6c(&sample);
    old = data_020c8068.flags;
    data_020c8068.flags = old & ~0x67;
    upper = old & 0x20;
    if (((*(volatile u16 *)0x4000304 & 0x8000) >> 15) == 0) {
        data_020c8068.flags |= 0x20;
    }
    if (upper != (data_020c8068.flags & 0x20)) {
        data_020c8068.flags |= 0x40;
    }
    if (sample.touch != 0 && sample.invalid == 0) {
        data_020c8068.x = sample.x;
        data_020c8068.y = sample.y;
        data_020c8068.flags |= 1;
    }
    if (!(data_020c8068.flags & 1) && (old & 1)) {
        data_020c8068.flags |= 4;
        if (data_020c8068.flags & 8) {
            data_020c8068.flags |= 0x10;
        }
        data_020c8068.flags &= ~8;
        data_020c8068.idle = 0;
    }
    if ((data_020c8068.flags & 1) && !(old & 1)) {
        data_020c8068.flags = (data_020c8068.flags | 2) & ~0x10;
        data_020c8068.held = 0;
        data_020c8068.lastX = 0;
        data_020c8068.lastY = 0;
    }
    if (func_0209774c(0)) {
        data_020c8068.pressX = data_020c8068.x;
        data_020c8068.pressY = data_020c8068.y;
    }
    if (func_02097840(0)) {
        data_020c8068.releaseX = data_020c8068.x;
        data_020c8068.releaseY = data_020c8068.y;
    }
    if (func_020978dc(0) && !func_020979c4(0)) {
        int dy = data_020c8068.y - data_020c8068.pressY;
        int dx = data_020c8068.x - data_020c8068.pressX;
        if (dx * dx + dy * dy > data_020bd570.dragDistance) {
            data_020c8068.flags |= 8;
        }
    }
    if (func_020978dc(0)) {
        int mx = data_020c8068.x - (data_020c8068.lastX + data_020c8068.pressX);
        int my;
        data_020c8068.moveX = mx;
        my = data_020c8068.y - (data_020c8068.lastY + data_020c8068.pressY);
        data_020c8068.moveY = my;
        data_020c8068.distance = func_02097a6c((mx * mx + my * my) << 12) >> 12;
        data_020c8068.lastX = data_020c8068.x - data_020c8068.pressX;
        data_020c8068.lastY = data_020c8068.y - data_020c8068.pressY;
    }
    if (!func_0209774c(0) && func_020978dc(0)) {
        data_020c8068.held++;
    }
    if (!func_02097840(0) && func_02097950(0)) {
        data_020c8068.idle++;
    }
    if (!func_0209774c(0)) {
        return;
    }
    if (data_020c8068.idle <= data_020bd570.tapFrames) {
        data_020c8068.taps++;
    } else {
        data_020c8068.taps = 1;
    }
}

bool func_0209774c(int screen) {
    if (screen != 0 && func_screen(screen) && (data_020c8068.flags & 0x40) && func_020978dc(0)) {
        return true;
    }
    if (func_screen(screen)) {
        return (data_020c8068.flags & 2) != 0;
    }
    return false;
}

bool func_02097840(int screen) {
    if (func_screen(screen)) {
        return (data_020c8068.flags & 4) != 0;
    }
    if ((data_020c8068.flags & 0x40) && func_020978dc(0)) {
        return true;
    }
    return false;
}

bool func_020978dc(int screen) {
    if (func_screen(screen)) {
        return (data_020c8068.flags & 1) != 0;
    }
    return false;
}

bool func_02097950(int screen) {
    if (func_screen(screen)) {
        return !(data_020c8068.flags & 1);
    }
    return true;
}

bool func_020979c4(int screen) {
    if (func_screen(screen)) {
        return (data_020c8068.flags & 8) != 0;
    }
    return false;
}

void func_02097a38() {
    data_020c8068.taps = 0;
}

int *func_02097a4c() {
    return &data_020c8068.x;
}
