/*
# tiffFileInfo : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : tiffFileInfo
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
#include "tiffio.h"

/*
Example:
typedef struct ltiffFileInfoInfo {
	float a;
	int   b;
} ltiffFileInfoInfo;

typedef enum ltiffFileInfoMode {
	a=0,
	b=1
} ltiffFileInfoMode;
*/

extern int tiffFileInfo(FILE* fpt, TIFF* tiff, int mode);


int
main(int argc, char* argv[]) 
{
	tiffFileInfoInfo info;
    TIFF* tiff;


	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    tiff = TIFFOpen(info.In, "r");
    if(tiff) {
        tiffFileInfo(info.fptOut, tiff, info.mode);
        TIFFClose(tiff);
    } else {
        fprintf(stderr, "Not Opened TIFF file: %s\n", info.In);
    }
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


int
tiffFileInfo(FILE* fpt, TIFF* tiff, int mode)
{
    TIFFRGBAImage img;
    char emsg[1024];

    int dircount = 1;
    
    while(TIFFSetDirectory(tiff, dircount-1)) {
        fprintf(fpt, "current: %d\n", TIFFCurrentDirectory(tiff));
        TIFFPrintDirectory(tiff, fpt, mode);;
        dircount++;
    }
    fprintf(fpt, "numdir: %d\n", dircount-1);
}
