/*
# clusterShow : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : clusterShow
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
#include "Memory.h"
#include "Cluster.h"


typedef struct clusterList {
	char* filename;
	int   num;
	float posX;
	float posY;
	int clusterSize;
	int clusterNumber;
} clusterList;


extern int compareX(const void* x, const void* y);
extern int compareY(const void* x, const void* y);

int compareX(const void* x, const void* y)
{
	clusterList* a;
	clusterList* b;

	a = (clusterList*)x;
	b = (clusterList*)y;
	if(a->posX<b->posX) {
		return -1;
	} else if(a->posX>b->posX) {
		return 1;
	}else {
		return 0;
	}
}

int compareY(const void* x, const void* y)
{
	clusterList* a;
	clusterList* b;

	a = (clusterList*)x;
	b = (clusterList*)y;
	if(a->posY<b->posY) {
		return 1;
	} else if(a->posY>b->posY) {
		return -1;
	}else {
		return 0;
	}
}

int
main(int argc, char* argv[]) 
{
	clusterShowInfo info;
	clusterLog* cluster=NULL;
	clusterLog2* cluster2=NULL;
	clusterTreeInfo linfo;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
	if(info.flagIn) {
		cluster = clusterLogReadAll(cluster, info.fptIn, 0);
	} else if(info.flagIn2) {
		cluster2 = clusterLog2ReadAll(cluster2, info.fptIn2, 0);
		DEBUGPRINT("Read\n")
		cluster  = clusterLogTransformLog2ToLog(cluster2, info.LastNum, 1);
		DEBUGPRINT1("ClusterSize in main: %d\n", cluster->bottom->clusterSize )
		DEBUGPRINT("Open\n")
#ifdef DEBUG
		{
			FILE* fpt;
			fpt = fopen("/tmp/test.log", "w");
			clusterLogWriteAll(cluster, fpt, 0);
			fclose(fpt);
		}
#endif
	} else if(info.flagInB) {
		cluster = clusterLogReadAllBinary(cluster, info.InB, 0);
	} else {
		usage(argv[0]);
	}

	DEBUGPRINT("InformationSet-Start\n");
	if(info.flagLastNum) {
		DEBUGPRINT1("ClusterSize in main before InformationSet: %d\n", cluster->bottom->clusterSize);
		if(info.flagIn2) {
			clusterLogClusterInformationSet(cluster, info.LastNum, 1);
		} else {
			clusterLogClusterInformationSet(cluster, info.LastNum, 0);
		}
		DEBUGPRINT1("ClusterSize in main after  InformationSet: %d\n", cluster->bottom->clusterSize);
	} else {
		if(info.flagIn2) {
			clusterLogClusterInformationSet(cluster, 0, 1);
		} else {
			clusterLogClusterInformationSet(cluster, 0, 0);
		}
	}

	linfo.flagFPTTreeInfo = info.flagTreeInfo;
	linfo.fptTreeInfo = info.fptTreeInfo;

	DEBUGPRINT("Out-Start\n");

	if(info.flagOut) {
		clusterLogWriteAll(cluster, info.fptOut, info.mode);
	}
	if(info.flagOut2) {
		clusterLogWriteClusterOnly(cluster, info.fptOut2, info.mode);
	}
	if(info.flagOutPS) {
		DEBUGPRINT1("ClusterSize in main: %d\n", cluster->bottom->clusterSize )
		linfo.posX = info.PosX;	
		linfo.posY = info.PosY;	
		linfo.ArmScale = info.ArmScale;	
		linfo.ShoulderScale = info.ShoulderScale;	
		linfo.ArmOffset = info.Offset;
		linfo.flagLog = info.Log;		
		linfo.flagScaling = info.Scaling;
		linfo.In          = info.InList;
		linfo.argv        = argv;
		linfo.argc        = argc;

		DEBUGPRINT2("Scale: %f %f\n", info.ArmScale,  info.ShoulderScale);	
		DEBUGPRINT2("Scale: %f %f\n", linfo.ArmScale,  linfo.ShoulderScale);	
		clusterLogWritePS(cluster, &linfo, info.fptOutPS, info.mode);
		if(info.flagOutOL || info.flagOutAL) {
			clusterList* tmp;
			tmp = (clusterList*)memoryAllocate(sizeof(clusterList)*info.flagInList, "in main");

			for(i=0; i<info.flagInList; i++) {
				tmp[i].num = i;
				tmp[i].filename = linfo.In[i];
				tmp[i].posY = linfo.InPosY[i];
				tmp[i].posX = linfo.InPosX[i];
				tmp[i].clusterSize   = linfo.clusterSize[i];
				tmp[i].clusterNumber = linfo.clusterNumber[i];
			}

			qsort(tmp, info.flagInList, sizeof(clusterList), compareY);
			if(info.flagOutOL) {
				for(i=0; i<info.flagInList; i++) {
					fprintf(info.fptOutOL, "%s %d %f %f \n", tmp[i].filename, tmp[i].num, tmp[i].posY, tmp[i].posX);
				}
			}

			if(info.flagOutAL) {
				for(i=0; i<info.flagInList; i++) {
					fprintf(info.fptOutAL, "%s.%s %d %f %f %d %d\n", tmp[i].filename, info.OutALSuffix, tmp[i].num, \
						tmp[i].posY, tmp[i].posX, tmp[i].clusterNumber, tmp[i].clusterSize);
				}
			}
		}
	}

#ifdef DEBUG
		{
			FILE* fpt;
			fpt = fopen("/tmp/test.log-log", "w");
			clusterLogWriteAll(cluster, fpt, 0);
			fclose(fpt);
		}
#endif
	DEBUGPRINT("End\n")
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

