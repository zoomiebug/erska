#include "gwthd.h"
#include "types.h"
#include "user.h"

void *
thread_fn(void *data)
{
	int arg = (int)data;

	printf(1, "sleep for %d seconds\n", arg);
	sleep(arg*100);
	printf(1, "done sleeping for %d seconds\n", arg);
	gwthd_exit();
	return 0;
}

int
main(void)
{
	gwthd_t gwt, gwt2;

	printf(1, "Starting up the main thread\n");

	if (gwthd_create(&gwt, thread_fn, (void *)5)) exit();
	if (gwthd_create(&gwt2, thread_fn, (void *)3)) exit();
	gwthd_join(gwt);
	gwthd_join(gwt2);

	printf(1, "back in main thread\n");
	exit();
}
