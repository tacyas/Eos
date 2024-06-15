/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% molecularEnvelopeResampling ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : molecularEnvelopeResampling
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%molecularEnvelopeResampling ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "ctfInfo.h"

int
main(int argc, char* argv[]) 
{
	molecularEnvelopeResamplingInfo info;
	molecularEnvelope in;
	molecularEnvelope out;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	lmolecularEnvelopeFileRead(info.fptIn, &in, 0); 
	lmolecularEnvelopeResampling(&out, &in, info.dR, info.Rmax, 0);
	lmolecularEnvelopeFileWrite(info.fptOut, &out, 0); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
