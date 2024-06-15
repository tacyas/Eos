/*
# clusterLog2ToLog : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : clusterLog2ToLog
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
#include "Cluster.h"


int
main(int argc, char* argv[]) 
{
	clusterLog2ToLogInfo info;
	clusterLog2* cluster2;
	clusterLog* cluster;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	cluster2 = clusterLog2ReadAll(cluster2, info.fptIn, 0);

	cluster = clusterLogTransformLog2ToLog(cluster2, info.lastNum, info.mode); 

	clusterLogWriteAll(cluster, info.fptOut, info.mode);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
