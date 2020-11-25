CC := gcc
CXX := g++
CXXFLAGS := -Wall -Og -std=c++20

.phony: all clean

all: scheduling

scheduling: main.o
	$(CXX) $(CXXFLAGS) -o $@ $+

main.o: src/main.cpp src/Scheduler.hpp src/RoundRobin.hpp src/SRJF.hpp src/FCFS.hpp
	$(CCX) $(CXXFLAGS) -c -o $@ $<


clean:
	rm scheduling