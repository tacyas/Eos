/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llExtractWithLayerSeparationCtrlFileCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llExtractWithLayerSeparationCtrlFileCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llExtractWithLayerSeparationCtrlFileCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define UNDEBUG
#include "genUtil.h"
#include "llData.h"
#include "mrcImage.h"

int
main(int argc, char* argv[]) 
{
	long l, n, n1, m;
	double mm;
	long lmax, nmax, nn;
	llExtractWithLayerSeparationCtrlFileCreateInfo info;
	mrcImage in;

	float CalculatedY;
	int IntCalculatedY;
	int error;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	if(info.flagIn) {
		mrcHeaderRead(&in, info.In, "in main", 0);
	}
	DEBUGPRINT("Program Start\n");
	DEBUGPRINT3("%d %d %d\n", info.nHelix, info.Turn, info.Unit);

	if (info.flagRZMax){
							lmax = floor(info.RZMax*info.truePitch); 
	} else {
							lmax = floor(info.RMax*info.truePitch); 
						}

	nmax = floor(2.0*PI*info.rMax*info.RMax + 2);

	if (info.flagIn){
		if (info.flagdY){
			fprintf(stderr, "The dY will be determine from -dY or -i option.  Erase -dY option. /n");
			exit(EXIT_FAILURE);
		} else {
			CalculatedY = in.HeaderN.y * in.HeaderLength.y / info.truePitch;
			IntCalculatedY = floor( 0.5 + CalculatedY);
			fprintf(stderr, "LengthY %15.6f [A] = LengthY %ld [Pixel] x PixelSize %15.6f [A/Pixel]\n",
								in.HeaderN.y * in.HeaderLength.y,in.HeaderN.y ,in.HeaderLength.y);
			error = floor(0.5 + (IntCalculatedY - CalculatedY)*info.truePitch/in.HeaderLength.y);
			
			info.dY = IntCalculatedY;
			fprintf(stderr, "Final CalculatedY  %15.6f\n",CalculatedY);
			fprintf(stderr, "      CalculatedY  %15d  \n",IntCalculatedY);
			fprintf(stderr, "      Error[Pixel] %15d  \n",error);
			info.dY = IntCalculatedY;
		}
	} else {
		if (info.flagdY){
			info.dY = info.dY;
		} else {
			fprintf(stderr, "The dY can not be determine.  Enter -i or -dY option. /n");
		}
	}


	fprintf(info.fptOut, "%ld %f %f %f\n", lmax, info.truePitch, info.rMax, info.RMax);
	for(l=0; l<lmax; l++) {
		fprintf(info.fptOut, "%ld %ld ", l, l*info.dY);
		nn = 0;
		for(n=-nmax; n<=nmax; n++) {
			/* 
				N l = t n + u m 
				m = (N l - t n)/u
			*/
			m  =          (info.nHelix*l - info.Turn*n) /          info.Unit;
			mm = ((double)(info.nHelix*l - info.Turn*n))/((double)(info.Unit));
			if(fabs(mm-m)<1e-6) {
				nn++;
			}
		}
		fprintf(info.fptOut, "%ld ", nn);
		
		for(n=0; n<=nmax; n++) {
			m  =          (info.nHelix*l - info.Turn*n) /          info.Unit;
			mm = ((double)(info.nHelix*l - info.Turn*n))/((double)(info.Unit));
			if(fabs(mm-m)<1e-6) {
				fprintf(info.fptOut, "%ld ", n);
			}	
			if(0<n) {
				n1 = -n;
				m  =          (info.nHelix*l - info.Turn*n1) /          info.Unit;
				mm = ((double)(info.nHelix*l - info.Turn*n1))/((double)(info.Unit));
				if(fabs(mm-m)<1e-6) {
					fprintf(info.fptOut, "%ld ", n1);
				}	
			}
		}
		fprintf(info.fptOut, "\n");
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
