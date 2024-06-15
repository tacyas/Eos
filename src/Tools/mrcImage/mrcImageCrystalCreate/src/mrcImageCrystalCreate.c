/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCrystalCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCrystalCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCrystalCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageCrystalCreate.h"

int
main(int argc, char* argv[]) 
{
	mrcImageCrystalCreateInfo  info;
	lmrcImageCrystalCreateInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);

	mrcFileRead(&in, info.In, "in main", 0);

	linfo.nx = info.nx;
	linfo.ny = info.ny;
	linfo.nz = info.nz;
  if(info.flagAX) {
	  linfo.ax = info.AX;
	  linfo.ay = info.AY;
	  linfo.az = info.AZ;
  } else {
    linfo.ax = in.HeaderN.x*in.HeaderLength.x;
    linfo.ay = 0;
    linfo.az = 0;
  }
  if(info.flagBX) {
	  linfo.bx = info.BX;
	  linfo.by = info.BY;
	  linfo.bz = info.BZ;
  } else {
    linfo.bx = 0;
    linfo.by = in.HeaderN.y*in.HeaderLength.y;
    linfo.bz = 0;
  }
  if(info.flagCX) {
	  linfo.cx = info.CX;
	  linfo.cy = info.CY;
	  linfo.cz = info.CZ;
  } else {
    linfo.cx = 0;
    linfo.cy = 0;
    linfo.cz = in.HeaderN.z*in.HeaderLength.z;
  }
  if(info.flagStartX) {
	  linfo.sx = info.StartX*in.HeaderLength.x;
	  linfo.sy = info.StartY*in.HeaderLength.y;
	  linfo.sz = info.StartZ*in.HeaderLength.z;
  } else {
	  linfo.sx = 0;
	  linfo.sy = 0;
	  linfo.sz = 0;
  }
  linfo.pixelMode = info.Mode;

  DEBUGPRINT3("A: %f %f %f\n", linfo.ax, linfo.ay, linfo.az);
  DEBUGPRINT3("B: %f %f %f\n", linfo.bx, linfo.by, linfo.bz);
  DEBUGPRINT3("C: %f %f %f\n", linfo.cx, linfo.cy, linfo.cz);
	lmrcImageCrystalCreate(&out, &in, &linfo); 

	mrcStatDataSet(&out, 0);
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

