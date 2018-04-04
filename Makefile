EXECUTABLE = swpathtracer

CXX = g++

CXXFLAGS = -std=c++14 -Wall -Wextra -Wpedantic -fopenmp -Itinyobjloader

ifeq ($(DEBUG), 1)
CXXFLAGS += -DDEBUG -O0 -g3
else
CXXFLAGS += -DNDEBUG -O3 -g0
endif

CPPFLAGS += -MMD

LDFLAGS =

LDLIBS =

SOURCES = $(wildcard *.cpp)

OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDLIBS)

.cpp.o:

-include $(OBJECTS:.o=.d)

.PHONY: clean distclean

clean:
	rm *.o *.d

distclean: clean
	rm $(EXECUTABLE)

