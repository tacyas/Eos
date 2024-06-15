/*
# leosPointPositionCorrection.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : leosPointPositionCorrection.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LEOSPOINT_POSITION_CORRECTION_H
#define LEOSPOINT_POSITION_CORRECTION_H

#include <stdio.h>

/* constant begin */

typedef enum leosPointPositionCorrectionMode {
	a=0,
	b=1
} leosPointPositionCorrectionMode;

/* constant end */

/* struct begin */

typedef struct leosPointPositionCorrectionInfo {
    // Input
	int n;

    // Output
    int m;
    eosPoint db;
} leosPointPositionCorrectionInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern int leosPointPositionCorrection(eosPoint* outP, eosPoint* inP, leosPointPositionCorrectionInfo* linfo, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LEOSPOINT_POSITION_CORRECTION_H*/ 

