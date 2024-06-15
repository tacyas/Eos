/*
# dmInfo : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dmInfo
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

/*
Example:
typedef struct ldmInfoInfo {
	float a;
	int   b;
} ldmInfoInfo;

typedef enum ldmInfoMode {
	a=0,
	b=1
} ldmInfoMode;
*/

int
main(int argc, char* argv[]) 
{
	dmFile in;
	dmInfoInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	dmFileRead(info.fptIn, &in, "in main", info.mode);

	dmFileInfo(info.fptOut, in, info.mode);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, " -m 0 ; tagTerm: tagName/tagValue/.. etc \n");
	fprintf(stderr, " -m 1 ; tagName: tagValue etc\n");
}
