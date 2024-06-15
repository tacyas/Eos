/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbNearAtomListShow ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbNearAtomListShow
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbNearAtomListShow ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "lpdbCoordInfo.h"

int lpdbnewAtomListShow(pdbFile* out, pdbFile* in, pdbCoord cor, pdbFileParaTypeReal distance, int mode);

int
main(int argc, char* argv[]) 
{
	pdbNearAtomListShowInfo info;
	pdbFile pdbIn;
	pdbFile pdbOut;
	pdbCoord cor;
	int     number = 0;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptIn, &pdbIn);
	pdbOut.nAtom = 0;
	if(info.flagPx && info.flagPy && info.flagPz) {
		cor.x = info.Px;
		cor.y = info.Py;
		cor.z = info.Pz;
		number = lpdbnewAtomListShow(&pdbOut, &pdbIn, cor, info.distance, info.mode);
	} else if(info.flagMRC) {
		float x, y, z;
		double data;
		mrcImage mrc;

		mrcFileRead(&mrc, info.MRC, "in main", 0);
		for(x=0; x<mrc.HeaderN.x; x++) {
		for(y=0; y<mrc.HeaderN.y; y++) {
		for(z=0; z<mrc.HeaderN.z; z++) {
			mrcPixelDataGet(&mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(info.Contour<data) {
				cor.x = (x+mrc.HeaderStartN.x)*mrc.HeaderLength.x;
				cor.y = (y+mrc.HeaderStartN.y)*mrc.HeaderLength.y;
				cor.z = (z+mrc.HeaderStartN.z)*mrc.HeaderLength.z;
				number += lpdbnewAtomListShow(&pdbOut, &pdbIn, cor, info.distance, info.mode);
			} 
		}
		}
		}	
	}
	if(0<number) {
		pdbFileWrite(info.fptOut, &pdbOut);
	} else { 
		fprintf(info.fptOut, "No ATOM\n");
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

int
lpdbnewAtomListShow(pdbFile* out, pdbFile* in, pdbCoord cor, pdbFileParaTypeReal distance, int mode) 
{
	int number=0; 

	pdbFileTop(in);
	while(1) {
		if(pdbFileIsAtom(in)) {
			if(lpdbDistanceNear(in, cor, distance, mode)) {
				if(0==number&&out->nAtom==0) {
					pdbFileNew(out);
					number++;	
				} else {
					pdbFileAppend(out);
					number++;
				}
				pdbFileOneRecordCopy(out, in);
				out->nAtom++;
			}
		}
		if(pdbFileEnd(in)) {
			break;
		} else {
			pdbFileNext(in);
		}
	}
	return number;
}

