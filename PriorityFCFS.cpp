#include <iostream>
#include <fstream>
#include "priority_fcfs.h"
#include "tcb.h"
#include "list.h"
#include<algorithm>

using namespace std; 

void PriorityFCFS::schedule(List<Tcb>& q, ofstream& outfile)
{
	Tcb running;
	List <Tcb> fcfsReadyQueue, tempQueue;
	ListIterator <Tcb> it(fcfsReadyQueue), tempIt(tempQueue);
	Tcb* ptr = NULL;
	if (started == false)
	{
		started = true;
		/* copy main queue to fcfs queue */
		copyQueue(q, tempQueue);
		ptr = tempIt.First();
		Tcb* cur = ptr;
		Tcb* next = ptr;
		bool unsorted = true;
		int i = 0;
		while (unsorted) {
			unsorted = false;
			cur = ptr;
			while (i < 10) {
				next = tempIt.Next();
				if (next == NULL || cur == NULL) {
					break;
				}
				if (next->getPriority() < cur->getPriority()) {
					swap(cur, next);
					unsorted = true;
				}
				i++;
				cur = next;
			}
		}
		copyQueue(tempQueue, fcfsReadyQueue);
		running = *fcfsReadyQueue.Retrieve();
		ptr = it.First();
	}
	if (started == true)
	{
		outfile << "PRIORITY FCFS" << endl;
		/* the while loop will schedule all of the tasks */
		while (ptr)
		{
			/* run CPU cycle */
			running.setCpuTime(running.getCpuTime() - 1);
			tick++;
			if (running.getCpuTime() == 0)
			{
				/* task is finished    */
				/* set turnaround time */
				running.setTaskWallTime(tick);
				averageWallTime += running.getTaskWallTime();
				cout << "T" << setw(2) << left << running.getTaskNumber()
					<< " WallTime = " << setw(5) << left << running.getTaskWallTime()
					<< " cpuTime =  " << setw(5) << left << running.getTotalTaskCpuTime()
					<< "  %cpuTime/wallTime = " << setprecision(2) << setw(7) << fixed << left << (static_cast <float>(running.getTotalTaskCpuTime()) / running.getTaskWallTime()) * 100.0f
					<< "  tick = " << setw(5) << left << tick << endl;

				outfile.setf(ios::fixed, ios::left);
				outfile << setprecision(2);
				outfile << setw(10) << left << running.getTaskNumber()
					<< setw(14) << left << running.getTaskWallTime()
					<< setw(13) << left << running.getTotalTaskCpuTime()
					<< setw(15) << left << fixed << (static_cast <float>(running.getTotalTaskCpuTime()) / running.getTaskWallTime()) * 100.0f
					<< setw(3) << tick << endl;

				/* get the next task from the queue */
				fcfsReadyQueue.Delete(*ptr);
				/* get the next task */
				ptr = it.First();
				if (ptr)
				{
					running = *fcfsReadyQueue.Retrieve();
				}
				else
				{
					done = true;
				}
			}
		}
		done = true;
	}
	cout << "\nAverage Wall Time for Priority FCFS = " << fixed << static_cast<float> (averageWallTime) / 10.0 << endl;
};


