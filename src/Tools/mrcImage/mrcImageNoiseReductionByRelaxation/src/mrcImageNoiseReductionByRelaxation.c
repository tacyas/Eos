/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageNoiseReductionByRelaxation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageNoiseReductionByRelaxation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageNoiseReductionByRelaxation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "Memory.h"
#include "mrcImage.h"
#undef DEBUG
#include "genUtil.h"
#include "lmrcImageSigmaCalculate.h"
#include "lmrcImageDataMaxAndMinGetByImage.h"
#include "lmrcImageDataStraightCopy.h"
#include "lmrcImagePixelSummationOfProbabilityGetByImage.h"
#include "lmrcImageProportionalDensityLevelSetByImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxationRValueSet.h"
#include "lmrcImageSecondNoiseReductionByRelaxationDijDimensionSet.h"
#include "lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate.h"
#include "lmrcImageSecondNoiseReductionByRelaxationDijValueSet.h"
#include "lmrcImageSecondNoiseReductionByRelaxationQValueSet.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"

void
main(int argc, char* argv[]) 
{
  mrcImage  in;
  mrcImage  out;
  mrcImage* p0;
  mrcImage* pPrev;
  mrcImage  summationOfProbability;
  double    datamax, datamin;
  double*   densityLevel;
  double*   r;
  double*   d;
  mrcImage* q;
  int l;
  
  mrcImageNoiseReductionByRelaxationInfo info;
  
  lmrcImageNoiseReductionByRelaxationInfo linfo;
  lmrcImageNoiseReductionByRelaxationMode lmode;
  
  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode1 mode1;
  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2 mode2;
  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode3 mode3;
  
  init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);
  
  mrcFileRead(&in, info.In, "in main", 0);
  
  /* Get Maximum and Minimum */
  //fprintf(stdout," This is Noise Reduction by Relaxation Ver 4.0 .\n");
  //fprintf(stdout," ---All right are reserved in the Univ. of Tokyo, only.---\n");
  lmrcImageDataMaxAndMinGetByImage(&in, &datamax, &datamin);
  linfo.datamax = datamax;
  linfo.datamin = datamin;
  if (info.flagmax){
    linfo.datamax = info.max;
  }
  if (info.flagmin){
    linfo.datamin = info.min;
  }
  if ( linfo.datamax < linfo.datamin){
    fprintf(stderr, " Maximun and Minimun Set Error !! (ToT)/\n");
    exit(EXIT_FAILURE);
  }
  
  
  /* Get Sigma and Number of categories, classes */
  linfo.SD = lmrcImageSigmaCalculate(&in);
  linfo.classNumber = info.Nlab;
  
  
  /* Set the Density Level of Each Category */
  densityLevel= (double*)memoryAllocate(sizeof(double)*(info.Nlab), "in main");
  lmrcImageProportionalDensityLevelSetByImage(densityLevel, &linfo);
  
  
  /* mrcImage Initialization for OutPut data and Summation of Probability */
  out.Header = in.Header;
  mrcInit(&out, NULL);
  summationOfProbability.Header = in.Header;
  mrcInit(&summationOfProbability, NULL);
  
  /* mrcImage Initialization for First Probability */
  p0 = (mrcImage*)memoryAllocate(sizeof(mrcImage)*(info.Nlab), "in main");
  for(l=0; l<info.Nlab; l++) {
     p0[l].Header =  in.Header;
     mrcInit(&(p0[l]), NULL);
  }
  
  
  /* Get the Original-First Probability */ 
  fprintf(stdout," Now we are going to do the First Noise reduction.\n");
  lmrcImageFirstNoiseReductionByRelaxation( &out, p0 , &in, &summationOfProbability, densityLevel, &linfo);
  mrcStatDataSet(&out, 0);
  mrcFileWrite(&out, info.Out, "in main" ,0);
  
  fprintf(stdout," First NoiseReduction OK !! (^_^)\n");
  
  
  /* Get the Next-Second Probability */ 
  if (info.flagtimes){ 
    if (info.times < 2 ){
      fprintf(stderr, " Times Error !! (ToT)/\n");
      exit(EXIT_FAILURE);
    }
    else{
      
      /* Get the Next Probability - Set Proportional Value r */
      fprintf(stdout," Now we are going to do the Second Noise reduction .\n");
      fprintf(stdout," .....Wait a minute.....\n");
      r = (double*)memoryAllocate(sizeof(double)*(info.Nlab*info.Nlab), "in main");
      lmrcImageSecondNoiseReductionByRelaxationRValueSet( r, densityLevel, &linfo);
      
      
      /* Get the next Probability - Set Proportional Value q  -- Defining dij -- */
      mode1 = info.mode1;
      mode2 = info.mode2;
      mode3 = info.mode3;
      lmrcImageSecondNoiseReductionByRelaxationDijDimensionSet( &linfo, &mode3);
      d = (double*)memoryAllocate(sizeof(double)*(linfo.ddimx*linfo.ddimy*linfo.ddimz), "in main");
      lmrcImageSecondNoiseReductionByRelaxationDijValueSet( d, &linfo, &mode1, &mode2);
      
      
      /* mrcImage Initialization and memory check for previous Probability and Next Probability */
      pPrev = (mrcImage*)memoryAllocate(sizeof(mrcImage)*(info.Nlab), "in main");
      for(l=0; l<info.Nlab; l++) {
	pPrev[l].Header =  in.Header;
	mrcInit(&(pPrev[l]), NULL);
      }
      /* mrcImageDataCopy */
      for (l=0; l<linfo.classNumber; l++){
	lmrcImageDataStraightCopy(&(pPrev[l]), &(p0[l]));
      }
      DEBUGPRINT(" transfer OK\n");
      
      /* Get the next Probability - Set Proportional Value q ,and Calculate next p */
      q = (mrcImage*)memoryAllocate(sizeof(mrcImage)*(info.Nlab), "in main");
      for(l=0; l<info.Nlab; l++) {
	q[l].Header =  in.Header;
	mrcInit(&(q[l]), NULL);
      } DEBUGPRINT(" Q OK\n");
      lmrcImageSecondNoiseReductionByRelaxationQValueSet(q, d, p0, r, &linfo);
       DEBUGPRINT(" Q OK\n");
      for ( l=0; l<info.times; l++){
	lmrcImageSecondNoiseReductionByRelaxation( &out, pPrev,  q, densityLevel, &linfo);
	fprintf(stdout," The %dth Noise Reduction Completed !!\n",l+2);
      }
    }
  }
  //fprintf(stdout," -------(^_^)------ Noise Reduction Ver 4.0\n");
  //fprintf(stdout," Composed, Written, Arranged by Tomochan (Tomoki Inoue).\n");
  //fprintf(stdout," Thank you, ByeBye !!\n");
  exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
