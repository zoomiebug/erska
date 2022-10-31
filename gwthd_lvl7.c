/*
	Level 7: Properly deallocate a gwthd_exited thread's stack. 
		You cannot free memory that you are using for current execution, 
		so this is a little complicated. To test this, 
		you can assume that if a stack is the only allocated memory, 
		then it is freed, and reallocated, you will get the same address of the initial allocation. 
*/

#include "gwthd.h"
#include "types.h"
#include "user.h"

void *
thread_fn(void *data)
{
	int arg = (int)data;

	printf(1, "argument to new thread %d is %d\n", gwthd_id(), (int)arg);

	gwthd_exit();
	return 0;
}

int
main(void)
{
	gwthd_t gwt;

	printf(1, "Starting up the main thread\n");

	if (gwthd_create(&gwt, thread_fn, (void *)42)) exit();
	gwthd_join(gwt);

	printf(1, "back in main thread\n");
	exit();
}