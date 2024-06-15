/*
# mrcImageAddValue : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageAddValue
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
#include "mrcImage.h"
#include "lmrcImageAddValue.h"

#ifdef  CUDA
#include "eosCuda.h"
#endif

int
main(int argc, char* argv[]) 
{
	mrcImageAddValueInfo info;
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

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageAddValue(&out, &in, info.Value, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
