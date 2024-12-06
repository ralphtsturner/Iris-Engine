# Compiler and flags
CXX := g++
CXXFLAGS := -Iinc -Iinc/engine -Wall -Wextra -std=c++17
LDFLAGS := -lSDL2 -lSDL2_image

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

# Output executable
TARGET := $(BIN_DIR)/main

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/engine/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Run the executable
run: $(TARGET)
	./$(TARGET)
