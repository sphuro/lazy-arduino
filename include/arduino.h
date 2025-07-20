#ifndef ARDUINO_H
#define ARDUINO_H

void compile_sketch(const char *filename, const char *fqbn);
void upload_sketch(const char *filename, const char *fqbn, const char *port);
void run_command(const char *cmd);

#endif // ARDUINO_H
