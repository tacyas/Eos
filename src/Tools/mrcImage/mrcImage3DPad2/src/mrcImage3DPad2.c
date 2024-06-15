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
static char __sccs_id[] = "%Z%mrcImage3DPad2 ver%I%; Date:%D% %Z%";
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
void lmrcImage3DPadfilament(mrcImage* out ,mrcImage* in , lmrcImage3DPadInfo linfo, int mode );
double lmrcImage3DPadfilamentCalcavr(mrcImage* in ,double rmax);
double lmrcImage3DPadCalcavr(mrcImage* in ,double rmax);
void lmrcImage3DPad(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode);


int
main(int argc, char* argv[]) 
{
	mrcImage3DPad2Info info;
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

    DEBUGPRINT3("N: %d %d %d\n", linfo.Nx, linfo.Ny, linfo.Nz);
	if (!info.mode2){
	  lmrcImage3DPadfilament(&out, &in, linfo, info.mode);
	} else {
	  lmrcImage3DPad(&out, &in, linfo, info.mode);
	}
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
  fprintf(stderr, "----- mode -----\n");
  fprintf(stderr, "0:Default: Out of threshold is avrage of threshold plain.\n");
  fprintf(stderr, "1:Mulplying cos function. Default: Out of threshold is avrage of threshold plain.\n");
  fprintf(stderr, "----- mode2 -----\n");
  fprintf(stderr, "0:For filaments.  R is calculated from its axis.\n");
  fprintf(stderr, "1:For particles.  R is calculated from its center.\n");

}

void 
lmrcImage3DPadfilament(mrcImage* out ,mrcImage* in , lmrcImage3DPadInfo linfo, int mode)
{
	/* variables */
	int x,y,z;
	double data,cx,cy,sx,sy,r2,av,c,dr2,averager;
	double offset;

	/* begin */
	out->Header = in->Header;
	out->HeaderN.x = linfo.Nx;
	out->HeaderN.y = linfo.Ny;
	mrcInit(out,NULL);
	DEBUGPRINT1("TailerNum %d\n", in->numTailer);
	if(0<in->numTailer) {
		out->numTailer = in->numTailer;
		out->Tailer = in->Tailer;
		DEBUGPRINT1("TailerNum %d in Out\n", out->numTailer);
	}

	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5;
	sx=(out->HeaderN.x-in->HeaderN.x)*0.5;
	sy=(out->HeaderN.y-in->HeaderN.y)*0.5;
	r2=SQR(linfo.rmax);
	switch(mode){
		case 0:
			if (!linfo.flagv){
				if (linfo.rmax > (in->HeaderN.x - 1)/2.0 || linfo.rmax > (in->HeaderN.y - 1)/2.0){
					averager = MIN((in->HeaderN.x - 1)/2.0, (in->HeaderN.y - 1)/2.0 );
				} else {
					averager = linfo.rmax;
				}
				DEBUGPRINT1("r: %g \n",averager);
        if(linfo.flagr) {
				  av=lmrcImage3DPadfilamentCalcavr(in, averager);
        } else {
				  av=lmrcImage3DPadfilamentCalcavr(in, -1);
        }
			} else {
				av=linfo.v;
			}
			if(linfo.flagFloating) {
				fprintf(stderr, "Floating avg:%f\n", av);
				offset = av;
			} else {
				offset = 0;
			}
			for (z=0;z<out->HeaderN.z;z++){
			for (y=0;y<out->HeaderN.y;y++){
			for (x=0;x<out->HeaderN.x;x++){
				mrcPixelDataSet(out, x, y, z , av-offset, mrcPixelRePart);
			}
			}
			}
			for (z=0;z<in->HeaderN.z;z++){
			for (y=0;y<in->HeaderN.y;y++){
			for (x=0;x<in->HeaderN.x;x++){
				mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
				if(linfo.flagr) {
					dr2=SQR(x-cx)+SQR(y-cy);
					if (dr2<=r2) {
						mrcPixelDataSet(out ,x+sx ,y+sy ,z ,data-offset, mrcPixelRePart);
					} 
				} else {	      
					mrcPixelDataSet(out ,x+sx ,y+sy ,z ,data-offset, mrcPixelRePart);
				}	    
			}
			}
			}
			break;
		case 1:
		case 2:
			if (!linfo.flagv){
        if(linfo.flagr) {
				  av = lmrcImage3DPadfilamentCalcavr(in, linfo.rmax+linfo.w);
        } else {
				  av = lmrcImage3DPadfilamentCalcavr(in, -1);
        }
				DEBUGPRINT1("r: %g \n",averager);
				fprintf(stdout,"av: %g \n",av);
			} else {
				av=linfo.v;
			}
			if(linfo.flagFloating) {
				offset = av;
			} else {
				offset = 0;
			}
			for (z=0;z<in->HeaderN.z;z++){
			for (y=0;y<in->HeaderN.y;y++){
			for (x=0;x<in->HeaderN.x;x++){
				mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
				if (linfo.flagr){
					dr2=SQR(x-cx)+SQR(y-cy);
					if (SQR(linfo.rmax-linfo.w)>dr2 ){
						mrcPixelDataSet(out ,x+sx ,y+sy ,z ,data - offset , mrcPixelRePart);
					}else if (SQR(linfo.rmax+linfo.w)<dr2 ){
						mrcPixelDataSet(out ,x+sx ,y+sy ,z ,av - offset , mrcPixelRePart);
					}else {
						c= (sin( ( linfo.rmax-sqrt(dr2)) / linfo.w *PI/2 )+1 ) /2;
						mrcPixelDataSet(out ,x+sx ,y+sy ,z ,(data-av)*c+av-offset, mrcPixelRePart);
					}
				} else {
					mrcPixelDataSet(out ,x+sx ,y+sy ,z ,av-offset, mrcPixelRePart);
				}	    
			}
			}
			}  
	}
	mrcStatDataSet(out ,0);
}

double lmrcImage3DPadfilamentCalcavr(mrcImage* in ,double rmax)
{
	/* variables */
	int x,y,z,n;
	double cx,cy,r2,sum,data,av;

	/* begin */
	n=0;
	sum=0;
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5; 
	for (y=0;y<in->HeaderN.y;y++){
	for (x=0;x<in->HeaderN.x;x++){
		r2=SQR(x-cx)+SQR(y-cy);
		if (SQR(rmax) <= r2 && r2<SQR(rmax+1)){
			for (z=0 ;z<in->HeaderN.z;z++){
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


void lmrcImage3DPad(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode) 
{

	/* variables */
	int x,y,z;
	double data,cx,cy,cz,sx,sy,sz,r2,av,c,dr2;
	double dstx, dsty, dstz;
	double offset, v;

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

  // Floating and padding value
	if (linfo.flagFloating) { // Boundery
        if(linfo.flagr) {
		      av=lmrcImage3DPadCalcavr(in, linfo.rmax);
        } else {
		  	  av=lmrcImage3DPadCalcavr(in, -1);
        }
	} else { // NotFloating
      av = 0;
  }

	if(linfo.flagFloating) {
    if(linfo.flagv) {
      v = linfo.v;
	    offset = av - v;
    } else {
      v = 0;
      offset = av;
    }
	} else {
    v = 0;
		offset = 0;
	}

  // Padding value
	for (z=0;z<out->HeaderN.z;z++){
	for (y=0;y<out->HeaderN.y;y++){
	for (x=0;x<out->HeaderN.x;x++){
    // 
	  mrcPixelDataSet(out, x, y, z, v, mrcPixelRePart);
	}
	}
	}

	switch(mode){
		case 0:
			for (z=0;z<out->HeaderN.z;z++){
			for (y=0;y<out->HeaderN.y;y++){
			for (x=0;x<out->HeaderN.x;x++){
				mrcPixelDataSet(out, x, y, z, av-offset, mrcPixelRePart);
			}
			}
			}
			for (z=0;z<in->HeaderN.z;z++){
			for (y=0;y<in->HeaderN.y;y++){
			for (x=0;x<in->HeaderN.x;x++){
				mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
				if (linfo.flagr){
					dr2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
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
		case 2:
			//fprintf(stdout,"av :%g\n",av); 
			for (z=0;z<in->HeaderN.z;z++){
			for (y=0;y<in->HeaderN.y;y++){
			for (x=0;x<in->HeaderN.x;x++){
				dstx = x + sx;
				dsty = y + sy;
				dstz = z + sz;
				if(-0.5<=dstx && dstx<out->HeaderN.x-0.5
				 &&-0.5<=dsty && dsty<out->HeaderN.y-0.5
				 &&-0.5<=dstz && dstz<out->HeaderN.z-0.5) {
					mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
					if (linfo.flagr) {
						dr2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
						if (dr2<SQR(linfo.rmax-linfo.w)) {
							mrcPixelDataSet(out ,dstx, dsty, dstz, data-offset, mrcPixelRePart);
						} else if (SQR(linfo.rmax+linfo.w)<dr2) {
							mrcPixelDataSet(out ,dstx, dsty, dstz, av-offset, mrcPixelRePart);
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
  if(0<=rmax) {
		n=0;
		sum=0;
		cx=(in->HeaderN.x-1)*0.5;
		cy=(in->HeaderN.y-1)*0.5; 
		cz=(in->HeaderN.z-1)*0.5; 
		for (z=0;z<in->HeaderN.z;z++){
		for (y=0;y<in->HeaderN.y;y++){
		for (x=0;x<in->HeaderN.x;x++){
			r2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
			if (SQR(rmax) <= r2 && r2<SQR(rmax+1)) {
				mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
				sum+=data;
				n++;
			}
		}
		}
		}
		av=sum/n;
  } else {
		n=0;
		sum=0;
		for (z=0;z<in->HeaderN.z;z++){
		for (y=0;y<in->HeaderN.y;y++){
		for (x=0;x<in->HeaderN.x;x++){
      if( z==0||z==in->HeaderN.z-1
        ||y==0||y==in->HeaderN.y-1
        ||x==0||x==in->HeaderN.x-1) {
				sum+=data;
				n++;
			}
		}
		}
		}
    av=sum/n;
  }
	return(av);
}
