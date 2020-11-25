CC := gcc #-9.1
CXX := g++ #-9.1
CXXFLAGS := -Wall -Og -std=c++20

.phony: all clean

all: scheduling

scheduling: main.o
	$(CXX) $(CXXFLAGS) -o $@ $+

main.o: src/main.cpp src/Scheduler.hpp src/RoundRobin.hpp src/SRJF.hpp src/FCFS.hpp
	$(CCX) -c -o $@ $<


clean:
	rm