/*
# dm2mrc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dm2mrc
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

#undef DEBUG
#include "genUtil.h"
#include "dmFile.h"
#include "mrcImage.h"

/*
Example:
typedef struct ldm2mrcInfo {
	float a;
	int   b;
} ldm2mrcInfo;

typedef enum ldm2mrcMode {
	a=0,
	b=1
} ldm2mrcMode;
*/

int
main(int argc, char* argv[]) 
{
	dmFile dm;
	dm2mrcInfo info;
	mrcImage out;
	mrcImage thumnail;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	
	dmFileRead(info.fptIn, &dm, "in main", 0);
	ldm2mrc(&out, &dm, 0);

	if(info.flagThumnail) {
		ldm2mrc(&thumnail, &dm, 1);
		DEBUGPRINT4("Thumnail: %d %d %d %d\n", thumnail.HeaderN.x, thumnail.HeaderN.y, thumnail.HeaderN.z, thumnail.HeaderMode);
	}
	DEBUGPRINT4("Out: %d %d %d %d\n", out.HeaderN.x, out.HeaderN.y, out.HeaderN.z, out.HeaderMode);
	mrcFileWrite(&out, info.Out, "in main", 0);
	DEBUGPRINT("Out Wrote\n");
	if(info.flagThumnail) {
		DEBUGPRINT4("Thumnail: %d %d %d %d\n", thumnail.HeaderN.x, thumnail.HeaderN.y, thumnail.HeaderN.z, thumnail.HeaderMode);
		mrcFileWrite(&thumnail, info.Thumnail, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
