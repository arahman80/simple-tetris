#include "game_utils.h"

typedef struct game_state game_state_t;

U0 init_game_board(game_state_t *state) {
  for (I8 i = 0; i < BOARD_HEIGHT - 1; i++) {
    state->board[i] = BOARD_WITH_WALLS;
  }

  state->board[BOARD_HEIGHT - 1] = 0xFFFF /* 1111111111111111 */;
}
