#include <iostream>
#include <fstream>
#include "round_robin.h"
#include "tcb.h"
#include "list.h"

using namespace std;

void Round_Robin::schedule(List<Tcb> &q, ofstream &outfile) {
    int quantum = 10;
    Tcb *running;
    List<Tcb> rr_queue;
    ListIterator<Tcb> it(rr_queue);
    Tcb *ptr = NULL;

    if (!started) {
        started = true;
        copyQueue(q, rr_queue);
    }

    while (!rr_queue.isEmpty()) {
        it.Reset();
        running = it.Next();

        // iterate through the whole list
        while (running != NULL) {
            if (running->getCpuTime() >= quantum) {
                unsigned int new_cpu_time = running->getCpuTime() - quantum;
                running->setCpuTime(new_cpu_time);
                running->setTotalTaskCpuTime(running->getTotalTaskCpuTime() + quantum);
                tick += quantum;
                running = it.Next();
            } else {

                tick += running->getCpuTime();
                running->setTotalTaskCpuTime(running->getTotalTaskCpuTime() + running->getCpuTime());
                running->setCpuTime(0);

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

                rr_queue.Delete(*running);
                running = it.Next();
            }
        }
    }
    cout << "\nAverage Wall Time for Round_Robin = " << fixed << static_cast<float> (averageWallTime) / 10.0 << endl;
}


