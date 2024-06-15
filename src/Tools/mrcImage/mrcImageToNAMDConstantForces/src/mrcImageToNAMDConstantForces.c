/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageToNAMDConstantForces ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageToNAMDConstantForces
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageToNAMDConstantForces ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "pdbFile.h"
#include "Random.h"

typedef struct lmrcImageToNAMDInfo {
	int flagContour;
	float Seed;
	float Contour;	
	float Weight;

	int flagRotate;
	float RWeight;

	float ScalingFactor;

	int   flagNoWater;

} lmrcImageToNAMDInfo;

extern void lmrcImageToNAMDConstantForces(pdbFile* pdb, mrcImage* mrc, lmrcImageToNAMDInfo* linfo, long mode);

int
main(int argc, char* argv[]) 
{
	mrcImageToNAMDConstantForcesInfo info;
	lmrcImageToNAMDInfo linfo;
	
	mrcImage mrc;
	pdbFile  pdb;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptInPDB, &pdb);
	mrcFileRead(&mrc, info.In, "in main", 0);

	linfo.Weight = info.Weight;
	linfo.ScalingFactor = info.ScalingFactor;

	linfo.flagContour = info.flagContour;
	linfo.Contour     = info.Contour;

	linfo.Seed = info.Seed;
	
	linfo.flagRotate = info.flagRotate;
	linfo.RWeight    = info.RWeight;

	linfo.flagNoWater = info.nowater;

	lmrcImageToNAMDConstantForces(&pdb, &mrc, &linfo, 0);

	pdbFileWrite(info.fptOut, &pdb);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "More Density is lower potential.\n");
}


void
lmrcImageToNAMDConstantForces(pdbFile* pdb, mrcImage* mrc, lmrcImageToNAMDInfo* linfo, long mode)
{
	pdbFileParaTypeReal x, y, z;
	double data100, data010, data001;
	double data_00, data0_0, data00_;
	double dataX, dataY, dataZ;
	double data000;
	double Rotate[7];
	double Paralel[4];
	double vector_a,vector_r,vector_r0_r;
	double Rotate_x,Rotate_y,Rotate_z,Rotate_omega,Rotate_theta,Rotate_phi;
	double Rotate00;
	double Paralel_x,Paralel_y,Paralel_z;
	double vector_a_x,vector_a_y,vector_a_z;
	double vector_r0_x,vector_r0_y,vector_r0_z;
	double Rotate_X,Rotate_Y,Rotate_Z,Rotate_R;
	double Rotate_RR, Rotate_RX, Rotate_RY, Rotate_RZ;
	double pai=M_PI;
	int i;
	
	if(linfo->flagRotate) {	
		if(0.0==linfo->Seed){
			srandomByTime();
		} else {
			srand(linfo->Seed);
		}	
		for(i=0; i<7; i++){	
			Rotate[i]= random();
		}
		for(i=0; i<4; i++){
			Paralel[i]= random();
		}

		Paralel_x = Paralel[0];
		Paralel_y = Paralel[1];
		Paralel_z = Paralel[2];

		/* Centre of Rotation */
		while(1) {
			Rotate_x = (Rotate[0]*mrc->HeaderN.x + mrc->HeaderStartN.x)*mrc->HeaderLength.x;
			Rotate_y = (Rotate[1]*mrc->HeaderN.y + mrc->HeaderStartN.y)*mrc->HeaderLength.y;
			Rotate_z = (Rotate[2]*mrc->HeaderN.z + mrc->HeaderStartN.z)*mrc->HeaderLength.z;
			mrcImageDataGetbyAU(mrc, Rotate_x, Rotate_y, Rotate_z, &data000, mrcPixelRePart, mrcPixelHowCubicConv);
			if(0 == linfo->flagContour) {
				break;
			} else if(1==linfo->flagContour && data000 < linfo->Contour) {
				break;
			}

			for(i=0; i<3; i++){	
				Rotate[i]= random();
			}
		}
		/* Rotation Axis */
		Rotate_theta = Rotate[3];
		Rotate_phi   = Rotate[4];

		vector_a_x = sin(Rotate_theta*pai)*cos(Rotate_phi*2.0*pai);
		vector_a_y = sin(Rotate_theta*pai)*sin(Rotate_phi*2.0*pai);
		vector_a_z = cos(Rotate_theta*pai);
		vector_a   = sqrt(SQR(vector_a_x)+SQR(vector_a_y)+SQR(vector_a_z));

		/* Rotation Angle */
		Rotate_omega = Rotate[5];
	}

	pdbFileTop(pdb);
	while(1) {
		if(pdbFileIsAtom(pdb)) {

			pdbFileCoordGet(pdb, &x, &y, &z);
	
			if( 0 == linfo->flagNoWater
			 ||(1 == linfo->flagNoWater && 0!=strncmp("WAT", pdbFileResidueNameGet(pdb,RESIDUE_THREECHAR_MODE), 3))) {
				/* Not Water */
				mrcImageDataGetbyAU(mrc, x, y, z, &data000, mrcPixelRePart, mrcPixelHowCubicConv);
				if( 0 == linfo->flagContour 
				 ||(1 == linfo->flagContour && data000 < linfo->Contour)) {
					mrcImageDataGetbyAU(mrc, x+mrc->HeaderLength.x, y, z, &data100, mrcPixelRePart, mrcPixelHowCubicConv);
					mrcImageDataGetbyAU(mrc, x, y+mrc->HeaderLength.y, z, &data010, mrcPixelRePart, mrcPixelHowCubicConv);
					mrcImageDataGetbyAU(mrc, x, y, z+mrc->HeaderLength.z, &data001, mrcPixelRePart, mrcPixelHowCubicConv);
					mrcImageDataGetbyAU(mrc, x-mrc->HeaderLength.x, y, z, &data_00, mrcPixelRePart, mrcPixelHowCubicConv);
					mrcImageDataGetbyAU(mrc, x, y-mrc->HeaderLength.y, z, &data0_0, mrcPixelRePart, mrcPixelHowCubicConv);
					mrcImageDataGetbyAU(mrc, x, y, z-mrc->HeaderLength.z, &data00_, mrcPixelRePart, mrcPixelHowCubicConv);
					/*gradient*/
					dataX = (data100 - data_00)/mrc->HeaderLength.x/2.0*linfo->Weight;
					dataY = (data010 - data0_0)/mrc->HeaderLength.y/2.0*linfo->Weight;
					dataZ = (data001 - data00_)/mrc->HeaderLength.z/2.0*linfo->Weight;
					
					if(linfo->flagRotate){
						vector_r0_x = x - Rotate_x;
						vector_r0_y = y - Rotate_y;
						vector_r0_z = z - Rotate_z;
						vector_r0_r = SQR(vector_r0_x)+SQR(vector_r0_y)+SQR(vector_r0_z);
						
						Rotate_R = vector_r0_r - SQR(vector_r0_x*vector_a_x+vector_r0_y*vector_a_y+vector_r0_z*vector_a_z);
						if(Rotate_R<=0) {
							Rotate_R = 0;
						} else {
							Rotate_R = sqrt(Rotate_R);
						}
					
						Rotate_RX = vector_a_y*vector_r0_z - vector_a_z*vector_r0_y;
						Rotate_RY = vector_a_z*vector_r0_x - vector_a_x*vector_r0_z;
						Rotate_RZ = vector_a_x*vector_r0_y - vector_a_y*vector_r0_x;
						Rotate_RR = sqrt(SQR(Rotate_RX) + SQR(Rotate_RY) + SQR(Rotate_RZ));

						Rotate_X = Rotate_RX/Rotate_RR * Rotate_omega * Rotate_R * linfo->RWeight;
						Rotate_Y = Rotate_RY/Rotate_RR * Rotate_omega * Rotate_R * linfo->RWeight;
						Rotate_Z = Rotate_RZ/Rotate_RR * Rotate_omega * Rotate_R * linfo->RWeight;
						
						dataX += Rotate_X;
						dataY += Rotate_Y;
						dataZ += Rotate_Z;
						
						/*
						dataX += Rotate_X + Paralel_x * linfo->RWeight;
						dataY += Rotate_Y + Paralel_y * linfo->RWeight;
						dataZ += Rotate_Z + Paralel_z * linfo->RWeight;
						*/
					}	
				} else { /* Protein Core */
					dataX = 0.0; 
					dataY = 0.0; 
					dataZ = 0.0; 
				}
			} else { /* Water */
				dataX = 0.0; 
				dataY = 0.0; 
				dataZ = 0.0; 
			}
			pdbFileCoordSet(pdb, dataX, dataY, dataZ);	
			pdbFileOccupancySet(pdb, linfo->ScalingFactor);
		}
		if(pdbFileEnd(pdb)) {
			break;
		} else {
			pdbFileNext(pdb);
		}
	}
}

