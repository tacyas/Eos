/*
# lmrc2gif.c  1.1
# The latest update : 01/23/97 at 11:07:17
#
#@(#) gifUtil ver 1.1
#@(#) Created by tacyas
#@(#)
#@(#) Usage : gifUtil 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)gifUtil ver1.1; Date:97/01/23 @(#)";

#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/gifFile.h"
#include "mrcImage.h"

#define PROGRAM_NAME "mrc2gif"
static int HandleGifError(GifFileType *GifFile);

int
lmrc2gif(char* out, mrcImage* mrc, ColorMapObject* ColorMap, long mode)
{
	int i, j, ImageHeight, ImageWidth;
	static GifPixelType* ScanLine;
	GifFileType* GifFile;
	double data;

	ImageWidth  = mrc->HeaderN.x;
	ImageHeight = mrc->HeaderN.y;

	DEBUGPRINT2("lmrc2gif %d %d", ImageWidth, ImageHeight);
	if (NULL == (ScanLine = (GifPixelType *) malloc(sizeof(GifPixelType) * mrc->HeaderN.x))) {
		GIF_MESSAGE("Failed to allocate scan line, aborted.");
		exit(3);
	}
    if ((GifFile = EGifOpenFileName(out, (long)NULL)) == NULL) {  
		free((char *) ScanLine);
		return HandleGifError(GifFile);
	}
    if(EGifPutScreenDesc(GifFile, ImageWidth, ImageHeight, ColorMap->BitsPerPixel, 0, ColorMap) == GIF_ERROR) {
		free((char *) ScanLine);
		return HandleGifError(GifFile);
	}
	
	if (EGifPutImageDesc(GifFile, 0, 0, ImageWidth, ImageHeight, FALSE, NULL) == GIF_ERROR) {
		free((char *) ScanLine);
		return HandleGifError(GifFile);
	}
	
	GifQprintf("\n%s: Image 1 at (0, 0) [%dx%d]:     ", PROGRAM_NAME, ImageWidth, ImageHeight);
	for (i = 0; i < ImageHeight; i++) {
		DEBUGPRINT1("%d", i);
		for(j = 0; j < ImageWidth; j++) {
			mrcPixelDataGet(mrc, j, ImageHeight - i - 1, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);	
			data = 255*(data - mrc->HeaderAMin)/(mrc->HeaderAMax - mrc->HeaderAMin);
			if(data<0) { 
				ScanLine[j] = 0;
			} else if(255<data) {
				ScanLine[j] = 255;
			} else {
				ScanLine[j] = (unsigned char)(data);
			}
			if (ScanLine[j] >= ColorMap->ColorCount) {
				GIF_MESSAGE("Warning: RAW data color > maximum color map entry.");
			}
		}
		if(EGifPutLine(GifFile, ScanLine, ImageWidth) == GIF_ERROR) {
				free((char *) ScanLine);
				return HandleGifError(GifFile);
		}
		GifQprintf("\b\b\b\b%-4d", i);
		DEBUGPRINT1("end", i);
	}
	
	DEBUGPRINT("Close-Start");
	if(EGifCloseFile(GifFile, NULL) == GIF_ERROR) {
		free((char *) ScanLine);
		return HandleGifError(GifFile);
	}
	DEBUGPRINT("Close");
	free((char *) ScanLine);
	return 0;
}

int
lmrc2gifColor(char* out, mrcImage* r, mrcImage* g, mrcImage* b, ColorMapObject* ColorMap, int n, int nr, int ng, int nb, long mode)
{
	int i, j, ImageHeight, ImageWidth;
	static GifPixelType* ScanLine;
	GifFileType* GifFile;
	int data;
	double rdata;
	double gdata;
	double bdata;
	unsigned char irdata;
	unsigned char igdata;
	unsigned char ibdata;

	DEBUGPRINT("In lmrc2gifColor\n");
	DEBUGPRINT4("%d=(%dx%dx%d)\n", n, nr, ng, nb);
	ImageWidth  = MAX(r->HeaderN.x, MAX(g->HeaderN.x, b->HeaderN.x));
	ImageHeight = MAX(r->HeaderN.y, MAX(g->HeaderN.y, b->HeaderN.y));

	DEBUGPRINT2("w,h = (%d, %d)\n", ImageWidth, ImageHeight);
	if (NULL == (ScanLine = (GifPixelType *) malloc(sizeof(GifPixelType) * ImageWidth))) {
		GIF_MESSAGE("Failed to allocate scan line, aborted.");
		exit(3);
	}
    if ((GifFile = EGifOpenFileName(out, (long)NULL)) == NULL) {  
		free((char *) ScanLine);
		return HandleGifError(GifFile);
	}
    if(EGifPutScreenDesc(GifFile, ImageWidth, ImageHeight, ColorMap->BitsPerPixel, 0, ColorMap) == GIF_ERROR) {
		free((char *) ScanLine);
		return HandleGifError(GifFile);
	}
	
	if (EGifPutImageDesc(GifFile, 0, 0, ImageWidth, ImageHeight, FALSE, NULL) == GIF_ERROR) {
		free((char *) ScanLine);
		return HandleGifError(GifFile);
	}
		
	GifQprintf("\n%s: Image 1 at (0, 0) [%dx%d]:     ", PROGRAM_NAME, ImageWidth, ImageHeight);
	for (i = 0; i < ImageHeight; i++) {
		for(j = 0; j < ImageWidth; j++) {
			if(1<nr) {
				mrcPixelDataGet(r, j, ImageHeight - i - 1, 0.0, &rdata, mrcPixelRePart, mrcPixelHowNearest);	
				rdata = (nr-1)*(rdata - r->HeaderAMin)/(r->HeaderAMax - r->HeaderAMin);
			} else {
				rdata = 0;
			}
			if(1<ng) {
				mrcPixelDataGet(g, j, ImageHeight - i - 1, 0.0, &gdata, mrcPixelRePart, mrcPixelHowNearest);	
				gdata = (ng-1)*(gdata - g->HeaderAMin)/(g->HeaderAMax - g->HeaderAMin);
			} else {
				gdata = 0;
			}
			if(1<nb) {
				mrcPixelDataGet(b, j, ImageHeight - i - 1, 0.0, &bdata, mrcPixelRePart, mrcPixelHowNearest);	
				bdata = (nb-1)*(bdata - b->HeaderAMin)/(b->HeaderAMax - b->HeaderAMin);
			} else {
				bdata = 0;
			}
			if(rdata<0) {
				irdata = 0;
			} else if(nr-1<rdata) {
				irdata = nr-1;
			} else {
				irdata = rdata;
			}
			if(gdata<0) {
				igdata = 0;
			} else if(ng-1<gdata) {
				igdata = ng-1;
			} else {
				igdata = gdata;
			}
			if(bdata<0) {
				ibdata = 0;
			} else if(nb-1<=bdata) {
				ibdata = nb-1;
			} else {
				ibdata = bdata;
			}
			data = ibdata + nb*igdata + nb*ng*irdata;
			DEBUGPRINT6("(%d, %d) %d:=%d %d %d\n", i, j, data, ibdata, igdata, irdata);
			if(data<0) { 
				ScanLine[j] = 0;
			} else if(n-1<data) {
				ScanLine[j] = n-1;
			} else {
				ScanLine[j] = (unsigned char)(data);
			}
			if (ScanLine[j] >= ColorMap->ColorCount) {
				GIF_MESSAGE("Warning: RAW data color > maximum color map entry.");
			}
		}
		DEBUGPRINT("Put");
		if(EGifPutLine(GifFile, ScanLine, ImageWidth) == GIF_ERROR) {
				free((char *) ScanLine);
				return HandleGifError(GifFile);
		}
		DEBUGPRINT("End");
		GifQprintf("\b\b\b\b%-4d", i);
	}
	DEBUGPRINT("Close");	
	if(EGifCloseFile(GifFile, NULL) == GIF_ERROR) {
		free((char *) ScanLine);
		return HandleGifError(GifFile);
	}

	free((char *) ScanLine);
	return 0;
}
int HandleGifError(GifFileType *GifFile)
{
	int i = GifLastError();
	
	if (EGifCloseFile(GifFile, NULL) == GIF_ERROR) {
		GifLastError();
	}
	return i;
}	
