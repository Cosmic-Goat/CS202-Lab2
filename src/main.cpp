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
#include "Process.hpp"
#include "Scheduler.hpp"
#include "FCFS.hpp"

void TimingSnapshot(const size_t cycle, std::ostream &output, std::vector<Process> &processes)
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
//
//void run(Scheduler &scheduler, std::ostream &output, std::vector<Process> &processes)
//{
//	scheduler.runCycle();
//	while (scheduler.isRunning())
//	{
//		TimingSnapshot(scheduler.getCurCycle(), output, processes);
//		scheduler.runCycle();
//	}
//
//	output << "\nFinishing time: " << scheduler.getCurCycle() - 1;
//	output << "\nCPU utilization: " << static_cast<float>(scheduler.activeCycles) / scheduler.getCurCycle();
//
//	for (auto &&p : scheduler.finishedList)
//	{
//		output << "\nTurnaround process " << p.first << ": " << p.second;
//	}
//}

int main(int argc, char *argv[])
{
	std::ifstream input(argv[1]);
	std::ostream &output = std::cout;
	std::vector<Process> processes;
	
	if (input.is_open())
	{
		size_t num;
		input >> num;
		
		processes.reserve(num);
		
		for (int i = 0; i < num; ++i)
		{
			size_t id, cpuTime, ioTime, arrival;
			input >> id >> cpuTime >> ioTime >> arrival;
			processes.emplace_back(id, cpuTime, ioTime, arrival);
		}
	
		std::unique_ptr<Scheduler> scheduler;
		
		switch (std::stoi(argv[2]))
		{
			case 0:
				scheduler = std::make_unique<FCFS>(processes);
				break;
		}
		
		scheduler->runCycle();
		while (scheduler->isRunning())
		{
			TimingSnapshot(scheduler->getCurCycle(), output, processes);
			scheduler->runCycle();
		}
		
		output << "\nFinishing time: " << scheduler->getCurCycle() - 1;
		output << "\nCPU utilization: " << static_cast<float>(scheduler->activeCycles) / scheduler->getCurCycle();
		
		for (auto &&p : scheduler->finishedList)
		{
			output << "\nTurnaround process " << p.first << ": " << p.second;
		}
	}
	return 0;
}
