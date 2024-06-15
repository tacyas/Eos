/*
# larray2mrc.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : larray2mrc.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LARRAY2MRC_H
#define LARRAY2MRC_H 

#include <stdio.h>

#define DEBUG
#include "genUtil.h"
#include "Array.h"
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef struct larray2mrcInfo {
	int   mrcMode;
	mrcImageParaTypeReal mrcLengthX;
	mrcImageParaTypeReal mrcLengthY;
	mrcImageParaTypeReal mrcLengthZ;
    int ax; // 1, 2, 3
    int ay;
    int az;
} larray2mrcInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void larray2mrc(mrcImage* out, Array a, larray2mrcInfo* linfo, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LARRAY2MRC_H */ 

