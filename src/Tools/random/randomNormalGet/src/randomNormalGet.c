/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% randomNormalGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : randomNormalGet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%randomNormalGet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "Random.h"
#include "mrcImage.h"

#include <time.h>

int
main(int argc, char* argv[]) 
{
	long i, status;
	randomNormalGetInfo info;
	randomParaTypeReal  random;
	time_t t;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	if(info.flagOutMRC) {
		out.HeaderN.x = info.N;
		out.HeaderN.y = 1;
		out.HeaderN.z = 1;
		out.HeaderMode = mrcFloatImage;
		mrcInit(&out, NULL);
	}
	srand(time(&t));
	for(i=0; i< info.N; i++) {
		random = info.Ave + info.SD*randomNormalGet(info.mode);
		fprintf(info.fptOut, "%g\n", random);
		if(info.flagOutMRC) {
			mrcPixelDataSet(&out, i, 0.0, 0.0, random, mrcPixelRePart);
		}
	}
	if(info.flagOutMRC) {
		mrcFileWrite(&out, info.OutMRC, "in main", 0);
	}
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
}
