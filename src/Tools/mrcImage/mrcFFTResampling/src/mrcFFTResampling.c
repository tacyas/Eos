/*
# mrcFFTResampli*mulxng : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcFFTResampling
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

/*
Example:
typedef struct lmrcFFTResamplingInfo {
	float a;
	int   b;
} lmrcFFTResamplingInfo;

typedef enum lmrcFFTResamplingMode {
	a=0,
	b=1
} lmrcFFTResamplingMode;
*/

typedef struct lmrcFFTResamplingInfo{
	float Nx;
	float Ny;
}lmrcFFTResamplingInfo;	


extern void lmrcFFTResampling(mrcImage *out, mrcImage *in, lmrcFFTResamplingInfo linfo, int mode); 


int
main(int argc, char* argv[]) 
{
	mrcFFTResamplingInfo info;
	lmrcFFTResamplingInfo linfo;

	mrcImage in;
	mrcImage out;


	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "from main", 0);

	linfo.Nx = info.Nx;
	linfo.Ny = info.Ny;

	lmrcFFTResampling(&out, &in, linfo, info.mode);
	mrcFileWrite(&out, info.Out, "from main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
lmrcFFTResampling(mrcImage *out, mrcImage *in, lmrcFFTResamplingInfo linfo, int mode)
{

	float iX, iY, mulx, muly;
	double re, im, dstre, dstim;


	out->Header = in->Header;

	out->HeaderN.x = linfo.Nx;
	out->HeaderN.y = linfo.Ny;
	mrcInit(out, NULL);
	
	mulx = (in->HeaderN.x *  in->HeaderLength.x) / (out->HeaderN.x * out->HeaderLength.x);	
	muly = (in->HeaderN.y *  in->HeaderLength.y) / (out->HeaderN.y * out->HeaderLength.y);	

	DEBUGPRINT2("%lf%lf\n", mulx, muly);

	for(iY = - out->HeaderN.y / 2.0; iY < out->HeaderN.y / 2.0; iY++){
		for(iX = 0.0; iX <= out->HeaderN.x / 2.0; iX++){
			
			mrcPixelDataGet(in, iX*mulx, iY*muly, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, iX*mulx, iY*muly, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);

			dstre = re;
			dstim = im;

			mrcPixelDataSet(out, iX, iY, 0.0, dstre, mrcPixelRePart);
			mrcPixelDataSet(out, iX, iY, 0.0, dstim, mrcPixelImPart);

		}
	}	
}			
		
	
