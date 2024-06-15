/*
# mrcImageDivergence : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageDivergence
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

typedef struct lmrcImageDivergenceInfo {
    int dim;
    mrcImage dx;
    mrcImage dy;
    mrcImage dz;     
} lmrcImageDivergenceInfo;

typedef enum lmrcImageDivergenceMode {
	a=0,
	b=1
} lmrcImageDivergenceMode;

extern int lmrcImageDivergence(mrcImage* out, lmrcImageDivergenceInfo* linfo, lmrcImageDivergenceMode mode);

int
main(int argc, char* argv[]) 
{
	mrcImageDivergenceInfo info;
	lmrcImageDivergenceInfo linfo;
    mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    if(info.flagIn) {
        mrcFileRead(&(linfo.dx), info.In, "in main", 0);
        linfo.dim = 1;
    } else if(info.flagIn2x) {
        mrcFileRead(&(linfo.dx), info.In2x, "in main", 0);
        mrcFileRead(&(linfo.dy), info.In2y, "in main", 0);
        linfo.dim = 2;
    } else if(info.flagIn3x) {
        mrcFileRead(&(linfo.dx), info.In3x, "in main", 0);
        mrcFileRead(&(linfo.dy), info.In3y, "in main", 0);
        mrcFileRead(&(linfo.dz), info.In3z, "in main", 0);
        linfo.dim = 3;
    } else {
        fprintf(stderr, "-i or -i2 or -i3 is necessary\n");
        usage(argv[0]);
    }

    
    lmrcImageDivergence(&out, &linfo, info.mode);

    mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


int 
lmrcImageDivergence(mrcImage* out, lmrcImageDivergenceInfo* linfo, lmrcImageDivergenceMode mode)
{
    mrcImageParaTypeReal x, y, z;
    double Axm, Axp, Aym, Ayp, Azm, Azp;
    double div;

    out->Header = linfo->dx.Header;
    mrcInit(out, NULL);

    for(z=0; z<out->HeaderN.z; z++) {
    for(y=0; y<out->HeaderN.y; y++) {
    for(x=0; x<out->HeaderN.x; x++) {
        Axm = Axp = Aym = Ayp = Azm = Azp = 0;
        switch(linfo->dim) {
            case 3:
                mrcPixelDataGet(&(linfo->dz), x, y, z-1, &Azm, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->dz), x, y, z+1, &Azp, mrcPixelRePart, mrcPixelHowNearest);
            case 2:
                mrcPixelDataGet(&(linfo->dy), x, y-1, z, &Aym, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->dy), x, y+1, z, &Ayp, mrcPixelRePart, mrcPixelHowNearest);
            case 1:
                mrcPixelDataGet(&(linfo->dx), x-1, y, z, &Axm, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->dx), x+1, y, z, &Axp, mrcPixelRePart, mrcPixelHowNearest);
                break;
        }
        div = (Axp - Axm)/2.0 + (Ayp - Aym)/2.0 + (Azp - Azm)/2.0;
        mrcPixelDataSet(out, x, y, z, div, mrcPixelRePart);
    }
    }
    }
    return 0;
}
