#include <string>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include "Scheduler.hpp"

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

