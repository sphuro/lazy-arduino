#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "status.h"
#include "state.h"
#include "board.h"
#include "pages.h"
#include "ui.h"

bool is_loading = false;
static int loading_idx = 0;
/* static const char *page_names[] = {"Dashboard", "Boards", "Libraries", "Cores", "Examples"}; */
static const char *page_names[] = {"Dashboard", "Boards", "Libraries", "Cores", "Examples", "Color Picker"};
static const char *panel_names[] = {"Sketches", "Boards", "Logs", "Serial"};
static const char spinner[] = "|/-\\";

static char status_msg[128] = "Ready. ";

void start_loading(void){
    is_loading = true;
    loading_idx = 0;
}

void stop_loading(void){
    is_loading = false;
}

void load_anime(void) {
    if (!is_loading) return;
    loading_idx = (loading_idx + 1) % (sizeof(spinner) - 1);
}


void draw_status(WINDOW *win) {
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);
    (void)max_y;

    int status_color_pair = CP_STATUS_NORMAL;
    const char* mode_str = "NORMAL >>";
    if (app_state.mode == mode_command) {
        status_color_pair = CP_STATUS_COMMAND;
        mode_str = "COMMAND >>";
    }

    wbkgd(win, COLOR_PAIR(status_color_pair));
    werase(win);

    wattron(win, COLOR_PAIR(status_color_pair));
    mvwprintw(win, 0, 1, "%s", mode_str);
    wattroff(win, COLOR_PAIR(status_color_pair));


    int current_pos = strlen(mode_str) + 2; 
    for (int i = 0; i < total; i++) {
        if (i == app_state.current_page) {
             wattron(win, COLOR_PAIR(CP_HIGHLIGHT_TAB) | A_BOLD);
        } else {
             wattron(win, COLOR_PAIR(status_color_pair));
        }
        mvwprintw(win, 0, current_pos, " F%d:%s ", i + 1, page_names[i]);
        current_pos += strlen(page_names[i]) + 6;
    }
    char right_status[128];
    if (is_loading) {
        snprintf(right_status, sizeof(right_status), "Working... %c", spinner[loading_idx]);
    } else {
        const char *board_status_str = (board_count > 0) ? "Connected" : "No Board";
        const char *focus_str = panel_names[app_state.focus_panel];
        snprintf(right_status, sizeof(right_status), "Board: %s | Focus: %s (TAB)", board_status_str, focus_str);
    }
    
    mvwprintw(win, 0, max_x - strlen(right_status) - 1, "%s", right_status);

    wnoutrefresh(win);

}

