/*
# mrcImageRandomParticlesImageCreate : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageRandomParticlesImageCreate
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

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"

typedef struct lmrcImageRandomParticlesImageCreateInfo {
	int	Nx;
	int	Ny;
	int Seed;
	int InterpolationMode;
} lmrcImageRandomParticlesImageCreateInfo;

typedef enum lmrcImageRandomParticlesImageCreateMode {
	 lmrcImageRandomParticlesImageCreateModeRandomPosiion=1,
	 lmrcImageRandomParticlesImageCreateModeRandomRotation=2
} lmrcImageRandomParticlesImageCreateMode;


extern  void lmrcImageRandomParticleCreate(mrcImage* out, mrcImage* in, int n,  lmrcImageRandomParticlesImageCreateInfo linfo,  lmrcImageRandomParticlesImageCreateMode lmode);

int
main(int argc, char* argv[]) 
{
	mrcImageRandomParticlesImageCreateInfo info;
	lmrcImageRandomParticlesImageCreateInfo linfo;
	lmrcImageRandomParticlesImageCreateMode lmode;
	mrcImage* in;
	mrcImage out;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main"); 
	for(i=0; i<info.flagIn; i++) {
		DEBUGPRINT2("%d %s\n", i, info.In[i]);
		mrcFileRead(&in[i], info.In[i], "in main", 0);
	}
	
	linfo.Nx = info.Nx;
	linfo.Ny = info.Ny;
	linfo.Seed = info.Seed;
	linfo.InterpolationMode = info.InterpolationMode;

	lmode  = info.mode;

	lmrcImageRandomParticleCreate(&out, in, info.flagIn, linfo, lmode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void 
lmrcImageRandomParticleCreate(
	mrcImage* out, 
	mrcImage* in, int n,  
	lmrcImageRandomParticlesImageCreateInfo linfo,  
	lmrcImageRandomParticlesImageCreateMode lmode)
{
	int i;
	double offsetx, offsety;
	double angle;
	float dstx, dsty, srcx, srcy;
	float radius;
	double src, dst;

	DEBUGPRINT("lmrcImageRandomParticleCreate Start\n");
	out->Header.Cont = in[0].Header.Cont;
	out->HeaderN.x = linfo.Nx;
	out->HeaderN.y = linfo.Ny;
	out->HeaderN.z = 1;
	mrcInit(out, NULL);

	srand(linfo.Seed);

	for(i=0; i<n; i++) {
		offsetx = (int)(((double)rand())/RAND_MAX*out->HeaderN.x + 0.5);
		offsety = (int)(((double)rand())/RAND_MAX*out->HeaderN.y + 0.5);
		angle   = ((double)rand())/RAND_MAX*2*M_PI;
		DEBUGPRINT4("%d %f %f %f\n", i, offsetx, offsety, angle); 

		radius = (int)(MAX(in[i].HeaderN.x, in[i].HeaderN.y)*sqrt(2.0)/2.0 + 0.5);	
		
		for(dsty= -radius; dsty < radius; dsty++) {
		for(dstx= -radius; dstx < radius; dstx++) {
			srcx =  dstx*cos(angle) + dsty*sin(angle) + in[i].HeaderN.x/2.0; 
			srcy = -dstx*sin(angle) + dsty*cos(angle) + in[i].HeaderN.y/2.0; 
			if(-0.5<=srcx && srcx < in[i].HeaderN.x-0.5 &&
			   -0.5<=srcy && srcy < in[i].HeaderN.y-0.5) {
				mrcPixelDataGet(out, dstx+offsetx, dsty+offsety, 0, &dst, mrcPixelRePart, mrcPixelHowNearest);  
				mrcPixelDataGet(&in[i], srcx, srcy, 0, &src, mrcPixelRePart, linfo.InterpolationMode); 

				mrcPixelDataSet(out, dstx+offsetx, dsty+offsety, 0, dst+src, mrcPixelRePart);
			}
		}
		}
	}

}
