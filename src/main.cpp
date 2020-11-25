#include <fstream>
#include <iomanip>
#include "Scheduler.hpp"
#include "FCFS.hpp"
#include "RoundRobin.hpp"
#include "SRJF.hpp"


void TimingSnapshot(const size_t cycle, std::ostream &output, std::vector<Process> &processes)
{
	constexpr std::string_view STATE_STRINGS[] = {"running", "ready", "blocked"};
	output << cycle << " ";
	for (auto &&p : processes)
	{
		if (p.state != Process::Inactive) output << p.id << ":" << STATE_STRINGS[p.state] << " ";
	}
	output << "\n";
}

template<typename T>
static void run(std::ostream &output, std::vector<Process> &processes)
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
	
	output << std::endl;
}

int main(int argc, char *argv[])
{
	std::vector<Process> processes;
	
	std::string file(argv[1]);
	
	std::ifstream input(file);
	std::ofstream output;
	output.open(file.erase(file.length() - 4) + "-" + std::string(argv[2]) + ".txt");
	output << std::fixed;
	output << std::setprecision(2);
	
	if (input.is_open() && output.is_open())
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
		
		input.close();
		
		constexpr auto a = &run<FCFS>; //, &run<RoundRobin>};
		
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
		
		output.close();
	}
}
