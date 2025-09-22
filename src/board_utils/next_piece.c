#include "board_utils.h"

typedef struct tetris_bag tetris_bag_t;

U8
next_piece (tetris_bag_t *bag)
{
  if (bag->index >= 7)
    {
      shuffle_bag (bag->bag, &bag->rng_state);
      bag->index = 0;
    }
  return bag->bag[bag->index++];
}