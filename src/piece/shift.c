#include "game_utils.h"

typedef struct game_state game_state_t;

U0
shift (struct game_state *state, BOOL left)
{
  for (U8 i = 0; i < BOARD_HEIGHT; i++)
    {
      if (state->board[i]
          & (left ? state->piece[state->selected_rot][i] << 1
                  : state->piece[state->selected_rot][i] >> 1))
        {
          return;
        }
    }

  for (U8 i = 0; i < BOARD_HEIGHT; i++)
    {
      if (left)
        {
          for (U8 j = 0; j < NUM_ROT; j++)
            {
              state->piece[j][i] <<= 1;
            }
        }
      else
        {
          for (U8 j = 0; j < NUM_ROT; j++)
            {
              state->piece[j][i] >>= 1;
            }
        }
    }
}