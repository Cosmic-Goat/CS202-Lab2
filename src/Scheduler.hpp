#ifndef LAB_2_SCHEDULER_HPP
#define LAB_2_SCHEDULER_HPP

#include <vector>
#include <queue>
#include <map>

struct Process
{
	size_t id{}, cpuTime{}, ioTime{}, arrival{};
	size_t elapsedCpu = 0;
	
	constexpr size_t ioStart() const
	{ return cpuTime / 2 + (cpuTime % 2 != 0); }
	
	enum State
	{
		Running, Ready, Blocked, Inactive
	} state{Inactive};
};

class Scheduler
{
protected:
	using pTimePair = std::pair<size_t, Process *>;
	std::vector<Process> &processes;
	std::priority_queue<pTimePair, std::vector<pTimePair>, std::greater<>> blockedList;
	Process *running = nullptr;
	size_t curCycle = 0;
	
	void updateBlocked();
	
	virtual void updateRunningProcess();
	
	virtual void readyProcess(Process *p) = 0;
	
	virtual void switchProcess() = 0;
	
	void blockProcess(Process *&p);
	
	void terminateProcess(Process *&p);
	
	virtual constexpr bool hasReadyProcess() = 0;

public:
	size_t activeCycles = 0;
	std::map<const size_t, const size_t> finishedList;
	
	explicit Scheduler(std::vector<Process> &processes);
	
	void runCycle();
	
	constexpr size_t getCurCycle() const
	{ return curCycle - 1; }
	
	inline bool isRunning() const
	{ return finishedList.size() < processes.size(); }
};

#endif //LAB_2_SCHEDULER_HPP
