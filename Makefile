# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11

# Target executable
TARGET = duel

# Source files and object files
SRC = main.cpp game.cpp
OBJ = $(SRC:.cpp=.o)

# Default target to build the game
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Rule to compile source files into object files
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
    rm -f $(OBJ) $(TARGET)

# To build specifically the duel target
duel: $(TARGET)
