CXX = g++
CXXFLAGS = -std=c++11 -Wall
OBJS = main.o game.o
TARGET = hangman

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp game.h
	$(CXX) $(CXXFLAGS) -c main.cpp

game.o: game.cpp game.h
	$(CXX) $(CXXFLAGS) -c game.cpp

clean:
	rm -f $(OBJS) $(TARGET)
