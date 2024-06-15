/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ltlg2ps ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ltlg2ps
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ltlg2ps ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "rec3d.h"

/*
Example:
typedef struct lltlg2psInfo {
	float a;
	int   b;
} lltlg2psInfo;

typedef enum lltlg2psMode {
	a=0,
	b=1
} lltlg2psMode;
*/

int
main(int argc, char* argv[]) 
{
	ltlg2psInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
