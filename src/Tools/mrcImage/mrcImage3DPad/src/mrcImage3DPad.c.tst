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

/* prototypes */
void lmrcImage3DPadfilament(mrcImage* out ,mrcImage* in ,float rmax ,long flagr, int Nx ,int Ny ,double w ,int mode ,double v ,long flagv);
double lmrcImage3DPadfilamentCalcavr(mrcImage* in ,double rmax);
double lmrcImage3DPadCalcavr(mrcImage* in ,double rmax);
void lmrcImage3DPad(mrcImage* out, mrcImage* in, float rmax, long flagr, int Nx ,int Ny, int Nz, double w, int mode, double v, long flagv);


int
main(int argc, char* argv[]) 
{
	mrcImage3DPadInfo info;

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
	if (!info.mode2){
	  lmrcImage3DPadfilament(&out ,&in ,info.r ,info.flagr, info.Nx ,info.Ny ,info.w ,info.mode ,info.v ,info.flagv);
	} else {
	  lmrcImage3DPad(&out, &in, info.r, info.flagr, info.Nx, info.Ny, info.Nz, info.w, info.mode, info.v, info.flagv);
	}
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
  fprintf(stderr, "0:For filaments.  R is calculated from its axis.\n");
  fprintf(stderr, "1:For particles.  R is calculated from its center.\n");
		
}

void lmrcImage3DPadfilament(mrcImage* out ,mrcImage* in ,float rmax ,long flagr, int Nx ,int Ny ,double w ,int mode ,double v ,long flagv)
{
/* variables */
  int x,y,z;
  double data,cx,cy,sx,sy,r2,av,c,dr2,averager;

/* begin */
  out->Header = in->Header;
  out->HeaderN.x = Nx;
  out->HeaderN.y = Ny;
  mrcInit(out,NULL);
  DEBUGPRINT1("TailerNum %d\n", in->numTailer);
  if(0<in->numTailer) {
  	out->numTailer = in->numTailer;
  	out->Tailer = in->Tailer;
    DEBUGPRINT1("TailerNum %d in Out\n", out->numTailer);
  }

  cx=(in->HeaderN.x-1)*0.5;
  cy=(in->HeaderN.y-1)*0.5;
  sx=(out->HeaderN.x-in->HeaderN.x)*0.5;
  sy=(out->HeaderN.y-in->HeaderN.y)*0.5;
  r2=SQR(rmax);
  switch(mode){
  case 0:
    if (!flagv){
      if (rmax > (in->HeaderN.x - 1)/2.0 || rmax > (in->HeaderN.y - 1)/2.0){
	averager = MIN((in->HeaderN.x - 1)/2.0, (in->HeaderN.y - 1)/2.0 );
      } else {
	averager = rmax;
      }
      DEBUGPRINT1("r: %g \n",averager);
      av=lmrcImage3DPadfilamentCalcavr(in ,averager);
   } else {
      av=v;
    }
    for (z=0 ;z<out->HeaderN.z;z++){
      for (x=0;x<out->HeaderN.x;x++){
	for (y=0;y<out->HeaderN.y;y++){
	  mrcPixelDataSet(out ,x ,y ,z ,av, mrcPixelRePart);
	}
      }
    }
    for (z=0 ;z<in->HeaderN.z;z++){
      for (x=0;x<in->HeaderN.x;x++){
	for (y=0;y<in->HeaderN.y;y++){
	  mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
	  if (flagr){
	    dr2=SQR(x-cx)+SQR(y-cy);
	    if (r2>=dr2 ){
	      mrcPixelDataSet(out ,x+sx ,y+sy ,z ,data, mrcPixelRePart);
	    } 
	  } else {	      
	    mrcPixelDataSet(out ,x+sx ,y+sy ,z ,data, mrcPixelRePart);
	  }	    
	}
      }
    }
    break;

  case 1:
  case 2:
    if (!flagv){
      av=lmrcImage3DPadfilamentCalcavr(in ,rmax+w);
      DEBUGPRINT1("r: %g \n",averager);
      fprintf(stdout,"av: %g \n",av);
    } else {
      av=v;
    }
    for (z=0 ;z<in->HeaderN.z;z++){
      for (x=0;x<in->HeaderN.x;x++){
	for (y=0;y<in->HeaderN.y;y++){
	  mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
	  if (flagr){
	    dr2=SQR(x-cx)+SQR(y-cy);
	    if (SQR(rmax-w)>dr2 ){
	      mrcPixelDataSet(out ,x+sx ,y+sy ,z ,data, mrcPixelRePart);
	    }else if (SQR(rmax+w)<dr2 ){
	      mrcPixelDataSet(out ,x+sx ,y+sy ,z ,av, mrcPixelRePart);
	    }else {
	      c= (sin( ( rmax-sqrt(dr2)) / w *PI/2 )+1 ) /2;
	      mrcPixelDataSet(out ,x+sx ,y+sy ,z ,(data-av)*c+av , mrcPixelRePart);
	    }
	  } else {
	      mrcPixelDataSet(out ,x+sx ,y+sy ,z ,av, mrcPixelRePart);
	  }	    
	}
      }
    }  
  }
  mrcStatDataSet(out ,0);
}

double lmrcImage3DPadfilamentCalcavr(mrcImage* in ,double rmax)
{
/* variables */
  int x,y,z,n;
  double cx,cy,r2,sum,data,av;

/* begin */
  n=0;
  sum=0;
  cx=(in->HeaderN.x-1)*0.5;
  cy=(in->HeaderN.y-1)*0.5; 
  for (x=0;x<in->HeaderN.x;x++){
    for (y=0;y<in->HeaderN.y;y++){
      r2=SQR(x-cx)+SQR(y-cy);
      if (r2>=SQR(rmax) && r2<SQR(rmax+1) ){
	for (z=0 ;z<in->HeaderN.z;z++){
	  mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
	  sum+=data;
	  n++;
	}
      }
    }
  }
  av=sum/n;
  return(av);
}


void lmrcImage3DPad(mrcImage* out, mrcImage* in, float rmax, long flagr, int Nx ,int Ny, int Nz, double w, int mode, double v, long flagv)
{

/* variables */
  int x,y,z;
  double data,cx,cy,cz,sx,sy,sz,r2,av,c,dr2;

  out->Header = in->Header;
  out->HeaderN.x = Nx;
  out->HeaderN.y = Ny;
  out->HeaderN.z = Nz;
  mrcInit(out,NULL);
  if(0<in->numTailer) {
  	out->numTailer = in->numTailer;
	out->Tailer = in->Tailer;
  }
  cx=(in->HeaderN.x-1)*0.5;
  cy=(in->HeaderN.y-1)*0.5;
  cz=(in->HeaderN.z-1)*0.5;
  sx=(out->HeaderN.x-in->HeaderN.x)*0.5;
  sy=(out->HeaderN.y-in->HeaderN.y)*0.5;
  sz=(out->HeaderN.z-in->HeaderN.z)*0.5;
  r2=SQR(rmax);
  switch(mode){
  case 0:
    if (!flagv){
      av=lmrcImage3DPadCalcavr(in ,rmax);
    } else {
      av=v;
    }
    for (z=0 ;z<out->HeaderN.z;z++){
      for (x=0;x<out->HeaderN.x;x++){
	for (y=0;y<out->HeaderN.y;y++){
	  mrcPixelDataSet(out ,x ,y ,z ,av, mrcPixelRePart);
	}
      }
    }
    for (z=0 ;z<in->HeaderN.z;z++){
      for (x=0;x<in->HeaderN.x;x++){
	for (y=0;y<in->HeaderN.y;y++){
	  mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
	  if (flagr){
	    dr2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
	    if (r2>=dr2 ){
	      mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,data, mrcPixelRePart);
	    } 
	  } else {	      
	    mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,data, mrcPixelRePart);
	  }	    
	}
      }
    }
    break;
  case 1:
  case 2:
    if (!flagv){
      av=lmrcImage3DPadCalcavr(in ,rmax+w);
    } else {
      av=v;
    }
    fprintf(stdout,"av :%g\n",av); 
    for (z=0 ;z<in->HeaderN.z;z++){
      for (x=0;x<in->HeaderN.x;x++){
	for (y=0;y<in->HeaderN.y;y++){
	  mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
	  if (flagr){
	    dr2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
	    if (SQR(rmax-w)>dr2 ){
	      mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,data, mrcPixelRePart);
	    }else if (SQR(rmax+w)<dr2 ){
	      mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,av, mrcPixelRePart);
	    }else {
	      c= (cos( ( rmax-sqrt(dr2)) / w *PI/2 )+1 )/2;
	      mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,(data-av)*c+av , mrcPixelRePart);
	    }
	  } else {
	      mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,av, mrcPixelRePart);
	  }	    
	}
      }
    }  
  }
  mrcStatDataSet(out ,0);
}
  
double lmrcImage3DPadCalcavr(mrcImage* in ,double rmax)
{
/* variables */
  int x,y,z,n;
  double cx,cy,cz,r2,sum,data,av;

/* begin */
  n=0;
  sum=0;
  cx=(in->HeaderN.x-1)*0.5;
  cy=(in->HeaderN.y-1)*0.5; 
  cz=(in->HeaderN.z-1)*0.5; 
  for (x=0;x<in->HeaderN.x;x++){
    for (y=0;y<in->HeaderN.y;y++){
      for (z=0 ;z<in->HeaderN.z;z++){
      r2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
      if (r2>=SQR(rmax) && r2<SQR(rmax+1) ){
	  mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
	  sum+=data;
	  n++;
	}
      }
    }
  }
  av=sum/n;
  return(av);
}
