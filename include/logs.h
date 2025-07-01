#ifndef LOGS_H
#define LOGS_H

#include <ncurses.h>

#define MAX_LOG_LINE 100
#define MAX_LOG_LENGTH 256

void add_log(const char *msg);
void clear_logs(void);
void draw_logs(WINDOW *win);

#endif
