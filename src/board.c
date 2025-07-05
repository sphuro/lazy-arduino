#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "board.h"
#include "ui.h"

Board connected_boards[MAX_BOARDS];
int board_count = 0;


int get_boards(Board boards[], int max) {
    FILE *fp = popen("arduino-cli board list --format json", "r");
    if (!fp) return -1;

    char buff[8192];
    fread(buff, 1, sizeof(buff), fp);
    pclose(fp);

    int count = 0;
    char *ptr = buff;

    while ((ptr = strstr(ptr, "\"address\"")) && count < max) {
        char *addr_start = strchr(ptr, ':');
        if (!addr_start) break;
        addr_start = strchr(addr_start, '"') + 1;
        char *addr_end = strchr(addr_start, '"');
        strncpy(boards[count].port, addr_start, addr_end - addr_start);
        boards[count].port[addr_end - addr_start] = '\0';

        char *label_ptr = strstr(ptr, "\"label\"");
        if (label_ptr) {
            char *label_start = strchr(label_ptr, ':');
            label_start = strchr(label_start, '"') + 1;
            char *label_end = strchr(label_start, '"');
            strncpy(boards[count].boardName, label_start, label_end - label_start);
            boards[count].boardName[label_end - label_start] = '\0';
            ptr = label_end;  
        } else {
            strcpy(boards[count].boardName, "Unknown Board");
            ptr = addr_end;  
        }

        count++;
    }

    return count;
}

void draw_boards_panel(WINDOW *win, bool has_focus) {
    werase(win);
    /* int border_color = has_focus ? CP_HIGHLIGHT_BORDER : CP_STANDARD; */
    int border_color = CP_HIGHLIGHT_BORDER;
    if(has_focus) wattron(win, COLOR_PAIR(border_color));
    box(win, 0, 0);
   if(has_focus) wattroff(win, COLOR_PAIR(border_color));

    wattron(win, COLOR_PAIR(CP_STANDARD));
    mvwprintw(win, 0, 2, " Boards ");
    if (board_count == 0) {
        mvwprintw(win, 1, 2, "No boards detected");
    } else {
        for (int i = 0; i < board_count; i++) {
            mvwprintw(win, i + 1, 2, "%s (%s)", connected_boards[i].boardName, connected_boards[i].port);
        }
    }
    wattroff(win, COLOR_PAIR(CP_STANDARD));
    wnoutrefresh(win);
}



/* void draw_boards_panel(WINDOW *win){ */
/*     box(win, 0, 0); */
/*     mvwprintw(win, 0, 2, " Boards "); */
/*     if(board_count ==0 ) { */
/*         mvwprintw(win, 1,2, "No board detected"); */
/*     } else { */
/*         for(int i = 0; i< board_count; i++){ */
/*             mvwprintw(win, i+1, 2, "%s (%s)", connected_boards[i].boardName, connected_boards[i].port); */
/*         } */
/*     } */
/*     wnoutrefresh(win); */
/* } */
