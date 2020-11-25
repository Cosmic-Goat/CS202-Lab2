#include "RoundRobin.hpp"

void RoundRobin::updateRunningProcess()
{
	qRunTime++;
	Scheduler::updateRunningProcess();
	
	if (running && qRunTime == 2)
	{
		readyProcess(running);
		running = nullptr;
	}
}

void RoundRobin::switchProcess()
{
		FCFS::switchProcess();
		qRunTime = 0;
}

RoundRobin::RoundRobin(std::vector<Process> &processes) : FCFS(processes)
{}
