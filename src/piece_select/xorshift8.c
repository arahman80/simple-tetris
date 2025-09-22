#include "piece_select.h"

U8
xorshift8 (U8 *state)
{
  U8 x = *state;
  x ^= UCAST (x << 3);
  x ^= UCAST (x >> 5);
  x ^= UCAST (x << 2);
  *state = x;
  return x;
}