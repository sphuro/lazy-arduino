#include <ncurses.h>

#include "arduino.h"

void init_ui(){
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
}


void end_ui(){
	endwin();
}

void main_menu(){
	const char *options[] = {
		"1. List Connected Boards",
		"2. Compile Sketch",
		"3. Upload Sketch",
		"4. Exit"
	};
	int choice =0, ch;
	
	while (1) {
		clear();
		mvprintw(0, 0, "Lazy Arduino IDE");
		for (int i =0; i <4 ; i++) {
			if(i == choice)	attron(A_REVERSE);
			mvprintw(i+2, 2, options[i]);
			attroff(A_REVERSE);
		}

		ch = getch();
        switch (ch) {
            case KEY_UP:    choice = (choice - 1 + 4) % 4; break;
            case 'k':    choice = (choice - 1 + 4) % 4; break;
            case KEY_DOWN:  choice = (choice + 1) % 4; break;
            case 'j':  choice = (choice + 1) % 4; break;
            case '\n':
                if (choice == 0)
                    list_boards();
                else if (choice == 1)
                    compile_sketch("example/example.ino");
                else if (choice == 2)
                    upload_sketch("example/example.ino", "/dev/ttyUSB0");
                else if (choice == 3)
                    return;
                break;
	    case 'q': return;break;
	
	}
}
}
