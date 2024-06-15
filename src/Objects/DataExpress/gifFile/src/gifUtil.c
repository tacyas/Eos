/*
# gifUtil.c  1.1
# The latest update : 01/23/97 at 11:07:07
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

ColorMapObject*
gifColorMapInit(int n, long mode)
{
	ColorMapObject* ColorMap;

	DEBUGPRINT("--ColorMapInit");
	if((ColorMap = MakeMapObject(256, NULL)) == NULL) {
   		GIF_MESSAGE("Failed to allocate bitmap, aborted.");
	  	exit(3);
	}
	return ColorMap;
}


ColorMapObject*
gifColorMapGrey(ColorMapObject* ColorMap, int n)
{
	int i;
	for(i=0; i<n; i++) {
		ColorMap->Colors[i].Red   = i*255/n;
		ColorMap->Colors[i].Green = i*255/n;
		ColorMap->Colors[i].Blue  = i*255/n;
	}
	return ColorMap;
}

ColorMapObject*
gifColorMapColor(ColorMapObject* ColorMap, int n, int r, int g, int b)
{
	int i;
	
	DEBUGPRINT("--ColorMapColor");
	if(r<1 || g<1 || b<1) {
		fprintf(stderr, "Error in gifColorMapColor: (r,g,b)=(%d,%d,%d)\n", r, g, b);
		exit(EXIT_FAILURE);
	} 
	for(i=0; i<n; i++) {
		if(r==1) {
			ColorMap->Colors[i].Red   = 0;
		} else {
			ColorMap->Colors[i].Red   = ((i/g/b)%r)*255/(r-1);
		}
		if(g==1) {
			ColorMap->Colors[i].Green = 0;
		} else {
			ColorMap->Colors[i].Green = ((i  /b)%g)*255/(g-1);
		} 
		if(b==1) {
			ColorMap->Colors[i].Blue  = 0;
		} else {
			ColorMap->Colors[i].Blue  = ((i    )%b)*255/(b-1);
		}
		DEBUGPRINT4("%d: (%d %d %d)\n", i, ColorMap->Colors[i].Red, ColorMap->Colors[i].Green, ColorMap->Colors[i].Blue);
	}
	return ColorMap;
}

static int HandleGifError(GifFileType *GifFile)
{
	int i = GifLastError();
	
	if (EGifCloseFile(GifFile) == GIF_ERROR) {
		GifLastError();
	}
	return i;
}	
