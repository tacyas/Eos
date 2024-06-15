/*
# mrcImageNeuralNetParticleExtraction : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageNeuralNetParticleExtraction
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
#include "pickup.h"

/*
Example:
typedef struct lmrcImageNeuralNetParticleExtractionInfo {
	float a;
	int   b;
} lmrcImageNeuralNetParticleExtractionInfo;

typedef enum lmrcImageNeuralNetParticleExtractionMode {
	a=0,
	b=1
} lmrcImageNeuralNetParticleExtractionMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageNeuralNetParticleExtractionInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
