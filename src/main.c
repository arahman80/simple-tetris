#include "game_utils.h"
#include "piece_select.h"
#include "score.h"
#include <ncurses.h> // <-- For TUI - replace with equivalent TI syscalls
#include <time.h>    // <-- For timing - replace with equivalent TI syscalls

typedef struct score_info score_info_t;
typedef struct tetris_bag tetris_bag_t;
typedef struct game_state game_state_t;

static const U8 piece_shapes[][4] = {
    {0x0, 0xF, 0x0, 0x0}, {0x6, 0x6, 0x0, 0x0}, {0x4, 0xE, 0x0, 0x0}, {0x6, 0xC, 0x0, 0x0},
    {0xC, 0x6, 0x0, 0x0}, {0x8, 0xE, 0x0, 0x0}, {0x2, 0xE, 0x0, 0x0},
};

void
draw_piece_preview (I8 y, I8 x, I8 piece_type)
{
  I8 idx = -1;
  switch (piece_type)
  {
  case PIECE_I:
    idx = 0;
    break;
  case PIECE_O:
    idx = 1;
    break;
  case PIECE_T:
    idx = 2;
    break;
  case PIECE_S:
    idx = 3;
    break;
  case PIECE_Z:
    idx = 4;
    break;
  case PIECE_J:
    idx = 5;
    break;
  case PIECE_L:
    idx = 6;
    break;
  default:
    return;
  }

  for (I8 r = 0; r < 4; r++)
  {
    for (I8 c = 0; c < 4; c++)
    {
      if ((piece_shapes[idx][r] >> (3 - c)) & 1)
      {
        mvprintw (y + r, x + c * 3, "[ ]");
      }
      else
      {
        mvprintw (y + r, x + c * 3, "  ");
      }
    }
  }
}

/* Externally dependent */
U0
print_bitboard (game_state_t* state, score_info_t* score)
{
  const I8 board_width = 10;
  const I8 x_offset = 13;

  for (I8 j = 0; j < BOARD_HEIGHT - 1; j++)
  {
    mvprintw (j, x_offset + 0, "<!");

    for (I8 i = 0; i < board_width; i++)
    {
      U16 board = state->board[j];
      U16 piece = state->piece[state->selected_rot][j];
      U8 bit1 = (U8) (((unsigned) board >> (12 - i)) & 1);
      U8 bit2 = (U8) (((unsigned) piece >> (12 - i)) & 1);
      U8 bit = bit1 | bit2;

      if (bit)
      {
        mvprintw (j, x_offset + 2 + i * 3, "[ ]");
      }
      else
      {
        mvprintw (j, x_offset + 2 + i * 3, " . ");
      }
    }

    mvprintw (j, x_offset + 2 + board_width * 3, ">!");
  }

  I8 bottom_y = BOARD_HEIGHT - 1;
  mvprintw (bottom_y, x_offset + 0, "<!");
  for (I8 i = 0; i < board_width; i++)
  {
    printw ("===");
  }
  printw (">!");

  bottom_y++;
  mvprintw (bottom_y, x_offset + 0, "\\/\\/\\/");
  for (I8 i = 1; i < board_width - 2; i++)
  {
    printw ("\\/\\/");
  }

  mvprintw (1, x_offset + 36, "Level %u", score->level);
  mvprintw (2, x_offset + 36, "Score: %u", score->score);
  mvprintw (3, x_offset + 36, "Lines: %u", score->lines);

  mvprintw (2, 0, "Held:");
  draw_piece_preview (3, 0, state->held_piece_type);

  mvprintw (10, 0, "Next:");
  draw_piece_preview (11, 0, state->next_piece_type);

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
  state.next_piece_type = next_piece (&bag);
  state.held_piece_type = next_piece (&bag);
  U8 placeholder = -1;
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
      do_rotation (&state, TRUE, state.piece_type == PIECE_I);
      break;
    case KEY_DOWN:
      do_rotation (&state, FALSE, state.piece_type == PIECE_I);
      break;
    case KEY_LEFT:
      h_shift (&state, 1, TRUE, FALSE);
      break;
    case KEY_RIGHT:
      h_shift (&state, 1, FALSE, FALSE);
      break;
    case 'f':
      if (v_shift (&state, 1, FALSE))
      {
        score.score += 1;
      }
      continue;
      break;
    case ' ':
      while (v_shift (&state, 1, FALSE))
      {
        score.score += 2;
      }
      elapsed = FALL_PERIOD;
      break;
    case 'p':
      mvprintw (23, 13, "Paused");
      nodelay (stdscr, FALSE);
      ch = getch ();
      nodelay (stdscr, TRUE);
    case 'h':
      if (placeholder < 0)
      {
        state.held_piece_type = state.next_piece_type;
        state.next_piece_type = next_piece (&bag);
      }
      else
      {
        placeholder = state.held_piece_type;
        state.held_piece_type = state.next_piece_type;
        state.next_piece_type = placeholder;
      }
    default:
      /* Consider adding default case */
      break;
    }

    if (elapsed >= FALL_PERIOD)
    {
      last_fall = now;
      if (!v_shift (&state, 1, FALSE))
      {
        add_piece_to_board (&state);
        U8 new_lines = clear_rows (&state);
        update_score (&score, new_lines);
        state.piece_type = state.next_piece_type;
        state.next_piece_type = next_piece (&bag);
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
