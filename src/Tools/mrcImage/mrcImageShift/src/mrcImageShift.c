#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageShiftInfo info;
	mrcImage in;
	mrcImage out;
	mrcImageParaTypeRealCoord shift;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	shift.x = info.xshift;
	shift.y = info.yshift;
	shift.z = info.zshift;
	mrcFileRead(&in, info.In, "in Main", 0);
	DEBUGPRINT("lmrcImageShift\n");
	lmrcImageShift(&out, &in, shift, info.mode);
	mrcFileWrite(&out, info.Out, "in Main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
