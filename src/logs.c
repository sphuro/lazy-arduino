#include <ncurses.h>
#include <string.h>
#include "logs.h"
#include "ui.h"

static char log_lines[MAX_LOG_LINE][MAX_LOG_LENGTH];
static int log_count = 0;

void add_log(const char *msg){
    if(log_count < MAX_LOG_LINE){
        strncpy(log_lines[log_count++], msg,MAX_LOG_LENGTH );
    }
}

void clear_logs(void){
    log_count =0;
}

void draw_logs(WINDOW *win, bool has_focus) {
    werase(win);
    int border_color = has_focus ? CP_HIGHLIGHT_BORDER : CP_STANDARD;
    wattron(win, COLOR_PAIR(border_color));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(border_color));

    wattron(win, COLOR_PAIR(CP_STANDARD));
    mvwprintw(win, 0, 2, " Logs ");
    for (int i = 0; i < log_count; i++) {
        mvwprintw(win, i + 1, 2, "%s", log_lines[i]);
    }
    wattroff(win, COLOR_PAIR(CP_STANDARD));
    wnoutrefresh(win);
}

/* void draw_logs(WINDOW *win){ */
/*     box(win, 0,0); */
/*     mvwprintw(win, 0, 2, " Logs "); */
/*     for(int i = 0; i <  log_count; i++){ */
/*         mvwprintw(win, i+1, 2, "%s", log_lines[i]); */
/*     } */
/*     wnoutrefresh(win); */
/* } */
