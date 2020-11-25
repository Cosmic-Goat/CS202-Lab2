//
// Created by Shrey on 24/11/2020.
//

#include <vector>
#include <queue>
#include <map>
#include "FCFS.hpp"

void FCFS::readyProcesses()
{
	while (!blockedList.empty() && blockedList.top().first == curCycle)
	{
		blockedList.top().second->state = Process::ready;
		readyQueue.push_back(blockedList.top().second);
		blockedList.pop();
	}
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

void FCFS::updateRunningProcess()
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

FCFS::FCFS(std::vector<Process> &processes) : Scheduler(processes)
{}
