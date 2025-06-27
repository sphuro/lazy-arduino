#ifndef STATE_H
#define STATE_H

#include "pages.h"

typedef struct{
	int focus_panel;
	Page_type current_page;
} appstate;

extern appstate app_state;

#endif
