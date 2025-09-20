#ifndef TEST_MACROS_H
#define TEST_MACROS_H

#include <stdio.h>
#define BOARD_WITH_WALLS 0b0010000000000100
#define FILLED_ROW 0b0011111111111100

#define ASSERT_TRUE(expr, msg) \
    if (!(expr)) { \
        printf("FAIL: %s\n", msg); \
        fails++; \
    } else { \
        printf("PASS: %s\n", msg); \
        passes++; \
    }

#endif