#include "state.h"

appstate app_state = {
    .focus_idx = 0,
    .current_idx = 0,
    .mode = mode_normal,
    .command_buffer = {0}
};
