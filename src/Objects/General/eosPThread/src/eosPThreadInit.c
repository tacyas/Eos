/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosPThreadInit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosPThreadInit 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosPThreadInit ver%I%; Date:%D% %Z%";
#ifdef __cplusepluse
extern "C" {
#endif

#include "Memory.h"
#include "../inc/eosPThread.h"

#ifdef __cplusepluse
};
#endif

void 
eosPThreadInit(eosPThread* t, int max, int mode)
{
	int i;
	t->max = max;
	t->th     = (pthread_t*)       memoryAllocate(sizeof(pthread_t)       *max, "in eosPThreadInit");
	t->status = (eosPThreadStatus*)memoryAllocate(sizeof(eosPThreadStatus)*max, "in eosPThreadInit");
	t->id     = (long*)            memoryAllocate(sizeof(long)            *max, "in eosPThreadInit");
	for(i=0; i<max; i++) {
		t->status[i] = eosPThreadStatusWaiting;
	}
	for(i=0; i<max; i++) {
		t->id[i] = 0;
	}
	t->count=0;
	t->oldest=0;
	t->latest=0;
}
