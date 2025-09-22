#include "game_utils.h"

typedef struct game_state game_state_t;

BOOL
test_interference (struct game_state* state)
{
  for (I8 i = 0; i < BOARD_HEIGHT; i++)
  {
    if (state->board[i] & state->piece[state->selected_rot][i])
    {
      return TRUE;
    }
  }

  return FALSE;
}
