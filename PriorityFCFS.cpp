#include <iostream>
#include <fstream>
#include "priority_fcfs.h"
#include "tcb.h"
#include "list.h"
#include<algorithm>

using namespace std;

Tcb* PriorityFCFS::getTcbWithPriority (List <Tcb> &priorityReadyQueue)
{
    ListIterator <Tcb> it(priorityReadyQueue);
    Tcb *highestPriority = NULL;
    Tcb *currentPriority = NULL;
    highestPriority = it.Next();
    currentPriority = highestPriority;
    while(currentPriority != NULL)
    {
        if (highestPriority->getPriority()  >= currentPriority->getPriority())
        {
            highestPriority = currentPriority;
        }
        currentPriority = it.Next();
    }
    return highestPriority;
}

void PriorityFCFS::schedule(List<Tcb>& q, ofstream& outfile)
{
	Tcb *running;
	List <Tcb> fcfspriorityReadyQueue;
	ListIterator <Tcb> it(fcfspriorityReadyQueue);
	Tcb* ptr = NULL;
    if (started == false)
    {
        started = true;
        /* copy main queue to priority queue */
        copyQueue(q, fcfspriorityReadyQueue);
    }
    if (started)
    {
        outfile << "PRIORITY" << endl;
        /* the while loop will schedule all of the tasks */
        while (fcfspriorityReadyQueue.isNotEmpty())
        {
            running = getTcbWithPriority(fcfspriorityReadyQueue);
            /* run CPU cycle */
            running->setTotalTaskCpuTime(running->getCpuTime());
            tick += running->getCpuTime();
            running->setCpuTime(0);

            /* task is finished    */
            /* set turnaround time */
            running->setTaskWallTime(tick);
            averageWallTime += running->getTaskWallTime();
            cout << "T" << setw(2) << left << running->getTaskNumber()
                 << " WallTime = " << setw(5) << left << running->getTaskWallTime()
                 << " cpuTime =  " << setw(5) << left << running->getTotalTaskCpuTime()
                 << "  %cpuTime/wallTime = " << setprecision(2) << setw(7) << fixed << left << (static_cast <float>(running->getTotalTaskCpuTime()) / running->getTaskWallTime()) * 100.0f
                 << "  tick = " << setw(5) << left << tick << endl;

            outfile.setf(ios::fixed, ios::left);
            outfile << setprecision(2);
            outfile << setw(10) << left << running->getTaskNumber()
                    << setw(14) << left << running->getTaskWallTime()
                    << setw(13) << left << running->getTotalTaskCpuTime()
                    << setw(15) << left << fixed << (static_cast <float>(running->getTotalTaskCpuTime()) / running->getTaskWallTime()) * 100.0f
                    << setw(3) << tick << endl;

            /* get the next task from the queue */
            fcfspriorityReadyQueue.Delete(*running);
        }
        done = true;
    }
	cout << "\nAverage Wall Time for Priority FCFS = " << fixed << static_cast<float> (averageWallTime) / 10.0 << endl;
};


