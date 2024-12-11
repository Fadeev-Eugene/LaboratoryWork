CXX = g++
CXXFLAGS = -Wall -Werror -Wpedantic -std=c++17
TARGET = main
SOURCES = main.cpp BMPImage.cpp LoadSaveFuncs.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
