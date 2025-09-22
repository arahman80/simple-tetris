#include "game_utils.h"
#include "initializers.h"

typedef enum piece piece_t;
typedef struct game_state game_state_t;

U0
init_piece_board (struct game_state* state)
{
  for (I8 i = 0; i < NUM_ROT; i++)
  {
    for (I8 j = 0; j < BOARD_HEIGHT; j++)
    {
      state->piece[i][j] = 0x0 /* 0000000000000000 */;
    }
  }

  switch (state->piece_type)
  {
  case PIECE_O:
    init_o (state->piece);
    break;
  case PIECE_T:
    init_t (state->piece);
    break;
  case PIECE_I:
    init_i (state->piece);
    break;
  case PIECE_S:
    init_s (state->piece);
    break;
  case PIECE_Z:
    init_z (state->piece);
    break;
  case PIECE_L:
    init_l (state->piece);
    break;
  case PIECE_J:
    init_j (state->piece);
    break;
  default:
    /* Malformed piece: do absolutely nothing */
    break;
  }
}
