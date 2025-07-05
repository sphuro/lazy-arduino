#ifndef SKETCH_H
#include <ncurses.h>
#include <stdbool.h>
#define SKETCH_H


#define MAX_SKETCHES 32
#define SKETCH_NAME_LEN 128

extern char sketches[MAX_SKETCHES][SKETCH_NAME_LEN];
extern int selected_sketch;

void load_sketches(const char *path);
void draw_sketches(WINDOW *win, bool has_focus);
void open_in_editor(const char *filename);
void handle_sketch(int key);

#endif
