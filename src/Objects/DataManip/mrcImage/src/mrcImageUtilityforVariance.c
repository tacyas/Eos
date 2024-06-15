#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"
#include "mrcRefUtil.h"
#include "time.h"
#include "Random.h"

void lmrcImageFilteringbyFileForVariance(mrcImage* out ,mrcImage* in ,double** filterval ,int mode)
{
  /* mode 0 filterval is for R */
  /* mode 1 filterval is for X */

/* variance */
  mrcImage infft,filterfft,filter,filter2,filter2fft,outfft;

/* begin */
  DEBUGPRINT("lmrcImageFilteringbyFileForVariance \n");
  lmrcImageFFT(&infft,in,0);
  filterfft.Header = infft.Header;
  mrcInit(&filterfft,0); 

  lmrcImageFTSetbyRArray(&filterfft ,filterval ,mode);
  lmrcImageFFT(&filter ,&filterfft ,0);
  lmrcImageMultiplyingbyMrc(&filter2 ,&filter ,&filter);
  lmrcImageFFT(&filter2fft ,&filter2 ,0);
  lmrcImageMultiplyingbyMrc(&outfft ,&infft ,&filter2fft);
  lmrcImageFFT(out ,&outfft ,0);
  mrcStatDataSet(out,0);
}

