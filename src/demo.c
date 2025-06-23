// lazy_arduino_tui.c
// Basic 5-panel Arduino TUI with ncurses and external editor launch

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SKETCHES 5
const char *sketches[MAX_SKETCHES] = {"blink.ino", "servo.ino", "adc.ino", "wifi.ino", "temp.ino"};
int selected_sketch = 0;

WINDOW *sketches_win, *boards_win, *logs_win, *serial_win, *status_win;

void draw_windows() {
    int h, w;
    getmaxyx(stdscr, h, w);

    int half_w = w / 2;
    int top_h = h / 4;
    int log_h = h / 6;
    int serial_h = h - top_h - log_h - 1;

    sketches_win = newwin(top_h, half_w, 0, 0);
    boards_win   = newwin(top_h, w - half_w, 0, half_w);
    logs_win     = newwin(log_h, w, top_h, 0);
    serial_win   = newwin(serial_h, w, top_h + log_h, 0);
    status_win   = newwin(1, w, h - 1, 0);
}

void draw_content() {
    box(sketches_win, 0, 0);
    mvwprintw(sketches_win, 0, 2, " Sketches ");
    for (int i = 0; i < MAX_SKETCHES; i++) {
        if (i == selected_sketch) wattron(sketches_win, A_REVERSE);
        mvwprintw(sketches_win, i + 1, 2, "%s", sketches[i]);
        if (i == selected_sketch) wattroff(sketches_win, A_REVERSE);
    }

    box(boards_win, 0, 0);
    mvwprintw(boards_win, 0, 2, " Boards ");
    mvwprintw(boards_win, 1, 2, "Arduino Uno (/dev/ttyUSB0)");
    mvwprintw(boards_win, 2, 2, "ESP32 DevKit (/dev/ttyUSB1)");

    box(logs_win, 0, 0);
    mvwprintw(logs_win, 0, 2, " Compile/Upload Logs ");
    mvwprintw(logs_win, 1, 2, "No logs yet.");

    box(serial_win, 0, 0);
    mvwprintw(serial_win, 0, 2, " Serial Monitor ");
    mvwprintw(serial_win, 1, 2, "Waiting for data...");

    mvwprintw(status_win, 0, 1, "[Tab] Focus  [e] Edit  [c] Compile  [u] Upload  [q] Quit");

    wrefresh(sketches_win);
    wrefresh(boards_win);
    wrefresh(logs_win);
    wrefresh(serial_win);
    wrefresh(status_win);

    napms(1);
    doupdate();
}

void cleanup_windows() {
    delwin(sketches_win);
    delwin(boards_win);
    delwin(logs_win);
    delwin(serial_win);
    delwin(status_win);
}

void open_in_editor(const char *filename) {
    endwin();
    const char *editor = getenv("EDITOR");
    if (!editor) editor = "nano";

    char cmd[256];
    snprintf(cmd, sizeof(cmd), "%s %s", editor, filename);
    system(cmd);

    refresh();
}

int main() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    /* draw_windows(); */
    /* draw_content(); */

    refresh();
    flushinp();
    timeout(0);
    getch();
    timeout(-1);

    draw_windows();
    draw_content();
    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:
            case 'k':
                if (selected_sketch > 0) selected_sketch--;
                break;
            case KEY_DOWN:
            case 'j':
                if (selected_sketch < MAX_SKETCHES - 1) selected_sketch++;
                break;
            case 'e':
                open_in_editor(sketches[selected_sketch]);
                break;
            case 'r':
            case KEY_RESIZE:
                endwin();
                refresh();
                draw_windows();
                break;
        }
        draw_content();
    }

    cleanup_windows();
    endwin();
    return 0;
}

