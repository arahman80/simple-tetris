#include "common_includes.h"

void test_init_game_board() {
    uint16_t board[21];
    init_game_board(board);

    int passes = 0, fails = 0;
    for (int i = 0; i < 20; i++) {
        ASSERT_TRUE(board[i] == BOARD_WITH_WALLS, "Row should be initialized with walls");
    }
    ASSERT_TRUE(board[20] == 0xFFFF, "Bottom row should be solid");
    printf("init_game_board: %d passed, %d failed\n\n", passes, fails);
}