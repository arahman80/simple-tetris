# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Os -Iinclude
LIBS = -lncurses

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/board_utils/*.c) \
       $(wildcard $(SRC_DIR)/makers/*.c)

# Object files (mirrors src/ hierarchy inside build/)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Target executable
TARGET = $(BUILD_DIR)/tetris

# Clang-format style (can be overridden)
STYLE = GNU

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Format all C and header files
format:
	clang-format -i -style=$(STYLE) $(SRCS) $(wildcard include/*.h)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean format
