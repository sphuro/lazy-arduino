#ifndef STATUS_H
#define STATUS_H

#include <ncurses.h>
#include <stdbool.h>

void start_loading(void);
void stop_loading(void);
void load_anime(void);
void draw_status(WINDOW *win);

#endif // STATUS_Hh
