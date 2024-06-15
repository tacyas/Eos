/*
# bin2mrc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : bin2mrc
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"

/*
Example:
typedef struct lbin2mrcInfo {
	float a;
	int   b;
} lbin2mrcInfo;

typedef enum lbin2mrcMode {
	a=0,
	b=1
} lbin2mrcMode;
*/

typedef struct binFile {
    short nx;
    short ny;
    short nz;
    long  number;
    short* image;  
    long offset;
} binFile;
#include <stdio.h>
#include "Memory.h"
#include "mrcImage.h"


extern void binFileRead(binFile* out, FILE* fpt, int mode);
extern void lbin2mrc(mrcImage* out, binFile* in, int mode);
int
main(int argc, char* argv[]) 
{
	bin2mrcInfo info;
	mrcImage out;
	binFile bin;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	binFileRead(&bin, info.fptIn, 0);

	lbin2mrc(&out, &bin, info.mode); 
	
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
binFileRead(binFile* out, FILE* fpt, int mode) 
{
	fseek(fpt, 0L, SEEK_SET);		
	fread(&out->nx, sizeof(short), 1, fpt);
	fread(&out->ny, sizeof(short), 1, fpt);
	fread(&out->nz, sizeof(short), 1, fpt);
	
	out->number = out->nx*out->ny*out->nz;

	out->image = memoryAllocate(sizeof(short)*out->number, "binFileRead");
	fread(out->image, sizeof(short), out->number, fpt);
}

void
lbin2mrc(mrcImage* out, binFile* bin, int mode)
{
	int i;
	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = bin->nx;
	out->HeaderN.y = bin->ny;
	out->HeaderN.z = bin->nz;
	out->HeaderMode = mrcFloatImage;
	mrcInit(out, NULL);

	for(i=0; i<bin->number; i++) {
		out->ImageFloatImage[i] =(float)((short) bin->image[i]);
	}
}

