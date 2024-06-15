/*
   # %M% %Y% %I%
   # The latest update : %G% at %U%
   #
   #%Z% mrcImageTransformDescartesIntoPolar ver %I%
   #%Z% Created by 
   #%Z%
   #%Z% Usage : mrcImageTransformDescartesIntoPolar
   #%Z% Attention
   #%Z%
*/
static char __sccs_id[] = "%Z%mrcImageTransformDescartesIntoPolar ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageSymmetryFind.h"
#include "lmrcImageTransformDescartesIntoPolar.h"
#include "lDescartesIntoPolar.h"


int
main(int argc, char* argv[]) 
{
    mrcImage in;
    mrcImage out;
    mrcImageTransformDescartesIntoPolarInfo info;
    lmrcImageTransformDescartesIntoPolarInfo linfo;
    lDescartesIntoPolarInfo linfo2;
    
    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
    
    DEBUGPRINT("Program Start\n");

    mrcFileRead(&in,info.In,"in main",0);

	linfo.dr     = info.dr;
	linfo.dphi   = info.dphi*RADIAN;
	linfo.dtheta = info.dtheta*RADIAN;
	switch(info.mode) {
		case 0: {
			linfo.flagImageCentreIsGravityCentre = 1;
			linfo.flagDescartesIntoPolarInfo = 0;
			break;
		}
		case 1: {
			linfo.flagImageCentreIsGravityCentre = 0;
			linfo.flagDescartesIntoPolarInfo = 1;
			linfo2.centre.x = info.cx;
			linfo2.centre.y = info.cy;
			linfo2.centre.z = info.cz;
			linfo2.xaxis.x  = info.xx;
			linfo2.xaxis.y  = info.xy;
			linfo2.xaxis.z  = info.xz;
			linfo2.zaxis.x  = info.zx;
			linfo2.zaxis.y  = info.zy;
			linfo2.zaxis.z  = info.zz;
			linfo.flagrWeight = info.rweight;
			break;
		}
		default: {
			usage(argv[0]);
			exit(EXIT_FAILURE);
			break;
		}
	}
    lmrcImageTransformDescartesIntoPolar(&out, &in, &linfo, &linfo2, 0);

    mrcFileWrite(&out,info.Out,"in main",0);
    
    exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
  fprintf(stderr, "----- Additional Usage -----\n");
  fprintf(stderr, ">>>>> -m \n");
  fprintf(stderr, "         0 : Image centre is gravity of centre of image.\n");
  fprintf(stderr, "         1 : Image centre is defined by the options of -axis -centre. \n");
}

