#include <ncurses.h>
#include "pages.h"
#include "sketches.h"
#include "board.h"
#include "logs.h"
#include "serial.h"
#include "status.h"

pagetype current_page = dashboard;

WINDOW *sketch_win, *board_win, *log_win, *serial_win, *status_win;

void draw_dashboard() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int mid_x = max_x / 2;
    int top_half = max_y * 0.5;
    int log_height = max_y * 0.2;
    int serial_height = max_y * 0.2;

    sketch_win = newwin(top_half, mid_x, 0, 0);
    board_win  = newwin(top_half, max_x - mid_x, 0, mid_x);
    log_win    = newwin(log_height, max_x, top_half, 0);
    serial_win = newwin(serial_height, max_x, top_half + log_height, 0);
    status_win = newwin(1, max_x, max_y - 1, 0);

    draw_sketches(sketch_win);
    draw_boards_panel(board_win);
    draw_logs(log_win);
    draw_serial(serial_win);
    draw_status(status_win);

    refresh();  // Force redraw to screen
}


void draw_page(pagetype page) {
    clear();
    switch (page) {
        case dashboard:
            draw_dashboard();
            break;
        case boards:
            mvprintw(1, 2, "[Boards Manager] Under construction");
            break;
        case libraries:
            mvprintw(1, 2, "[Library Manager] Under construction");
            break;
        case cores:
            mvprintw(1, 2, "[Cores Manager] Under construction");
            break;
        case examples:
            mvprintw(1, 2, "[Examples Browser] Under construction");
            break;
        default:
            mvprintw(1, 2, "[Unknown Page]");
    }
    refresh();
}

void draw_curr_page(void) {
    draw_page(current_page);
}


void switch_page(int delta) {
    current_page = (pagetype)((current_page + delta + total) % total);
}

