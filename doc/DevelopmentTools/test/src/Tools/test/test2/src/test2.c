#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

void
main(int argc, char* argv[]) 
{
	long status;
	test2Info info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
}

void
additionalUsage()
{
}
