#include "piece_select.h"

U0 shuffle_bag(U8 bag[7], U8 *random_state) {
  for (I8 i = 0; i < 7; i++) {
    bag[i] = i;
  }

  for (I8 i = 0; i < 7; i++) {
    U8 j = xorshift8(random_state) % 7;
    U8 tmp = bag[i];
    bag[i] = bag[j];
    bag[j] = tmp;
  }
}
