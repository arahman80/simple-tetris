#include <stdio.h>
#include "test.h"

void run_tests() {
    printf("Running unit tests...\n\n");

    test_init_game_board();
    test_clear_rows();

    printf("All tests done.\n");
}