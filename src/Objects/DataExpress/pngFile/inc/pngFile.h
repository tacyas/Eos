/*
# pngFile.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : pngFile.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef PNG_FILE_H  
#define PNG_FILE_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <png.h>
#include "mrcImage.h"
#include "Memory.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef struct pngFile {
	png_image   pngImage;
	uint32_t    stride;
	unsigned char* byteImage;
	int         flagHanded;
	int         size;

} pngFile;

typedef struct lmrc2pngInfo {
	int z;
} lmrc2pngInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

void pngFileInit(pngFile* png, int mode);
void lmrc2png(pngFile* png, mrcImage* mrc, lmrc2pngInfo* linfo, int mode);
void pngFileWrite(pngFile* png, char* filename, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
