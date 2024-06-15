/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% bmpFileInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : bmpFileInfo 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%bmpFileInfo ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "../inc/bmpFile.h"

void
bmpFileInfo(FILE* fpt, bmpFile* in, int mode)
{
	DEBUGPRINT("bmpFileInfo: Start\n");
	bmpFileFileHeaderInfo(fpt, in, mode);
	bmpFileInfoHeaderInfo(fpt, in, mode);
	bmpFilePaletteInfo(fpt, in, mode);
	DEBUGPRINT("bmpFileInfo: End\n");
}

void
bmpFileFileHeaderInfo(FILE* fpt, bmpFile* in, int mode)
{
	DEBUGPRINT("bmpFileFileHeaderInfo Start\n");
	fprintf(fpt, "bfType: %c%c\n", in->Header.bfType[0], in->Header.bfType[1]);
	fprintf(fpt, "bfSize: %d\n", in->Header.bfSize);
	fprintf(fpt, "bfOffBits: %d\n", in->Header.bfOffBits);
	DEBUGPRINT("bmpFileFileHeaderInfo End\n");
}


void
bmpFileInfoHeaderInfo(FILE* fpt, bmpFile* in, int mode)
{
	DEBUGPRINT("bmpFileInfoHeaderInfo Start\n");
	fprintf(fpt, "biSize: %d\n", in->Info.biSize);
	fprintf(fpt, "biWidth: %d\n", in->Info.biWidth);
	fprintf(fpt, "biHeight: %d\n", in->Info.biHeight);
	fprintf(fpt, "biPanes: %d\n", in->Info.biPlanes);
	fprintf(fpt, "biBitCount: %d\n", in->Info.biBitCount);
	fprintf(fpt, "biCompression: %d\n", in->Info.biCompression);
	fprintf(fpt, "biSizeImage: %d\n", in->Info.biSizeImage);
	fprintf(fpt, "biXPixPerMeter: %d\n", in->Info.biXPixPerMeter);
	fprintf(fpt, "biYPixPerMeter: %d\n", in->Info.biYPixPerMeter);
	fprintf(fpt, "biCirUsed: %d\n", in->Info.biCirUsed);
	fprintf(fpt, "biCirImportant: %d\n", in->Info.biCirImportant);
	DEBUGPRINT("bmpFileInfoHeaderInfo End\n");
}

void
bmpFilePaletteInfo(FILE* fpt, bmpFile* in, int mode)
{

}
