# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -OS
LIBS = -lncurses

# Directories
SRC_DIRS = board_utils makers
BUILD_DIR = build

# Source files
SRCS = main.c \
       $(wildcard board_utils/*.c) \
       $(wildcard makers/*.c)

# Object files (all go into build/)
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

# Target executable
TARGET = $(BUILD_DIR)/tetris

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compile source files into object files
# Ensure subdirectories exist in build
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean