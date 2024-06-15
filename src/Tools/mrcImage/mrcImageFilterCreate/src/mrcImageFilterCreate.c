/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageFilterCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageFilterCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageFilterCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageFilterCreate.h"


int
main(int argc, char* argv[]) 
{
	mrcImageFilterCreateInfo info;
	lmrcImageFilterCreateInfo linfo;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.N.x = info.Nx;
	linfo.N.y = info.Ny;
	linfo.N.z = info.Nz;
	linfo.Size.x = info.Sx;
	linfo.Size.y = info.Sy;
	linfo.Size.z = info.Sz;
	linfo.shape  = info.Mode;
	linfo.outputMode = info.mode;
	lmrcImageFilterInfoFileRead(info.fptIn, &linfo, 0); 
	if(info.verbose) {
		lmrcImageFilterInfoPrint(stdout, linfo, 0); 
	}
	lmrcImageFilterCreate(&out, linfo, 0); 
	if(info.flagOut) {
		mrcFileWrite(&out, info.Out, "in main", 0);	
	} else {
		fwrite(&(out.Header.Cont), MRC_HEADER, 1, info.fptOut);
		fwrite(out.Image, 1, out.BytePerImage, info.fptOut);	
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">>>> Input file Format n");
	lmrcImageFilterInfoFileFormat(stderr, 0);
}


