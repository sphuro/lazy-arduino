#include "color_picker.h"
#include "colors.h"
#include "state.h"
#include "ui.h"

static int selected_x = 0;
static int selected_y = 0;

void draw_color_picker_page(void) {
    erase();
    mvprintw(1, 2, "Select a base color with arrow keys. Press Enter to confirm.");

    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            int color_index = 16 + (y * 16 + x); // Skips the first 16 basic colors
            if (color_index > 255) continue;

            init_pair(color_index, color_index, color_index);

            /* if (x == selected_x && y == selected_y) { */
            /*     attron(A_REVERSE); */
            /* } */

            /* attron(COLOR_PAIR(color_index)); */
            /* mvprintw(y + 3, x * 3 + 2, "  "); // Draw two spaces for a wider block */
            /* attroff(COLOR_PAIR(color_index)); */

            /* if (x == selected_x && y == selected_y) { */
            /*     attroff(A_REVERSE); */
            /* } */
                        attron(COLOR_PAIR(color_index));

            // Use a different character to highlight the selection
            if (x == selected_x && y == selected_y) {
                mvprintw(y + 3, x * 3 + 2, "<>");
            } else {
                mvprintw(y + 3, x * 3 + 2, "  ");
            }

            attroff(COLOR_PAIR(color_index));
        }
    }
    refresh();
}

void handle_color_picker_input(int key) {
    switch (key) {
        case KEY_UP:    if (selected_y > 0) selected_y--; break;
        case KEY_DOWN:  if (selected_y < 15) selected_y++; break;
        case KEY_LEFT:  if (selected_x > 0) selected_x--; break;
        case KEY_RIGHT: if (selected_x < 15) selected_x++; break;
        case '\n': // Enter key
            {
                int selected_color_index = 16 + (selected_y * 16 + selected_x);
                apply_theme(selected_color_index);
                // --- END FIX ---

                // Switch back to the dashboard
                app_state.current_page = dashboard;
            }
            break;
        case 'q': // Also allow quitting back to dashboard
        case 27:  // ESC key
            app_state.current_page = dashboard;
            break;
    }
}
