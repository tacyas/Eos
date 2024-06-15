#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define UNDEBUG

#include <gsl/gsl_math.h>
#include "genUtil.h"
#include "mrcImage.h"
#include "Memory.h"
#include "lmrcImagePad.h"

int
main(int argc, char* argv[]) 
{
	mrcImagePadInfo info;
	lmrcImagePadInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	linfo.Value  = info.Value;
	linfo.ExpectedValue = info.ExpectedValue;
	linfo.flagExpectedValue = info.flagExpectedValue;
	mrcFileRead(&in, info.In, "in main", 0);

	if(info.flagHeight) {
		linfo.Height = info.Height;
	} else {
		linfo.Height = in.HeaderN.y;
	}
	if(info.flagWidth) {
		linfo.Width = info.Width;
	} else {
		linfo.Width = in.HeaderN.x;
	}
	linfo.Value  = info.Value;
	linfo.AWSize = info.AvgWnd;
	linfo.AWMin  = info.AWMin;
	linfo.AWMax  = info.AWMax;
	linfo.TiltAxisAngle = info.TiltAxisAngle*RADIAN;
	linfo.TiltAngle = info.TiltAngle*RADIAN;

	lmrcImagePad(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Mode -----\n");
	lmrcImagePadModePrint(stderr);
}

