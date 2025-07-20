#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>


char config_path[256];
char last_used_board[64] = "Unknown";
char last_sketch_path[256] = "";

char target_fqbn[128]= "esp32:esp32:esp32";
char target_port[64] = "/dev/ttyUSB0";
char target_baud[16] = "115200";

void ensure_config_dir_exists(const char* path) {
    char* sep = strrchr(path, '/');
    if (sep != NULL) {
        char dir[256];
        strncpy(dir, path, sep - path);
        dir[sep - path] = '\0';
        mkdir(dir, 0700);
    }
}

void init_config_path(void) {
    const char *home_dir = getenv("HOME");
    if (home_dir) {
        snprintf(config_path, sizeof(config_path), "%s/%s", home_dir, CONFIG_FILE_NAME);
    } else {
        strncpy(config_path, "config.ini", sizeof(config_path) - 1);
        config_path[sizeof(config_path) - 1] = '\0';
    }
    ensure_config_dir_exists(config_path);
}

void load_config(void) {
    init_config_path();
    FILE *f = fopen(config_path, "r");
    if (!f) {
        save_config();
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        sscanf(line, "TARGET_FQBN=%127[^\n]", target_fqbn);
        sscanf(line, "TARGET_PORT=%63[^\n]", target_port);
        sscanf(line, "TARGET_BAUD=%15[^\n]", target_baud);
    }
    fclose(f);
}

void save_config(void) {
    FILE *f = fopen(config_path, "w");
    if (!f) return;

    fprintf(f, "TARGET_FQBN=%s\n", target_fqbn);
    fprintf(f, "TARGET_PORT=%s\n", target_port);
    fprintf(f, "TARGET_BAUD=%s\n", target_baud);
    fclose(f);
}
