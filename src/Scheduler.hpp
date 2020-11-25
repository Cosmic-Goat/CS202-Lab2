#ifndef LAB_2_SCHEDULER_HPP
#define LAB_2_SCHEDULER_HPP

#include "Process.hpp"

class Scheduler
{
	using pTimePair = std::pair<size_t, Process *>;
private:
	std::vector<Process> &processes;
	std::priority_queue<pTimePair, std::vector<pTimePair>, std::greater<>> blockedList;
	std::deque<Process *> readyQueue;
	Process *running = nullptr;
	
	size_t curCycle = 0;
	
	void readyProcesses();
	
	void processSwitch();
	
	void updateRunningProcess();

public:
	size_t activeCycles = 0;
	std::map<PID, const size_t> finishedList;
	
	explicit Scheduler(std::vector<Process> &processes);
	
	inline size_t getCurCycle() const
	{ return curCycle - 1; }
	
	void runCycle();
	
	inline bool isRunning() const
	{ return finishedList.size() < processes.size(); }
};

#endif //LAB_2_SCHEDULER_HPP
