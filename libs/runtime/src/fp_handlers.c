/*
 * Soft-float trap handlers. Hypotheses: the file name, the size of the table (the
 * `.bss` symbols are 0x1C bytes apart). A separate file from fp_status.c: `.bss` is
 * sorted by size inside an object, and the smaller word comes first here.
 */

unsigned int data_020c7d00[7];

unsigned int* func_02085750(void) {
    return data_020c7d00;
}
