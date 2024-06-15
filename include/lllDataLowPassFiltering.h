/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataLowPassFiltering.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataLowPassFiltering.h 
#%Z% Attention
#%Z%
*/
#ifndef LLLDATA_LOW_PASS_FILTERING_H
#define LLLDATA_LOW_PASS_FILTERING_H

#include "llData.h"

/* constant begin */
typedef enum lllDataLowPassFilteringMode {
	lllDataLowPassFilteringModeSameMemorySize  = 0,
	lllDataLowPassFilteringModeSavedMemorySize = 1
} lllDataLowPassFilteringMode;
/* contant end */

/* prototype begin */
extern void lllDataLowPassFiltering(llData* ll, double RMax, int mode);
extern void lllDataRadialLowPassFiltering(llData* ll, double RRMax, int mode);
/* prototype end   */ 

#endif /* LLLDATA_LOW_PASS_FILTERING_H */
