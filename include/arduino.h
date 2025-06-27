#ifndef ARDUINO_H
#define ARDUINO_H

void list_boards(void);
void compile_sketch(const char *filename);
void upload_sketch(const char *filename, const char *port);

#endif

