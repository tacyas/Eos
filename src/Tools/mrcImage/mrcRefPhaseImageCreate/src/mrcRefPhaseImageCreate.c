/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefPhaseImageCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefPhaseImageCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefPhaseImageCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"

/* prototype */
void lmrcRefPhaseImageCreate(mrcImage* out ,mrcImage* in ,double power ,double cutoff ,int mode);
void lmrcPhaseImageCreate(mrcImage* out ,mrcImage* in ,double power ,double cutoff );

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefPhaseImageCreateInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* initialization */
 	DEBUGPRINT("start \n"); 
	mrcFileRead(&in ,info.In ,"in main" ,0); 
	if (info.mode < 4) {
	  if (info.mode == 1){
	    info.Cutoff *= lmrcRefStandardDeviation(&in) ;
	  }
	  if (info.Cutoff == -1.0){ 
	    info.Cutoff = lmrcRefStandardDeviation(&in) / 10.0 ; 
	    DEBUGPRINT1("%f \n" ,info.Cutoff);
	    if (info.Cutoff < 1e-08){ 
	      fprintf(stderr ,"Please input Cutoff. Mean is too small." ); 
	      exit(EXIT_FAILURE);
	    }  
	  }  
	} else {
	  if (info.mode == 5){
	    info.Cutoff *= lmrcImageStandardDeviation(&in) ;
	  }
	  if (info.Cutoff == -1.0){
            info.Cutoff = lmrcImageStandardDeviation(&in) / 10.0 ;
            DEBUGPRINT1("%f \n" ,info.Cutoff);
            if (info.Cutoff < 1e-08){
              fprintf(stderr ,"Please input Cutoff. Mean is too small." );
              exit(EXIT_FAILURE);
            }
          }
	}
 	DEBUGPRINT1("%f ",info.Cutoff);   

/* begin */       
 	DEBUGPRINT("Create"); 
 	lmrcRefPhaseImageCreate(&out ,&in ,info.Power ,info.Cutoff ,info.mode); 
 	mrcFileWrite(&out ,info.Out ,"in main" ,0); 
 	exit(EXIT_SUCCESS);     
}

void
additionalUsage()
{
fprintf(stdout,"----- mode -----");
fprintf(stdout,"+4 For 2D Image \n");
}

void lmrcRefPhaseImageCreate(mrcImage* out ,mrcImage* in ,double power ,double cutoff ,int mode)
{
/* variables */
  mrcImage tmpimg,tmpfft;
  int z;

/* initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);
 
/* begin */
  if (mode >= 4){
    lmrcImageFFT(&tmpfft ,in ,0);
    lmrcPhaseImageCreate(out ,&tmpfft ,power ,cutoff);
  }else{
    lmrc3DZ1ImgGet(&tmpimg ,in ,0);
    lmrc3DZ1ImgPut(out ,&tmpimg ,0);
    for (z = 1 ;z < in->HeaderN.z ;z++){
      fprintf(stderr,"%d " ,z);
      lmrc3DZ1ImgGet(&tmpimg ,in ,z);
      lmrcImageFFT(&tmpfft ,&tmpimg ,0);
      lmrcPhaseImageCreate(&tmpimg ,&tmpfft ,power ,cutoff); 
      lmrc3DZ1ImgPut(out ,&tmpimg ,z ); 
      mrcImageFree(&tmpimg ,"in lmrcRefPhaseImageCreate");
      mrcImageFree(&tmpfft ,"in lmrcRefPhaseImageCreate");
    }  
  }
  mrcStatDataSet(out,0);
}


void lmrcPhaseImageCreate(mrcImage* out ,mrcImage* in ,double power ,double cutoff)
{
/* variables */
  int X,Y;
  double datam,datap,datar,datai,dataabs;
  mrcImage tmp;

/* Initialization */
  tmp.Header = in->Header ;
  mrcInit(&tmp ,NULL);

/* begin */
  for (X=0 ;X <= in->HeaderN.x / 2 ;X++){
    for (Y = -in->HeaderN.y / 2 ;Y < in->HeaderN.y / 2 ; Y++){ 
      mrcPixelDataGet(in ,X ,Y ,0 ,&datam ,mrcPixelMag ,mrcPixelHowNearest);
      mrcPixelDataGet(in ,X ,Y ,0 ,&datap ,mrcPixelPhase ,mrcPixelHowNearest); 
      if (datam > cutoff ){
	if (power != 0.0) {
  		dataabs = pow(datam,power);
		datar = dataabs*cos(datap); 
 		datai = dataabs*sin(datap) ; 
	} else {
		datar = cos(datap);
		datai = sin(datap);
	}
      } else {
 	datar = 0.0; 
 	datai = 0.0; 
      } 
      mrcPixelDataSet(&tmp ,X ,Y ,0 ,datar, mrcPixelRePart);      
      mrcPixelDataSet(&tmp ,X ,Y ,0 ,datai, mrcPixelImPart);
    }
  }
  lmrcImageFFT(out ,&tmp, 0); 
  mrcStatDataSet(out ,0);    
}
















