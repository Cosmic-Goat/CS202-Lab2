#include "FCFS.hpp"

void FCFS::readyProcess(Process *const p)
{
	p->state = Process::Ready;
	readyQueue.push_back(p);
}

void FCFS::switchProcess()
{
	if (!readyQueue.empty())
	{
		running = readyQueue[0];
		readyQueue.pop_front();
		running->state = Process::Running;
	}
}

FCFS::FCFS(std::vector<Process> &processes) : Scheduler(processes)
{}
