/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfDeterminationFromMultiImage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfDeterminationFromMultiImage
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfDeterminationFromMultiImage ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "ctfInfo.h"

typedef struct lctfDeterminationFromMultiImageInfoElement {
	char*   filename;
	ctfInfo ctf;
} lctfDeterminationFromMultiImageInfoElement;

typedef struct lctfDeterminationFromMultiImageInfo {
	int                                         n;
	lctfDeterminationFromMultiImageInfoElement* A;	
} lctfDeterminationFromMultiImageInfo;

typedef enum lctfDeterminationFromMultiImageMode {
	a=0,
	b=1
} lctfDeterminationFromMultiImageMode;

int
main(int argc, char* argv[]) 
{
	ctfDeterminationFromMultiImageInfo info;

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
	fprintf(stderr, "----- InFile format: -i or -i2 \n");
	fprintf(stderr, "filename defocus[A] AmpOverPhase kV Cs Cc Ai I SN MTFMode MTF MTF2 MolecEnv Magnification\n");
}


