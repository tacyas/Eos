/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageRectangleGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageRectangleGet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageRectangleGet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"


void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageRectangleGetInfo info;

/* variables */
        mrcImage in;
        mrcImage out;
	int temp;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	if (info.mode==1){
	  temp = info.bly;
	  info.bly = info.blx;
	  info.try = temp;
       	  info.blx = 0;
	  info.trx = in.HeaderN.x-1;
	}
	if (info.mode==2){
	  info.trx = info.bly;
	  info.bly = 0;
	  info.try = in.HeaderN.y-1;
	}
	lmrcImageRectangleGet(&out ,&in ,info.blx ,info.bly ,info.trx ,info.try);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"----- mode -----\n");
fprintf(stdout,"mode 0 :Rectangle get. -r option requires 4 values.\n");
fprintf(stdout,"mode 1 :Cut along y axis. -r option requires 4 values, y of bottom and top and 0 0. For example, -r 10 20 0 0 means get image of y position between 10 and 20\n");
fprintf(stdout,"mode 2 :Cut along x axis. -r option requires 4 values, x of bottom and top and 0 0. For example, -r 10 20 0 0 means get image of x position between 10 and 20\n");
}
