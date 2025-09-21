#include "board_utils/board_utils.h"
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

/* Externally dependent */
void
print_bitboard (unsigned int board_in[21], unsigned int piece_in[21])
{
  for (int j = 0; j < 21; j++)
    {
      unsigned int board = board_in[j];
      unsigned int piece = piece_in[j];
      for (int i = 15; i >= 0; i--)
        {
          unsigned char bit1 = (board >> i) & 1;
          unsigned char bit2 = (piece >> i) & 1;
          unsigned char bit = bit1 | bit2;

          mvaddch (j, 15 - i, bit ? '#' : ' ');
        }
    }

  refresh ();
}

int
test_interference (unsigned int board_in[21], unsigned int piece_in[4][21],
                   int selected_rot)
{
  for (int i = 0; i < 21; i++)
    {
      if (board_in[i] & piece_in[selected_rot][i])
        {
          return 1;
        }
    }

  return 0;
}

/* Externally dependent */
int
main (void)
{
  unsigned int board[21] = { 0 };
  unsigned int piece[4][21] = { 0 };
  int selected_rot = 0;
  init_game_board (board);
  init_piece_board (piece, PIECE_I);
  struct timespec last_fall;
  clock_gettime (CLOCK_MONOTONIC, &last_fall);

  initscr ();
  noecho ();
  cbreak ();
  curs_set (0);
  keypad (stdscr, TRUE);
  nodelay (stdscr, TRUE);

  int ch;
  while ((ch = getch ()) != 'q')
    {
      struct timespec now;
      clock_gettime (CLOCK_MONOTONIC, &now);
      double elapsed = (now.tv_sec - last_fall.tv_sec)
                       + (now.tv_nsec - last_fall.tv_nsec) / 1e9;

      switch (ch)
        {
        case KEY_UP:
          if (!test_interference (board, piece, (selected_rot + 1) % 4))
            {
              selected_rot = (selected_rot + 1) % 4;
            }
          break;
        case KEY_DOWN:
          if (!test_interference (board, piece, (selected_rot - 1) % 4))
            {
              selected_rot = (selected_rot - 1) % 4;
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
          init_piece_board (piece, PIECE_I);
          continue;
          break;
        }

      if (elapsed >= 0.1)
        {
          last_fall = now;
          if (!fall (board, piece, selected_rot))
            {
              add_piece_to_board (board, piece, selected_rot);
              clear_rows (board);
              init_piece_board (piece, PIECE_I);
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