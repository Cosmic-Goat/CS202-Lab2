#include "RoundRobin.hpp"

void RoundRobin::updateRunningProcess()
{
	qRunTime++;
	running->elapsedCpu++;
	
	if (running->elapsedCpu == running->ioStart)
	{
		blockProcess(running);
	} else if (running->elapsedCpu == running->cpuTime)
	{
		terminateProcess(running);
	} else if (qRunTime == 2)
	{
		readyProcess(running);
		running = nullptr;
	}
}

void RoundRobin::processSwitch()
{
	if (!readyQueue.empty())
	{
		running = readyQueue[0];
		readyQueue.pop_front();
		running->state = Process::Running;
		qRunTime = 0;
	}
}

RoundRobin::RoundRobin(std::vector<Process> &processes) : FCFS(processes)
{}
