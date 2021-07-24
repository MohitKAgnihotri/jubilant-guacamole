#pragma once
#include "tcb.h"
#include <ostream>
#include "list.h"

class Priority
{
protected:
	bool done;
	bool started;

	unsigned int tick;
	unsigned int averageWallTime;


public:
	Priority()
	{
		done = false;
		started = false;
		tick = 0;
		averageWallTime = 0;
	}
	~Priority() { ; }

	virtual void schedule(List<Tcb>& q, ofstream& outfile);

	bool isDone() { return (done); }
	bool isNotDone() { return (!done); }
	bool isStarted() { return (started); }
	bool isNotStarted() { return (!started); }
    Tcb* getTcbWithPriority (List <Tcb> &priorityReadyQueue);

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

