/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCTFSN ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCTFSN
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCTFSN ver%I%; Date:%D% %Z%";
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
	mrcImage dst, src;
	mrcImageCTFSNInfo info;
	lmrcImageCTFSNInfo linfo;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	linfo.mode = info.mode;
	linfo.deg1 = info.deg1;
	linfo.deg2 = info.deg2;
	linfo.ctf.Cs = info.Cs;
	linfo.ctf.defocus = info.Defocus;
	linfo.ctf.kV = info.kV;
	mrcFileRead(&src, info.In, "in main", 0);
	lmrcImageCTFSN(&dst, &src, &linfo, 0);
	mrcStatDataSet(&dst, 0);
	mrcFileWrite(&dst, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

