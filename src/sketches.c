#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "sketches.h"
#include "ui.h"

char sketches[MAX_SKETCHES][SKETCH_NAME_LEN];
int selected_sketch = 0;

void load_sketches(const char *path) {
    DIR *d = opendir(path);
    if (!d) {
        perror("Error opening sketches directory");
        return;
    }
    int i = 0;
    struct dirent *dir;
    while ((dir = readdir(d)) != NULL && i < MAX_SKETCHES) {
        if (strstr(dir->d_name, ".ino")) {
            strncpy(sketches[i], dir->d_name, SKETCH_NAME_LEN - 1);
            i++;
        }
    }
    closedir(d);
}


void handle_sketch(int key) {
    switch (key) {
        case KEY_UP:
        case 'k':
            if (selected_sketch > 0)
                selected_sketch--;
            break;
        case KEY_DOWN:
        case 'j':
            if (selected_sketch < MAX_SKETCHES - 1 && sketches[selected_sketch + 1][0])
                selected_sketch++;
            break;
        case '\n':
            open_in_editor(sketches[selected_sketch]);
            break;
    }
}


void open_in_editor(const char *filename) {
    endwin();
    const char *editor = getenv("EDITOR");
    if (!editor) editor = "nano"; // Default editor
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "%s %s", editor, filename);
    system(cmd);
    // After editor exits, we need to re-initialize the screen
    initscr();
    refresh();
}

void draw_sketches(WINDOW *win, bool has_focus) {
    werase(win);
    int border_color = has_focus ? CP_HIGHLIGHT_BORDER : CP_STANDARD;
    wattron(win, COLOR_PAIR(border_color));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(border_color));

    wattron(win, COLOR_PAIR(CP_STANDARD));
    mvwprintw(win, 0, 2, " Sketches ");
    wattroff(win, COLOR_PAIR(CP_STANDARD));

    for (int i = 0; i < MAX_SKETCHES && sketches[i][0]; i++) {
        // Highlight the selected line
        if (i == selected_sketch) {
            // Use the highlight color pair if the panel has focus
            wattron(win, has_focus ? COLOR_PAIR(CP_HIGHLIGHT_TAB) : A_REVERSE);
        } else {
            wattron(win, COLOR_PAIR(CP_STANDARD));
        }
        mvwprintw(win, i + 1, 2, "%s", sketches[i]);

        if (i == selected_sketch) {
            wattroff(win, has_focus ? COLOR_PAIR(CP_HIGHLIGHT_TAB) : A_REVERSE);
        } else {
            wattroff(win, COLOR_PAIR(CP_STANDARD));
        }
    }
    wnoutrefresh(win);
}


