# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -Os -Iinclude
LDFLAGS = 

FPC = fpc
FPCFLAGS = -O2 -o

# Directories
SRC_DIR = src
BUILD_DIR = build

# C sources and objects
C_SRC = $(wildcard $(SRC_DIR)/*.c)
C_HDR = $(wildcard include/*.h)
C_OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRC))
C_TARGET = $(BUILD_DIR)/tetris

# Pascal sources and target
PAS_SRC = $(SRC_DIR)/main.pas
PAS_TARGET = $(BUILD_DIR)/tetris-pas

# Default target
all: c pascal

# Build directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# C build
c: $(BUILD_DIR) $(C_TARGET)

$(C_TARGET): $(C_OBJ) | $(BUILD_DIR)
	@echo "Linking C Tetris..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Pascal build
pascal: $(BUILD_DIR) $(PAS_TARGET)

$(PAS_TARGET): $(PAS_SRC) | $(BUILD_DIR)
	@echo "Building Pascal Tetris..."
	$(FPC) $(FPCFLAGS)$@ $<

# Clean targets
clean: clean-c clean-pascal

clean-c:
	rm -f $(C_OBJ) $(C_TARGET)

clean-pascal:
	rm -f $(PAS_TARGET)

# Format (C only)
format:
	clang-format -i $(C_SRC) $(C_HDR)

# Phony targets
.PHONY: all c pascal clean clean-c clean-pascal format