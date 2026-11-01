/*
 * Unit 0x020A414C-0x020A4C0C: access to the backup memory of the cartridge, static object pointer
 * data_020d6cfc. The object holds eight access functions chosen from the backup device type;
 * each pair is one operation, synchronous then asynchronous. Each function calls the same
 * NitroSDK function with a different command. Bounds: hypothesis (after the sub-file unit; the
 * next function is the constructor of the stream class). All names are placeholders: the
 * operations (read, write, verify) are a hypothesis, only the use of the first as a read is seen
 * in the code. Real file name unknown.
 */
typedef unsigned short u16;
typedef unsigned long u32;

extern "C" {
int func_02074728(const void *src, void *dst, u32 size, void *callback, void *arg, bool async, int a, int b, int c);
int func_02073ff8();
int OS_GetLockID();
void func_02073ee0(u16 id);
void func_02073ed0(u16 id);
int func_020745b8(int type);
int func_02074714();
int func_020745ac();
int func_02073f30();
}

typedef int (*Unk020a4180Sync)(const void *src, void *dst, u32 size);
typedef int (*Unk020a4180Async)(const void *src, void *dst, u32 size, void *callback, void *arg);

class Unk020a4180 {
public:
    Unk020a4180Sync read;
    Unk020a4180Async readAsync;
    Unk020a4180Sync write;
    Unk020a4180Async writeAsync;
    Unk020a4180Sync verify;
    Unk020a4180Async verifyAsync;
    Unk020a4180Sync writeAndVerify;
    Unk020a4180Async writeAndVerifyAsync;
    u16 flags;
    u16 lockId;
    int status;
};

extern "C" {
void func_020a4a00(Unk020a4180 *p);
void func_020a4a34(Unk020a4180 *p);
bool func_020a4ad8(Unk020a4180 *p, const void *src, void *dst, u32 size);
int func_020a43f0(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a4438(const void *src, void *dst, u32 size);
int func_020a447c(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a44bc(const void *src, void *dst, u32 size);
int func_020a44fc(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a4540(const void *src, void *dst, u32 size);
int func_020a4584(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a45b8(const void *src, void *dst, u32 size);
int func_020a45ec(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a4634(const void *src, void *dst, u32 size);
int func_020a4678(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a46b8(const void *src, void *dst, u32 size);
int func_020a46f8(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a473c(const void *src, void *dst, u32 size);
int func_020a4780(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a47b4(const void *src, void *dst, u32 size);
int func_020a47e8(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a4830(const void *src, void *dst, u32 size);
int func_020a4874(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a48b4(const void *src, void *dst, u32 size);
int func_020a48f4(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a4938(const void *src, void *dst, u32 size);
int func_020a497c(const void *src, void *dst, u32 size, void *callback, void *arg);
int func_020a49b0(const void *src, void *dst, u32 size);
}

Unk020a4180 *data_020d6cfc;

extern "C" bool func_020a414c(Unk020a4180 *p) {
    int word;
    func_020a4a00(p);
    bool result = func_020a4ad8(p, 0, &word, 4);
    func_020a4a34(p);
    return result;
}

extern "C" Unk020a4180 *func_020a4180(Unk020a4180 *p, int type) {
    p->read = 0;
    p->readAsync = 0;
    p->write = 0;
    p->writeAsync = 0;
    p->verify = 0;
    p->verifyAsync = 0;
    p->writeAndVerify = 0;
    p->writeAndVerifyAsync = 0;
    p->flags = 0;
    p->lockId = 0;
    p->status = 0;
    data_020d6cfc = p;
    if (func_02073ff8() == 0) {
        return p;
    }
    int id = OS_GetLockID();
    if (id == -3) {
        return p;
    }
    p->lockId = id;
    func_02073ee0(p->lockId);
    int found = func_020745b8(type);
    func_02073ed0(p->lockId);
    if (found == 0) {
        return p;
    }
    switch (type) {
    case 0x901:
    case 0xd01:
    case 0x1001:
        p->read = func_020a49b0;
        p->readAsync = func_020a497c;
        p->write = func_020a4938;
        p->writeAsync = func_020a48f4;
        p->verify = func_020a48b4;
        p->verifyAsync = func_020a4874;
        p->writeAndVerify = func_020a4830;
        p->writeAndVerifyAsync = func_020a47e8;
        break;
    case 0x1202:
    case 0x1302:
    case 0x1402:
        p->read = func_020a47b4;
        p->readAsync = func_020a4780;
        p->write = func_020a473c;
        p->writeAsync = func_020a46f8;
        p->verify = func_020a46b8;
        p->verifyAsync = func_020a4678;
        p->writeAndVerify = func_020a4634;
        p->writeAndVerifyAsync = func_020a45ec;
        break;
    case 0xf03:
        p->read = func_020a45b8;
        p->readAsync = func_020a4584;
        p->write = func_020a4540;
        p->writeAsync = func_020a44fc;
        p->verify = func_020a44bc;
        p->verifyAsync = func_020a447c;
        p->writeAndVerify = func_020a4438;
        p->writeAndVerifyAsync = func_020a43f0;
        break;
    default:
        return p;
    }
    p->flags |= 1;
    if (!func_020a414c(p)) {
        p->flags &= ~1;
    }
    return p;
}

extern "C" int func_020a43f0(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(dst, (void *)src, size, callback, arg, true, 8, 10, 2);
}

extern "C" int func_020a4438(const void *src, void *dst, u32 size) {
    return func_02074728(dst, (void *)src, size, 0, 0, false, 8, 10, 2);
}

extern "C" int func_020a447c(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(dst, (void *)src, size, callback, arg, true, 9, 1, 1);
}

extern "C" int func_020a44bc(const void *src, void *dst, u32 size) {
    return func_02074728(dst, (void *)src, size, 0, 0, false, 9, 1, 1);
}

extern "C" int func_020a44fc(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(dst, (void *)src, size, callback, arg, true, 8, 10, 1);
}

extern "C" int func_020a4540(const void *src, void *dst, u32 size) {
    return func_02074728(dst, (void *)src, size, 0, 0, false, 8, 10, 1);
}

extern "C" int func_020a4584(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(src, dst, size, callback, arg, true, 6, 1, 0);
}

extern "C" int func_020a45b8(const void *src, void *dst, u32 size) {
    return func_02074728(src, dst, size, 0, 0, false, 6, 1, 0);
}

extern "C" int func_020a45ec(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(dst, (void *)src, size, callback, arg, true, 7, 10, 2);
}

extern "C" int func_020a4634(const void *src, void *dst, u32 size) {
    return func_02074728(dst, (void *)src, size, 0, 0, false, 7, 10, 2);
}

extern "C" int func_020a4678(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(dst, (void *)src, size, callback, arg, true, 9, 1, 1);
}

extern "C" int func_020a46b8(const void *src, void *dst, u32 size) {
    return func_02074728(dst, (void *)src, size, 0, 0, false, 9, 1, 1);
}

extern "C" int func_020a46f8(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(dst, (void *)src, size, callback, arg, true, 7, 10, 1);
}

extern "C" int func_020a473c(const void *src, void *dst, u32 size) {
    return func_02074728(dst, (void *)src, size, 0, 0, false, 7, 10, 1);
}

extern "C" int func_020a4780(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(src, dst, size, callback, arg, true, 6, 1, 0);
}

extern "C" int func_020a47b4(const void *src, void *dst, u32 size) {
    return func_02074728(src, dst, size, 0, 0, false, 6, 1, 0);
}

extern "C" int func_020a47e8(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(dst, (void *)src, size, callback, arg, true, 8, 10, 2);
}

extern "C" int func_020a4830(const void *src, void *dst, u32 size) {
    return func_02074728(dst, (void *)src, size, 0, 0, false, 8, 10, 2);
}

extern "C" int func_020a4874(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(dst, (void *)src, size, callback, arg, true, 9, 1, 1);
}

extern "C" int func_020a48b4(const void *src, void *dst, u32 size) {
    return func_02074728(dst, (void *)src, size, 0, 0, false, 9, 1, 1);
}

extern "C" int func_020a48f4(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(dst, (void *)src, size, callback, arg, true, 8, 10, 1);
}

extern "C" int func_020a4938(const void *src, void *dst, u32 size) {
    return func_02074728(dst, (void *)src, size, 0, 0, false, 8, 10, 1);
}

extern "C" int func_020a497c(const void *src, void *dst, u32 size, void *callback, void *arg) {
    return func_02074728(src, dst, size, callback, arg, true, 6, 1, 0);
}

extern "C" int func_020a49b0(const void *src, void *dst, u32 size) {
    return func_02074728(src, dst, size, 0, 0, false, 6, 1, 0);
}

extern "C" int func_020a49e4(Unk020a4180 *p) {
    if (!(p->flags & 1)) {
        return 0;
    }
    return func_02074714();
}

extern "C" void func_020a4a00(Unk020a4180 *p) {
    if (!(p->flags & 1)) {
        return;
    }
    if (p->flags & 2) {
        return;
    }
    func_02073ee0(p->lockId);
    p->flags |= 2;
}

extern "C" void func_020a4a34(Unk020a4180 *p) {
    if (!(p->flags & 1)) {
        return;
    }
    if (!(p->flags & 2)) {
        return;
    }
    if (p->flags & 4) {
        return;
    }
    func_02073ed0(p->lockId);
    p->flags &= ~2;
}

extern "C" int func_020a4a70(Unk020a4180 *p) {
    if (!(p->flags & 1) || !(p->flags & 2)) {
        return 0;
    }
    if (!(p->flags & 4)) {
        return 0;
    }
    if (func_020745ac() == 0) {
        return 1;
    }
    p->status = func_02073f30() == 0 ? 2 : 3;
    p->flags &= ~4;
    return 0;
}

extern "C" bool func_020a4ad8(Unk020a4180 *p, const void *src, void *dst, u32 size) {
    if (!(p->flags & 1) || !(p->flags & 2) || (p->flags & 4)) {
        return false;
    }
    p->status = 0;
    return p->read(src, dst, size) != 0;
}

extern "C" void func_020a4b2c(Unk020a4180 *p, const void *src, void *dst, u32 size) {
    if (!(p->flags & 1)) {
        return;
    }
    if (!(p->flags & 2)) {
        return;
    }
    if (p->flags & 4) {
        return;
    }
    p->status = 1;
    p->flags |= 4;
    p->readAsync(src, dst, size, 0, 0);
}

extern "C" void func_020a4b9c(Unk020a4180 *p, const void *src, void *dst, u32 size) {
    if (!(p->flags & 1)) {
        return;
    }
    if (!(p->flags & 2)) {
        return;
    }
    if (p->flags & 4) {
        return;
    }
    p->status = 1;
    p->flags |= 4;
    p->writeAndVerifyAsync(src, dst, size, 0, 0);
}
