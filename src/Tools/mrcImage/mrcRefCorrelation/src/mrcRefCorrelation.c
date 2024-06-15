/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefCorrelation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefCorrelation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Random.h"
#include "mrcRefUtil.h"


/* prototype */
void lmrcRefImgAllCorrelation(mrcImage* out ,mrcImage* in );
void lmrcRefImgRndCorrelation(mrcImage* out ,mrcImage* in ,int num);
void lmrcRefImgw0a0Correlation(mrcImage* out ,mrcImage* in );
void lmrcRefImgAllCrossCorrelation(mrcImage* out ,mrcImage* in ,mrcImage *ref);
void lmrcRefImgRndCrossCorrelation(mrcImage* out ,mrcImage* in ,mrcImage* ref ,int num);
void lmrcRefImgw0a0CrossCorrelation(mrcImage* out ,mrcImage* in ,mrcImage* ref );
void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefCorrelationInfo info;

/* variables */
	mrcImage in;
	mrcImage out;
	mrcImage ref;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("srart \n");
	mrcFileRead(&in ,info.In ,"in main" ,0);
	if (info.mode) {
	  mrcFileRead(&ref ,info.In2 ,"in main",0);
	  switch(info.mode2){
	  case 0:
	    DEBUGPRINT("Cross \n");
	    lmrcRefImgAllCrossCorrelation(&out ,&in ,&ref);
	    break;
	  case 1:
	    if (!info.number) {info.number = (in.HeaderN.z - 1)/10; } 
	    lmrcRefImgRndCrossCorrelation(&out ,&in ,&ref ,info.number);
	    break;
	  case 2:
	    lmrcRefImgw0a0CrossCorrelation(&out ,&in ,&ref);
	  }
	} else {
	  switch(info.mode2){
	  case 0:
	    lmrcRefImgAllCorrelation(&out ,&in ); 
	    break;
	  case 1:
	    if (!info.number) {info.number = (in.HeaderN.z - 1)/10; } 
	    lmrcRefImgRndCorrelation(&out ,&in ,info.number);
	    break;
	  case 2:
	    lmrcRefImgw0a0Correlation(&out ,&in );
	  }
	}
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}
 
void
additionalUsage()
{
  fprintf(stdout,"----test----");
}

void lmrcRefImgAllCorrelation(mrcImage* out ,mrcImage* in )
{
/* variables */
  int z1,z2;
  double c;
  mrcImage tmp1,tmp2;
  mrcRefHeader rhead;

/* intialization */
  out->Header = in->Header;
  out->HeaderN.x = out->HeaderN.y = in->HeaderN.z - 1;
  out->HeaderN.z = 2;
  mrcInit(out,NULL);
  lmrcRefHeaderGet(&rhead ,in);
  lmrcRefHeaderSet(out ,&rhead);
  
/* begin */
  lmrcRefNormalization(in);
  for (z1 = 1 ;z1 < in->HeaderN.z ;z1++ ){
    for (z2 = 1 ;z2 <= z1 ;z2++ ){
      lmrc3DZ1ImgGet(&tmp1 ,in ,z1);
      lmrc3DZ1ImgGet(&tmp2 ,in ,z2);
      c = lmrcRef2DImgCorrelation(&tmp1 ,&tmp2 );
      mrcPixelDataSet(out ,z1 - 1 ,z2 - 1 ,1 ,c ,mrcPixelRePart);
      mrcPixelDataSet(out ,z2 - 1 ,z1 - 1 ,1 ,c ,mrcPixelRePart);
/*      DEBUGPRINT2("%d %d ",z1,z2);  */
    }
    DEBUGPRINT1("%d ",z1);
  }
  mrcStatDataSet(out,0);
}


void lmrcRefImgRndCorrelation(mrcImage* out ,mrcImage* in ,int num)
{
/* variables */
  int z1,z2,x;
  double c;
  mrcImage tmp1,tmp2;
  union {
    mrcRefHeader Refheader;
    mrcRefCorHeader RefCorheader;
  }uni; 
  
/* intialization */
  out->Header = in->Header;
  out->HeaderN.x = num;
  out->HeaderN.y = in->HeaderN.z;	
  out->HeaderN.z = 2;
  mrcInit(out,NULL);
  lmrcRefHeaderGet(&(uni.Refheader) ,in);
  uni.RefCorheader.mode = 1;
  lmrcRefCorHeaderSet(out ,&(uni.RefCorheader) );

/* begin */
  
  lmrcRefNormalization(in);
  lRandShuffle();
  for (x = 0 ;x < num ;x++ ){
    z1 = (int)(random() * (in->HeaderN.z-1) ) +1;	    	
    fprintf(stderr,"%d ",z1);
    for (z2 = 1 ;z2 < in->HeaderN.z ;z2++ ){
      lmrc3DZ1ImgGet(&tmp1 ,in ,z1);
      lmrc3DZ1ImgGet(&tmp2 ,in ,z2);
      c = lmrcRef2DImgCorrelation(&tmp1 ,&tmp2 );
      mrcPixelDataSet(out ,x ,z2 - 1 ,1 ,c ,mrcPixelRePart);
    }
    mrcPixelDataSet(out ,x ,in->HeaderN.z-1 ,1 ,z1 - 1 ,mrcPixelRePart);
  }
  mrcStatDataSet(out,0);
}


void lmrcRefImgw0a0Correlation(mrcImage* out ,mrcImage* in )
{
/* variables */
  int z1,z2,x;
  mrcRefDegCoordinate phi;
  double c;
  mrcImage tmp1,tmp2;
  union {
    mrcRefHeader Refheader;
    mrcRefCorHeader RefCorheader;
  }uni; 
  
/* intialization */
  lmrcRefHeaderGet(&(uni.Refheader) ,in);
  out->Header = in->Header;
  out->HeaderN.x = (uni.Refheader.wp / uni.Refheader.dp * 2 + 1);
  out->HeaderN.y = in->HeaderN.z;	
  out->HeaderN.z = 2;
  mrcInit(out,NULL);
  uni.RefCorheader.mode = 2;
  lmrcRefCorHeaderSet(out ,&(uni.RefCorheader) );
    
/* begin */
  
  x = 0;
  lmrcRefNormalization(in);
  DEBUGPRINT("start \n");
  for (phi = uni.Refheader.ip - uni.Refheader.wp ;phi <= uni.Refheader.ip + uni.Refheader.wp ;phi += uni.Refheader.dp  ){
    z1 = lmrcRefCorrelationGetCordinate(phi,0,0,&(uni.RefCorheader) ) +1;
    fprintf(stderr,"%d ",z1);
    for (z2 = 1 ;z2 < in->HeaderN.z ;z2++ ){
      lmrc3DZ1ImgGet(&tmp1 ,in ,z1);
      lmrc3DZ1ImgGet(&tmp2 ,in ,z2);
      c = lmrcRef2DImgCorrelation(&tmp1 ,&tmp2 );
      mrcPixelDataSet(out ,x ,z2 - 1 ,1 ,c ,mrcPixelRePart);
    }
    mrcPixelDataSet(out ,x ,in->HeaderN.z-1 ,1 ,z1 - 1 ,mrcPixelRePart);
    x++;
  }
  mrcStatDataSet(out,0);
}


void lmrcRefImgAllCrossCorrelation(mrcImage* out ,mrcImage* in ,mrcImage *ref)
{
/* variables */
  int z1,z2;
  double c;
  mrcImage tmp1,tmp2;
  mrcRefHeader rhead;

/* intialization */
  out->Header = in->Header;
  out->HeaderN.x = out->HeaderN.y = in->HeaderN.z - 1;
  out->HeaderN.z = 2;
  mrcInit(out,NULL);
  DEBUGPRINT2("%d %d cor ",out->HeaderN.x ,out->HeaderN.z);
  lmrcRefHeaderGet(&rhead ,in);
  DEBUGPRINT("get ");
  lmrcRefHeaderSet(out ,&rhead);
  DEBUGPRINT("Header ");
/* begin */
  
  lmrcRefNormalization(in);
  lmrcRefNormalization(ref); 
  DEBUGPRINT("Norm ");
  for (z1 = 1 ;z1 < in->HeaderN.z ;z1++ ){
    for (z2 = 1 ;z2 < in->HeaderN.z ;z2++ ){
      DEBUGPRINT1("%d ",z2);
      lmrc3DZ1ImgGet(&tmp1 ,in ,z1);
      lmrc3DZ1ImgGet(&tmp2 ,ref ,z2);
      c = lmrcRef2DImgCorrelation(&tmp1 ,&tmp2 );
      mrcImageFree(&tmp1,"lmrcRefImgAllCrossCorrelation");
      mrcImageFree(&tmp2,"lmrcRefImgAllCrossCorrelation");
      mrcPixelDataSet(out ,z1 - 1 ,z2 - 1 ,1 ,c ,mrcPixelRePart);

/*      DEBUGPRINT2("%d %d ",z1,z2);  */
    }
    DEBUGPRINT1("%d ",z1);
  }
  mrcStatDataSet(out,0);
}


void lmrcRefImgRndCrossCorrelation(mrcImage* out ,mrcImage* in ,mrcImage* ref ,int num)
{
/* variables */
  int z1,z2,x;
  double c;
  mrcImage tmp1,tmp2;
  union {
    mrcRefHeader Refheader;
    mrcRefCorHeader RefCorheader;
  }uni; 
  
/* intialization */
  out->Header = in->Header;
  out->HeaderN.x = num;
  out->HeaderN.y = in->HeaderN.z;	
  out->HeaderN.z = 2;
  mrcInit(out,NULL);
  lmrcRefHeaderGet(&(uni.Refheader) ,in);
  uni.RefCorheader.mode = 1;
  lmrcRefCorHeaderSet(out ,&(uni.RefCorheader) );

/* begin */
  lRandShuffle();
  lmrcRefNormalization(in);
  lmrcRefNormalization(ref);
  DEBUGPRINT("start \n");
  for (x = 0 ;x < num ;x++ ){
    z1 = (int)(random() * (in->HeaderN.z-1) ) +1;	    	
    fprintf(stderr,"%d ",z1);
    for (z2 = 1 ;z2 < in->HeaderN.z ;z2++ ){
      lmrc3DZ1ImgGet(&tmp1 ,in ,z1);
      lmrc3DZ1ImgGet(&tmp2 ,ref ,z2);
      c = lmrcRef2DImgCorrelation(&tmp1 ,&tmp2 );
      mrcPixelDataSet(out ,x ,z2 - 1 ,1 ,c ,mrcPixelRePart);
    }
    mrcPixelDataSet(out ,x ,in->HeaderN.z-1 ,1 ,z1 - 1 ,mrcPixelRePart);
  }
  mrcStatDataSet(out,0);
}


void lmrcRefImgw0a0CrossCorrelation(mrcImage* out ,mrcImage* in ,mrcImage* ref )
{
/* variables */
  int z1,z2,x;
  mrcRefDegCoordinate phi;
  double c;
  mrcImage tmp1,tmp2;
  union {
    mrcRefHeader Refheader;
    mrcRefCorHeader RefCorheader;
  }uni; 
  
/* intialization */
  lmrcRefHeaderGet(&(uni.Refheader) ,in);
  out->Header = in->Header;
  out->HeaderN.x = (uni.Refheader.wp / uni.Refheader.dp * 2 + 1);
  out->HeaderN.y = in->HeaderN.z;	
  out->HeaderN.z = 2;
  mrcInit(out,NULL);
  uni.RefCorheader.mode = 2;
  lmrcRefCorHeaderSet(out ,&(uni.RefCorheader) );
    
/* begin */
  
  x = 0;
  lmrcRefNormalization(in);
  lmrcRefNormalization(ref);
  DEBUGPRINT("start \n");
  for (phi = uni.Refheader.ip - uni.Refheader.wp ;phi <= uni.Refheader.ip + uni.Refheader.wp ;phi += uni.Refheader.dp  ){
    z1 = lmrcRefCorrelationGetCordinate(phi,0,0,&(uni.RefCorheader) ) +1;
    fprintf(stderr,"%d ",z1);
    for (z2 = 1 ;z2 < in->HeaderN.z ;z2++ ){
      lmrc3DZ1ImgGet(&tmp1 ,in ,z1);
      lmrc3DZ1ImgGet(&tmp2 ,ref ,z2);
      c = lmrcRef2DImgCorrelation(&tmp1 ,&tmp2 );
      mrcPixelDataSet(out ,x ,z2 - 1 ,1 ,c ,mrcPixelRePart);
    }
    mrcPixelDataSet(out ,x ,in->HeaderN.z-1 ,1 ,z1 - 1 ,mrcPixelRePart);
    x++;
  }
  mrcStatDataSet(out,0);
}
















