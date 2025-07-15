#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_FILE_NAME ".lazyduino/config.ini"

extern char config_path[256];
extern char last_used_board[64];
extern char last_sketch_path[256];

void init_config_path(void);
void load_config(void);
void save_config(void);

#endif // CONFIG_H:
