#ifndef ARDUINO_H
#define ARDUINO_H

void list_boards(void);
void compile_sketch(const char *sketch_path);
void upload_sketch(const char *sketch_path, const char *port);

#endif

