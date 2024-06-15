/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageOddBoxel ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageOddBoxel
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageOddBoxel ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#define EPS 1e-20
#include "genUtil.h"
#include "mrcImage.h"
#include "nr2.h"
#include "mrcRefUtil.h"
#include "lmrcImageMultiplying.h"

/* prototypes */
void lmrcImageScoreCalc (mrcImage* out, mrcImage* in, int N, double Th, int flagAbs);
void lmrcImageAveragingForImages(mrcImage* avr, mrcImage* in, int N, int mode);
void lmrcImageStandardDeviationForImages(mrcImage* dev, mrcImage* in, int N, int mode);
void lmrcImageSqr(mrcImage* in, int mode);
void lmrcImageSqrt(mrcImage*in, int mode);
void llmrcImageScoreCalc(mrcImage* score, mrcImage* in, mrcImage* avr, mrcImage* dev, int flagabs);
void lmrcImageScoreCalcWithoutOddBoxels(mrcImage* out, mrcImage* in, int N, double Th, int AbsoluteFlag, long finalpixelnum, int IterFlag);
float lAvrCalcForVectorWithFlag(float* in ,float* flag, int N);
float lStandardDeviationCalcForVectorWithFlag(float* in, float* flag, int N);


int
main(int argc, char* argv[]) 
{
/* variables */
	mrcImageOddBoxelInfo info;
	long i,finalpixelnum,n;
	mrcImage* in;
	mrcImage* out;
	char outname[256];
	double level,vol;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	if ( ( in = (mrcImage *)malloc(sizeof(mrcImage)*info.flagIn) ) == NULL){
	  fprintf(stderr, "Enough memory is not available!\n");
	  exit(EXIT_FAILURE);
	}
	for (i=0; i<info.flagIn; i++){
	  mrcFileRead(&in[i], info.In[i], "in main file", 0);
	}
	if ( ( out = (mrcImage *)malloc(sizeof(mrcImage)*info.flagIn) ) == NULL){
	  fprintf(stderr, "Enough memory is not available!\n");
	  exit(EXIT_FAILURE);
	}
	for (i=0; i<info.flagIn; i++){
	  out[i].Header=in[i].Header;
	  mrcInit(&out[i], 0);
	}
	if (!info.Iteration){
	  finalpixelnum = in[0].HeaderN.x*in[0].HeaderN.y*in[0].HeaderN.z*info.flagIn;
	} else {
	  if (info.flagBoxel){
	    finalpixelnum = info.Boxel;
	  } else {
	    n = in[0].HeaderN.x*in[0].HeaderN.y*in[0].HeaderN.z*info.flagIn;
	    level = ((double)info.nMolecule)*info.MolecularWeight/info.Density*10.0/6.02;
	    vol = in[0].HeaderLength.x*in[0].HeaderLength.y*in[0].HeaderLength.z;
	    finalpixelnum = (unsigned int)((double)level)/vol;
	  }
	}
	lmrcImageScoreCalcWithoutOddBoxels(out, in, info.flagIn, info.Th, info.Absolute, finalpixelnum, info.Iteration);

	for (i=0; i<info.flagIn; i++){
	  strcpy(outname, info.In[i]);
	  strcat(outname, ".score");
	  mrcFileWrite(&out[i] ,outname ,"in main" ,0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageScoreCalc (mrcImage* out, mrcImage* in, int N, double Th, int flagAbs)
{
  mrcImage avr,dev,score;
  int n;
  mrcImageParaTypeRealCoord dum;

  lmrcImageAveragingForImages(&avr, in, N, 0);
  lmrcImageStandardDeviationForImages(&dev, in, N, 1);
  for (n=0; n<N; n++){
    llmrcImageScoreCalc(&score, &in[n], &avr, &dev, flagAbs);
    dum.x = dum.y = dum.z =0;
    lmrcImageCopy(&out[n], &score, dum);
    mrcImageFree(&score,"");
  }
}

void  lmrcImageAveragingForImages(mrcImage* avr, mrcImage* in, int N, int mode)
{
  int n;
  mrcImage sum;
  double factor;
  
  sum.Header = in[0].Header;
  mrcInit(&sum,0);

  for (n=0; n<N; n++){
    llmrcImageAdd(&sum, &in[n]);
  }
  factor = 1.0/N;
  lmrcImageMultiplying(avr, &sum, factor, sum.HeaderMode);
  mrcStatDataSet(avr, 0);
  mrcImageFree(&sum,0);
}

void   lmrcImageStandardDeviationForImages(mrcImage* dev, mrcImage* in, int N, int mode)
{
  int n,x,y,z;
  mrcImage sum2,avr,avr2,tmp;
  double factor,data1,data2;

  sum2.Header = in[0].Header;
  mrcInit(&sum2,0);
  lmrcImageAveragingForImages(&avr, in, N, 0);
  
  for (n=0; n<N; n++){
    for (z=0; z<in[0].HeaderN.z; z++){
      for (y=0; y<in[0].HeaderN.y; y++){
	for (x=0; x<in[0].HeaderN.x; x++){
	  mrcPixelDataGet(&sum2 ,x ,y ,z ,&data1 ,mrcPixelRePart ,mrcPixelHowNearest);
	  mrcPixelDataGet(&in[n] ,x ,y ,z ,&data2 ,mrcPixelPow ,mrcPixelHowNearest);
	  data1 += data2;
	  mrcPixelDataSet(&sum2 ,x ,y ,z ,data1 ,mrcPixelRePart);
	}
      }
    }
  }
  factor=1.0/N;
  lmrcImageMultiplying(&avr2, &sum2, factor, sum2.HeaderMode);

  lmrcImageSqr(&avr,0);

  llmrcImageSub(&tmp, &avr2, &avr);

  factor=N/(N-1.0);
  lmrcImageMultiplying(dev, &tmp, factor, tmp.HeaderMode);
  lmrcImageSqrt(dev,0);
  mrcStatDataSet(dev, 0);
  mrcImageFree(&sum2,"");
  mrcImageFree(&avr,"");
  mrcImageFree(&avr2,"");
  mrcImageFree(&tmp,"");
}

void lmrcImageSqr(mrcImage* in, int mode)
{
  int x,y,z;
  double data;

  for (z=0; z<in[0].HeaderN.z; z++){
    for (y=0; y<in[0].HeaderN.y; y++){
      for (x=0; x<in[0].HeaderN.x; x++){
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	data *= data;
	mrcPixelDataSet(in ,x ,y ,z ,data ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(in, 0);
}

void lmrcImageSqrt(mrcImage*in, int mode)
{
  int x,y,z;
  double data;
  for (z=0; z<in[0].HeaderN.z; z++){
    for (y=0; y<in[0].HeaderN.y; y++){
      for (x=0; x<in[0].HeaderN.x; x++){
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	if (data > EPS){
	  data = sqrt(data);
	} else {
	  data = 0;
	}
	mrcPixelDataSet(in ,x ,y ,z ,data ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(in, 0);
}
 
void llmrcImageScoreCalc(mrcImage* score, mrcImage* in, mrcImage* avr, mrcImage* dev, int flagAbs)
{
  int x,y,z;
  double dataavr,datadev,data;
 
  score->Header = avr->Header;
  mrcInit(score,0);
  for (z=0; z<avr->HeaderN.z; z++){
    for (y=0; y<avr->HeaderN.y; y++){
      for (x=0; x<avr->HeaderN.x; x++){
	mrcPixelDataGet(avr ,x ,y ,z ,&dataavr, mrcPixelRePart ,mrcPixelHowNearest);
	mrcPixelDataGet(dev ,x ,y ,z ,&datadev, mrcPixelRePart ,mrcPixelHowNearest);
	mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart ,mrcPixelHowNearest);
	if (datadev > EPS){
	  data = (data - dataavr) / datadev;
	} else {
	  data = 0;
	}
	if (flagAbs){
	  data = fabs(data);
	}
	mrcPixelDataSet(score ,x ,y ,z ,data, mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(score, 0);
}

void lmrcImageScoreCalcWithoutOddBoxels(mrcImage* out, mrcImage* in, int N, double Th, int AbsoluteFlag, long finalpixelnum, int IterFlag)
{
  long totalpixelnum,n,pixelnum,pos,secpos,allmaxn,secn,x,y,z,allmaxpos,oneimagepixelnum;
  mrcImage avr,dev;
  float** dataarray;
  float** flag;
  float* maxscore;
  int* maxn;
  double data,allmax,avrdata,devdata,scoredata;
   
  DEBUGPRINT("lmrcImageScoreCalcWithoutOddBoxels start \n");
  totalpixelnum = in[0].HeaderN.x * in[0].HeaderN.y * in[0].HeaderN.z *N;
  oneimagepixelnum = in[0].HeaderN.x * in[0].HeaderN.y * in[0].HeaderN.z;
  dataarray=matrix(0, oneimagepixelnum, 0, N-1); 
  flag=matrix(0, oneimagepixelnum-1, 0, N-1); 
  pixelnum = totalpixelnum;
  maxscore = vector(0,oneimagepixelnum-1);
  maxn = ivector(0,oneimagepixelnum-1);
  DEBUGPRINT1("%d ",pixelnum);

  lmrcImageAveragingForImages(&avr, in, N, 0);
  lmrcImageStandardDeviationForImages(&dev, in, N, 1);
  allmax = -1e+20;
  for (pos=0; pos<oneimagepixelnum; pos++){
    maxscore[pos]=-1e+20;
  }
  for (n=0; n<N; n++){
    DEBUGPRINT1("%d ",n);
    llmrcImageScoreCalc(&out[n], &in[n], &avr, &dev, AbsoluteFlag);
    pos=0;
    for (z=0; z<in[0].HeaderN.z; z++){
      for (y=0; y<in[0].HeaderN.y; y++){
	for (x=0; x<in[0].HeaderN.x; x++){
	  mrcPixelDataGet(&dev ,x ,y ,z ,&devdata ,mrcPixelRePart ,mrcPixelHowNearest);
	  mrcPixelDataGet(&avr ,x ,y ,z ,&avrdata ,mrcPixelRePart ,mrcPixelHowNearest);
	  if (devdata < EPS || avrdata < Th){
	    flag[pos][n]=1;
	    pixelnum --;
	    dataarray[pos][n]=0;
	    mrcPixelDataSet(&out[n] ,x ,y ,z ,0 ,mrcPixelRePart); 
	  } else {
	    mrcPixelDataGet(&out[n] ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	    dataarray[pos][n]=data;
	    flag[pos][n]=0;
	    if (maxscore[pos] < data){
	      maxscore[pos] = data;
	      maxn[pos] = n;
	      if (allmax < data){
		allmax = data;
		allmaxpos = pos;
		allmaxn = n;
	      } 
	    }
	  }    
	  pos++;
	}
      }
    }
  }
  
  if (IterFlag){
    flag[allmaxpos][allmaxn]=1;
    pixelnum --;
    DEBUGPRINT2("%d %d \n",finalpixelnum,pixelnum);    
    while (pixelnum >= finalpixelnum){
      avrdata = lAvrCalcForVectorWithFlag(dataarray[allmaxpos] ,flag[allmaxpos], N);
      devdata = lStandardDeviationCalcForVectorWithFlag(dataarray[allmaxpos], flag[allmaxpos], N);
      x = (allmaxpos % (in[0].HeaderN.x * in[0].HeaderN.y)) % in[0].HeaderN.x;
      y = (allmaxpos % (in[0].HeaderN.x * in[0].HeaderN.y)) / in[0].HeaderN.x;
      z = allmaxpos / (in[0].HeaderN.x * in[0].HeaderN.y);
      mrcPixelDataSet(&avr, x, y, z, avrdata, mrcPixelRePart);
      mrcPixelDataSet(&dev, x, y, z, devdata, mrcPixelRePart);
      maxscore[allmaxpos] = -1e+20;
      for (n=0; n<N; n++){      
	mrcPixelDataGet(&out[n] ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	if (devdata > EPS){
	  scoredata=(data-avrdata)/devdata;
	} else {
	  scoredata=0;
	}
	if (AbsoluteFlag){
	  scoredata = fabs(scoredata);
	}
	mrcPixelDataSet(&out[n], x, y, z, scoredata, mrcPixelRePart);
	dataarray[allmaxpos][n] = scoredata;
	
	if (! flag[allmaxpos][n]){
	  if (maxscore[allmaxpos] < scoredata){
	    maxscore[allmaxpos] = scoredata;
	    maxn[allmaxpos] = n;
	  }
	}
      }
      
      allmaxn = maxn[allmaxpos];
      allmax = maxscore[allmaxpos];
      for (pos=0; pos<oneimagepixelnum; pos++){
	if (allmax < maxscore[pos]){
	  allmax = maxscore[pos];
	  allmaxn = maxn[pos];
	  allmaxpos = pos;
	}
      }
      flag[allmaxpos][allmaxn]=1;
      pixelnum--;
    }
  }
  for (n=0; n<N; n++){
    mrcStatDataSet(&out[n],0);
  }
  
}

float lAvrCalcForVectorWithFlag(float* in ,float* flag, int N)
{
  int n,m;
  double sum;
  
  sum = 0;
  m = 0;
  for (n=0; n<N; n++){
    if (! flag[n]){
      sum += in[n];
      m ++;
    }
  }
  sum /= m;
  return(sum);
}

float lStandardDeviationCalcForVectorWithFlag(float* in, float* flag, int N)
{
  int n,m;
  double sum2,avr,dev,avr2;

  sum2=0;
  m=0;
  avr = lAvrCalcForVectorWithFlag(in, flag, N);
  for (n=0; n<N; n++){
    if (! flag[n]){
      sum2 += in[n]*in[n];
      m ++;
    }
  }
  avr2 = sum2 / m;
  if (m == 2){
    for (n=0; n<N; n++){
      flag[n]=1;
    }
  }
  dev = m/(m-1.0)* (avr2 - avr*avr);
  if (dev > EPS){
    dev = sqrt(dev);
  } else {
    dev = 0;
  }
    
  return(dev);
}










