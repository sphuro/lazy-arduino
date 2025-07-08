#include "arduino.h"
#include "board.h"
#include "logs.h"
#include "sketches.h"
#include "status.h"
#include "ui.h"
#include <complex.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_command(const char *cmd) {
  FILE *fp = popen(cmd, "r");
  if (!fp) {
    mvprintw(10, 0, "Failed to run command");
    return;
  }

  clear();
  mvprintw(0, 0, "Output: [%s]", cmd);

  start_loading();
  char buffer[256];
  int line = 2;
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
  mvprintw(line + 1, 2, "Press any key to return ... ");
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
      mvprintw(i + 2, 2, "[%d] %s (%s)", i + 1, boards[i].boardName,
               boards[i].port);
    }
  }

  mvprintw(count + 4, 2, "Press any key to return...");
  refresh();
  getch();
}

void compile_sketch(const char *sketch_path) {
  char cmd[512];
  snprintf(cmd, sizeof(cmd), "arduino-cli compile -- fqbn arduino:avr:uno %s",
           sketch_path);
  run_command(cmd);
}

void upload_sketch(const char *sketch_path, const char *port) {
  char cmd[512];
  snprintf(cmd, sizeof(cmd),
           "arduino-cli upload -p %s --fqbn arduino:avr:uno %s", port,
           sketch_path);
  run_command(cmd);
}

void process_cmd(const char *cmd) {
  char filename[128];

  if (sscanf(cmd, ":newfile %s", filename) == 1) {
    if (!strstr(filename, ".ino")) {
      strcat(filename, ".ino");
    }
    FILE *file = fopen(filename, "w");
    if (file) {
      fprintf(file, "void setup() {\n");
      fprintf(file, "  // put your setup code here, to run once:\n\n");
      fprintf(file, "}\n\n");
      fprintf(file, "void loop() {\n");
      fprintf(file, "  // put your main code here, to run repeatedly:\n\n");
      fprintf(file, "}\n");
      fclose(file);

      char log_msg[256];
      snprintf(log_msg, sizeof(log_msg), "Created file: %s", filename);
      add_log(log_msg);
      load_sketches(".");
    } else {
      add_log("Error: Could not create file.");
    }

  } else {
    add_log("Error: unknown command");
  }
}
