#include "ui.h"
#include "board.h"
#include "logs.h"
#include "serial.h"
#include "sketches.h"
#include "colors.h"
#include "status.h"
#include <ncurses.h>

WINDOW *sketch_win, *board_win, *log_win, *serial_win, *status_win, *cmd_win;

void apply_theme(int base_color_256) {
    // Redefine your core color pairs using the new base color
    init_pair(CP_STATUS_BAR, COLOR_BLACK, base_color_256);
    init_pair(CP_STATUS_NORMAL, COLOR_BLACK, base_color_256);
    init_pair(CP_HIGHLIGHT_BORDER, base_color_256, -1); // Use the color for borders

    // Example: Highlight tab with the new color
    init_pair(CP_HIGHLIGHT_TAB, base_color_256, -1);
}


void resize_w(){
  int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // --- Robust Layout Calculation ---
    // Reserve space for the bottom bars first.
    int main_area_height = max_y - 2;
    int status_bar_y = max_y - 2;
    int cmd_bar_y = max_y - 1;

    // Divide the main area proportionally.
    int mid_x = max_x / 2;
    int top_half_h = main_area_height / 2;
    int bottom_half_h = main_area_height - top_half_h;
    int log_h = bottom_half_h / 2;
    int serial_h = bottom_half_h - log_h;

    int bottom_start_y = top_half_h;
    int serial_start_y = bottom_start_y + log_h;

    // --- Clean Up Old Windows ---
    // This prevents memory leaks on resize.
    if (sketch_win) delwin(sketch_win);
    if (board_win) delwin(board_win);
    if (log_win) delwin(log_win);
    if (serial_win) delwin(serial_win);
    if (status_win) delwin(status_win);
    if (cmd_win) delwin(cmd_win);

    // --- Create New Windows with New Dimensions ---
    sketch_win = newwin(top_half_h, mid_x, 0, 0);
    board_win = newwin(top_half_h, max_x - mid_x, 0, mid_x);
    log_win = newwin(log_h, max_x, bottom_start_y, 0);
    serial_win = newwin(serial_h, max_x, serial_start_y, 0);
    status_win = newwin(1, max_x, status_bar_y, 0);
    cmd_win = newwin(1, max_x, cmd_bar_y, 0);

    // Mark the screen as needing a full redraw.
    clear();
    refresh();
}

void init_ui() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);

  if (has_colors() == TRUE) {
    start_color();
    use_default_colors();
    // Pair 1: Standard UI (White text on Blue background)
    /* init_pair(CP_STANDARD, COLOR_WHITE, COLOR_BLUE); */
    init_pair(CP_STANDARD, COLOR_WHITE, -1);
    // Pair 2: Highlighted Panel Border (Cyan text on Blue background)
    init_pair(CP_HIGHLIGHT_BORDER, COLOR_CYAN, -1);
    // Pair 3: Highlighted Status Tab (White text on Black background)
    /* init_pair(CP_HIGHLIGHT_TAB, COLOR_WHITE, COLOR_BLACK); */
    init_pair(CP_HIGHLIGHT_TAB, COLOR_CYAN, -1);
    init_pair(CP_STATUS_BAR, COLOR_BLACK, COLOR_CYAN);
    init_pair(CP_STATUS_NORMAL ,COLOR_BLACK, COLOR_CYAN);
    init_pair(CP_STATUS_COMMAND,COLOR_BLACK, COLOR_YELLOW);
  
    /* resize_w(); */
  }

  /* int max_y, max_x; */
  /* getmaxyx(stdscr, max_y, max_x); */

  /* int mid_x = max_x / 2; */
  /* int top_half = max_y * 0.5; */
  /* int log_height = max_y * 0.2; */
  /* int serial_height = max_y * 0.2; */

  /* sketch_win = newwin(top_half, mid_x, 0, 0); */
  /* board_win = newwin(top_half, max_x - mid_x, 0, mid_x); */
  /* log_win = newwin(log_height, max_x, top_half, 0); */
  /* serial_win = newwin(serial_height + 2, max_x, top_half + log_height, 0); */
  /* status_win = newwin(1, max_x, max_y - 2, 0); */
  /* cmd_win = newwin(1, max_x, max_y - 1, 0); */

  resize_w();

  refresh();
}

void end_ui() {
  delwin(sketch_win);
  delwin(board_win);
  delwin(log_win);
  delwin(serial_win);
  delwin(status_win);
  delwin(cmd_win);
  endwin();
}


