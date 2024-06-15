/*
# mrcImageSeriesInfoPerPixel : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSeriesInfoPerPixel
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
#include "Vector.h"
#include "mrcImage.h"

typedef struct lmrcImageSeriesInfoPerPixelInfo {
    float x;
    float y;
    floatVector p;
} lmrcImageSeriesInfoPerPixelInfo;

typedef enum lmrcImageSeriesInfoPerPixelMode {
	a=0,
	b=1
} lmrcImageSeriesInfoPerPixelMode;

extern void lmrcImageiSeriesInfoPerPixelInfo(lmrcImageSeriesInfoPerPixelInfo* linfo, mrcImage* mrc, int mode);
extern void mrcImageSeriesInfoPerPixelInfoOut(FILE* fpt, lmrcImageSeriesInfoPerPixelInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
    mrcImage mrc;
	mrcImageSeriesInfoPerPixelInfo info;
	lmrcImageSeriesInfoPerPixelInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    linfo.x = info.X;
    linfo.y = info.Y;

    mrcFileRead(&mrc, info.In, "in main", 0);
    
    lmrcImageiSeriesInfoPerPixelInfo(&linfo, &mrc, info.mode);

    mrcImageSeriesInfoPerPixelInfoOut(info.fptOut, linfo, info.mode);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");

}


void 
lmrcImageiSeriesInfoPerPixelInfo(lmrcImageSeriesInfoPerPixelInfo* linfo, mrcImage* mrc, int mode)
{
    int i;
    double data;

    floatVectorInit(&linfo->p, mrc->HeaderN.z);
    for(i=0; i<mrc->HeaderN.z; i++) {
            mrcPixelDataGet(mrc, linfo->x, linfo->y, i, &data, mrcPixelRePart, mrcPixelHowNearest);
            linfo->p.data[i] = data;
    }
}

void 
mrcImageSeriesInfoPerPixelInfoOut(FILE* fpt, lmrcImageSeriesInfoPerPixelInfo linfo, int mode)
{
    int i;

    for(i=0; i<linfo.p.size; i++) {
            fprintf(fpt, "%d %f\n", i, linfo.p.data[i]);
    }
}
