/*
# clusterLogRead : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : clusterLogRead 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
/*
#include <values.h>
*/
#include "Memory.h"
#include "eosString.h"
#include "../inc/Cluster.h"
#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

clusterLog2OneRecord*
clusterLog2Read(clusterLog2* cluster, FILE* fpt, int mode)
{
	char  s[1024];
	char* stmp;
	clusterLog2OneRecord* tmp;

	stmp=stringGetFromFile(s, "clusterLog2Read", fpt, stdout, 3);
	if(NULL==stmp) {
		return NULL;
	} 

	if(NULL==cluster->current) {           /* Top */
		cluster->current = clusterLog2InitOneRecord(cluster->current, 0);	
        cluster->current->prev = NULL;
        cluster->current->next = NULL;
        cluster->top           = cluster->current;
        cluster->bottom        = cluster->current;
    } else { 
		if(NULL==cluster->current->next) { /* Bottom */
			cluster->current->next = clusterLog2InitOneRecord(cluster->current->next, 0);	
        	cluster->current->next->prev   = cluster->current;
        	cluster->current->next->next   = NULL;
        	cluster->current = cluster->current->next;
			cluster->bottom  = cluster->current;
    	} else { /* On the way */
			tmp = cluster->current->next;
			cluster->current->next = clusterLog2InitOneRecord(cluster->current->next, 0);	
        	cluster->current->next->prev   = cluster->current;
        	cluster->current->next->next   = tmp;
			cluster->current = cluster->current->next;
		}
	}
    cluster->current->N        = stringGetNthIntegerData(s, 3, " \t,");
    cluster->current->M        = stringGetNthIntegerData(s, 4, " \t,");
    cluster->current->distance = stringGetNthRealData   (s, 5, " \t,");
    cluster->current->linearCorrelation = stringGetNthRealData(s, 6, " \t,");

#ifdef DEBUG2
	fprintf(stderr, "%d %d %f %f\n", cluster->current->N, cluster->current->M,
			                         cluster->current->distance,
									 cluster->current->linearCorrelation);
#endif
	return cluster->current;
}

clusterLogOneRecord*
clusterLogRead(clusterLog* cluster, FILE* fpt, int mode)
{
	char  s[1024];
	char* stmp;
	clusterLogOneRecord* tmp;

	stmp=stringGetFromFile(s, "clusterLogRead", fpt, stdout, 3);
	if(NULL==stmp) {
		return NULL;
	} 

	if(NULL==cluster->current) {           /* Top */
		cluster->current = clusterLogInitOneRecord(cluster->current, 0);	
        cluster->current->prev = NULL;
        cluster->current->next = NULL;
        cluster->top           = cluster->current;
        cluster->bottom        = cluster->current;
    } else { 
		if(NULL==cluster->current->next) { /* Bottom */
			cluster->current->next = clusterLogInitOneRecord(cluster->current->next, 0);	
        	cluster->current->next->prev   = cluster->current;
        	cluster->current->next->next   = NULL;
        	cluster->current = cluster->current->next;
			cluster->bottom  = cluster->current;
    	} else { /* On the way */
			tmp = cluster->current->next;
			cluster->current->next = clusterLogInitOneRecord(cluster->current->next, 0);	
        	cluster->current->next->prev   = cluster->current;
        	cluster->current->next->next   = tmp;
			cluster->current = cluster->current->next;
		}
	}
    cluster->current->N        = stringGetNthIntegerData(s, 1, " \t,");
    cluster->current->M        = stringGetNthIntegerData(s, 2, " \t,");
    cluster->current->prevN    = stringGetNthIntegerData(s, 3, " \t,");
    cluster->current->prevM    = stringGetNthIntegerData(s, 4, " \t,");
    cluster->current->distance = stringGetNthRealData(s, 5, " \t,");

#ifdef DEBUG2
	clusterLogWriteOneRecord(cluster->current, stderr, 0);
#endif 
	return cluster->current;
}

clusterLog2*
clusterLog2ReadAll(clusterLog2* cluster, FILE* fpt, int mode)
{
	clusterLog2OneRecord* last = NULL;
	int i = 0;

	cluster = clusterLog2Init(cluster, 0);
	while(NULL != (last=clusterLog2Read(cluster, fpt, mode))) {
		DEBUGPRINT1("Counter: %d \n", i);
		i++;
	}
	return cluster;
}

clusterLog*
clusterLogReadAll(clusterLog* cluster, FILE* fpt, int mode)
{
	clusterLogOneRecord* last = NULL;
	
	DEBUGPRINT("----- clusterLog Read Start -----");
	cluster = clusterLogInit(cluster, 0);
	while(NULL != (last=clusterLogRead(cluster, fpt, mode))) {
	}
	DEBUGPRINT("----- clusterLog Read End -----");
	return cluster;
}


clusterLog*
clusterLogReadAllBinary(clusterLog* cluster, char* basename, int mode)
{
	clusterLogOneRecord* last = NULL;
	char filename[1024];
	clusterTypeInteger N;	
	clusterTypeInteger prevN, prevM;
	FILE* fpt=NULL;

	N = 1; 
	while(N<1e8) {
		 sprintf(filename, CLUSTERLOG_BINARY_FILENAME_FORMAT, basename, N, N, N);	
		 fpt = fopen(filename, "r");
		 if(NULL!=fpt) {
		 	fclose(fpt);
			break;
		 } 
		 N++;
	}
	if(NULL==fpt) {
		return NULL;
	}

	prevN = N;
	prevM = N;
	cluster = clusterLogInit(cluster, 0);
	while(NULL!=(last=clusterLogReadBinary(cluster, &prevN, &prevM, filename, mode))) {
		fprintf(stderr, "%s -> prevN %d prevM %d N %d\n", filename, prevN, prevM, N-1);
		cluster->current = last;
		N--;
		sprintf(filename,  CLUSTERLOG_BINARY_FILENAME_FORMAT, basename, prevN, prevM, N);
	}

	return cluster;
}


clusterLogOneRecord*
clusterLogReadBinary(clusterLog* cluster, clusterTypeInteger* N, clusterTypeInteger* M, char* filename, int mode)
{
	clusterLogOneRecord* tmp;
	mrcImage in;
	mrcImageParaTypeReal x, y;
	double data;
	double min;
	int prevN, prevM;
	FILE* fpt;

	fpt = fopen(filename, "r");
	if(NULL==fpt) {
		return NULL;
	} else {	
		fclose(fpt);
	}
	mrcFileRead(&in, filename, "in  clusterLogReadBinary", 0);

	min  = MAXFLOAT;
	prevN = *N;
	prevM = *M;
	for(x=0; x<in.HeaderN.x; x++) {	
	for(y=0; y<x; y++) {
		mrcPixelDataGet(&in, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
	
		/* Calculation Check */
		if(fabs(CLUSTERLOG_BINARY_NO_CALCULATION_VALUE-data)<1e-6) {
			mrcImageFree(&in, 0);
			return NULL;
		}

		if(NULL==cluster->current) { /* Top */
    		cluster->current = clusterLogInitOneRecord(cluster->current, 0);
        	cluster->current->prev   = NULL;
        	cluster->current->next   = NULL;
        	cluster->top    = cluster->current;
        	cluster->bottom = cluster->current;
    	} else {
			if(NULL==cluster->current->next) { /* Bottom */
    			cluster->current->next = clusterLogInitOneRecord(cluster->current->next, 0);
        		cluster->current->next->prev   = cluster->current;
        		cluster->current->next->next   = NULL;
	        	cluster->current = cluster->current->next;
				cluster->bottom = cluster->current;
	    	} else { /* On the way */
				tmp = cluster->current->next;
    			cluster->current->next = clusterLogInitOneRecord(cluster->current->next, 0);
	        	cluster->current->next->prev   = cluster->current;
	        	cluster->current->next->next   = tmp;
				cluster->current = cluster->current->next;
			}
		}
	    cluster->current->N = x; 
	    cluster->current->M = y; 
	    cluster->current->prevN = prevN;
	    cluster->current->prevM = prevM;
	    cluster->current->distance = data;

		if(data<min) {
			min = data;
			*N = x;
			*M = y;
		}
	}
	}
	mrcImageFree(&in, 0);
	return cluster->current;
}
