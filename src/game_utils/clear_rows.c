#include "game_utils.h"

typedef struct game_state game_state_t;

I8
clear_rows (struct game_state *state)
{
  I8 dst = BOARD_HEIGHT - 2;
  I8 cleared_count = 0;
  for (I8 src = BOARD_HEIGHT - 2; src >= 0; src--)
    {
      if ((state->board[src] & (unsigned)FILLED_ROW) != (unsigned)FILLED_ROW)
        {
          state->board[dst--] = state->board[src];
        }
    }

  while (dst >= 0)
    {
      state->board[dst--] = BOARD_WITH_WALLS;
      cleared_count++;
    }
  return cleared_count;
}
