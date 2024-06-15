/*
# mrcImageBackgroundSubtraction : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageBackgroundSubtraction
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosMath.h"
#include "mrcImage.h"

typedef struct lmrcImageBackgroundSubtractionInfo {
  double widthX; // [pixel]
  double widthY;
  double widthZ;
  double edgeX;
  double edgeY;
  double edgeZ;
  double Trim;
} lmrcImageBackgroundSubtractionInfo;

typedef enum lmrcImageBackgroundSubtractionMode {
	a=0,
	b=1
} lmrcImageBackgroundSubtractionMode;


extern int lmrcImageBackgroundSubtraction(mrcImage* out, mrcImage* in, lmrcImageBackgroundSubtractionInfo linfo, int mode);
extern int lmrcImageBackgroundSubtractionYLineSubtractAverage(mrcImage* out, mrcImage* in, lmrcImageBackgroundSubtractionInfo linfo, int mode);
extern int lmrcImageBackgroundSubtractionYLineSubtractTrimmedAverage(mrcImage* out, mrcImage* in, lmrcImageBackgroundSubtractionInfo linfo, int mode);
extern int lmrcImageBackgroundSubtractionYLineSubtractMedian(mrcImage* out, mrcImage* in, lmrcImageBackgroundSubtractionInfo linfo, int mode);
extern int lmrcImageBackgroundSubtractionYLineSubtractHodgesLehmann(mrcImage* out, mrcImage* in, lmrcImageBackgroundSubtractionInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
  mrcImage in;
  mrcImage out;
	mrcImageBackgroundSubtractionInfo info;
	lmrcImageBackgroundSubtractionInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

  linfo.widthX = info.widthX;
  linfo.widthY = info.widthY;
  linfo.widthZ = info.widthZ;
  linfo.edgeX = info.edgeX;
  linfo.edgeY = info.edgeY;
  linfo.edgeZ = info.edgeZ;

  linfo.Trim = info.Trim;
	DEBUGPRINT("Program Start\n");
  mrcFileRead(&in, info.In, "in main", 0);
  
  lmrcImageBackgroundSubtraction(&out, &in, linfo, info.mode);
  mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m 0: YLineSubtractAverage using -edgeY and -widthX \n");
	fprintf(stderr, "-m 1: YLineSubtractMedian  using -edgeY and -widthX \n");
	fprintf(stderr, "-m 2: YLineSubtractTrimmedAverage using -edgeY and -widthX, -trim\n");
	fprintf(stderr, "-m 3: YLineSubtractHodgesLehmann using -edgeY and -widthX \n");

}

int
lmrcImageBackgroundSubtraction(mrcImage* out, mrcImage* in, lmrcImageBackgroundSubtractionInfo linfo, int mode)
{
  switch(mode&0xff) {
    case 0: {
      lmrcImageBackgroundSubtractionYLineSubtractAverage(out, in, linfo, mode);
      break;
    } 
    case 1: {
      DEBUGPRINT("Median\n");
      lmrcImageBackgroundSubtractionYLineSubtractMedian(out, in, linfo, mode);
      break;
    } 
    case 2: {
      DEBUGPRINT("TrimmedAverage\n");
      lmrcImageBackgroundSubtractionYLineSubtractTrimmedAverage(out, in, linfo, mode);
      break;
    } 
    case 3: {
      DEBUGPRINT("HodgesLehmann\n");
      lmrcImageBackgroundSubtractionYLineSubtractHodgesLehmann(out, in, linfo, mode);
      break;
    } 
    default: {
      fprintf(stderr, "Not supported mode in lmrcImageBackgroundSubtraction");
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}

int
lmrcImageBackgroundSubtractionYLineSubtractAverage(mrcImage* out, mrcImage* in, lmrcImageBackgroundSubtractionInfo linfo, int mode)
{
  mrcImageParaTypeReal x, y, z;
  mrcImageParaTypeReal orgx, orgy, orgz;
  int i;
  double avg1, sum1;
  double avg2, sum2;
  double data;
  double weight;
  double offset;
  mrcImageParaTypeReal minX,maxX;
   
  out->Header =  in->Header;
  mrcInit(out, NULL);
  for(z=0; z<in->HeaderN.z; z++) {
  for(x=0; x<in->HeaderN.x; x++) {
    sum1 = 0; avg1 = 0;
    sum2 = 0; avg2 = 0;
    minX = MAX(0, (int)(x-linfo.widthX+0.5));
    maxX = MIN(in->HeaderN.x-1, (int)(x+linfo.widthX+0.5));
    //DEBUGPRINT2("x wdith: %f - %f^n ", minX, maxX);
    // Bottom
    for(y=0; y<linfo.edgeY; y++) {
    for(orgx=minX; orgx<=maxX; orgx++) {
      weight = (linfo.widthX - fabs(orgx - x))/linfo.widthX;
     // DEBUGPRINT1("weight: %f\n", weight);
      if(0<weight) {
        mrcPixelDataGet(in, orgx, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        sum1 += weight;
        avg1 += data*weight;
      }
    }
    }
    if(0<sum1) {
      avg1 /= sum1;
    } else {
      DEBUGPRINT("sum1 is zero??\n");
      avg1 = 0;
    }

    // Top
    for(y=in->HeaderN.y-linfo.edgeY-1; y<in->HeaderN.y; y++) {
    for(orgx=minX; orgx<=maxX; orgx++) {
      weight = (linfo.widthX - fabs(orgx - x))/linfo.widthX;
      if(0<weight) {
        mrcPixelDataGet(in, orgx, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        sum2 += weight;
        avg2 += data*weight;
      }
    }
    }
    if(0<sum2) {
      avg2 /= sum2;
    } else {
      DEBUGPRINT("sum2 is zero??\n");
      avg2 = 0;
    }

    DEBUGPRINT2("avg: %f - %f\n", avg1, avg2);
    for(y=0; y<in->HeaderN.y; y++) {
        offset = (avg2*y + avg1*(in->HeaderN.y - 1 - y))/(in->HeaderN.y - 1);
        mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        data -= offset;
        mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
    }
  }
  }
  return 0;
}


int
lmrcImageBackgroundSubtractionYLineSubtractMedian(mrcImage* out, mrcImage* in, lmrcImageBackgroundSubtractionInfo linfo, int mode)
{
  mrcImageParaTypeReal x, y, z;
  mrcImageParaTypeReal orgx, orgy, orgz;
  int i;
  double avg1, sum1;
  double avg2, sum2;
  double med1, med2;
  double* y1;
  double* y2;
  double data;
  double weight;
  double offset;
  mrcImageParaTypeReal minX,maxX;
   
  out->Header =  in->Header;
  mrcInit(out, NULL);

  y1 = (double*)memoryAllocate(linfo.edgeY*sizeof(double), "in Median");
  y2 = (double*)memoryAllocate(linfo.edgeY*sizeof(double), "in Median");
  for(z=0; z<in->HeaderN.z; z++) {
  for(x=0; x<in->HeaderN.x; x++) {
    minX = MAX(0, (int)(x-linfo.widthX+0.5));
    maxX = MIN(in->HeaderN.x-1, (int)(x+linfo.widthX+0.5));
    //DEBUGPRINT2("x wdith: %f - %f^n ", minX, maxX);
    // Bottom
    for(y=0; y<linfo.edgeY; y++) {
      sum1 = 0; avg1 = 0;
      for(orgx=minX; orgx<=maxX; orgx++) {
        weight = (linfo.widthX - fabs(orgx - x))/linfo.widthX;
        // DEBUGPRINT1("weight: %f\n", weight);
        if(0<weight) {
          mrcPixelDataGet(in, orgx, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
          sum1 += weight;
          avg1 += data*weight;
        }
      }
      if(0<sum1) {
        avg1 /= sum1;
      } else {
        DEBUGPRINT("sum1 is zero??\n");
        avg1 = 0;
      }
      y1[(int)y] = avg1;   
    }
    
    // Top
    for(y=in->HeaderN.y-linfo.edgeY-1; y<in->HeaderN.y; y++) {
      sum2 = 0; avg2 = 0;
      for(orgx=minX; orgx<=maxX; orgx++) {
        weight = (linfo.widthX - fabs(orgx - x))/linfo.widthX;
        if(0<weight) {
          mrcPixelDataGet(in, orgx, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
          sum2 += weight;
          avg2 += data*weight;
        }
      }
      if(0<sum2) {
        avg2 /= sum2;
      } else {
        DEBUGPRINT("sum2 is zero??\n");
        avg2 = 0;
      }
      y2[(int)(y-(in->HeaderN.y-linfo.edgeY-1))] = avg2;
    }

    med1 = eosMathMedian(y1, linfo.edgeY); 
    med2 = eosMathMedian(y2, linfo.edgeY); 
    //DEBUGPRINT2("avg: %f - %f\n", avg1, avg2);
    DEBUGPRINT2("avg: %f - %f\n", eosMathAverage(y1, linfo.edgeY), eosMathAverage(y2,linfo.edgeY));
    DEBUGPRINT2("med: %f - %f\n", med1, med2);
    for(y=0; y<in->HeaderN.y; y++) {
        offset = (med2*y + med1*(in->HeaderN.y - 1 - y))/(in->HeaderN.y - 1);
        mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        data -= offset;
        mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
    }
  }
  }
  return 0;
}


int
lmrcImageBackgroundSubtractionYLineSubtractHodgesLehmann(mrcImage* out, mrcImage* in, lmrcImageBackgroundSubtractionInfo linfo, int mode)
{
  mrcImageParaTypeReal x, y, z;
  mrcImageParaTypeReal orgx, orgy, orgz;
  int i;
  double avg1, sum1;
  double avg2, sum2;
  double med1, med2;
  double* y1;
  double* y2;
  double data;
  double weight;
  double offset;
  mrcImageParaTypeReal minX,maxX;
   
  out->Header =  in->Header;
  mrcInit(out, NULL);

  y1 = (double*)memoryAllocate(linfo.edgeY*sizeof(double), "in Median");
  y2 = (double*)memoryAllocate(linfo.edgeY*sizeof(double), "in Median");
  for(z=0; z<in->HeaderN.z; z++) {
  for(x=0; x<in->HeaderN.x; x++) {
    minX = MAX(0, (int)(x-linfo.widthX+0.5));
    maxX = MIN(in->HeaderN.x-1, (int)(x+linfo.widthX+0.5));
    //DEBUGPRINT2("x wdith: %f - %f^n ", minX, maxX);
    // Bottom
    for(y=0; y<linfo.edgeY; y++) {
      sum1 = 0; avg1 = 0;
      for(orgx=minX; orgx<=maxX; orgx++) {
        weight = (linfo.widthX - fabs(orgx - x))/linfo.widthX;
        // DEBUGPRINT1("weight: %f\n", weight);
        if(0<weight) {
          mrcPixelDataGet(in, orgx, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
          sum1 += weight;
          avg1 += data*weight;
        }
      }
      if(0<sum1) {
        avg1 /= sum1;
      } else {
        DEBUGPRINT("sum1 is zero??\n");
        avg1 = 0;
      }
      y1[(int)y] = avg1;   
    }
    
    // Top
    for(y=in->HeaderN.y-linfo.edgeY-1; y<in->HeaderN.y; y++) {
      sum2 = 0; avg2 = 0;
      for(orgx=minX; orgx<=maxX; orgx++) {
        weight = (linfo.widthX - fabs(orgx - x))/linfo.widthX;
        if(0<weight) {
          mrcPixelDataGet(in, orgx, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
          sum2 += weight;
          avg2 += data*weight;
        }
      }
      if(0<sum2) {
        avg2 /= sum2;
      } else {
        DEBUGPRINT("sum2 is zero??\n");
        avg2 = 0;
      }
      y2[(int)(y-(in->HeaderN.y-linfo.edgeY-1))] = avg2;
    }

    med1 = eosMathHodgesLehmannEstimator(y1, linfo.edgeY); 
    med2 = eosMathHodgesLehmannEstimator(y2, linfo.edgeY); 
    //DEBUGPRINT2("avg: %f - %f\n", avg1, avg2);
    DEBUGPRINT2("avg: %f - %f\n", eosMathAverage(y1, linfo.edgeY), eosMathAverage(y2,linfo.edgeY));
    DEBUGPRINT2("med: %f - %f\n", med1, med2);
    for(y=0; y<in->HeaderN.y; y++) {
        offset = (med2*y + med1*(in->HeaderN.y - 1 - y))/(in->HeaderN.y - 1);
        mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        data -= offset;
        mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
    }
  }
  }
  return 0;
}



int
lmrcImageBackgroundSubtractionYLineSubtractTrimmedAverage(mrcImage* out, mrcImage* in, lmrcImageBackgroundSubtractionInfo linfo, int mode)
{
  mrcImageParaTypeReal x, y, z;
  mrcImageParaTypeReal orgx, orgy, orgz;
  int i;
  double avg1, sum1;
  double avg2, sum2;
  double med1, med2;
  double* y1;
  double* y2;
  double data;
  double weight;
  double offset;
  mrcImageParaTypeReal minX,maxX;
   
  out->Header =  in->Header;
  mrcInit(out, NULL);

  y1 = (double*)memoryAllocate(linfo.edgeY*sizeof(double), "in Median");
  y2 = (double*)memoryAllocate(linfo.edgeY*sizeof(double), "in Median");
  for(z=0; z<in->HeaderN.z; z++) {
  for(x=0; x<in->HeaderN.x; x++) {
    sum2 = 0; avg2 = 0;
    minX = MAX(0, (int)(x-linfo.widthX+0.5));
    maxX = MIN(in->HeaderN.x-1, (int)(x+linfo.widthX+0.5));
    //DEBUGPRINT2("x wdith: %f - %f^n ", minX, maxX);
    // Bottom
    for(y=0; y<linfo.edgeY; y++) {
      sum1 = 0; avg1 = 0;
      for(orgx=minX; orgx<=maxX; orgx++) {
        weight = (linfo.widthX - fabs(orgx - x))/linfo.widthX;
        // DEBUGPRINT1("weight: %f\n", weight);
        if(0<weight) {
          mrcPixelDataGet(in, orgx, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
          sum1 += weight;
          avg1 += data*weight;
        }
      }
      if(0<sum1) {
        avg1 /= sum1;
      } else {
        DEBUGPRINT("sum1 is zero??\n");
        avg1 = 0;
      }
      y1[(int)y] = avg1;   
    }
    
    // Top
    for(y=in->HeaderN.y-linfo.edgeY-1; y<in->HeaderN.y; y++) {
      sum2 = 0; avg2 = 0;
      for(orgx=minX; orgx<=maxX; orgx++) {
        weight = (linfo.widthX - fabs(orgx - x))/linfo.widthX;
        if(0<weight) {
          mrcPixelDataGet(in, orgx, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
          sum2 += weight;
          avg2 += data*weight;
        }
      }
      if(0<sum2) {
        avg2 /= sum2;
      } else {
        DEBUGPRINT("sum2 is zero??\n");
        avg2 = 0;
      }
      y2[(int)(y-(in->HeaderN.y-linfo.edgeY-1))] = avg2;
    }

    med1 = eosMathTrimmedAverage(y1, linfo.edgeY, linfo.Trim); 
    med2 = eosMathTrimmedAverage(y2, linfo.edgeY, linfo.Trim); 
    //DEBUGPRINT2("avg: %f - %f\n", avg1, avg2);
    DEBUGPRINT2("avg: %f - %f\n", eosMathAverage(y1, linfo.edgeY), eosMathAverage(y2,linfo.edgeY));
    DEBUGPRINT2("med: %f - %f\n", med1, med2);
    for(y=0; y<in->HeaderN.y; y++) {
        offset = (med2*y + med1*(in->HeaderN.y - 1 - y))/(in->HeaderN.y - 1);
        mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        data -= offset;
        mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
    }
  }
  }
  return 0;
}


