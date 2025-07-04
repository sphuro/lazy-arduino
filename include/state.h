#ifndef STATE_H
#define STATE_H

#include "pages.h"

typedef enum{
	focus_sketch,
	focus_board,
	focus_log,
	focus_serial
} focuspanel;

typedef struct{
	focuspanel focus_panel;
	pagetype current_page;
} appstate;

extern appstate app_state;

#endif
