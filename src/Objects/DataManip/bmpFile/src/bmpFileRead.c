/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% bmpFileRead ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : bmpFileRead 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%bmpFileRead ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/bmpFile.h"

void
bmpFileRead(bmpFile* bmp, FILE* fpt, int mode)
{
	size_t size;
	int n;
	long pos;

	fseek(fpt, 0L, SEEK_SET);
	size = fread(&(bmp->Header.bfType),      2, 1, fpt);
	size = fread(&(bmp->Header.bfSize),      4, 1, fpt);
	size = fread(&(bmp->Header.bfReserved1), 2, 1, fpt);
	size = fread(&(bmp->Header.bfReserved2), 2, 1, fpt);
	size = fread(&(bmp->Header.bfOffBits),   4, 1, fpt);
	if(size!=1) {
	 	fprintf(stderr, "Header Size Strange: %zu != %d\n", size, 14);
		exit(EXIT_FAILURE);
	}
	if(bmp->Header.bfType[0] != 'B'
	 ||bmp->Header.bfType[1] != 'M') {
	 	fprintf(stderr, "This is not a BMP-formatted image file\n");
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG
	fprintf(stderr, "header size: %d\n", sizeof(bmpFileHeader)*size);
	bmpFileFileHeaderInfo(stderr, bmp, 0);
#endif

	size = fread(&(bmp->Info.biSize), 4, 1, fpt);
	if(40!=bmp->Info.biSize || 40!=sizeof(bmp->Info)) {
	 	fprintf(stderr, "Not supported verions of bmpFile: biSize = %d\n", bmp->Info.biSize);
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG
	fprintf(stderr, "biSIzeSize: %d\n", sizeof(bmp->Info.biSize)*size);
	fprintf(stderr, "biSize: %d\n", bmp->Info.biSize);
	fprintf(stderr, "InfoSize: %d\n", sizeof(bmp->Info));
#endif
	
	fseek(fpt, -4L, SEEK_CUR);
	size = fread(&(bmp->Info), 40, 1, fpt);
	if(1!=size) {
	 	fprintf(stderr, "Size is Strange: %zu != %d\n", size, 40);
		exit(EXIT_FAILURE);
	}
#ifdef DEBUG
	fprintf(stderr, "info header size: %d\n", size*sizeof(bmp->Info)); fflush(stderr);
	bmpFileInfoHeaderInfo(stderr, bmp, 0);
#endif

	if(bmp->Info.biBitCount<=8) {
		n = pow(2,bmp->Info.biBitCount);
		DEBUGPRINT1("numPalette to read: %d\n", n);
		bmp->Palette = (bmpFileColorPalette*) memoryAllocate(sizeof(bmpFileColorPalette)*n, "in bmpFileRead");	
		size = fread(bmp->Palette, sizeof(bmpFileColorPalette), n, fpt);
		DEBUGPRINT1("read numPalette   : %zu\n", size);
	}

	pos = ftell(fpt);
	if(pos != bmp->Header.bfOffBits) {
		fprintf(stderr, "Warning: Something wrong: another header: pos %ld bfOffBits %d\n", pos, bmp->Header.bfOffBits);
		fseek(fpt, bmp->Header.bfOffBits, SEEK_SET);
	}

	if(bmp->Info.biHeight<0) {
		bmp->Height = -bmp->Info.biHeight;
	} else {
		bmp->Height =  bmp->Info.biHeight;
	} 
	bmp->Width = bmp->Info.biWidth;
	bmp->numPixel = bmp->Width*bmp->Height;
	bmp->Width4   = (bmp->Width*bmp->Info.biBitCount/8/4)*4;
	if(bmp->Width4<bmp->Width*bmp->Info.biBitCount/8) {
		bmp->Width4 += 4;
	}
	bmp->Width4/=(bmp->Info.biBitCount/8);	
	bmp->numPixel4 = bmp->Width4*bmp->Height;
	DEBUGPRINT1("Width: %d\n", bmp->Width);
	DEBUGPRINT1("Height: %d\n", bmp->Height);
	DEBUGPRINT1("Width4(4BytesBoundary): %d\n", bmp->Width4);

	if(0!=bmp->Info.biCompression) {
		fprintf(stderr, "Not supported: Compression\n");
		exit(EXIT_FAILURE);
	}

	bmp->BytesPerPixel = bmp->Info.biBitCount/8;
	bmp->BitsPerPixel  = bmp->Info.biBitCount;
	if(1<=bmp->BytesPerPixel) {
		bmp->BytesPerImage = bmp->BytesPerPixel*bmp->numPixel4;
	} else {
		bmp->BytesPerImage = (bmp->BitsPerPixel*bmp->numPixel4)/8;
	}
	DEBUGPRINT1("BytesPerPixel: %d\n", bmp->BytesPerPixel);
	DEBUGPRINT1("BitsPerPixel:  %d\n", bmp->BitsPerPixel);
	DEBUGPRINT1("ByptePerImage: %d\n", bmp->BytesPerImage);

	pos = ftell(fpt);
	if(pos!=bmp->Header.bfOffBits) {
		fprintf(stderr, "Image Position is wrong: %ld\n", pos);	
		exit(EXIT_FAILURE);
	}

	if(bmp->BitsPerPixel<=8) {
		bmp->Image = (unsigned char*)memoryAllocate(sizeof(unsigned char)*bmp->BytesPerImage, "in "); 
		DEBUGPRINT1("bmp->Image: %p\n", bmp->Image);
		DEBUGPRINT1("BytesPerImage: %d\n", bmp->BytesPerImage);
		DEBUGPRINT("fread before\n");
		size = fread(bmp->Image, sizeof(unsigned char), bmp->BytesPerImage, fpt);
		DEBUGPRINT("fread after\n");
		bmp->ColorImage = NULL;
	} else {
		bmp->Image = NULL;
		bmp->ColorImage = (unsigned char*)memoryAllocate(sizeof(unsigned char)*bmp->BytesPerPixel*bmp->numPixel4, "in"); 
		size = fread(bmp->ColorImage, sizeof(unsigned char), bmp->BytesPerImage, fpt);
	}	
	DEBUGPRINT1("Read Bytes: %d\n", size);
}
