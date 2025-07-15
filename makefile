CC = gcc

CFLAGS = -Wall -Wextra -g -Iinclude

LDFLAGS = -lncurses

TARGET = lazy-arduino

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

DEPS = $(wildcard $(INCLUDE_DIR)/*.h)

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking object files to create executable..."
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete! Executable is '$(TARGET)'."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(OBJ_DIR)
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: run
run: all
	./$(TARGET)

.PHONY: clean
clean:
	@echo "Cleaning up build files..."
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)
	@echo "Cleanup complete."


