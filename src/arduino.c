#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "board.h"
#include "status.h"
#include "ui.h"

void run_command(const char *cmd){
	FILE *fp = popen(cmd, "r");
	if(!fp){
		mvprintw(10, 0, "Failed to run command");
		return;
	}

	clear();
	mvprintw(0, 0, "Output: [%s]", cmd);

	start_loading();
	char buffer[256];
	int line =2;
	nodelay(stdscr, TRUE);
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		mvprintw(line++, 2, "%s", buffer);
		refresh();
		load_anime();
		draw_status(status_win);	
		doupdate();
		/* namps(100); */
	}
	pclose(fp);

	stop_loading();
	draw_status(status_win);
	doupdate();
	mvprintw(line+1, 2, "Press any key to return ... ");
	getch();
}

void list_boards() {
    clear();
    mvprintw(0, 0, "Connected Boards:");

    Board boards[MAX_BOARDS];
    int count = get_boards(boards, MAX_BOARDS);

    if (count <= 0) {
        mvprintw(2, 2, "No boards found.");
    } else {
        for (int i = 0; i < count; ++i) {
            mvprintw(i + 2, 2, "[%d] %s (%s)", i + 1, boards[i].boardName, boards[i].port);
        }
    }

    mvprintw(count + 4, 2, "Press any key to return...");
    refresh();
    getch();
}

void compile_sketch(const char *sketch_path){
	char cmd[512];
	snprintf(cmd, sizeof(cmd), "arduino-cli complie -- fqbn arduino:avr:uno %s", sketch_path);
	run_command(cmd);
}

void upload_sketch(const char *sketch_path, const char *port){
	char cmd[512];
	snprintf(cmd, sizeof(cmd), "arduino-cli upload -p %s --fqbn arduino:avr:uno %s", port, sketch_path);
	run_command(cmd);
}
