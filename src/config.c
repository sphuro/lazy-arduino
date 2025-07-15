#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char config_path[256];
char last_used_board[64] = "Unknown";
char last_sketch_path[256] = "";

void init_config_path(void) {
    const char *home_dir = getenv("HOME");
    if (home_dir) {
        snprintf(config_path, sizeof(config_path), "%s/%s", home_dir, CONFIG_FILE_NAME);
    } else {
        // Fallback for non-standard environments
        strncpy(config_path, "config.ini", sizeof(config_path) - 1);
        config_path[sizeof(config_path) - 1] = '\0';
    }
}

void load_config(void) {
    // TODO: Implement file reading to load configuration
    init_config_path();
}

void save_config(void) {
    // TODO: Implement file writing to save configuration
}
