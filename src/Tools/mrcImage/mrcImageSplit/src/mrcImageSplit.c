/*
# mrcImageSplit : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSplit
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageSplit.h"

int
main(int argc, char* argv[]) 
{
	mrcImageSplitInfo info;
	lmrcImageSplitInfo linfo;
	mrcImage in;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	linfo.filename = info.Out;
	linfo.suffix   = info.Suffix;

	linfo.Size.x = info.Width;
	linfo.Size.y = info.Height;
	linfo.Size.z = info.Section;

	if(info.flagWidthA) {
		linfo.Size.x = (int)(info.WidthA/in.HeaderLength.x+0.5);
	}
	if(info.flagHeightA) {
		linfo.Size.y = (int)(info.HeightA/in.HeaderLength.y+0.5);
	}
	if(info.flagSectionA) {
		linfo.Size.z = (int)(info.SectionA/in.HeaderLength.z+0.5);
	}

	lmrcImageSplit(&in, &linfo, info.mode);

	for(i=0; i<linfo.N; i++) {
		if(linfo.FileName[i]!=NULL) {
			mrcFileWrite(&linfo.Out[i], linfo.FileName[i], "in main", 0);
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


