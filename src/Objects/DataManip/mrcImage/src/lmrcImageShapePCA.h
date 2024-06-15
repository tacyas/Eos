/*
# lmrcImageShapePCA.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageShapePCA.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRC_IMAGE_SHAPE_PCA_H 
#define LMRC_IMAGE_SHAPE_PCA_H 

#include <stdio.h>
#include "genUtil.h"
#include "Array.h"
#include "mrcImage.h"
/* constant begin */


/* constant end */

/* struct begin */

typedef struct lmrcImageShapePCAInfo {
        /* Input */
        int nLevel;
        float* Level;

        /* Output */
        Array C;
        Array u;
        Array Lambda;
        Array Average;

		/* Control */
		int dimension;
} lmrcImageShapePCAInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern int lmrcImageShapePCA(mrcImage* in, lmrcImageShapePCAInfo* linfo, int mode);
extern int lmrcImageShapePCA2D(mrcImage* in, lmrcImageShapePCAInfo* linfo, int mode);
extern int lmrcImageShapePCA3D(mrcImage* in, lmrcImageShapePCAInfo* linfo, int mode);
extern int lmrcImageShapePCAResultsPrint(FILE* fpt, lmrcImageShapePCAInfo* linfo, int mode);
extern int lmrcImageShapePCAResultsPrint2D(FILE* fpt, lmrcImageShapePCAInfo* linfo, int mode);
extern int lmrcImageShapePCAResultsPrint3D(FILE* fpt, lmrcImageShapePCAInfo* linfo, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRC_IMAGE_SHAPE_PCA_H */ 
