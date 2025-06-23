#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

void run_command(const char *cmd){
	FILE *fp = popen(cmd, "r");
	if(!fp){
		mvprintw(10, 0, "Failed to run command");
		return;
	}

	clear();
	mvprintw(0, 0, "Output: [%s]", cmd);
	char buffer[256];
	int line =2;
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		mvprintw(line++, 2, "%s", buffer);
	
	}
	pclose(fp);
	mvprintw(line+1, 2, "Press any key to return ... ");
	getch();
}

void list_boards(){
	run_command("arduino-cli board list");
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
