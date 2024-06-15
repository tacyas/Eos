/*
# mrc2ascii : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrc2ascii
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

/*
Example:
typedef struct lmrc2asciiInfo {
	float a;
	int   b;
} lmrc2asciiInfo;

typedef enum lmrc2asciiMode {
	a=0,
	b=1
} lmrc2asciiMode;
*/

extern void lmrc2ascii(FILE* fpt, mrcImage* in, int mode);
int
main(int argc, char* argv[]) 
{
    mrcImage in;
	mrc2asciiInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    mrcFileRead(&in, info.In, "in main", 0);

    lmrc2ascii(info.fptOut, &in, info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m \n");
	fprintf(stderr, " 0: A\n");
	fprintf(stderr, " 1: nm\n");
	fprintf(stderr, " +16: Length is Sampling x N\n");
	fprintf(stderr, " +32: Use start\n");
	fprintf(stderr, " +64: Integer\n");
}


void 
lmrc2ascii(FILE* fpt, mrcImage* in, int mode)
{
    float x, y, z;
    int ix, iy, iz;
    float offsetx, offsety, offsetz;
    float lx, ly, lz;
    double data;

    if(mode&0x10) {
        lx = in->HeaderLength.x/in->HeaderN.x;
        ly = in->HeaderLength.y/in->HeaderN.y;
        lz = in->HeaderLength.z/in->HeaderN.z;
    } else {
        lx = in->HeaderLength.x;
        ly = in->HeaderLength.y;
        lz = in->HeaderLength.z;
    }
    if(mode&0x1) {
        lx /=10;
        ly /=10;
        lz /=10;
    }
    if(mode&0x20) {
        offsetx = in->HeaderStartN.x*lx;
        offsety = in->HeaderStartN.y*ly;
        offsetz = in->HeaderStartN.z*lz;
    } else {
        offsetx = 0;
        offsety = 0;
        offsetz = 0;
    }

    for(iz=0; iz<in->HeaderN.z; iz++) {
        z = iz*lz + offsetz;
    for(iy=0; iy<in->HeaderN.y; iy++) {
        y = iy*ly + offsety;
    for(ix=0; ix<in->HeaderN.x; ix++) {
        x = ix*lx + offsetx;
        mrcPixelDataGet(in, ix, iy, iz, &data, mrcPixelRePart, mrcPixelHowNearest);
        if(0x40&mode) {
            fprintf(fpt, "%10d %10d %10d %10d\n", (int)x, (int)y, (int)z, (int)data);
        } else {
            fprintf(fpt, "%15.6f %15.6f %15.6f %15.6f\n", x, y, z, data);
        }
    }
    }
    }

}
