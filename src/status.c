#include "status.h"
#include "state.h"
#include "board.h"
#include "pages.h"
#include "ui.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

bool is_loading = false;
static int loading_idx = 0;
static const char *panel_names[] = {"Sketches", "Boards", "Logs", "Serial"};
static const char spinner[] = "|/-\\";

void start_loading(void) {
    is_loading = true;
    loading_idx = 0;
}

void stop_loading(void) {
    is_loading = false;
}

void load_anime(void) {
    if (!is_loading) return;
    loading_idx = (loading_idx + 1) % (strlen(spinner));
}

void draw_status(WINDOW *win) {
    if (!win) return;

    int max_y, max_x;
    getmaxyx(win, max_y, max_x);
    (void)max_y;

    int status_color_pair = CP_STATUS_NORMAL;
    const char *mode_str = "NORMAL >>";
    if (app_state.mode == mode_command) {
        status_color_pair = CP_STATUS_COMMAND;
        mode_str = "COMMAND >>";
    }

    wbkgd(win, COLOR_PAIR(status_color_pair));
    werase(win);

    // Draw Mode
    wattron(win, COLOR_PAIR(status_color_pair) | A_BOLD);
    mvwprintw(win, 0, 1, "%s", mode_str);
    wattroff(win, COLOR_PAIR(status_color_pair) | A_BOLD);

    // Draw Page Tabs
    int current_pos = strlen(mode_str) + 2;
    for (int i = 0; i < NUM_PAGES; i++) {
        if (i == app_state.current_idx) {
            wattron(win, COLOR_PAIR(CP_HIGHLIGHT_TAB) | A_BOLD);
        } else {
            wattron(win, COLOR_PAIR(status_color_pair));
        }
        mvwprintw(win, 0, current_pos, " F%d:%s ", i + 1, page_registry[i].name);
        current_pos += strlen(page_registry[i].name) + 6;
    }

    // Draw Right-aligned Status
    char right_status[128];
    if (is_loading) {
        snprintf(right_status, sizeof(right_status), "Working... %c", spinner[loading_idx]);
    } else {
        const char *board_status_str = (board_count > 0) ? "Connected" : "No Board";
        if (app_state.current_idx == 0) { // If on Dashboard page
            const char *focus_str = (app_state.focus_idx < 4) ? panel_names[app_state.focus_idx] : "Unknown";
            snprintf(right_status, sizeof(right_status), "Board: %s | Focus: %s (TAB)", board_status_str, focus_str);
        } else {
            snprintf(right_status, sizeof(right_status), "Board: %s", board_status_str);
        }
    }

    mvwprintw(win, 0, max_x - strlen(right_status) - 1, "%s", right_status);
    wnoutrefresh(win);
}
