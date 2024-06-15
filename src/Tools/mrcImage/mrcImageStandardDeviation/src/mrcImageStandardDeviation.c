/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageStandardDeviation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageStandardDeviation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageStandardDeviation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
void lmrcImageSqr(mrcImage* out ,mrcImage* in);
void lmrcImageStandardDeviationwithTh(double* sd, double* av, mrcImage* in, double Hth, double Lth,  long mode);

/*
Example:
typedef struct lmrcImageStandardDeviationInfo {
	float a;
	int   b;
} lmrcImageStandardDeviationInfo;

typedef enum lmrcImageStandardDeviationMode {
	a=0,
	b=1
} lmrcImageStandardDeviationMode;
*/

void
main(int argc, char* argv[]) 
{
	mrcImageStandardDeviationInfo info;

/* variables */
	mrcImage in;
	mrcImage out;
	mrcImage av,sqav,tmp;
	FILE* fpin;
	char infile[256];
	int filenum;
	int x,y,z;
	double data,data2;
	
/* input patameters ,file open */
	DEBUGPRINT("Program Start\n");
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	if (info.mode2){
	  if((fpin=fopen(info.In,"r"))==NULL){
	    fprintf(stderr ,"File can not be opened.\n");
	    exit(1);
	  }
	  fscanf(fpin,"%s ",infile);
	  mrcFileRead(&in ,infile ,"in main" ,0);
	  av.Header=in.Header;
	  out.Header=in.Header;
	  mrcInit(&av,0);
	  mrcInit(&out,0);
	  llmrcImageAdd(&av,&in);
	  lmrcImageSqr(&sqav,&in);
	  mrcImageFree(&in,"");
	  filenum=1;
	  
	  while(fscanf(fpin,"%s ",infile)!=EOF ){
	    DEBUGPRINT1("%s \n",infile);
	    mrcFileRead(&in ,infile ,"in main" ,0);
	    llmrcImageAdd(&av,&in);
	    lmrcImageSqr(&tmp,&in);
	    llmrcImageAdd(&sqav,&tmp);
	    mrcImageFree(&in,"");
	    mrcImageFree(&tmp,"");
	    filenum++;
	  }
	  for (x=0 ;x<in.HeaderN.x ;x++){
	    for (y=0 ;y<in.HeaderN.y ;y++){
	      for (z=0 ;z<in.HeaderN.z ;z++){
		mrcPixelDataGet(&av ,x ,y ,z ,&data ,mrcPixelRePart , mrcPixelHowNearest);
		mrcPixelDataGet(&sqav ,x ,y ,z ,&data2 ,mrcPixelRePart , mrcPixelHowNearest);
		data=data2-data*data/filenum;
		data /= (filenum - 1);
		if (info.mode == 0){
		  data = sqrt(data);
		}
		mrcPixelDataSet(&out ,x ,y ,z ,data ,mrcPixelRePart );
	      }
	    }
	  }
	  mrcStatDataSet(&out,0);
	  mrcFileWrite(&out ,info.Out ,"in main" ,0);
	} else {
	  if (info.flagHth){
	    info.mode += 2;
	  }
	  if (info.flagLth){
	    info.mode += 4;
	  }
	  mrcFileRead(&in ,info.In ,"in main" ,0);
	  lmrcImageStandardDeviationwithTh(&data, &data2, &in, info.Hth, info.Lth, info.mode); 
	  fprintf(stdout,"avr= %g \nresult= %g \n",data2,data);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Input file is a list of mrc files.\n");
	fprintf(stderr, "mode 0: Standard deviation\n");
	fprintf(stderr, "mode 1: Variation\n");
	fprintf(stderr, "mode2 0: Standard deviation or Variation in one mrcfile.\n");
	fprintf(stderr, "mode2 1: Standard deviation or Variation of each pixel between mrcfiles.\n");
}

void lmrcImageSqr(mrcImage* out ,mrcImage* in)
{
  int x,y,z;
  double data;
  out->Header = in->Header;
  mrcInit(out ,0);
  DEBUGPRINT3("%d %d %d \n",in->HeaderN.x,in->HeaderN.y,in->HeaderN.z);
  
  for (x=0 ; x<in->HeaderN.x ; x++){
    DEBUGPRINT1("%d ",x);
    for (y=0 ; y<in->HeaderN.y ;y++){
      for (z=0 ; z<in->HeaderN.z ;z++){
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart , mrcPixelHowNearest);
	data = data*data;
	mrcPixelDataSet(out ,x ,y ,z ,data ,mrcPixelRePart );
      }
    }
  }
  mrcStatDataSet(out,0);
}

void lmrcImageStandardDeviationwithTh(double* sd, double* av, mrcImage* in, double Hth, double Lth,  long mode)
{
/* variables */
  int x,y,z,flag;
  double sum2,sum,data;
  long size;

/* begin */
  size = 0;
  sum2 = 0.0;
  sum = 0.0;
  for(x=0 ;x < in->HeaderN.x ;x++) {
    for(y=0 ;y < in->HeaderN.y ;y++){
      for(z=0 ;z < in->HeaderN.z ;z++){
	flag = 0;
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	if ( (mode & 4) && (data > Lth ) ) {
	  flag ++;
	} 
	if ( (mode & 2) && (data < Hth ) ) {
	  flag ++;
	}
	if ( ((mode & 6) && flag==2) || ( !((mode & 6)==6 ) && flag == 1)){
	  sum2 += data*data;
	  sum += data;
	  size ++;
	} else if (mode == 0 || mode ==1){
	  sum2 += data*data;
	  sum += data;
	}
      }
    }
  }
  if (size == 0){
    size = in->HeaderN.x * in->HeaderN.y * in->HeaderN.z;
  }
  DEBUGPRINT4("%g %g %d %d\n",sum,sum2,size,mode);
  sum /= size;
  sum2 /= size;
  sum2 -= sum*sum;
  if (! (mode & 1 )){
    sum2 = sqrt(sum2);
  }
  *av=sum;
  *sd=sum2;
}
