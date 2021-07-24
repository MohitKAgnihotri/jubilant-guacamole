#include <iostream>
#include <fstream>
#include "round_robin.h"
#include "tcb.h"
#include "list.h"

using namespace std;

void Round_Robin::schedule(List<Tcb>& q, ofstream& outfile)
{
	int quantum = 10;
	Tcb running;
	List <Tcb> fcfsReadyQueue;
	ListIterator <Tcb> it(fcfsReadyQueue);
	Tcb* ptr = NULL;
	if (started == false)
	{
		started = true;
		/* copy main queue to fcfs queue */
		copyQueue(q, fcfsReadyQueue);
		running = *fcfsReadyQueue.Retrieve();
		ptr = it.First();
	}
	if (started == true)
	{
		outfile << "ROUND ROBIN" << endl;
		/* the while loop will schedule all of the tasks */
		while (true)
		{
			done = true;
			while (ptr)
			{
				if (running.getBurstTime() > 0)
				{
					done = false; // There is a pending process

					/* run CPU cycle */
					running.setCpuTime(running.getCpuTime() - quantum);
					if (running.getBurstTime() > quantum)
					{
						// how much time a process has been processed
						tick += quantum;

						// Decrease the burst_time of current process
						// by quantum
						running.setBurstTime(running.getBurstTime() - quantum);
					}

					// If burst time is smaller than or equal to
					// quantum. Last cycle for this process
					else
					{
						// how much time a process has been processed
						tick += running.getBurstTime();

						// Waiting time is current time minus time
						// used by this process
						//ptr->setTaskWallTime(tick - ptr->getBurstTime());

						// As the process gets fully executed
						// make its remaining burst time = 0
						running.setBurstTime(0);

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

					}
				}
			}
			done = true;
			break;
		}
		done = true;
	}
	cout << "\nAverage Wall Time for Round_Robin = " << fixed << static_cast<float> (averageWallTime) / 10.0 << endl;
};


