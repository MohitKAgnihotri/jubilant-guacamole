#ifndef OS_DEFS
#define OS_DEFS

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fcfs.h"
#include "round_robin.h"
#include "priority.h"
#include "priority_fcfs.h"
#include "SJF.h"
#include "list.h"
#include "tcb.h"

using namespace std;

#define MAX_LOWER_BURST_TIME	 20
#define MIN_LOWER_BURST_TIME	 1

#define MAX_UPPER_BURST_TIME	150
#define MIN_UPPER_BURST_TIME	15


#define MAX_CPU_TIME			50 
#define MIN_CPU_TIME			1  

#define MAX_QUEUE_SIZE			10
#define MAX_TASKS				10

#define MAX_PRIORITY            10
#define MIN_PRIORITY            1

ofstream outFile("proj3_1.out", ios::out);


class OsTask
{
protected:

	List <Tcb> tempQueueL;  /* generate new tasks */

	bool         done;

	unsigned int tick;	    /* absolute time since start of simulation  */
							/* this is good for 1193.04 hours since     */
							/* unsigned int is 4 bytes long and         */
							/* if 1 tick  = 1 ms                        */

	unsigned int taskNumber;	/* task number 1-10             */

	string taskName;
	Tcb tcbRunning; 			      /* running task           */
	Tcb tcb;					      /* task control block     */
	Tcb* tptr;				          /* pointer to tcb class   */

	FCFS fcfs;
	Priority priority;
	PriorityFCFS priorityfcfs;
	SJF sjf;
	Round_Robin roundrobin;
public:

	OsTask()
	{
		//srand((unsigned)time(NULL));
		srand(1);
		tick = 0;
		taskNumber = 1;
		tptr = &tcb;

		done = false;

		generateRandomTasks(4);
		outFile << left;
		outFile << setw(9) << "taskName" << SPACE;
		outFile << setw(13) << "taskWallTime" << SPACE;
		outFile << setw(12) << "taskCpuTime" << SPACE;
		outFile << setw(14) << "cpu/WalLTime%" << SPACE;
		outFile << setw(5) << "tick" << endl;
		outFile << "--------------------------------------------------------" << endl;
	}

	~OsTask() { ; }

	unsigned int getTick(void) { return tick; }

	void generateNewTCB(Tcb* t)
	{
		unsigned int temp;

		temp = ((rand()) % (MAX_CPU_TIME - MIN_CPU_TIME)) + MIN_CPU_TIME;
		t->setCpuTime(temp);
		t->setTotalTaskCpuTime(temp);
		temp = ((rand()) % (MAX_PRIORITY - MIN_PRIORITY)) + MIN_PRIORITY;
		t->setPriority(temp);

		temp = ((rand()) % (MAX_UPPER_BURST_TIME - MIN_UPPER_BURST_TIME)) + (MAX_LOWER_BURST_TIME-MIN_LOWER_BURST_TIME);
		t->setBurstTime(temp);
		/* all tasks are created at the same time */
		t->setTaskWallTimeStart(0);
		return;
	}

	unsigned int generateRandomTime(unsigned int max_upper,
		unsigned int min_upper,
		unsigned int max_lower,
		unsigned int min_lower)
	{
		unsigned int temp, upper, lower;

		do
		{
			upper = ((rand()) % (max_upper - min_upper)) + min_upper;
			lower = ((rand()) % (max_lower - min_lower)) + min_lower;
		} while (upper <= lower);

		// now generate the actual time
		temp = ((rand()) % (upper - lower)) + lower;
		return (temp);
	}

	/* generate 10 random tasks */
	void generateRandomTasks(unsigned int count)
	{
		Tcb tcb;

		for (unsigned int i = 0; i < count; i++)
		{

			generateNewTCB(&tcb);
			tcb.setTaskNumber(taskNumber++);
			tcb.setTaskName("T" + taskNumber);
			tempQueueL.InsertSorted(tcb);
		}

	}
	void schedule()
	{
		if (fcfs.isDone() == false)
		{
			fcfs.schedule(tempQueueL, outFile);
		}
		if (roundrobin.isDone() == false)
		{
			roundrobin.schedule(tempQueueL, outFile);
		}
		if (priority.isDone() == false)
		{
			//priority.schedule(tempQueueL, outFile);
		}
		if (priorityfcfs.isDone() == false)
		{
			//priorityfcfs.schedule(tempQueueL, outFile);
		}
		if (sjf.isDone() == false)
		{
			sjf.schedule(tempQueueL, outFile);
		}
		done = true;
	}
	bool isDone() { return done; }
	bool isNotDone() { return !done; }
};


#endif







