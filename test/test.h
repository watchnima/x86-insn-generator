#ifndef NASM_TEST_H
#define NASM_TEST_H

#define assign_arr5(arr,a0,a1,a2,a3,a4) \
    { \
        arr[0] = a0; \
        arr[1] = a1; \
        arr[2] = a2; \
        arr[3] = a3; \
        arr[4] = a4; \
    }

void test_mov(void);

#endif
