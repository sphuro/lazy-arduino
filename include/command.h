#ifndef COMMAND_H
#define COMMAND_H

typedef void (*command_act)(const char *args);

typedef struct {
    const char *name;
    command_act action;
} Command;

void process_command(const char *input);

#endif // COMMAND_H
