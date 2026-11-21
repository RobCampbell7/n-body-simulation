CC = gcc
CFLAGS = -O2 -Wall -Wextra
LDFLAGS =
LDLIBS = -lm

SRC_DIR = src
BUILD_DIR = build

SRCS = main.c nbody.c
OBJS = $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))
TARGET = $(BUILD_DIR)/nbody

SANITIZERS = -fsanitize=address,undefined
DEBUG_CFLAGS = -g -O0 -Wall -Wextra $(SANITIZERS)

.PHONY: all debug run clean

# Default target: optimised build
all: $(TARGET)

# Link the object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compile each .c in src/ to a .o in the build folder
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Objects that include nbody.h must rebuild when it changes
$(BUILD_DIR)/main.o: $(SRC_DIR)/nbody.h
$(BUILD_DIR)/nbody.o: $(SRC_DIR)/nbody.h

$(BUILD_DIR):
	mkdir -p $@

# Debug build with sanitisers, kept in its own folder
debug:
	$(MAKE) BUILD_DIR=$(BUILD_DIR)/debug CFLAGS="$(DEBUG_CFLAGS)" LDFLAGS="$(SANITIZERS)"

# Run from inside build/ so main.c's ../output path resolves to output/
run: all
	mkdir -p output
	cd $(BUILD_DIR) && ./nbody

clean:
	rm -rf $(BUILD_DIR)
