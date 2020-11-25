#include "FCFS.hpp"
#include <vector>

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
	
	if (!running) processSwitch();
	curCycle++;
}

void Scheduler::updateRunningProcess()
{
	running->elapsedCpu++;
	
	if (running->elapsedCpu == running->ioStart)
	{
		blockProcess(running);
	} else if (running->elapsedCpu == running->cpuTime)
	{
		terminateProcess(running);
	}
}

void Scheduler::terminateProcess(Process *&p)
{
	p->state = Process::inactive;
	finishedList.emplace(p->id, curCycle - p->arrival);
	p = nullptr;
}

void Scheduler::blockProcess(Process *&p)
{
	p->state = Process::blocked;
	blockedList.push({curCycle + p->ioTime, p});
	p = nullptr;
}

void Scheduler::readyProcesses()
{
	while (!blockedList.empty() && blockedList.top().first == curCycle)
	{
		readyProcess(blockedList.top().second);
		blockedList.pop();
	}
}
