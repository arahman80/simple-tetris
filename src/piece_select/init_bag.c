#include "piece_select.h"

typedef struct tetris_bag tetris_bag_t;

u0
init_bag (tetris_bag_t* bag, U8 seed)
{
  bag->rng_state = seed;
  bag->index = 7;
}
