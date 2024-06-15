/*
# mrcFFTCentralSection : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcFFTCentralSection
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
#include "eosString.h"
#include "lmrcFFTCentralSection.h"

int
main(int argc, char* argv[]) 
{
	mrcFFTCentralSectionInfo info;
	lmrcFFTCentralSectionInfo linfo;
	mrcImage in;
	mrcImage template;
	mrcImage out;
	mrcImage outImage;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	
	mrcFileRead(&in, info.In, "in main", 0);
	if(info.flagTemplate) {
		mrcFileRead(&template, info.Template, "in main", 0);
	} else {
		template.Header = in.Header;
		template.HeaderN.z = 1;
		mrcInit(&template, NULL);
	}

	strncpy(linfo.EulerMode, info.EAMode, 4);
	linfo.Rot1 = info.Rot1*RADIAN;
	linfo.Rot2 = info.Rot2*RADIAN;
	linfo.Rot3 = info.Rot3*RADIAN;
	linfo.TransX = info.TransX;
	linfo.TransY = info.TransY;
	linfo.InterpMode = info.InterpMode;

	lmrcFFTCentralSectionGet(&out, &template, &in, &linfo, info.mode); 

	mrcFileWrite(&out, info.Out, "in main", 0);

	if(info.flagOutImage) {
		lmrcImageFFT(&outImage, &out, 0);
		mrcFileWrite(&outImage, info.OutImage, "in main", 0);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-t[emplate] : If not set, the size of out (Nx, Ny) is set as the size of in (Nx, Ny).");
}
