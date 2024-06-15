/*
# bmp2mrc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : bmp2mrc
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
#include "mrcImage.h"

/*
Example:
typedef struct lbmp2mrcInfo {
	float a;
	int   b;
} lbmp2mrcInfo;

typedef enum lbmp2mrcMode {
	a=0,
	b=1
} lbmp2mrcMode;
*/

int
main(int argc, char* argv[]) 
{
	bmp2mrcInfo info;
	lbmp2mrcInfo linfo;
	bmpFile in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.Length.x = info.LengthX;
	linfo.Length.y = info.LengthY;
	linfo.Length.z = info.LengthX;
	linfo.mode = info.Mode;
	bmpFileRead(&in, info.fptIn, 0);
	
	DEBUGPRINT("lbmp2mrc\n");

	lbmp2mrc(&out, &in, linfo, info.mode);

	DEBUGPRINT1("mrcFileWrite: %s\n", info.Out);
	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-M \n");
	lbmp2mrcUsage(stderr);
}
