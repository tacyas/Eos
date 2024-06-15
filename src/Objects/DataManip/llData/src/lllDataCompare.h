#ifndef LLLDATA_COMPARE_H 
#define LLLDATA_COMPARE_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#include "genUtil.h"
#include "llData.h"

/* struct begin */

typedef struct lllDataCompareInfo {
	int FilamentNumber;
	double ratio;
	double OriginReflection;
	double OtherReflection;
	int mode;
} lllDataCompareInfo;

/* struct end */

/* prototype begin */
extern void lllDataCompare(lllDataIntensityInformation* data,
						   lllDataCompareInfo* linfo, 
							int mode);
/* prototype end */

#endif /* LLLDATA_COMPARE_H */
