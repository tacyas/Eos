/*
# ctfEnvelopFunctionEstimate : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : ctfEnvelopFunctionEstimate
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "ctfInfo.h"
#include "mrcImage.h"

#include "lctfDetermination.h"
#include "powerspectraTangentLine.h"
#include "ctfInfoWrite2.h"
#include "lmrcFSInfoScatteringAngularDistributionAverageSection.h"


/*
Example:
typedef struct lctfEnvelopFunctionEstimateInfo {
	float a;
	int   b;
} lctfEnvelopFunctionEstimateInfo;

typedef enum lctfEnvelopFunctionEstimateMode {
	a=0,
	b=1
} lctfEnvelopFunctionEstimateMode;
*/

int
main(int argc, char* argv[]) 
{
	ctfEnvelopFunctionEstimateInfo info;
	mrcImage in;
	floatVector* spacing;
	floatVector* scatter;
	float** belowCoefficient;
	float** aboveCoefficient;
	ctfInfo ini;
	lctfDetermineInfo linfo;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.degree = info.degree;
	ini.CutLow = info.CutLow;
	ini.CutHigh = info.CutHigh;

	mrcFileRead(&in, info.In, "in main", 0);
	scatter = lmrcFSInfoScatteringAngularDistributionAverage(&in);
	spacing = lmrcFSInfoSpacing(&in);
	DEBUGPRINT2("%f %f\n", spacing->data[0], scatter->data[0]);
	DEBUGPRINT2("%f %f\n", spacing->data[1], scatter->data[1]);
	
	belowCoefficient = MemoryAllocate(float*, linfo.degree+1, "in lctfDeterminationByTangent");
	for(i=0; i<linfo.degree+1; i++) {
         belowCoefficient[i] = MemoryAllocate(float, i+1, "in lctfDeterminationByTangent");
	}
	aboveCoefficient = MemoryAllocate(float*, linfo.degree+1, "in lctfDeterminationByTangent");
	for(i=0; i<linfo.degree+1; i++) {
		aboveCoefficient[i] = MemoryAllocate(float, i+1, "in lctfDeterminationByTangent");
	}

	TangentLine(spacing, scatter, belowCoefficient, aboveCoefficient, &ini, &linfo, info.mode);

	DEBUGPRINT2("below %f above %f\n", belowCoefficient[0][0], aboveCoefficient[0][0]);
	TangentLinePrint(info.fptOut, spacing, scatter, belowCoefficient, aboveCoefficient, &linfo, info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
