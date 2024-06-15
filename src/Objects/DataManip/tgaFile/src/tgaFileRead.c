/*
# tgaFileRead : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : tgaFileRead 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>

#undef DEBUG
#include "genUtil.h" 

#include "Memory.h"
#include "../inc/tgaFile.h"

tgaFile* 
tgaFileHeaderRead(tgaFile* tga, FILE* fpt, int mode) 
{
	if(NULL==tga) {
			tga = tgaFileInit(NULL, NULL, mode);
	}
	fseek(fpt, 0, SEEK_SET);	
	DEBUGPRINT1("tgaFileHeaderSize: %d\n", sizeof(tgaFileHeader));
	DEBUGPRINT1("tgaFileColorMapSpec: %d\n", sizeof(tgaFileColorMapSpecification));
	DEBUGPRINT1("tgaFileImageSpec: %d\n", sizeof(tgaFileImageSpecification));
	fread(&tga->Header, sizeof(tgaFileHeader), 1, fpt);
	tga->flagHeader = 1; 
	return tga;
}

tgaFile*
tgaFileImageDataRead(tgaFile* tga, FILE* fpt, int mode)
{
	tgaFileImageInit(tga, fpt, mode);	
	fread(tga->Image, sizeof(tgaFileImageData), tga->ImageDataBytes, fpt);

	return tga;
}

tgaFile*
tgaFileRead(tgaFile* tga, FILE* fpt, int mode)
{
	tgaFileImageDataRead(tga, fpt, mode);

	return tga;
}
