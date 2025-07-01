#include <string.h>
#include <ncurses.h>
#include "status.h"

static char status_msg[128] = "Ready. ";

void update_status(const char *message){
    strncpy(status_msg, message, sizeof(status_msg));
}

void draw_status(WINDOW *win){
    werase(win);
    mvwprintw(win, 0, 1, "%s", status_msg);
    wrefresh(win);
}
