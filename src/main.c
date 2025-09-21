#include "board_utils.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* Externally dependent */
void
print_bitboard (u16 board_in[BOARD_HEIGHT], u16 piece_in[BOARD_HEIGHT])
{
  start_color ();
  init_pair (1, COLOR_BLACK, COLOR_WHITE);
  init_pair (2, COLOR_BLACK, COLOR_BLACK);

  for (i16 j = 0; j < BOARD_HEIGHT - 1; j++)
    {
      u16 board = board_in[j];
      u16 piece = piece_in[j];
      for (i16 i = 15; i >= 0; i--)
        {
          u8 bit1 = (board >> i) & 1;
          u8 bit2 = (piece >> i) & 1;
          u8 bit = bit1 | bit2;

          if (bit)
            attron (COLOR_PAIR (1));
          else
            attron (COLOR_PAIR (2));

          mvaddch (j, 15 - i, ' ');

          attroff (COLOR_PAIR (1));
          attroff (COLOR_PAIR (2));
        }
    }

  refresh ();
}

bool
test_interference (u16 board_in[BOARD_HEIGHT],
                   u16 piece_in[NUM_ROT][BOARD_HEIGHT], i16 selected_rot)
{
  for (i16 i = 0; i < BOARD_HEIGHT; i++)
    {
      if (board_in[i] & piece_in[selected_rot][i])
        {
          return true;
        }
    }

  return false;
}

/* Externally dependent */
i16
main (void)
{
  srand (time (NULL));
  u16 board[BOARD_HEIGHT] = { 0 };
  u16 piece[NUM_ROT][BOARD_HEIGHT] = { 0 };
  i16 selected_rot = 0;
  init_game_board (board);
  init_piece_board (piece, rand () % 7);
  struct timespec last_fall;
  clock_gettime (CLOCK_MONOTONIC, &last_fall);

  initscr ();
  noecho ();
  cbreak ();
  curs_set (0);
  keypad (stdscr, TRUE);
  nodelay (stdscr, TRUE);

  i16 ch;
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
          fall (board, piece, selected_rot);
          continue;
          break;
        case ' ':
          while (fall (board, piece, selected_rot))
            ;
          add_piece_to_board (board, piece, selected_rot);
          clear_rows (board);
          init_piece_board (piece, rand () % 7);
          continue;
          break;
        }

      if (elapsed >= 0.25)
        {
          last_fall = now;
          if (!fall (board, piece, selected_rot))
            {
              add_piece_to_board (board, piece, selected_rot);
              clear_rows (board);
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
      print_bitboard (board, piece[selected_rot]);

      usleep (50000);
    }

  endwin ();
  return 0;
}