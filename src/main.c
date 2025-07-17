#include "board.h"
#include "command.h"
#include "pages.h"
#include "sketches.h"
#include "state.h"
#include "ui.h"
#include "logs.h"
#include <ncurses.h>
#include <string.h>
#include <stdbool.h>

void draw_command_bar() {
    werase(cmd_win);
    if (app_state.mode == mode_command) {
        mvwprintw(cmd_win, 0, 0, "%s", app_state.command_buffer);
        wmove(cmd_win, 0, strlen(app_state.command_buffer));
    }
    wnoutrefresh(cmd_win);
}


int main() {
    init_ui();

    app_state.current_idx = 0; // Dashboard
    app_state.focus_idx = 0;   // Sketches panel
    app_state.mode = mode_normal;

    load_sketches(".");
    board_count = get_boards(connected_boards, MAX_BOARDS);
    add_log("Welcome to lazy-arduino!");

    init_current_page();
    
    // Initial draw
    draw_current_page();
    draw_command_bar();
    doupdate();

    int ch;
    // Fixed event loop - draw first, then wait for input, then process
    while ((ch = getch()) != EOF) {
        // Process the input first
        if (app_state.mode == mode_command) {
            int len = strlen(app_state.command_buffer);
            switch (ch) {
                case '\n':
                    process_command(app_state.command_buffer);
                    app_state.mode = mode_normal;
                    app_state.command_buffer[0] = '\0';
                    curs_set(0);
                    break;
                case 27: // ESC
                    app_state.mode = mode_normal;
                    app_state.command_buffer[0] = '\0';
                    curs_set(0);
                    break;
                case KEY_BACKSPACE:
                case 127: // Common backspace chars
                case 8:
                    if (len > 1) { // Keep the leading ':'
                        app_state.command_buffer[len - 1] = '\0';
                    } else { // Buffer is only ":", so exit command mode
                        app_state.mode = mode_normal;
                        app_state.command_buffer[0] = '\0';
                        curs_set(0);
                    }
                    break;
                default:
                    if (ch >= 32 && ch <= 126 && len < sizeof(app_state.command_buffer) - 1) {
                        app_state.command_buffer[len] = ch;
                        app_state.command_buffer[len + 1] = '\0';
                    }
                    break;
            }
        } else if (app_state.mode == mode_normal) {
            switch (ch) {
                case ERR: // This happens on timeout, we can ignore it
                    break;
                case KEY_RESIZE:
                    resize_current_page();
                    break;
                case ':':
                    app_state.mode = mode_command;
                    strcpy(app_state.command_buffer, ":");
                    curs_set(1);
                    break;
                case KEY_F(1): switch_page(0); break;
                case KEY_F(2): switch_page(1); break;
                case KEY_F(3): switch_page(2); break;
                case KEY_F(4): switch_page(3); break;
                case KEY_F(5): switch_page(4); break;
                case 'q':
                    end_ui();
                    return 0;
                default:
                    handle_current_page_input(ch);
                    break;
            }
        }

        // Then draw the updated state
        draw_current_page();
        draw_command_bar();
        doupdate();
    }

    end_ui();
    return 0;
}
