/*
# tgaFileInit : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : tgaFileInit 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include "Memory.h"
#include "../inc/tgaFile.h"

tgaFile* 
tgaFileInit(tgaFile* tga, FILE* fpt, int mode) 
{
	if(NULL==tga) {
		tga = (tgaFile*)memoryAllocate(sizeof(tgaFile), "in tgaFileHeaderRead");	
	}
	tga->flagHeader = 0;
	if(NULL!=fpt) {
		tgaFileHeaderRead(tga, fpt, mode);
	}
	return tga;
}

tgaFile*
tgaFileImageInit(tgaFile* tga, FILE* fpt, int mode)
{
	if(!tga->flagHeader) {
		tgaFileHeaderRead(tga, fpt, mode);
	}
	fseek(fpt, tga->Header.IDLength, SEEK_CUR);
	switch(tga->Header.ColorMapType) {
		case tgaFileColorMapNoColorMap: {
			break;											
		}
		default: {
			fprintf(stderr, "tgaColorMap is not yet supported\n");
			break; 
		}
	}
	tga->ImageDataOffset = ftell(fpt);	
	tga->ImageDataBytes = sizeof(tgaFileImageData)
			*tga->Header.ImageSpec.Width
			*tga->Header.ImageSpec.Height
			*tga->Header.ImageSpec.Depth/8;

	tga->Image = (tgaFileImageData*)memoryAllocate(
			tga->ImageDataBytes,
			"ImageDataSize");

	return tga;
}

