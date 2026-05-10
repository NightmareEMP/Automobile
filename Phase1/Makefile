# =========================
# Compiler
# =========================
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinc

# =========================
# Project structure
# =========================
SRC_DIR = .
INC_DIR = inc
OBJ_DIR = obj
BIN = servo_ctrl

# Source files
SRCS = Uart_drv.cpp Vehicle_Ctrl.cpp

# Object files
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# =========================
# Rules
# =========================

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp → .o
$(OBJ_DIR)/%.o: %.cpp
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