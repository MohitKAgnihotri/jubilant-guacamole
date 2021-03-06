#pragma once
#include "tcb.h"
#include <ostream>
#include "list.h"
class SJF
{
protected:
	bool done;
	bool started;

	unsigned int tick;
	unsigned int averageWallTime;


public:
	SJF()
	{
		done = false;
		started = false;
		tick = 0;
		averageWallTime = 0;
	}
	~SJF() { ; }

	virtual void schedule(List<Tcb>& q, ofstream& outfile);

	bool isDone() { return (done); }
	bool isNotDone() { return (!done); }
	bool isStarted() { return (started); }
	bool isNotStarted() { return (!started); }
    Tcb* getTcbWithShortestCPUTime(List <Tcb> &sjfReadyQueue);
	void copyQueue(List<Tcb>& from, List<Tcb>& to)
	{

        ListIterator <Tcb> ito(from);
        Tcb* ptr = ito.Next();
        while (ptr)
        {

            to.InsertAtEnd(*ptr);
            ptr = ito.Next();
        }
	}
};

