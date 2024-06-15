/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageROI ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageROI
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageROI ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageROI2D.h"

int
main(int argc, char* argv[]) 
{
	mrcImageROIInfo info;
	mrcImage in;
	mrcImage out;
	lmrcImageSingleROIInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
    mrcFileRead(&in, info.In, "main routine", 0);
	
	linfo.FileName = info.In;
	linfo.Shape = info.ROIShapeMode;
	linfo.mode  = mrcFloatImage;

    if(info.flagblx && info.flagbly 
	 &&info.flagbrx && info.flagbry 
	 &&info.flagtlx && info.flagtly 
	 &&info.flagtrx && info.flagtry) {
		linfo.blx = info.blx;
		linfo.bly = info.bly;
		linfo.brx = info.brx;
		linfo.bry = info.bry;
		linfo.tlx = info.tlx;
		linfo.tly = info.tly;
		linfo.trx = info.trx;
		linfo.try = info.try;
	} else {	
		linfo.blx = 0.0;
		linfo.bly = 0.0;
		linfo.brx = in.HeaderN.x - 1.0;
		linfo.bry = 0.0;
		linfo.tlx = 0.0;
		linfo.tly = in.HeaderN.y - 1.0;
		linfo.trx = in.HeaderN.x - 1.0;
		linfo.try = in.HeaderN.y - 1.0;
	}

	if(info.flagShrink) {
		linfo.blx *= info.Shrink;	
		linfo.bly *= info.Shrink;	
		linfo.brx *= info.Shrink;	
		linfo.bry *= info.Shrink;	
		linfo.tlx *= info.Shrink;	
		linfo.tly *= info.Shrink;	
		linfo.trx *= info.Shrink;	
		linfo.try *= info.Shrink;
	}

	if(info.flagShiftX || info.flagShiftY) {
		linfo.blx += info.ShiftX;	
		linfo.bly += info.ShiftY;	
		linfo.brx += info.ShiftX;	
		linfo.bry += info.ShiftY;	
		linfo.tlx += info.ShiftX;	
		linfo.tly += info.ShiftY;	
		linfo.trx += info.ShiftX;	
		linfo.try += info.ShiftY;
	}

	if(info.flagAngle) {
		linfo.flagRotation = 1;
	} else {
		linfo.flagRotation = 0;
	}
	linfo.angle = info.Angle*RADIAN;

	if(info.flagWidthBeforeExpansion) {
		linfo.flagWidth = 1;
		linfo.width     = info.WidthBeforeExpansion;
	} else {
		linfo.flagWidth = 0;
	}
	if(info.flagHeightBeforeExpansion) {
		linfo.flagHeight = 1;
		linfo.height = info.HeightBeforeExpansion;
	} else {
		linfo.flagHeight = 0;
	}

	if(info.flagWidthAfterExpansion) {
		linfo.flagMagnifiedWidth = 1;
		linfo.magnifiedWidth     = info.WidthAfterExpansion;
	} else {
		linfo.flagMagnifiedWidth = 0;
	}
	if(info.flagHeightAfterExpansion) {
		linfo.flagMagnifiedHeight = 1;
		linfo.magnifiedHeight = info.HeightAfterExpansion;
	} else {
		linfo.flagMagnifiedHeight = 0;
	}

	if (!(info.flagHeightAfterExpansion) 
	   && info.flagtruePitch 
	   && info.flagdY 
	   && info.flagLy) {
		linfo.flagLayerLine = 1;
		linfo.truePitch = info.truePitch;
		linfo.Ly        = info.Ly;
		linfo.dY        = info.dY;
	} else {
		linfo.flagLayerLine = 0;
	}

    lmrcImageSingleROI(&out, &in, &linfo, info.mode);

	DEBUGPRINT("mrcFileWrite\n");
    mrcFileWrite(&out, info.Out, "main routine", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "---- mode ----\n");
	fprintf(stderr, "\t0: Nearest Neighbor Method\n");
	fprintf(stderr, "\t1: Bilinear method\n");
	fprintf(stderr, "\t2: Cubic Convolution method\n");
	fprintf(stderr, "\t3: Polynominal method\n");
	fprintf(stderr, "---- ROI Shape Mode ----\n");
	fprintf(stderr, "\t%d: Rect\n", Rect);
	fprintf(stderr, "\t%d: TiltRect\n", TiltRect);
	fprintf(stderr, "---- Note  (Magnification change for normalize)----\n");
	fprintf(stderr, "-truePitch, -dY and -Ly options make \n");
	fprintf(stderr, "H[pixel] = truePitch[A] / Ly[A/pixel] x dY \n");
}

