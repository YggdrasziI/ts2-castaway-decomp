/*
 * Unit 0x02099840-0x02099870: global operator new, new[], delete and delete[].
 *
 * Names: the call sites have the shapes mwccarm gives new and delete expressions:
 * `new T(...)` calls 0x02099840, tests the result for null, then calls a
 * constructor; `delete p` tests p for null, calls a destructor, then 0x02099858;
 * `new T[n]` scales n by the element size before calling 0x0209984C. With 50 to
 * 200 callers each across unrelated classes, they are the global operators rather
 * than class-specific ones.
 *
 * Bounds: hypothesis. The four functions may belong to unit_02099800.cpp before
 * them or to the allocator after them (func_02099b44 and func_02099b60, which
 * they forward to). Real file name unknown.
 */

extern "C" void *func_02099b44(unsigned long size);
extern "C" void func_02099b60(void *ptr);

void *operator new(unsigned long size) {
    return func_02099b44(size);
}

void *operator new[](unsigned long size) {
    return func_02099b44(size);
}

void operator delete(void *ptr) {
    func_02099b60(ptr);
}

void operator delete[](void *ptr) {
    func_02099b60(ptr);
}
