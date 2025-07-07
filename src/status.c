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
static const char *page_names[] = {"Dashboard", "Boards", "Libraries", "Cores", "Examples"};
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

    // Set the background for the whole bar using our standard color pair
    wbkgd(win, COLOR_PAIR(CP_STATUS_BAR));
    werase(win);

    // --- 1. Draw Page Indicators (Left Aligned) ---
    int current_pos = 1;
    for (int i = 0; i < total; i++) {
        // Use a different color pair for the highlighted tab
        if (i == app_state.current_page) {
            wattron(win, COLOR_PAIR(CP_HIGHLIGHT_TAB));
        }

        mvwprintw(win, 0, current_pos, " F%d:%s ", i + 1, page_names[i]);

        if (i == app_state.current_page) {
            wattroff(win, COLOR_PAIR(CP_HIGHLIGHT_TAB));
        }
        
        current_pos += strlen(page_names[i]) + 6;
    }

    // --- 2. Draw Status Indicators (Right Aligned) ---
    char right_status[128];
    if (is_loading) {
        snprintf(right_status, sizeof(right_status), "Working... %c", spinner[loading_idx]);
    } else {
        const char *board_status_str = (board_count > 0) ? "Connected" : "No Board";
        const char *focus_str = panel_names[app_state.focus_panel];
        snprintf(right_status, sizeof(right_status), "Board: %s | Focus: %s (TAB)", board_status_str, focus_str);
    }
    
    // The text will be drawn with the window's default color pair (CP_STANDARD)
    mvwprintw(win, 0, max_x - strlen(right_status) - 1, "%s", right_status);

    wnoutrefresh(win);
}


/* void draw_status(WINDOW *win){ */
/*     int maxy, maxx; */
/*     getmaxyx(win, maxy, maxx); */
/*     (void)maxy; */

/*     wbkgd(win, A_REVERSE); */
/*     werase(win); */

/*     int curr = 1; */
/*     for(int i =0; i< total; i++){ */
/*         if(i == app_state.current_page) wattron(win, A_REVERSE); */
/*         mvwprintw(win, 0, curr, " F%d:%s", i+1, page_name[i]); */
/*         if(i == app_state.current_page) wattroff(win, A_REVERSE); */
/*         curr += strlen(page_name[i]) + 5; */
/*     } */

/*     char right_status[128]; */


/*     if(is_loading){ */
/*         snprintf(right_status, sizeof(right_status), "Working... %c", spinner[loading_idx]); */
/*     }else{ */
/*         const char *board_status = (board_count > 0)? "Connected" : "No Board"; */
/*         const char *focus_str = panel_name[app_state.focus_panel]; */
/*         snprintf(right_status, sizeof(right_status), "Board: %s | Focus: %s [TAB]", board_status, focus_str); */
/*      } */

/*     mvwprintw(win, 0, maxx - strlen(right_status) -1, "%s", right_status); */

/*     wnoutrefresh(win); */
/* } */
