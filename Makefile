# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11

# Target executable name
TARGET = duel

# Source files
SRC = main.cpp game.cpp

# Rule to build the duel target
duel:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean up build artifacts
clean:
	rm -f $(TARGET)
