#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_PATH "~/.lazyduino/config.ini"
char config_path[256];
const char *home_dir = getenv("HOME");
if (home_dir) {
    snprintf(config_path, sizeof(config_path), "%s/.lazyduino/config.ini", home_dir);
} else {
	
}

void load_config(void);
void save_config(void);

extern char last_used_board[64];
extern char last_sketch_path[256];


#endif
