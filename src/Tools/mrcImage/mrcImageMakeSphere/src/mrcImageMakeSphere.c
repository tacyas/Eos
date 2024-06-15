/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMakeSphere ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMakeSphere
#%Z% Attention
#%Z%
*/
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
void lmrcImageMakeSphere(mrcImage* out, mrcImage* in, float Cx, float Cy, float Cz, float ir, float or, float v, float cr, int mode);
void lmrcImageMakeSphereWithOthers(mrcImage* out, mrcImage* in, float Cx, float Cy, float Cz, float ir, float or, float v, float r, double** Otherspos, int restricts,  int mode);
int
main(int argc, char* argv[]) 
{
	mrcImageMakeSphereInfo info;

/* variables */
	mrcImage in;
	mrcImage out;
	int molnum,i;
	FILE* fpother;
	double** Otherpos;
	double dum[3];

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in ,info.In ,"in main" ,0);
	if (info.mode && ! info.flagr ){
	  info.r = (info.ir + info.or)/2;
	}
	if (info.flagOther){
	  if((fpother=fopen(info.Other,"r"))==NULL){
	    fprintf(stderr ,"File can not be opened.\n");
	    exit(1);
	  }
	  molnum=0;
	  while(fscanf(fpother ,"%lg %lg %lg \n",&dum[0],&dum[1],&dum[2])!=EOF ){
	    molnum++;
	  }
	  if ( ( Otherpos = (double **)malloc(sizeof(double *)*molnum) ) == NULL ){
	    fprintf(stderr ,"Enough memoly is not available.");
	    exit(EXIT_FAILURE);
	  }
	  fclose(fpother);
	  if((fpother=fopen(info.Other,"r"))==NULL){
	    fprintf(stderr ,"File can not be opened.\n");
	    exit(1);
	  }
	  for (i=0 ;i < molnum; i++){
	    if ( ( Otherpos[i] = (double *)malloc(sizeof(double)*3) ) == NULL ){
	      fprintf(stderr ,"Enough memoly is not available.");
	      exit(EXIT_FAILURE);
	    }
	    fscanf(fpother,"%lg %lg %lg \n",&Otherpos[i][0], &Otherpos[i][1], &Otherpos[i][2]);
	    printf("%d %g %g %g \n",i,Otherpos[i][0], Otherpos[i][1], Otherpos[i][2]);
	  }
	  lmrcImageMakeSphereWithOthers(&out, &in, info.Cx, info.Cy, info.Cz, info.ir, info.or, info.Value, info.r, Otherpos, molnum, info.mode);
	} else {
	  lmrcImageMakeSphere(&out, &in, info.Cx, info.Cy, info.Cz, info.ir, info.or, info.Value, info.r, info.mode);
	}
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0: Constant\n");
	fprintf(stderr, "mode 1: Gaussian\n");
}

void lmrcImageMakeSphere(mrcImage* out, mrcImage* in, float Cx, float Cy, float Cz, float ir, float or, float v, float r, int mode)
{
  double d,data,ind,outd;
  int x,y,z;

  out->Header = in->Header;  	
  mrcInit(out, NULL);
  ind = r-ir;
  outd = or-r;

  for (z=0 ; z < out->HeaderN.z; z++){
    for (y=0 ; y < out->HeaderN.y; y++){
      for (x=0 ; x < out->HeaderN.x; x++){
	d=(z-Cz)*(z-Cz)+(y-Cy)*(y-Cy)+(x-Cx)*(x-Cx);
	if (mode == 0){
	  if (d >= ir*ir && d <= or*or){
	    mrcPixelDataSet(out, x, y, z, v, mrcPixelMag);
	  }
	} else {
	  if (d > 0){
	    d = sqrt(d);
	  }
	  if (d < r){
	    data = v * exp( - (r-d)*(r-d)/ind/ind );
	  } else {
	    data = v * exp( - (d-r)*(d-r)/outd/outd );
	  }
	  mrcPixelDataSet(out, x, y, z, data, mrcPixelMag);
	}
      }
    }
  }
  mrcStatDataSet(out ,0);
}

void lmrcImageMakeSphereWithOthers(mrcImage* out, mrcImage* in, float Cx, float Cy, float Cz, float ir, float or, float v, float r, double** Otherspos, int restricts,  int mode)
{
  double d,data,ind,outd,dother;
  int x,y,z,i,flag;

  out->Header = in->Header;  	
  mrcInit(out, NULL);
  ind = r-ir;
  outd = or-r;

  for (z=0 ; z < out->HeaderN.z; z++){
    for (y=0 ; y < out->HeaderN.y; y++){
      for (x=0 ; x < out->HeaderN.x; x++){
	d=(z-Cz)*(z-Cz) + (y-Cy)*(y-Cy) + (x-Cx)*(x-Cx);
	flag=0;
	for (i=0; i<restricts; i++){
	  dother=(z-Otherspos[i][2])*(z-Otherspos[i][2]) + 
	    (y-Otherspos[i][1])*(y-Otherspos[i][1]) + 
	    (x-Otherspos[i][0])*(x-Otherspos[i][0]);
	  if (dother < d){
	    flag = 1;
	    break;
	  }
	}
	if (!flag){
	  if (mode == 0){
	    if (d >= ir*ir && d <= or*or){
	      mrcPixelDataSet(out, x, y, z, v, mrcPixelMag);
	    }
	  } else {
	      if (d > 0){
		d = sqrt(d);
	      }
	      if (d < r){
		data = v * exp( - (r-d)*(r-d)/ind/ind );
	      } else {
		data = v * exp( - (d-r)*(d-r)/outd/outd );
	      }
	      mrcPixelDataSet(out, x, y, z, data, mrcPixelMag);
	  }
	}
      }
    }
  }
  mrcStatDataSet(out ,0); 
}











