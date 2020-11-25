#ifndef LAB_2_FCFS_HPP
#define LAB_2_FCFS_HPP

#include <deque>
#include <vector>
#include "Scheduler.hpp"

class FCFS : public Scheduler
{
protected:
	std::deque<Process *> readyQueue;

public:
	explicit FCFS(std::vector<Process> &processes);

protected:
	void readyProcesses() override;
	void processSwitch() override;
	void updateRunningProcess() override;
};


#endif //LAB_2_FCFS_HPP
