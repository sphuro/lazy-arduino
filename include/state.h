#ifndef STATE_H
#define STATE_H

#include "pages.h"

typedef enum { mode_normal, mode_command } appmode;

typedef enum { focus_sketch, focus_board, focus_log, focus_serial } focuspanel;

typedef struct {
  focuspanel focus_panel;
  pagetype current_page;
  appmode mode;
  char command_buffer[256];
} appstate;

extern appstate app_state;

#endif
