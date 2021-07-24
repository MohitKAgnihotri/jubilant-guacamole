#include <iostream>
#include <fstream>
#include "round_robin.h"
#include "tcb.h"
#include "list.h"

using namespace std;

void Round_Robin::schedule(List<Tcb> &q, ofstream &outfile) {
    int quantum = 10;
    Tcb *running;
    List<Tcb> fcfsReadyQueue;
    ListIterator<Tcb> it(fcfsReadyQueue);
    Tcb *ptr = NULL;

    if (!started) {
        started = true;
        copyQueue(q, fcfsReadyQueue);
    }

    while (!fcfsReadyQueue.isEmpty()) {
        it.Reset();
        running = it.Next();

        // iterate through the whole list
        while (running != NULL) {
            if (running->getBurstTime() >= quantum) {
                unsigned int burst_time = running->getBurstTime() - quantum;
                running->setBurstTime(burst_time > 0 ? burst_time : 0);
                running->setTotalTaskCpuTime(running->getTotalTaskCpuTime() + quantum);
                tick += quantum;
                running = it.Next();
            } else {

                tick += running->getBurstTime();
                running->setTotalTaskCpuTime(running->getTotalTaskCpuTime() + running->getBurstTime() + running->getCpuTime());
                running->setBurstTime(0);

                /* task is finished    */
                /* set turnaround time */
                running->setTaskWallTime(tick);
                averageWallTime += running->getTaskWallTime();
                cout << "T" << setw(2) << left << running->getTaskNumber()
                     << " WallTime = " << setw(5) << left << running->getTaskWallTime()
                     << " cpuTime =  " << setw(5) << left << running->getTotalTaskCpuTime()
                     << "  %cpuTime/wallTime = " << setprecision(2) << setw(7) << fixed << left
                     << (static_cast <float>(running->getTotalTaskCpuTime()) / running->getTaskWallTime()) * 100.0f
                     << "  tick = " << setw(5) << left << tick << endl;

                outfile.setf(ios::fixed, ios::left);
                outfile << setprecision(2);
                outfile << setw(10) << left << running->getTaskNumber()
                        << setw(14) << left << running->getTaskWallTime()
                        << setw(13) << left << running->getTotalTaskCpuTime()
                        << setw(15) << left << fixed
                        << (static_cast <float>(running->getTotalTaskCpuTime()) / running->getTaskWallTime()) * 100.0f
                        << setw(3) << tick << endl;

                fcfsReadyQueue.Delete(*running);
                running = it.Next();
            }
        }
    }
    cout << "\nAverage Wall Time for Round_Robin = " << fixed << static_cast<float> (averageWallTime) / 10.0 << endl;
}


