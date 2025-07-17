#include "serial.h"
#include "ui.h"
#include <ncurses.h>

void start_serial_monitor(const char *port) {
    // TODO: open serial port using termios
    (void)port;
}

void stop_serial_monitor(void) {
    // TODO: close serial port
}

void update_serial(void) {
    // TODO: read and store lines
}

void draw_serial_panel(Panel *self, bool has_focus) {
    werase(self->win);
    int border_color = has_focus ? CP_HIGHLIGHT_BORDER : CP_STANDARD;
    wattron(self->win, COLOR_PAIR(border_color));
    box(self->win, 0, 0);
    wattroff(self->win, COLOR_PAIR(border_color));

    wattron(self->win, COLOR_PAIR(CP_STANDARD));
    mvwprintw(self->win, 0, 2, " Serial Monitor ");
    mvwprintw(self->win, 1, 2, "Waiting for data...");
    wattroff(self->win, COLOR_PAIR(CP_STANDARD));
    wnoutrefresh(self->win);
}
