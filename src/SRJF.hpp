#ifndef LAB_2_SRJF_HPP
#define LAB_2_SRJF_HPP

#include "Scheduler.hpp"

class SRJF : public Scheduler
{
	std::priority_queue<pTimePair, std::vector<pTimePair>, std::greater<>> readyQueue;
	
	void switchProcess() override;
	
	void readyProcess(Process *p) override;

public:
	explicit SRJF(std::vector<Process> &processes);
	
	void updateRunningProcess() override;
};


#endif //LAB_2_SRJF_HPP
