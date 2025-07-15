#ifndef PANEL_H
#define PANEL_H

#include <ncurses.h>
#include <stdbool.h>

// Forward declaration of the struct
struct Panel;

// Typedefs for function pointers
typedef void (*panel_drw)(struct Panel *self, bool has_focus);
typedef void (*panel_ipt)(struct Panel *self, int key);

// Struct definition
typedef struct Panel {
    const char *title;
    WINDOW *win;
    panel_drw draw_func;
    panel_ipt inp_func;
    void *data;
} Panel;

#endif // PANEL_H
