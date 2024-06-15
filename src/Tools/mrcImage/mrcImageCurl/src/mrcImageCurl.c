/*
# mrcImageCurl : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageCurl
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

typedef struct lmrcImageCurlInfo {
    // Input
    int dim;
	mrcImage Ax;
	mrcImage Ay;
	mrcImage Az;
    // Output
    mrcImage Curlx;
    mrcImage Curly;
    mrcImage Curlz;
} lmrcImageCurlInfo;

typedef enum lmrcImageCurlMode {
	a=0,
	b=1
} lmrcImageCurlMode;

extern int lmrcImageCurl(mrcImage* out, lmrcImageCurlInfo* linfo, lmrcImageCurlMode mode);

int
main(int argc, char* argv[]) 
{
	mrcImageCurlInfo info;
	lmrcImageCurlInfo linfo;
    mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    if(info.flagIn2x) {
        mrcFileRead(&(linfo.Ax), info.In2x, "in main", 0);
        mrcFileRead(&(linfo.Ay), info.In2y, "in main", 0);
        linfo.dim = 2;
    } else if(info.flagIn3x) {
        mrcFileRead(&(linfo.Ax), info.In3x, "in main", 0);
        mrcFileRead(&(linfo.Ay), info.In3y, "in main", 0);
        mrcFileRead(&(linfo.Az), info.In3z, "in main", 0);
        linfo.dim = 3;
    } else {
        fprintf(stderr, "-i2 or -i3 is necessary\n");
        usage(argv[0]);
    }

    lmrcImageCurl(&out, &linfo, info.mode);

    mrcFileWrite(&out, info.Out, "in main", 0);

    if(info.flagOut3x) {
        mrcFileWrite(&(linfo.Curlx), info.Out3x, "in main", 0);
        mrcFileWrite(&(linfo.Curly), info.Out3y, "in main", 0);
        mrcFileWrite(&(linfo.Curlz), info.Out3z, "in main", 0);
    }
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


int 
lmrcImageCurl(mrcImage* out, lmrcImageCurlInfo* linfo, lmrcImageCurlMode mode)
{
    mrcImageParaTypeReal x, y, z;
    double Axm, Axp, Aym, Ayp, Azm, Azp;
    double curlx, curly, curlz, curl;

    linfo->Curlx.Header = linfo->Ax.Header;
    linfo->Curly.Header = linfo->Ax.Header;
    linfo->Curlz.Header = linfo->Ax.Header;
    out->Header = linfo->Ax.Header;

    mrcInit(&(linfo->Curlx), NULL);
    mrcInit(&(linfo->Curly), NULL);
    mrcInit(&(linfo->Curlz), NULL);
    mrcInit(out, NULL);

    DEBUGPRINT1("dim: %d\n", linfo->dim);
    for(z=0; z<linfo->Ax.HeaderN.z; z++) {
    for(y=0; y<linfo->Ax.HeaderN.y; y++) {
    for(x=0; x<linfo->Ax.HeaderN.x; x++) {
        curlx = curly = curlz = curl = 0;
        switch(linfo->dim) {
            case 2:
                mrcPixelDataGet(&(linfo->Ax), x, y-1, z, &Axm, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Ax), x, y+1, z, &Axp, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Ay), x-1, y, z, &Aym, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Ay), x+1, y, z, &Ayp, mrcPixelRePart, mrcPixelHowNearest);
                curlz = (Ayp - Aym)/2.0 - (Axp - Axm)/2.0; 
                curl  = curlz;
                break;
            case 3:
                mrcPixelDataGet(&(linfo->Ax), x, y-1, z, &Axm, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Ax), x, y+1, z, &Axp, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Ay), x-1, y, z, &Aym, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Ay), x+1, y, z, &Ayp, mrcPixelRePart, mrcPixelHowNearest);
                curlz = (Ayp - Aym)/2.0 - (Axp - Axm)/2.0; 

                mrcPixelDataGet(&(linfo->Ay), x, y, z-1, &Aym, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Ay), x, y, z+1, &Ayp, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Az), x, y-1, z, &Azm, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Az), x, y+1, z, &Azp, mrcPixelRePart, mrcPixelHowNearest);
                curlx = (Azp - Azm)/2.0 - (Ayp - Aym)/2.0; 

                mrcPixelDataGet(&(linfo->Az), x-1, y, z, &Azm, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Az), x+1, y, z, &Azp, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Ax), x, y, z-1, &Axm, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(linfo->Ax), x, y, z+1, &Axp, mrcPixelRePart, mrcPixelHowNearest);
                curly = (Axp - Axm)/2.0 - (Azp - Azm)/2.0; 
                //DEBUGPRINT5("%f %f %f %f %f\n", x, y, z, Azm, Azp);
                curl = sqrt(curlx*curlx + curly*curly + curlz*curlz);
                break;
            default:
                fprintf(stderr, "Not supoorted dimension: %d\n", linfo->dim);
                break;
        }
        //DEBUGPRINT6("%f %f %f %f %f %f\n", x, y, z, curlx, curly, curlz);
        //DEBUGPRINT4("%f %f %f %f f\n", x, y, z, curl);
        mrcPixelDataSet(&(linfo->Curlx), x, y, z, curlx, mrcPixelRePart);
        mrcPixelDataSet(&(linfo->Curly), x, y, z, curly, mrcPixelRePart);
        mrcPixelDataSet(&(linfo->Curlz), x, y, z, curlz, mrcPixelRePart);
        mrcPixelDataSet(out, x, y, z, curl, mrcPixelRePart);
    }
    }
    }
    return 0;   
}
