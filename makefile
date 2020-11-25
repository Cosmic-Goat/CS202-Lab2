CXX = g++-9.1
CPPFLAGS = -Wall -std=c++2a
LD_FLAGS = -static-libstdc++

SOURCEDIR = src
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
EXE = scheduling

.phony: all clean

all: $(SOURCES) $(EXE)

$(EXE): $(OBJECTS)
		$(CXX) $(LD_FLAGS) $(OBJECTS) -o $@

clean:
		rm -f *.o $(OBJECTS)