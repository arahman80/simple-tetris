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

# Formatting
.PHONY: format
format:
	clang-format -i $(SRCS) $(wildcard include/*.h)  # Auto-format sources and headers

# Default build
.PHONY: all
all: $(TARGET)

# Run targets
.PHONY: run
run: $(TARGET)
	make format
	./$(TARGET)

.PHONY: debug
debug: $(DEBUG_TARGET)
	make format
	./$(DEBUG_TARGET)

# Static analysis
.PHONY: tidy
tidy:
	clang-tidy $(SRCS) \
		--checks=clang-analyzer-*,bugprone-*,hicpp-* \
		-header-filter=.* \
		-- $(CFLAGS) -fdiagnostics-color=always

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Link executable
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(DEBUG_TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(DEBUG_FLAGS) -o $@ $^ $(LIBS)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_DEBUG)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR_DEBUG)
	@mkdir -p $(dir $@)
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

# Ensure build directories exist
$(BUILD_DIR) $(OBJ_DIR):
	mkdir -p $@