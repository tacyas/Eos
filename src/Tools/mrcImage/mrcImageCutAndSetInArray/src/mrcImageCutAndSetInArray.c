/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCutAndSetInArray ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCutAndSetInArray
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCutAndSetInArray ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/*
   Example:
   typedef struct lmrcImageCutAndSetInArrayInfo {
   float a;
   int   b;
   } lmrcImageCutAndSetInArrayInfo;
   
   typedef enum lmrcImageCutAndSetInArrayMode {
   a=0,
   b=1
   } lmrcImageCutAndSetInArrayMode;
*/


typedef struct lmrcImageCutAndSetInArrayInfo {
  int n;
  int blank;
  FILE* outfile;
} lmrcImageCutAndSetInArrayInfo;


void lmrcImageCutAndSetInArrayInfoPrint(mrcImage* out, mrcImage* in,
					lmrcImageCutAndSetInArrayInfo* linfo){
  int i,iStart;
  int outImageLengthXexample;
  int outImageLengthYexample;
  int outImageLengthZexample;
  
  fprintf(linfo->outfile,
	  "This program is a tool of cutting a long mrcImage into
some parts and putting them side by side.
  Using this program, your original mrcImage length and width was transformed 
  from %d x %d x %d 
  into %d x %d x %d\n",in->HeaderN.x, in->HeaderN.y, in->HeaderN.z, 
out->HeaderN.x, out->HeaderN.y, out->HeaderN.z);
  fprintf(linfo->outfile,"Then Here are some examples of cutting your mrcImage.\n");
  fprintf(linfo->outfile," Supposed : blank = %d\n", linfo->blank);
  
  if((linfo->n) > 5){
    iStart = (linfo->n) - 5;
  }
  else iStart = 1;
  
  for (i=iStart; i<(linfo->n)+6; i++){
    outImageLengthXexample = (in->HeaderN.x)*i + (linfo->blank)*(i-1);
    outImageLengthYexample = (in->HeaderN.y)/i;
    outImageLengthZexample = in->HeaderN.z;
    fprintf(linfo->outfile," n=%d : x=%d, y=%d, z=%d\n",i, outImageLengthXexample,
	    outImageLengthYexample, outImageLengthZexample);
  }
}

void lmrcImageCutAndSetInArrayHelpPrint(){
  fprintf(stderr,"If you try the option '-ref [filename]',\n");
  fprintf(stderr,"a refernce file for cutting is created.\n");
}


void
  main(int argc, char* argv[]) 
{
  
  mrcImage in;
  mrcImage out;
  
  int x,y,z;
  double data;
  int i,n,maxLength;
  int blank;
  int outHeaderStartPoint,outHeaderEndPoint;
  
  mrcImageCutAndSetInArrayInfo info;
  lmrcImageCutAndSetInArrayInfo linfo;
  
  init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);
  
  DEBUGPRINT("Program Start\n");
  
  mrcFileRead(&in, info.In, "in main", 0);
  n = info.numberOfParts;
  blank = info.blank;
  
  maxLength = in.HeaderN.y / n;
  DEBUGPRINT1("max=%d\n", maxLength);
  out.Header = in.Header;
  out.HeaderN.x = n*(in.HeaderN.x) + (n-1)*blank;
  out.HeaderN.y = maxLength;
    
  mrcInit(&out, NULL);
  
  if (info.fptRef){
    linfo.outfile = info.fptRef;
    linfo.blank = info.blank;
    linfo.n     = info.numberOfParts;
    lmrcImageCutAndSetInArrayInfoPrint(&out, &in, &linfo);
  }
  
  DEBUGPRINT("Copy Start\n");
  
  for (i=0; i<n; i++){
    outHeaderStartPoint = maxLength*i;
    outHeaderEndPoint   = maxLength*(i+1);
    for (z=0; z<in.HeaderN.z; z++){
      for (y=outHeaderStartPoint ; y<outHeaderEndPoint; y++){
	DEBUGPRINT1("y=%d\n", y);
	for (x=0; x<in.HeaderN.x; x++){
	  mrcPixelDataGet(&in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataSet(&out, x+(in.HeaderN.x+blank)*i, y-outHeaderStartPoint, z, data, mrcPixelRePart);
	  /*	  DEBUGPRINT1("x=%d\n", x); */
	}
      }
    }
  }
  
  mrcStatDataSet(&out, 0);
  mrcFileWrite(&out, info.Out, "in main", 0);
  
  
  exit(EXIT_SUCCESS);
}

void
  additionalUsage()
{
  fprintf(stderr, "----- Additional Usage -----\n");
  lmrcImageCutAndSetInArrayHelpPrint();
}
