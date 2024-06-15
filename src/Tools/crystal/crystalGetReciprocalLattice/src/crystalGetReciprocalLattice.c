/*
# crystalGetReciprocalLattice : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : crystalGetReciprocalLattice
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
#include "Crystal.h"

/*
Example:
typedef struct lcrystalGetReciprocalLatticeInfo {
	float a;
	int   b;
} lcrystalGetReciprocalLatticeInfo;

typedef enum lcrystalGetReciprocalLatticeMode {
	a=0,
	b=1
} lcrystalGetReciprocalLatticeMode;
*/

int
main(int argc, char* argv[]) 
{
	crystalGetReciprocalLatticeInfo info;
    CrystalInfo linnfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    info(info.flagIn) {
        crystalFileRead(info.fptIn, &linfo, 0);
    }
    if(info.flagax) {
        linfo.aAxis.x = info.ax;
        linfo.aAxis.y = info.ay;
        linfo.aAxis.z = info.az;
    }

    if(info.flagbx) {
        linfo.bAxis.x = info.bx;
        linfo.bAxis.y = info.by;
        linfo.bAxis.z = info.bz;
    }

        linfo.cAxis.x = info.cx;
        linfo.cAxis.y = info.cy;
        linfo.cAxis.z = info.cz;
    }

    crystaGetReciprocalLattice(&linfo, info.mode);

    crystalInfoPrint(info.fptOut, linfo, 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
