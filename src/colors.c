#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "colors.h"
#include "ui.h"

void hex_to_rgb(const char *hex_str, rgb_color *clr){
    long hex_val = strtol(hex_str, NULL, 16);
    clr->r = (hex_val >> 16) & 0xFF;
    clr->g = (hex_val >> 8) & 0xFF;
    clr->b = hex_val & 0xFF;
}

int rgb_to_256(rgb_color *color) {
    int r = (color->r * 5 / 255);
    int g = (color->g * 5 / 255);
    int b = (color->b * 5 / 255);
    
    return 16 + (r * 36) + (g * 6) + b;
}

void draw_color_picker(WINDOW *win) {

    rgb_color my_color;
    hex_to_rgb("89B4FA", &my_color);
    int color_index = rgb_to_256(&my_color);

    init_pair(100, color_index, color_index);

    wattron(win, COLOR_PAIR(100));
    mvwprintw(win, 5, 5, "      "); // Draw a block of color
    wattroff(win, COLOR_PAIR(100));

    wnoutrefresh(win);
}

void apply_theme_hex(const char *hex_str){
    rgb_color new_color;
    hex_to_rgb(hex_str, &new_color);
    int color_index = rgb_to_256(&new_color);
    apply_theme(color_index);
}
