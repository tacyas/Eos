/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% muscleSimulation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : muscleSimulation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%muscleSimulation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Random.h"

typedef double nodeParaTypeReal;

typedef enum nodeMode {
	nodeModeMove=0,
	nodeModeNoMove=1
} nodeMode;

typedef struct node {
	int   ID;
	char*  name;
	double x;
	double y;
	double z;
	nodeMode    mode;
} node;

typedef enum interactionMode {
	interactionModeSolid = 0,
	interactionModeHalfSpring = 1,
	interactionModeLenardJonesPotential =2
} interactionMode;

typedef struct interaction {
	interactionMode mode;
} interaction;

typedef struct lmuscleSimulation {
	int   nNode;
	node* n;
	double T; /* [K] */
} lmuscleSimulation;

void
main(int argc, char* argv[]) 
{
	muscleSimulationInfo info;
	lmuscleSimulationInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	switch(info.mode) {
		case 0: {
			lmuscleSimulationMyosinModelSet(&linfo);	
			break;
		}
		default: {
			break;
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m \n");
	fprintf(stderr, "   0: myosin model\n");
	fprintf(stderr, "   1: actin  model\n");
	fprintf(stderr, "   2: actomyosin model\n");
}

void
lmuscleSimulationMyosinModelSet(&linfo)
{
	linfo->nNode = 5;
	linfo->n     = (node*)memoryAllocate(sizeof(node)*linfo->nNode, "in lmuscleSimulationMyosinModelSet");

	linfo->n[0].ID = 1;
	linfo->n[0].name = strdup("Ma");
	linfo->n[0].x  = 5;
	linfo->n[0].y  = 30;
	linfo->n[0].z  = 0;
	linfo->n[0].mode  = nodeModeMove;

	linfo->n[1].ID = 2;
	linfo->n[1].name = strdup("Mb");
	linfo->n[1].x  = 5;
	linfo->n[1].y  = 15;
	linfo->n[1].z  = 0;
	linfo->n[1].mode  = nodeModeMove;

	linfo->n[1].ID = 3;
	linfo->n[1].name = strdup("Mc");
	linfo->n[1].x  = 0;
	linfo->n[1].y  = 30;
	linfo->n[1].z  = 0;
	linfo->n[1].mode  = nodeModeMove;

	linfo->n[1].ID = 4;
	linfo->n[1].name = strdup("Md");
	linfo->n[1].x  = 0;
	linfo->n[1].y  = 15;
	linfo->n[1].z  = 0;
	linfo->n[1].mode  = nodeModeMove;

	linfo->n[1].ID = 5;
	linfo->n[1].name = strdup("Me");
	linfo->n[1].x  = 0;
	linfo->n[1].y  = 0;
	linfo->n[1].z  = 0;
	linfo->n[1].mode  = nodeModeNoMove;
}
