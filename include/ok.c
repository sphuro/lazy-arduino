#include <stdio.h>
#include "board.h"

int main() {
    Board boards[MAX_BOARDS];
    int count = get_boards(boards, MAX_BOARDS);

    if (count < 0) {
        fprintf(stderr, "Failed to retrieve board list.\n");
        return 1;
    }

    printf("Found %d board(s):\n", count);
    for (int i = 0; i < count; ++i) {
        printf("  [%d] %s (%s)\n", i + 1, boards[i].boardName, boards[i].port);
    }

    return 0;
}

