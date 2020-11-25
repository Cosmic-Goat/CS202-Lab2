#ifndef LAB_2_ROUNDROBIN_HPP
#define LAB_2_ROUNDROBIN_HPP

#include "FCFS.hpp"

class RoundRobin : public FCFS
{
protected:
	static constexpr size_t quantum = 2;
	size_t qRunTime = 0;
	
	void updateRunningProcess() override;

public:
	explicit RoundRobin(std::vector<Process> &processes);
	
	void switchProcess();
};

#endif //LAB_2_ROUNDROBIN_HPP
