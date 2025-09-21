# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Os -Iinclude
LIBS = -lncurses

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/board_utils/*.c) \
       $(wildcard $(SRC_DIR)/makers/*.c)

# Object files (mirrors src/ hierarchy inside build/obj/)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Target executable
TARGET = $(BUILD_DIR)/tetris

# Clang-format style (can be overridden)
STYLE = GNU

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build and object directories exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Format all C and header files
format:
	clang-format -i -style=$(STYLE) $(SRCS) $(wildcard include/*.h)

# Run clang-tidy on all sources
lint:
	clang-tidy $(SRCS) -header-filter=.* -- $(CFLAGS) -fdiagnostics-color=always

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean format lint
