#ifndef LAB_2_PROCESS_HPP
#define LAB_2_PROCESS_HPP

using PID = const size_t;

struct Process
{
	PID id;
	const size_t cpuTime, ioTime, arrival;
	const size_t ioStart = cpuTime / 2 + (cpuTime % 2 != 0);
	size_t elapsedCpu = 0;
	
	enum State
	{
		running, ready, blocked, inactive
	} state{inactive};
	
	Process(const PID id, const size_t cpuTime, const size_t ioTime, const size_t arrival) : id(id),
	                                                                                         cpuTime(cpuTime),
	                                                                                         ioTime(ioTime),
	                                                                                         arrival(arrival)
	{}
};

#endif //LAB_2_PROCESS_HPP
