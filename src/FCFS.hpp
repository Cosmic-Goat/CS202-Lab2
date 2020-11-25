#ifndef LAB_2_FCFS_HPP
#define LAB_2_FCFS_HPP

#include "Scheduler.hpp"

class FCFS : public Scheduler
{
protected:
	std::deque<Process *> readyQueue;
	
	void switchProcess() override;
	
	void readyProcess(Process *p) override;

public:
	explicit FCFS(std::vector<Process> &processes);
};


#endif //LAB_2_FCFS_HPP
