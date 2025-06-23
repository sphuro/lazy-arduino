CC = gcc
CFLAGS = -Wall -lncurses


all: lazy-arduino

lazy-arduino: src/main.c src/ui.c src/arduino.c
	$(CC) $(CFLAGS) -o lazy-arduino src/main.c src/ui.c src/arduino.c

clean:
	rm -f lazy-arduino
