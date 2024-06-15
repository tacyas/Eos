/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSubtractionCalc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSubtractionCalc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSubtractionCalc ver%I%; Date:%D% %Z%";

#include "lmrcImageSubtractionCalc.h"

void
lmrcImageSubtractionCalc(mrcImage* out, mrcImage* in1, mrcImage* in2)
{
  int x,y,z;
  double data1, data2, datao;

  out->Header = in1->Header;
  mrcInit(out, NULL);
  for (z=0; z<in1->HeaderN.z; z++){
  for (y=0; y<in1->HeaderN.y; y++){
  for (x=0; x<in1->HeaderN.x; x++){
	data1=mrcPixelDataGet(in1, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
	data2=mrcPixelDataGet(in2, x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
	datao=data1-data2;
	mrcPixelDataSet(out,x,y,z,datao,mrcPixelRePart);
  }
  }
  }
}

void 
lmrcImageMeanSubtraction(mrcImage* out, mrcImage* in){
  int x,y,z;
  double data,sum,mean,N;

  sum=0,N=0;
  for(x=0;x<in->HeaderN.x;x++){
  for(y=0;y<in->HeaderN.y;y++){
  for(z=0;z<in->HeaderN.z;z++){
      mrcPixelDataGet(in,x,y,0,&data,mrcPixelRePart,mrcPixelHowNearest);
      sum+=data;
      N++;
  }
  }
  }

  mean=sum/N;
  lmrcImageSubtraction(out, in, mean);	
}


void 
lmrcImageMinSubtraction(mrcImage* out,mrcImage* in){
  int x,y,z;
  double data,min;

  mrcPixelDataGet(in,0,0,0,&min,mrcPixelRePart,mrcPixelHowNearest);
  for(x=0;x<in->HeaderN.x;x++){
  for(y=0;y<in->HeaderN.y;y++){
  for(z=0;z<in->HeaderN.z;z++){
      mrcPixelDataGet(in,x,y,0,&data,mrcPixelRePart,mrcPixelHowNearest);
      if(data<min) {
  		  min=data;
	  }
  }
  }
  }
  lmrcImageSubtraction(out, in, min);	
}

void 
lmrcImageSubtraction(mrcImage* out, mrcImage* in, double value){
  int x,y,z;
  double data,min;

  out->Header=in->Header;
  mrcInit(out,NULL);

  for(x=0;x<in->HeaderN.x;x++){
  for(y=0;y<in->HeaderN.y;y++){
  for(z=0;z<in->HeaderN.z;z++){
        mrcPixelDataGet(in, x,y,z,&data,mrcPixelRePart,mrcPixelHowNearest);
        mrcPixelDataSet(out,x,y,z,data-value,mrcPixelRePart);
  }
  }
  }
  mrcStatDataSet(out,0);
}

