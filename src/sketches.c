#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sketches.h"

char sketches[MAX_SKETCHES][SKETCH_NAME_LEN];
int selected_sketch = 0;

void load_sketches(const char *path){
	// data here
	strncpy(sketches[0], "blink.ino", SKETCH_NAME_LEN);
	strncpy(sketches[1], "servo.ino", SKETCH_NAME_LEN);

}


void draw_sketches(WINDOW *win){
	box(win, 0, 0);
	mvwprintw(win, 0, 2, " Sketches ");
	for (int i  = 0; i< MAX_SKETCHES && sketches[i][0]; i++) {
		if(i== selected_sketch)wattron(win, A_REVERSE);
		mvwprintw(win, i+1, 2, "%s", sketches[i]);
		if(i == selected_sketch) wattroff(win, A_REVERSE);
	}
	wrefresh(win);
}


void open_in_editor(const char *filename){
	endwin();
	const char *editor = getenv("EDITOR");
	if(!editor) editor = "nano";
	char cmd[256];
	snprintf(cmd, sizeof(cmd), "%s %s", editor, filename);
	system(cmd);
	
	refresh();
}
void handle_sketch(int key){

}
