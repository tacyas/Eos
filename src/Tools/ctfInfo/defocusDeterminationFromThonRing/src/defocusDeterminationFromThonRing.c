/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% defocusDeterminationFromThonRing ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : defocusDeterminationFromThonRing
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%defocusDeterminationFromThonRing ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#define UNDEBUG
#include "../inc/config.h"
#include "genUtil.h"
#include "ctfInfo.h"
#include "mrcImage.h"
#include "lllExtractdYEstimate.h"

int
main(int argc, char* argv[]) 
{
	char CTFInformation[200];
	char CTFInformation2[200];
	char CTFInformation3[200];
	long i, n;
	defocusDeterminationFromThonRingInfo info;
	ctfInfo ctf;
	float sam, sam2, aveU, aveO, sd;
	lllExtractdYEstimateInfo dYinfo;
	int dY;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	ctf.kV   = info.kV;
	ctf.Cs   = info.Cs;
	ctf.ratioOfAmpToPhase = info.AoverP;
	ctf.mode = info.ctfMode;

	dYinfo.truePitch = info.truePitch;
	dYinfo.deltadY   = info.deltadY;
	dYinfo.mag       = 1.0;
	dYinfo.PixelSize = info.PixelSize;

	DEBUGPRINT1("flagR: %ld\n", info.flagR);
	fprintf(info.fptOut, ">>> Underfocus\n");
	fprintf(info.fptOut, "Ring Number   Amount of defocus[A]   R[1/A] \n");
	sam = sam2 = 0.0;
	for(i=1; i<=info.flagR; i++) {
		n = i;
		defocusDeterminationFromThonRing(&ctf, info.R[i-1], n, info.mode);					
		sam  += ctf.defocus;
		sam2 += SQR(ctf.defocus);
		fprintf(info.fptOut, "%5ld         %15.6e :   %15.6e\n", n, ctf.defocus, info.R[i-1]); 
	}
	aveU = sam/info.flagR;
	sd  = sqrt(sam2/info.flagR - aveU*aveU);
	fprintf(info.fptOut, "---------------------------------------------\n");
	fprintf(info.fptOut, "Avg. %15.6e [A]  +- S.D. %15.6e [A] \n", aveU, sd);
	fprintf(info.fptOut, "Avg. %11.2f [um]     +- S.D. %11.2f [um] \n", aveU/10000, sd/10000);
	fprintf(info.fptOut, ">>> Overfocus\n");
	fprintf(info.fptOut, "Ring Number   Amount of defocus[A]   R[1/A] \n");
	sam = sam2 = 0.0;
	for(i=1; i<=info.flagR; i++) {
		n = i;
		defocusDeterminationFromThonRing(&ctf, info.R[i-1], -n, info.mode);					
		sam  += ctf.defocus;
		sam2 += SQR(ctf.defocus);
		fprintf(info.fptOut, "%5ld         %15.6e :   %15.6e\n", -n, ctf.defocus, info.R[i-1]); 
	}
	aveO = sam/info.flagR;
	sd  = sqrt(sam2/info.flagR - aveO*aveO);
	fprintf(info.fptOut, "---------------------------------------------\n");
	fprintf(info.fptOut, "Avg. %15.6e [A]  +- S.D. %15.6e [A] \n", aveO, sd);
	fprintf(info.fptOut, "Avg. %11.2f [um]     +- S.D. %11.2f [um] \n", aveO/10000, sd/10000);

	if(info.flagOutI){
		sprintf( CTFInformation, "%s %f %f %f %f \n",info.InN, aveU, ctf.Cs, ctf.kV, info.AoverP);
		fprintf(info.fptOutI, CTFInformation);
	}
	if(info.flagOutI2){
		sprintf( CTFInformation2, "%f %f %f %f \n", aveU, ctf.Cs, ctf.kV, info.AoverP);
		fprintf(info.fptOutI2, CTFInformation2);
	}
	if(info.flagOutI3){
		mrcHeaderRead(&in, info.InR, "in main", 0);
		dY = lllExtractdYEstimate(&in, &dYinfo);
		sprintf( CTFInformation3, "%s %d %f %f %f %f %ld\n",
					info.InN, dY, aveU, ctf.Cs, ctf.kV, info.AoverP, info.ctfMode);
		fprintf(info.fptOutI3, CTFInformation3);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stderr, "----- Additional Usage ----- \n");
fprintf(stderr, ">>>> o[uput] I[nformation] <<<<\n");
fprintf(stderr, "This file is used for [mrcImageMultiCTFCompensation and mrcImageCTFCompensation] \n");
fprintf(stderr, ">>>> o[uput] I[nformation] 2<<<<\n");
fprintf(stderr, "This file is used for [llDataCTFCompensate -I2] \n");
fprintf(stderr, ">>>> o[uput] I[nformation] 3<<<<\n");
fprintf(stderr, "This file is used for [llExtractWithLayerSeparation] \n");
fprintf(stderr, "Options: -truePitch, -PixelSize, -deltadY and -ctfMode\n");
fprintf(stderr, ">>>> ctfMode <<<< \n");
fprintf(stderr, " 0: Phase CTF \n");
fprintf(stderr, " 1: PhaseCTF + ratio*AmpCTF \n");
fprintf(stderr, ">>>> mode <<<< \n");
fprintf(stderr, "No action\n");
}
