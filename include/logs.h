#ifndef LOGS_H
#define LOGS_H

#include "panel.h"
#include <ncurses.h>
#include <stdbool.h>

#define MAX_LOG_LINE 20
#define MAX_LOG_LENGTH 256

void add_log(const char *msg);
void clear_logs(void);
void draw_logs_panel(Panel *self, bool has_focus);

#endif // LOGS_H
