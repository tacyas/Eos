/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageDeadPixelCorrection ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageDeadPixelCorrection
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageDeadPixelCorrection ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <nr2.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
void lmrcImageDeadPixelCorrection(mrcImage* in, int* dpc_x, int* dpc_ys, int* dpc_ye, int dpcnum);


int
main(int argc, char* argv[]) 
{
	mrcImageDeadPixelCorrectionInfo info;

	/* variables */
	mrcImage in;
	FILE *fpdpc;
	int dpcnum;
	int *dpc_x;
	int *dpc_ys;
	int *dpc_ye;
	int dummy;

        init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
        mrcFileRead(&in ,info.In ,"in main" ,0);
	if((fpdpc=fopen(info.Dp,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
        }
	dpcnum=0;
	while(fscanf(fpdpc,"%d %d %d \n",&dummy,&dummy,&dummy )!=EOF ){
	  dpcnum++;
	}
        dpc_x = ivector(0,dpcnum-1);
	dpc_ys = ivector(0,dpcnum-1);
	dpc_ye = ivector(0,dpcnum-1);

	DEBUGPRINT("Program Start\n");
	fclose(fpdpc);
	if((fpdpc=fopen(info.Dp,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
        }
	dpcnum=0;
	while(fscanf(fpdpc,"%d %d %d \n",&dpc_x[dpcnum], &dpc_ys[dpcnum], &dpc_ye[dpcnum] )!=EOF ){
	  dpcnum++;
	}
	lmrcImageDeadPixelCorrection(&in, dpc_x, dpc_ys, dpc_ye, dpcnum);
	mrcFileWrite(&in ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageDeadPixelCorrection(mrcImage* in, int* dpc_x, int* dpc_ys, int* dpc_ye, int dpcnum)
{
  int y,i;
  double odata,idata1,idata2;

  for (i=0; i<dpcnum; i++){
    for (y=dpc_ys[i]; y<=dpc_ye[i] ;y++){
      mrcPixelDataGet(in ,dpc_x[i]-1 ,y ,0 ,&idata1 ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataGet(in ,dpc_x[i]+1 ,y ,0 ,&idata2 ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(in ,dpc_x[i] ,y ,0 ,(idata1 + idata2)/2.0  ,mrcPixelRePart);
    }
  }
  mrcStatDataSet(in ,0);
}
