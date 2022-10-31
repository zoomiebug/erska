/*
	Level 6: Correct error values are passed when processes call thread functions, 
		and threads call process functions. This includes (but is not limited to) 
		processes calling gwthd_exit, and threads calling exit. 
		Note that some functions return void, and thus cannot return an error code. 
		Instead, they should act appropriately, for example, if exit is called from a thread, 
		instead of exiting, it should return. Similarly, if fork is called from a child thread, 
		an error should be returned.
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