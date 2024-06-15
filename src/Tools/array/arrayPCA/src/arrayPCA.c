/*
# arrayPCA : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : arrayPCA
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
#include "Array.h"

/*
Example:
typedef struct larrayPCAInfo {
	float a;
	int   b;
} larrayPCAInfo;

typedef enum larrayPCAMode {
	a=0,
	b=1
} larrayPCAMode;
*/

int
main(int argc, char* argv[]) 
{
	Array X; 
	Array lambda;
	Array u;
	Array C;
	Array ave;
	Array XX;

	arrayPCAInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	arrayReadFromFile(info.fptIn, &X, "in main");

	arrayPCA(&u, &C, &lambda, &X, &ave, info.mode);

	arrayPCAPrint(info.fptOut, &u, &lambda, 0);

	arrayPCATransform(&XX, &X, &ave, &u, 0);

	arrayWriteToFile(info.fptOut2, &XX, "in main");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
