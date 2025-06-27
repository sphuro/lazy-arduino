#ifndef STATUS_H
#define STATUS_H

#include <ncurses.h>

void update_status(const char *message);
void draw_status(WINDOW *win);

#endif
