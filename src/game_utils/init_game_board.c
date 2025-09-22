#include "game_utils.h"

typedef struct game_state game_state_t;

U0
init_game_board (struct game_state *state)
{
  for (U8 i = 0; i < BOARD_HEIGHT - 1; i++)
    {
      state->board[i] = BOARD_WITH_WALLS;
    }

  state->board[BOARD_HEIGHT - 1] = 0b1111111111111111;
}