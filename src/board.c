#include "board.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

Board connected_boards[MAX_BOARDS];
int board_count = 0;

// NOTE: This manual JSON parsing is fragile. A dedicated JSON library like cJSON is highly recommended.
int get_boards(Board boards[], int max) {
    FILE *fp = popen("arduino-cli board list --format json", "r");
    if (!fp) return -1;

    char buff[BOARD_BUFFER];
    size_t bytes_read = fread(buff, 1, sizeof(buff) - 1, fp);
    buff[bytes_read] = '\0'; // Ensure buffer is null-terminated
    pclose(fp);

    int count = 0;
    char *ptr = buff;

    while ((ptr = strstr(ptr, "\"address\"")) && count < max) {
        char *addr_start = strchr(ptr, ':');
        if (!addr_start) break;
        
        addr_start = strchr(addr_start, '"');
        if (!addr_start) break;
        addr_start++; // Move past the opening quote

        char *addr_end = strchr(addr_start, '"');
        if (!addr_end) break;
        
        size_t addr_len = addr_end - addr_start;
        if (addr_len < sizeof(boards[count].port)) {
            strncpy(boards[count].port, addr_start, addr_len);
            boards[count].port[addr_len] = '\0';
        }

        char *label_ptr = strstr(ptr, "\"label\"");
        if (label_ptr) {
            char *label_start = strchr(label_ptr, ':');
            if (!label_start) break;

            label_start = strchr(label_start, '"');
            if (!label_start) break;
            label_start++; // Move past the opening quote

            char *label_end = strchr(label_start, '"');
            if (!label_end) break;

            size_t label_len = label_end - label_start;
            if (label_len < sizeof(boards[count].boardName)) {
                strncpy(boards[count].boardName, label_start, label_len);
                boards[count].boardName[label_len] = '\0';
            }
            ptr = label_end;
        } else {
            strcpy(boards[count].boardName, "Unknown Board");
            ptr = addr_end;
        }

        count++;
    }

    return count;
}


void draw_boards_panel(Panel *self, bool has_focus) {
    werase(self->win);
    int border_color = has_focus ? CP_HIGHLIGHT_BORDER : CP_STANDARD;
    wattron(self->win, COLOR_PAIR(border_color));
    box(self->win, 0, 0);
    wattroff(self->win, COLOR_PAIR(border_color));

    wattron(self->win, COLOR_PAIR(CP_STANDARD));
    mvwprintw(self->win, 0, 2, " Boards ");
    if (board_count == 0) {
        mvwprintw(self->win, 1, 2, "No boards detected");
    } else {
        for (int i = 0; i < board_count; i++) {
            mvwprintw(self->win, i + 1, 2, "%s (%s)", connected_boards[i].boardName, connected_boards[i].port);
        }
    }
    wattroff(self->win, COLOR_PAIR(CP_STANDARD));
    wnoutrefresh(self->win);
}

/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <ncurses.h> */
/* #include <string.h> */
/* #include "board.h" */
/* #include "ui.h" */

/* Board connected_boards[MAX_BOARDS]; */
/* int board_count = 0; */


/* int get_boards(Board boards[], int max) { */
/*     FILE *fp = popen("arduino-cli board list --format json", "r"); */
/*     if (!fp) return -1; */

/*     char buff[8192]; */
/*     fread(buff, 1, sizeof(buff), fp); */
/*     pclose(fp); */

/*     int count = 0; */
/*     char *ptr = buff; */

/*     while ((ptr = strstr(ptr, "\"address\"")) && count < max) { */
/*         char *addr_start = strchr(ptr, ':'); */
/*         if (!addr_start) break; */
/*         addr_start = strchr(addr_start, '"') + 1; */
/*         char *addr_end = strchr(addr_start, '"'); */
/*         strncpy(boards[count].port, addr_start, addr_end - addr_start); */
/*         boards[count].port[addr_end - addr_start] = '\0'; */

/*         char *label_ptr = strstr(ptr, "\"label\""); */
/*         if (label_ptr) { */
/*             char *label_start = strchr(label_ptr, ':'); */
/*             label_start = strchr(label_start, '"') + 1; */
/*             char *label_end = strchr(label_start, '"'); */
/*             strncpy(boards[count].boardName, label_start, label_end - label_start); */
/*             boards[count].boardName[label_end - label_start] = '\0'; */
/*             ptr = label_end; */  
/*         } else { */
/*             strcpy(boards[count].boardName, "Unknown Board"); */
/*             ptr = addr_end; */  
/*         } */

/*         count++; */
/*     } */

/*     return count; */
/* } */

/* void draw_boards_panel(Panel *self, bool has_focus) { */
/*   werase(self->win); */
/*   int border_color = has_focus ? CP_HIGHLIGHT_BORDER : CP_STANDARD; */
/*   wattron(self->win, COLOR_PAIR(border_color)); */
/*   box(self->win, 0, 0); */
/*   wattroff(self->win, COLOR_PAIR(border_color)); */

/*   wattron(self->win, COLOR_PAIR(CP_STANDARD)); */
/*   mvwprintw(self->win, 0, 2, " Boards "); */
/*   if (board_count == 0) { */
/*     mvwprintw(self->win, 1, 2, "No boards detected"); */
/*   } else { */
/*     for (int i = 0; i < board_count; i++) { */
/*       mvwprintw(self->win, i + 1, 2, "%s (%s)", connected_boards[i].boardName, */
/*                 connected_boards[i].port); */
/*     } */
/*   } */
/*   wattroff(self->win, COLOR_PAIR(CP_STANDARD)); */
/*   wnoutrefresh(self->win); */
/* } */

