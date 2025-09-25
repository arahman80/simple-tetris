#include "game_utils.h"

typedef enum piece piece_t;
typedef struct game_state game_state_t;

static inline U0 init_o(U16 piece[NUM_ROT][BOARD_HEIGHT]);
static inline U0 init_t(U16 piece[NUM_ROT][BOARD_HEIGHT]);
static inline U0 init_i(U16 piece[NUM_ROT][BOARD_HEIGHT]);
static inline U0 init_s(U16 piece[NUM_ROT][BOARD_HEIGHT]);
static inline U0 init_z(U16 piece[NUM_ROT][BOARD_HEIGHT]);
static inline U0 init_l(U16 piece[NUM_ROT][BOARD_HEIGHT]);
static inline U0 init_j(U16 piece[NUM_ROT][BOARD_HEIGHT]);

U0 init_piece_board(game_state_t *state) {
  for (I8 i = 0; i < NUM_ROT; i++) {
    for (I8 j = 0; j < BOARD_HEIGHT; j++) {
      state->piece[i][j] = 0x0 /* 0000000000000000 */;
    }
  }

  switch (state->piece_type) {
  case PIECE_O:
    init_o(state->piece);
    break;
  case PIECE_T:
    init_t(state->piece);
    break;
  case PIECE_I:
    init_i(state->piece);
    break;
  case PIECE_S:
    init_s(state->piece);
    break;
  case PIECE_Z:
    init_z(state->piece);
    break;
  case PIECE_L:
    init_l(state->piece);
    break;
  case PIECE_J:
    init_j(state->piece);
    break;
  default:
    /* Malformed piece: do absolutely nothing */
    break;
  }
}

static inline U0 init_o(U16 piece[NUM_ROT][BOARD_HEIGHT]) {
  piece[0][0] = 0x180 /* 0000000110000000 */;
  piece[0][1] = 0x180 /* 0000000110000000 */;

  piece[1][0] = 0x180 /* 0000000110000000 */;
  piece[1][1] = 0x180 /* 0000000110000000 */;

  piece[2][0] = 0x180 /* 0000000110000000 */;
  piece[2][1] = 0x180 /* 0000000110000000 */;

  piece[3][0] = 0x180 /* 0000000110000000 */;
  piece[3][1] = 0x180 /* 0000000110000000 */;
}

static inline U0 init_t(U16 piece[NUM_ROT][BOARD_HEIGHT]) {
  piece[0][0] = 0x100 /* 0000000100000000 */;
  piece[0][1] = 0x380 /* 0000001110000000 */;

  piece[1][0] = 0x100 /* 0000000100000000 */;
  piece[1][1] = 0x180 /* 0000000110000000 */;
  piece[1][2] = 0x100 /* 0000000100000000 */;

  piece[2][1] = 0x380 /* 0000001110000000 */;
  piece[2][2] = 0x100 /* 0000000100000000 */;

  piece[3][0] = 0x100 /* 0000000100000000 */;
  piece[3][1] = 0x300 /* 0000001100000000 */;
  piece[3][2] = 0x100 /* 0000000100000000 */;
}

static inline U0 init_i(U16 piece[NUM_ROT][BOARD_HEIGHT]) {
  piece[0][1] = 0x3C0 /* 0000001111000000 */;
  piece[1][0] = 0x80 /* 0000000010000000 */;
  piece[1][1] = 0x80 /* 0000000010000000 */;
  piece[1][2] = 0x80 /* 0000000010000000 */;
  piece[1][3] = 0x80 /* 0000000010000000 */;

  piece[2][2] = 0x3C0 /* 0000001111000000 */;

  piece[3][0] = 0x100 /* 0000000100000000 */;
  piece[3][1] = 0x100 /* 0000000100000000 */;
  piece[3][2] = 0x100 /* 0000000100000000 */;
  piece[3][3] = 0x100 /* 0000000100000000 */;
}

static inline U0 init_s(U16 piece[NUM_ROT][BOARD_HEIGHT]) {
  piece[0][0] = 0x180 /* 0000000110000000 */;
  piece[0][1] = 0x300 /* 0000001100000000 */;

  piece[1][0] = 0x100 /* 0000000100000000 */;
  piece[1][1] = 0x180 /* 0000000110000000 */;
  piece[1][2] = 0x80 /* 0000000010000000 */;

  piece[2][1] = 0x180 /* 0000000110000000 */;
  piece[2][2] = 0x300 /* 0000001100000000 */;

  piece[3][0] = 0x200 /* 0000001000000000 */;
  piece[3][1] = 0x300 /* 0000001100000000 */;
  piece[3][2] = 0x100 /* 0000000100000000 */;
}

static inline U0 init_z(U16 piece[NUM_ROT][BOARD_HEIGHT]) {
  piece[0][0] = 0x300 /* 0000001100000000 */;
  piece[0][1] = 0x180 /* 0000000110000000 */;

  piece[1][0] = 0x80 /* 0000000010000000 */;
  piece[1][1] = 0x180 /* 0000000110000000 */;
  piece[1][2] = 0x100 /* 0000000100000000 */;

  piece[2][1] = 0x300 /* 0000001100000000 */;
  piece[2][2] = 0x180 /* 0000000110000000 */;

  piece[3][0] = 0x100 /* 0000000100000000 */;
  piece[3][1] = 0x300 /* 0000001100000000 */;
  piece[3][2] = 0x200 /* 0000001000000000 */;
}

static inline U0 init_l(U16 piece[NUM_ROT][BOARD_HEIGHT]) {
  piece[0][0] = 0x200 /* 0000001000000000 */;
  piece[0][1] = 0x380 /* 0000001110000000 */;

  piece[1][0] = 0x180 /* 0000000110000000 */;
  piece[1][1] = 0x100 /* 0000000100000000 */;
  piece[1][2] = 0x100 /* 0000000100000000 */;

  piece[2][1] = 0x380 /* 0000001110000000 */;
  piece[2][2] = 0x80 /* 0000000010000000 */;

  piece[3][0] = 0x100 /* 0000000100000000 */;
  piece[3][1] = 0x100 /* 0000000100000000 */;
  piece[3][2] = 0x300 /* 0000001100000000 */;
}

static inline U0 init_j(U16 piece[NUM_ROT][BOARD_HEIGHT]) {
  piece[0][0] = 0x80 /* 0000000010000000 */;
  piece[0][1] = 0x380 /* 0000001110000000 */;

  piece[1][0] = 0x100 /* 0000000100000000 */;
  piece[1][1] = 0x100 /* 0000000100000000 */;
  piece[1][2] = 0x180 /* 0000000110000000 */;

  piece[2][1] = 0x380 /* 0000001110000000 */;
  piece[2][2] = 0x200 /* 0000001000000000 */;

  piece[3][0] = 0x300 /* 0000001100000000 */;
  piece[3][1] = 0x100 /* 0000000100000000 */;
  piece[3][2] = 0x100 /* 0000000100000000 */;
}
