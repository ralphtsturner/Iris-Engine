# Compiler and flags
CXX := g++
CXXFLAGS := -Iinc -Wall -Wextra -std=c++17
LDFLAGS := -lSDL2 -lSDL2_image  # Link SDL2_image

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

# Output executable
TARGET := $(BIN_DIR)/main

# Source and object files
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Run the executable
run: $(TARGET)
	./$(TARGET)
