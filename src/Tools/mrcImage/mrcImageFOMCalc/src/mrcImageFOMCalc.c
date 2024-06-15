/*
# mrcImageFOMCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageFOMCalc
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
//#undef  DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "mrcImage.h"
#include "lmrcImageFOMCalc.h"


int
main(int argc, char* argv[]) 
{
	mrcImageFOMCalcInfo info;
	mrcImage* in;
	mrcImage  ref;
	lmrcImageFOMCalcInfo linfo;
	int i, k, sector;	
	double* FOM;
	double* XXMax;
	double** Scale;
	double  XMax;
	int*    Num;
	double nRing;
	char s[1024];
	double* allAreaScale;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	// Input Files
	if(info.flagIn && info.flagInList) {
		fprintf(stderr, "You should select -i or -I.\n");
		exit(EXIT_FAILURE);
	} else if(info.flagIn) {
		in = memoryAllocate(sizeof(mrcImage)*1, "in main");
		linfo.inImageNumber = 1;
		linfo.Weight        = memoryAllocate(sizeof(double)*1, "in main");
		linfo.Weight[0]     = info.Weight; 
		mrcFileRead(in, info.In, "in main", 0);
		DEBUGPRINT2("%s %f\n", info.In, linfo.Weight[0])
	} else if(info.flagInList)	{
		in = memoryAllocate(sizeof(mrcImage)*info.flagInList, "in main");
		linfo.inImageNumber = info.flagInList;
		linfo.Weight        = memoryAllocate(sizeof(double)*info.flagInList, "in main");
		fseek(info.fptInListList, 0L, SEEK_SET);
		for(i=0; i<linfo.inImageNumber; i++) {
			mrcFileRead(&in[i], info.InList[i], "in main", 0);
			stringGetFromFile(s, "in main", info.fptInListList, stdout, 3);
			linfo.Weight[i] = stringGetNthRealData(s, 2, " ,\t");
		}
	} else {
		fprintf(stderr, "You should select -i or -I.\n");
		exit(EXIT_FAILURE);
	}

	// Input Ref.
	mrcFileRead(&ref, info.Ref, "in main", 0);

	linfo.deltaAlpha = info.dAlpha*RADIAN; 
	linfo.flagRScale = info.RScale;


	allAreaScale = memoryAllocate(sizeof(double)*linfo.inImageNumber, "in main"); 
	if(info.flagAASRMax) {
		float X, Y, Z;
		double dat1, dat2, sum1, sum2;
		double RRLimit, delX, delY, delZ;
		DEBUGPRINT1("All Area Scaling Calc. Start: %d\n", linfo.inImageNumber);
		sum1 = sum2 = 0.0;
		RRLimit = SQR(info.AASRMax);
		delX = 1.0/in->HeaderLength.x/in->HeaderN.x; 
		delY = 1.0/in->HeaderLength.y/in->HeaderN.y; 
		delZ = 1.0/in->HeaderLength.z/in->HeaderN.z; 
		for(i=0; i<linfo.inImageNumber; i++) {
			for(Z=-in->HeaderN.z/2.0; Z< in->HeaderN.z/2.0; Z++) {
			for(Y=-in->HeaderN.y/2.0; Y< in->HeaderN.y/2.0; Y++) {
			for(X=0;                  X<=in->HeaderN.x/2.0; X++) {  
				if(SQR(((int)(X+0.5))*delX)+SQR(((int)(Y+0.5))*delY)+SQR(((int)(Z+0.5))*delZ)<RRLimit) {
					mrcPixelDataGet(&in[i],  X, Y, Z, &dat1, mrcPixelMag, mrcPixelHowNearest);	
					mrcPixelDataGet(&ref,    X, Y, Z, &dat2, mrcPixelMag, mrcPixelHowNearest);	
					sum1 += dat1;
					sum2 += dat2;
				}
			}
			}
			}
			allAreaScale[i] = sum2/sum1; 
			DEBUGPRINT4("ScalingFactor %d: %g = %g/%g\n", i, allAreaScale[i], sum1, sum2);
		}
	}

	if(0<info.dR) {
		nRing = (int)((info.Rmax - info.Rmin)/info.dR); 	
	} else {
		nRing = 1;
		info.dR = info.Rmax - info.Rmin;
	}
	FOM   = memoryAllocate(sizeof(double) *nRing, "in main"); 
	Num   = memoryAllocate(sizeof(int)    *nRing, "in main"); 
	Scale = memoryAllocate(sizeof(double*)*nRing, "in main"); 
	XXMax = memoryAllocate(sizeof(double) *nRing, "in main"); 

	linfo.delSector = M_PI/2.0/info.nSector; 
	for(sector=0; sector<info.nSector; sector++) {
		linfo.minSector =  sector   *linfo.delSector;
		linfo.maxSector = (sector+1)*linfo.delSector;
		// Calculation
		XMax = 0;
		for(i=0; i<nRing; i++) {
			linfo.minR =  i   *info.dR + info.Rmin;
			linfo.maxR = (i+1)*info.dR + info.Rmin;

			// Set Scale(R)
			Scale[i] = memoryAllocate(sizeof(double)*linfo.inImageNumber, "in main");
			for(k=0; k<linfo.inImageNumber; k++) {
				if(info.AutoScale) {
					Scale[i][k] = lmrcImageFOMScaleCalc(&in[k], &ref, &linfo, 0);
				} else if(info.flagAASRMax){
					Scale[i][k] = allAreaScale[k];
				} else {
					Scale[i][k]	= 1.0;
				}
			}

			// Set XXMax
			linfo.Scale = Scale[i];
			XXMax[i] = lmrcImageFOMXMaxCalc(in, &ref, &linfo, 0);
			if(XMax<XXMax[i]) {
					XMax = XXMax[i];
			}
			// FOM[i] = i; // For test for memoryArea
		}

		//DEBUGPRINT1("XMax: %g\n", XMax);
		for(i=0; i<nRing; i++) {
			linfo.minR =  i   *info.dR + info.Rmin;
			linfo.maxR = (i+1)*info.dR + info.Rmin;
			linfo.Scale = Scale[i];

			if(info.flagXMax)  {
				linfo.XXMax = info.XMax;
			} else {
				linfo.XXMax = XXMax[i];
			}

			FOM[i] = lmrcImageFOMCalc(in, &ref, &linfo, 0);	
			Num[i] = linfo.Num;
			// FOM[i] = i; // For test for memoryArea
		}


		// 
		// Output
		//
		fprintf(info.fptOut, "##Sector index %5d/%5d %11.2f %11.2f %11.2f\n", sector, info.nSector, linfo.minSector*DEGREE, linfo.maxSector*DEGREE, linfo.delSector*DEGREE)	;
		fprintf(info.fptOut, "##%11s %13s %13s %13s %13s %13s\n", "minR<", "<=maxR", "FOM", "Num", "XMax", "Scaling")	;
		for(i=0; i<nRing; i++) {
			linfo.minR = i    *info.dR + info.Rmin;
			linfo.maxR = (i+1)*info.dR + info.Rmin;
			fprintf(info.fptOut, "%13.4e %13.4e %13.4f %13d %13.4e", linfo.minR, linfo.maxR, FOM[i], Num[i], XXMax[i]);	
			for(k=0; k<linfo.inImageNumber; k++) {
					fprintf(info.fptOut, " %13.4e", Scale[i][k]*linfo.Weight[k]);
			}
			fprintf(info.fptOut, "\n");
		}
	} // sector
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">> -I FileFormat \n");
	fprintf(stderr, "mrc[0]   weight[0]\n");
	fprintf(stderr, "mrc[1]   weight[1]\n");
	fprintf(stderr, ".....\n");
	fprintf(stderr, "mrc[n-1] weight[n-1]\n");
	fprintf(stderr, "This algorithm is originated from K. Yonekura for Layer Lines. Nature/SupplmentTable 2 \n");
}
