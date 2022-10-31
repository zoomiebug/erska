/*
	Level 5: gwthd_exit and gwthd_join properly synchronize between child thread exit, 
		and parent thread blocking and resumption.
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