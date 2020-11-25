#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <queue>
#include <cmath>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include "Scheduler.hpp"

void TimingSnapshot(const size_t cycle, const std::vector<Process> &processes, std::ostream &output)
{
	output << cycle << " ";
	for (auto &&p : processes)
	{
		switch (p.state)
		{
			case Process::running:
				output << p.id << ":running ";
				break;
			case Process::ready:
				output << p.id << ":ready ";
				break;
			case Process::blocked:
				output << p.id << ":blocked ";
				break;
			case Process::inactive:
				break;
		}
	}
	output << "\n";
}


int main(int argc, char *argv[])
{
	std::ifstream input(argv[1]);
	std::ostream &output = std::cout;
	
	if (input.is_open())
	{
		size_t num;
		input >> num;
		
		std::vector<Process> pList;
		pList.reserve(num);
		
		for (int i = 0; i < num; ++i)
		{
			size_t id, cpuTime, ioTime, arrival;
			input >> id >> cpuTime >> ioTime >> arrival;
			pList.emplace_back(id, cpuTime, ioTime, arrival);
		}
		
		Scheduler scheduler(pList);
		
		scheduler.runCycle();
		while (scheduler.isRunning())
		{
			TimingSnapshot(scheduler.getCurCycle(), pList, output);
			scheduler.runCycle();
		}
		
		output << "\nFinishing time: " << scheduler.getCurCycle() - 1;
		output << "\nCPU utilization: " << static_cast<float>(scheduler.activeCycles) / scheduler.getCurCycle();
		
		for (auto &&p : scheduler.finishedList)
		{
			output << "\nTurnaround process " << p.first << ": " << p.second;
		}
	}
	return 0;
}
