/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageNormalizedSubtraction ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageNormalizedSubtraction
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageNormalizedSubtraction ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#include "lmrcImageSubtractionCalc.h"
#include "lmrcImageDensityNormalizationByImage.h"
#include "lmrcImageSigmaCalculate.h"

#undef DEBUG
#include "genUtil.h"

int
main(int argc, char* argv[]) 
{
  mrcImage in1;
  mrcImage in2;
  mrcImage normalizedIn2;
  mrcImage out;
  static lmrcImageDensityNormalizationByImageInfo norInfo;
  long status;
  static mrcImageNormalizedSubtractionInfo info;
  static lmrcImageDensityNormalizationByImageMode mode;
  mrcImageInformation linfo;

  
  init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);

  mode = info.mode;
  /* Read File */
  mrcFileRead(&in1, info.In1, "in main", 0);
  mrcFileRead(&in2, info.In2, "in main", 0);
  
  /* Calculate NormalizedImage and a, b*/
  if(mode&lmrcImageDensityNormalizationByImageModeSigma) {
    norInfo.sigma =  lmrcImageSigmaCalculate(&in1);
  } else {
    norInfo.sigma = 1.0;
  }
  DEBUGPRINT1("%f \n ",norInfo.sigma);
  lmrcImageDenstiyNormalizationByImage(&normalizedIn2, &in2, &in1, &norInfo, mode);
  
 /* Caluculate substraction */  
  if (mode&lmrcImageDensityNormalizationByImageModeReverse) {
    lmrcImageSubtractionCalc(&out, &normalizedIn2, &in1);
  } else {
    lmrcImageSubtractionCalc(&out, &in1, &normalizedIn2);
  }
  
  /* Output */
  if(mode&lmrcImageDensityNormalizationByImageModeStdout){
    fprintf(stdout, "a= %f, b= %f, r= %f, \n", norInfo.a, norInfo.b, norInfo.r);
    fprintf(stdout, "sigma_a= %f, sigma_b= %f, \n", norInfo.sigma_a, norInfo.sigma_b);
  }
  fprintf(info.fptParamFile, "a= %f, b= %f, r= %f, \n", norInfo.a, norInfo.b, norInfo.r);
  fprintf(info.fptParamFile, "sigma_a= %f, sigma_b= %f, \n", norInfo.sigma_a, norInfo.sigma_b);
  
  if(info.flagIn2_tmp) {
    mrcStatDataSet(&normalizedIn2, 0);
    mrcFileWrite(&normalizedIn2, info.In2_tmp, "in main", 0);
  }
  
  mrcStatDataSet(&out, 0);
  mrcFileWrite(&out, info.Out, "in main", 0);

  linfo.mode = RMSofAllPixels;
  lmrcImageInformation(&linfo, &out);
  fprintf(info.fptRMSD, "RMSD: %f\n", linfo.RMS);

/*  
  fprintf(stdout, "Programmed , Composed, Written by Tomoki Inoue. \n");
  fprintf(stdout, "Thank You , ByeBye !! (^_^)// \n");
*/
  exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
  fprintf(stderr, "-- Attention ---\n");
  fprintf(stderr, "in1(default:ref) -  in2(normalized:tst) : \n");
  fprintf(stderr, "-- Mode ---\n");
  lmrcImageDensityNormalizationByImageModePrint(stderr);
}

