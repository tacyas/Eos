/*
# mrcImageCylinderSection.c  1.1
# The latest update : 05/21/97 at 19:22:39
#
#@(#) mrcImageCylinderSection ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageCylinderSection
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageCylinderSection ver1.1; Date:97/05/21 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcImageCylinderSection {
	float angmin;
	float angmax;
	float dang;
	float zmin;
	float zmax;
	float dz;
	float rmin;
	float rmax;
	float dr;
} lmrcImageCylinderSection;

int
main(int argc, char* argv[]) 
{
	mrcImageCylinderSectionInfo info;
	lmrcImageCylinderSection linfo;
	static mrcImage out;
	static mrcImage in;
	mrcImageParaTypeReal cx,cy;
	mrcImageParaTypeReal srcx,srcy,srcz;
	mrcImageParaTypeReal dstang,dstz,dstr;
	mrcImageParaTypeReal  r, ang, z;
	mrcImageParaTypeReal nr,nang,nz;
	double data;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.angmin = info.angmin*RADIAN;
	linfo.angmax = info.angmax*RADIAN;
	linfo.dang   = info.dang*RADIAN;
	linfo.zmin   = info.zmin;
	linfo.zmax   = info.zmax;
	linfo.dz     = info.dz;
	linfo.rmin   = info.rmin;
	linfo.rmax   = info.rmax;
	linfo.dr     = info.dr;
		
	out.HeaderN.x = (int) ((linfo.angmax - linfo.angmin)/linfo.dang + 1);
	out.HeaderN.y = (int) ((linfo.zmax   - linfo.zmin  )/linfo.dz   + 1);
	out.HeaderN.z = (int) ((linfo.rmax   - linfo.rmin  )/linfo.dr   + 1);
	out.HeaderLength.x = linfo.dang;
	out.HeaderLength.y = linfo.dz;
	out.HeaderLength.z = linfo.dr;
	out.HeaderStartN.x = 0;
	out.HeaderStartN.y = 0;
	out.HeaderStartN.z = 0;
	out.HeaderMode = mrcFloatImage;
	mrcInit(&out, NULL);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	if(linfo.zmin<in.HeaderStartN.z*in.HeaderLength.z) {
		fprintf(stderr, "zmin(%f)<StartN.z(%d)*Length.z(%f); zmin := StartN.z*Length.z\n", linfo.zmin, in.HeaderStartN.z, in.HeaderLength.z);
		linfo.zmin = in.HeaderStartN.z*in.HeaderLength.z;
	}
	if((in.HeaderStartN.z+in.HeaderN.z)*in.HeaderLength.z<=linfo.zmax) {
		fprintf(stderr, "(StartN.z(%d)+N.z(%d))*Length.z(%f)<=zmax(%f); zmax := (StartN.z+N.z-1)*Length.z\n", 
			in.HeaderStartN.z, in.HeaderN.z, in.HeaderLength.z, linfo.zmax);
		linfo.zmin = (in.HeaderStartN.z+in.HeaderN.z-1)*in.HeaderLength.z;
	}
	if(linfo.rmin<0) {
		fprintf(stderr, "rmin(%d)<0; rmin = 0\n", linfo.rmin);
		linfo.rmin = 0;
	}
	if(MIN(in.HeaderN.x*in.HeaderLength.x/2.0, in.HeaderN.y*in.HeaderLength.y/2.0)<=linfo.rmax){
		fprintf(stderr, "rmax(%f) > x:%f or y:%f\n", linfo.rmax, in.HeaderN.x*in.HeaderLength.x/2.0, in.HeaderN.y*in.HeaderLength.y/2.0);
		linfo.rmax = MIN(in.HeaderN.x*in.HeaderLength.x/2.0, in.HeaderN.y*in.HeaderLength.y/2.0);
	}

	cx = in.HeaderN.x / 2 * in.HeaderLength.x;
	cy = in.HeaderN.y / 2 * in.HeaderLength.y;

	if ( linfo.zmin<0 || linfo.zmax>in.HeaderN.z*in.HeaderLength.z
	  || linfo.rmin<0 || linfo.rmax>cx){ 
	  	fprintf(stderr,"strange range in zmin:%f zmax:%f rmin:%f rmax:%f\n",linfo.zmin,linfo.zmax,linfo.rmin,linfo.rmax);
	  	exit(EXIT_FAILURE);
	}
	DEBUGPRINT2("%f  %f\n",cx,cy);
	for(nang=0,ang=linfo.angmin; nang<out.HeaderN.x; nang++,ang+=linfo.dang){
		for(nz=0,z=linfo.zmin; nz<out.HeaderN.y; nz++,z+=linfo.dz){
			for(nr=0,r=linfo.rmin; nr<out.HeaderN.z; nr++,r+=linfo.dr){
				srcx = r*cos(ang) + cx;
				srcy = r*sin(ang) + cy;
				srcz = z;
				dstang = ang - linfo.angmin;
				dstz = z - linfo.zmin;
				dstr = r - linfo.rmin;
				DEBUGPRINT6("(%f,%f,%f)->(%f,%f,%f) :",srcx,srcy,srcz,dstang,dstz,dstr); 
				mrcImageDataGetbyAU(&in, srcx, srcy, srcz, &data, mrcPixelRePart, mrcPixelHowLinear);
				if (info.Weight){
					data *= r;
				}
				mrcImageDataSetbyAU(&out, dstang, dstz, dstr,  data, mrcPixelRePart);
				/* DEBUGPRINT1("%f \n",data); */
			}/* r */
		}/* z */
	}/* ang */

	out.HeaderLength.x = linfo.dang*DEGREE;
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Format Change\n");
	fprintf(stderr, "x --> ang\n");
	fprintf(stderr, "y --> z\n");
	fprintf(stderr, "z --> r\n");
}
