#include <fstream>
#include <iomanip>
#include "Scheduler.hpp"
#include "FCFS.hpp"
#include "RoundRobin.hpp"
#include "SRJF.hpp"

static void TimingSnapshot(const size_t cycle, std::vector<Process> &processes, std::ostream &output)
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
static void run(std::vector<Process> &processes, std::ostream &output)
{
	T scheduler(processes);
	scheduler.runCycle();
	while (scheduler.isRunning())
	{
		TimingSnapshot(scheduler.getCurCycle(), processes, output);
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

template<typename... Ts>
constexpr void runScheduler(int algorithm, Ts &... args)
{
	constexpr void (*algoList[])(std::vector<Process> &, std::ostream &) = {run<FCFS>, run<RoundRobin>, run<SRJF>};
	algoList[algorithm](args...);
}

int main(int argc, char *argv[])
{
	std::string file(argv[1]);
	std::ifstream input(file);
	std::ofstream output;
	output.open(file.erase(file.length() - 4) + "-" + std::string(argv[2]) + ".txt");
	output << std::fixed << std::setprecision(2);
	
	if (input.is_open() && output.is_open())
	{
		size_t num;
		input >> num;
		
		std::vector<Process> processes(num);
		for (auto &p : processes) input >> p.id >> p.cpuTime >> p.ioTime >> p.arrival;
		
		runScheduler(std::stoi(argv[2]), processes, output);
		
		input.close();
		output.close();
	}
}
