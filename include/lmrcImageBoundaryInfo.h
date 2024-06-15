/*
# lmrcImageBoundaryInfo.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageBoundaryInfo.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

typedef enum lmrcImageBoundaryInfoMode {
	lmrcImageBoundaryInfoModeAverageOfYAxis=0x1, 
	lmrcImageBoundaryInfoModeDynamicAverageOfYAxis=0x2, 
	lmrcImageBoundaryInfoModeAverageOfEdge=0x4, 
	lmrcImageBoundaryInfoModeAverageOfOutsideCircle=0x8, 
	lmrcImageBoundaryInfoModeAverageOfOutsideRing=0x10, 
	lmrcImageBoundaryInfoModeWithSD=0x10000 
} lmrcImageBoundaryInfoMode;

typedef struct lmrcImageBoundaryInfoInfo {
	lmrcImageBoundaryInfoMode mdoe;
} lmrcImageBoundaryInfoInfo;


typedef struct lmrcImageBoundaryInfoResults {
	double Average; 
	double* DynamicAverage;
	double StandardDeviation;

} lmrcImageBoundaryInfoResults;



