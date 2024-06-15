/*
# bmpFile.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : bmpFile.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef BMP_FILE_H 
#define BMP_FILE_H 

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef struct bmpFileHeader {
	char  bfType[2]; 		// BM
	unsigned int   bfSize;			// FileSize [Byte]	
	char  bfReserved1[2];	
	char  bfReserved2[2];	
	unsigned int   bfOffBits;		// ImageOffset [Byte]	
} bmpFileHeader; /* 14 BYTE */

typedef struct bmpFileInfoHeader {
	unsigned int biSize;
	int	biWidth;  // [Pixel]
	int	biHeight; // [Pixel]
	unsigned short biPlanes;  // 1
	unsigned short biBitCount; // bits/pixel
	unsigned int biCompression;   
	unsigned int biSizeImage;
	int biXPixPerMeter;
	int biYPixPerMeter;
	unsigned int biCirUsed;
	unsigned int biCirImportant;
} bmpFileCoreHeader;

typedef struct bmpFileColorPalette {
	char rgbBlue;
	char rgbGreen;
	char rgbRed;
	char rgbReserved;
} bmpFileColorPalette;

typedef struct bmpFile {
	bmpFileHeader 		 Header;
	bmpFileCoreHeader 	 Info;
	bmpFileColorPalette* Palette ;
	unsigned char*  Image;
	unsigned char*  ColorImage;

	int Width;
	int Width4;
	int Height;
	int numPixel;
	int numPixel4; 
	int BytesPerPixel;
	int BitsPerPixel;
	int BytesPerImage;
} bmpFile;

typedef enum lbmp2mrcInfoMode {
	lbmp2mrcInfoModeY=0,
	lbmp2mrcInfoModeR=1,
	lbmp2mrcInfoModeG=2,
	lbmp2mrcInfoModeB=3
} lbmp2mrcInfoMode;

typedef struct lbmp2mrcInfo {
	mrcImageParaTypeRealCoord Length;	
	lbmp2mrcInfoMode mode;
} lbmp2mrcInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

/* bmpFileRead.c */
extern void bmpFileRead(bmpFile* in, FILE* fpt, int mode);

/* lbmp2mrc.c */
extern void lbmp2mrc(mrcImage* out, bmpFile* in, lbmp2mrcInfo linfo, int mode);
extern void lbmp2mrcUsage(FILE* fpt);

/* bmpFileInfo.c */
extern void bmpFileInfo(FILE* fpt, bmpFile* in, int mode);
extern void bmpFileFileHeaderInfo(FILE* fpt, bmpFile* in, int mode);
extern void bmpFileInfoHeaderInfo(FILE* fpt, bmpFile* in, int mode);
extern void bmpFilePaletteInfo(FILE* fpt, bmpFile* in, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
