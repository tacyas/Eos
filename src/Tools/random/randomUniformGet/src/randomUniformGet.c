/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% randomUniformGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : randomUniformGet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%randomUniformGet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "Random.h"
#include "Memory.h"
#include <time.h>

int
main(int argc, char* argv[]) 
{
	long status;
	randomUniformGetInfo info;
	float* x;
	int i;
	time_t t;
	
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	x = (float*)memoryAllocate(sizeof(float)*info.num, "in main");

	srandomByTime();
	for(i=0;i<info.num;i++){
		x[i] = randomUniformGet(info.min, info.max, info.mode);
	}

	/*
	fprintf(stdout,"Composed and Written By Tomoki Inoue.\n");
	fprintf(stdout,"Thank you, ByeBye !! (ToT)/ \n");
	*/

	for(i=0;i<info.num;i++){
	  fprintf(info.fptOut,"%f\n",x[i]);
	}

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
}
