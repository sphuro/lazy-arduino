#ifndef SERIAL_H
#define SERIAL_H

#include "panel.h"
#include <ncurses.h>
#include <stdbool.h>

void start_serial_monitor(const char *port);
void stop_serial_monitor(void);
void draw_serial_panel(Panel *self, bool has_focus);
void update_serial(void);

#endif // SERIAL_H
