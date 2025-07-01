# Makefile for Lazy Arduino TUI

CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lncurses

SRC_DIR = src
OBJ_DIR = obj
BIN = lazy-arduino

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean run

all: $(OBJ_DIR) $(BIN)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

run: all
	./$(BIN)

clean:
	rm -rf $(OBJ_DIR) $(BIN)

