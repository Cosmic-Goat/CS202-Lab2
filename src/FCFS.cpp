#include <vector>
#include "FCFS.hpp"

void FCFS::readyProcess(Process *const p)
{
	p->state = Process::ready;
	readyQueue.push_back(p);
}

void FCFS::processSwitch()
{
	if (!readyQueue.empty())
	{
		running = readyQueue[0];
		readyQueue.pop_front();
		running->state = Process::running;
	}
}

FCFS::FCFS(std::vector<Process> &processes) : Scheduler(processes)
{}
