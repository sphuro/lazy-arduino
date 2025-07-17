#include "logs.h"
#include "ui.h"
#include <ncurses.h>
#include <string.h>

static char log_lines[MAX_LOG_LINE][MAX_LOG_LENGTH];
static int log_count = 0;

void add_log(const char *msg) {
    if (log_count >= MAX_LOG_LINE) {
        // Shift all lines up by one to make room for the new one
        for (int i = 0; i < MAX_LOG_LINE - 1; i++) {
            strcpy(log_lines[i], log_lines[i + 1]);
        }
        log_count = MAX_LOG_LINE - 1;
    }
    
    // Safely copy the new message, ensuring null termination
    strncpy(log_lines[log_count], msg, MAX_LOG_LENGTH - 1);
    log_lines[log_count][MAX_LOG_LENGTH - 1] = '\0';
    log_count++;
}

void clear_logs(void) {
    log_count = 0;
    for (int i = 0; i < MAX_LOG_LINE; i++) {
        log_lines[i][0] = '\0';
    }
}

void draw_logs_panel(Panel *self, bool has_focus) {
    werase(self->win);
    int border_color = has_focus ? CP_HIGHLIGHT_BORDER : CP_STANDARD;
    wattron(self->win, COLOR_PAIR(border_color));
    box(self->win, 0, 0);
    wattroff(self->win, COLOR_PAIR(border_color));

    wattron(self->win, COLOR_PAIR(CP_STANDARD));
    mvwprintw(self->win, 0, 2, " Logs ");
    for (int i = 0; i < log_count; i++) {
        mvwprintw(self->win, i + 1, 2, "%s", log_lines[i]);
    }
    wattroff(self->win, COLOR_PAIR(CP_STANDARD));
    wnoutrefresh(self->win);
}
