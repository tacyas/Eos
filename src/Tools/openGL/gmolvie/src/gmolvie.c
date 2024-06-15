/*
# gmolvie : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : gmolvie
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
#include "eosOpenGL.h"

/*
Example:
typedef struct lgmolvieInfo {
	float a;
	int   b;
} lgmolvieInfo;

typedef enum lgmolvieMode {
	a=0,
	b=1
} lgmolvieMode;
*/

int
main(int argc, char* argv[]) 
{
	gmolvieInfo info;

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