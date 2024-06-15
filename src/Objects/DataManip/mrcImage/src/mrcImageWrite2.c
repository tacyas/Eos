/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageWrite2 ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageWrite2 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageWrite2 ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"

mrcStatusType
mrcFileWriteLowerResolution(mrcImage* mrc, char* filename, char* message, long sample, long mode)
{
	mrcImage mrc2;
	mrcImageParaTypeReal  x, y, z;
	double data;

	mrc2.Header = mrc->Header;

	if(sample==0) {
		fprintf(stderr, "Something wrong, sample is zero\n");
		return -1;
	}	
	mrc2.HeaderN.x = (mrc->HeaderN.x + sample - 1)/sample;
	mrc2.HeaderN.y = (mrc->HeaderN.y + sample - 1)/sample;
	mrc2.HeaderN.z = (mrc->HeaderN.z + sample - 1)/sample;
	mrc2.HeaderLength.x = mrc->HeaderLength.x*sample;
	mrc2.HeaderLength.y = mrc->HeaderLength.y*sample;
	mrc2.HeaderLength.z = mrc->HeaderLength.z*sample;
	mrcInit(&mrc2, NULL);
	DEBUGPRINT3("mrc2Header: %d %d %d\n", mrc2.HeaderN.x, mrc2.HeaderN.y, mrc2.HeaderN.z);
	for(x=0; x<mrc2.HeaderN.x; x++) {
		for(y=0; y<mrc2.HeaderN.y; y++) {
			for(z=0; z<mrc2.HeaderN.z; z++) {
				mrcPixelDataGet(mrc, x*sample, y*sample, z*sample, &data, mrcPixelRePart, mrcPixelHowNearest); 
				mrcPixelDataSet(mrc, x, y, z, data, mrcPixelRePart);
			}
		}
	}
	mrcFileWrite(&mrc2, filename, message, mode);
	mrcImageFree(&mrc2, "in mrcFileWriteLowerResolution");
	return 0;
}
