/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% moi2mrc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : moi2mrc
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%moi2mrc ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "File.h"
#include "eosString.h"
#include "mrcImage.h"

typedef int            MedOpticsInteger;
typedef float          MedOpticsReal;
typedef short          MedOpticsImageInteger;
#define MedOpticsCCDPixelSize (24)

typedef struct MedOpticsScan {
	MedOpticsInteger prescan;
	MedOpticsInteger underscan;
	MedOpticsInteger origin;
	MedOpticsInteger read;
	MedOpticsInteger postscan;
	MedOpticsInteger overscan;
	MedOpticsInteger bin;
} MedOpticsScan;

typedef struct MedOpticsCameraParam {
	MedOpticsScan ser; 
	MedOpticsScan par; 
	MedOpticsInteger gain;
	MedOpticsInteger mpp;
	MedOpticsInteger openDelay;
	MedOpticsInteger closeDelay;
	MedOpticsInteger expTime;
	MedOpticsInteger clears;
	MedOpticsInteger cclear;
	MedOpticsInteger frame;
	MedOpticsInteger parShift;
	MedOpticsInteger numImages;
	MedOpticsInteger imDelay;
	MedOpticsInteger expInc;
	MedOpticsInteger crab;
	MedOpticsInteger offset;
	MedOpticsInteger setpointTemp;
	MedOpticsInteger spec3;
	MedOpticsInteger spec2;
	MedOpticsInteger spec1;
} MedOpticsCameraParam;

typedef struct MedOpticsROI {
	MedOpticsInteger x;
	MedOpticsInteger y;
	MedOpticsInteger xsz;
	MedOpticsInteger ysz;
} MedOpticsROI;

typedef struct MedOpticsLabels {
	char* name[4];
	char* comment[4];
	char* filter[4];
	char* lens[4];
	char* aperture[4];
	char* history[4];
} MedOpticsLabels;

typedef struct MedOpticsHeader {
	char* title;
	char* vers;
	MedOpticsCameraParam params;
	MedOpticsInteger serDim;
	MedOpticsInteger parDim;
	MedOpticsInteger Shutter;
	char* startTime;
	char* endTime;
	MedOpticsInteger Temperature;
	char* type;
	MedOpticsInteger numMean;
	MedOpticsInteger exclude;
	MedOpticsLabels  labels;
	MedOpticsInteger min;
	MedOpticsInteger max;
	MedOpticsReal    mean;
	MedOpticsReal    stdev;
	MedOpticsROI     roi;
	MedOpticsInteger wmin;
	MedOpticsInteger wmax;
} MedOpticsHeader;

typedef struct MedOpticsImage {
	MedOpticsHeader        Header;
	MedOpticsImageInteger* Image;
} MedOpticsImage;

typedef struct lmoi2mrcInfo {
	mrcImageParaTypeReal ADUperElectron;
	mrcImageParaTypeReal Magnification;
} lmoi2mrcInfo;

extern void MedOpticsImageFileRead(MedOpticsImage* moi, char* filename, int mode);
extern void MedOpticsImageHeaderPrint(FILE* fpt, MedOpticsHeader* moi, int mode);
extern void lmoi2mrc(MedOpticsImage* moi, mrcImage*  mrc, lmoi2mrcInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	MedOpticsImage moi;
	mrcImage       mrc;
	moi2mrcInfo    info;
	lmoi2mrcInfo   linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.ADUperElectron = info.ADUperE;
	linfo.Magnification  = info.Mag*info.Mag2*1000;

	DEBUGPRINT("Program Start\n");
	MedOpticsImageFileRead(&moi, info.In, 0); 
	
	switch(info.Info) {
		case 1: {
			MedOpticsImageHeaderPrint(stdout, &(moi.Header), 0); 
			break;
		}
		default: {
			break;
		}
	}
	
	lmoi2mrc(&moi, &mrc, linfo, info.mode);

	if(info.flagOut) {
		mrcFileWrite(&mrc, info.Out, "in main", 0);	
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">>>> -info Integer\n");
	fprintf(stderr, " 1: All Header Info List \n");
}


void 
lmoi2mrc(MedOpticsImage* moi, mrcImage*  mrc, lmoi2mrcInfo linfo, int mode)
{
	mrcDefaultHeaderValueSet(mrc);
	mrc->HeaderN.x = moi->Header.serDim;	
	mrc->HeaderN.y = moi->Header.parDim;	
	mrc->HeaderN.z = 1;	
	mrc->HeaderMode = mode;
	mrc->HeaderLength.x = MedOpticsCCDPixelSize*10000/linfo.Magnification;
	mrc->HeaderLength.y = mrc->HeaderLength.x; 
	mrc->HeaderLength.z = mrc->HeaderLength.x;
	mrcInit(mrc, NULL);

	switch(mode) {
		case mrcCharImage: {
			int n = mrc->HeaderN.x*mrc->HeaderN.y;
			int i;
			int count;
			double sum  = 0;
			double sum2 = 0;  
			double mean;
			double stdev;
			double stdev3;
			
			fprintf(stderr, "mean+-3 sd\n");
			count = 0;
			for(i=0; i<n; i++) {
				if(0<=moi->Image[i]) {
					sum  +=     ((double)moi->Image[i]);
					sum2 +=  SQR((double)moi->Image[i]);
					count++;
				}
			}
			mean  = sum/count;
			stdev = sqrt(sum2/count - mean*mean);
			stdev3 = stdev*3;

			for(i=0; i<n; i++) {
				if(moi->Image[i] <= mean - stdev3) {
					mrc->ImageCharImage[i] = 0;
				} else if(moi->Image[i] >= mean + stdev3) {
					mrc->ImageCharImage[i] = 255;
				} else {
					mrc->ImageCharImage[i] =  (((double)moi->Image[i]) - mean)/stdev3*127 + 127;
				}
			}
			break;
		}
		case mrcShortImage: {
			int i;
			int n = mrc->HeaderN.x*mrc->HeaderN.y;

			fprintf(stderr, "Direct(Positive only)\n");
			for(i=0; i<n; i++) {
				if(moi->Image[i] < 0) {
					mrc->ImageShortImage[i] = 0;	
				} else {
					mrc->ImageShortImage[i] = moi->Image[i];
				}
#ifdef DEBUG
				if(i%2048==1024) {
						fprintf(stderr, "%d %d\n", mrc->ImageShortImage[i], moi->Image[i]);
				}
#endif
			}
			break;
		}	
		case mrcFloatImage: {
			int n = mrc->HeaderN.x*mrc->HeaderN.y;
			int i;

			fprintf(stderr, "Electon Number\n");
			for(i=0; i<n; i++) {
				if(moi->Image[i] < 0) {
					mrc->ImageFloatImage[i] = 0;
				} else {
					mrc->ImageFloatImage[i] = ((double)moi->Image[i])/linfo.ADUperElectron;
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported  mode in lmoi2mrc: %d\n", mode);
			exit(EXIT_FAILURE);
		}
	}
}

void
MedOpticsImageFileReadScan(MedOpticsScan* scan, FILE* fpt, int mode)
{
	fread(scan, sizeof(MedOpticsInteger), 7, fpt);
#ifdef M68
	memoryByteSwap(scan, sizeof(MedOpticsInteger), 7);
#endif
}

void
MedOpticsImageScanPrint(FILE* fpt, MedOpticsScan* scan, int mode)
{
	fprintf(fpt, "Scan ----\n");		
	fprintf(fpt, "prescan:   %d\n", scan->prescan);
	fprintf(fpt, "underscan: %d\n", scan->underscan);
	fprintf(fpt, "origin:    %d\n", scan->origin);
	fprintf(fpt, "read:      %d\n", scan->read);
	fprintf(fpt, "postscan:  %d\n", scan->postscan);
	fprintf(fpt, "overscan:  %d\n", scan->overscan);
	fprintf(fpt, "bin:       %d\n", scan->bin);
}

void
MedOpticsImageFileReadCameraParam(MedOpticsCameraParam* cam, FILE* fpt, int mode)
{
	MedOpticsImageFileReadScan(&(cam->ser), fpt, mode); 
	MedOpticsImageFileReadScan(&(cam->par), fpt, mode); 
	fread(&(cam->gain), sizeof(MedOpticsInteger), 18, fpt);
#ifdef M68
	memoryByteSwap(&(cam->gain), sizeof(MedOpticsInteger), 18);
#endif
}

void 
MedOpticsImageCameraParamPrint(FILE* fpt, MedOpticsCameraParam* cam, int mode)
{
	fprintf(fpt, "Camera Parameters ----\n");
	fprintf(fpt, "---- Serial ");
	MedOpticsImageScanPrint(fpt, &(cam->ser), mode);
	fprintf(fpt, "---- Parallel ");
	MedOpticsImageScanPrint(fpt, &(cam->par), mode);
	fprintf(fpt, "gain:       %d\n", cam->gain);
	fprintf(fpt, "mpp:        %d\n", cam->mpp);
	fprintf(fpt, "openDelay:  %d\n", cam->openDelay);
	fprintf(fpt, "closeDelay: %d\n", cam->closeDelay);
	fprintf(fpt, "expTime:    %d\n", cam->expTime);
	fprintf(fpt, "clears:     %d\n", cam->clears);
	fprintf(fpt, "cclear:     %d\n", cam->cclear);
	fprintf(fpt, "frame:      %d\n", cam->frame);
	fprintf(fpt, "parShift:   %d\n", cam->parShift);
	fprintf(fpt, "numImages:  %d\n", cam->numImages);
	fprintf(fpt, "imDelay:    %d\n", cam->imDelay);
	fprintf(fpt, "expInc:     %d\n", cam->expInc);
	fprintf(fpt, "crab:       %d\n", cam->crab);
	fprintf(fpt, "offset:     %d\n", cam->offset);
	fprintf(fpt, "setTemp:    %d\n", cam->setpointTemp);
	fprintf(fpt, "spec3:      %d\n", cam->spec3);
	fprintf(fpt, "spec2:      %d\n", cam->spec2);
	fprintf(fpt, "spec1:      %d\n", cam->spec1);
}

void
MedOpticsImageFileReadROI(MedOpticsROI* roi, FILE* fpt, int mode)
{
	fread(&(roi->x), sizeof(MedOpticsInteger), 4, fpt);
#ifdef M68
	memoryByteSwap(&(roi->x), sizeof(MedOpticsInteger), 4);
#endif
}

void
MedOpticsImageROIPrint(FILE* fpt, MedOpticsROI* roi,  int mode)
{
	fprintf(fpt, "ROI ----\n");
	fprintf(fpt, "x:      %d\n", roi->x);
	fprintf(fpt, "y:      %d\n", roi->y);
	fprintf(fpt, "xsz:    %d\n", roi->xsz);
	fprintf(fpt, "ysz:    %d\n", roi->ysz);
}

void
MedOpticsImageFileReadLabels(MedOpticsLabels* labels, FILE* fpt, int mode)
{
	char s[1024];
	int i;
	
	for(i=0; i<4; i++) {
		stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); labels->name[i] = stringDuplicate(s);  
	}
	for(i=0; i<4; i++) {
		stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); labels->comment[i] = stringDuplicate(s);  
	}
	for(i=0; i<4; i++) {
		stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); labels->filter[i] = stringDuplicate(s);  
	}
	for(i=0; i<4; i++) {
		stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); labels->lens[i] = stringDuplicate(s);  
	}
	for(i=0; i<4; i++) {
		stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); labels->aperture[i] = stringDuplicate(s);  
	}
	for(i=0; i<4; i++) {
		stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); labels->history[i] = stringDuplicate(s);  
	}
}

void
MedOpticsImageLabelsPrint(FILE* fpt, MedOpticsLabels* labels, int mode)
{
	int i;

	fprintf(fpt, "Labels ----\n");
	fprintf(fpt, "---- Name ----\n");
	for(i=0; i<4; i++) {
		fprintf(fpt, "%s\n", labels->name[i]);
	}
	fprintf(fpt, "---- Comment ----\n");
	for(i=0; i<4; i++) {
		fprintf(fpt, "%s\n", labels->comment[i]);
	}
	fprintf(fpt, "---- Filter ----\n");
	for(i=0; i<4; i++) {
		fprintf(fpt, "%s\n", labels->filter[i]);
	}
	fprintf(fpt, "---- Lens ----\n");
	for(i=0; i<4; i++) {
		fprintf(fpt, "%s\n", labels->lens[i]);
	}
	fprintf(fpt, "---- Aperture ----\n");
	for(i=0; i<4; i++) {
		fprintf(fpt, "%s\n", labels->aperture[i]);
	}
	fprintf(fpt, "---- History ----\n");
	for(i=0; i<4; i++) {
		fprintf(fpt, "%s\n", labels->history[i]);
	}
}

void
MedOpticsImageFileRead(MedOpticsImage* MOI, char* filename, int mode)
{
	char s[1024];
	FILE* fpt;
	MedOpticsHeader* moi;
	int n;

	fpt = fileOpen(filename, "r");

	moi = &(MOI->Header);	
	stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); moi->title = stringDuplicate(s);  
	stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); moi->vers  = stringDuplicate(s);  
	MedOpticsImageFileReadCameraParam(&(moi->params), fpt, mode);
	fread(&(moi->serDim), sizeof(MedOpticsInteger), 3, fpt);
#ifdef M68
	memoryByteSwap(&(moi->serDim), sizeof(MedOpticsInteger), 3);
#endif
	stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); moi->startTime = stringDuplicate(s);  
	stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); moi->endTime   = stringDuplicate(s);  
	fread(&(moi->Temperature), sizeof(MedOpticsInteger), 1, fpt);
#ifdef M68
	memoryByteSwap(&(moi->Temperature), sizeof(MedOpticsInteger), 1);
#endif
	stringGetFromFile(s, "MedOpticsImageFileRead", fpt, stdout, 3); moi->type = stringDuplicate(s);  
	fread(&(moi->numMean), sizeof(MedOpticsInteger), 2, fpt);
#ifdef M68
	memoryByteSwap(&(moi->numMean), sizeof(MedOpticsInteger), 2);
#endif
	MedOpticsImageFileReadLabels(&(moi->labels), fpt, mode);
	fread(&(moi->min), sizeof(MedOpticsInteger), 4, fpt);
#ifdef M68
	memoryByteSwap(&(moi->min), sizeof(MedOpticsInteger), 4);
#endif
	MedOpticsImageFileReadROI(&(moi->roi), fpt, mode);
	fread(&(moi->wmin), sizeof(MedOpticsInteger), 2, fpt);
#ifdef M68
	memoryByteSwap(&(moi->wmin), sizeof(MedOpticsInteger), 2);
#endif
	MOI->Image = (MedOpticsImageInteger*)memoryAllocate(sizeof(MedOpticsImageInteger)*moi->serDim*moi->parDim, "MedOptics");	
	n = fread(MOI->Image, sizeof(MedOpticsImageInteger), moi->serDim*moi->parDim, fpt);
	if(n != moi->serDim*moi->parDim) {
		fprintf(stderr, "All Data Cannot Read: %d(present) != %d(predict) at %ld\n", n, moi->serDim*moi->parDim, ftell(fpt));
	}
#ifdef M68
	memoryByteSwap(MOI->Image, sizeof(MedOpticsImageInteger), moi->serDim*moi->parDim);
#endif

}

void
MedOpticsImageHeaderPrint(FILE* fpt, MedOpticsHeader* moi, int mode)
{
	fprintf(fpt, "title: %s\n", moi->title);
	fprintf(fpt, "vers:  %s\n", moi->vers);
	fprintf(fpt, "---- Camera Params ");
	MedOpticsImageCameraParamPrint(fpt, &(moi->params), mode);
	fprintf(fpt, "serDim:    %d\n", moi->serDim);
	fprintf(fpt, "parDim:    %d\n", moi->parDim);
	fprintf(fpt, "Shutter:   %d\n", moi->Shutter);
	fprintf(fpt, "startTime:  %s\n", moi->startTime);
	fprintf(fpt, "endTime:  %s\n", moi->endTime);
	fprintf(fpt, "Temperature: %d\n", moi->Temperature);
	fprintf(fpt, "type:  %s\n", moi->type);
	fprintf(fpt, "numMean:  %d\n", moi->numMean);
	fprintf(fpt, "exclude:  %d\n", moi->exclude);
	MedOpticsImageLabelsPrint(fpt, &(moi->labels), mode);
	fprintf(fpt, "min:  %d\n", moi->min);
	fprintf(fpt, "max:  %d\n", moi->max);
	fprintf(fpt, "mean:  %15.6f\n", moi->mean);
	fprintf(fpt, "stdev:  %15.6f\n", moi->stdev);
	MedOpticsImageROIPrint(fpt, &(moi->roi), mode);
	fprintf(fpt, "wmin:  %d\n", moi->wmin);
	fprintf(fpt, "wmax:  %d\n", moi->wmax);
}

