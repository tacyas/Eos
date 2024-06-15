/*
# clusterLogASCII2Binary : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : clusterLogASCII2Binary
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
#include "File.h"
#include "Cluster.h"

/*
Example:
typedef struct lclusterLogASCII2BinaryInfo {
	float a;
	int   b;
} lclusterLogASCII2BinaryInfo;

typedef enum lclusterLogASCII2BinaryMode {
	a=0,
	b=1
} lclusterLogASCII2BinaryMode;
*/

int
main(int argc, char* argv[]) 
{
	clusterLog* cluster=NULL;
	clusterLogASCII2BinaryInfo info;
	FILE* fpt;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	cluster = clusterLogReadAll(cluster, info.fptIn, 0);

	clusterLogWriteAllBinary(cluster, info.Out, 0);

	fpt = fileOpen(info.Out, "w");
	clusterLogWriteAllBinary2(cluster, fpt, 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
