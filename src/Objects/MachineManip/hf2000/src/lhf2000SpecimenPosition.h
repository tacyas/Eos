/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lhf2000SepecimenPosition.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lhf2000SepecimenPosition.h 
#%Z% Attention
#%Z%
*/
#include "hf2000.h"
/* struct begin  */

typedef struct lhf2000SepecimenPositionInfo {
	float  x;
	int   ix;
	float  y;
	int   iy;
} lhf2000SpecimenPositionInfo;

/* struct end */

/* prototype begin */
extern void lhf2000SpecimenPositionGet(hf2000Info* hf2000, lhf2000SpecimenPositionInfo* linfo, int mode);
extern void lhf2000SpecimenPositionSet(hf2000Info* hf2000, lhf2000SpecimenPositionInfo* linfo, int mode);
/* prototype end */
