/*
# lmrcImageLocal.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageLocal.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGELOCAL_H
#define LMRCIMAGELOCAL_H

#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>    
#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef struct lmrcImageLocalMaximumValuesFindInfo {
    double threshold; 
	int size;
} lmrcImageLocalMaximumValuesFindInfo;

typedef enum lmrcImageLocalMaximumValuesFindMode {
	a=0,
	b=1 
} lmrcImageLocalMaximumValuesFindMode;


/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageLocalMaximumValuesFind(mrcImage* out, mrcImage* in, lmrcImageLocalMaximumValuesFindInfo* linfo, int mode); 

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
