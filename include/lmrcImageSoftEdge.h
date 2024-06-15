/*
# lmrcImageSoftEdge.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageSoftEdge.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_SOFTEDGE
#define LMRCIMAGE_SOFTEDGE

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */
typedef enum lmrcImageSoftEdgeInfoEnvelop {
    lmrcImageSoftEdgeInfoEnvelopGaussian = 0,
    lmrcImageSoftEdgeInfoEnvelopCosine   = 1
} lmrcImageSoftEdgeInfoEnvelop;

/* constant end */

/* struct begin */

typedef struct lmrcImageSoftEdgeInfo {
    double width;
    lmrcImageSoftEdgeInfoEnvelop envelop;
} lmrcImageSoftEdgeInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */
extern int lmrcImageSoftEdge(mrcImage* out, mrcImage* in, lmrcImageSoftEdgeInfo linfo,  int mode);


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRCIMAGE_SOFTEDGE */ 
