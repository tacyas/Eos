/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageFFT ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageFFT
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageFFT ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

#ifdef  CUDA
#include "eosCuda.h"
#endif


int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageFFTInfo info;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

#ifdef CUDA
        if(info.flagcudaDeviceID) {
                eosCudaInit(info.cudaDeviceID);
        }
#endif

	mrcFileRead(&in, info.In, "in main", 0);
	lmrcImageFFT(&out, &in, info.mode);
	mrcFileWrite(&out, info.Out, "in main", 0);

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "x, y and z must be even pixels.\n");
	fprintf(stderr, "Excepts for like that \n");
	fprintf(stderr, "(x, y, z)=(100, 1, 1)\n");
}
