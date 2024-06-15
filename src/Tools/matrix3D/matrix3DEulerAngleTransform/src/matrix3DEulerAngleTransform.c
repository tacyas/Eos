/*
# matrix3DEulerAngleTransform : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : matrix3DEulerAngleTransform
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
#include "Matrix3D.h"
#include "eosString.h"
#include "Memory.h"

#define WORDLEN 1024

typedef struct lmatrix3DEulerAngleTransformInfo {
	char** filename;
	int    filenum;
	char** rotationalMode;
	float* phi;
	float* theta;
	float* psi;

	char*   MulRotMode;
	float  MulRot1;
	float  MulRot2;
	float  MulRot3;

	char*  changerotationalMode;
} lmatrix3DEulerAngleTransformInfo;

/*
typedef enum lmatrix3DEulerAngleTransformMode {
	a=0,
	b=1
} lmatrix3DEulerAngleTransformMode;
*/

void
__FileRead(lmatrix3DEulerAngleTransformInfo* linfo, FILE* fpt, int mode);

void
lmatrix3DEulerAngleTransform(lmatrix3DEulerAngleTransformInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	matrix3DEulerAngleTransformInfo  info;
	lmatrix3DEulerAngleTransformInfo linfo;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.filenum        = info.flagIn;
	linfo.filename       = MemoryAllocate(char*, linfo.filenum, "in main"); 
	linfo.rotationalMode = MemoryAllocate(char*, linfo.filenum, "in main"); 
	linfo.phi            = MemoryAllocate(float, linfo.filenum, "in main"); 
	linfo.theta          = MemoryAllocate(float, linfo.filenum, "in main"); 
	linfo.psi            = MemoryAllocate(float, linfo.filenum, "in main"); 
	linfo.changerotationalMode = MemoryAllocate(char, 5, "in main");
	strcpy(linfo.changerotationalMode, info.RotationalMode);

	linfo.MulRotMode = info.RotMode;
	linfo.MulRot1   = info.Rot1;
	linfo.MulRot2   = info.Rot2;
	linfo.MulRot3   = info.Rot3;

	__FileRead(&linfo, info.fptInList, 0);
	for(i=0; i<linfo.filenum; i++){
		strcpy(linfo.filename[i], info.In[i]);
	}

	lmatrix3DEulerAngleTransform(&linfo, 0);

	for(i=0; i<linfo.filenum; i++){
		fprintf(info.fptOut, "%s %s %f %f %f\n", linfo.filename[i], linfo.changerotationalMode, 
												 linfo.phi[i]*DEGREE, linfo.theta[i]*DEGREE, linfo.psi[i]*DEGREE);
	}
	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- input file format -----\n");
	fprintf(stderr, " filename rotationalMode phi theta psi\n");
	fprintf(stderr, "    .          .          .    .    . \n");
	fprintf(stderr, "    .          .          .    .    . \n");
	fprintf(stderr, "    .          .          .    .    . \n");
	fprintf(stderr, "\n");
}

void
__FileRead(lmatrix3DEulerAngleTransformInfo* linfo, FILE* fpt, int mode)
{
	int i=0;
	char s[WORDLEN];
	
	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<linfo->filenum; i++){
		linfo->filename[i]       = MemoryAllocate(char, WORDLEN, "in __FileRead");
		linfo->rotationalMode[i] = MemoryAllocate(char, 5,       "in __FileRead");
	
		stringGetFromFile(s, "", fpt, stdout, 3);
		stringCopy(linfo->rotationalMode[i], stringGetNthWord(s, 2, " \t,"), 4);
		linfo->phi[i]   = stringGetNthRealData(s, 3, " \t,")*RADIAN;
		linfo->theta[i] = stringGetNthRealData(s, 4, " \t,")*RADIAN;
		linfo->psi[i]   = stringGetNthRealData(s, 5, " \t,")*RADIAN;
	}

}

void
lmatrix3DEulerAngleTransform(lmatrix3DEulerAngleTransformInfo* linfo, int mode)
{
	int         i;
	float       nphi, ntheta, npsi;	
	floatVector Originalxv;
	floatVector Originalyv;
	floatVector Originalzv;
	floatVector Workxv;
	floatVector Workyv;
	floatVector Workzv;
	Matrix3D    OriginalRotation;
	Matrix3D    WorkRotation;
	double      difference;
	double      differenceMin;
	float       phiMin, thetaMin, psiMin;
	float       phiHigh, thetaHigh, psiHigh;
	float       phiLow,  thetaLow,  psiLow;
	float       Delta;
	int         count;

	floatVectorInit(&Originalxv, 4);
	floatVectorInit(&Originalyv, 4);
	floatVectorInit(&Originalzv, 4);
	floatVectorInit(&Workxv, 4);
	floatVectorInit(&Workyv, 4);
	floatVectorInit(&Workzv, 4);

	for(i=0; i<linfo->filenum; i++){
		DEBUGPRINT1("start : image number --> %d\n", i);
		Originalxv.data[0] = 1.0;
		Originalxv.data[1] = 0.0;
		Originalxv.data[2] = 0.0;
		Originalxv.data[3] = 1.0;
		Originalyv.data[0] = 0.0;
		Originalyv.data[1] = 1.0;
		Originalyv.data[2] = 0.0;
		Originalyv.data[3] = 1.0;
		Originalzv.data[0] = 0.0;
		Originalzv.data[1] = 0.0;
		Originalzv.data[2] = 1.0;
		Originalzv.data[3] = 1.0;

		matrix3DRotationSetFollowingEulerAngle(OriginalRotation,
										       linfo->rotationalMode[i],
											   linfo->phi[i],
											   linfo->theta[i],
											   linfo->psi[i],
											   MATRIX_3D_MODE_INITIALIZE);
		matrix3DRotationSetFollowingEulerAngle(OriginalRotation,
												linfo->MulRotMode,
												linfo->MulRot1,
												linfo->MulRot2,
												linfo->MulRot3,
												MATRIX_3D_MODE_NOT_INITIALIZE);
		matrix3DMultiplyVector(&Originalxv, OriginalRotation);
		matrix3DMultiplyVector(&Originalyv, OriginalRotation);
		matrix3DMultiplyVector(&Originalzv, OriginalRotation);

		count = 0;
		differenceMin = 1.0e5;
		phiLow = thetaLow = psiLow = 0.0;
		phiHigh = psiHigh = 2*M_PI;
		thetaHigh = M_PI;
		Delta = M_PI/18;	
		do{	
			for(nphi  =phiLow  ; nphi  <phiHigh  ; nphi  +=Delta){
			for(ntheta=thetaLow; ntheta<thetaHigh; ntheta+=Delta){
			for(npsi  =psiLow  ; npsi  <psiHigh  ; npsi  +=Delta){
				Workxv.data[0] = 1.0;
				Workxv.data[1] = 0.0;
				Workxv.data[2] = 0.0;
				Workxv.data[3] = 1.0;
				Workyv.data[0] = 0.0;
				Workyv.data[1] = 1.0;
				Workyv.data[2] = 0.0;
				Workyv.data[3] = 1.0;
				Workzv.data[0] = 0.0;
				Workzv.data[1] = 0.0;
				Workzv.data[2] = 1.0;
				Workzv.data[3] = 1.0;
			
				matrix3DRotationSetFollowingEulerAngle(WorkRotation,
													   linfo->changerotationalMode,
													   nphi,
													   ntheta,
													   npsi,
													   MATRIX_3D_MODE_INITIALIZE);
				
				matrix3DMultiplyVector(&Workxv, WorkRotation);
				matrix3DMultiplyVector(&Workyv, WorkRotation);
				matrix3DMultiplyVector(&Workzv, WorkRotation);

				difference = SQR(Originalxv.data[0] - Workxv.data[0])
			    	        +SQR(Originalxv.data[1] - Workxv.data[1])
							+SQR(Originalxv.data[2] - Workxv.data[2])
				            +SQR(Originalyv.data[0] - Workyv.data[0])
			    	        +SQR(Originalyv.data[1] - Workyv.data[1])
							+SQR(Originalyv.data[2] - Workyv.data[2])
				            +SQR(Originalzv.data[0] - Workzv.data[0])
			    	        +SQR(Originalzv.data[1] - Workzv.data[1])
							+SQR(Originalzv.data[2] - Workzv.data[2]);
				
				difference = sqrt(difference);
			
				if(difference < differenceMin){
					phiMin   = nphi;
					thetaMin = ntheta;
					psiMin   = npsi;
					differenceMin = difference;
				}
				else{
				}
			}
			}
			}
			phiHigh   = phiMin + Delta;
			phiLow    = phiMin - Delta;
			thetaHigh = thetaMin + Delta;
			thetaLow  = thetaMin - Delta;
			psiHigh   = psiMin + Delta;
			psiLow    = psiMin - Delta;
			Delta /= 10;
			count++;
		}while(count < 5);
		
		linfo->phi[i]   = fmod(phiMin + 2*M_PI, 2*M_PI);
		linfo->theta[i] = fmod(thetaMin + M_PI, M_PI);
		linfo->psi[i]   = fmod(psiMin + 2*M_PI, 2*M_PI);
	}
}
