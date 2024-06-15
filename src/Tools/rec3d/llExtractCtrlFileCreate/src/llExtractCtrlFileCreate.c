/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llExtractCtrlFileCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llExtractCtrlFileCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llExtractCtrlFileCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "llData.h"
#include "lllExtractdYEstimate.h"

typedef struct infoDataList {
	llDataParaTypeReal lx; /* Length of x */
	llDataParaTypeReal ly; /* Length of y */
	int nx; /* Nx */
	int ny; /* Ny */
	int center; /* Axis */
	int layerline; /* llMax */
	llDataParaTypeReal Ax; /* delRInv */
	int dY; /* How many repeats */ 
	float truePitch; /* TruePitch */
	char* Out;       /* FileName */
	FILE *fptOut;    /* FilePtr */
	long flagIn;
	mrcImage       in;
	int turn;
	int unit;
	int nstrand;
	int Y1;
	int Y0;
	float Rmax;
	float rMax;
} infoDataList;

extern void lllExtractCtrlFileCreateAny(infoDataList info, int mode);
extern void lllExtractCtrlFileCreateMyosin(llExtractCtrlFileCreateInfo* info,
											infoDataList* linfo);


int
main(int argc, char* argv[]) 
{
	llExtractCtrlFileCreateInfo info;
	infoDataList linfo;
	lllExtractdYEstimateInfo dYinfo;

	mrcImage in;	
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	memoryClear(&dYinfo, sizeof(dYinfo), (char)0);

	switch(info.mode) {
		case 0: {
			linfo.lx		= info.lx;
			linfo.ly		= info.ly;
			linfo.nx		= info.nx;
			linfo.ny		= info.ny;
			linfo.center    = info.center;
			linfo.layerline = info.layerline;
			linfo.Ax        = info.Ax;
			linfo.dY        = info.dY;
			linfo.truePitch = info.truePitch;
			linfo.Out       = info.Out;
			linfo.fptOut    = info.fptOut;

			dYinfo.truePitch = info.truePitch;
			dYinfo.deltadY   = info.deltadY;
			dYinfo.mag       = 1.0;
			dYinfo.PixelSize = info.PixelSize;

			/* dY determination */
			if (info.flagIn){
				if (info.flagdY){
					fprintf(stderr, "The dY will be determine from -dY or -i option.  Erase -dY option. /n");
					exit(EXIT_FAILURE);
				} else {
					mrcHeaderRead(&in, info.In, "in main", 0);
					linfo.dY = lllExtractdYEstimate(&in, &dYinfo);
				}
			} else {
				if (info.flagdY){
					linfo.dY = linfo.dY;
				} else {
					fprintf(stderr, "The dY can not be determine.  Enter -i or -dY option. \n");
				}
			}
			lllExtractCtrlFileCreateMyosin(&info, &linfo);
			break;
		}
		case 1: {
			linfo.fptOut = info.fptOut;
			linfo.Out    = info.Out;
			linfo.flagIn = info.flagIn;
			if(info.flagIn) {
				mrcHeaderRead(&(linfo.in), info.In, "in main", 0);
			}
			linfo.Y1 = info.Y1;
			linfo.Y0 = info.Y0;
			linfo.turn = info.turn;
			linfo.unit = info.unit;
			linfo.nstrand = info.nstrand;
			linfo.truePitch = info.truePitch;
			linfo.Rmax   = info.Rmax;
			linfo.rMax   = info.rmax;
			lllExtractCtrlFileCreateAny(linfo, 0);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %ld \n", info.mode);
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "    0: for myosin  t=1 u=9\n");
	fprintf(stderr, "    1: for anything\n");
}

void
lllExtractCtrlFileCreateAny(infoDataList linfo, int mode)
{
	int llMax, ll;
	int nlMax;
	int nnMax;
	int nl;
	int nn, n1;
	int nm, Y;
	double mm;
	int* n;
	int* m;
	int* l;

	nlMax = floor(linfo.Rmax*linfo.truePitch);
	nnMax = floor(2.0*PI*linfo.rMax*linfo.Rmax + 2.0); 
	fprintf(stderr, "nlMax: %d nnMax: %d\n", nlMax, nnMax);
	for(nl=0, llMax = 0; nl<nlMax; nl++) {
		for(nn=0; nn<=nnMax; nn++) {
			nm =         (linfo.nstrand*nl - linfo.turn*nn)/        linfo.unit;
			mm = (double)(linfo.nstrand*nl - linfo.turn*nn)/(double)linfo.unit;
			if(fabs(mm-nm)<1e-6) {
				llMax++;	
			}
			if(0<nn) {
				n1 = -nn;
				nm =         (linfo.nstrand*nl - linfo.turn*n1)/        linfo.unit;
				mm = (double)(linfo.nstrand*nl - linfo.turn*n1)/(double)linfo.unit;
				if(fabs(mm-nm)<1e-6) {
			 		llMax++;	
				}
			}
		}
	}
	n = (int*)memoryAllocate(sizeof(int)*llMax, ""); 
	m = (int*)memoryAllocate(sizeof(int)*llMax, ""); 
	l = (int*)memoryAllocate(sizeof(int)*llMax, ""); 

	for(nl=0, ll = 0; nl<nlMax; nl++) {
		for(nn=0; nn<=nnMax; nn++) {
			nm =         (linfo.nstrand*nl - linfo.turn*nn)/        linfo.unit;
			mm = (double)(linfo.nstrand*nl - linfo.turn*nn)/(double)linfo.unit;
			if(fabs(mm-nm)<1e-6) {
				n[ll] = nn; 
				m[ll] = nm; 
				l[ll] = nl;
				ll++;	
			}
			if(0<nn) {
				n1 = -nn;
				nm =         (linfo.nstrand*nl - linfo.turn*n1)/        linfo.unit;
				mm = (double)(linfo.nstrand*nl - linfo.turn*n1)/(double)linfo.unit;
				if(fabs(mm-nm)<1e-6) {
					n[ll] = n1; 
					m[ll] = nm; 
					l[ll] = nl;
			 		ll++;	
				}
			}
		}
	}
	if(linfo.flagIn) {
		linfo.lx = linfo.in.HeaderLength.x;
		linfo.ly = linfo.in.HeaderLength.y;
		linfo.nx = linfo.in.HeaderN.x;
		linfo.ny = linfo.in.HeaderN.y;
		linfo.center = linfo.in.HeaderN.x/2;
		linfo.Ax = linfo.in.HeaderN.x*linfo.in.HeaderLength.x; 
	}

	fprintf(linfo.fptOut, "llData\n");
	fprintf(linfo.fptOut, "%g %g\n", linfo.lx, linfo.ly);
	fprintf(linfo.fptOut, "%d %d\n", linfo.nx/2-1, linfo.ny/2-1);
	fprintf(linfo.fptOut, "In\n");
	fprintf(linfo.fptOut, "Nea\n");
	fprintf(linfo.fptOut, "Far\n");
	fprintf(linfo.fptOut, "0.0\n");
	fprintf(linfo.fptOut, "0.0\n");
	fprintf(linfo.fptOut, "0.0\n");
	fprintf(linfo.fptOut, "0\n");
	fprintf(linfo.fptOut, "0.0\n");
	fprintf(linfo.fptOut, "0.0\n");
	fprintf(linfo.fptOut, "%d\n", linfo.center);
	fprintf(linfo.fptOut, "%d\n", llMax);
	fprintf(linfo.fptOut, "%g\n", linfo.Ax);
	fprintf(linfo.fptOut, "0\n");
	for(ll=0; ll<llMax; ll++) {
		Y = linfo.Y0*m[ll] + linfo.Y1*n[ll]*linfo.turn/fabs(linfo.turn);
		fprintf(linfo.fptOut, "%6d %6d %6d 0 %d 0 %d ", n[ll], l[ll], Y, linfo.nx/2-1, linfo.nx/2-1);
		if(0==Y) {
			fprintf(linfo.fptOut, "0.5\n");
		} else {
			fprintf(linfo.fptOut, "1.0\n");
		}
	}
}

void 
lllExtractCtrlFileCreateMyosin(llExtractCtrlFileCreateInfo* info,
											infoDataList* linfo)
{
		fprintf(linfo->fptOut, "llData\n");
		fprintf(linfo->fptOut, "%g %g\n",linfo->lx,linfo->ly);
		fprintf(linfo->fptOut, "%d %d\n",linfo->nx,linfo->ny);
		fprintf(linfo->fptOut, "0\n");
		fprintf(linfo->fptOut, "0\n");
		fprintf(linfo->fptOut, "0\n");
		fprintf(linfo->fptOut, "0\n");
		fprintf(linfo->fptOut, "0\n");
		fprintf(linfo->fptOut, "0\n");
		fprintf(linfo->fptOut, "0\n");
		fprintf(linfo->fptOut, "0\n");
		fprintf(linfo->fptOut, "0\n");
		fprintf(linfo->fptOut, "%d\n",linfo->center);
		fprintf(linfo->fptOut, "%d\n",linfo->layerline);
		fprintf(linfo->fptOut, "%f\n",linfo->Ax);
		fprintf(linfo->fptOut, "0\n");
		fprintf(linfo->fptOut, "   0  0  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*0  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   3  1  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*1  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "  -6  1  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*1  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "  -3  2  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*2  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   6  2  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*2  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   0  3  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*3  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   3  4  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*4  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "  -6  4  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*4  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "  -3  5  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*5  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   6  5  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*5  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   0  6  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*6  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   3  7  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*7  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "  -6  7  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*7  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "  -3  8  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*8  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   6  8  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*8  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   0  9  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*9  ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   3 10  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*10 ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "  -6 10  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*10 ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "  -3 11  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*11 ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   6 11  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*11 ,linfo->center-1 ,linfo->center-1 );
		fprintf(linfo->fptOut, "   0 12  %4d  0    %4d   0   %4d  1.0 \n",linfo->dY*12 ,linfo->center-1 ,linfo->center-1 );
}

