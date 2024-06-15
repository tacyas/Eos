#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#include "pdbFile.h"

extern void lmrcImageAssignedToTFofPDB(pdbFile* pdbOut, pdbFile* pdbIn, mrcImage* mrc, long mode);

#define MODE_ORIGIN_BIT   (0x00000001L)
#define MODE_POSINEGA_BIT (0x00000010L)

void
main(int argc, char* argv[]) 
{
	mrcImageAssignedToTFofPDBInfo info;
	mrcImage mrc;
	pdbFile  pdbIn;
	pdbFile  pdbOut;
	mrcImageParaTypeReal x, y, z;
	double data;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead(&mrc, info.In, "in mail routine", 0);
	pdbFileRead(info.fptInPDB, &pdbIn);

	if(info.flagLowLevel) {
		for(x=0; x<mrc.HeaderN.x; x++) {	
		for(y=0; y<mrc.HeaderN.y; y++) {	
		for(z=0; z<mrc.HeaderN.z; z++) {	
			mrcPixelDataGet(&mrc, x, y, z, &data, mrcPixelMag, mrcPixelHowNearest); 
			if(data<info.LowLevel) {
				mrcPixelDataSet(&mrc, x, y, z, info.LowLevel, mrcPixelMag);
			}
		}}}
	}
	if(info.flagHighLevel) {
		for(x=0; x<mrc.HeaderN.x; x++) {	
		for(y=0; y<mrc.HeaderN.y; y++) {	
		for(z=0; z<mrc.HeaderN.z; z++) {	
			mrcPixelDataGet(&mrc, x, y, z, &data, mrcPixelMag, mrcPixelHowNearest); 
			if(info.HighLevel<data) {
				mrcPixelDataSet(&mrc, x, y, z, info.HighLevel, mrcPixelMag);
			}
		}}}
	}

	lmrcImageAssignedToTFofPDB(&pdbOut, &pdbIn, &mrc, info.mode);
	pdbFileWrite(info.fptOut, &pdbOut);
}

void
additionalUsage()
{
	fprintf(stderr, ">>> Mode:	\n");
	fprintf(stderr, "\t0: Default.\n");
	fprintf(stderr, "\t1 : Origin is Center  (1) or BottomLeft (0).\n");
	fprintf(stderr, "\t2 : Posi-Nega Reverse (2) or Direct     (0).\n");
}

void
lmrcImageAssignedToTFofPDB(pdbFile* pdbOut, pdbFile* pdbIn, mrcImage* mrc, long mode)
{
	pdbFileParaTypeReal x, y, z;
	double data, sign;
	long flag;

	if(!IsImage(mrc, "in lmrcImageAssignedToTFofPDB", 0)) {
		fprintf(stderr, "Not supported mode of mrcImage\n");
		exit(EXIT_FAILURE);
	}
	switch(mode&MODE_POSINEGA_BIT) {
		case 0: {
			sign=1.0;
			break;
		}
		case 2: {
			sign=-1.0;
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode : %ld\n", mode); 
			exit(EXIT_FAILURE);
			break;
		}
	}
	flag = 0;
	pdbFileTop(pdbIn);
	do {
		if(0==flag) {
			pdbFileNew(pdbOut);
			flag++;
		} else {
			pdbFileAppend(pdbOut);
			flag++;
		}
		pdbFileOneRecordCopy(pdbOut, pdbIn);
		if(pdbFileIsAtom(pdbOut)) {
			pdbFileCoordGet(pdbOut, &x, &y, &z);
			switch(mode&MODE_ORIGIN_BIT) {
				case 0: {
					mrcPixelDataGet(mrc, x/mrc->HeaderLength.x, 
										 y/mrc->HeaderLength.y, 
										 z/mrc->HeaderLength.z, 
										&data, mrcPixelMag, mrcPixelHowNearest);
					break;
				}
				case 1: {
					mrcPixelDataGet(mrc, x/mrc->HeaderLength.x+(mrc->HeaderN.x+1)/2, 
										 y/mrc->HeaderLength.y+(mrc->HeaderN.y+1)/2, 
										 z/mrc->HeaderLength.z, 
										 &data, mrcPixelMag, mrcPixelHowNearest);
					break;
				}
				default: {
					fprintf(stderr, "Not supported Mode: %ld\n", mode);
					exit(EXIT_FAILURE);
					break;
				}
			}
			pdbFileTemperatureFactorSet(pdbOut, (sign*data));
		}
	} while(NULL!=pdbFileNext(pdbIn));
}
