#include <ncurses.h>
#include "serial.h"
#include "ui.h"

void start_serial_monitor(const char *port){
    // TODO: open serial port using terminos
}

void stop_serial_monitor(void){
    // TODO: close serial port
}

void update_serial(void){
    // TODO:read and store lines
}

void draw_serial(WINDOW *win, bool has_focus) {
    werase(win);
    int border_color = has_focus ? CP_HIGHLIGHT_BORDER : CP_STANDARD;
    wattron(win, COLOR_PAIR(border_color));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(border_color));

    wattron(win, COLOR_PAIR(CP_STANDARD));
    mvwprintw(win, 0, 2, " Serial Monitor ");
    mvwprintw(win, 1, 2, "Waiting for data...");
    wattroff(win, COLOR_PAIR(CP_STANDARD));
    wnoutrefresh(win);
}

/* void draw_serial(WINDOW *win){ */
/*     box(win, 0, 0); */
/*     mvwprintw(win, 0, 2, " Serial Monitor "); */
/*     mvwprintw(win, 1, 2, "Waiting for data..."); */
/*     wnoutrefresh(win); */
/* } */
