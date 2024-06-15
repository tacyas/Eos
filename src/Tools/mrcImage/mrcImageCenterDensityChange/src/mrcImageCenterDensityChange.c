/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCenterDensityChange ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCenterDensityChange
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCenterDensityChange ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#define UNDEBUG2
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcImageCenterDensityChangeInfo {
	float rmin;
	float rmax;
	float ratio;
	long mode;
	long radiusMode;
} lmrcImageCenterDensityChangeInfo;

extern void lmrcImageCenterDensityChange(lmrcImageCenterDensityChangeInfo* info, mrcImage* out, mrcImage* in);

int
main(int argc, char* argv[]) 
{
	mrcImageCenterDensityChangeInfo info;
	lmrcImageCenterDensityChangeInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.rmin  = info.rmin;
	linfo.rmax  = info.rmax;
	linfo.ratio = info.ratio;
	linfo.mode  = info.mode;
	linfo.radiusMode  = info.radiusMode;

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in Main", 0);
	lmrcImageCenterDensityChange(&linfo, &out, &in);
	mrcFileWrite(&out, info.Out, "in Main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- radiusMode -----\n");
	fprintf(stderr, "0: \n");
	fprintf(stderr, "change density from r=0 to r=rmin \n");
	fprintf(stderr, "then connect density gradually from rmin to rmax \n");
	fprintf(stderr, "1: \n");
	fprintf(stderr, "connect density gradually from rmin to rmax \n");
	fprintf(stderr, "change density more than rmax \n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "0: multiply\n");
}

void
lmrcImageCenterDensityChange(lmrcImageCenterDensityChangeInfo* info, mrcImage* out, mrcImage* in)
{
	mrcImageParaTypeReal    x,    y,    z,  r; /* Pixel */
	mrcImageParaTypeReal cenx, ceny;
	double data;

	out->Header = in->Header;
	mrcInit(out, NULL);

	cenx = (in->HeaderN.x - 1)/2.0;
	ceny = (in->HeaderN.y - 1)/2.0;

	switch(info->radiusMode) {
		case 0: {
			for(x=0; x<in->HeaderN.x; x++){
				for(y=0; y<in->HeaderN.y; y++){
					for(z=0; z<in->HeaderN.z; z++){
						r = sqrt(SQR((x-cenx)*in->HeaderLength.x) + SQR((y-ceny)*in->HeaderLength.y)); /* A */
				
						if (r<=info->rmin){
							mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
							DEBUG2PRINT1("r [%15.6f] Change\n",r)
							data = data * info->ratio;
							mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
						} 
				
						if (r>info->rmin && r<=info->rmax){
							mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
							DEBUG2PRINT1("r [%15.6f] Intermidiate\n",r)
							data = data * ( (1- info->ratio)/(info->rmax - info->rmin)*(r - info->rmin)+info->ratio);
							mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
						}

						if (r>info->rmax){
							mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
							DEBUG2PRINT1("r [%15.6f] NoChange\n",r)
							mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
						}

					}
				}
			}
		break;
		}
		case 1: {
			for(x=0; x<in->HeaderN.x; x++){
				for(y=0; y<in->HeaderN.y; y++){
					for(z=0; z<in->HeaderN.z; z++){
						r = sqrt(SQR((x-cenx)*in->HeaderLength.x) + SQR((y-ceny)*in->HeaderLength.y)); /* A */
				
						if (r<=info->rmin){
							mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
							DEBUG2PRINT1("r [%15.6f] Change\n",r)
							mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
						} 
				
						if (r>info->rmin && r<=info->rmax){
							mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
							DEBUG2PRINT1("r [%15.6f] Intermidiate\n",r)
							data = data * ( (1- info->ratio)/(info->rmax - info->rmin)*(r - info->rmin)+info->ratio);
							mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
						}

						if (r>info->rmax){
							mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
							DEBUG2PRINT1("r [%15.6f] NoChange\n",r)
							data = data * info->ratio;
							mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
						}

					}
				}
			}
		break;
		}
	}
}
