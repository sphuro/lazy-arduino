#ifndef SERIAL_H
#define SERIAL_H

#include <ncurses.h>

void start_serial_monitor(const char *port);
void stop_serial_monitor(void);
void draw_serial(WINDOW *win);
void update_serial(void);

#endif
