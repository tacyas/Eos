/*
# mrcImageSiemensStar : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSiemensStar
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcImageSiemensStarInfo {
	int    Nx;
	int    Ny;
	double R; // [pixel]
	int    nOfRadial; 
	float  delta;

	int    Shape;
} lmrcImageSiemensStarInfo;
/*
typedef enum lmrcImageSiemensStarMode {
	a=0,
	b=1
} lmrcImageSiemensStarMode;
*/

int 
lmrcImageSiemensStarCreate(mrcImage* out, lmrcImageSiemensStarInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageSiemensStarInfo info;
	lmrcImageSiemensStarInfo linfo;
	mrcImage out; 
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.Nx = info.Nx;
	linfo.Ny = info.Ny;
	linfo.R  = info.R;
	linfo.nOfRadial = info.nRadial;
	linfo.delta =  info.Delta;
	linfo.Shape = info.Shape;

	lmrcImageSiemensStarCreate(&out, linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-mode : mrcImageHeaderMode: 2 float\n");
	fprintf(stderr, "                            0 char\n");
	fprintf(stderr, "-Shape  0 : SiemensStar(Step)\n");
	fprintf(stderr, "-Shape  1 : SiemensStar(Cos)\n");
	fprintf(stderr, "-Shape  2 : Linear(Step)\n");
	fprintf(stderr, "-Shape  3 : Linear(Cos)\n");
}


int 
lmrcImageSiemensStarCreate(mrcImage* out, lmrcImageSiemensStarInfo linfo, int mode)
{
	mrcImageParaTypeReal x, y;
	mrcImageParaTypeReal gx, gy;
	double data;
	double r, theta;
	double w, h, xx, yy;
	int flagTheta;
	double dTheta;

	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = linfo.Nx;	
	out->HeaderN.y = linfo.Ny;	
	out->HeaderN.z = 1;
	out->HeaderMode = mode;
	out->HeaderLength.x = out->HeaderLength.y = out->HeaderLength.z = linfo.delta;
	mrcInit(out, NULL);	


	dTheta = 2*M_PI/linfo.nOfRadial;
	gx = (linfo.Nx-1)/2.0;
	gy = (linfo.Ny-1)/2.0;
	for(x=0; x<out->HeaderN.x; x++) {
	for(y=0; y<out->HeaderN.y; y++) {
		r = sqrt(SQR(x-gx)+SQR(y-gy));		 	
		w = x-gx;
		h = y-gy;
		theta = atan2(y-gy, x-gx);
		switch(linfo.Shape) {
			case 0: {
				if(0<=theta) {
					flagTheta = (int)(( theta - ((int)(theta/dTheta))*dTheta)/(dTheta/2.0)); 
				} else {
					flagTheta = 1 - (int)((-theta + ((int)(theta/dTheta))*dTheta)/(dTheta/2.0)); 
				}
				if(flagTheta==1 && r<=linfo.R) {
					data = 1;
				} else {
					data = 0;
				}
				break;
			}
			case 1: {
				if(r<=linfo.R) {
					data = cos(theta*linfo.nOfRadial);
				} else {
					data = 0;
				}
				break;
			}
			case 2: {
				if(fabs(w)<=linfo.R && fabs(h)<=linfo.R) {
					xx = (w+linfo.R)/(2*linfo.R);
					yy = (h+linfo.R)/(2*linfo.R);
					data = (cos(linfo.nOfRadial*(1/(1-xx))*xx)*cos(linfo.nOfRadial*(1/(1-yy))*yy));
					if(data>0) { 
						data = 1;
					} else {
						data = 0;
					}
				} else {
					data = 0;
				}
				break;
			}
			case 3: {
				if(fabs(w)<=linfo.R && fabs(h)<=linfo.R) {
					xx = (w+linfo.R)/(2*linfo.R);
					yy = (h+linfo.R)/(2*linfo.R);
					data = (cos(linfo.nOfRadial*(1/(1-xx))*xx)*cos(linfo.nOfRadial*(1/(1-yy))*yy));
				} else {
					data = 0;
				}
				break;
			}
			default: {
				fprintf(stderr, "Not supported Mode: %d\n", linfo.Shape);
				exit(EXIT_FAILURE);
			}
		}	
		mrcPixelDataSet(out, x, y, 0, data, mrcPixelRePart);
	}
	}
	return 0;
}
