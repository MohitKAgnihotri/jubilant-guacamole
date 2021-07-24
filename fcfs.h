#pragma once

#include <ostream>
#include "list.h"
#include "tcb.h"


using namespace std;

class FCFS
{
protected:
	bool done;
	bool started;

	unsigned int tick;
	unsigned int averageWallTime;


public:
	FCFS()
	{
		done = false;
		started = false;
		tick = 0;
		averageWallTime = 0;
	}
	~FCFS() { ; }

	virtual void schedule(List<Tcb>& q, ofstream& outfile);

	bool isDone() { return (done); }
	bool isNotDone() { return (!done); }
	bool isStarted() { return (started); }
	bool isNotStarted() { return (!started); }

	void copyQueue(List<Tcb>& from, List<Tcb>& to)
	{

		ListIterator <Tcb> ito(from);
		Tcb* ptr = ito.First();
		while (ptr)
		{

			to.InsertAtEnd(*ptr);
			ptr = ito.Next();
		}
	}
};


