#include "game_utils.h"
#include "piece_select.h"
#include "score.h"
#include <ncurses.h> // <-- For TUI - replace with equivalent TI syscalls
#include <time.h>    // <-- For timing - replace with equivalent TI syscalls

typedef struct score_info score_info_t;
typedef struct tetris_bag tetris_bag_t;
typedef struct game_state game_state_t;

/* Externally dependent */
U0
print_bitboard (game_state_t* state, score_info_t* score)
{
  start_color ();
  init_pair (1, COLOR_BLACK, COLOR_WHITE);
  init_pair (2, COLOR_BLACK, COLOR_BLACK);

  for (I8 j = 0; j < BOARD_HEIGHT - 1; j++)
  {
    U16 board = state->board[j];
    U16 piece = state->piece[state->selected_rot][j];
    for (I8 i = 12; i >= 3; i--)
    {
      U8 bit1 = (U8) (((unsigned) board >> i) & 1);
      U8 bit2 = (U8) (((unsigned) piece >> i) & 1);
      U8 bit = bit1 | bit2;

      if (bit)
      {
        attron (COLOR_PAIR (1));
      }
      else
      {
        attron (COLOR_PAIR (2));
      }

      mvaddch (j, 15 - i, ' ');

      attroff (COLOR_PAIR (1));
      attroff (COLOR_PAIR (2));
    }
  }

  mvprintw (1, 16, "Level %u", score->level);
  mvprintw (2, 16, "Score: %u", score->score);
  mvprintw (3, 16, "Lines: %u", score->lines);
  refresh ();
}

/* Externally dependent */
I16
main (U0)
{
  tetris_bag_t bag = {0};
  game_state_t state = {0};
  init_bag (&bag, 123);
  state.piece_type = next_piece (&bag);
  score_info_t score = {1, 0, 0, 0};
  init_game_board (&state);
  init_piece_board (&state);
  struct timespec last_fall = {0};
  clock_gettime (CLOCK_MONOTONIC, &last_fall);

  struct timespec frame_delay = {0};
  frame_delay.tv_sec = (__syscall_slong_t) BASE_US_BETWEEN_FRAMES / 1000000;
  frame_delay.tv_nsec = (__syscall_slong_t) (BASE_US_BETWEEN_FRAMES % 1000000) * 1000;

  initscr ();
  noecho ();
  cbreak ();
  curs_set (0);
  keypad (stdscr, TRUE);
  nodelay (stdscr, TRUE);

  I16 ch;
  while ((ch = getch ()) != 'q')
  {
    struct timespec now;
    clock_gettime (CLOCK_MONOTONIC, &now);
    double elapsed = (double) (now.tv_sec - last_fall.tv_sec) + (double) (now.tv_nsec - last_fall.tv_nsec) / 1e9;

    switch (ch)
    {
    case KEY_UP:
      state.selected_rot = (state.selected_rot + 1) % NUM_ROT;
      if (test_interference (&state))
      {
        state.selected_rot = (state.selected_rot - 1) % NUM_ROT;
      }
      break;
    case KEY_DOWN:
      state.selected_rot = (state.selected_rot - 1) % NUM_ROT;
      if (test_interference (&state))
      {
        state.selected_rot = (state.selected_rot + 1) % NUM_ROT;
      }
      break;
    case KEY_LEFT:
      shift (&state, TRUE);
      break;
    case KEY_RIGHT:
      shift (&state, FALSE);
      break;
    case 'f':
      if (fall (&state))
      {
        score.score += 1;
      }
      continue;
      break;
    case ' ':
      while (fall (&state))
      {
        score.score += 2;
      }
      elapsed = FALL_PERIOD;
      break;
    default:
      /* Consider default case */
      break;
    }

    if (elapsed >= FALL_PERIOD)
    {
      last_fall = now;
      if (!fall (&state))
      {
        add_piece_to_board (&state);
        U8 new_lines = clear_rows (&state);
        update_score (&score, new_lines);
        state.piece_type = next_piece (&bag);
        init_piece_board (&state);
        state.selected_rot = 0;

        if (test_interference (&state))
        {
          endwin ();
          return 0;
        }
      }
    }

    erase ();
    print_bitboard (&state, &score);
    nanosleep (&frame_delay, NULL);
  }

  endwin ();
  return 0;
}
