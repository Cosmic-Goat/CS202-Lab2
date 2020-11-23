#include <iostream>
#include <vector>
#include <deque>
#include <memory>
#include <fstream>
#include <queue>
#include <cmath>
#include <list>
#include <set>
#include <map>

using PID = const size_t;
struct Process
{
	PID id;
	const size_t cpuTime, ioTime, arrival;
	const size_t ioStart = cpuTime / 2 + (cpuTime % 2 != 0);
	size_t elapsedCpu = 0;
	
	Process(const PID id, const size_t cpuTime, const size_t ioTime, const size_t arrival) : id(id),
	                                                                                            cpuTime(cpuTime),
	                                                                                            ioTime(ioTime),
	                                                                                            arrival(arrival)
	{}
};

using TimeProcPair = std::pair<const size_t, Process *const>;

void fcfs(std::vector<Process> &processes)
{
	std::priority_queue<TimeProcPair> blockedList;
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
			readyQueue.push(blockedList.top().second);
			blockedList.pop();
		}
		
		if (running)
		{
			running->elapsedCpu++;
			
			if (running->elapsedCpu == running->ioStart)
			{
				blockedList.push({curCycle + running->ioTime, running});
				running = nullptr;
			} else if (running->elapsedCpu == running->cpuTime)
			{
				finishedList.emplace(running->id, curCycle);
				running = nullptr;
			}
		}
		
		if (!running)
		{
			running = readyQueue.top();
			readyQueue.pop();
		}
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
		
		fcfs(pList);
	}
	return 0;
}
