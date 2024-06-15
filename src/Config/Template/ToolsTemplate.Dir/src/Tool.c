#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Class.h"

/*
Example:
typedef struct lToolInfo {
	float a;
	int   b;
} lToolInfo;

typedef enum lToolMode {
	a=0,
	b=1
} lToolMode;
*/

int
main(int argc, char* argv[]) 
{
	ToolInfo info;

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
