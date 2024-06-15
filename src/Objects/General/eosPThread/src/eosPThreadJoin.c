/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosPThreadJoin ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosPThreadJoin 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosPThreadJoin ver%I%; Date:%D% %Z%";


#include "../inc/eosPThread.h"

void
eosPThreadJoin(eosPThread* th, int i, int mode)
{
	int j;
	int oldest;
	int latest;

	if(th->status[i] == eosPThreadStatusRunning) {
		pthread_join(th->th[i], NULL);
	} else {
		return;
	}
	th->status[i] = eosPThreadStatusWaiting;
	if(th->latest!=th->oldest) {
		if(th->id[i]==th->oldest) {
			for(oldest=th->latest, j=0; j<th->max; j++) {
				if(th->status[j] == eosPThreadStatusRunning 
				&& th->id[j]<oldest) {
					oldest = th->id[j];
				}
			}
			th->oldest = oldest;
		}
		if(th->id[i]==th->latest) {
			for(latest=th->oldest, j=th->max-1; 0<=j; j--) {
				if(th->status[j] == eosPThreadStatusRunning 
				&& latest<th->id[j]) {
					latest = th->id[j];
				}
			}
			th->latest = latest;
		}
	} else {
		th->latest = 0;
		th->oldest = 0;
	}
}

void
eosPThreadJoinAll(eosPThread* th, int mode)
{
	int i;
	for(i=0; i<th->max; i++) {
		eosPThreadJoin(th, i, mode);
	}
}

