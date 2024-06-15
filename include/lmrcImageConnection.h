#ifndef MRC_CONNECTION_H
#define MRC_CONNECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define UNDEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageConnectionInfo {
	long mode;
} lmrcImageConnectionInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageConnection(mrcImage* out,
								mrcImage* in1,
								mrcImage* in2,
							    lmrcImageConnectionInfo* info);
/* prototype end */

#endif



