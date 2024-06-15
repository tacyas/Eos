/*
# crystalGetLatticeVolume : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : crystalGetLatticeVolume
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
typedef struct lcrystalGetLatticeVolumeInfo {
	float a;
	int   b;
} lcrystalGetLatticeVolumeInfo;

typedef enum lcrystalGetLatticeVolumeMode {
	a=0,
	b=1
} lcrystalGetLatticeVolumeMode;
*/

int
main(int argc, char* argv[]) 
{
    CrystalInfo linfo;
	crystalGetLatticeVolumeInfo info;
    double V;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    if(info.flagIn) {
        crystalInfoRead(info.fptIn, &linfo, 0);
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
    if(info.flagcx) {
        linfo.cAxis.x = info.cx;
        linfo.cAxis.y = info.cy;
        linfo.cAxis.z = info.cz;
    }

    V = crystalInfoGetLatticeVolume(&linfo, info.mode);

    fprintf(info.fptOut, "Volume: %f\n", V); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
    fprintf(stderr, "> crystaInfo\n");
    crystalInfoFileFormat(stderr, 0);
}
