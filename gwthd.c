#include "gwthd.h"
#include "types.h"
#include "stat.h"
#include "user.h"

#define STACK_MEM 4096
#define NULL 0
/*	
	gwthd_create creates a new thread that executes the function pointer passed in (fn), 
		and passes the data to it as an argument. 
	It returns 0 on success, and -1 otherwise (in cases similar to when fork returns error). 
	If it returns success, the childid variable is set to the new thread's (the child's) identifier. 
	Each thread shares the address space of the thread that created it.
*/

int     
gwthd_create(gwthd_t *childid, gwthd_fn_t fn, void *data) {
	// printf(1,"> gwthd_create\n");

	// allocating doubled memory space in order to shift the stack_heap into a multiple of 4096
	void *stack_heap = malloc(STACK_MEM*2);
	if (stack_heap == NULL) {
		// Malloc failure
		return -1;
	}
		
	// shifting stack_heap to a multiple of 4096
	if((uint)stack_heap % STACK_MEM) {
		stack_heap = stack_heap + (STACK_MEM - (uint)stack_heap % STACK_MEM);
	}

	// clone the 
	*childid = clone(fn, data, stack_heap);
	return 0; 
}

/*
	gwthd_exit kills the current thread. 
	You should never return from the function executed for a thread. 
	Instead, always call gwthd_exit to terminate the thread.
*/
void    
gwthd_exit(void) {
	// printf(1,"> gwthd_exit\n");
	exit();
}

/* 
	gwthd_join is executed by a parent, who passes the gwthd_id of the child they want to wait to terminate execution. 
	Joining is similar to wait in xv6 (though it is closer to waitpid in systems like Linux) in that it serves two purposes. 
	First, it allows the parent to block waiting for the child to terminate at which point the parent will continue executing. 
	Second, since the child must have gwthd_exited at this point, 
		it allows the kernel to reclaim and reuse that thread id since a parent can no longer be waiting for it. 
	This returns 0 when successful, and -1 if you pass in a gwthd_t that is not appropriate.

	child: the id of thread want to wait and join
*/
int     
gwthd_join(gwthd_t childid) {
	// printf(1,"> gwthd_join\n");

	void* ustack;
  	int thread_id = join(&ustack, childid);
  	if (thread_id != -1) {
    	free(ustack);
  	} else {
		// if childid is not appropriate
		return -1;
	}
  
	return 0;
}

/*
	gwthd_id is simple: return the current thread's gwthd_t identifier. 
	You should be able to call this function from both processes and threads, 
		and it should always return a unique id (i.e. no other process or thread has the same id).
*/
gwthd_t 
gwthd_id(void) {
	// printf(1,"> gwthd_id\n");
	gwthd_t id;

	get_gwthd_id(&id);
	return id;

}

/* Supported function */
int test(int n) {
	printf(1,"Number = %d\n",n);
	return 0;
}