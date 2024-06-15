/*
# mrcImageHelicalConvolution : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageHelicalConvolution
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

typedef struct lmrcImageHelicalConvolutionInfo {
	mrcImageParaTypeIntegerCoord N;
	float delPhi;
	float delZ;
} lmrcImageHelicalConvolutionInfo;

/*
typedef enum lmrcImageHelicalConvolutionMode {
	a=0,
	b=1
} lmrcImageHelicalConvolutionMode;
*/
extern int lmrcImageHelicalConvolution(mrcImage* out, 
		mrcImage* in, 
		lmrcImageHelicalConvolutionInfo info, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageHelicalConvolutionInfo info;
	lmrcImageHelicalConvolutionInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	
	linfo.N.x = info.Nx;
	linfo.N.y = info.Ny;
	linfo.N.z = info.Nz;
	linfo.delPhi = info.delPhi;
	linfo.delZ   = info.delZ;

	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageHelicalConvolution(&out, &in, linfo, 0);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


int 
lmrcImageHelicalConvolution(mrcImage* out, 
		mrcImage* in, 
		lmrcImageHelicalConvolutionInfo linfo, int mode)
{
	mrcImageParaTypeRealCoord srcc;
	mrcImageParaTypeRealCoord dstc;
	mrcImageParaTypeRealCoord src;
	mrcImageParaTypeRealCoord dst;

	out->Header.Cont = in->Header.Cont;
	out->Header.Cont.N = linfo.N; 
	mrcInit(out, NULL);

	srcc.x = (in->HeaderN.x-1)/2;
	srcc.y = (in->HeaderN.y-1)/2;
	srcc.z = (in->HeaderN.z-1)/2;

	dstc.x = (out->HeaderN.x-1)/2;
	dstc.y = (out->HeaderN.y-1)/2;
	dstc.z = (out->HeaderN.z-1)/2;

	for(dst.z=0; dst.z<out->HeaderN.z; dst.z++) {		
	for(dst.y=0; dst.y<out->HeaderN.y; dst.y++) {		
	for(dst.x=0; dst.x<out->HeaderN.x; dst.x++) {		
		if(dst.z<in->HeaderN.z) {
			src.x = (dst.x - dstc.x) + srcc.x; 
			src.y = (dst.y - dstc.y) + srcc.y; 
			src.z = dst.z;
		} else {
			//src.z = ()/in->HeaaderLength.x;
		}
	}
	}
	}
}
