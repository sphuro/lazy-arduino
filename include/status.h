#ifndef STATUS_H
#define STATUS_H

#include <ncurses.h>
#include <stdbool.h> 

extern bool is_loading;

void start_loading(void);
void stop_loading(void);
void load_anime(void);

void update_status(const char *message);
void draw_status(WINDOW *win);

#endif
