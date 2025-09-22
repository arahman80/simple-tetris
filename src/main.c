#include "board_utils.h"
#include <ncurses.h> // <-- For TUI - replace with equivalent TI syscalls
#include <stdlib.h>  // <-- For RNG - replace with equivalent TI syscalls
#include <time.h>    // <-- For timing - replace with equivalent TI syscalls

typedef struct score_info score_info_t;

/* Externally dependent */
U0
print_bitboard (U16 board_in[BOARD_HEIGHT], U16 piece_in[BOARD_HEIGHT],
                score_info_t score)
{
  start_color ();
  init_pair (1, COLOR_BLACK, COLOR_WHITE);
  init_pair (2, COLOR_BLACK, COLOR_BLACK);

  for (I16 j = 0; j < BOARD_HEIGHT - 1; j++)
    {
      U16 board = board_in[j];
      U16 piece = piece_in[j];
      for (I16 i = 15; i >= 0; i--)
        {
          U8 bit1 = (board >> i) & 1;
          U8 bit2 = (piece >> i) & 1;
          U8 bit = bit1 | bit2;

          if (bit)
            attron (COLOR_PAIR (1));
          else
            attron (COLOR_PAIR (2));

          mvaddch (j, 15 - i, ' ');

          attroff (COLOR_PAIR (1));
          attroff (COLOR_PAIR (2));
        }
    }
  mvprintw (1, 16, "Level %u", score.level);
  mvprintw (2, 16, "Score: %lu", score.score);
  mvprintw (3, 16, "Lines: %u", score.lines);
  refresh ();
}

/* Externally dependent */
I16
main (U0)
{
  srand (time (NULL));
  U16 board[BOARD_HEIGHT] = { 0 };
  U16 piece[NUM_ROT][BOARD_HEIGHT] = { 0 };
  I16 selected_rot = 0;
  score_info_t score = { 1, 0, 0, 0 };
  init_game_board (board);
  init_piece_board (piece, rand () % 7);
  struct timespec last_fall;
  clock_gettime (CLOCK_MONOTONIC, &last_fall);

  struct timespec frame_delay;
  frame_delay.tv_sec = BASE_US_BETWEEN_FRAMES / 1000000;
  frame_delay.tv_nsec = (BASE_US_BETWEEN_FRAMES % 1000000) * 1000;

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
      double elapsed = (now.tv_sec - last_fall.tv_sec)
                       + (now.tv_nsec - last_fall.tv_nsec) / 1e9;

      switch (ch)
        {
        case KEY_UP:
          if (!test_interference (board, piece, (selected_rot + 1) % NUM_ROT))
            {
              selected_rot = (selected_rot + 1) % NUM_ROT;
            }
          break;
        case KEY_DOWN:
          if (!test_interference (board, piece, (selected_rot - 1) % NUM_ROT))
            {
              selected_rot = (selected_rot - 1) % NUM_ROT;
            }
          break;
        case KEY_LEFT:
          shift (board, piece, selected_rot, 1);
          break;
        case KEY_RIGHT:
          shift (board, piece, selected_rot, 0);
          break;
        case 'f':
          if (fall (board, piece, selected_rot))
            {
              score.score += 1;
            }
          continue;
          break;
        case ' ':
          while (fall (board, piece, selected_rot))
            {
              score.score += 2;
            }
          elapsed = FALL_PERIOD;
          break;
        }

      if (elapsed >= FALL_PERIOD)
        {
          last_fall = now;
          if (!fall (board, piece, selected_rot))
            {
              add_piece_to_board (board, piece, selected_rot);
              U8 new_lines = clear_rows (board);
              score = update_score (score, new_lines);
              init_piece_board (piece, rand () % 7);
              selected_rot = 0;

              if (test_interference (board, piece, selected_rot))
                {
                  endwin ();
                  return 0;
                }
            }
        }

      erase ();
      print_bitboard (board, piece[selected_rot], score);
      nanosleep (&frame_delay, NULL);
    }

  endwin ();
  return 0;
}
