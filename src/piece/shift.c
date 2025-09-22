#include "game_utils.h"

typedef struct game_state game_state_t;

U0
shift (struct game_state* state, BOOL left)
{
  for (I8 i = 0; i < BOARD_HEIGHT; i++)
  {
    if (state->board[i] & (left ? state->piece[state->selected_rot][i] << (unsigned) 1
                                : state->piece[state->selected_rot][i] >> (unsigned) 1))
    {
      return;
    }
  }

  for (I8 i = 0; i < BOARD_HEIGHT; i++)
  {
    if (left)
    {
      for (I8 j = 0; j < NUM_ROT; j++)
      {
        state->piece[j][i] <<= (unsigned) 1;
      }
    }
    else
    {
      for (I8 j = 0; j < NUM_ROT; j++)
      {
        state->piece[j][i] >>= (unsigned) 1;
      }
    }
  }
}
