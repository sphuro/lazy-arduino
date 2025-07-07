#include "ui.h"
#include "board.h"
#include "logs.h"
#include "serial.h"
#include "sketches.h"
#include "status.h"
#include <ncurses.h>

WINDOW *sketch_win, *board_win, *log_win, *serial_win, *status_win;

void init_ui() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);

  if (has_colors() == TRUE) {
    start_color();
    use_default_colors();
    // Define our color pairs
    // Pair 1: Standard UI (White text on Blue background)
    /* init_pair(CP_STANDARD, COLOR_WHITE, COLOR_BLUE); */
    init_pair(CP_STANDARD, COLOR_WHITE, -1);
    // Pair 2: Highlighted Panel Border (Cyan text on Blue background)
    init_pair(CP_HIGHLIGHT_BORDER, COLOR_CYAN, -1);
    // Pair 3: Highlighted Status Tab (White text on Black background)
    init_pair(CP_HIGHLIGHT_TAB, COLOR_WHITE, COLOR_BLACK);
    init_pair(CP_STATUS_BAR, COLOR_BLACK, COLOR_WHITE);
  }

  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  int mid_x = max_x / 2;
  int top_half = max_y * 0.5;
  int log_height = max_y * 0.2;
  int serial_height = max_y * 0.2;

  sketch_win = newwin(top_half, mid_x, 0, 0);
  board_win = newwin(top_half, max_x - mid_x, 0, mid_x);
  log_win = newwin(log_height, max_x, top_half, 0);
  serial_win = newwin(serial_height, max_x, top_half + log_height, 0);
  status_win = newwin(1, max_x, max_y - 1, 0);

  refresh();
}

void end_ui() {
  delwin(sketch_win);
  delwin(board_win);
  delwin(log_win);
  delwin(serial_win);
  delwin(status_win);
  endwin();
}

/* #include <ncurses.h> */
/* #include "arduino.h" */

/* void init_ui(){ */
/* 	initscr(); */
/* 	noecho(); */
/* 	cbreak(); */
/* 	keypad(stdscr, TRUE); */
/* 	curs_set(0); */
/* 	refresh(); */
/* } */

/* void end_ui(){ */
/* 	endwin(); */
/* } */

/* void main_menu(){ */
/* 	const char *options[] = { */
/* 		"1. List Connected Boards", */
/* 		"2. Compile Sketch", */
/* 		"3. Upload Sketch", */
/* 		"4. Exit" */
/* 	}; */
/* 	int choice =0, ch; */

/* 	while (1) { */
/* 		clear(); */
/* 		mvprintw(0, 0, "Lazy Arduino IDE"); */
/* 		for (int i =0; i <4 ; i++) { */
/* 			if(i == choice)	attron(A_REVERSE); */
/* 			mvprintw(i+2, 2, options[i]); */
/* 			attroff(A_REVERSE); */
/* 		} */

/* 		ch = getch(); */
/*         switch (ch) { */
/*             case KEY_UP:    choice = (choice - 1 + 4) % 4; break; */
/*             case 'k':    choice = (choice - 1 + 4) % 4; break; */
/*             case KEY_DOWN:  choice = (choice + 1) % 4; break; */
/*             case 'j':  choice = (choice + 1) % 4; break; */
/*             case '\n': */
/*                 if (choice == 0) */
/*                     list_boards(); */
/*                 else if (choice == 1) */
/*                     compile_sketch("example/example.ino"); */
/*                 else if (choice == 2) */
/*                     upload_sketch("example/example.ino", "/dev/ttyUSB0"); */
/*                 else if (choice == 3) */
/*                     return; */
/*                 break; */
/* 	    case 'q': return;break; */

/* 	} */
/* } */
/* } */

// ui.c
