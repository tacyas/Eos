/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSetFunction ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSetFunction
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSetFunction ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototype */
void lmrc2DImageSetFunction(mrcImage* out ,double (*func)(double x,double y) ,int sizex ,int sizey  ,double length);
void lmrc2DFourierSetFunction(mrcImage* out ,void (*func)(double* r, double* i,double x ,double y) ,int sizex ,int sizey ,double length );
double func(double x ,double y );
void lmrc3DImageSetFunction(mrcImage* out ,double (*func)(double x,double y,double z) ,int sizex ,int sizey ,int sizez ,double length);
void lmrc3DFourierSetFunction(mrcImage* out ,void (*func)(double* r, double* i,double x ,double y ,double z) ,int sizex ,int sizey ,int sizez ,double length);
double makecylinder(double x ,double y);
double makecylinder3d(double x ,double y, double z);
 
/* global constants */
        int sizex = 40;
        int sizey = 40;
        int sizez = 224;
        double length = 3.4125;  

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageSetFunctionInfo info;

/* constants */
	int nx = sizex;
	int ny = sizey;
	int nz = sizez;
/* variables */
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	lmrc3DImageSetFunction(&out ,makecylinder3d  ,nx ,ny ,nz, length);
	DEBUGPRINT("write ");
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

double makecylinder3d(double x ,double y, double z)
{
/* variables */
  double radius,ix,data,d,iy;
/* initialization */
  radius = 15;
  ix = 19.5;
  iy = 19.5;
/* begin */
  d=sqrt( (x-ix)*(x-ix)+ (y-iy)*(y-iy) );
  if ( d < radius ){
    data = cos( d / radius *PI ) + 1.0;
  } else {
    data = 0;
  }
  return(data);
}

double func(double x,double y)
{
/* variables */
  double data,dx,dy;
  double r;
  double v;
/* begin */
  r=6;
  v=2.5;
  data=0.0;
  dx = fabs(x-30);
  dy = fabs ( y-floor(y/114.66 +0.5)*114.66 );
  if (r*r - dx*dx - dy*dy > 0  ){
      data = v * 2 * sqrt (r*r - dx*dx - dy*dy );
  }
  dy = fabs ( y-floor(y/114.66 +0.5)*114.66+8.19 );
  if (r*r - dx*dx - dy*dy > 0  ){
      data += v * 2 * sqrt (r*r - dx*dx - dy*dy );
  }
  return(data);
}

void lmrc2DImageSetFunction(mrcImage* out ,double (*func)(double x ,double y) ,int sizex ,int sizey ,double length)
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
      data = func( (double)x ,(double)y);
      mrcPixelDataSet(out ,x ,y ,0 ,data  ,mrcPixelRePart);
    }
    DEBUGPRINT1("%d ",y);
  }
  mrcStatDataSet(out,0);
}

void lmrc2DFourierSetFunction(mrcImage* out ,void (*func)(double* r, double* i,double x ,double y) ,int sizex ,int sizey ,double length)
{

/* variables */
  int x,y;
  double datar,datai;

/* Header Create */
  out->HeaderN.x = sizex;
  out->HeaderN.y = sizey;
  out->HeaderN.z = 1;
  out->HeaderMode = mrcComplexFloatFT;
  out->HeaderM.x = 0.0;
  out->HeaderM.y = 0.0;
  out->HeaderM.z = 0.0;
  out->HeaderLength.x = length;  
  out->HeaderLength.y = length;
  out->HeaderLength.z = length;
  mrcInit(out ,NULL);
  DEBUGPRINT("BEGIN");

/* begin */
  for (y = - sizey / 2 ;y < sizey / 2 ;y++){
    for (x = 0 ;x <= sizex / 2 ;x++){
      func( &datar ,&datai ,(double)x ,(double)y);
      mrcPixelDataSet(out ,x ,y ,0 ,datar  ,mrcPixelRePart);
      mrcPixelDataSet(out ,x ,y ,0 ,datai  ,mrcPixelImPart);
    }
  }
  mrcStatDataSet(out,0);
}

void lmrc3DImageSetFunction(mrcImage* out ,double (*func)(double x,double y,double z) ,int sizex ,int sizey ,int sizez ,double length)
{

/* variables */
  int x,y,z;
  double data;

/* Header Create */
  out->HeaderN.x = sizex;
  out->HeaderN.y = sizey;
  out->HeaderN.z = sizez;
  out->HeaderMode = mrcFloatImage;
  out->HeaderM.x = 0.0;
  out->HeaderM.y = 0.0;
  out->HeaderM.z = 0.0;
  out->HeaderLength.x = length;  
  out->HeaderLength.y = length;
  out->HeaderLength.z = length;
  mrcInit(out ,NULL);

/* begin */
  for (z = 0 ;z < sizez ;z++){ 
    for (y = 0 ;y < sizey ;y++){
      for (x = 0 ;x < sizex ;x++){
	data = func( (double)x ,(double)y ,(double)z );
	mrcPixelDataSet(out ,x ,y ,z ,data  ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(out,0);
}
  
void lmrc3DFourierSetFunction(mrcImage* out ,void (*func)(double* r, double* i,double x ,double y ,double z) ,int sizex ,int sizey ,int sizez ,double length)
{

/* variables */
  int x,y,z;
  double datar,datai;

/* Header Create */
  out->HeaderN.x = sizex;
  out->HeaderN.y = sizey;
  out->HeaderN.z = sizez;
  out->HeaderMode = mrcComplexFloatFT;
  out->HeaderM.x = 0.0;
  out->HeaderM.y = 0.0;
  out->HeaderM.z = 0.0;
  out->HeaderLength.x = length;  
  out->HeaderLength.y = length;
  out->HeaderLength.z = length;
  mrcInit(out ,NULL);
  DEBUGPRINT("BEGIN");

/* begin */
  for (z = - sizez / 2 ;z < sizez / 2 ;z++){ 
    for (y = - sizey / 2 ;y < sizey / 2 ;y++){
      for (x = 0 ;x <= sizex / 2 ;x++){
	func( &datar ,&datai ,(double)x ,(double)y ,(double)z );
	mrcPixelDataSet(out ,x ,y ,z ,datar  ,mrcPixelRePart);
	mrcPixelDataSet(out ,x ,y ,z ,datai  ,mrcPixelImPart);
      }
    }
  }
  mrcStatDataSet(out,0);
}







