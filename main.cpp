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

struct pInfo
{
	size_t id, cpuTime, ioTime, arrival;
};

struct Process
{
	const size_t id, cpuTime, ioTime;
	const size_t ioStart = cpuTime / 2 + (cpuTime % 2 != 0);
	size_t elapsedCpu = 0;
	size_t elapsedIO = 0;
	
	enum State
	{
		Running, Ready, Blocked
	} state{Ready};
	
	Process(size_t id, size_t cpuTime, size_t ioTime) : id(id), cpuTime(cpuTime), ioTime(ioTime)
	{}
};

void fcfs(const std::vector<pInfo> &list)
{
	std::vector<Process> processes;
	processes.reserve(list.size());
	std::priority_queue<std::pair<const size_t, Process *>> blockedList;
	std::priority_queue<Process *> readyQueue;
	Process *running = nullptr;
	
	for (auto const &p : list)
	{
		processes.emplace_back(p.id, p.cpuTime, p.ioTime);
		blockedList.push({p.arrival, &processes.back()});
	}
	
	for (int i = 0; i < 99; ++i)
	{
		
		while (blockedList.top().first == i)
		{
			readyQueue.push(blockedList.top().second);
			blockedList.pop();
		}
		
		if (running)
		{
			
			running->elapsedCpu++;
			
			if (running->elapsedCpu == running->ioStart)
			{
				blockedList.push({i + running->ioTime, running});
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
		
		std::vector<pInfo> pList(num);
		for (pInfo &p : pList) input >> p.id >> p.cpuTime >> p.ioTime >> p.arrival;
		
		fcfs(pList);
	}
	return 0;
}
