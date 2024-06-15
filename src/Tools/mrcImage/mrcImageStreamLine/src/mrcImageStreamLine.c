/*
# mrcImageStreamLine : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageStreamLine
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
#include "Memory.h"

typedef struct lmrcImageStreamLineInfo {
    // in
    int dim;
	mrcImage Vx;
	mrcImage Vy;
	mrcImage Vz;
    int numFrame;
    double dt;
    //
    int numPoints;
    // Out
    mrcImageParaTypeRealCoord** streamLineA;  
    mrcImageParaTypeRealCoord** streamLineP;  
} lmrcImageStreamLineInfo;

typedef enum lmrcImageStreamLineMode {
	a=0,
	b=1
} lmrcImageStreamLineMode;


extern int lmrcImageStreamLine(lmrcImageStreamLineInfo* linfo, lmrcImageStreamLineMode mode);
extern int streamLinesOutput(FILE* fpt, mrcImageParaTypeRealCoord** streams, int num, int frame, int mode);
extern int streamLinesOutputInBILD(FILE* fpt, mrcImageParaTypeRealCoord** streams, int num, int frame, int mode);
extern int streamLineOutput(FILE* fpt, mrcImageParaTypeRealCoord* stream, int frame, int mode);
extern int streamLineOutputInBILD(FILE* fpt, mrcImageParaTypeRealCoord* stream, int frame, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageStreamLineInfo info;
	lmrcImageStreamLineInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    // Input
    linfo.numFrame = info.NumFrame;
    linfo.dt = info.dt;

    if(info.flagIn2x) {
        mrcFileRead(&(linfo.Vx), info.In2x, "in main", 0);
        mrcFileRead(&(linfo.Vy), info.In2y, "in main", 0);
        linfo.dim = 2;
    } else if(info.flagIn3x) {
        mrcFileRead(&(linfo.Vx), info.In3x, "in main", 0);
        mrcFileRead(&(linfo.Vy), info.In3y, "in main", 0);
        mrcFileRead(&(linfo.Vz), info.In3z, "in main", 0);
        linfo.dim = 3;
    } else {
        fprintf(stderr, "-i2 or -i3 is necessary\n");
        usage(argv[0]);
    }

    // Calc
    lmrcImageStreamLine(&linfo, info.mode);

    // Output
    if(info.flagOut) {
        streamLinesOutput(info.fptOut, linfo.streamLineA, linfo.numPoints, linfo.numFrame, info.mode);
    }
    if(info.flagOutPixel) {
        streamLinesOutput(info.fptOutPixel, linfo.streamLineP, linfo.numPoints, linfo.numFrame, info.mode);
    }
    if(info.flagOutBILD) {
        streamLinesOutputInBILD(info.fptOutBILD, linfo.streamLineA, linfo.numPoints, linfo.numFrame, info.mode);
    }
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

int
lmrcImageStreamLine(lmrcImageStreamLineInfo* linfo, lmrcImageStreamLineMode mode)
{
    int i;
    int it;
    mrcImageParaTypeReal x, y, z;
    mrcImageParaTypeReal cx, cy, cz;
    mrcImageParaTypeReal currentx, currenty, currentz;
    mrcImage tmp;
    double vx, vy, vz;

    tmp = linfo->Vx;

    linfo->numPoints = tmp.HeaderN.x*tmp.HeaderN.y*tmp.HeaderN.z;

    linfo->streamLineA = (mrcImageParaTypeRealCoord**)memoryAllocate(sizeof(mrcImageParaTypeRealCoord*)*linfo->numPoints, "in lmrcImageStreamLine");
    linfo->streamLineP = (mrcImageParaTypeRealCoord**)memoryAllocate(sizeof(mrcImageParaTypeRealCoord*)*linfo->numPoints, "in lmrcImageStreamLine");
    for(i=0; i<linfo->numPoints; i++) {
        linfo->streamLineA[i] = (mrcImageParaTypeRealCoord*)memoryAllocate(sizeof(mrcImageParaTypeRealCoord)*linfo->numFrame, "in lmrcImageStreamLine");
        linfo->streamLineP[i] = (mrcImageParaTypeRealCoord*)memoryAllocate(sizeof(mrcImageParaTypeRealCoord)*linfo->numFrame, "in lmrcImageStreamLine");
    }

    i = 0;
    for(z=0; z<tmp.HeaderN.z; z++) {
    for(y=0; y<tmp.HeaderN.y; y++) {
    for(x=0; x<tmp.HeaderN.x; x++) {
        linfo->streamLineP[i][0].x = x;
        linfo->streamLineP[i][0].y = y;
        linfo->streamLineP[i][0].z = z;
        linfo->streamLineA[i][0].x = (x + tmp.HeaderStartN.x)*tmp.HeaderLength.x;
        linfo->streamLineA[i][0].y = (y + tmp.HeaderStartN.y)*tmp.HeaderLength.y;
        linfo->streamLineA[i][0].z = (z + tmp.HeaderStartN.z)*tmp.HeaderLength.z;
        cx = x;
        cy = y;
        cz = z;
        for(it=1; it<linfo->numFrame; it++) {
            mrcPixelDataGet(&(linfo->Vx), cx, cy, cz, &vx,  mrcPixelRePart, mrcPixelHowCubicConv);
            mrcPixelDataGet(&(linfo->Vy), cx, cy, cz, &vy,  mrcPixelRePart, mrcPixelHowCubicConv);
            switch(linfo->dim) {
                case 2: 
                    vz = 0;
                    break;
                case 3:
                    mrcPixelDataGet(&(linfo->Vz), cx, cy, cz, &vz,  mrcPixelRePart, mrcPixelHowCubicConv);
                    break;
                default: 
                    fprintf(stderr, "Not supported dim: %d\n", linfo->dim);
                    exit(EXIT_FAILURE);
            }
            cx += vx*linfo->dt;
            cy += vy*linfo->dt;
            cz += vz*linfo->dt;
            linfo->streamLineP[i][it].x = cx;
            linfo->streamLineP[i][it].y = cy;
            linfo->streamLineP[i][it].z = cz;
            linfo->streamLineA[i][it].x = (cx + tmp.HeaderStartN.x)*tmp.HeaderLength.x;
            linfo->streamLineA[i][it].y = (cy + tmp.HeaderStartN.y)*tmp.HeaderLength.y;
            linfo->streamLineA[i][it].z = (cz + tmp.HeaderStartN.z)*tmp.HeaderLength.z;
        }
        i++;
    }
    }
    }

    return 0;
}

int
streamLinesOutput(FILE* fpt, mrcImageParaTypeRealCoord** streams, int num, int frame, int mode)
{
    int i;

    for(i=0; i<num; i++) {
        streamLineOutput(fpt, streams[i], frame, mode);
    }
    return 0;
}

int
streamLinesOutputInBILD(FILE* fpt, mrcImageParaTypeRealCoord** streams, int num, int frame, int mode)
{
    int i;

    for(i=0; i<num; i++) {
        streamLineOutputInBILD(fpt, streams[i], frame, mode);
    }

    return 0;
}

int
streamLineOutput(FILE* fpt, mrcImageParaTypeRealCoord* stream, int frame, int mode) 
{
    int i;
    for(i=0; i<frame; i++) {
        fprintf(fpt, "%f %f %f ", stream[i].x, stream[i].y, stream[i].z);
    }
    fprintf(fpt, "\n");

    return 0;
}

static int 
color(double* r, double* g, double* b, int i, int max)
{
    int half;
    
    half = max/2;
    if(i<half) {
        *b = - 1.0/half*i + 1.0;
        *g =   1.0/half*i;
        *r =   0;
    } else {
        *b =  0;
        *g =   -1.0/half*i +  2;
        *r =   1.0/half*i - 1;
    }
    return 0;
}

int
streamLineOutputInBILD(FILE* fpt, mrcImageParaTypeRealCoord* stream, int frame, int mode) 
{
    int i;
    double r, g, b;

    for(i=0; i<frame; i++) {
        if((int)((double)i/frame*5)==(int)(i*5/frame)) { 
            color(&r, &g, &b, i, frame);        
        }
        fprintf(fpt, ".color %f %f %f\n", r, g, b);
        if(0==i) {
            fprintf(fpt, ".m ");
        } else {
            fprintf(fpt, ".d ");
        }
        fprintf(fpt, "%f %f %f\n", stream[i].x, stream[i].y, stream[i].z);
    }
    return 0;
}


