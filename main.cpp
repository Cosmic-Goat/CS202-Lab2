#include <iostream>
#include <vector>
#include <deque>
#include <memory>

struct pInfo
{
	size_t id, cpuTime, ioTime, arrival;
};

struct Process
{
	const size_t id, cpuTime, ioTime;
	size_t elapsedCpu = 0;
	size_t elapsedIO = 0;
	
	enum State
	{
		Running, Ready, Blocked
	} state{Ready};
	
	Process(size_t id, size_t cpuTime, size_t ioTime) : id(id), cpuTime(cpuTime), ioTime(ioTime)
	{}
};

struct Cycle
{
	std::vector<Process> processes;
};

void fcfs(const std::vector<pInfo>& list)
{
	
	std::deque<std::unique_ptr<Process>> blockedQueue;
	std::deque<std::unique_ptr<Process>> readyQueue;
	auto running = std::unique_ptr<Process>{};
	
	size_t i = 0;
	
	for (i; i < 99; ++i)
	{
		for (pInfo p : list)
		{
			if (p.arrival == i)
			{
				readyQueue.emplace_back(std::make_unique<Process>(p.id, p.cpuTime, p.ioTime));
			}
		}
	
		if (!running)
		{
			running = readyQueue.front();
		}
		
	}
	
	
}

int main()
{
	size_t num;
	std::cin >> num;
	
	std::vector<pInfo> pList(num);
	for (pInfo &p : pList) std::cin >> p.id >> p.cpuTime >> p.ioTime >> p.arrival;
	
	fcfs(pList);
	
	return 0;
}
