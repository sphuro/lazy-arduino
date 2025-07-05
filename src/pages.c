#include <ncurses.h>
#include "pages.h"
#include "sketches.h"
#include "board.h"
#include "logs.h"
#include "serial.h"
#include "status.h"
#include "ui.h"
#include "state.h"
pagetype current_page = dashboard;


void draw_dashboard() {
    werase(sketch_win);
    werase(board_win);
    werase(log_win);
    werase(serial_win);
    werase(status_win);

    /* draw_sketches(sketch_win); */
    /* draw_boards_panel(board_win); */
    /* draw_logs(log_win); */
    /* draw_serial(serial_win); */
    /* draw_status(status_win); */

    draw_sketches(sketch_win, app_state.focus_panel == focus_sketch);
    draw_boards_panel(board_win, app_state.focus_panel == focus_board);
    draw_logs(log_win, app_state.focus_panel == focus_log);
    draw_serial(serial_win, app_state.focus_panel == focus_serial);
    draw_status(status_win);

    doupdate();
    // Don't call refresh() unless using stdscr. Use wrefresh per window.
}


void draw_page(pagetype page) {
    /* clear(); */
    switch (page) {
        case dashboard:
            draw_dashboard();
            break;
        case boards:
            erase();
            mvprintw(1, 2, "[Boards Manager] Under construction");
            break;
        case libraries:
            erase();
            mvprintw(1, 2, "[Library Manager] Under construction");
            break;
        case cores:
            erase();
            mvprintw(1, 2, "[Cores Manager] Under construction");
            break;
        case examples:
            erase();
            mvprintw(1, 2, "[Examples Browser] Under construction");
            break;
        default:
            erase();
            mvprintw(1, 2, "[Unknown Page]");
    }
    refresh();
}

void draw_curr_page(void) {
    draw_page(app_state.current_page);
    draw_status(status_win);

    doupdate();
}


void switch_page(int delta) {
    app_state.current_page = (pagetype)((app_state.current_page + delta + total) % total);
}

