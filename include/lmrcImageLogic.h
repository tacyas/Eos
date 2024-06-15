/*
# lmrcImageLogic.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageLogic.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_LOGIC_H 
#define LMRCIMAGE_LOGIC_H 

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */
typedef enum lmrcImageLogicalOpMode {
	lmrcImageLogicalOpModeAND=0,
	lmrcImageLogicalOpModeOR,
	lmrcImageLogicalOpModeNOT,
	lmrcImageLogicalOpModeXOR,
	lmrcImageLogicalOpModeXNOR,
	lmrcImageLogicalOpModeNAND,
	lmrcImageLogicalOpModeNOR,
	lmrcImageLogicalOpModeF,
	lmrcImageLogicalOpModeT,
	lmrcImageLogicalOpModeP,
	lmrcImageLogicalOpModeQ,
	lmrcImageLogicalOpModeIMP,
	lmrcImageLogicalOpModeNIMP,
	lmrcImageLogicalOpModeIIMP,
	lmrcImageLogicalOpModeNIIMP
} lmrcImageLogicalOpMode;

/* constant end */

/* struct begin */


/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageLogicalOpModePrint(FILE* fpt);
extern double lmrcImageLogicalOperation(mrcImage* out, mrcImage* P, mrcImage* Q, lmrcImageLogicalOpMode mode);


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
