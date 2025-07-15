#include "color_picker.h"
#include "colors.h"
#include "state.h"
#include "ui.h"
#include "pages.h"
#include <ncurses.h>

static int selected_x = 0;
static int selected_y = 0;

void draw_color_picker_page(void) {
    mvprintw(1, 2, "Select a base color with arrow keys. Press Enter to apply or ESC to cancel.");

    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            int color_index = 16 + (y * 16 + x);
            if (color_index > 255) continue;

            // Initialize a pair for the color block itself
            init_pair(color_index, color_index, color_index);

            // 1. Always draw the background color block first
            attron(COLOR_PAIR(color_index));
            mvprintw(y + 3, x * 3 + 2, "  ");
            attroff(COLOR_PAIR(color_index));

            // 2. If this cell is selected, draw the highlight indicator on top
            if (x == selected_x && y == selected_y) {
                attron(COLOR_PAIR(CP_STANDARD) | A_BOLD); // Use standard text color for visibility
                mvprintw(y + 3, x * 3 + 2, "<>");
                attroff(COLOR_PAIR(CP_STANDARD) | A_BOLD);
            }
        }
    }
}

void handle_color_picker_input(int key) {
    draw_status_bar();
    switch (key) {
        case KEY_UP:    if (selected_y > 0) selected_y--; break;
        case KEY_DOWN:  if (selected_y < 15) selected_y++; break;
        case KEY_LEFT:  if (selected_x > 0) selected_x--; break;
        case KEY_RIGHT: if (selected_x < 15) selected_x++; break;
        case '\n': // Enter
            {
                int selected_color_index = 16 + (selected_y * 16 + selected_x);
                apply_theme(selected_color_index);
                switch_page(0); // Switch back to dashboard
            }
            break;
        case 'q':
        case 27: // ESC
            switch_page(0); // Switch back to dashboard
            break;
    }
}
