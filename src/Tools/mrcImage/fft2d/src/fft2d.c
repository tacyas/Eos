#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"


void
main(int argc, char* argv[]) 
{
	long status;
	fft2dInfo info;
	mrcImage fft;
	mrcImage mrc;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead(&mrc, info.In, "fft2d", 0);
	lfft2d(&fft, &mrc);
	mrcFileWrite(&fft, info.Out, "fft2d", 0);
}

void
additionalUsage()
{
}
