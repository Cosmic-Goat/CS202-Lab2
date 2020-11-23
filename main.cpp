#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <queue>
#include <cmath>
#include <list>
#include <set>
#include <map>
#include <string>
#include <sstream>

#include "magic_enum.hpp"

using PID = const size_t;
struct Process
{
	PID id;
	const size_t cpuTime, ioTime, arrival;
	const size_t ioStart = cpuTime / 2 + (cpuTime % 2 != 0);
	size_t elapsedCpu = 0;
	
	enum State {
		running, ready, blocked, notArrived, finished
	} state{notArrived};
	
	Process(const PID id, const size_t cpuTime, const size_t ioTime, const size_t arrival) : id(id),
	                                                                                            cpuTime(cpuTime),
	                                                                                            ioTime(ioTime),
	                                                                                            arrival(arrival)
	{}
};

using pTimePair = std::pair<size_t, Process *>;

void TimingSnapshot(const size_t cycle, const std::vector<Process> &processes, std::ostream &output)
{
	output << cycle << " ";
	for (auto &&p : processes)
	{
		switch (p.state)
		{
			case Process::running:
				output << p.id << ":running ";
				break;
			case Process::ready:
				output << p.id << ":ready ";
				break;
			case Process::blocked:
				output << p.id << ":blocked ";
				break;
			case Process::notArrived:
			case Process::finished:
				break;
		}
	}
	output << "\n";
}

void scheduler(std::vector<Process> &processes, std::ostream &out)
{
	std::priority_queue<pTimePair, std::vector<pTimePair>, std::greater<>> blockedList;
	std::priority_queue<Process *> readyQueue;
	std::map<PID, size_t> finishedList;
	Process *running = nullptr;
	
	for (auto &&p: processes)
	{
		blockedList.push({p.arrival, &p});
	}
	
	for (int curCycle = 0; finishedList.size() < processes.size(); ++curCycle)
	{
		
		while (blockedList.top().first == curCycle)
		{
			blockedList.top().second->state = Process::ready;
			readyQueue.push(blockedList.top().second);
			blockedList.pop();
		}
		
		if (running)
		{
			running->elapsedCpu++;
			
			if (running->elapsedCpu == running->ioStart)
			{
				running->state = Process::blocked;
				blockedList.push({curCycle + running->ioTime, running});
				running = nullptr;
			} else if (running->elapsedCpu == running->cpuTime)
			{
				running->state = Process::finished;
				finishedList.emplace(running->id, curCycle);
				running = nullptr;
			}
		}
		
		if (!running && !readyQueue.empty())
		{
			running = readyQueue.top();
			readyQueue.pop();
			running->state = Process::running;
		}
		
		TimingSnapshot(curCycle, processes, out);
		
		
	}
	
	
}




int main(int argc, char *argv[])
{
	std::ifstream input(argv[1]);
	
	if (input.is_open())
	{
		size_t num;
		input >> num;
		
		std::vector<Process> pList;
		pList.reserve(num);
		
		for (int i = 0; i < num; ++i)
		{
			size_t id, cpuTime, ioTime, arrival;
			input >> id >> cpuTime >> ioTime >> arrival;
			pList.emplace_back(id, cpuTime, ioTime, arrival);
		}
		
		scheduler(pList, std::cout);
	}
	return 0;
}
