/*
# mrc2bild : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrc2bild
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
#include "mrcImage.h"
#include "bildFile.h"

int
main(int argc, char* argv[]) 
{
	mrc2bildInfo info;
	mrcImage     in[3];
	lmrc2bildInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	switch(info.mode) {
		case lmrc2bildModeArrows: {
			if(info.flagIn0) {
				mrcFileRead(&in[0], info.In0, "in main", 0);
				mrcFileRead(&in[1], info.In1, "in main", 0);
				mrcFileRead(&in[2], info.In2, "in main", 0);
			} else {
				fprintf(stderr, "need -i3\n"); 
				usage(argv[0]);
			}
			break;
		}
		case lmrc2bildModeSpheres: {
			if(info.flagIn) {
				mrcFileRead(&in[0], info.In, "in main", 0);
			} else {
				fprintf(stderr, "need -i\n"); 
				usage(argv[0]);
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %ld\n", info.mode);
			exit(EXIT_FAILURE);
		}
	}

	linfo.color[0] = info.Red;
	linfo.color[1] = info.Green;
	linfo.color[2] = info.Blue;
	linfo.zoom     = info.Zoom;
	linfo.r1 = info.R1;
	linfo.r2 = info.R2;
	linfo.rho = info.Rho;
	linfo.flagSkip = info.flagskipX;
	linfo.skipX    = info.skipX;
	linfo.skipY    = info.skipY;
	linfo.skipZ    = info.skipZ;

  linfo.flagRainbow = info.flagRainbowMode; 
  linfo.RainbowMode = info.RainbowMode; 
  linfo.flagRainbowThresLow = info.flagRainbowThresLow;
  linfo.RainbowThresLow  = info.RainbowThresLow;
  linfo.flagRainbowThresHigh = info.flagRainbowThresHigh;
  linfo.RainbowThresHigh= info.RainbowThresHigh;
  linfo.flagRainbowRangeLow = info.flagRainbowRangeLow;
  linfo.RainbowRangeLow  = info.RainbowRangeLow;
  linfo.flagRainbowRangeHigh = info.flagRainbowRangeHigh;
  linfo.RainbowRangeHigh= info.RainbowRangeHigh;

  linfo.flagRangeX = info.flagRangeXMin;
  if(info.flagRangeXMin) {
      linfo.RangeXMin  = info.RangeXMin;
      linfo.RangeXMax  = info.RangeXMax;
  }
  linfo.flagRangeY = info.flagRangeYMin;
  if(info.flagRangeYMin) {
      linfo.RangeYMin  = info.RangeYMin;
      linfo.RangeYMax  = info.RangeYMax;
  }
  linfo.flagRangeZ = info.flagRangeZMin;
  if(info.flagRangeZMin) {
      linfo.RangeZMin  = info.RangeZMin;
      linfo.RangeZMax  = info.RangeZMax;
  }
  linfo.flagRangeR = info.flagRangeRR;
  if(info.flagRangeRR) {
      linfo.RangeRR = info.RangeRR;
      linfo.RangeRCX = info.RangeRCX;
      linfo.RangeRCY = info.RangeRCY;
      linfo.RangeRCZ = info.RangeRCZ;
  }
    DEBUGPRINT3("RangeX: %d %d %d\n", linfo.flagRangeX, linfo.RangeXMin, linfo.RangeXMax);
    DEBUGPRINT3("RangeY: %d %d %d\n", linfo.flagRangeY, linfo.RangeYMin, linfo.RangeYMax);
    DEBUGPRINT3("RnageZ: %d %d %d\n", linfo.flagRangeZ, linfo.RangeZMin, linfo.RangeZMax);
	lmrc2bild(info.fptOut, in, linfo, info.mode);
	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrc2bildUsage(stderr);
}


