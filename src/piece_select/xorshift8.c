#include "piece_select.h"

U8
xorshift8 (U8 *state)
{
  U8 x = *state;
  x ^= x << 3;
  x ^= x >> 5;
  x ^= x << 2;
  *state = x;
  return x;
}