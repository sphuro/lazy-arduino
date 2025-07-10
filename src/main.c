#include "arduino.h"
#include "board.h"
#include "pages.h"
#include "sketches.h"
#include "state.h"
#include "ui.h"
#include <ncurses.h>
#include <string.h>
#include "color_picker.h"

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

    app_state.current_page = dashboard;
    app_state.focus_panel = focus_sketch;
    app_state.mode = mode_normal;

    load_sketches(".");
    board_count = get_boards(connected_boards, MAX_BOARDS);

    draw_curr_page();
    int ch;
    while ((ch = getch())) {

        if (app_state.current_page == color_picker) {
            handle_color_picker_input(ch);
        } else if (app_state.mode == mode_command) {
            int len = strlen(app_state.command_buffer);
            switch (ch) {
            case '\n':
                process_cmd(app_state.command_buffer);
                app_state.mode = mode_normal;
                app_state.command_buffer[0] = '\0';
                curs_set(0);
                refresh();
        draw_curr_page();
        draw_command_bar();
                continue; 
                break;
            case 27:
                app_state.mode = mode_normal;
                app_state.command_buffer[0] = '\0';
                curs_set(0);
                break;
            case KEY_BACKSPACE:
            case 127:
            case 8:
                if (len > 1) {
                    app_state.command_buffer[len - 1] = '\0';
                } else {
                    app_state.mode = mode_normal;
                }
                break;
            default:
                if (ch >= 32 && ch <= 126 &&
                    len < sizeof(app_state.command_buffer) - 1) {
                    app_state.command_buffer[len] = ch;
                    app_state.command_buffer[len + 1] = '\0';
                }
                break;
            }
        } else if (app_state.mode == mode_normal) {
            if (app_state.focus_panel == focus_sketch) {
                        handle_sketch(ch);
                }
            switch (ch) {
            case KEY_RESIZE:
                resize_w();
                break;
            case ':':
                app_state.mode = mode_command;
                strcpy(app_state.command_buffer, ":");
                curs_set(1);
                break;
            case KEY_F(1): app_state.current_page = dashboard; break;
            case KEY_F(2): app_state.current_page = boards; break;
            case KEY_F(3): app_state.current_page = libraries; break;
            case KEY_F(4): app_state.current_page = cores; break;
            case KEY_F(5): app_state.current_page = examples; break;
            case '\t':
                app_state.focus_panel = (focuspanel)((app_state.focus_panel + 1) % 4);
                break;
            case 'q':
            case 27: 
                end_ui();
                return 0;
            }
        }

        draw_curr_page();
        draw_command_bar();
        doupdate();
    }

    end_ui();
    return 0;
}

