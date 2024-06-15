/*
# mrcImageRadonTransform : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageRadonTransform
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

typedef struct lmrcImageRadonTransformInfo {
	double dtheta; 		/* delta theta : [rad] */
	double dphi; 		/* delta phi: [rad] */
} lmrcImageRadonTransformInfo;

/*
typedef enum lmrcImageRadonTransformMode {
	a=0,
	b=1
} lmrcImageRadonTransformMode;
*/

extern void lmrcImageRadonTransform(mrcImage* out, mrcImage* in, lmrcImageRadonTransformInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageRadonTransformInfo info;
	lmrcImageRadonTransformInfo linfo;

	mrcImage in;
	mrcImage out;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "Read In", 0);

    linfo.dtheta = info.dtheta*RADIAN;
	linfo.dphi   = info.dphi*RADIAN;
	lmrcImageRadonTransform(&out, &in, linfo, info.mode);  

	mrcFileWrite(&out, info.Out, "Write Out", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void
lmrcImageRadonTransform(mrcImage* out, mrcImage* in, lmrcImageRadonTransformInfo linfo, int mode)
{
	mrcImageParaTypeReal srcx, srcy, srcz;
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal difference;
	mrcImageParaTypeReal p, theta, phi;
	double sum, data;
	mrcImageParaTypeReal costheta,sintheta,cosphi,sinphi,movep;

	out->Header = in->Header;
	out->HeaderN.x = MAX(in->HeaderN.x,MAX(in->HeaderN.y,in->HeaderN.z));	/* p-axis */  
	out->HeaderN.y = M_PI/linfo.dtheta;  					/* theta-axis */
	out->HeaderN.z = 2*M_PI/linfo.dphi;  					/* phi-axis */
	out->HeaderLength.x = in->HeaderLength.x;
	out->HeaderLength.y = linfo.dtheta*DEGREE;
	out->HeaderLength.z = linfo.dphi*DEGREE;
	out->HeaderMode = mrcFloatRadonImage;
	mrcInit(out, NULL);

	for(p=0;     p<out->HeaderN.x; p++) {
		if(fmod(p,out->HeaderN.x/10)==0){
			DEBUGPRINT("*");
		}
	for(theta=0; theta<out->HeaderN.y; theta++) {
	for(phi=0;   phi<out->HeaderN.z; phi++) {
		sum = 0;
		costheta = cos(theta*out->HeaderLength.y*RADIAN);
		sintheta = sin(theta*out->HeaderLength.y*RADIAN);
		cosphi = cos(phi*out->HeaderLength.z*RADIAN);
		sinphi = sin(phi*out->HeaderLength.z*RADIAN);
		movep = (p-(out->HeaderN.x-1)/2)*out->HeaderLength.x;
		for(srcx=0;srcx<in->HeaderN.x; srcx++){
		for(srcy=0;srcy<in->HeaderN.y; srcy++){
		for(srcz=0;srcz<in->HeaderN.z; srcz++){

		  x = in->HeaderLength.x*(srcx-(in->HeaderN.x-1)/2);
		  y = in->HeaderLength.y*(srcy-(in->HeaderN.y-1)/2);
		  z = in->HeaderLength.z*(srcz-(in->HeaderN.z-1)/2);

		  difference = x*costheta*cosphi-y*sinphi+z*sintheta*cosphi-movep;
		  difference /= out->HeaderLength.x;
		  if(difference<0.5 && difference>=-0.5){
		    mrcPixelDataGet(in, srcx, srcy, srcz, &data, mrcPixelRePart, mrcPixelHowNearest);
		    sum += data;
		  }
		}
		}
		}
		mrcPixelDataSet(out, p, theta, phi, sum, mrcPixelRePart);
	}
	}
	}
	DEBUGPRINT("\n");
}

