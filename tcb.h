#ifndef TCB_CLASS
#define TCB_CLASS	 

#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

#define SPACE	' ' 

// Task Control Block Class

class Tcb
{
protected:

	unsigned int taskNumber;
	unsigned int taskCpuTime;
	unsigned int memorySize;
	unsigned int burstTime;
	unsigned int blockedTime;
	unsigned int taskTotalCpuTime;
	unsigned int taskWallTimeStart;
	unsigned int taskWallTime;
	unsigned int priority;
	string       taskName;
	bool	     fRunning;

public:
	Tcb()
	{
		taskCpuTime = 0;
		taskTotalCpuTime = 0;
		burstTime = 0;
		taskNumber = 0;
		fRunning = false;
		priority = 0;
		taskName = "";

	}

	Tcb& operator = (Tcb& t)
	{
		taskCpuTime = t.taskCpuTime;
		taskTotalCpuTime = t.taskTotalCpuTime;
		memorySize = t.memorySize;
		burstTime = t.burstTime;
		blockedTime = t.blockedTime;
		taskNumber = t.taskNumber;
		fRunning = t.fRunning;
		taskWallTimeStart = t.taskWallTimeStart;
		taskWallTime = t.taskWallTime;
		priority = t.priority;
		return *this;
	}

	friend ostream& operator << (ostream& out, Tcb& t)
	{

		out << setw(13);
		out << t.taskNumber;
		out << setw(13);
		out << t.memorySize;
		return out;
	}


	bool operator < (Tcb& t)
	{
		return (blockedTime < t.blockedTime);
	}

	bool operator >= (Tcb& t)
	{
		return (blockedTime >= t.blockedTime);
	}

	bool operator == (Tcb& t)
	{
		return (blockedTime == t.blockedTime);
	}

	void setPriority(unsigned int p) { priority = p; }
	void setCpuTime(unsigned int time) { taskCpuTime = time; }
	void setTotalTaskCpuTime(unsigned int time) { taskTotalCpuTime = time; }
	void setMemorySize(unsigned int mem_size) { memorySize = mem_size; }
	void setBurstTime(unsigned int time) { burstTime = time; }
	void setBlockedTime(unsigned int time) { blockedTime = time; }
	void setTaskNumber(unsigned int task) { taskNumber = task; }
	void setTaskWallTime(unsigned int tick) { taskWallTime = tick; }
	void setTaskWallTimeStart(unsigned int tick) { taskWallTimeStart = tick; }
	void setRunning(bool status) { fRunning = status; }
	void setTaskName(string t) { taskName = t; }

	unsigned int  getPriority(void) { return priority; }
	unsigned int  getCpuTime(void) { return taskCpuTime; }
	unsigned int  getTotalTaskCpuTime(void) { return taskTotalCpuTime; }
	unsigned int  getMemorySize(void) { return memorySize; }
	unsigned int  getBurstTime(void) { return burstTime; }
	unsigned int  getBlockedTime(void) { return blockedTime; }
	unsigned int  getTaskNumber(void) { return taskNumber; }
	unsigned int  getTaskWallTime(void) { return taskWallTime; }
	unsigned int  getTaskWallTimeStart(void) { return taskWallTimeStart; }
	bool		  isRunning(void) { return fRunning; }
	bool		  isNotRunning(void) { return !fRunning; }

	string        getTaskName(void) { return taskName; }
};

#endif
