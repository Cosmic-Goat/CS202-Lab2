#ifndef LAB_2_FCFS_HPP
#define LAB_2_FCFS_HPP

#include <deque>
#include <vector>
#include "Scheduler.hpp"

class FCFS : public Scheduler
{
protected:
	std::deque<Process *> readyQueue;
	
	void readyProcesses() override;
	
	void processSwitch() override;

public:
	explicit FCFS(std::vector<Process> &processes);
	
	void readyProcess(Process *p);
};


#endif //LAB_2_FCFS_HPP
