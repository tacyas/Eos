/*
# raw2mrc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : raw2mrc
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
#include "Memory.h"
#include "mrcImage.h"

typedef struct rawImage {
	long offset;
	int nx;
	int ny;
	int nz;
    long number;
	int dataType;
    void* Image;
} rawImage;

typedef struct lraw2mrcInfo {
	float a;
	int   b;
} lraw2mrcInfo;

typedef enum lraw2mrcMode {
	a=0,
	b=1
} lraw2mrcMode;

void rawImageRead(rawImage* raw, FILE* fpt, int mode);
void lraw2mrc(rawImage* raw, mrcImage* mrc, lraw2mrcInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
    rawImage raw;
    mrcImage mrc;
	raw2mrcInfo info;
	lraw2mrcInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    raw.offset = info.Offset;
    raw.nx = info.Nx;
    raw.ny = info.Ny;
    raw.nz = info.Nz;
    raw.number = raw.nx*raw.ny*raw.nz;
    raw.dataType = info.DataType;

    rawImageRead(&raw, info.fptIn, 0);
    lraw2mrc(&raw, &mrc, linfo, info.mode);
    DEBUGPRINT3("N: %d %d %d\n", mrc.HeaderN.x, mrc.HeaderN.y, mrc.HeaderN.z);    
    mrcFileWrite(&mrc, info.Out, "in main", 0);
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void 
rawImageRead(rawImage* raw, FILE* fpt, int mode)
{
    
    fseek(fpt, raw->offset, SEEK_SET);
    switch(raw->dataType) {
        case 0: {
            raw->Image = memoryAllocate(sizeof(unsigned char)*raw->number, "in rawImageRead");
            fread(raw->Image, sizeof(unsigned char), raw->number, fpt); 
            break;
        }
        case 1: {
            raw->Image = memoryAllocate(sizeof(unsigned short)*raw->number, "in rawImageRead");
            fread(raw->Image, sizeof(unsigned short), raw->number, fpt); 
            break;
        }
        case 2: {
            raw->Image = memoryAllocate(sizeof(float)*raw->number, "in rawImageRead");
            fread(raw->Image, sizeof(float), raw->number, fpt); 
            break;
        }
        case 101: {
            raw->Image = memoryAllocate(sizeof(long int)*raw->number, "in rawImageRead");
            fread(raw->Image, sizeof(long int), raw->number, fpt); 
            break;
        }
        case 102: {
            raw->Image = memoryAllocate(sizeof(double)*raw->number, "in rawImageRead");
            fread(raw->Image, sizeof(double), raw->number, fpt); 
            break;
        }
        default: {
            fprintf(stderr, "Not supported dataType: %d\n", raw->dataType);
            exit(EXIT_FAILURE);
        }
    }
}
    

void 
lraw2mrc(rawImage* raw, mrcImage* out, lraw2mrcInfo linfo, int mode)
{
    int i;
    mrcDefaultHeaderValueSet(out);
    out->HeaderN.x = raw->nx;
    out->HeaderN.y = raw->ny;
    out->HeaderN.z = raw->nz;
    out->HeaderMode = mrcFloatImage;
    mrcInit(out, NULL);
    DEBUGPRINT3("N: %d %d %d\n", out->HeaderN.x, out->HeaderN.y, out->HeaderN.z);    
    switch(raw->dataType) {
        case 0: {
            for(i=0; i<raw->number; i++) {
                out->ImageFloatImage[i] =(float)(((unsigned char*)raw->Image)[i]);
            }
            break;
        }
        case 1: {
            for(i=0; i<raw->number; i++) {
                out->ImageFloatImage[i] =(float)(((unsigned short*)raw->Image)[i]);
            }
            break;
        }
        case 2: {
            for(i=0; i<raw->number; i++) {
                out->ImageFloatImage[i] =(float)(((float*)raw->Image)[i]);
            }
            break;
        }
        case 101: {
            DEBUGPRINT1("sizeof(long int): %d\n", sizeof(long int));
            for(i=0; i<raw->number; i++) {
                out->ImageFloatImage[i] =(float)(((long int*)raw->Image)[i]);
            }
            break;
        }
        case 102: {
            for(i=0; i<raw->number; i++) {
                out->ImageFloatImage[i] =(float)(((double*)raw->Image)[i]);
            }
            break;
        }
        default: {
            fprintf(stderr, "Not supported dataType: %d\n", raw->dataType);
            exit(EXIT_FAILURE);
        }
    }
}
