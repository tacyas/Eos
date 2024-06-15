/*
# mrcImageRefCreate.c  1.5
# The latest update : 08/27/96 at 16:17:35
#
#@(#) mrcImageRefCreate ver 1.5
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageRefCreate
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageRefCreate ver1.5; Date:96/08/27 @(#)";
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

/* prototype */
void lmrcRefCreate(mrcImage* out ,mrcImage* in ,mrcRefHeader* header ,int wx ,int mode);
void lmrcPutRef(mrcImage* out ,mrcImage* in ,int z ,int wx) ;

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageRefCreateInfo info;
	mrcRefHeader refheader;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	refheader.ip = info.iP;
	refheader.iw = info.iW;
	refheader.ia = info.iA;
	refheader.dp = info.Dp;
	refheader.dw = info.Dw;
	refheader.da = info.Da;
	refheader.wp = info.Wp;
	refheader.ww = info.Ww;
	refheader.wa = info.Wa;
	

/* begin */
	DEBUGPRINT("Reading\n");
	mrcFileRead(&in ,info.In ,"in main" ,0);
	DEBUGPRINT("Creating\n");
	lmrcRefCreate(&out ,&in ,&refheader ,info.Wx ,info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
 	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"---------- mode ----------\n");
fprintf(stdout,"0:Usual mode\n");
fprintf(stdout,"1:Magnification is changed to unchange molecular distance.\n");
}

void lmrcRefCreate(mrcImage* out ,mrcImage* in ,mrcRefHeader* header ,int wx ,int mode)
{
/* variables */
  mrcRefDegCoordinate phi,omega,alpha;
  int  z;
  float Nz,rww,rwa,tmp,Nx,wmax,amax;
  mrcImage tmpimg,tmpimg2;

/* Initialization */
  if (header->dp == 0 || header->dw == 0 || header->da == 0){
    fprintf(stderr,"Delta can not be zoro.");
    exit(EXIT_FAILURE);
  }

/* Out Header Creation */

  if (surplus(header->ww,header->dw)  > 0.0 || 
      surplus(header->wa,header->da)  > 0.0 || 
      surplus(header->wp,header->dp)  > 0.0 ){
    fprintf(stderr,"Width of omega or alpha or phi can not be devided by Delta. w %g %g %g a %g %g %g p %g %g %g\n",header->ww,header->dw,surplus(header->ww,header->dw),header->wa,header->da,surplus(header->wa,header->da),header->wp,header->dp,surplus(header->wp,header->dp));
    exit(EXIT_FAILURE);
  }
  out->Header = in->Header;
  out->HeaderN.z = floor( (2*header->wp/header->dp +1)  * (2*header->ww/header->dw+1) * (2*header->wa/header->da+1) +0.5) +1 ;

  wmax = ( fabs(header->iw) < fabs(header->iw - 180) )?(header->iw):(header->iw -180);
  wmax = ( wmax > 0)?(wmax + header->ww):(wmax - header->ww);
  amax = ( fabs(header->ia) < fabs(header->ia - 180) )?(header->ia):(header->ia -180);
  amax = ( amax > 0)?(amax + header->wa):(amax - header->wa);
  rww = RADIAN*fabs(wmax); 
  rwa = RADIAN*fabs(amax);
  tmp = 1.0/cos(rww) - tan(rww)*sin(rww) ;
  tmp *= in->HeaderN.z;
  tmp -= in->HeaderN.y * sqrt(2.0) * sin(rww);
  Nz = 1.0/cos(rwa) - tan(rwa)*sin(rwa);
  Nz *= tmp;
  Nz -= in->HeaderN.y * sin(rwa);
  out->HeaderN.y = Nz;
  if (out->HeaderN.y < 0){
     fprintf(stderr,"Length of data along z axis is too short.");
    exit(EXIT_FAILURE);
  }

  Nx = tmp * sin(rwa) + in->HeaderN.y * cos(rwa) ;
  (wx == NULL)?(out->HeaderN.x = wx = (int)((Nx + 1)/2) * 2 ):(out->HeaderN.x = wx); 
  fprintf(stderr,"%d %d %d %f %f\n",out->HeaderN.x ,out->HeaderN.y ,out->HeaderN.z ,Nx,Nz);
  
  DEBUGPRINT("mrcinit  ");
  mrcInit(out,NULL);
  z = 0;
  
/* begin */
  DEBUGPRINT("Writing Infomation ");
  lmrcRefHeaderSet(out ,header);
  DEBUGPRINT("End \n");
  for (omega = -header->ww + header->iw ;omega <= header->ww + header->iw ;omega += header->dw){
    for (phi = -header->wp + header->ip ;phi <= header->wp + header->ip ;phi += header->dp){
      for (alpha = -header->wa + header->ia  ;alpha <= header->wa + header->ia ;alpha += header->da){
	fprintf(stderr,"%f,%f,%f   ",omega,phi,alpha);
	lmrcRefFilamentProjction(&tmpimg ,in ,phi*RADIAN ,omega*RADIAN ,alpha*RADIAN ,wx ,out->HeaderN.y  );
	z ++;
	DEBUGPRINT("Extract And Put \n");
	if (mode==1){
	  lmrcImageMagnificationChange(&tmpimg2 ,&tmpimg ,1.0 / cos(omega*RADIAN) );
	  DEBUGPRINT5("z:%d %f %f %f %f \n",z, omega ,RADIAN ,omega *RADIAN ,1.0/cos(omega*RADIAN) );
	  mrcImageFree(&tmpimg,"in lmrcRefCreate");
	  lmrcImageCenterGet(&tmpimg ,&tmpimg2 ,out->HeaderN.x ,out->HeaderN.y , 1 ,( (float)tmpimg2.HeaderN.x-1.0)/2.0 ,( (float)tmpimg2.HeaderN.y-1.0)/2.0 ,0 ,mrcPixelHowCubicConv);
	  mrcImageFree(&tmpimg2,"in lmrcRefCreate");
	}
	lmrc3DZ1ImgPut(out ,&tmpimg ,z);
      }
      mrcImageFree(&tmpimg,"in lmrcRefCreate");
    }
  }
  mrcStatDataSet(out,0);  
}

void lmrcPutRef(mrcImage* out ,mrcImage* in ,int z ,int wx) 
{
/* variables */
  int x,y,xl,xr,xout;
  double data;

/* begin */
  for (y = 0 ;y <= in->HeaderN.y ;y++ ){    
    for (x = 0 ;x < out->HeaderN.x ;x++){
      mrcPixelDataGet(in  ,x    ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest); 
      mrcPixelDataSet(out ,x ,y ,z ,data  ,mrcPixelRePart);
    }
  }
}



































