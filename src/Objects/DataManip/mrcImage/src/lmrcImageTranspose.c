/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageTranspose ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageTranspose 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageTranspose ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "./lmrcImageTranspose.h"


void
lmrcImageTransposeUsage(FILE* fpt)
{
fprintf(stdout ,"----- mode1 -----\n");
fprintf(stdout ,"0:+90degree in xy plane around z-axis: x->+y\n");
fprintf(stdout ,"1:-90degree in xy plane around z-axis: x->-y\n");
fprintf(stdout ,"2:+90degree in yz plane around x-axis: y->+z\n");
fprintf(stdout ,"3:-90degree in yz plane around x-axis: y->-z\n");
fprintf(stdout ,"4:+90degree in zx plane around y-axis: z->+x\n");
fprintf(stdout ,"5:-90degree in zx plane around y-axis: z->-x\n");
fprintf(stdout ,"----- mode2 -----\n");
fprintf(stdout ,"0: Image\n");
fprintf(stdout ,"1: Ref Image(mode1 =0 or 1)\n");
}

void lmrcImageTranspose(mrcImage* out , mrcImage* in ,int mode ,int mode2)
{
  
/* variables */
  int x,y,ox,oy,oz,flag,z;
  double data;
  mrcRefHeader header;

/* Initialization */
  out->Header = in->Header;
  switch (mode){
  case 0:
  case 1: {
    out->HeaderN.x = in->HeaderN.y;
    out->HeaderN.y = in->HeaderN.x;
    break;
  }
  case 2:
  case 3: {
    out->HeaderN.y = in->HeaderN.z;
    out->HeaderN.z = in->HeaderN.y;
	break;
  }
  case 4:
  case 5: {
    out->HeaderN.z = in->HeaderN.x;
    out->HeaderN.x = in->HeaderN.z;
	break;
  }
  dafault: {
  	fprintf(stderr, "Not supported modelmrcImageTranspose: %d\n", mode);
  }
  }
  mrcInit(out,NULL);

/* begin */
  flag = 0;
  if (mode2){
    flag = 1;
    lmrcRefHeaderGet(&header ,in);
    lmrcRefHeaderSet(out ,&header);
  }
  for (z=flag; z < in->HeaderN.z ;z++){
  for (y=0;    y < in->HeaderN.y ;y++){
  for (x=0;    x < in->HeaderN.x ;x++){
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	switch (mode){
	case 0:
	  ox = in->HeaderN.y - 1 - y;
	  oy = x;
	  oz = z;
	  break;
	case 1:
	  ox = y;
	  oy = in->HeaderN.x - 1 - x;
	  oz = z;
	  break;
	case 2:
	  ox = x;
	  oy = in->HeaderN.z - 1 - z;
	  oz = y;
	  break;
	case 3:
	  ox = x;
	  oy = z;
	  oz = in->HeaderN.y - -1 - y;
	  break;
	case 4:
	  ox = z;
	  oy = y;
	  oz = in->HeaderN.x - 1 - x;
	  break;
	case 5:
	  ox = in->HeaderN.z - 1 - z;
	  oy = y;
	  oz = x;
	  break;
    default: {
		fprintf(stderr, "Not supported mode in lmrcImageTranspose : %d\n", mode);
		exit(EXIT_FAILURE);
	}	
	}
	mrcPixelDataSet(out, ox, oy, oz, data, mrcPixelRePart);
  }
  }
  }
  mrcStatDataSet(out,0);
}
      
	




