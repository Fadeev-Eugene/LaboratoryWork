CXX = g++
CXXFLAGS = -Wall -Werror -Wpedantic -std=c++17
ASTYLE = astyle -A1 -s4
TARGET = main
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
run: $(TARGET)
	/usr/bin/time -v ./$(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

format:
	$(ASTYLE) $(SOURCES)

clean:
	rm -f $(OBJECTS) $(TARGET)
