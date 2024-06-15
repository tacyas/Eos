/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImage3DPad ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImage3DPad
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageiZPad ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcImage3DPadInfo {
	int Nx;
	int Ny;
	int Nz;

	double w;

	int flagv;
	double v;

	int flagr;
	float rmax;

	int flagFloating;
} lmrcImage3DPadInfo;

/* prototypes */
double lmrcImage3DPadCalcavr(mrcImage* in ,double rmax);
void lmrcImage3DPad(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode);


int
main(int argc, char* argv[]) 
{
	mrcImageZPadInfo info;
	lmrcImage3DPadInfo linfo;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in ,info.In ,"in main" ,0);
	DEBUGPRINT1("Tailer: %d\n", in.numTailer);	
/* begin */
	DEBUGPRINT("Program Start\n");
	if (!info.flagNx){
	  info.Nx=in.HeaderN.x;
	}
	if (!info.flagNy){
	  info.Ny=in.HeaderN.y;
	}
	if (!info.flagNz){
	  info.Nz=in.HeaderN.z;
	}
	if (!info.flagr){
	  info.r=MIN( (in.HeaderN.x-1)/2.0, (in.HeaderN.y-1)/2.0);
	}
	linfo.rmax = info.r;
	linfo.flagr = info.flagr;
	linfo.Nx = info.Nx;
	linfo.Ny = info.Ny;
	linfo.Nz = info.Nz;
	linfo.w  = info.w;
	linfo.flagv = info.flagv;
	linfo.v     = info.v;
	linfo.flagFloating = info.Floating;

	lmrcImage3DPad(&out, &in, linfo, info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
  fprintf(stderr, "----- mode -----\n");
  fprintf(stderr, "0:Default: Out of threshold is avrage of threshold plain.\n");
  fprintf(stderr, "1:Mulplying cos function. Default: Out of threshold is avrage of threshold plain.\n");

}

void lmrcImage3DPad(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode) 
{

	/* variables */
	int x,y,z;
	double data,cx,cy,cz,sx,sy,sz,r2,av,c,dr2;
	double dstx, dsty, dstz;
	double offset;

	out->Header = in->Header;
	out->HeaderN.x = linfo.Nx;
	out->HeaderN.y = linfo.Ny;
	out->HeaderN.z = linfo.Nz;
	mrcInit(out,NULL);
	if(0<in->numTailer) {
		out->numTailer = in->numTailer;
		out->Tailer = in->Tailer;
	}
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5;
	cz=(in->HeaderN.z-1)*0.5;
	sx=(out->HeaderN.x-in->HeaderN.x)*0.5;
	sy=(out->HeaderN.y-in->HeaderN.y)*0.5;
	sz=(out->HeaderN.z-in->HeaderN.z)*0.5;
	r2=SQR(linfo.rmax);
	switch(mode){
		case 0:
			if (!linfo.flagv){
				av=lmrcImage3DPadCalcavr(in, linfo.rmax);
			} else {
				av=linfo.v;
			}
			if(linfo.flagFloating) {
				offset = av;
			} else {
				offset = 0;
			}
			for (x=0;x<out->HeaderN.x;x++){
			for (y=0;y<out->HeaderN.y;y++){
			for (z=0;z<out->HeaderN.z;z++){
				mrcPixelDataSet(out, x, y, z, av-offset, mrcPixelRePart);
			}
			}
			}
			for (x=0;z<in->HeaderN.x;x++){
			for (y=0;y<in->HeaderN.y;y++){
			for (z=0;x<in->HeaderN.z;z++){
				mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
				if (linfo.flagr){
					dr2=SQR(z-cz);
					if (r2>=dr2 ){
						mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,data-offset, mrcPixelRePart);
					} 
				} else {	      
					mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,data-offset, mrcPixelRePart);
				}	    
			}
			}
			}
			break;
		
		case 1:
			if (!linfo.flagv) {
				av=lmrcImage3DPadCalcavr(in ,linfo.rmax+linfo.w);
			} else {
				av=linfo.v;
			}
			if(linfo.flagFloating) {
				offset = av;
			} else {
				offset = 0;
			}
			fprintf(stdout,"av :%g\n",av); 
			for (x=0;x<in->HeaderN.x;x++){
			for (y=0;y<in->HeaderN.y;y++){
			for (z=0;z<in->HeaderN.z;z++){
				dstx = x + sx;
				dsty = y + sy;
				dstz = z + sz;
				if(-0.5<=dstx && dstx<out->HeaderN.x-0.5
				 &&-0.5<=dsty && dsty<out->HeaderN.y-0.5
				 &&-0.5<=dstz && dstz<out->HeaderN.z-0.5) {
					mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
					if (linfo.flagr) {
						dr2=SQR(z-cz);
						if (dr2<SQR(linfo.rmax-linfo.w)) {
							mrcPixelDataSet(out ,dstx, dsty, dstz, data-offset, mrcPixelRePart);
						} else if (SQR(linfo.rmax+linfo.w)<dr2) {
							mrcPixelDataSet(out , dstx, dsty, dstz, av-offset, mrcPixelRePart);
						} else {
							c= (cos( ( linfo.rmax-sqrt(dr2)) / linfo.w *PI/2 )+1 )/2;
									mrcPixelDataSet(out, dstx, dsty, dstz, (data-av)*c+av-offset , mrcPixelRePart);
						}
					} else {
						mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,av-offset, mrcPixelRePart);
					}	  
				}	
			}
			}
			}  
	}
	mrcStatDataSet(out ,0);
}

double 
lmrcImage3DPadCalcavr(mrcImage* in ,double rmax)
{
	/* variables */
	int x,y,z,n;
	double cx,cy,cz,r2,sum,data,av;

	/* begin */
	n=0;
	sum=0;
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5; 
	cz=(in->HeaderN.z-1)*0.5; 
	for (x=0;x<in->HeaderN.x;x++){
	for (y=0;y<in->HeaderN.y;y++){
	for (z=0;z<in->HeaderN.z;z++){
		r2=SQR(z-cz);
		if (SQR(rmax) <= r2 && r2<SQR(rmax+1)) {
			mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
			sum+=data;
			n++;
		}
	}
	}
	}
	av=sum/n;
	return(av);
}
