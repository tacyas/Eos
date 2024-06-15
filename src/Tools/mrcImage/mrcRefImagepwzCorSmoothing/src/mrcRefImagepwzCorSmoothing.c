/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefImagepwzCorSmoothing ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefImagepwzCorSmoothing
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefImagepwzCorSmoothing ver%I%; Date:%D% %Z%";
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

/* typedef */
typedef struct {
  mrcImage image;
  double sy;
  double ey;
  double ysize;
} lmrcpwzCorrelation;

/* prototype */
void lmrcRefImagepwzCorSmoothing(mrcImage* out ,mrcImage* in ,int N ,double dp ,double dz ,int mode);

void lmrcpwzTemplateCorrelation(lmrcpwzCorrelation* out,mrcImage* in2 ,mrcImage* in,lmrcpwzCorrelation* template ,int sy, int ey ,int mode);

void lmrcMakepwzCortemplate(lmrcpwzCorrelation* out ,int N ,double dp ,double dz ,mrcpwzCorHeader* header ,mrcImage* in ,int mode);

void
main(int argc, char* argv[]) 
{
	mrcRefImagepwzCorSmoothingInfo info;
/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in ,info.In ,"in main" ,0);
	lmrcRefImagepwzCorSmoothing(&out,&in,info.N,info.dp,info.dz,info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcRefImagepwzCorSmoothing(mrcImage* out ,mrcImage* in ,int N ,double dp ,double dz ,int mode)
{
/* variables */
  lmrcpwzCorrelation template,tmp;
  mrcImage in2;
  mrcpwzCorHeader header;
/* begin */
  lmrcpwzCorHeaderGet(&header ,in);
  lmrcMakepwzCortemplate(&template ,N ,dp ,dz ,&header ,in ,mode);
  lmrcpwzTemplateCorrelation(out,&in2,in,&template,header.sy ,header.ey,1);

  /*
  lmrcpwzTemplateCorrelation(&tmp,&in2,in,&template,header.sy ,header.ey,1);
  printf("ey:%f %f\n",header.ey,N * dz / in->HeaderLength.y); 
  header.ey -= N * dz / in->HeaderLength.y;
  out->Header=in->Header;
  mrcInit(out,NULL);
  lmrcpwzCorHeaderSet(out ,&header);
  lmrc3DZ1ImgPut(out,&tmp.image,1);
  mrcStatDataSet(out,0);
  */
}


void lmrcMakepwzCortemplate(lmrcpwzCorrelation* out ,int N ,double dp ,double dz ,mrcpwzCorHeader* header ,mrcImage* in ,int mode)
{
/* variables */
  double z,p,sp,sz;
  int oz,op,n;
  
  union uniheader{
    mrcRefHeader ref;
    mrcpwzCorHeader cor;
  };   
  union uniheader tmpheader;

/* initialization */
  out->image.Header = in->Header;
  out->image.HeaderN.z = 1;
  out->image.HeaderN.x = in->HeaderN.x -1 ;
  mrcInit(&out->image ,NULL);
  tmpheader.cor = *header;
  p=0;
  z=dz/2;
  n=0;
  out->sy = 0;
  out->ey = floor(N*dz / in->HeaderLength.y+0.5);
  DEBUGPRINT1("%f ",out->ey);
/* begin */
  if (mode==0){
    while (n < N){
      p=NormalDegree(p);
      op=lmrcRefGetzCordinate(p,header->iw ,header->ia,&(tmpheader.ref) ) - 1; 
      oz=floor(z / in->HeaderLength.y +0.5);
      mrcPixelDataSet(&out->image ,op ,oz ,0 ,1 ,mrcPixelRePart);
      DEBUGPRINT2("%d %d  ",op,oz);
      n ++ ;
      z += dz ;
      p += dp ;
    } 
  } else {
    out->sy = - floor ( floor(N/2) *dz / in->HeaderLength.y +0.5);
    out->ey = floor (floor( (N-1) / 2 )*dz /in->HeaderLength.y +0.5 );
    sp=0; sz=0;  
    for (n = -N/2 ;n <= (N-1)/2 ;n++) {
      DEBUGPRINT1("%d ",n);
      p = sp + dp*n + header->ip -header->wp ;
      DEBUGPRINT1("%f ",p);
      p = NormalDegree(p);
      z = sz + dz*n;
      op=lmrcRefGetzCordinate(p,header->iw ,header->ia,&(tmpheader.ref) ) - 1; 
      oz=floor(z / in->HeaderLength.y +0.5);
      DEBUGPRINT2("%d %d  ",op,oz);
      mrcPixelDataSet(&out->image ,op ,oz ,0 ,1 ,mrcPixelRePart);
    }
  }
  mrcStatDataSet(&out->image,0);
}

void lmrcpwzTemplateCorrelation(lmrcpwzCorrelation* out,mrcImage* in2 ,mrcImage* in,lmrcpwzCorrelation* template ,int sy, int ey ,int mode)
{
/* variables */
  mrcImage tmp;
  mrcpwzCorHeader header;
  int x,y;
/* begin */
  if (mode/2){
    lmrcImageCorrelation(&out->image,in,&template->image,0);
     for (x=0;x<in->HeaderN.x ;x++){
      for (y=0 ;y<sy-(int)template->sy ;y++){
	mrcPixelDataSet(&out->image,x,y,0,in->HeaderAMin,mrcPixelRePart);
      }
      for (y=ey-(int)template->ey+1 ;y<in->HeaderN.y ;y++){
	mrcPixelDataSet(&out->image,x,y,0,in->HeaderAMin,mrcPixelRePart);
      }
    }	
    DEBUGPRINT4("mode2:%d %d %g %g \n",sy-(int)template->sy,ey-(int)template->ey+1,sy-(int)template->sy ,ey-(template->ey-template->ey) );
    DEBUGPRINT4("%d %g %d %g \n",sy,template->sy,ey,template->ey );

  }else{
    lmrc3DZ1ImgGet(&tmp ,in ,1);
    lmrcImageRectangleGet(in2 ,&tmp ,0 ,0 ,in->HeaderN.x-2 ,in->HeaderN.y-1 );
    if (mode){
      lmrcImageCorrelation(&out->image ,in2 ,&template->image ,0);
      printf("sy: %f ey: %f tsy: %f tey: %f",sy,ey,template->sy, template->ey);
      /*
      for (x=0;x<in->HeaderN.x ;x++){
	for (y=0 ;y<sy-(int)template->sy ;y++){
	  mrcPixelDataSet(&out->image,x,y,0,in2->HeaderAMin,mrcPixelRePart);
	}
	for (y=ey-(int)template->ey+1 ;y <in->HeaderN.y ;y++){
	  mrcPixelDataSet(&out->image,x,y,0,in2->HeaderAMin,mrcPixelRePart);
	}
      }	
      */ 
    } else {
      lmrcpwzCorHeaderGet(&header ,in);
      lmrcImageCorrelation(&tmp ,in2 ,&template->image ,0);
      for (x=0;x<in->HeaderN.x ;x++){
	for (y=0 ;y<sy-(int)template->sy ;y++){
	  mrcPixelDataSet(&tmp,x,y,0,in2->HeaderAMin,mrcPixelRePart);
	}
	for (y=ey-(int)template->ey+1 ;y <in->HeaderN.y ;y++){
	  mrcPixelDataSet(&tmp,x,y,0,in2->HeaderAMin,mrcPixelRePart);
	}
      }	
      out->image.Header = in->Header;
      out->image.HeaderN.x = in->HeaderN.x-1;
      mrcInit(&out->image,NULL);
      lmrc3DZ1ImgPut(&out->image,&tmp ,1);
      lmrcpwzCorHeaderSet(&out->image,&header);
    }
  }
  out->ey=ey-(int)template->ey;
  out->sy=sy-(int)template->sy;
  mrcStatDataSet(&out->image,0);
}















