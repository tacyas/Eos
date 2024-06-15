/*
# eosPointPositionCorrection : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosPointPositionCorrection
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

#undef DEBUG
#include "genUtil.h"
#include "eosPoint.h"

#include "leosPointPositionCorrection.h"

int
main(int argc, char* argv[]) 
{
	eosPointPositionCorrectionInfo info;
	leosPointPositionCorrectionInfo linfo;
    eosPoint inP;
    eosPoint outP;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    eosPointRead(info.fptIn, &inP, info.InType);
    
    linfo.n = info.N;
    leosPointPositionCorrection(&outP, &inP, &linfo, info.mode);
    
    eosPointWrite(info.fptOut, &outP, info.OutType);
    if(info.flagOutDelta) {
        eosPointWrite(info.fptOutDelta, &(linfo.db), 0);
    }
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
    eosPointFileFormatUsage(stderr);
}

