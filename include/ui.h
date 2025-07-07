#ifndef UI_H
#define UI_H

#include <ncurses.h>

#define CP_STANDARD 1
#define CP_HIGHLIGHT_BORDER 2
#define CP_HIGHLIGHT_TAB 3
#define CP_STATUS_BAR 4

extern WINDOW *sketch_win, *board_win, *log_win, *serial_win, *status_win;
void init_ui();

void end_ui();
/* void draw_current_page(void); */

/* void main_menu(); */

#endif
