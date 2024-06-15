/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageVolumeCalc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageVolumeCalc
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageVolumeCalc ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "nr2.h"
#include "lmrcImageVolumeCalc.h"

extern void lmrcImageVolumeCalcPrepare(lmrcImageVolumeCalcInfo* linfo, mrcImageVolumeCalcInfo info, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImage img;
	mrcImageVolumeCalcInfo   info;
	lmrcImageVolumeCalcInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	lmrcImageVolumeCalcPrepare(&linfo, info, info.mode);
	mrcFileRead(&img, info.In, "in main", 0);
	DEBUGPRINT3("%f,%f,%f ", img.HeaderLength.x, img.HeaderLength.y, img.HeaderLength.z);

	/* Calculcation */
	lmrcImageVolumeCalc(&img, &linfo, info.mode);

	/* Output */	
	lmrcImageVolumeCalcPrint(info.fptOut, &linfo, info.mode);

	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-format \n");
	fprintf(stderr, " 1st double  # ContourLevel[%%] \n");
	fprintf(stderr, " 2nd double  # Contour[value]\n");
	fprintf(stderr, " 3rd int     # VolumeNumber [fromBlack]\n");
	fprintf(stderr, " 4th int     # VolumeNumber [fromWhite]  ; Default : omiited \n");
	fprintf(stderr, " 5th double  # Volume[A^3]               ; Default : omitted \n");
}

void
lmrcImageVolumeCalcPrepare(lmrcImageVolumeCalcInfo* linfo, mrcImageVolumeCalcInfo info, int mode)
{
	int i;
	double scal;

	linfo->Inverse   = info.Inverse;
	linfo->nMolecule = info.nMolecule;
	linfo->Density   = info.Density;
	linfo->MolecularWeight = info.MolecularWeight;

	/* For FORMAT */
	linfo->format = strdup(info.Format);
    DEBUGPRINT1("%s\n", linfo->format);
	linfo->MinVol   = info.MinVol/100.0;
	linfo->MaxVol   = info.MaxVol/100.0;
	linfo->DeltaVol = info.DeltaVol/100.0;

	linfo->flagDelta = info.flagDelta;
	linfo->Delta     = info.Delta;

	linfo->flagContourLevel = 0;
}

