#ifndef ASTIGMATISM_DETECTION_H
#define ASTIGMATISM_DETECTION_H
/*
# lastigmatismDetection.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lastigmatismDetection.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include "ctfInfo.h" 

typedef struct lastigmatismDetectionInfo  {
	double* defocus; 
	int		sectionSize;
}  lastigmatismDetectionInfo;


/* prototype begin */
extern void lastigmatismDetection(ctfInfo* results, lastigmatismDetectionInfo linfo, int mode);

/* prototype end */
#endif
