/*
# bmpFileInfo : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : bmpFileInfo
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
#include "bmpFile.h"

/*
Example:
typedef struct lbmpFileInfoInfo {
	float a;
	int   b;
} lbmpFileInfoInfo;

typedef enum lbmpFileInfoMode {
	a=0,
	b=1
} lbmpFileInfoMode;
*/

int
main(int argc, char* argv[]) 
{
	bmpFileInfoInfo info;
	bmpFile bmp;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	bmpFileRead(&bmp, info.fptIn, 0);
	DEBUGPRINT2("%c%c\n", bmp.Header.bfType[0], bmp.Header.bfType[1]);
	DEBUGPRINT1("%d\n", bmp.Header.bfSize);
	DEBUGPRINT("bmpFileRead End\n");

	DEBUGPRINT("bmpFileInfo Start\n");
	DEBUGPRINT1("fptOut: %p\n", info.fptOut);
	DEBUGPRINT1("stdout: %p\n", stdout);
	bmpFileInfo(info.fptOut, &bmp, info.mode);
	//bmpFileInfo(stdout, &bmp, info.mode);
	//bmpFileInfoHeaderInfo(stdout, &bmp, info.mode);
	//bmpFilePaletteInfo(stdout, &bmp, info.mode);
	DEBUGPRINT("bmpFileInfo End\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
