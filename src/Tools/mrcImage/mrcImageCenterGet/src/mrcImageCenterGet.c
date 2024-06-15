/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCenterGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCenterGet
#%Z% Attention
#%Z%
*/
/*
	tacyas: 98/09/30 : bug fixed:   
					   new option: add -even option
*/
static char __sccs_id[] = "%Z%mrcImageCenterGet ver%I%; Date:%D% %Z%";
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


/* prototype */
void lmrcRefCenterGet(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,float Cx ,float Cy ,int mode);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageCenterGetInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);


/* initialization */
	mrcFileRead(&in ,info.In ,"in main" ,0); 
	if (!info.flagNx){
	  	if(info.even) {
	  		info.Nx = MAX(in.HeaderN.x/2*2,1);
	  	} else {
	  		info.Nx = in.HeaderN.x;
		}
	}
	if (!info.flagNy){
	  	if(info.even) {
	  		info.Ny = MAX(in.HeaderN.y/2*2,1);
	  	} else {
	  		info.Ny = in.HeaderN.y;
		}
	}
	if (!info.flagNz){
	  	if(info.even) {
	  		info.Nz = MAX(in.HeaderN.z/2*2,1);
		} else {
	  		info.Nz = in.HeaderN.z;
		}
	}

	if (info.Nx > in.HeaderN.x || info.Ny > in.HeaderN.y || info.Nz > in.HeaderN.z){
	  fprintf(stderr,"Nx or Ny or Nz is larger than inputfile");
	  exit(EXIT_FAILURE);
	}
	DEBUGPRINT2("%d,%d \n",info.Nx,info.Ny);
	if (!info.flagCx){
	  info.Cx=( (float)in.HeaderN.x-1)/2;
	}
	if (!info.flagCy){
	  info.Cy=( (float)in.HeaderN.y-1)/2;
	}
	if (!info.flagCz){
	  info.Cz=( (float)in.HeaderN.z-1)/2;
	}

	switch (info.mode2){
	case 0:
	  if (info.Nx != in.HeaderN.x || info.Ny != in.HeaderN.y || info.Nz != in.HeaderN.z ){
	    lmrcImageCenterGet(&out ,&in ,info.Nx ,info.Ny ,info.Nz ,info.Cx ,info.Cy ,info.Cz ,info.mode);
	  } else {
		out = in;
	  }
	  mrcFileWrite(&out ,info.Out ,"in main" ,0); 
	  break;
	case 1:
	  if (info.Nx != in.HeaderN.x || info.Ny != in.HeaderN.y){
	    lmrcRefCenterGet(&out ,&in ,info.Nx ,info.Ny ,info.Cx ,info.Cy ,info.mode );
	  } else {
		out = in;
	  }
	  DEBUGPRINT2("%d %d\n",out.HeaderN.x,out.HeaderN.y);
	  mrcFileWrite(&out ,info.Out ,"in main" ,0); 
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"----- mode -----\n");
fprintf(stdout,"Mode is interpolation mode.\n");
fprintf(stdout,"0:By Nearest\n");
fprintf(stdout,"1:By Linear\n");
fprintf(stdout,"2:By Cubic Convolusion\n");
fprintf(stdout,"----- mode 2 ----- \n");
fprintf(stdout,"0:Normal Image\n");
fprintf(stdout,"1:Ref Image\n");
}



void lmrcRefCenterGet(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,float Cx ,float Cy ,int mode)
{
/* variables */
  int z;
  mrcImage tmpin,tmpout;
  mrcRefHeader ref;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = Nx;
  out->HeaderN.y = Ny;
  mrcInit(out,NULL);

/* begin */
  lmrcRefHeaderGet(&ref ,in);
  lmrcRefHeaderSet(out ,&ref);
  for (z=1 ; z<out->HeaderN.z ; z++){
    lmrc3DZ1ImgGet(&tmpin ,in ,z); 
    lmrcImageCenterGet(&tmpout ,&tmpin ,Nx ,Ny ,1 ,Cx ,Cy ,z ,mode);
    lmrc3DZ1ImgPut(out ,&tmpout, z);
    mrcImageFree(&tmpout,"");
    mrcImageFree(&tmpin,"");
  }
  mrcStatDataSet(out,0);
}

