# =========================
# Compiler
# =========================
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INC_DIR)

# =========================
# Project structure
# =========================
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN = main

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# =========================
# Rules
# =========================
.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp → .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =========================
# Clean
# =========================
clean:
	rm -rf $(OBJ_DIR) $(BIN)

# =========================
# Run
# =========================
run: $(BIN)
	./$(BIN)