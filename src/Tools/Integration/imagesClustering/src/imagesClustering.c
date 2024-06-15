/*
# imagesClustering : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : imagesClustering
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
#include "Integration.h"

/*
Example:
typedef struct limagesClusteringInfo {
	float a;
	int   b;
} limagesClusteringInfo;

typedef enum limagesClusteringMode {
	a=0,
	b=1
} limagesClusteringMode;
*/

int
main(int argc, char* argv[]) 
{
	imagesClusteringInfo info;

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
