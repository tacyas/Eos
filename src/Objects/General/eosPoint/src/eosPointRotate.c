/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosPointRotate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosPointRotate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosPointRotate ver%I%; Date:%D% %Z%";

#include "../inc/eosPoint.h"

void
eosPointRotate(eosPoint* p, Matrix3D mat)
{
	eosPointTop(p);
	while(NULL!=p->current) {
		matrix3DMultiplyVector(&p->current->p.coord, mat);
		eosPointNext(p);
	}
}


void
eosPointRotate2(eosPoint* out, eosPoint* in, Matrix3D mat)
{
	eosPointCopy(out, in);
	eosPointRotate(out, mat); 
}


