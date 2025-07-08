#include "state.h"
#include "pages.h"

appstate app_state = {.focus_panel = focus_sketch,
                      .current_page = dashboard,
                      .mode = mode_normal,
                      .command_buffer = {0}};
