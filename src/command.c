#include "command.h"
#include "state.h"
#include "logs.h"
#include "colors.h"
#include "pages.h"
#include "sketches.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void command_newfile(const char *args) {
    char filename[128] = {0};
    sscanf(args, "%127s", filename);

    if (strlen(filename) == 0) {
        add_log("Error: :newfile requires a filename");
        return;
    }

    // Safely append .ino extension if not present
    if (!strstr(filename, ".ino")) {
        strncat(filename, ".ino", sizeof(filename) - strlen(filename) - 1);
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
}

void command_color_hex(const char *args) {
    char hex_clr[8] = {0};
    sscanf(args, "%7s", hex_clr);

    if (strlen(hex_clr) == 6) {
        // Validate it's a real hex string
        bool is_valid = true;
        for(int i = 0; i < 6; i++) {
            if (!isxdigit(hex_clr[i])) {
                is_valid = false;
                break;
            }
        }

        if(is_valid) {
            char log_msg[64];
            snprintf(log_msg, sizeof(log_msg), "Set color to #%s", hex_clr);
            add_log(log_msg);
            apply_theme_hex(hex_clr);
        } else {
            add_log("Error: Invalid hex characters.");
        }
    } else {
        add_log("Error: Invalid hex format. Use #RRGGBB");
    }
}

void command_color_picker(const char *args) {
    (void)args; // Unused
    for (int i = 0; i < NUM_PAGES; i++) {
        if (strcmp(page_registry[i].name, "Color Picker") == 0) {
            switch_page(i);
            break;
        }
    }
}

static const Command command_registry[] = {
    {":newfile", command_newfile},
    {":color #", command_color_hex},
    {":color", command_color_picker}
};
static const int num_commands = sizeof(command_registry) / sizeof(Command);

void process_command(const char *input) {
    for (int i = 0; i < num_commands; i++) {
        size_t cmd_len = strlen(command_registry[i].name);
        if (strncmp(input, command_registry[i].name, cmd_len) == 0) {
            const char *args = input + cmd_len;
            while (*args == ' ') // Skip whitespace
                args++;
            
            command_registry[i].action(args);
            return;
        }
    }
    add_log("Error: Unknown command");
}
