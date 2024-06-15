/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageGaussDisc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageGaussDisc
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageGaussDisc ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcImageGaussDiscInfo {
	float sigmax;
	float sigmay;
	float sigma_range;
	float weight;
	float size;
	long mode;
	int flagWidth;
	float Width;
	int flagHeight;
	float Height;
	float CentreX;
	float CentreY;
	float Angle;
} lmrcImageGaussDiscInfo;

extern void lmrcImageGaussDisc(lmrcImageGaussDiscInfo* info, mrcImage* out);

int
main(int argc, char* argv[]) 
{
	mrcImageGaussDiscInfo info;
	lmrcImageGaussDiscInfo linfo;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.sigmax       = info.sigmax/info.size;
	linfo.sigmay       = info.sigmay/info.size;
	linfo.sigma_range  = info.sigma_range;
	linfo.weight       = info.weight;
	linfo.size         = info.size;
	linfo.mode         = info.mode;
	linfo.flagWidth    = info.flagWidth; 
	linfo.Width        = info.Width; 
	linfo.flagHeight   = info.flagHeight; 
	linfo.Height       = info.Height; 
	linfo.CentreX      = info.centrex;
	linfo.CentreY      = info.centrey;
	linfo.Angle        = info.Angle*RADIAN;

	lmrcImageGaussDisc(&linfo, &out);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Gauss Disc is cutted at sigma_range*sigma \n");
	fprintf(stderr, "Gauss Disc = weight * exp ( - ((x^2 / sigmax^2)+(y^2 / sigmay^2)) \n");
	fprintf(stderr, "mrcImageFileSize is (sigma_range*sigmax*2) x (sigma_range*sigmay*2) \n");
	fprintf(stderr, "-----------------------------------------------------------------------------------\n");
	fprintf(stderr, "mode 0 char \n");
	fprintf(stderr, "mode 2 float \n");

}

void
lmrcImageGaussDisc(lmrcImageGaussDiscInfo* linfo, mrcImage* out)
{
	mrcImageParaTypeReal    x,    y; /* Pixel */
	mrcImageParaTypeReal    srcx,    srcy; /* Pixel */
	mrcImageParaTypeReal cenx, ceny;
	double data;
	double angle;

	out->HeaderLength.x = linfo->size;
	out->HeaderLength.y = linfo->size;
	out->HeaderLength.z = 1;

	out->HeaderN.x = linfo->sigmax * linfo->sigma_range * 2 + 1;
	out->HeaderN.y = linfo->sigmay * linfo->sigma_range * 2 + 1;
	out->HeaderN.z = 1;

	if(linfo->flagWidth) {
		out->HeaderN.x = linfo->Width/out->HeaderLength.x; 
	}
	if(linfo->flagHeight) {
		out->HeaderN.y = linfo->Height/out->HeaderLength.y; 
	}
	out->HeaderMode = linfo->mode;

	mrcInit(out, NULL);  /* Memory allocate */
	cenx = (out->HeaderN.x - 1)/2.0 + linfo->CentreX;
	ceny = (out->HeaderN.y - 1)/2.0 + linfo->CentreY;
	angle = linfo->Angle; 

	for(x=0; x<out->HeaderN.x; x++){
		for(y=0; y<out->HeaderN.y; y++){
			srcx = (x-cenx)*cos(-angle) - (y-ceny)*sin(-angle)+cenx; 
			srcy = (x-cenx)*sin(-angle) + (y-ceny)*cos(-angle)+ceny;
			data = linfo->weight*exp(-(SQR(srcx-cenx)/(linfo->sigmax*linfo->sigmax)
									  +SQR(srcy-ceny)/(linfo->sigmay*linfo->sigmay)));
			mrcPixelDataSet(out, x, y, 1, data, mrcPixelRePart);
		}
	}
}

