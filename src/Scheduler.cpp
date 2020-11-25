#include "Scheduler.hpp"

Scheduler::Scheduler(std::vector<Process> &processes) : processes(processes)
{
	for (auto &&p: processes) blockedList.push({p.arrival, &p});
}

void Scheduler::runCycle()
{
	updateBlocked();
	
	if (running)
	{
		activeCycles++;
		updateRunningProcess();
	}
	
	if (!running && hasReadyProcess()) switchProcess();
	curCycle++;
}

void Scheduler::updateRunningProcess()
{
	running->elapsedCpu++;
	
	if (running->elapsedCpu == running->ioStart())
	{
		blockProcess(running);
	} else if (running->elapsedCpu == running->cpuTime)
	{
		terminateProcess(running);
	}
}

void Scheduler::terminateProcess(Process *&p)
{
	p->state = Process::Inactive;
	finishedList.emplace(p->id, curCycle - p->arrival);
	p = nullptr;
}

void Scheduler::blockProcess(Process *&p)
{
	p->state = Process::Blocked;
	blockedList.push({curCycle + p->ioTime, p});
	p = nullptr;
}

void Scheduler::updateBlocked()
{
	while (!blockedList.empty() && blockedList.top().first == curCycle)
	{
		readyProcess(blockedList.top().second);
		blockedList.pop();
	}
}
