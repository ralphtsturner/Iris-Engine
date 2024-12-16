# Compiler and flags
CXX := g++
CXXFLAGS := -I/opt/homebrew/include/SDL2/ -Iinc -Iinc/engine -Iinclude/glad -Wall -Wextra -std=c++17
LDFLAGS := -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_mixer

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

# Output executable
TARGET := $(BIN_DIR)/main

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/engine/*.cpp) $(SRC_DIR)/glad.c
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(OBJS))

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR) $(BUILD_DIR)/engine
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files (e.g., glad.c) to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Run the executable
run: $(TARGET)
	./$(TARGET)
