#include <filesystem>
#include <fstream>
#include "Scheduler.hpp"
#include "FCFS.hpp"
#include "RoundRobin.hpp"
#include "SRJF.hpp"

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

template<typename T>
void run(std::ostream &output, std::vector<Process> &processes)
{
	T scheduler(processes);
	scheduler.runCycle();
	while (scheduler.isRunning())
	{
		TimingSnapshot(scheduler.getCurCycle(), output, processes);
		scheduler.runCycle();
	}
	
	output << "\nFinishing time: " << scheduler.getCurCycle() - 1;
	output << "\nCPU utilization: " << static_cast<float>(scheduler.activeCycles) / scheduler.getCurCycle();
	
	for (auto &&p : scheduler.finishedList)
	{
		output << "\nTurnaround process " << p.first << ": " << p.second;
	}
}

int main(int argc, char *argv[])
{
	std::vector<Process> processes;
	
	std::filesystem::path p(argv[1]);
	
	std::ifstream input(p);
	std::ofstream output;
	output.open(p.stem().string() + "------" + std::string(argv[2]) + ".txt");
	output << std::fixed;
	output << std::setprecision(2);
	
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
		
		switch (std::stoi(argv[2]))
		{
			case 0:
				run<FCFS>(output, processes);
				break;
			case 1:
				run<RoundRobin>(output, processes);
				break;
			case 2:
				run<SRJF>(output, processes);
				break;
		}
	}
	return 0;
}
