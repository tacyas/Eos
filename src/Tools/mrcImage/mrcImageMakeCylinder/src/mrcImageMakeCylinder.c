/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMakeCylinder ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMakeCylinder
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMakeCylinder ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototypes */
void lmrc2DImageSetFunction(mrcImage* out ,double (*func)(double x ,double y ,double param) ,int sizex ,int sizey ,double length ,double param);
double makecylinder(double x ,double y ,double sizex);
void lmrcImageMakecylinderbyfile(mrcImage* out ,char* in ,int sizex ,int sizey ,double length ,double param);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageMakeCylinderInfo info;

/* variables */
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	if (info.mode){
	  lmrcImageMakecylinderbyfile(&out,info.In,info.Nx,info.Ny,info.Resolution,0);
	}else{
	  lmrc2DImageSetFunction(&out ,makecylinder  ,info.Nx ,info.Ny ,info.Resolution ,0 );
	}
	DEBUGPRINT("write ");
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrcImageMakecylinderbyfile(mrcImage* out ,char* in ,int sizex ,int sizey ,double length ,double param)
{
/* variables */
  int x,y;
  double data;
  FILE* fpin;
  double** cylinderval;
  int cylindernum,i;
  double dummy;


/* Header Create */
  out->HeaderN.x = sizex;
  out->HeaderN.y = sizey;
  out->HeaderN.z = 1;
  out->HeaderMode = mrcFloatImage;
  out->HeaderM.x = 0.0;
  out->HeaderM.y = 0.0;
  out->HeaderM.z = 0.0;
  out->HeaderLength.x = length;  
  out->HeaderLength.y = length;
  out->HeaderLength.z = length;
  mrcInit(out ,NULL);

/* Data Read */
  if((fpin=fopen(in,"r"))==NULL){
    fprintf(stderr ,"File can not be opened.\n");
    exit(1);
  }
  cylindernum=0;
  while(fscanf(fpin,"%lf %lf \n",&dummy,&dummy )!=EOF ){
    cylindernum++;
  }
  if ( ( cylinderval = (double** )malloc(sizeof(double*)*(cylindernum+1)) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  for (i=0 ; i<=cylindernum ;i++){
    if ( ( cylinderval[i] = (double* )malloc(sizeof(double)*2) ) == NULL ){
      fprintf(stderr ,"Enough memoly is not available.");
      exit(EXIT_FAILURE);
    }
  } 
  cylindernum=0;
  fclose(fpin);
  if((fpin=fopen(in,"r"))==NULL){
    fprintf(stderr ,"File can not be opened.\n");
    exit(1);
  }
  while(fscanf(fpin,"%lf %lf \n",&cylinderval[cylindernum][0],&cylinderval[cylindernum][1] )!=EOF ){
    cylindernum++;
  }
  fclose(fpin);
  cylinderval[cylindernum][0] = -1;
  i=0;
  for (x = 0 ;x < sizex ;x++){
    while(floor(cylinderval[i][0]+0.5) != x && cylinderval[i][0] != -1){
      i++;
    }
    DEBUGPRINT4("%g %g %g %d\n",floor(cylinderval[i][0]+0.5),cylinderval[i][0],cylinderval[i][1],x);
    if (cylinderval[i][0] == -1){
      fprintf(stderr ,"Data for R=%d does not exist!" ,x);
      exit(1);
    }
    data=cylinderval[i][1];
    for (y=0 ;y < sizey ;y++){
      mrcPixelDataSet(out ,x ,y ,0 ,data  ,mrcPixelRePart);
    }
  }
  mrcStatDataSet(out,0);
}






void lmrc2DImageSetFunction(mrcImage* out ,double (*func)(double x ,double y ,double param) ,int sizex ,int sizey ,double length ,double param)
{

/* variables */
  int x,y;
  double data;

/* Header Create */
  out->HeaderN.x = sizex;
  out->HeaderN.y = sizey;
  out->HeaderN.z = 1;
  out->HeaderMode = mrcFloatImage;
  out->HeaderM.x = 0.0;
  out->HeaderM.y = 0.0;
  out->HeaderM.z = 0.0;
  out->HeaderLength.x = length;  
  out->HeaderLength.y = length;
  out->HeaderLength.z = length;
  mrcInit(out ,NULL);

/* begin */
  for (y = 0 ;y < sizey ;y++){
    for (x = 0 ;x < sizex ;x++){
      data = func( (double)x ,(double)y ,(double)sizex);
      mrcPixelDataSet(out ,x ,y ,0 ,data  ,mrcPixelRePart);
    }
    DEBUGPRINT1("%d ",y);
  }
  mrcStatDataSet(out,0);
}


double makecylinder(double x ,double y ,double sizex)
{
/* variables */
  double radius,ix,data;

/* initialization */
  radius = sizex/2;
  ix = (sizex-1)/2;

/* begin */
  if ( fabs(ix-x) < radius ){
/*    data = cos( fabs(ix-x) / radius *PI ) + 1.0; */
    data = sqrt(radius*radius-(ix-x)*(ix-x));
  } else {
    data = 0;
  }
  return(data);
}
