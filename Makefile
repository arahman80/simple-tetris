# C compiler
CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Werror -Os -Iinclude
DEBUG_FLAGS = -std=c99 -Wall -Wextra -Werror -Wpedantic -O0 -g -Iinclude
LIBS = -lncurses

# Directories
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
OBJ_DIR_DEBUG = $(BUILD_DIR)/obj_debug

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/**/*.c $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_DEBUG := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR_DEBUG)/%.o,$(SRCS))

# Targets
TARGET = $(BUILD_DIR)/tetris
DEBUG_TARGET = $(BUILD_DIR)/tetris_debug

# Default goal: format + build
.DEFAULT_GOAL := build

.PHONY: build
build: format $(TARGET)
	@echo "Build complete: $(TARGET)"

# Formatting
.PHONY: format
format:
	clang-format -i $(SRCS) $(wildcard include/*.h)

# Run targets
.PHONY: run
run: build
	./$(TARGET)

.PHONY: debug
debug: $(DEBUG_TARGET)
	./$(DEBUG_TARGET)

# Static analysis
.PHONY: lint
lint:
	clang-tidy $(SRCS) \
		--checks=clang-analyzer-*,bugprone-*,hicpp-* \
		-header-filter=.* \
		-- $(CFLAGS) -fdiagnostics-color=always

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Pull from the remote repository
.PHONY: update
update:
	git pull

# Display targets
.PHONY: help
help:
	@grep -E '^[[:space:]]*\.PHONY[[:space:]]*:' $(MAKEFILE_LIST) \
		| sed 's/^[^:]*: //' \
		| tr ' ' '\n'

# Link executable
$(TARGET): $(OBJS) | build_dir
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(DEBUG_TARGET): $(OBJS_DEBUG) | build_dir
	$(CC) $(DEBUG_FLAGS) -o $@ $^ $(LIBS)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | build_dir
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_DEBUG)/%.o: $(SRC_DIR)/%.c | build_dir
	@mkdir -p $(dir $@)
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

# Ensure build directories exist
.PHONY: build_dir
build_dir:
	mkdir -p $(BUILD_DIR) $(OBJ_DIR) $(OBJ_DIR_DEBUG)