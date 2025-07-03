#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "sketches.h"

char sketches[MAX_SKETCHES][SKETCH_NAME_LEN];
int selected_sketch = 0;

void load_sketches(const char *path){
	// data here
	strncpy(sketches[0], "blink.ino", SKETCH_NAME_LEN);
	strncpy(sketches[1], "servo.ino", SKETCH_NAME_LEN);
	
	DIR *d;
	struct dirent *dir;
	d = opendir(path);
	int i = 0;
	if(d){
		while ((dir = readdir(d)) != NULL) {
			/* printf("%s\n", ); */	
			strncpy(sketches[i], dir->d_name, SKETCH_NAME_LEN);
			i++;
		}
		closedir(d);
	}
	else{
		perror("Error opening sketches");
	}

}


void draw_sketches(WINDOW *win){
	box(win, 0, 0);
	mvwprintw(win, 0, 2, " Sketches ");
	for (int i  = 0; i< MAX_SKETCHES && sketches[i][0]; i++) {
		if(i== selected_sketch)wattron(win, A_REVERSE);
		mvwprintw(win, i+1, 2, "%s", sketches[i]);
		if(i == selected_sketch) wattroff(win, A_REVERSE);
	}
	wnoutrefresh(win);
}

void handle_sketch(int key) {
    switch (key) {
        case KEY_UP:
        case 'k':
            if (selected_sketch > 0)
                selected_sketch--;
            break;
        case KEY_DOWN:
        case 'j':
            if (selected_sketch < MAX_SKETCHES - 1 && sketches[selected_sketch + 1][0])
                selected_sketch++;
            break;
        case '\n':
            open_in_editor(sketches[selected_sketch]);
            break;
    }
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

