#ifndef SKETCH_H
#define SKETCH_H


#define MAX_SKETCHES 32
#define SKETCH_NAME 128

extern char sketches[MAX_SKETCHES][SKETCH_NAME];
extern int selected_sketch;

void load_sketch(const char *path);
void draw_sketches(WINDOW *win);
void open_in_editor(const char *filename);
void handle_sketch(int key);

#endif
