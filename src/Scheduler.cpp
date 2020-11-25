#include <string>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include "Scheduler.hpp"

void Scheduler::readyProcesses()
{
	while (!blockedList.empty() && blockedList.top().first == curCycle)
	{
		blockedList.top().second->state = Process::ready;
		readyQueue.push_back(blockedList.top().second);
		blockedList.pop();
	}
}

void Scheduler::processSwitch()
{
	running = readyQueue[0];
	readyQueue.pop_front();
	running->state = Process::running;
}

void Scheduler::updateRunningProcess()
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

Scheduler::Scheduler(std::vector<Process> &processes) : processes(processes)
{
	for (auto &&p: processes)
	{
		blockedList.push({p.arrival, &p});
	}
}

void Scheduler::runCycle()
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
