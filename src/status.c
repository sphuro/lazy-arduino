#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include "status.h"
#include "state.h"
#include "board.h"
#include "pages.h"

bool is_loading = false;
static int loading_idx = 0;
static const char *page_name = {"Dashboard", "Boards", "Libraries", "Cores", "Examples"};
static const char *panel_name = {"Sketches", "Boards", "Logs", "Serial"};
static const char spinner[] = "|/-\\"

static char status_msg[128] = "Ready. ";

void start_loading(void){
    is_loading = true;
    loading_idx = 0;
}

void stop_loading(void){
    is_loading = false;
}

void tick_animation(void){
    if(!is_loading)return;
    loading_idx = (loading_idx +1) % (sizeof(spinner) -1);
}
void update_status(const char *message){
    strncpy(status_msg, message, sizeof(status_msg));
}

void draw_status(WINDOW *win){
    werase(win);
    mvwprintw(win, 0, 1, "%s", status_msg);
    wnoutrefresh(win);
}
