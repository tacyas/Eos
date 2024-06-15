/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMakeFromTextFile ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMakeFromTextFile
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMakeFromTextFile ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"



int
main(int argc, char* argv[]) 
{
	mrcImageMakeFromTextFileInfo info;

	/* variables */
	mrcImage out;
	FILE* fpIn;
	int x,y,z;
	double data;
	
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
	if((fpIn=fopen(info.In,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	out.HeaderN.x = info.nx;
	out.HeaderN.y = info.ny;
	out.HeaderN.z = info.nz;
	out.HeaderMode = mrcFloatImage;
	out.HeaderM.x = 0.0;
	out.HeaderM.y = 0.0;
	out.HeaderM.z = 0.0;
	out.HeaderLength.x = info.d;  
	out.HeaderLength.y = info.d;
	out.HeaderLength.z = info.d;
	mrcInit(&out ,0);
	for (x=0 ;x<out.HeaderN.x ;x++){
	  for (y=0 ;y<out.HeaderN.y ;y++){
	    for (z=0 ;z<out.HeaderN.z ;z++){
	      mrcPixelDataSet(&out, x, y, z, info.v, mrcPixelRePart);
	    }
	  }
	}
	while(fscanf(fpIn,"%d %d %d %lf \n",&x,&y,&z,&data )!=EOF ){
	  mrcPixelDataSet(&out, x, y, z, data, mrcPixelRePart);
  	}
	mrcStatDataSet(&out,0);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
       	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
