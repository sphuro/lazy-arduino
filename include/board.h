#ifndef BOARD_H
#define BOARD_H

#define BOARD_BUFFER 8192
#define MAX_BOARDS 16

typedef struct{
	char boardName[64];
	char port[64];
} Board;

int get_boards(Board boards[], int max);

#endif
