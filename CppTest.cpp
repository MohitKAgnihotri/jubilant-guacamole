
#include <fstream>
#include <iomanip>
#include <time.h>

#include "list.h"
#include "tcb.h"
#include "os.h"


int  main()
{
	OsTask	os;
	do
	{
		os.schedule();
	} while (os.isNotDone());
	system("pause");
}

