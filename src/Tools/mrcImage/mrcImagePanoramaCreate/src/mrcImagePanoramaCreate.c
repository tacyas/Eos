/*
# mrcImagePanoramaCreate : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImagePanoramaCreate
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
#include "eosString.h"
#include "mrcImage.h"

typedef struct lmrcImagePanoramaCreateInfo {
	/* Input */
	mrcImage* Image;
	mrcImageParaTypeInteger N;
	mrcImageParaTypeRealCoord* Offset;
	mrcImageParaTypeIntegerCoord Size;
	mrcPixelDataHowToGet InterpolationMode;	

	/* Output */
	mrcImage Count;
} lmrcImagePanoramaCreateInfo;
/*
typedef enum lmrcImagePanoramaCreateMode {
	a=0,
	b=1
} lmrcImagePanoramaCreateMode;
*/

extern void lmrcImagePanoramaCreate(mrcImage* out, lmrcImagePanoramaCreateInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImagePanoramaCreateInfo info;
	lmrcImagePanoramaCreateInfo linfo;
	mrcImage out;
	int i;
	char s[1024];

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.N = info.flagIn;
	linfo.Image  = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.N, "in main");
	linfo.Offset = (mrcImageParaTypeRealCoord*)memoryAllocate(sizeof(mrcImageParaTypeRealCoord)*linfo.N, "in main");
	for(i=0; i<linfo.N; i++) {
		mrcFileRead(&(linfo.Image[i]), info.In[i], "in main", 0);
	}
	linfo.Size.x = info.Nx;
	linfo.Size.y = info.Ny;
	linfo.Size.z = info.Nz;
	linfo.InterpolationMode = info.InterpolationMode;

	fseek(info.fptInList, 0L, SEEK_SET);
	i=0;
	while(NULL!=stringGetFromFile(s, "", info.fptInList, stdout, 1)) {
		linfo.Offset[i].x = stringGetNthRealData(s, 2, " ,\t");
		linfo.Offset[i].y = stringGetNthRealData(s, 3, " ,\t");
		linfo.Offset[i].z = stringGetNthRealData(s, 4, " ,\t");
		i++;
	}
	   
	lmrcImagePanoramaCreate(&out, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	if(info.flagCount) {
		mrcFileWrite(&linfo.Count, info.Count, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">>>InputFileList Format\n");
	fprintf(stderr, "FileName OffsetX OffsetY OffsetZ\n");
	fprintf(stderr, ".....\n");
}


void 
lmrcImagePanoramaCreate(mrcImage* out, lmrcImagePanoramaCreateInfo* linfo, int mode)
{
	int i;
	double startx, starty, startz;
	double dx, dy, dz;
	double dstx, dsty, dstz;
	double srcx, srcy, srcz;
	int ix, iy, iz;
	double data, dstdata, count;	

	out->Header = linfo->Image[0].Header;
	out->HeaderN = linfo->Size; 
	mrcInit(out, NULL);

	linfo->Count.Header = out->Header;
	mrcInit(&linfo->Count, NULL);

	for(i=0; i<linfo->N; i++) {
		startx = (int)(linfo->Offset[i].x + 0.5);
		starty = (int)(linfo->Offset[i].y + 0.5);
		startz = (int)(linfo->Offset[i].z + 0.5);
		dx = linfo->Offset[i].x - startx;	
		dy = linfo->Offset[i].y - starty;	
		dz = linfo->Offset[i].z - startz;	
		for(iz=0; iz<linfo->Image[i].HeaderN.z; iz++) {
			dstz = startz + iz;  
			srcz = iz     - dz;
		for(iy=0; iy<linfo->Image[i].HeaderN.y; iy++) {
			dsty = starty + iy;  
			srcy = iy     - dy;
		for(ix=0; ix<linfo->Image[i].HeaderN.x; ix++) {
			dstx = startx + ix;
			srcx = ix     - dx;
			mrcPixelDataGet(&(linfo->Image[i]), srcx, srcy, srcz, &data, mrcPixelRePart, linfo->InterpolationMode);		
			mrcPixelDataGet(out, dstx, dsty, dstz, &dstdata, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&(linfo->Count), dstx, dsty, dstz, &count, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(out, dstx, dsty, dstz, dstdata+data, mrcPixelRePart);
			mrcPixelDataSet(&(linfo->Count), dstx, dsty, dstz, count+1, mrcPixelRePart);
		}
		}
		}
	}


	for(dstz=0; dstz<out->HeaderN.z; dstz++) {
	for(dsty=0; dsty<out->HeaderN.y; dsty++) {
	for(dstx=0; dstx<out->HeaderN.x; dstx++) {
		mrcPixelDataGet(&(linfo->Count), dstx, dsty, dstz, &count, mrcPixelRePart, mrcPixelHowNearest);
		if(0<count) { 
			mrcPixelDataGet(out, dstx, dsty, dstz, &dstdata, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(out, dstx, dsty, dstz, dstdata/count, mrcPixelRePart);
		}
	}
	}
	}
}
