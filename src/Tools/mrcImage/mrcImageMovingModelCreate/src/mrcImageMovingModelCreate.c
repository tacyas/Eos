/*
# mrcImageMovingModelCreate : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageMovingModelCreate
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

typedef struct lmrcImageMovingModelCreateInfo {
    mrcImage template;
	char* OutName;
	FILE* OutList;

    int N;
} lmrcImageMovingModelCreateInfo;

typedef enum lmrcImageMovingModelCreateMode {
	a=0,
	b=1
} lmrcImageMovingModelCreateMode;

void lmrcImageMovingModelCreate(Array* in, lmrcImageMovingModelCreateInfo* linfo, lmrcImageMovingModelCreateMode mode);

int
main(int argc, char* argv[]) 
{
	mrcImageMovingModelCreateInfo info;
	lmrcImageMovingModelCreateInfo linfo;
	lmrcImageMovingModelCreateMode mode;
    mrcImage out;
    Array in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    arrayReadFromFile(info.fptIn, &in, "in main");      
    
    linfo.OutName = info.OutName;
    linfo.OutList = info.fptOut;
    mrcDefaultHeaderValueSet(&linfo.template);
    linfo.template.HeaderN.x = info.Nx; 
    linfo.template.HeaderN.y = info.Ny; 
    linfo.template.HeaderN.z = info.Nz; 
    linfo.template.HeaderLength.x = info.Lx; 
    linfo.template.HeaderLength.y = info.Ly; 
    linfo.template.HeaderLength.z = info.Lz; 
    linfo.template.HeaderMode = mrcFloatImage;
    linfo.N = info.Num;

    lmrcImageMovingModelCreate(&in, &linfo, mode);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "input file type: Array type N:Number of Moving objects\n");
	fprintf(stderr, "2 10 N\n");
	fprintf(stderr, "intensity sigx sigy sigz startx starty startz vx vy vz\n");
}

void 
lmrcImageMovingModelCreate(Array* in, lmrcImageMovingModelCreateInfo* linfo, lmrcImageMovingModelCreateMode mode)
{
    int i, j, k;
    mrcImage tmp;
    double I, sig[3], start[3], v[3], p[3];
    float x, y, z;
    double data, px, py, pz;
    char tmpString[1024];

    for(i=0; i<linfo->N; i++) {
        tmp = linfo->template;
        mrcInit(&tmp, NULL) ;
        for(k=0; k < in->n[1]; k++) { // particle
            I = in->A[0+k*in->n[0]];
            for(j=0; j<3; j++) {
                sig[j]   = in->A[1+j+k*in->n[0]]; 
                start[j] = in->A[4+j+k*in->n[0]]; 
                v[j]     = in->A[7+j+k*in->n[0]]; 
                p[j] = start[j] + i*v[j];
            }
            DEBUGPRINT3("p %f %f %f\n", p[0], p[1], p[2]);
            DEBUGPRINT3("sig %f %f %f\n", sig[0], sig[1], sig[2]);
            for(z=0; z<tmp.HeaderN.z; z++) {
            for(y=0; y<tmp.HeaderN.y; y++) {
            for(x=0; x<tmp.HeaderN.x; x++) {
                mrcPixelDataGet(&tmp, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
                data += I*exp(-SQR(x-p[0])/SQR(sig[0])/2.0-SQR(y-p[1])/SQR(sig[1])/2.0-SQR(z-p[2])/SQR(sig[2])/2.0);
                mrcPixelDataSet(&tmp, x, y, z, data, mrcPixelRePart);
            }
            }
            }
        }
        sprintf(tmpString, linfo->OutName, i);
        mrcFileWrite(&tmp, tmpString, "in main", 0);
        fprintf(linfo->OutList, "%s\n", tmpString);fflush(linfo->OutList);
        mrcImageFree(&tmp, "in main");
    }
}
