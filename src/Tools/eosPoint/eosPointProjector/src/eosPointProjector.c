/*
# eosPointProjector : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosPointProjector
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
#include "eosPoint.h"

/*
Example:
typedef struct leosPointProjectorInfo {
	float a;
	int   b;
} leosPointProjectorInfo;

typedef enum leosPointProjectorMode {
	a=0,
	b=1
} leosPointProjectorMode;
*/

int
main(int argc, char* argv[]) 
{
	eosPointProjectorInfo info;
	int i;
    eosPoint p;
	eosPoint* pList;
	char s[STRING_MAX_LENGTH];

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	if(info.flagIn||info.flagInList) { 
		if(info.flagIn) {
			eosPointRead(info.fptIn, &p, info.InType);
		} else {
			if(!info.flagOutList) {
				fprintf(stderr, "Need -O\n");
				usage(argv[0]);
				exit(EXIT_FAILURE);
			}
			pList   = (eosPoint*) memoryAllocate(sizeof(eosPoint)*info.flagInList, "in main");
			for(i=0; i<info.flagInList; i++) {
				eosPointRead(info.fptInList[i], &(pList[i]), info.InType);
			}
		}
	} else {
		fprintf(stderr, "Need -i or -I\n");
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	if(info.flagIn) {
		eosPointProject(&p, info.mode);
	}
	if(info.flagInList) {
		for(i=0; i<info.flagInList; i++) {
			eosPointProject(&(pList[i]), info.mode);
		}
	}

	if(info.flagOut) {
		eosPointWrite(info.fptOut, &p, info.OutType);
	} else if(info.flagOutList) {
		for(i=0; i<info.flagOutList; i++) {
			eosPointWrite(info.fptOutList[i], &(pList[i]), info.OutType);
		}
	} 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">> eosPointFileType\n");
	eosPointFileFormatUsage(stderr);
	fprintf(stderr, ">> mode\n");
	fprintf(stderr, "0: x-projection\n");
	fprintf(stderr, "1: y-projection\n");
	fprintf(stderr, "2: z-projection\n");
}
