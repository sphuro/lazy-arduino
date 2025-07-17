#include "arduino.h"
#include "logs.h"
#include <stdio.h>
#include <stdlib.h>

// Helper function to restore ncurses state after temporarily leaving it
void restore_ncurses_mode() {
    initscr();      // Re-initialize ncurses
    cbreak();       // Go back to cbreak mode
    noecho();       // Don't echo keypresses
    keypad(stdscr, TRUE); // Enable function keys, arrow keys, etc.
    curs_set(0);    // Hide the cursor
    refresh();      // Refresh the screen to clear any command output
}

// This function is completely rewritten to properly pause ncurses
void run_command(const char *cmd) {
    // 1. Safely pause ncurses
    endwin();
    printf("--- Running Command: %s ---\n\n", cmd);

    // 2. Run the command and stream its output using standard I/O
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

    // 3. Wait for user to continue
    printf("\n--- Command finished. Press Enter to return to the app ---");
    getchar(); // Wait for Enter key

    // 4. Restore ncurses mode completely
    restore_ncurses_mode();
}

void compile_sketch(const char *sketch_path) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "arduino-cli compile --fqbn arduino:avr:uno %s", sketch_path);
    run_command(cmd);
}

void upload_sketch(const char *sketch_path, const char *port) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "arduino-cli upload -p %s --fqbn arduino:avr:uno %s", port, sketch_path);
    run_command(cmd);
}
