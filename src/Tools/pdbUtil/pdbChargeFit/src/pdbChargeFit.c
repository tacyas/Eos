/*
# pdbChargeFit.c  1.5
# The latest update : 12/17/96 at 16:20:48
#
#@(#) pdbChargeFit ver 1.5
#@(#) Created by Yu MENG
#@(#)
#@(#) Usage : pdbChargeFit
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)pdbChargeFit ver1.5; Date:96/12/17 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include "pdbFile.h"
#include "Vector.h"

#define GLOBAL_DECLARATION
#define PI (3.14159265358979)
#undef CHARGEDEBUG
#undef DEBUG
#include "../inc/config.h"

extern void lpdbChargeFit(pdbChargeFitInfo*);
void
main(int argc, char* argv[]) 
{
	long status;
	pdbChargeFitInfo info;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	lpdbChargeFit(&info);
	exit(EXIT_SUCCESS);
}

void lpdbChargeFit(pdbChargeFitInfo *info)
{
	pdbFile inFix;
	pdbFile inMove;
	pdbFile inFixCA;
	pdbFile inMoveCA;
	pdbFile tmpPdb;
	pdbRecord* fixPdbRecord;
	pdbRecord* movePdbRecord;
	floatVector *lengthV;
	float z;
	float phi;
	float rad;
	float score;
	float length;
	Matrix3D MatrixRot;
	Matrix3D MatrixShift0; /* to the (0, 0) coord */
	Matrix3D MatrixShift1; /* back to the original coord */

	pdbFileParaTypeReal X1,Y1,Z1;
	pdbFileParaTypeReal X2,Y2,Z2;


	tmpPdb.nAtom=0;
	tmpPdb.top = tmpPdb.PDB=NULL;
	inFixCA.nAtom=0;
	inFixCA.top = inFixCA.PDB=NULL;
	inMoveCA.nAtom=0;
	inMoveCA.top = inMoveCA.PDB=NULL;
	
	lengthV=floatVectorInit(lengthV,3);

	pdbFileRead(info->fptInFix,&inFix);
	pdbFileRead(info->fptInMove,&inMove);

	pdbFileCAOnlyCopyAll(&inFixCA,&inFix);
	pdbFileCAOnlyCopyAll(&inMoveCA,&inMove);

/* initialize MatrixShift0 and MatrixShift1 */
	matrix3DInit(MatrixShift0);
	matrix3DInit(MatrixShift1);

/*
         [0][0]   [1][0]   [2][0]   [3][0]    |x|
         [0][1]   [1][1]   [2][1]   [3][1] * | y |
         [0][2]   [1][2]   [2][2]   [3][2]   | z |
         [0][3]   [1][3]   [2][3]   [3][3]    |1|
 */
	
	MatrixShift0[3][0]=-info->axisX;
	MatrixShift0[3][1]=-info->axisY;
	MatrixShift1[3][0]= info->axisX;
	MatrixShift1[3][1]= info->axisY;
	pdbTrans(&inFixCA, MatrixShift0);
	pdbTrans(&inMoveCA,MatrixShift0);

	for(z=info->zmin;z<info->zmax;z=z+info->zDel){
		matrix3DInit(MatrixRot);
		phi=info->symmetry*z;
		rad=phi*PI/180;
        MatrixRot[0][0] =  cos(rad);
		MatrixRot[1][0] = -sin(rad);
		MatrixRot[0][1] =  sin(rad);
		MatrixRot[1][1] =  cos(rad);
		MatrixRot[3][2] = z;
		pdbFileCopyAll(&tmpPdb,&inMoveCA);
		pdbTrans(&tmpPdb,MatrixRot);
		score=0;
		fixPdbRecord=pdbFileTop(&inFixCA);
		while(NULL!=fixPdbRecord){
			#ifdef DEBUG
				fprintf(stderr,"fix pdb\n");
			#endif
			if(pdbFileIsCharge(&inFixCA)){
				pdbFileCoordGet(&inFixCA,&X1,&Y1,&Z1);
				movePdbRecord=pdbFileTop(&tmpPdb);
				while(NULL!=movePdbRecord){
					if(pdbFileIsCharge(&tmpPdb)){
						pdbFileCoordGet(&tmpPdb,&X2,&Y2,&Z2);
						lengthV->data[0]=X1-X2;
						lengthV->data[1]=Y1-Y2;
						lengthV->data[2]=Z1-Z2;
						length=(float)lfloatVectorLength(lengthV);
						#ifdef CHARGEDEBUG
							fprintf(stderr,"length=%f\n",length);
						#endif
						if(length<info->maxd){
							#ifdef CHARGEDEBUG
								fprintf(stderr,"length=%f\n",length);
							#endif
							if(length<info->mind){
								length=info->mind;
							}
							if(pdbFileIsNegative(&tmpPdb)){
								length= -length;
							}
							if(pdbFileIsNegative(&inFixCA)){
								length= -length;
							}
							score= score+1/(length*length);
						}
					}
					movePdbRecord=pdbFileNextAtom(&tmpPdb);
				}
			}
			fixPdbRecord=pdbFileNextAtom(&inFixCA);
		}
		fprintf(info->fptOutTxt,"%7.2f %7.3f %7.4f\n",z,phi,score);
	}

	return;
}
void
additionalUsage()
{
	fprintf(stderr, "----- Algorythm -----\n");
	fprintf(stderr, "score = Sum(1/SQR(length))\n");
	fprintf(stderr, ", where length is the set of length between charged atoms\n");
}
