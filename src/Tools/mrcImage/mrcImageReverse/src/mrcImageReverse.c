/*
# mrcImageReverse.c  1.1
# The latest update : 11/26/96 at 18:31:03
#
#@(#) mrcImageReverse ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageReverse
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageReverse ver1.1; Date:96/11/26 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

extern void lmrcImageReverse(mrcImage* out,mrcImage* in);
void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageReverseInfo info;
	mrcImage in;
	mrcImage out;


	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	mrcFileRead(&in,   info.In,  "in main", 0);
	lmrcImageReverse(&out,&in);
	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}
void lmrcImageReverse(mrcImage* out,mrcImage* in)
{
    mrcImageParaTypeReal x, y, z;
	double data;
	out->Header = in->Header;
    mrcInit(out, NULL);
	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			for(z=0; z<in->HeaderN.z; z++) {
				mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart,mrcPixelHowNearest);
				mrcPixelDataSet(out, in->HeaderN.x-x-1, y, in->HeaderN.z-z-1, data, mrcPixelRePart);
			}
        }
    }
}
void
additionalUsage()
{
	fprintf(stderr,"y values keep the same.\n");
}
