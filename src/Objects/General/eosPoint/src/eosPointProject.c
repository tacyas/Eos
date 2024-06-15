/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosPointProject ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosPointProject 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosPointProject ver%I%; Date:%D% %Z%";
#include "../inc/eosPoint.h"

void
eosPointProject(eosPoint* p, int index) {
	eosPointTop(p);
	while(NULL!=p->current) {
		p->current->p.coord.data[index] = 0;
		eosPointNext(p);
	}
}

void
eosPointProject2(eosPoint* out, eosPoint* in, int index)
{
	eosPointCopy(out, in);
	eosPointProject(out, index); 
}


