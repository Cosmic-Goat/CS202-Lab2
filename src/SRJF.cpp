#include "SRJF.hpp"

SRJF::SRJF(std::vector<Process> &processes) : Scheduler(processes)
{}

void SRJF::updateRunningProcess()
{
	Scheduler::updateRunningProcess();
	if (running)
	{
		readyProcess(running);
		running = nullptr;
	}
}

void SRJF::readyProcess(Process *const p)
{
	p->state = Process::Ready;
	readyQueue.emplace(p->cpuTime - p->elapsedCpu, p);
}

void SRJF::switchProcess()
{
	if (!readyQueue.empty())
	{
		running = readyQueue.top().second;
		readyQueue.pop();
		running->state = Process::Running;
	}
}
