/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% crystalInit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : crystalInit 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%crystalInit ver%I%; Date:%D% %Z%";
#define __CRYSTALINIT__
#include "../inc/Crystal.h"

/* 
	Initialize Crystal Struct
*/
void crystalInit(CrystalInfo* crystal) 
{
	crystalAxisSet(crystal, 'a', 1, 0, 0, 0);
	crystalAxisSet(crystal, 'b', 0, 1, 0, 0);
	crystalAxisSet(crystal, 'c', 0, 0, 1, 0);

	crystal->Origin.x = 0.0;
	crystal->Origin.y = 0.0;
	crystal->Origin.z = 0.0;

	crystal->N.a = 1;
	crystal->N.b = 1;
	crystal->N.c = 1;

	crystal->StartN.a = 0;
	crystal->StartN.b = 0;
	crystal->StartN.c = 0;

	crystal->SpaceGroup = CrystalSpaceGroupP1;
}

