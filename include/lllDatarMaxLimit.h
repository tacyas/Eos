/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDatarMaxLimit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDatarMaxLimit
#%Z% Attention
#%Z%
*/

#ifndef LLLDATA_RMAX_LIMIT_H
#define LLLDATA_RMAX_LIMIT_H

#include "llData.h"
#include "genUtil.h"

/* constant begin */

typedef enum lllDatarMaxLimitMode {
	lllDatarMaxLimitModeNoMemorySave = 0 ,
	lllDatarMaxLimitModeMemorySave   = 1
} lllDatarMaxLimitMode;
/* constant end */

/* struct begin */

typedef struct lllDatarMaxLimitInfo {
	float rMax;
	int   flagrMaxMin;
	float rMaxMin;
} lllDatarMaxLimitInfo;
/* struct end */

/* prototype begin */
extern void
lllDatarMaxLimit(llData* llIn, lllDatarMaxLimitInfo linfo, int mode);

extern inline int 
lllDatarMaxLimitCheck(float R, int n, float rMax);

extern inline float 
lllDatarMaxLimitWeight(float R, int n, float rMax, float rMaxMin);
/* prototype end */

#endif /* LLLDATA_RMAX_LIMIT_H */
