#ifndef ARDUINO_H
#define ARDUINO_H

void compile_sketch(const char *filename);
void upload_sketch(const char *filename, const char *port);
void run_command(const char *cmd);

#endif // ARDUINO_H
