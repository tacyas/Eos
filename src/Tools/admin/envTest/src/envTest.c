/*
# envTest : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : envTest
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
//#include "Class.h"

/*
Example:
typedef struct lenvTestInfo {
	float a;
	int   b;
} lenvTestInfo;

typedef enum lenvTestMode {
	a=0,
	b=1
} lenvTestMode;
*/

extern void lenvTest(FILE* fpt);

int
main(int argc, char* argv[]) 
{
	envTestInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    lenvTest(info.fptOut);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
lenvTest(FILE* fpt)
{
    fprintf(fpt, "SIZEOF_INT %lu\n", sizeof(int));
    fprintf(fpt, "SIZEOF_LONG %lu\n", sizeof(long));
    fprintf(fpt, "SIZEOF_LONG_LONG %lu\n", sizeof(long long));
    fprintf(fpt, "SIZEOF_LONG %lu\n", sizeof(long));
    fprintf(fpt, "SIZEOF_VOID_P: %lu\n", sizeof(void*));
}
