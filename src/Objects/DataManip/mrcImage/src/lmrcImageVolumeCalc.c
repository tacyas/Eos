/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageVolumeCalc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageVolumeCalc
#%Z% Attention
#%Z%
*/
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "nr2.h"
#include "./lmrcImageVolumeCalc.h"

void
lmrcImageVolumeCalcPrint(FILE* fpt, lmrcImageVolumeCalcInfo* linfo,  int mode)
{
	int i;

	for(i=0; i<linfo->nContour; i++) {
		fprintf(fpt, linfo->format, linfo->ContourLevel[i]*100, 
									linfo->Contour[i], 
									linfo->VoxelNumber[i], 
									linfo->VoxelNumberInv[i], 
									linfo->Volume[i]);
		fprintf(fpt, "\n");
	}
}


void
lmrcImageVolumeCalc(mrcImage* mrc, lmrcImageVolumeCalcInfo* linfo, int mode)
{
    mrcImageParaTypeReal x, y, z;
    float* data;
    double tmpdata, vol, scal;
    int i;
    unsigned long n, k, level;;
	double min, max, delta;

	char* format;

    DEBUGPRINT(">>>>>>> Prepare ");

	if(!linfo->flagContourLevel) {
		linfo->nContour = (linfo->MaxVol - linfo->MinVol)/linfo->DeltaVol+1;
		linfo->ContourLevel = (double*) memoryAllocate(sizeof(double)*linfo->nContour, "");
    	for(i=0; i<linfo->nContour; i++) {
			linfo->ContourLevel[i] = linfo->MaxVol - i*linfo->DeltaVol;
		}
	}

	linfo->Contour         = (double*) memoryAllocate(sizeof(double)*linfo->nContour, "");
	linfo->VoxelNumber     = (int*)    memoryAllocate(sizeof(int)   *linfo->nContour, "");
	linfo->VoxelNumberInv  = (int*)    memoryAllocate(sizeof(int)   *linfo->nContour, "");
	linfo->Volume          = (double*) memoryAllocate(sizeof(double)*linfo->nContour, "");

	
    n = mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z;
    data = (float*)memoryAllocate(sizeof(float) * (n + 1), "in lmrcImageVolumeCalc");
    i = 1;
    for(x=0; x<mrc->HeaderN.x; x++) {
        for(y=0; y<mrc->HeaderN.y; y++) {
            for(z=0; z<mrc->HeaderN.z; z++) {
                mrcPixelDataGet(mrc, x, y, z, &(tmpdata), mrcPixelMag, mrcPixelHowNearest);
                data[i] = tmpdata;
                i++;
            }
        }
    }
    if(linfo->flagDelta) {
        mrc->HeaderLength.x = linfo->Delta;
        mrc->HeaderLength.y = linfo->Delta;
        mrc->HeaderLength.z = linfo->Delta;
    }

	/* Unit Volume */
    vol = mrc->HeaderLength.x*mrc->HeaderLength.y*mrc->HeaderLength.z;
    DEBUGPRINT4("%f,%f,%f Vol %f\n", mrc->HeaderLength.x, mrc->HeaderLength.y, mrc->HeaderLength.z, vol);

    DEBUGPRINT("Calc\n");

	/* Volume of Molecules */
    level = ((double)linfo->nMolecule)*linfo->MolecularWeight/linfo->Density*10.0/6.02;

	/* Calcucate Contour Level */
    for(i=0; i<linfo->nContour; i++) {
        if(0==linfo->Inverse) {
            k =     (unsigned int)(((double)level)*linfo->ContourLevel[i]/vol);
        } else {
            k = n - (unsigned int)(((double)level)*linfo->ContourLevel[i]/vol);
       	} 

		linfo->VoxelNumber[i]    = MIN(n, MAX(k,   0));
		linfo->VoxelNumberInv[i] = MIN(n, MAX(n-k, 0));
		linfo->Contour[i]     = nrselect(linfo->VoxelNumber[i], n, data);
		linfo->Volume[i]      = level*linfo->ContourLevel[i];
    }
    
    DEBUGPRINT(">>>>>>End\n");
}

