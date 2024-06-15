/*
# mrcImagePosterization : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImagePosterization
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
#include "lmrcImagePosterization.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

int
main(int argc, char* argv[]) 
{
	mrcImagePosterizationInfo info;

	mrcImage in;
	mrcImage out;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in,  info.In , "in main" ,0);
	lmrcImagePosterization(&in, &out, info.Grad, info.mode);
	mrcFileWrite(&out, info.Out ,"in main" ,0);
	
	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
