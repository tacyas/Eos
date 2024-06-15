/*
# tgaFilePrint : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : tgaFilePrint 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>

#include "../inc/tgaFile.h"

void
tgaFileHeaderPrint(tgaFile* tga, FILE* fpt, int mode)
{
	fprintf(fpt, "IDLength[Bytes]:   %d \n", tga->Header.IDLength);
	switch(tga->Header.ColorMapType) {
		case tgaFileColorMapNoColorMap: {
			fprintf(fpt, "ColorMap:          %d : NoColorMap\n", tga->Header.ColorMapType);
			break;
		}
		case tgaFileColorMapColorMap: {
			fprintf(fpt, "ColorMap:          %d : WithColorMap\n", tga->Header.ColorMapType);
			break;
		}
		default: {
			fprintf(fpt, "Not supported ColorMap \n");
			break;
		}
	}
	fprintf(fpt, "ImageType:                %d \n", tga->Header.ImageType);
	fprintf(fpt, "ColorMapSpec.FirstEntryIndex:   %d \n", tga->Header.ColorMapSpec.FirstEntryIndex);
	fprintf(fpt, "ColorMapSpec.ColorMapLength:    %d \n", tga->Header.ColorMapSpec.ColorMapLength);
	fprintf(fpt, "ColorMapSpec.ColorMapEntrySize: %d \n", tga->Header.ColorMapSpec.ColorMapEntrySize);
	fprintf(fpt, "ImageSpec.Xorigin: %d \n", tga->Header.ImageSpec.Xorigin);
	fprintf(fpt, "ImageSpec.Yorigin: %d \n", tga->Header.ImageSpec.Yorigin);
	fprintf(fpt, "ImageSpec.Width: %d \n", tga->Header.ImageSpec.Width);
	fprintf(fpt, "ImageSpec.Height: %d \n", tga->Header.ImageSpec.Height);
	fprintf(fpt, "ImageSpec.Depth: %d \n", tga->Header.ImageSpec.Depth);
	fprintf(fpt, "ImageSpec.Descriptor: %d \n", tga->Header.ImageSpec.Descriptor.All);
	fprintf(fpt, "ImageSpec.Descriptor.ImageOrigin: %d \n", tga->Header.ImageSpec.Descriptor.Bit.ImageOrigin);
	fprintf(fpt, "ImageSpec.Descriptor.AlphaChannel: %d \n", tga->Header.ImageSpec.Descriptor.Bit.AlphaChannelBits);
}
