#ifndef STDMAC_H
#define STDMAC_H

#define _POSIX_C_SOURCE 199309L
#define _XOPEN_SOURCE 700

typedef enum { FALSE = 0, TRUE = 1 } BOOL;
#define U32 unsigned long
#define U16 unsigned int
#define U8 unsigned char
#define I16 int
#define I8 signed char
#define U0 void
#define BOARD_WITH_WALLS 0b0010000000000100
#define FILLED_ROW 0b0011111111111100
#define BOARD_HEIGHT 21
#define NUM_ROT 4
#define BASE_US_BETWEEN_FRAMES 50000
#define FALL_PERIOD 0.25

#endif
