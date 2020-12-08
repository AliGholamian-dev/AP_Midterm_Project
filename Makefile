CXX = g++
CXXFLAGS = -std=c++2a -Wall -I h -I /usr/local/include/gtest/ -O3 -c
LXXFLAGS = -std=c++2a -Ih -pthread
OBJECTS = ./obj/puzzle.o ./obj/main.o
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/puzzle.o: ./cpp/puzzle.cpp
	$(CXX) $(CXXFLAGS) ./cpp/puzzle.cpp -o ./obj/puzzle.o
./obj/main.o: ./cpp/main.cpp ./h/puzzle.h
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
