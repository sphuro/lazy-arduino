#include "arduino.h"
#include "logs.h"
#include <stdio.h>
#include <stdlib.h>

void restore_ncurses_mode() {
    initscr();      
    cbreak();       
    noecho();       
    keypad(stdscr, TRUE); 
    curs_set(0);    
    refresh();
}

void run_command(const char *cmd) {
    endwin();
    printf("--- Running Command: %s ---\n\n", cmd);
    FILE *fp = popen(cmd, "r");
    if (!fp) {
        printf("Failed to run command.\n");
    } else {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }
        pclose(fp);
    }
    printf("\n--- Command finished. Press Enter to return to the app ---");
    getchar(); 
    restore_ncurses_mode();
}

void compile_sketch(const char *sketch_path, const char *fqbn) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "arduino-cli compile --fqbn %s %s", fqbn, sketch_path);
    run_command(cmd);
}

void upload_sketch(const char *sketch_path, const char *fqbn, const char *port) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "arduino-cli upload -p %s --fqbn %s %s", port, fqbn, sketch_path);
    run_command(cmd);
}
