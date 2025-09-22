# Compiler and flags
CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Werror -Os -Iinclude
DEBUG_FLAGS = -std=c99 -Wall -Wextra -Werror -Wpedantic -O0 -g -Iinclude
LIBS = -lncurses

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/game_utils/*.c) \
       $(wildcard $(SRC_DIR)/initializers/*.c) \
       $(wildcard $(SRC_DIR)/piece/*.c) \
       $(wildcard $(SRC_DIR)/piece_select/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Target executables
TARGET = $(BUILD_DIR)/tetris
DEBUG_TARGET = $(BUILD_DIR)/tetris_debug

# Default rule
all: $(TARGET)

# Link executables
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(DEBUG_TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(DEBUG_FLAGS) -o $@ $^ $(LIBS)

# Compile object files (generic rule)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile object files for debug
debug_objs := $(OBJS)
debug: CFLAGS := $(DEBUG_FLAGS)
debug: $(DEBUG_TARGET)

# Ensure build directories exist
$(BUILD_DIR) $(OBJ_DIR):
	mkdir -p $@

# Format
format:
	clang-format -i $(SRCS) $(wildcard include/*.h)

# Clang-tidy
tidy:
	clang-tidy $(SRCS) \
		--checks=clang-analyzer-*,bugprone-*,hicpp-* \
		-header-filter=.* \
		-- $(CFLAGS) -fdiagnostics-color=always

# Clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean format tidy debug