/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosPointCopy ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosPointCopy 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosPointCopy ver%I%; Date:%D% %Z%";

#include "../inc/eosPoint.h"

void
eosPointCopy(eosPoint* out, eosPoint* in)
{
	eosPointInit(out, NULL);
	eosPointTop(in);
	while(NULL!=in->current) {
		eosPointAppend(out, &(in->current->p), 0);
		eosPointNext(in);
	}
}

