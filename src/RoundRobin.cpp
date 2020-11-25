//
// Created by Shrey on 24/11/2020.
//

#include "RoundRobin.hpp"

void RoundRobin::updateRunningProcess()
{
	FCFS::updateRunningProcess();
	
	if (qRunTime == 2)
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
		running->state = Process::running;
	}
}

RoundRobin::RoundRobin(std::vector<Process> &processes) : FCFS(processes)
{}
