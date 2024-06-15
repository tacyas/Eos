/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageDivideIntoTwoImages ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageDivideIntoTwoImages
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageDivideIntoTwoImages ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototype */
void lmrcImageDivideIntoTwoImages(char* out1 ,char* out2 ,mrcImage* in ,int mode);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageDivideIntoTwoImagesInfo info;

/* variables */
	mrcImage in;
	
/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	lmrcImageDivideIntoTwoImages(info.Out1 ,info.Out2 ,&in ,info.mode);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stderr,"----- mode -----\n");
fprintf(stderr,"0:Vertical to the longest axis.\n");
fprintf(stderr,"1:Vertical to x axis\n");
fprintf(stderr,"2:Vertical to y axis\n");
fprintf(stderr,"3:Vertical to z axis\n");
}

void lmrcImageDivideIntoTwoImages(char* out1 ,char* out2 ,mrcImage* in ,int mode)
{
/* variables */
  int x,y,z,lmode;
  double data;
  mrcImage out;

/* begin */
  if (!mode){
    if (in->HeaderN.x >= in->HeaderN.y && in->HeaderN.x >= in->HeaderN.z){
      lmode = 1;
    }else if (in->HeaderN.y >= in->HeaderN.x && in->HeaderN.y >= in->HeaderN.z){
      lmode = 2;
    }else{
      lmode = 3;
    }
  }else{
    lmode = mode;
  }
  DEBUGPRINT1("%d",lmode);
  if (lmode==1 ){
    out.Header = in->Header;
    out.HeaderN.x = in->HeaderN.x/2;
    mrcInit(&out,NULL);
    for (z=0 ;z<out.HeaderN.z ;z++){
      for (x=0 ;x<out.HeaderN.x ;x++){
	for (y=0 ;y<in->HeaderN.y ;y++){
	  mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
	  mrcPixelDataSet(&out,x,y,z,data ,mrcPixelRePart);
	}
      }
    }
    mrcStatDataSet(&out,0);
    mrcFileWrite(&out ,out1 ,"in lmrcImageDivideIntoTwoImages" ,0);
    mrcImageFree(&out,0);
    
    out.Header = in->Header;
    out.HeaderN.x = in->HeaderN.x - in->HeaderN.x/2;
    mrcInit(&out,NULL);
    for (z=0 ;z<out.HeaderN.z ;z++){
      for (x=0 ;x<out.HeaderN.x ;x++){
	for (y=0 ;y<in->HeaderN.y ;y++){
	  mrcPixelDataGet(in,x + in->HeaderN.x/2 ,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
	  mrcPixelDataSet(&out,x,y,z,data ,mrcPixelRePart);
	}
      }
    }
    mrcStatDataSet(&out,0);
    mrcFileWrite(&out ,out2 ,"in lmrcImageDivideIntoTwoImages" ,0);
    mrcImageFree(&out,0);

  } else if (lmode==2) {
    DEBUGPRINT1("%d\n",lmode);
    out.Header = in->Header;
    out.HeaderN.y = in->HeaderN.y/2;
    mrcInit(&out,NULL);
    for (z=0 ;z<out.HeaderN.z ;z++){
      for (y=0 ;y<out.HeaderN.y ;y++){
	for (x=0 ;x<in->HeaderN.x ;x++){
	  mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
	  mrcPixelDataSet(&out,x,y,z,data ,mrcPixelRePart);
	}
      }
    }
    mrcStatDataSet(&out,0);
    mrcFileWrite(&out ,out1 ,"in lmrcImageDivideIntoTwoImages" ,0);
    mrcImageFree(&out,0);
    
    out.Header = in->Header;
    out.HeaderN.y = in->HeaderN.y - in->HeaderN.y/2;
    mrcInit(&out,NULL);
    for (z=0 ;z<out.HeaderN.z ;z++){
      for (y=0 ;y<out.HeaderN.y ;y++){
	for (x=0 ;x<in->HeaderN.x ;x++){
	  mrcPixelDataGet(in,x,y+in->HeaderN.y/2,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
	  mrcPixelDataSet(&out,x,y,z,data ,mrcPixelRePart);
	}
      }
    }
    mrcStatDataSet(&out,0);
    mrcFileWrite(&out ,out2 ,"in lmrcImageDivideIntoTwoImages" ,0);
    mrcImageFree(&out,0);

  } else if (lmode==3) {
    out.Header = in->Header;
    out.HeaderN.z = in->HeaderN.z/2;
    mrcInit(&out,NULL);
    for (x=0 ;x<out.HeaderN.x ;x++){
      for (y=0 ;y<out.HeaderN.y ;y++){
	for (z=0 ;z<out.HeaderN.z ;z++){
	  mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
	  mrcPixelDataSet(&out,x,y,z,data ,mrcPixelRePart);
	}
      }
    }
    mrcStatDataSet(&out,0);
    mrcFileWrite(&out ,out1 ,"in lmrcImageDivideIntoTwoImages" ,0);
    mrcImageFree(&out,0);
    
    out.Header = in->Header;
    out.HeaderN.z = in->HeaderN.z - in->HeaderN.z/2;
    mrcInit(&out,NULL);
    for (x=0 ;x<out.HeaderN.x ;x++){
      for (y=0 ;y<out.HeaderN.y ;y++){
	for (z=0 ;z<out.HeaderN.z ;z++){
	  mrcPixelDataGet(in,x,y,z+in->HeaderN.z/2,&data,mrcPixelRePart ,mrcPixelHowNearest); 
	  mrcPixelDataSet(&out,x,y,z,data ,mrcPixelRePart);
	}
      }
    }
    mrcStatDataSet(&out,0);
    mrcFileWrite(&out ,out2 ,"in lmrcImageDivideIntoTwoImages" ,0);
    mrcImageFree(&out,0);
  }    
}   




