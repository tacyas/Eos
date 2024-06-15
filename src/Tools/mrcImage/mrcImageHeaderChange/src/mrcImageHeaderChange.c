/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageHeaderChange ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageHeaderChange
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageHeaderChange ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"

void
main(int argc, char* argv[]) 
{
	mrcImageHeaderChangeInfo info;

/* variables */
        mrcImage in;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	if (info.flagr){
	  in.HeaderLength.x = info.r;
	  in.HeaderLength.y = info.r;
	  in.HeaderLength.z = info.r;
	}
	if (info.flagLx){
	  in.HeaderLength.x = info.Lx;
	}
	if (info.flagLy){
	  in.HeaderLength.y = info.Ly;
	}
	if (info.flagLz){
	  in.HeaderLength.z = info.Lz;
	}
	mrcFileWrite(&in ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stderr,"If r is defined, pixel size is r\n");
}



