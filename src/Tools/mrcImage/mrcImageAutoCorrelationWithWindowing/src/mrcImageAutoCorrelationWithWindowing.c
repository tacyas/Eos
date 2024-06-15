/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageAutoCorrelationWithWindowing ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageAutoCorrelationWithWindowing
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageAutoCorrelationWithWindowing ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageWindowing.h"

/*
Example:
typedef struct lmrcImageAutoCorrelationWithWindowingInfo {
	float a;
	int   b;
} lmrcImageAutoCorrelationWithWindowingInfo;

typedef enum lmrcImageAutoCorrelationWithWindowingMode {
	a=0,
	b=1
} lmrcImageAutoCorrelationWithWindowingMode;
*/

void
main(int argc, char* argv[]) 
{
	mrcImage mrc;
	mrcImage win;
	mrcImage cor;
	lmrcImageWindowingInfo linfo;
	mrcImageAutoCorrelationWithWindowingInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	if(info.flagWy) {
		linfo.flagWy = 1;
		linfo.Wy = info.Wy;
	}
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&mrc, info.In, "in main", 0);
	win.Header = mrc.Header;
	mrcInit(&win, NULL);
	lmrcImageWindowing(&win, &mrc, &linfo, 1);
	lmrcImageCorrelation(&cor, &mrc, &win, info.mode);

	if(info.flagOutWin) {
		mrcFileWrite(&win, info.OutWin, "in main", 0);
	}
	mrcFileWrite(&cor, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

