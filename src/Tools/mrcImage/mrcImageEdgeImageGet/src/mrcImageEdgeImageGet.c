/*
# mrcImageEdgeImageGet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageEdgeImageGet
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

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "mrcImage.h"

typedef struct lmrcImageEdgeImageGetInfo {
	int   Size;
	int   numImage;
} lmrcImageEdgeImageGetInfo;

typedef enum lmrcImageEdgeImageGetMode {
	lmrcImageEdgeImageGetModeFour=0,
	lmrcImageEdgeImageGetModeNine=1
} lmrcImageEdgeImageGetMode;

extern void lmrcImageEdgeImageGet(
	mrcImage* in, 
	mrcImage** out, 
	lmrcImageEdgeImageGetInfo* linfo, 
	lmrcImageEdgeImageGetMode mode
	); 

extern void lmrcImageEdgeImageGetFour(
	mrcImage* in, 
	mrcImage** out, 
	lmrcImageEdgeImageGetInfo* linfo, 
	lmrcImageEdgeImageGetMode mode
	); 

extern void lmrcImageEdgeImageGetNine (
	mrcImage* in, 
	mrcImage** out, 
	lmrcImageEdgeImageGetInfo* linfo, 
	lmrcImageEdgeImageGetMode mode
	); 

extern void lmrcImageEdgeImageGetInit(
	mrcImage* in, 
	mrcImage** out, 
	lmrcImageEdgeImageGetInfo* linfo, 
	lmrcImageEdgeImageGetMode mode
	);

int
main(int argc, char* argv[]) 
{
	mrcImageEdgeImageGetInfo info;
	lmrcImageEdgeImageGetInfo linfo;

	mrcImage in;
	mrcImage* out;
	int i;
	char filename[STRING_MAX_LENGTH];

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.Size = info.Size;

	mrcFileRead(&in, info.In, "in main", 0);

	DEBUGPRINT2("%p %p\n", &out, out);
	lmrcImageEdgeImageGet(&in, &out, &linfo, info.mode);
	DEBUGPRINT2("%p %p\n", &out, out);

	DEBUGPRINT1("numImage: %d\n", linfo.numImage);
	DEBUGPRINT1("out: %p\n", out);
	for(i=0; i<linfo.numImage; i++) {
		sprintf(filename, "%s.%03d", info.Out, i);

		DEBUGPRINT2("out[%03d]: %d\n", i, out[i].HeaderMode);
		mrcFileWrite(&(out[i]), filename, "in main", 0);
	}
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode: \n");
	fprintf(stderr, "    %4d: 4 Edge (x-y plane) from Image(0-3)\n", lmrcImageEdgeImageGetModeFour);
	fprintf(stderr, "    %4d: 8 Edge (x-y plane) + centre from Image(0-8)\n", lmrcImageEdgeImageGetModeNine);
}


void 
lmrcImageEdgeImageGet(mrcImage* in, mrcImage** out, lmrcImageEdgeImageGetInfo* linfo, lmrcImageEdgeImageGetMode mode)
{
	DEBUGPRINT1("lmrcImageEdgeImageGet Mode: %d\n", mode);
	switch(mode) {
		case lmrcImageEdgeImageGetModeFour: {
			lmrcImageEdgeImageGetFour(in, out, linfo, mode);
			break;
		}
		case lmrcImageEdgeImageGetModeNine: {
			lmrcImageEdgeImageGetNine(in, out, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode: %d\n", mode);
			exit(EXIT_FAILURE);
		}
	}
}

void
lmrcImageEdgeImageGetInit(mrcImage* in, mrcImage** out, lmrcImageEdgeImageGetInfo* linfo, lmrcImageEdgeImageGetMode mode)
{
	int i;
	mrcImage* pout;

	DEBUGPRINT1("numImage: %d\n", linfo->numImage);
	DEBUGPRINT2("p: %p %p\n", out, *out);
	*out = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo->numImage, "in lmrcImageEdgeImageGetInit");
	DEBUGPRINT2("p: %p %p\n", out, *out);
	pout = *out;
	DEBUGPRINT3("p: out %p *out %p pout %p\n", out, *out, pout);
	for(i=0; i<linfo->numImage; i++) {
		DEBUGPRINT3("p: out %p *out %p pout %p\n", out, *out, pout);
		mrcDefaultHeaderValueSet(&(pout[i]));
		pout[i].HeaderN.x = MIN(in->HeaderN.x, linfo->Size);
		pout[i].HeaderN.y = MIN(in->HeaderN.y, linfo->Size);
		pout[i].HeaderN.z = MIN(in->HeaderN.z, linfo->Size);
		pout[i].HeaderMode = in->HeaderMode;
		DEBUGPRINT1("%d\n", pout[i].HeaderMode);
		DEBUGPRINT4("%d: %d %d %d\n", i, in->HeaderN.x, in->HeaderN.y, in->HeaderN.z);
		DEBUGPRINT4("%d: %d %d %d\n", i, pout[i].HeaderN.x, pout[i].HeaderN.y, pout[i].HeaderN.z);
		mrcInit(&(pout[i]), NULL);
	}
}

void 
lmrcImageEdgeImageGetFour(mrcImage* in, mrcImage** out, lmrcImageEdgeImageGetInfo* linfo, lmrcImageEdgeImageGetMode mode)
{
	mrcImageParaTypeReal srcx, srcy, srcz;
	mrcImageParaTypeReal dstx, dsty, dstz;
	mrcImageParaTypeReal offsetx, offsety, offsetz;
	int i;
	double data;
	mrcImage* pout;

	linfo->numImage = 4;

	lmrcImageEdgeImageGetInit(in, out, linfo, mode); 

	pout = *out;
	DEBUGPRINT("ROI Get \n");
	for(i=0; i<linfo->numImage; i++) {
		DEBUGPRINT2("i: %d p: %p\n", i, &(pout[i]));
	}
	for(i=0; i<linfo->numImage; i++) {
		DEBUGPRINT2("i: %d p: %p\n", i, &(pout[i]));
		offsetx = (i%2)?MAX(in->HeaderN.x - linfo->Size, 0):(0);
		offsety = (i/2)?MAX(in->HeaderN.y - linfo->Size, 0):(0);
		offsetz = MAX(pout[i].HeaderN.z, pout[i].HeaderN.z/2 - linfo->Size/2);

		DEBUGPRINT1("%d\n", out[i]->HeaderMode);
		DEBUGPRINT4("%d: %d %d %d\n", i, pout[i].HeaderN.x, pout[i].HeaderN.y, pout[i].HeaderN.z);

		for(dstz=0; dstz<pout[i].HeaderN.z; dstz++) { 
		for(dsty=0; dsty<pout[i].HeaderN.y; dsty++) {
		for(dstx=0; dstx<pout[i].HeaderN.x; dstx++) {
			srcx = offsetx + dstx;
			srcy = offsety + dsty;
			srcz = offsetz + dstz;
			mrcPixelDataGet(in, srcx, srcy, srcz, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(&(pout[i]), dstx, dsty, dstz, data, mrcPixelRePart); 
		}
		}
		}
	}
}

void 
lmrcImageEdgeImageGetNine(mrcImage* in, mrcImage** out, lmrcImageEdgeImageGetInfo* linfo, lmrcImageEdgeImageGetMode mode)
{
	mrcImageParaTypeReal srcx, srcy, srcz;
	mrcImageParaTypeReal dstx, dsty, dstz;
	mrcImageParaTypeReal offsetx, offsety, offsetz;
	int i;
	double data;
	mrcImage* pout;

	linfo->numImage = 9;

	lmrcImageEdgeImageGetInit(in, out, linfo, mode); 

	pout = *out;
	DEBUGPRINT("ROI Get \n");
	for(i=0; i<linfo->numImage; i++) {
		switch(i%3) {
			case 0:
				offsetx = 0;
				break;
			case 1:
				offsetx = MAX((in->HeaderN.x - linfo->Size)/2, 0); 
				break;
			case 2:	
				offsetx = MAX( in->HeaderN.x - linfo->Size,    0);
				break;
			default:
				offsetx = 0;
				fprintf(stderr, "Something wrong: mod(%d,3)=%d \n", i, i%3);
				break;
		}
		switch(i/3) {
			case 0:
				offsety = 0;
				break;
			case 1:
				offsety = MAX((in->HeaderN.y - linfo->Size)/2, 0); 
				break;
			case 2:
				offsety = MAX( in->HeaderN.y - linfo->Size,    0);
				break;
			default:
				offsety = 0;
				fprintf(stderr, "Something wrong: %d/3=%d\n", i, i/3); 
				break;
		}

		offsetz = MAX(pout[i].HeaderN.z, pout[i].HeaderN.z/2 - linfo->Size/2);

		DEBUGPRINT1("%d\n", pout[i].HeaderMode);
		DEBUGPRINT4("%d: %d %d %d\n", i, pout[i].HeaderN.x, pout[i].HeaderN.y, pout[i].HeaderN.z);

		for(dstz=0; dstz<pout[i].HeaderN.z; dstz++) { 
		for(dsty=0; dsty<pout[i].HeaderN.y; dsty++) {
		for(dstx=0; dstx<pout[i].HeaderN.x; dstx++) {
			srcx = offsetx + dstx;
			srcy = offsety + dsty;
			srcz = offsetz + dstz;
			mrcPixelDataGet(in, srcx, srcy, srcz, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(&(pout[i]), dstx, dsty, dstz, data, mrcPixelRePart); 
		}
		}
		}
	}
}
