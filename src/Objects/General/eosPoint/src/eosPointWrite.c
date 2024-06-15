/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosPointWrite ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosPointWrite 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosPointWrite ver%I%; Date:%D% %Z%";

#include "../inc/eosPoint.h"

void
eosPointWrite(FILE* fpt, eosPoint* p, int mode)
{
	eosPointTop(p);
	while(NULL != p->current) {
		fprintf(fpt, "%15.6g %15.6g %15.6g ", 
			p->current->p.coord.data[0], p->current->p.coord.data[1], p->current->p.coord.data[2]);
		if(mode&0x01) {
			fprintf(fpt, "%15.6g ", p->current->p.sigma); 
		}
		if(mode&0x02) {
			fprintf(fpt, "%15.6g %15.6g %15.6g ", 
				p->current->p.sig.data[0], p->current->p.sig.data[1], p->current->p.sig.data[2]);
		}
		fprintf(fpt, "\n");
		eosPointNext(p);
	}	

}
