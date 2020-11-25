#ifndef LAB_2_SCHEDULER_HPP
#define LAB_2_SCHEDULER_HPP

#include <vector>
#include <queue>
#include <map>

using PID = const size_t;

struct Process
{
	PID id;
	const size_t cpuTime, ioTime, arrival;
	const size_t ioStart = cpuTime / 2 + (cpuTime % 2 != 0);
	size_t elapsedCpu = 0;
	
	enum State
	{
		Running, Ready, Blocked, Inactive
	} state{Inactive};
	
	Process(const PID id, const size_t cpuTime, const size_t ioTime, const size_t arrival) : id(id),
	                                                                                         cpuTime(cpuTime),
	                                                                                         ioTime(ioTime),
	                                                                                         arrival(arrival)
	{}
};

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
