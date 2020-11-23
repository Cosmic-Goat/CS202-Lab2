#include <iostream>
#include <vector>
#include <deque>
#include <memory>
#include <fstream>
#include <queue>
#include <cmath>
#include <list>

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
	
	std::vector<std::unique_ptr<Process>> blockedList;
	std::deque<std::unique_ptr<Process>> readyQueue;
	auto running = std::unique_ptr<Process>{};
	
	for (int i = 0; i < 99; ++i)
	{
		for (pInfo p : list)
		{
			if (p.arrival == i)
			{
				readyQueue.emplace_back(std::make_unique<Process>(p.id, p.cpuTime, p.ioTime));
			}
		}
		
		blockedList.erase(
				std::remove_if(
						blockedList.begin(),
						blockedList.end(),
						[](std::unique_ptr<Process> &p)
						{
							p->elapsedIO++;
							readyQueue.push_back(std::move(p));
							return p->elapsedIO == p->ioTime;
						}
				),
				blockedList.end()
		);
		for (int j = 0; j < blockedList.size(); j++)
		{
			blockedList[j]->elapsedIO++;
			if (blockedList[j]->elapsedIO == blockedList[j]->ioTime)
			{
				readyQueue.push_back(std::move(blockedList[j]));
				blockedList.erase(blockedList[j]);
			}
		}
		
		running->elapsedCpu++;
		
		if (running->elapsedCpu == running->ioStart)
		{
			blockedList.push_back(std::move(running));
		}
		
		if (!running)
		{
			running = std::move(readyQueue.front());
			readyQueue.pop_front();
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
