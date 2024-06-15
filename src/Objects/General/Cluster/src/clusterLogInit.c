/*
# clusterLogInit : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : clusterLogInit 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include "Memory.h"
#include "../inc/Cluster.h"

clusterLog*
clusterLogInit(clusterLog* cluster, int mode)
{
	if(NULL==cluster) {
		cluster = (clusterLog*)memoryAllocate(sizeof(clusterLog)*1, "in clusterLogInit");
	}
	cluster->top     = NULL;
	cluster->bottom  = NULL;
	cluster->current = NULL;

	return cluster;
}

clusterLog2*
clusterLog2Init(clusterLog2* cluster, int mode)
{
	if(NULL==cluster) {
		cluster = (clusterLog2*)memoryAllocate(sizeof(clusterLog2)*1, "in clusterLogInit");
	}
	cluster->top     = NULL;
	cluster->bottom  = NULL;
	cluster->current = NULL;

	return cluster;
}

clusterLogOneRecord*
clusterLogInitOneRecord(clusterLogOneRecord* cluster, int mode)
{
	if(NULL==cluster) {
		cluster = (clusterLogOneRecord*)memoryAllocate(sizeof(clusterLogOneRecord)*1, "in clusterLogInitOneRecord");
	}
	cluster->clusterSize      = -1;	
	cluster->upperLayer      = NULL;	
	cluster->belowLayer      = NULL;	
	cluster->belowLayerStart = NULL;	
	cluster->belowLayerEnd   = NULL;	
	cluster->belowLayerForN  = NULL;	
	cluster->belowLayerForM  = NULL;	

	return cluster;
}

clusterLog2OneRecord*
clusterLog2InitOneRecord(clusterLog2OneRecord* cluster, int mode)
{
	if(NULL==cluster) {
		cluster = (clusterLog2OneRecord*)memoryAllocate(sizeof(clusterLog2OneRecord)*1, "in clusterLogInitOneRecord");
	}
	return cluster;
}
