#include "game_utils.h"

typedef struct game_state game_state_t;

U0
add_piece_to_board (game_state_t* state)
{
  for (I8 i = 0; i < BOARD_HEIGHT; i++)
  {
    state->board[i] |= state->piece[state->selected_rot][i];
  }
}
