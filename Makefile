CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude
SDL_FLAGS = $(shell pkg-config --cflags --libs sdl2)

SRC_DIR = src
BUILD_DIR = build

TARGET = jump-run

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)


all: $(TARGET)


$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(SDL_FLAGS)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET)


clean:
	rm -rf $(BUILD_DIR) $(TARGET)


rebuild: clean all


.PHONY: all run clean rebuild