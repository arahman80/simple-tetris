#include "game_utils.h"

typedef struct game_state game_state_t;

BOOL
fall (struct game_state *state)
{
  for (I8 i = 0; i < BOARD_HEIGHT - 1; i++)
    {
      if (state->board[i + 1] & state->piece[state->selected_rot][i])
        {
          return FALSE;
        }
    }

  for (I8 i = 0; i < NUM_ROT; i++)
    {
      for (I8 j = BOARD_HEIGHT - 1; j > 0; j--)
        {
          state->piece[i][j] = state->piece[i][j - 1];
        }

      state->piece[i][0] = 0b0000000000000000;
    }

  return TRUE;
}