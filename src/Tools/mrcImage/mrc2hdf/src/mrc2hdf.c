#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hdf5.h"
#include "mrcImage.h"       
#include "../inc/config.h"

typedef struct lmrc2hdfInfo {
	int32 dimsize[3];
	int32 numbertype;
	int windims[2];
	int dims[2];
	int SDSdims[2];
	void* Image;
} lmrc2hdfInfo;

extern void lmrc2hdf(lmrc2hdfInfo* info, mrcImage* img);

void
main(int argc, char* argv[])
{
    mrcImage img;
	mrc2hdfInfo  info;
	lmrc2hdfInfo lInfo;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
    mrcFileRead(&img, info.In, "from Main Routine", 0);
	lmrc2hdf(&lInfo, &img);
	DFSDsetNT(lInfo.numbertype);	
	DFSDputdata(info.Out, 3, lInfo.dimsize, lInfo.Image);
}
 
void
additionalUsage()
{
}

void 
lmrc2hdf(lmrc2hdfInfo* info, mrcImage* img)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	mrcImage tmp;

	switch(img->HeaderMode) {
		case mrcCharImage: {
			info->numbertype = DFNT_UINT8;
			break;
		}
		case mrcShortImage: {
			info->numbertype = DFNT_UINT16;
			break;
		}
		case mrcFloatImage: {
			info->numbertype = DFNT_FLOAT32;
			break;
		}
		case mrcLongImage: {
			info->numbertype = DFNT_UINT32;
			break;
		}
		case mrcDoubleImage: {
			info->numbertype = DFNT_FLOAT64;
			break;
		}
		default: {
			fprintf(stderr, "Data Mode Not Supported!\n");
			exit(EXIT_FAILURE);
			break;
		}
	}
	tmp.Header = img->Header;
	tmp.HeaderN.x = img->HeaderN.z;
	tmp.HeaderN.y = img->HeaderN.x;
	tmp.HeaderN.z = img->HeaderN.y;
	mrcInit(&tmp, NULL);
	if(tmp.HeaderN.z>0) {
		info->dimsize[0] = img->HeaderN.x;
	} else {
		info->dimsize[0] = 1;
	}
	if(tmp.HeaderN.x>0) {
		info->dimsize[1] = img->HeaderN.y;
	} else {
		info->dimsize[1] = 1;
	}
	if(tmp.HeaderN.y>0) {
		info->dimsize[2] = img->HeaderN.z;
	} else {
		info->dimsize[2] = 1;
	}
	for(x=0; x<img->HeaderN.x; x++) {
		for(y=0; y<img->HeaderN.y; y++) {
			for(z=0; z<img->HeaderN.z; z++) {
				mrcPixelDataGet(img, x, y, z, &data, mrcPixelMag, mrcPixelHowNearest);
				mrcPixelDataSet(&tmp, z, x, y, data, mrcPixelMag);
			}
		}
	}
	info->Image = tmp.Image;
}
