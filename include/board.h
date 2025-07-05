#ifndef BOARD_H
#include <ncurses.h>
#include <stdbool.h>
#define BOARD_H

#define BOARD_BUFFER 8192
#define MAX_BOARDS 16

typedef struct{
	char boardName[64];
	char port[64];
} Board;

extern Board connected_boards[MAX_BOARDS];
extern int board_count;

int get_boards(Board boards[], int max);
void refresh_board_list(void);
void draw_boards_panel(WINDOW *win, bool has_focus);

#endif
