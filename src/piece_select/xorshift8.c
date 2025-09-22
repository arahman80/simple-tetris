#include "piece_select.h"

U8
xorshift8 (U8 *state)
{
  U8 x = *state;
  x ^= (U8) ((unsigned) x << 3);
  x ^= (U8) ((unsigned) x >> 5);
  x ^= (U8) ((unsigned) x << 2);
  *state = x;
  return x;
}