/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageDisplayDensityAsTempFactor ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageDisplayDensityAsTempFactor
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageDisplayDensityAsTempFactor ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "pdbInfoGet.h"

void lmrcImageDisplayAsTempFactor(pdbFile* pdb, mrcImage* in, double v, double H, double L, long flagH, long flagL, int mode);



int
main(int argc, char* argv[]) 
{
	mrcImageDisplayDensityAsTempFactorInfo info;

/* variables */
	pdbFile pdb;
	mrcImage in;
	pdbInfoData pdbinfo;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in ,info.In ,"in main" ,0);
	pdbFileRead(info.fptPdb, &pdb);
	pdbInfoGet(&pdb, &pdbinfo, 0);

/* begin */

	DEBUGPRINT("Program Start\n");
	lmrcImageDisplayAsTempFactor(&pdb, &in, info.Value, info.H, info.L, info.flagH, info.flagL, info.mode);
	pdbFileWrite(info.fptOut, &pdb);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageDisplayAsTempFactor(pdbFile* pdb, mrcImage* in, double v, double H, double L, long flagH, long flagL, int mode)
{
  
/* variables */
  double data,x,y,z;
  float px,py,pz;

/* begin */
  pdbFileTop(pdb);
  while(1) {
    if(pdbFileIsAtom(pdb)) {
      pdbFileCoordGet(pdb, &px, &py, &pz);

  /*
      x=(px / in->HeaderLength.x);
      y=(py / in->HeaderLength.y);
      z=(pz / in->HeaderLength.z);
      mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
	  */
      mrcImageDataGetbyAU(in, px, py, pz, &data, mrcPixelRePart, mrcPixelHowNearest); 
	DEBUGPRINT4("%f %f %f %f\n", px, py, pz, data); 

      data *= v;
      if (flagH){
	if (data > H){
	  data=H;
	}
      }
      if (flagL){
	if (data < L){
	  data=L;
	}
      }
      pdb->PDB->TemperatureFactor = data;
   }
    if(pdbFileEnd(pdb)) {
      break;
    } else {
      pdbFileNext(pdb);
    }
  }    
}




