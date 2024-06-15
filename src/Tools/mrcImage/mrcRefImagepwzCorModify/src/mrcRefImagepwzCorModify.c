/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefImagepwzCorModify ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefImagepwzCorModify
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefImagepwzCorModify ver%I%; Date:%D% %Z%";
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

/* type definition */
typedef struct mrcImageROIInfo {
    float blx;
    float bly;
    float brx;
    float bry;
    float trx;
    float try;
    float tlx;
    float tly;
    
    long flagWidthBeforeExpansion;
    float WidthBeforeExpansion;
    
    long flagHeightBeforeExpansion;
    float HeightBeforeExpansion;
    
    long flagAngle;
    float Angle;
    
    long flagWidthAfterExpansion;
    float WidthAfterExpansion;
    
    long flagHeightAfterExpansion;
    float HeightAfterExpansion;
    
    long flagmode;
    long mode;
    
} mrcImageROInotChangeHeaderLengthInfo;

/* prototype */
void mrcRefImagepwzCorPadbyMin(mrcImage* out ,mrcImage* in ,int Nry ,int mode);
void mrcRefImagepwzCorMirroring(mrcImage* out ,mrcImage* in );
void mrcRefImagepwzCorMagChange(mrcImage* out ,mrcImage* in ,double mag);
void lmrcImageROInotChangeHeaderLength(mrcImage* out, mrcImage* in, mrcImageROInotChangeHeaderLengthInfo* info);
void mrcRefImagepwzCorShift(mrcImage* out ,mrcImage* in ,int shift);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefImagepwzCorModifyInfo info;

/* variables */
        mrcImage in;
        mrcImage out;
	mrcImage* tmp1;
	mrcImage* tmp2;
	mrcImage* tmp3;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	tmp2=&in;
	tmp1=&out;
	if (info.mode % 2){
	  tmp3=tmp2;
	  tmp2=tmp1;
	  tmp1=tmp3;
	  DEBUGPRINT("Padding \n");
	  mrcRefImagepwzCorPadbyMin(tmp2 ,tmp1 ,info.Nry ,info.mode2);
	  info.mode -= 1;
	}
	if (info.mode % 4){
	  DEBUGPRINT("mode2\n");
	  tmp3=tmp2;
	  tmp2=tmp1;
	  tmp1=tmp3;
	  DEBUGPRINT("Mirroring \n");
	  mrcRefImagepwzCorMirroring(tmp2 ,tmp1 );
	  info.mode -= 2;
	}
	if (info.mode % 8){
	  tmp3=tmp2;
	  tmp2=tmp1;
	  tmp1=tmp3;
	  DEBUGPRINT("Mag change \n");
	  mrcRefImagepwzCorMagChange(tmp2 ,tmp1 ,info.mag);
	  info.mode -= 4;
	}
	if (info.mode % 16){
	  tmp3=tmp2;
	  tmp2=tmp1;
	  tmp1=tmp3;
	  mrcRefImagepwzCorShift(tmp2 ,tmp1 ,info.shift);
	  info.mode -= 8;
	}

	mrcFileWrite(tmp2 ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"-------- mode --------\n");
fprintf(stdout,"+1: min padding\n");
fprintf(stdout,"+2: mirroring\n");
fprintf(stdout,"+4: magnification change\n");
fprintf(stdout,"+8: shift\n");

fprintf(stdout,"-------- mode2 --------\n");
fprintf(stdout,"1:old format\n");
fprintf(stdout,"2:mode1+No shift\n");
}

void mrcRefImagepwzCorPadbyMin(mrcImage* out ,mrcImage* in ,int Nry ,int mode)
{
/* variables */
  mrcpwzCorHeader corheader;
  mrcRefHeader refheader;
  union uniheader{
    mrcRefHeader ref;
    mrcpwzCorHeader cor;
  };
  union uniheader tmpheader;
  int x,y;
  double data;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.y = in->HeaderN.y + Nry ;
  mrcInit(out,NULL);

/* begin */
  if (mode) {
    lmrcRefHeaderGet(&refheader ,in);
    tmpheader.ref = refheader;
    tmpheader.cor.sy = (Nry-1)/2;
    tmpheader.cor.ey = in->HeaderN.y+(Nry-1)/2;
    tmpheader.cor.refsize = Nry;
    tmpheader.cor.inverse = 1;
    corheader = tmpheader.cor;
  }else{
    lmrcpwzCorHeaderGet(&corheader,in);
    Nry=corheader.refsize;
  }
  lmrcpwzCorHeaderSet(out,&corheader);

  for (y=0 ;y<(Nry-1)/2 ;y++){
    for (x=0 ;x<out->HeaderN.x ;x++){
      mrcPixelDataSet(out ,x ,y ,1 ,in->HeaderAMin ,mrcPixelRePart);
    }
  }
  for (y=0 ;y<in->HeaderN.y ;y++){
    for (x=0 ;x<out->HeaderN.x ;x++){
      mrcPixelDataGet(in ,x ,y ,1 ,&data ,mrcPixelRePart , mrcPixelHowNearest); 
      mrcPixelDataSet(out ,x ,y+(Nry-1)/2 ,1 ,data ,mrcPixelRePart);
    }
  }
  for (y=in->HeaderN.y+(Nry-1)/2  ;y<out->HeaderN.y ;y++){
    for (x=0 ;x<out->HeaderN.x ;x++){
      mrcPixelDataSet(out ,x ,y ,1 ,in->HeaderAMin ,mrcPixelRePart);
    }
  }
  mrcStatDataSet(out,0);
}


void mrcRefImagepwzCorMirroring(mrcImage* out ,mrcImage* in )
{
/* variables */
  int x,y;
  double data;
  mrcpwzCorHeader header;

/* Initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);

/* begin */
  lmrcpwzCorHeaderGet(&header,in);
  header.inverse *= -1;
  data=in->HeaderN.y-header.ey-1;
  header.ey=in->HeaderN.y-header.sy-1;
  header.sy=data;
  lmrcpwzCorHeaderSet(out,&header);
  for  (x = 0 ;x < in->HeaderN.x ;x++){
    for (y = 0 ;y < in->HeaderN.y ;y++){
      mrcPixelDataGet(in ,x ,y ,1 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,x ,in->HeaderN.y -y -1 ,1 ,data, mrcPixelRePart);
    }
  }
  mrcStatDataSet(out ,0);
}
  
void mrcRefImagepwzCorMagChange(mrcImage* out ,mrcImage* in ,double mag)
{
/* variables */
  mrcImage tmpin;
  mrcImage tmpout;
  mrcImageROInotChangeHeaderLengthInfo roiinfo;
  mrcpwzCorHeader header;
  int z;

/* initialization  */
  roiinfo.blx = roiinfo.tlx = 0;
  roiinfo.brx = roiinfo.trx = in->HeaderN.x - 1 ;
  roiinfo.bly = roiinfo.bry = 0;
  roiinfo.tly = roiinfo.try = in->HeaderN.y - 1 ;
  roiinfo.flagWidthBeforeExpansion = 0;
  roiinfo.flagHeightBeforeExpansion = 0;
  roiinfo.flagAngle = 0;
  roiinfo.flagWidthAfterExpansion = 1;
  roiinfo.WidthAfterExpansion = in->HeaderN.x;
  roiinfo.flagHeightAfterExpansion = 1;
  roiinfo.HeightAfterExpansion = floor(in->HeaderN.y * mag +0.5);
  roiinfo.mode = 2;

/* begin */
  out->Header=in->Header;
  out->HeaderN.x=roiinfo.WidthAfterExpansion;
  out->HeaderN.y=roiinfo.HeightAfterExpansion;
  mrcInit(out,NULL);
  lmrcpwzCorHeaderGet(&header ,in);
  header.refsize *= mag;
  header.sy *= mag;
  header.ey *= mag;
  lmrcpwzCorHeaderSet(out ,&header);	
  for (z=1 ;z<in->HeaderN.z ;z++){
    lmrc3DZ1ImgGet(&tmpin ,in ,z);
    lmrcImageROInotChangeHeaderLength(&tmpout ,&tmpin ,&roiinfo);
    lmrc3DZ1ImgPut(out ,&tmpout ,z);
    mrcImageFree(&tmpin ,0);
    mrcImageFree(&tmpout ,0);
  }
  mrcStatDataSet(out,0);
}

void mrcRefImagepwzCorShift(mrcImage* out ,mrcImage* in ,int shift)
{
/* variables */
  mrcImage tmpin;
  mrcImage tmpout;
  mrcImageParaTypeRealCoord s;
  mrcpwzCorHeader header;

/* Initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);

/* begin */
  lmrcpwzCorHeaderGet(&header,in);
  header.sy += shift;
  header.ey += shift;
  if (header.sy < 0) header.sy=0;
  if (header.ey >= in->HeaderN.y) header.ey = in->HeaderN.y - 1; 
  lmrcpwzCorHeaderSet(out , &header);

  s.x = 0;
  s.y = shift;
  s.z = 0;
  lmrc3DZ1ImgGet(&tmpin ,in ,1);
  lmrcImageShift(&tmpout, &tmpin, s, mrcPixelHowNearest);
  lmrc3DZ1ImgPut(out ,&tmpout ,1);
  
  mrcStatDataSet(out,0);
}


void
lmrcImageROInotChangeHeaderLength(mrcImage* out, mrcImage* in, mrcImageROInotChangeHeaderLengthInfo* info)
{
    double* tmpImage;
    int ix, iy;
    double xdx, xdy;
    double ydx, ydy;
    double x, y;
	double cx, cy;    				/* Centre of source image */
	double dwdx, dwdy, dhdx, dhdy;  /* Differentiation of source image */
	double tdwdx, tdwdy, tdhdx, tdhdy;  /* Temporaty differentiation of source image */
	double angle;
    double width, height; 			/* Size of source image */ 
    double max, min, mean;
	double data;

	width  = sqrt(SQR(info->brx - info->blx) + SQR(info->bry - info->bly));
	height = sqrt(SQR(info->tlx - info->blx) + SQR(info->tly - info->bly));
	if(width<0.5 || height<0.5) {
		fprintf(stderr, "ROI Area is zero(%f, %f)\n", width, height);
		exit(EXIT_FAILURE);
	}
	if(info->flagWidthBeforeExpansion || info->flagHeightBeforeExpansion) {
		cx = (info->blx + info->trx)/2.0;
		cy = (info->bly + info->try)/2.0;
		dwdx = (info->brx - info->blx)/width;
		dwdy = (info->bry - info->bly)/width;
		dhdx = (info->tlx - info->blx)/height;
		dhdy = (info->tly - info->bly)/height;
		if(info->flagAngle) {
			angle = info->Angle*DEGREE;
			tdwdx = cos(angle)*dwdx - sin(angle)*dwdy;
			tdwdy = sin(angle)*dwdx + cos(angle)*dwdy;
			dwdx = tdwdx;
			dwdy = tdwdy;
			tdhdx = cos(angle)*dhdx - sin(angle)*dhdy;
			tdhdy = sin(angle)*dhdx + cos(angle)*dhdy;
			dhdx = tdhdx;
			dhdy = tdhdy;
		}
		if(info->flagWidthBeforeExpansion) {
			width = info->WidthBeforeExpansion;
		} 
		if(info->flagHeightBeforeExpansion) {
			height = info->HeightBeforeExpansion;
		} 
		info->blx = cx - dwdx*width/2.0 - dhdx*height/2.0;
		info->bly = cy - dwdy*width/2.0 - dhdy*height/2.0;
		info->brx = cx + dwdx*width/2.0 - dhdx*height/2.0;
		info->bry = cy + dwdy*width/2.0 - dhdy*height/2.0;
		info->trx = cx + dwdx*width/2.0 + dhdx*height/2.0;
		info->try = cy + dwdy*width/2.0 + dhdy*height/2.0;
		info->tlx = cx - dwdx*width/2.0 + dhdx*height/2.0;
		info->tly = cy - dwdy*width/2.0 + dhdy*height/2.0;
	}

    /* Definition of Expansion Rate */
    switch(info->flagHeightAfterExpansion) {
		case 0:
			switch(info->flagWidthAfterExpansion) {
				case 0:
					info->HeightAfterExpansion = floor(height+1.0);
                    info->WidthAfterExpansion  = floor(width +1.0);
					break;
				case 1:
					info->HeightAfterExpansion = floor((height+1.0)*info->WidthAfterExpansion/(width+1.0));
					info->WidthAfterExpansion  = info->WidthAfterExpansion;
					break;
				default:
					fprintf(stderr, "Not Supported flag: flagWidthAfterExpansion\n");
					exit(EXIT_FAILURE);
					break;
			}
			break;
		case 1:	
			switch(info->flagWidthAfterExpansion) {
				case 0:
					info->HeightAfterExpansion = info->HeightAfterExpansion;
					info->WidthAfterExpansion  = floor((width+1.0)*info->HeightAfterExpansion/(height+1.0));
					break;
               case 1:
					info->HeightAfterExpansion = info->HeightAfterExpansion;
					info->WidthAfterExpansion  = info->WidthAfterExpansion;
					break;
				default:
					fprintf(stderr, "Not Supported flag: flagWidthAfterExpansion\n");
					exit(EXIT_FAILURE);
					break;
			}
			break;
		default:
			fprintf(stderr, "Not Supported flag: flagHeightAfterExpansion\n");
			exit(EXIT_FAILURE);
			break;
	}

	out->Header = in->Header;
    out->HeaderN.x = info->WidthAfterExpansion;
    out->HeaderN.y = info->HeightAfterExpansion;
    out->HeaderN.z = 1;
    out->HeaderMode = mrcFloatImage;
    mrcInit(out, NULL);

    xdx = (info->brx - info->blx)/(info->WidthAfterExpansion -1.0);
    xdy = (info->bry - info->bly)/(info->WidthAfterExpansion -1.0);
    ydx = (info->tlx - info->blx)/(info->HeightAfterExpansion-1.0);
    ydy = (info->tly - info->bly)/(info->HeightAfterExpansion-1.0);

	switch(info->mode) {
		case 0: {
			break;
		}
		default: {
    		if(NULL==(tmpImage = (double*)malloc(sizeof(double)*in->HeaderN.x*in->HeaderN.y*in->HeaderN.z))) {
		        fprintf(stderr, "Not Allocate Memory in lmrcImageROI\n");
				exit(EXIT_FAILURE);
    		}
		    for(ix=0; ix<in->HeaderN.x; ix++) {
       			for(iy=0; iy<in->HeaderN.y; iy++) {
       			    mrcPixelDataGet(in,
						   (mrcImageParaTypeReal)ix, 
						   (mrcImageParaTypeReal)iy, 
						   0.0, 
						   &(tmpImage[ix+iy*in->HeaderN.x]), 
						   mrcPixelRePart, mrcPixelHowNearest);
        		}
    		}
			break;
		}
	}

    switch(info->mode) {
        case 0: {
            for(ix=0; ix<out->HeaderN.x; ix++) {
                for(iy=0; iy<out->HeaderN.y; iy++) {
                    x = ix*xdx + iy*ydx + info->blx;
                    y = ix*xdy + iy*ydy + info->bly;
					mrcPixelDataGet(in, 
									(mrcImageParaTypeReal)x, 
									(mrcImageParaTypeReal)y, 
									0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out, 
									(mrcImageParaTypeReal)ix,
									(mrcImageParaTypeReal)iy,
									0.0,
									data,
									mrcPixelRePart);
                }
            }
            break;
        }
        case 1: {
            for(ix=0; ix<out->HeaderN.x; ix++) {
                for(iy=0; iy<out->HeaderN.y; iy++) {
                    x = ix*xdx + iy*ydx + info->blx;
                    y = ix*xdy + iy*ydy + info->bly;
					mrcPixelDataSet(out, 
									(mrcImageParaTypeReal)ix,
									(mrcImageParaTypeReal)iy,
									0.0,
                        			lbilinearInterpolation(tmpImage,
                                		in->HeaderN.x, in->HeaderN.y,
										x, y),
									mrcPixelRePart);
                }
            }
            break;
        }
        case 2: {
            for(ix=0; ix<out->HeaderN.x; ix++) {
                for(iy=0; iy<out->HeaderN.y; iy++) {
                    x = ix*xdx + iy*ydx + info->blx;
                    y = ix*xdy + iy*ydy + info->bly;
					
					mrcPixelDataSet(out, 
									(mrcImageParaTypeReal)ix,
									(mrcImageParaTypeReal)iy,
									0.0,
                        			lcubicConvolutionInterpolation(tmpImage, 
                                		in->HeaderN.x, in->HeaderN.y,
                                		x, y),
									mrcPixelRePart);
                }
            }
            break;
        }
        case 3: {
            for(ix=0; ix<out->HeaderN.x; ix++) {
                for(iy=0; iy<out->HeaderN.y; iy++) {
                    x = ix*xdx + iy*ydx + info->blx;
                    y = ix*xdy + iy*ydy + info->bly;
					mrcPixelDataSet(out, 
									(mrcImageParaTypeReal)ix,
									(mrcImageParaTypeReal)iy,
									0.0,
                        			lpolyNominalInterpolation(tmpImage, 
                                		in->HeaderN.x, in->HeaderN.y,
                                		x, y),
									mrcPixelRePart);
                }
            }
            break;                              
        }
        default: {
            fprintf(stderr, "Not Supported Mode : %ld\n", info->mode);
            break;
        }
    }
	mrcStatDataSet(out, 0);
}

