/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMake2DArrayImage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMake2DArrayImage
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMake2DArrayImage ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"

/* prototypes */
void lmrcImageMake2DArrayImage(mrcImage* out ,mrcImage* in ,int Nx ,int filenum ,int sw ,float sv ,int mode);

void
main(int argc, char* argv[]) 
{
	mrcImageMake2DArrayImageInfo info;

/* variables */
	mrcImage* in;
	mrcImage in0;
	mrcImage out;
	FILE* fpin;
	char infile[1000][2560];
	int filenum,i;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	if (info.mode == 0){
	  if((fpin=fopen(info.In,"r"))==NULL){
	    fprintf(stderr ,"File can not be opened.\n");
	    exit(1);
	  }
	  filenum=0;
	  while(fscanf(fpin,"%s \n",infile[filenum])!=EOF ){
	    filenum++;
	  }
	  if ( ( in = (mrcImage *)malloc(sizeof(mrcImage)*filenum) ) == NULL ){
	    fprintf(stderr ,"Enough memoly is not available.");
	    exit(EXIT_FAILURE);
	  }
	  for( i=0 ; i<filenum ;i++){
	    mrcFileRead(&in[i] ,infile[i] ,"in main" ,0);
	  }
	} else {
	    mrcFileRead(&in0 ,info.In ,"in main" ,0);
	    filenum=in0.HeaderN.z;
	    if ( ( in = (mrcImage *)malloc(sizeof(mrcImage)*filenum) ) == NULL ){
	      fprintf(stderr ,"Enough memoly is not available.");
	      exit(EXIT_FAILURE);
	    }
	    for( i=0 ; i<filenum ;i++){
	      lmrc3DZ1ImgGet(&in[i], &in0, i);
	    }
	}
	    
/* begin */
	DEBUGPRINT("start ");
	lmrcImageMake2DArrayImage(&out ,in ,info.Nx ,filenum ,info.w ,info.v ,info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0:Input is data array.\n");
	fprintf(stderr, "mode 1:Input is one 3D file. \n");
}

void lmrcImageMake2DArrayImage(mrcImage* out ,mrcImage* in ,int Nx ,int filenum ,int sw ,float sv ,int mode)
{
/* variables */
  int Ny;
  int x,y,fy,tx,ty,f,i,maxy,maxx;
  double data;

/* HeaderSet */
  Ny=(filenum%Nx)?(filenum/Nx+1):(filenum/Nx);
  f=y=maxx=0;
  for (fy=0 ;fy<Ny ;fy++){
    maxy=0;
    x=0;
    for (i=f ;i<MIN(f+Nx,filenum) ;i++){
      DEBUGPRINT2("%d %d   ",f,i);
      maxy=MAX(maxy,in[i].HeaderN.y);
      x+=in[i].HeaderN.x+sw;
    }
    f += Nx;
    y += maxy+sw;
    maxx=MAX(maxx,x);
    DEBUGPRINT3("%d %d %d  \n",f,y,maxx);
  }
  out->Header=in[0].Header;
  out->HeaderN.x=maxx-sw;
  out->HeaderN.y=y-sw;
  mrcInit(out,NULL);
  for (x=0;x<out->HeaderN.x;x++){
    for (y=0;y<out->HeaderN.y;y++){
      mrcPixelDataSet(out ,x ,y ,0 ,sv, mrcPixelRePart);
    }
  }
      

/* begin */
  f=y=0;
  for (fy=0 ;fy<Ny ;fy++){
    maxy=0;
    x=0;
    for (i=f ;i<MIN(f+Nx,filenum) ;i++){
      maxy=MAX(maxy,in[i].HeaderN.y);
    }
    for (i=f ;i<MIN(f+Nx,filenum) ;i++){
      DEBUGPRINT2("%d %d   ",f,i);
      for (ty=y ;ty<y+in[i].HeaderN.y ;ty++){
	for (tx=x ;tx<x+in[i].HeaderN.x ;tx++){
	  mrcPixelDataGet(&in[i] ,tx-x ,ty-y ,0 ,&data, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataSet(out ,tx ,ty ,0 ,data, mrcPixelRePart);
	}
      }
      x+=in[i].HeaderN.x+sw;
    }
    y+=maxy+sw;
    f+=Nx;
    DEBUGPRINT2("%d %d  \n",f,y);
  }
  mrcStatDataSet(out ,0);
}
  
