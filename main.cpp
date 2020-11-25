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

using PID = const size_t;

struct Process
{
	PID id;
	const size_t cpuTime, ioTime, arrival;
	const size_t ioStart = cpuTime / 2 + (cpuTime % 2 != 0);
	size_t elapsedCpu = 0;
	
	enum State
	{
		running, ready, blocked, inactive
	} state{inactive};
	
	Process(const PID id, const size_t cpuTime, const size_t ioTime, const size_t arrival) : id(id),
	                                                                                         cpuTime(cpuTime),
	                                                                                         ioTime(ioTime),
	                                                                                         arrival(arrival)
	{}
};

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
			case Process::inactive:
				break;
		}
	}
	output << "\n";
}

class Scheduler
{
	using pTimePair = std::pair<size_t, Process *>;
private:
	std::vector<Process> &processes;
	std::priority_queue<pTimePair, std::vector<pTimePair>, std::greater<>> blockedList;
	std::deque<Process *> readyQueue;
	Process *running = nullptr;
	
	size_t curCycle = 0;
	void readyProcesses()
	{
		while (!blockedList.empty() && blockedList.top().first == curCycle)
		{
			blockedList.top().second->state = Process::ready;
			readyQueue.push_back(blockedList.top().second);
			blockedList.pop();
		}
	}
	
	void processSwitch()
	{
		running = readyQueue[0];
		readyQueue.pop_front();
		running->state = Process::running;
	}
	
	void updateRunningProcess()
	{
		running->elapsedCpu++;
		
		if (running->elapsedCpu == running->ioStart)
		{
			running->state = Process::blocked;
			blockedList.push({curCycle + running->ioTime, running});
			running = nullptr;
		} else if (running->elapsedCpu == running->cpuTime)
		{
			running->state = Process::inactive;
			finishedList.emplace(running->id, curCycle - running->arrival);
			running = nullptr;
		}
	}
	
public:
	size_t activeCycles = 0;
	std::map<PID, const size_t> finishedList;
	
	explicit Scheduler(std::vector<Process> &processes) : processes(processes)
	{
		for (auto &&p: processes)
		{
			blockedList.push({p.arrival, &p});
		}
	}
	
	inline size_t getCurCycle() const {return curCycle - 1;}
	
	void runCycle()
	{
		readyProcesses();
		
		if (running)
		{
			activeCycles++;
			updateRunningProcess();
		}
		
		if (!running && !readyQueue.empty())
		{
			processSwitch();
		}
		
		curCycle++;
	}
	
	bool isRunning()
	{
		return finishedList.size() < processes.size();
	}
};


int main(int argc, char *argv[])
{
	std::ifstream input(argv[1]);
	std::ostream &output = std::cout;
	
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
		
		Scheduler scheduler(pList);
		
		scheduler.runCycle();
		while (scheduler.isRunning())
		{
			TimingSnapshot(scheduler.getCurCycle(), pList, output);
			scheduler.runCycle();
		}
		
		output << "\nFinishing time: " << scheduler.getCurCycle() - 1;
		output << "\nCPU utilization: " << static_cast<float>(scheduler.activeCycles) / scheduler.getCurCycle();
		
		for (auto &&p : scheduler.finishedList)
		{
			output << "\nTurnaround process " << p.first << ": " << p.second;
		}
	}
	return 0;
}
