/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbRhoFit ver %I%
#%Z% Created by Yu MENG
#%Z% Add the option of -ipdb : max score pdbFile : modified by tacyas@tkyemghp.phys.s.u-tokyo.ac.jp
#%Z%
#%Z% Usage : pdbRhoFit
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%pdbRhoFit ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <memory.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"


#undef  DEBUG
#undef PDBDEBUG
#undef MRCDEBUG
#undef NORDEBUG
#define Count_mode (0)
#define Density_mode (1)
#define MINTFACTOR (1)
#define MAX_VALUE (1000)
#include "genUtil.h"
#include "mrcImage.h"
#include "pdbFile.h"

extern void lpdbRhoFit(pdbRhoFitInfo*);

int
main(int argc, char* argv[]) 
{
	long status;
	pdbRhoFitInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	lpdbRhoFit(&info);

	return 0;
}

void lpdbRhoFit(pdbRhoFitInfo* info)
{
	pdbFile inPdb;
	pdbFile inS0Pdb; /* pdb file shifted to the (0, 0) coord */
	pdbFile tmpPdb;
	double data;
	double score;
	double maxscore;
	double maxphi, maxpsi, maxtheta;
	double maxx, maxy, maxz;
	double maxscoreMax;
	double maxscoreMaxXY;
	double maxscoreMaxPsiTheta;
	double normalizeData;
	float xPosition;
	float yPosition;
	float zPosition;
	float phi;
	float psi;
	float theta;
	float rad;
	Matrix3D MatrixRot;
	Matrix3D MatrixShift0; /* to the (0, 0, 0) coord */
	Matrix3D MatrixShift1; /* back to the original coord */
	float xofMrc;
	float yofMrc;
	float zofMrc;
	mrcImage inMrc;
	mrcImage outmrc;
	mrcImage outmrctmp;
	mrcImage tmpmrc;
	mrcImageParaTypeReal x,y,z;
#ifdef PDBDEBUG
		FILE* pdbfpt;
		char tmpPdbFName[256];
#endif

	pdbRecord* onePdbRecord;
	pdbFileParaTypeReal X,Y,Z;
	mrcImageParaTypeReal mrcX,mrcY;
	mrcImageParaTypeReal mrcX1,mrcY1;
	mrcImageParaTypeReal mrcX2,mrcY2;
	int i;

	DEBUGPRINT1("pdbFileRead: %s\n", info->InPdb);
	pdbFileRead(info->fptInPdb, &inPdb);

	DEBUGPRINT1("mrcFileRead: %s\n", info->InMrc);
	mrcFileRead(&inMrc,info->InMrc,"in lpdbRhoFit\n",0);

	xofMrc=(inMrc.HeaderN.x-1) * inMrc.HeaderLength.x;
	yofMrc=(inMrc.HeaderN.y-1) * inMrc.HeaderLength.y;
	zofMrc=(inMrc.HeaderN.z-1) * inMrc.HeaderLength.z;
#ifdef DEBUG
		fprintf(stderr,"xlen(A) %f\n",xofMrc);
		fprintf(stderr,"ylen(A) %f\n",yofMrc);
		fprintf(stderr,"zlen(A) %f\n",zofMrc);
#endif

	DEBUGPRINT("Set matrix3D\n");
	/*
	matrix3DTranslationSet(MatrixShift0, -xofMrc/2.0, -yofMrc/2.0,  0.0, MATRIX_3D_MODE_INITIALIZE);
	matrix3DTranslationSet(MatrixShift1,  xofMrc/2.0,  yofMrc/2.0,  0.0, MATRIX_3D_MODE_INITIALIZE);
	*/	
	matrix3DTranslationSet(MatrixShift0, -xofMrc/2.0, -yofMrc/2.0,  -zofMrc/2.0, MATRIX_3D_MODE_INITIALIZE);
	matrix3DTranslationSet(MatrixShift1,  xofMrc/2.0,  yofMrc/2.0,   zofMrc/2.0, MATRIX_3D_MODE_INITIALIZE);

	DEBUGPRINT("Initialize output file of mrc\n");	
	if(info->psimin==info->psimax
	 &&info->thetamin==info->thetamax
	 &&info->xmin==info->xmax
	 &&info->ymin==info->zmin) {
		outmrc.HeaderN.x = (info->phimax-info->phimin)/info->phiDelta + 1;
		outmrc.HeaderN.y = (info->zmax  -info->zmin)  /info->zDelta + 1;
		outmrc.HeaderN.z = 3;
	} else {
		outmrc.HeaderN.x = (info->phimax-info->phimin)/info->phiDelta; 
		outmrc.HeaderN.x = MAX(outmrc.HeaderN.x, (info->psimax-info->psimin)/info->psiDelta); 
		outmrc.HeaderN.x = MAX(outmrc.HeaderN.x, (info->thetamax-info->thetamin)/info->thetaDelta) + 1; 
		outmrc.HeaderN.y = (info->zmax  -info->zmin)  /info->zDelta;
		outmrc.HeaderN.y = MAX(outmrc.HeaderN.y, (info->xmax  -info->xmin)  /info->xDelta);
		outmrc.HeaderN.y = MAX(outmrc.HeaderN.y, (info->ymax  -info->ymin)  /info->yDelta) + 1;
		outmrc.HeaderN.z = 3;
	}
	outmrc.HeaderMode = MRC_float_image;
	mrcInit(&outmrc, NULL);
	outmrctmp.Header = outmrc.Header;
	mrcInit(&outmrctmp, NULL);
	
	DEBUGPRINT("pdbFileSet\n");	
	
	pdbFileNew(&inS0Pdb);
	//inS0Pdb.top =  NULL;
	pdbFileNew(&tmpPdb);
	//tmpPdb.top =  NULL;
	
	DEBUGPRINT("pdbFileCopyAll\n");	
	pdbFileCopyAll(&inS0Pdb,&inPdb);

	DEBUGPRINT("pdbTrans\n");	
	if(!info->Centre) {
		pdbTrans(&inS0Pdb, MatrixShift0);
	}
	DEBUGPRINT("OutTxt Set\n");	
	fprintf(stderr,"zmax = %f\n",info->zmax);
	if(info->flagOutTxt){
		fprintf(info->fptOutTxt,"z\\phi ");
		for(phi=info->phimin;phi<=info->phimax;phi=phi+info->phiDelta){
			fprintf(info->fptOutTxt,"%4.0f ",phi);
		}
		fprintf(info->fptOutTxt,"\n\n");
	}

	DEBUGPRINT("Normalization of mrc\n");	
	tmpmrc.Header=inMrc.Header;
	mrcInit(&tmpmrc,NULL);

	normalizeData=0;
	for(x=0;x<inMrc.HeaderN.x;x++){
		for(y=0;y<inMrc.HeaderN.y;y++){
			for(z=0;z<inMrc.HeaderN.z;z++){
				mrcPixelDataGet(&inMrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(info->Inverse){
					data= -data;
				}
				if(info->flagnormalizeContour){
					if(data<info->normalizeContour){
						normalizeData += data/info->normalizeWeight;
					}
				}
				score=0;

				switch(info->mode) {
					case Density_mode: {
						if(1<=info->flagcontourLevel) {
							for(i=0;i<info->flagcontourLevel;i++){
								if(data<info->contourLevel[i]) {
									score -= data/100;
								}
							}
						} else {
							score -= data/100; 
						}
						break;
					}
					case Count_mode:   {
						if(1<=info->flagcontourLevel) {
							for(i=0;i<info->flagcontourLevel;i++){
								if(data<info->contourLevel[i]) {
									score++;
								}
							}
						} else {
                    		usage("pdbRhoFit, you need contourLevel for -m 0 -C ");
                    		exit(EXIT_FAILURE);
						}
						break;
					}
				}
/*
				if(info->flagcontourLevel>=1){
					for(i=0;i<info->flagcontourLevel;i++){
						if(data<info->contourLevel[i]){
							if(Count_mode==info->mode){
								score++;
							} else if(Density_mode==info->mode){
								score=score-data/100;
							}
						}
					}
				} else if(!info->flagcontourLevel 
				        && Density_mode==info->mode){
					score = score - data/100;
				}else{
                    usage("pdbRhoFit, you need contourLevel for -m 0 -C ");
                    exit(EXIT_FAILURE);
				}
*/
				mrcPixelDataSet(&tmpmrc, x, y, z, score, mrcPixelRePart);
			}
		}
	}

	normalizeData=normalizeData*inMrc.HeaderLength.x
							   *inMrc.HeaderLength.y
							   *inMrc.HeaderLength.z;

#ifdef NORDEBUG
		fprintf(stderr,"normalizeData= %f.\n",normalizeData);
		exit(0);
#endif
	fprintf(stderr,"normalizeData= %f.\n",normalizeData);

	maxphi = maxpsi = maxtheta = maxx = maxy = maxz = 0;
	maxscore = maxscoreMax = 0.0;
	for(zPosition=info->zmin, mrcY=0.0; zPosition<=info->zmax; zPosition+=info->zDelta, mrcY++){
		DEBUGPRINT1("zPosition = %f\n",zPosition);
		if(info->flagOutTxt){
			fprintf(info->fptOutTxt,"%5.1f ",zPosition);
		}
		for(phi=info->phimin, mrcX=0.0; phi<=info->phimax; phi+=info->phiDelta, mrcX++){
			DEBUGPRINT1("phi=%f\n",phi);

			maxscoreMaxPsiTheta = 0.0;
		for(psi=info->psimin, mrcX2=0;     psi<=info->psimax;    psi+=info->psiDelta, mrcX2++) {
			DEBUGPRINT1("psi=%f\n",psi);
		for(theta=info->thetamin, mrcY2=0; theta<=info->thetamax; theta+=info->thetaDelta, mrcY2++) {
			DEBUGPRINT1("theta=%f\n",theta);
			
			maxscoreMaxXY = 0.0;
		for(xPosition=info->xmin, mrcX1=0; xPosition<=info->xmax; xPosition+=info->xDelta, mrcX1++) {
			DEBUGPRINT1("xPosition = %f\n",xPosition);
		for(yPosition=info->ymin, mrcY1=0; yPosition<=info->ymax; yPosition+=info->yDelta, mrcY1++) {
			DEBUGPRINT1("yPosition = %f\n",yPosition);

			matrix3DRotationSetFollowingEulerAngle(MatrixRot, info->EulerAngle, phi*RADIAN, psi*RADIAN, theta*RADIAN,  MATRIX_3D_MODE_INITIALIZE); 
			if(0==info->Zminus){
				matrix3DTranslationSet(MatrixRot,  xPosition,  yPosition,  zPosition, MATRIX_3D_MODE_NOT_INITIALIZE);
			}else{
				matrix3DTranslationSet(MatrixRot,  xPosition,  yPosition, -zPosition, MATRIX_3D_MODE_NOT_INITIALIZE);
			}
			//DEBUGPRINT3("%f %f %f\n", MatrixRot[0][0], MatrixRot[1][1], Matrix[2][2]);	
			pdbFileCopyAll(&tmpPdb, &inS0Pdb);
			pdbTrans(&tmpPdb,MatrixRot);
			pdbTrans(&tmpPdb,MatrixShift1);
#ifdef PDBDEBUG
				sprintf(tmpPdbFName,"tmp%1.0f%1.0f.pdb",zPosition,phi); 
				pdbfpt=fopen(tmpPdbFName,"w"); pdbFileWrite(pdbfpt,&tmpPdb);
				fclose(pdbfpt);
#endif

			onePdbRecord=pdbFileTop(&tmpPdb);
			score=0;
			while(NULL!=onePdbRecord){
				if(pdbFileIsAtom(&tmpPdb)) {
					pdbFileCoordGet(&tmpPdb, &X, &Y, &Z);
					if(  -0.5*tmpmrc.HeaderLength.x <= X 
					  && X < (tmpmrc.HeaderN.x-0.5)*tmpmrc.HeaderLength.x
					  && -0.5*tmpmrc.HeaderLength.y <= Y 
					  && Y < (tmpmrc.HeaderN.y-0.5)*tmpmrc.HeaderLength.y
					  && -0.5*tmpmrc.HeaderLength.z <= Z
					  && Z < (tmpmrc.HeaderN.z-0.5)*tmpmrc.HeaderLength.z) {
						mrcImageDataGetbyAU(&tmpmrc, X, Y, Z, &data, mrcPixelRePart, mrcPixelHowNearest);
					} else {
						data = 0.0;
					}
					if(data>MAX_VALUE || data<-MAX_VALUE){
						fprintf(stderr,"data is %f\n",data);
					}
#ifdef MRCDEBUG
						fprintf(stderr,"X=%f; Y=%f; Z=%f; data= %f\n",X,Y,Z,data);
#endif
					if(0!=info->Tfactor && onePdbRecord->TemperatureFactor<info->Tlim){
						score=score+data*30/onePdbRecord->TemperatureFactor;
					}else{
						score=score+data;
					}
				}
				onePdbRecord=pdbFileNextAtom(&tmpPdb);
			}
			if(info->flagnormalizeContour){
				score = -score/normalizeData;
				/* density in normal image is minus (normalizeData < 0) */
			}

			if(maxscore <= score) { /* all (x, y, theta, psi, z, phi) */
				DEBUGPRINT1("max: %f ", score);
				DEBUGPRINT6("%f %f %f %f %f %f\n", phi, psi, theta, xPosition, yPosition, zPosition);
				fprintf(stdout, "max: %f ", score);
				fprintf(stdout, "%f %f %f %f %f %f\n", phi, psi, theta, xPosition, yPosition, zPosition);
				maxscore = score;
				maxphi   = phi;
				maxpsi   = psi;
				maxtheta = theta;
				maxx     = xPosition;
				maxy     = yPosition;
				maxz     = zPosition;
			}
			if(info->flagOutPar) {
				fprintf(info->fptOutPar, "%10.3f %10.3f %10.3f %10.3f %10.3f %10.3f %15.6g\n", phi, psi, theta, xPosition, yPosition, zPosition, score);
			}
			if(maxscoreMaxXY<=score) { 		/* all (x, y) and specific (theta, psi) */
				maxscoreMaxXY = score;	
			}
			if(maxscoreMaxPsiTheta<=score) {/* all (x, y, theta, psi) and specific (z, phi) */
				maxscoreMaxPsiTheta = score;	
			}
			if(maxscoreMax<=score) { 		/* all (x, y, theta, psi, z, phi) */
				maxscoreMax   = score;	
			}
			/* scores of (x, y)  at the current (theta, psi, z, phi) */
			mrcPixelDataSet(&outmrctmp, mrcX1, mrcY1, 2.0, score, mrcPixelRePart);  
		} /* y */
		} /* x */
			if(maxscore<=maxscoreMaxXY) { 
				for(mrcX1=0; mrcX1<outmrctmp.HeaderN.x; mrcX1++) {	
					for(mrcY1=0; mrcY1<outmrctmp.HeaderN.y; mrcY1++) {	
						mrcPixelDataGet(&outmrctmp, mrcX1, mrcY1, 2.0, &data, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataSet(&outmrc   , mrcX1, mrcY1, 2.0,  data, mrcPixelRePart);
					}
				}
			}
			/* Maximum value of (x, y) plane */
			mrcPixelDataSet(&outmrctmp, mrcX2, mrcY2, 1.0, maxscoreMaxXY, mrcPixelRePart);   
		} /* theta */
		} /* psi */
			if(maxscore<=maxscoreMaxPsiTheta) {
				for(mrcX2=0; mrcX2<outmrctmp.HeaderN.x; mrcX2++) {	
					for(mrcY2=0; mrcY2<outmrctmp.HeaderN.y; mrcY2++) {	
						mrcPixelDataGet(&outmrctmp, mrcX2, mrcY2, 1.0, &data, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataSet(&outmrc   , mrcX2, mrcY2, 1.0,  data, mrcPixelRePart);
					}
				}
			}
			mrcPixelDataSet(&outmrc, mrcX, mrcY, 0.0, maxscoreMaxPsiTheta, mrcPixelRePart); 
			if(info->flagOutTxt) {
				fprintf(info->fptOutTxt, "%4.0f ", maxscoreMaxPsiTheta);
			}
		} /* phi */
		if(info->flagOutTxt){
			fprintf(info->fptOutTxt,"\n");
		}
	} /* z */
	fprintf(stdout, "MaxPoint Trans: %f %f %f Rot: %f %f %f\n", maxx, maxy, maxz, maxphi, maxpsi, maxtheta);
	if(info->flagOutPDB) {
		//matrix3DRotationSetFollowingEulerAngle(MatrixRot, info->EulerAngle, maxphi*RADIAN, maxpsi*RADIAN, maxtheta*RADIAN, 0); 
		matrix3DRotationSetFollowingEulerAngle(MatrixRot, info->EulerAngle, maxphi*RADIAN, maxpsi*RADIAN, maxtheta*RADIAN, MATRIX_3D_MODE_INITIALIZE); 
		if(0==info->Zminus){
			matrix3DTranslationSet(MatrixRot, maxx, maxy,  maxz, MATRIX_3D_MODE_NOT_INITIALIZE);
		}else{
			matrix3DTranslationSet(MatrixRot, maxx, maxy, -maxz, MATRIX_3D_MODE_NOT_INITIALIZE);
		}
		/* pdbTrans(&inPdb, MatrixRot); */
		pdbTrans(&inS0Pdb, MatrixRot); 
		pdbTrans(&inS0Pdb, MatrixShift1);
		pdbFileWrite(info->fptOutPDB, &inS0Pdb);
	}

	DEBUGPRINT("Write fitmap\n");
	outmrc.HeaderM.x=1;
	outmrc.HeaderM.y=1;
	outmrc.HeaderM.z=1;
	outmrc.HeaderLength.x=info->phiDelta;
	outmrc.HeaderLength.y=info->zDelta;
	outmrc.HeaderLength.z=1;
	outmrc.HeaderAlpha = 90;
	outmrc.HeaderBeta  = 90;
	outmrc.HeaderGamma = 90;
	outmrc.HeaderMAPC = 1;
	outmrc.HeaderMAPR = 2;
	outmrc.HeaderMAPS = 3;
	DEBUGPRINT("StatDataSet\n");
	mrcStatDataSet(&outmrc, 0);
	DEBUGPRINT1("Fille Write: %s\n", info->OutMrc);
	mrcFileWrite(&outmrc, info->OutMrc, "in lpdbRhoFit", 0);
}

void
additionalUsage()
{
	fprintf(stderr,"\n\nUsage of pdbRhoFit:\n");
	fprintf(stderr,"    -ipdb   : Filename of pdb file of atomic model\n");
	fprintf(stderr,"    -imrc   : Filename of mrc file of contour map\n");
	fprintf(stderr,"    -omrc   : Filename of mrc file of fitting results\n");
	fprintf(stderr,"    -otxt   : Filename of text file of fitting results\n");
	fprintf(stderr,"    -opar   : Filename of text file of fitting results\n");
	fprintf(stderr,"    -opdb   : Filename of pdb file with a max score after fitting results\n");
	fprintf(stderr,"    -zmin   : Initial value of z (should <= zmax)\n");
	fprintf(stderr,"    -zmax   : Final value of z\n");
	fprintf(stderr,"    -zd     : Delta z for fitting (should >0)\n");
	fprintf(stderr,"    -phimin : Initial value of phi (should <= phimax; initial value of phi is 0)\n");
	fprintf(stderr,"    -phimax : Final value of phi (should >0)\n");
	fprintf(stderr,"    -phid   : Delta phi for fitting (should >0)\n");
	fprintf(stderr,"    -C      : Contour level (variable and MUST be last option)\n");
	fprintf(stderr,"    -Inverse: Protein has high density on the image\n");
	fprintf(stderr,"    -Zminus : Atomic model shift to -z while fitting\n");
	fprintf(stderr,"    -Tfactor: Consider temperature factor\n");
	fprintf(stderr,"    -Tlim   : The atoms whose T factor is above Tlim will be neglected\n");
	fprintf(stderr,"    -Centre : Filament-axis is x=0, y=0\n");
	fprintf(stderr,"    -c      : Not used now\n");
	fprintf(stderr,"    -m   %d : Count the atom number inside the contour.\n",Count_mode);
	fprintf(stderr,"         %d : Add the densities of atoms.\n",Density_mode);
}
