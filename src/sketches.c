#include "sketches.h"
#include "ui.h"
#include "arduino.h"
#include "board.h"
#include "logs.h"
#include <dirent.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char sketches[MAX_SKETCHES][SKETCH_NAME_LEN];
int sketch_count = 0;
int selected_sketch = 0;

void load_sketches(const char *path) {
    DIR *d = opendir(path);
    if (!d) {
        perror("Error opening sketches directory");
        return;
    }

    // Clear existing sketch list
    sketch_count = 0;
    memset(sketches, 0, sizeof(sketches));

    struct dirent *dir;
    while ((dir = readdir(d)) != NULL && sketch_count < MAX_SKETCHES) {
        if (strstr(dir->d_name, ".ino")) {
            strncpy(sketches[sketch_count], dir->d_name, SKETCH_NAME_LEN - 1);
            sketches[sketch_count][SKETCH_NAME_LEN - 1] = '\0';
            sketch_count++;
        }
    }
    closedir(d);
}

void open_in_editor(const char *filename) {
    endwin(); // Temporarily leave ncurses mode
    
    const char *editor = getenv("EDITOR");
    if (!editor) editor = "vim"; // Sensible default
    
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "%s %s", editor, filename);
    
    system(cmd); // Run the editor
    
    // Restore ncurses mode
    initscr();
    refresh();
}

void handle_sketches_input(Panel *self, int key) {
    (void)self;
    switch (key) {
        case KEY_UP:
        case 'k':
            if (selected_sketch > 0)
                selected_sketch--;
            break;
        case KEY_DOWN:
        case 'j':
            if (selected_sketch < sketch_count - 1)
                selected_sketch++;
            break;
        case '\n': // Enter key
            if (sketch_count > 0)
                open_in_editor(sketches[selected_sketch]);
            break;
        case 'c': // Compile
            if (sketch_count > 0)
                compile_sketch(sketches[selected_sketch]);
            break;
        case 'u': // Upload
            if (sketch_count > 0) {
                if (board_count > 0) {
                    upload_sketch(sketches[selected_sketch], connected_boards[0].port);
                } else {
                    add_log("Error: No board connected for upload.");
                }
            }
            break;
    }
}

void draw_sketches_panel(Panel *self, bool has_focus) {
    werase(self->win);
    int border_color = has_focus ? CP_HIGHLIGHT_BORDER : CP_STANDARD;
    wattron(self->win, COLOR_PAIR(border_color));
    box(self->win, 0, 0);
    wattroff(self->win, COLOR_PAIR(border_color));

    wattron(self->win, COLOR_PAIR(CP_STANDARD));
    mvwprintw(self->win, 0, 2, " Sketches (c: compile, u: upload) ");
    wattroff(self->win, COLOR_PAIR(CP_STANDARD));

    for (int i = 0; i < sketch_count; i++) {
        if (i == selected_sketch) {
            wattron(self->win, has_focus ? (COLOR_PAIR(CP_HIGHLIGHT_TAB) | A_BOLD) : A_REVERSE);
        } else {
            wattron(self->win, COLOR_PAIR(CP_STANDARD));
        }
        mvwprintw(self->win, i + 1, 2, "%s", sketches[i]);
        wattroff(self->win, has_focus ? (COLOR_PAIR(CP_HIGHLIGHT_TAB) | A_BOLD) : A_REVERSE);
    }
    wnoutrefresh(self->win);
}
