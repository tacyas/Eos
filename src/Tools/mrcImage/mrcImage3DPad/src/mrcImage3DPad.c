/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImage3DPad ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImage3DPad
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImage3DPad ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImage3DPad.h"

int
main(int argc, char* argv[]) 
{
	mrcImage3DPadInfo info;
	lmrcImage3DPadInfo linfo;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in ,info.In ,"in main" ,0);
	DEBUGPRINT1("Tailer: %d\n", in.numTailer);	
/* begin */
	DEBUGPRINT("Program Start\n");
	if (!info.flagNx){
	  info.Nx=in.HeaderN.x;
	}
	if (!info.flagNy){
	  info.Ny=in.HeaderN.y;
	}
	if (!info.flagNz){
	  info.Nz=in.HeaderN.z;
	}
	if (!info.flagr){
	  info.r=MIN( (in.HeaderN.x-1)/2.0, (in.HeaderN.y-1)/2.0);
	}
	linfo.rmax = info.r;
	linfo.flagr = info.flagr;
	linfo.Nx = info.Nx;
	linfo.Ny = info.Ny;
	linfo.Nz = info.Nz;
	linfo.w  = info.w;
	linfo.flagv = info.flagv;
	linfo.v     = info.v;
	linfo.flagFloating = info.Floating;

	DEBUGPRINT3("N: %d %d %d\n", linfo.Nx, linfo.Ny, linfo.Nz);
	lmrcImage3DPad(&out, &in, linfo, info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
  fprintf(stderr, "----- mode -----\n");
  fprintf(stderr, "0:Default: Out of threshold is avrage of threshold plain.\n");
  fprintf(stderr, "1:Mulplying cos function. Default: Out of threshold is avrage of threshold plain.\n");
  fprintf(stderr, "----- mode2 -----\n");
  //fprintf(stderr, "0:For filaments.  R is calculated from its axis.\n");
  //fprintf(stderr, "1:For particles.  R is calculated from its center.\n");
  lmrcImage3DPadUsage(stderr);
}

