/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosPThreadCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosPThreadCreate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosPThreadCreate ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"

#include "../inc/eosPThread.h"


int
eosPThreadCreateOnWaitingThread(eosPThread* t, void* (*start_routine)(void *), void * arg, int mode)
{
	int i;

	while(1) { 
		for(i=0; i<t->max; i++) {
			if( t->status[i] == eosPThreadStatusWaiting) {
				eosPThreadCreate(t, i, start_routine, arg, mode);
				return 0;
			} 
		}
	}
	return -1;
}

int
eosPThreadCreate(eosPThread* t, int i, void* (*start_routine)(void *), void * arg, int mode)
{
	int status;

	DEBUGPRINT("eosPThreadCreate\n");
	if( t->status[i] == eosPThreadStatusRunning) {
		DEBUGPRINT2("ID: $d threadID: %x pthread_join in eosPThreadCreate\n", i, t->th[i]);
		eosPThreadJoin(t, i, mode);
	} 
	status = pthread_create(&(t->th[i]), NULL, start_routine, arg);
	DEBUGPRINT1("%d\n", status);
	switch(status) {
		case 0: {
			t->status[i] = eosPThreadStatusRunning; 
			t->count++;
			t->id[i]  = t->count;
			t->latest = t->count;
			if(t->oldest==0) t->oldest = t->count;

			DEBUGPRINT2("ID: %d ThreadID: %p in pthread_create\n", i, t->th[i]);
			break;
		}
		case EINVAL: {
			perror("eosPThreadCreate");
			fprintf(stderr, "The value specified by attr is invalid.\n");
			exit(EXIT_FAILURE);
			break;
		}
		case EAGAIN: {
			perror("eosPThreadCreate");
			fprintf(stderr, "The system locked the necessary resources to create another thread, \n");
			fprintf(stderr, "or the system-imposed limit on the total number of threads in a process would be exceeded.\n");
			exit(EXIT_FAILURE);
			break;
		}

		default: {
			fprintf(stderr, "Something wrong\n");
			exit(EXIT_FAILURE);
			break;
		}
	}
	return status;
}
