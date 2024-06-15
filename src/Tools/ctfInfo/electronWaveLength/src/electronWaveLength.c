/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% electronWaveLength ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : electronWaveLength
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%electronWaveLength ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "ctfInfo.h"

/*
Example:
typedef struct lelectronWaveLengthInfo {
	float a;
	int   b;
} lelectronWaveLengthInfo;

typedef enum lelectronWaveLengthMode {
	a=0,
	b=1
} lelectronWaveLengthMode;
*/

int
main(int argc, char* argv[]) 
{
	electronWaveLengthInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	fprintf(info.fptOut, "wavelength[A]: %g\n", wavelengthOfElectron(info.kV*1e3)*1e10);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
