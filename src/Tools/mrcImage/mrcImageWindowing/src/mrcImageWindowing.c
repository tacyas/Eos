#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

#include "lmrcImageWindowing.h"

int
main(int argc, char* argv[]) 
{
	long status;
	lmrcImageWindowingInfo linfo;
	mrcImageWindowingInfo info;
	mrcImage src;
	mrcImage dst;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	if(info.flagWx)	{
		linfo.flagWx = info.flagWx;
		linfo.Wx = info.Wx;
		linfo.flagWxMax = info.flagWxMax;
		linfo.WxMax = info.WxMax;
		linfo.flagWy = info.flagWy;
		linfo.Wy = info.Wy;
		linfo.flagWyMax = info.flagWyMax;
		linfo.WyMax = info.WyMax;
	} else {
		linfo.Wx = info.WX;
		linfo.Wy = info.WY;
	}
	if(info.flagWX) {
		linfo.flagWx = info.flagWX;
		linfo.Wx = info.WX;
	}
	if(info.flagWY) {
		linfo.flagWy = info.flagWY;
		linfo.Wy = info.WY;
	}

	mrcFileRead(&src, info.In, "in main", 0);
	dst.Header = src.Header;
	mrcInit(&dst, NULL);

	lmrcImageWindowing(&dst, &src, &linfo, info.mode);

	mrcFileWrite(&dst, info.Out, "in main", 0);
}

void
additionalUsage()
{
	fprintf(stderr, ">>> Mode\n");
	fprintf(stderr, "    0: If 0<x<0.1*nx or 0.9*nx<x<nx, then cos windowing, else original.\n");
	lmrcImageWindowingModePrint(stderr);
}
