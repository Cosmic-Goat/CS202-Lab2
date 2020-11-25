#ifndef LAB_2_SCHEDULER_HPP
#define LAB_2_SCHEDULER_HPP

#include <queue>
#include <map>
#include <deque>
#include <vector>
#include "Process.hpp"

class Scheduler
{
protected:
	using pTimePair = std::pair<size_t, Process *>;
	std::vector<Process> &processes;
	std::priority_queue<pTimePair, std::vector<pTimePair>, std::greater<>> blockedList;
	Process *running = nullptr;
	size_t curCycle = 0;
	
	virtual void processSwitch() = 0;
	
	virtual void updateRunningProcess();
	
	void readyProcesses();
	
	virtual void readyProcess(Process *p) = 0;
	
	void blockProcess(Process *&p);
	
	void terminateProcess(Process *&p);

public:
	size_t activeCycles = 0;
	std::map<PID, const size_t> finishedList;
	
	explicit Scheduler(std::vector<Process> &processes);
	
	void runCycle();
	
	inline size_t getCurCycle() const
	{ return curCycle - 1; }
	
	inline bool isRunning() const
	{ return finishedList.size() < processes.size(); }
	
	
};

#endif //LAB_2_SCHEDULER_HPP
