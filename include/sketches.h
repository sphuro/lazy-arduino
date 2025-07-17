#ifndef SKETCHES_H
#define SKETCHES_H

#include <ncurses.h>
#include <stdbool.h>
#include "panel.h"

#define MAX_SKETCHES 32
#define SKETCH_NAME_LEN 128

extern char sketches[MAX_SKETCHES][SKETCH_NAME_LEN];
extern int sketch_count;
extern int selected_sketch;

void load_sketches(const char *path);
void open_in_editor(const char *filename);

void handle_sketches_input(Panel *self, int key);
void draw_sketches_panel(Panel *self, bool has_focus);

#endif // SKETCHES_H
