#ifndef UI_H
#define UI_H

#include <ncurses.h>

extern WINDOW *sketch_win, *board_win, *log_win, *serial_win, *status_win;
void init_ui();

void end_ui();
/* void draw_current_page(void); */

/* void main_menu(); */

#endif
