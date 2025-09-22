#include "game_utils.h"

typedef struct game_state game_state_t;

U8
clear_rows (struct game_state *state)
{
  U8 dst = BOARD_HEIGHT - 2;
  U8 cleared_count = 0;
  for (U8 src = BOARD_HEIGHT - 2; src >= 0; src--)
    {
      if ((state->board[src] & FILLED_ROW) != FILLED_ROW)
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
