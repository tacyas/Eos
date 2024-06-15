/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCircumferentialProjection ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCircumferentialProjection
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCircumferentialProjection ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define UNDEBUG
#define UNDEBUG2
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcImageCircumferentialProjectionInfo {
	float dang;
	float zmin;
	float zmax;
	float dz;
	float rmin;
	float rmax;
	float dr;
	float threshold;
	long mode;
} lmrcImageCircumferentialProjectionInfo;

extern void lmrcImageCircumferentialProjection(  mrcImage* out,
												 mrcImage* in,
												lmrcImageCircumferentialProjectionInfo* info);

int
main(int argc, char* argv[]) 
{
	mrcImageCircumferentialProjectionInfo info;
	lmrcImageCircumferentialProjectionInfo linfo;
	mrcImage out;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	mrcFileRead(&in, info.In, "in main", 0);

	linfo.dang    = info.dang;
	linfo.zmin    = info.zmin;
	linfo.zmax    = info.zmax;
	linfo.dz      = info.dz;
	linfo.rmin    = info.rmin;
	linfo.rmax    = info.rmax;
	linfo.dr      = info.dr;
	linfo.threshold = info.threshold;
	linfo.mode    = info.mode;

	lmrcImageCircumferentialProjection(&out, &in, &linfo);
			
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "x --> r\n");
	fprintf(stderr, "y --> z\n");
	fprintf(stderr, "--------- mode ---------\n");
	fprintf(stderr, "0: Out Put Averaged Density (dataSum = dataSum / nang)\n");
	fprintf(stderr, "1: Out Put Added    Density (dataSum = dataSum / nang *(2*PI*r))\n");
	fprintf(stderr, "2: Out Put Averaged Density more than threshold (dataSum = dataSum / [nang number more than threshold value] *(2*PI*r))\n");
}

void
lmrcImageCircumferentialProjection(mrcImage* out,
								   mrcImage* in,
								  lmrcImageCircumferentialProjectionInfo* linfo)
{
	mrcImageParaTypeReal cx,cy;
	mrcImageParaTypeReal srcx,srcy,srcz;
	mrcImageParaTypeReal dstz,dstr;
	mrcImageParaTypeReal  r, ang, z;
	mrcImageParaTypeReal nr,nang,nz;
	double data, dataSum=0, count=1;

	out->HeaderN.x = (int) ((linfo->rmax   - linfo->rmin  )/linfo->dr   + 1);
	out->HeaderN.y = (int) ((linfo->zmax   - linfo->zmin  )/linfo->dz   + 1);
	out->HeaderN.z = 1; 
	out->HeaderLength.x = linfo->dr;
	out->HeaderLength.y = linfo->dz;
	out->HeaderLength.z = linfo->dz;
	out->HeaderMode = mrcFloatImage;
	mrcInit(out, NULL);

	cx = in->HeaderN.x / 2 * in->HeaderLength.x;
	cy = in->HeaderN.y / 2 * in->HeaderLength.y;

	if ( linfo->zmin<0 || linfo->zmax>in->HeaderN.z*in->HeaderLength.z
	                   || linfo->rmin<0 || linfo->rmax>cx){
		fprintf(stderr,"strange range in zmin:%f zmax:%f rmin:%f rmax:%f\n",
							linfo->zmin,linfo->zmax,linfo->rmin,linfo->rmax);
		exit(EXIT_FAILURE);
	}
	DEBUG2PRINT2("%f  %f\n",cx,cy);

	for(nz=0,z=linfo->zmin; nz<out->HeaderN.y; nz++,z+=linfo->dz){
		for(nr=0,r=linfo->rmin; nr<out->HeaderN.x; nr++,r+=linfo->dr){
			for(nang=0,ang=0; nang<(int)(360/linfo->dang); nang++,ang+=linfo->dang){
				srcx = r*cos(ang*RADIAN) + cx;
				srcy = r*sin(ang*RADIAN) + cy;
				srcz = z;
				dstz = z - linfo->zmin;
				dstr = r - linfo->rmin;
				DEBUG2PRINT5("(%f,%f,%f)->(%f,%f) :",srcx,srcy,srcz,dstz,dstr);
				mrcImageDataGetbyAU(in, srcx, srcy, srcz, &data, mrcPixelRePart, mrcPixelHowLinear);
				DEBUG2PRINT1("%f \n",data);
				if (data < linfo->threshold) {
				}else{
					dataSum += data;
					count ++;
				}
			}

			switch(linfo->mode){
				case 0: {
					DEBUGPRINT1("mode:(%ld) average \n",linfo->mode);
					dataSum = dataSum / nang;
					break;
				}
				case 1: {
					DEBUGPRINT1("mode:(%ld) add \n",linfo->mode);
					dataSum = dataSum / nang *2 *PI *r;
					break;
				}
				case 2: {
					DEBUGPRINT2("mode:(%ld) add more than threshold, count:(%15.6f) \n",linfo->mode, count);
					dataSum = dataSum / count;
					break;
				}
				default: {
					fprintf(stderr, "Not supported Mode in lmrcImageCircumferentialProjection: %ld\n", linfo->mode);
					exit(EXIT_FAILURE);
				}
			}

			mrcImageDataSetbyAU(out, dstr, dstz, 0,  dataSum, mrcPixelRePart);
			dataSum =0;
			count =1;
		}
	}

	/*
	for(nz=0,z=linfo->zmin; nz<out->HeaderN.y; nz++,z+=linfo->dz){
		for(nr=0,r=linfo->rmin; nr<out->HeaderN.x; nr++,r+=linfo->dr){
			for(nang=0,ang=0; nang<(int)(360/linfo->dang); nang++,ang+=linfo->dang){
				srcx = r*cos(ang*RADIAN) + cx;
				srcy = r*sin(ang*RADIAN) + cy;
				srcz = z;
				dstz = z - linfo->zmin;
				dstr = r - linfo->rmin;
				DEBUG2PRINT5("(%f,%f,%f)->(%f,%f) :",srcx,srcy,srcz,dstz,dstr);
				mrcImageDataGetbyAU(in, srcx, srcy, srcz, &data, mrcPixelRePart, mrcPixelHowLinear);
				mrcImageDataGetbyAU(out, dstr, dstz, 0,  &data0, mrcPixelRePart, mrcPixelHowNearest);
				mrcImageDataSetbyAU(out, dstr, dstz, 0,  data+data0, mrcPixelRePart);
				DEBUG2PRINT1("%f \n",data);
			}
		}
	}
	*/
}



