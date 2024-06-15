/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageEdgeAverage.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageEdgeAverage.h 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_EDGE_AVERAGE_H 
#define  LMRC_IMAGE_EDGE_AVERAGE_H

#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageEdgeAverageInfo {
	/* In */
	mrcImageParaTypeInteger devide; 
	mrcImageParaTypeInteger width;
	/* Out */
	mrcImageParaTypeReal*   avg[4];
	mrcImageParaTypeReal*   count[4];
} lmrcImageEdgeAverageInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageEdgeAverage(mrcImage* mrc, lmrcImageEdgeAverageInfo* linfo, long mode);
/* prototype end */

#endif




