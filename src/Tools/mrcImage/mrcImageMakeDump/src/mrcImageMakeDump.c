/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMakeDump ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMakeDump
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMakeDump ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

/* prototype */
void lmrcImageMakeDump2DReal(FILE* fpt, mrcImage* in, int mode);
void lmrcImageMakeDump3DReal(FILE* fpt, mrcImage* in, int mode);
void lmrcImageMakeDump2DFourier(FILE* fpt, mrcImage* in ,int mode);
void lmrcImageMakeDump3DFourier(FILE* fpt, mrcImage* in ,int mode);

void
main(int argc, char* argv[]) 
{
    long status;
	mrcImageMakeDumpInfo info;

/* variables */
	mrcImage in;
	int flag;
     
/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	if(in.HeaderN.z == 1) {
		if(IsImage(&in, "", 0)) {
	  		lmrcImageMakeDump2DReal(info.fptOut, &in, info.mode);
		} else if(IsFT(&in, "", 0)) {
	  		lmrcImageMakeDump2DFourier(info.fptOut, &in ,info.mode);
		} else {
			fprintf(stderr, "Not supported image mode: %d\n", in.HeaderMode);
		}
	} else {
		if(IsImage(&in, "", 0)) {
	  		lmrcImageMakeDump3DReal(info.fptOut, &in, info.mode);
		} else if(IsFT(&in, "", 0)) {
	  		lmrcImageMakeDump3DFourier(info.fptOut, &in ,info.mode);
		} else {
			fprintf(stderr, "Not supported image mode: %d\n", in.HeaderMode);
		}
	}
	exit(EXIT_SUCCESS);				  
}

void
additionalUsage()
{
  fprintf(stdout ,"----- mode(For Fourier space) ----- \n");
  fprintf(stdout ,"0:Repart Impart\n");
  fprintf(stdout ,"1:Power\n");
  fprintf(stdout ,"2:Phase\n");
  fprintf(stdout ,"+4:Dump full space for Power. Default is x>=0 only.\n");
  fprintf(stdout ,"+8:Dump for table \n");
}

void lmrcImageMakeDump2DReal(FILE* fpt, mrcImage* in, int mode)
{

/* variables */
  int x,y;
  double data;

/* begin */
  if((mode&8)==0) {
  	for (y = 0; y < in->HeaderN.y ; y++){
      for (x = 0; x < in->HeaderN.x ; x++){
      	mrcPixelDataGet(in ,x ,y ,0 ,&data, mrcPixelRePart, mrcPixelHowNearest);
      	fprintf(fpt,"%d %d %g \n",x,y,data);
      }
	}
  } else {
    for (y = in->HeaderN.y - 1; 0<=y ; y--){
      for (x = 0; x < in->HeaderN.x ; x++){
        mrcPixelDataGet(in ,x ,y ,0 ,&data, mrcPixelRePart, mrcPixelHowNearest);
      	fprintf(fpt,"%15g ",data);
	  }
	  fprintf(fpt, "\n");
	}
  }
}

void lmrcImageMakeDump3DReal(FILE* fpt, mrcImage* in, int mode)
{

/* variables */
  int x,y,z;
  double data;

/* begin */
  if((mode&8)==0) {
    for (z = 0; z < in->HeaderN.z ; z++){
      for (y = 0; y < in->HeaderN.y ; y++){
        for (x = 0; x < in->HeaderN.x ; x++){
		  mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
		  fprintf(stdout,"%d %d %d %g \n",x,y,z,data);
        }
      }
    }
  } else {
    for (z = 0; z < in->HeaderN.z ; z++){
      for (y = in->HeaderN.y-1; 0<=y; y--){
        for (x = 0; x < in->HeaderN.x ; x++){
		  mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
		  fprintf(stdout,"%15g ",data);
        }
	    fprintf(fpt, "\n");
      }
    }
  }
}


void lmrcImageMakeDump3DFourier(FILE* fpt, mrcImage* in ,int mode)
{

/* variables */
  int X,Y,Z,Xmin;
  double rdata,idata;

/* begin */
  Xmin = (mode>3)?(-in->HeaderN.x / 2):(0);
  for (Z = - in->HeaderN.z / 2; Z < in->HeaderN.z / 2 ; Z++){
    for (Y = -in->HeaderN.y / 2; Y < in->HeaderN.y / 2  ; Y++){
      for (X = Xmin; X <= in->HeaderN.x / 2 ; X++){
	switch (mode % 4){
	case 0:
	  mrcPixelDataGet(in ,X ,Y ,Z ,&rdata, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataGet(in ,X ,Y ,Z ,&idata, mrcPixelImPart, mrcPixelHowNearest);
	  fprintf(stdout,"%d %d %d %g %g \n",X,Y,Z,rdata,idata);	
	  break;
	case 1:
	  mrcPixelDataGet(in ,X ,Y ,Z ,&rdata, mrcPixelPow, mrcPixelHowNearest);
	  fprintf(stdout,"%d %d %d %g \n",X,Y,Z,rdata);
	  break;
	case 2:
	  mrcPixelDataGet(in ,X ,Y ,Z ,&rdata, mrcPixelPhase, mrcPixelHowNearest);
	  fprintf(stdout,"%d %d %d %g \n",X,Y,Z,rdata);
	  break;
	  mrcPixelDataGet(in ,X ,Y ,Z ,&rdata, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataGet(in ,X ,Y ,Z ,&idata, mrcPixelImPart, mrcPixelHowNearest);
	  fprintf(stdout,"%d %d %d %g %g \n",X,Y,Z,rdata,idata);
	}
      }
    }
  }
}

void lmrcImageMakeDump2DFourier(FILE* fpt, mrcImage* in ,int mode)
{

/* variables */
  int X,Y,Xmin;
  double rdata,idata;

/* begin */
  Xmin = (mode>3)?(-in->HeaderN.x / 2):(0);
  for (Y = - in->HeaderN.y / 2; Y < in->HeaderN.y / 2 ; Y++){
    for (X = Xmin ; X <= in->HeaderN.x / 2  ; X++){
      switch (mode % 4){
      case 0:
	mrcPixelDataGet(in ,X ,Y ,0 ,&rdata, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataGet(in ,X ,Y ,0 ,&idata, mrcPixelImPart, mrcPixelHowNearest);
	fprintf(stdout,"%d %d %g %g \n",X,Y,rdata,idata);	
	break;
      case 1:
	mrcPixelDataGet(in ,X ,Y ,0 ,&rdata, mrcPixelPow, mrcPixelHowNearest);
	fprintf(stdout,"%d %d %g \n",X,Y,rdata);
	break;
      case 2:
	mrcPixelDataGet(in ,X ,Y ,0 ,&rdata, mrcPixelPhase, mrcPixelHowNearest);
	fprintf(stdout,"%d %d %g \n",X,Y,rdata);
	break;
      }
    }
  }
}








