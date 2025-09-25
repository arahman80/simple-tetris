#include "game_utils.h"
#include "kicks.h"
#include "stdmac.h"

typedef struct game_state game_state_t;
typedef struct kick kick_t;

inline static void determine_from_to(U8 *from, U8 *to, U8 current_rot,
                                     BOOL clockwise);
inline static BOOL attempt_kick(game_state_t *state, U8 from, U8 to,
                                const kick_t (*kicks)[NUM_ROT][5], I8 step);

void do_rotation(game_state_t *state, BOOL clockwise, BOOL is_I) {
  U8 from, to;
  determine_from_to(&from, &to, state->selected_rot, clockwise);

  const kick_t(*kick_table)[NUM_ROT][5] = is_I ? I_kicks : JSLTZ_kicks;

  for (I8 i = 0; i < 5; i++) {
    if (attempt_kick(state, from, to, kick_table, i)) {
      return;
    }
  }
}

inline static void determine_from_to(U8 *from, U8 *to, U8 current_rot,
                                     BOOL clockwise) {
  *from = current_rot;
  if (clockwise) {
    *to = (current_rot + 1) % NUM_ROT;
  } else {
    /* Ensure to is positive with + NUM_ROT */
    *to = (current_rot + NUM_ROT - 1) % NUM_ROT;
  }
}

inline static BOOL attempt_kick(game_state_t *state, U8 from, U8 to,
                                const kick_t (*kicks)[NUM_ROT][5], I8 step) {
  I8 x_shift = kicks[from][to][step].x;
  I8 y_shift = kicks[from][to][step].y;

  state->selected_rot = to;
  h_shift(state, (x_shift >= 0) ? x_shift : -x_shift, x_shift < 0, TRUE);
  v_shift(state, -y_shift, TRUE);

  if (!test_interference(state)) {
    return TRUE;
  }

  state->selected_rot = from;
  h_shift(state, (x_shift >= 0) ? x_shift : -x_shift, x_shift > 0, TRUE);
  v_shift(state, y_shift, TRUE);

  return FALSE;
}
