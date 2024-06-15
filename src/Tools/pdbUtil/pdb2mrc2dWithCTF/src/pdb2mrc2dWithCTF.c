/*
# pdb2mrc2dWithCTF : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : pdb2mrc2dWithCTF
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
#include "Memory.h"
#include "mrcImage.h"
#include "pdbFile.h"
#include "ctfInfo.h"
#include "lpdb2mrcInfo.h"

typedef struct lpdb2mrc2dWithCTFInfo {
	mrcImageParaTypeRealCoord     C; // Centre [A]
	mrcImageParaTypeIntegerCoord  N; // Number [pixel]
	mrcImageParaTypeRealCoord     d; // Delta [A] 
	mrcImageParaTypeIntegerCoord  n; // Number for SubArea for Atom[pixel]
}  lpdb2mrc2dWithCTFInfo;

extern void lpdb2mrc2dWithCTF(mrcImage* out, pdbFile* pdb, lpdb2mrc2dWithCTFInfo* linfo, ctfInfo* ctf, int mode);

int
main(int argc, char* argv[]) 
{
	pdb2mrc2dWithCTFInfo info;
	lpdb2mrc2dWithCTFInfo linfo;
	ctfInfo ctfInfo;
	pdbFile  pdb;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptIn, &pdb);

	memoryClear(&ctfInfo, sizeof(ctfInfo), (char)0);
	ctfInfo.Cs = info.Cs;	
	ctfInfo.defocus = info.Defocus;	
	ctfInfo.kV = info.kV;	
	ctfInfo.mode = info.ctfMode;	
	ctfInfo.ratioOfAmpToPhase = info.AoverP;	
	ctfInfo.Ain = info.Ain;	
	linfo.C.x = info.cx;
	linfo.C.y = info.cy;
	linfo.C.z = info.cz; 
	linfo.d.x = info.dx; 
	linfo.d.y = info.dy; 
	linfo.d.z = info.dy; 
	linfo.N.x = info.Nx;
	linfo.N.y = info.Ny;
	linfo.N.z = 1;
	linfo.n.x = info.nx;
	linfo.n.y = info.ny;
	linfo.n.z = 1;

	if(info.flagEulerAngle) {
		pdbRotationFollowingEulerAngle(&pdb, info.EulerAngle, info.Rot1*RADIAN, info.Rot2*RADIAN, info.Rot3*RADIAN);
	}

	lpdb2mrc2dWithCTF(&out, &pdb, &linfo, &ctfInfo, info.mode);

	mrcStatDataSet(&out, 0);	
	mrcFileWrite(&out, info.Out, "in main", 0);	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

/*
 * * pdbZValueGet
 * *  return value: Atomic Mass of the current atom
*/
/*
int
pdbZValueGet(pdbRecord* current)
{
	if(       current->Footnote[6] == ' ' && current->Footnote[7] == 'H') {
		return 1;
	} else if(current->Footnote[6] == ' ' && current->Footnote[7] == 'C') {
		return 6;
	} else if(current->Footnote[6] == ' ' && current->Footnote[7] == 'N') {
		return 7;
	} else if(current->Footnote[6] == ' ' && current->Footnote[7] == 'O') {
		return 8;
	} else if(current->Footnote[6] == ' ' && current->Footnote[7] == 'P') {
		return 15;
	} else if(current->Footnote[6] == ' ' && current->Footnote[7] == 'S') {
		return 16;
	} else if(current->Footnote[6] == 'N' && current->Footnote[7] == 'A') {
		return 11;
	} else if(current->Footnote[6] == 'M' && current->Footnote[7] == 'G') {
		return 12;
	} else if(current->Footnote[6] == ' ' && current->Footnote[7] == 'K') {
		return 19;
	} else if(current->Footnote[6] == 'C' && current->Footnote[7] == 'A') {
		return 20;
	} else if(current->AtomName[0] == ' ' && current->AtomName[1] == 'H') {
		return 1;
	} else if(current->AtomName[0] == ' ' && current->AtomName[1] == 'C') {
		return 6;
	} else if(current->AtomName[0] == ' ' && current->AtomName[1] == 'N') {
		return 7;
	} else if(current->AtomName[0] == ' ' && current->AtomName[1] == 'O') {
		return 8;
	} else if(current->AtomName[0] == ' ' && current->AtomName[1] == 'P') {
		return 15;
	} else if(current->AtomName[0] == ' ' && current->AtomName[1] == 'S') {
		return 16;
	} else if(current->AtomName[0] == 'N' && current->AtomName[1] == 'A') {
		return 11;
	} else if(current->AtomName[0] == 'M' && current->AtomName[1] == 'G') {
		return 12;
	} else if(current->AtomName[0] == ' ' && current->AtomName[1] == 'K') {
		return 19;
	} else if(current->AtomName[0] == 'C' && current->AtomName[1] == 'A') {
		return 20;
	} else {
		fprintf(stderr, "Not supported element: %c%c\n", current->Footnote[6], current->Footnote[7]);
		fprintf(stderr, "Not supported element: %c%c\n", current->AtomName[0], current->AtomName[1]);
		return 6;
	}
	return 1;
}
*/
void
lpdb2mrc2dWithCTF(mrcImage* out, pdbFile* pdb, lpdb2mrc2dWithCTFInfo* linfo, ctfInfo* ctf, int mode)
{
	mrcImage sub;
	mrcImage subFFT;
	mrcImage dstFFT;
	mrcImage dst;
	ctfInfo  subCTF;
	double r, Z, R;
	int i;
	double data, data2;
	mrcImageParaTypeReal x, y, z;
	const double aH = 0.0529e-9; 
	const double K  = 9.0e9; 
	const double e  = 1.6e-19; 
	mrcImageParaTypeReal offsetx, offsety, offsetz; 
	mrcImageParaTypeReal offsetX, offsetY, offsetZ; 
	mrcImageParaTypeReal srcx, srcy, srcz; 
	mrcImageParaTypeReal dstx, dsty, dstz; 

	out->Header.Cont.N = linfo->N;
	out->Header.Cont.Length = linfo->d;
	out->HeaderMode = mrcFloatImage;
	out->HeaderM.x = out->HeaderM.y = out->HeaderM.z = 1; 
	out->HeaderAlpha = out->HeaderBeta = out->HeaderGamma = 90; 
	out->HeaderMAPC = 1;
	out->HeaderMAPR = 2;
	out->HeaderMAPS = 3;
	mrcInit(out, NULL);
	offsetX = (out->HeaderN.x-1)/2;
	offsetY = (out->HeaderN.y-1)/2;
	offsetZ = (out->HeaderN.z-1)/2;


	sub.Header.Cont.N = linfo->n;
	sub.Header.Cont.Length = linfo->d;
	sub.HeaderMode = mrcFloatImage;
	offsetx = (linfo->n.x-1)/2;
	offsety = (linfo->n.y-1)/2;
	offsetz = (linfo->n.z-1)/2;

	subCTF = *ctf;
	i = 0;
	pdbFileTop(pdb);
	while(1) {
		if(pdbFileIsAtom(pdb)) {
			if(i%100==0) {	
				fprintf(stderr, "%d\n", i);
			}
			Z  = pdbZValueGet(pdb);
			R  = aH *pow(Z, -1.0/3.0);

			mrcInit(&sub, NULL);
			for(z=-10; z<=10; z+=1.0) {	
			for(y=-10; y<=10; y+=1.0) {	
			for(x=-10; x<=10; x+=1.0) {	
				r = sqrt(SQR(x/linfo->d.x)+SQR(y/linfo->d.y)+SQR(z/linfo->d.z));
				if(0.5 < r && r< 10/linfo->d.x) {
					srcx = x/linfo->d.x + offsetx;
					srcy = y/linfo->d.y + offsety;
					mrcPixelDataGet(&sub, srcx, srcy, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
					r *= 1e-10;
					data2 =	(K*e*Z/r)*exp(-r/R);	 
					data  += data2;
					//fprintf(stderr, "data %e data2 %e Z %e R %e r %e\n", data, data2, Z, R, r*1e10);
					mrcPixelDataSet(&sub, srcx, srcy, 0, data, mrcPixelRePart); 
				}
			}
			}
			}	
				
			subCTF.defocus = ctf->defocus - pdb->PDB->Coord.z;   
			lmrcImageFFT(&subFFT, &sub, 0);
			lmrcImageCTFObservation(&dstFFT, &subFFT, &subCTF, mode);
			lmrcImageFFT(&dst, &dstFFT, 0);

			for(y=0; y<sub.HeaderN.y; y++) {		
			for(x=0; x<sub.HeaderN.x; x++) {		
				mrcPixelDataGet(&dst, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest); 
				dstx = x - offsetx + pdb->PDB->Coord.x/linfo->d.x + offsetX;  
				dsty = y - offsety + pdb->PDB->Coord.y/linfo->d.x + offsetY;  
				if(-0.5<=dstx && dstx<out->HeaderN.x-0.5 
				 &&-0.5<=dsty && dsty<out->HeaderN.y-0.5) {
					mrcPixelDataGet(out, dstx, dsty, 0, &data2, mrcPixelRePart, mrcPixelHowNearest); 
					mrcPixelDataSet(out, dstx, dsty, 0, data+data2, mrcPixelRePart);
				}	
			}
			}	
			mrcImageFree(&sub, 0);
			mrcImageFree(&subFFT, 0);
			mrcImageFree(&dstFFT, 0);
			mrcImageFree(&dst, 0);
			i++;
		}
		if(pdbFileEnd(pdb)) {
			break;
		} else {
			pdbFileNext(pdb);
		}
	}
}
