#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#undef DEBUG
#include "../inc/config.h"
#include "genUtil.h"
#include "lctfDetermination.h"
#include "powerspectraTangentLine.h"
#include "lmrcFSInfoScatteringAngularDistributionAverageSection.h"
#include "lastigmatismDetection.h"
#include "mrcImage.h"
#include "Vector.h"
#include "ctfInfo.h"
#include "ctfInfoWrite2.h"
#include "nr2.h"
#include "Memory.h"

extern void info2ctfInfo(ctfInfo* ctf, ctfDetermineInfo info, int mode);

int
main(int argc, char* argv[]) 
{
	int  i;
	long status;
	ctfDetermineInfo info;
	lctfDetermineInfo linfo;
	long ThonRing;
	mrcImage mrc;
	mrcImage *mrcSection;
	ctfInfo result;
	ctfInfo var;
	ctfInfo initial;
	floatVector* defocus;
	floatVector* E;
	double *defocusOfSection;
	
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	
	defocus = floatVectorInit(NULL,2000);
	E       = floatVectorInit(NULL,2000);
	mrcFileRead(&mrc, info.In, "in main", 0);
	info2ctfInfo(&initial, info, 0);
	if(info.flagconfigFile) {
		ctfInfoRead(info.fptconfigFile, &initial, "", 0);
	}
	info2ctfInfo(&initial, info, 1);
	//ctfInfoWrite(stdout, initial, "", 0);

	initial.mode    = 1;
	result = var = initial;
	ThonRing = -1;

	linfo.degree = info.degree;
	linfo.step  = info.step;
	linfo.max   = info.max;
	linfo.min   = info.min;
	linfo.noise = MemoryAllocate(float,info.degree+1,"in ctfDetermine");
	if(linfo.min > linfo.max){
		fprintf(stderr, "min is higher than max !\n");
		exit(1);
	}
	switch(info.mode&0x000000F0) {
		case 0: {
			lctfDeterminationbyMinMaxMethods(&result, &mrc, &initial, 0x0000000F&info.mode);
			result.defocus2D[0] = result.defocus2D[1] = result.defocus;
			result.defocus0axis = 0;
			ctfInfoWrite(info.fptOut, result, "", 0);
			break;
		}
		case 16: {
			fprintf(stdout, "Fitting Start!!!");
			lctfDeterminationbyFittingMethods(&result, &var, &mrc, &initial, 0x0000000F&info.mode);
			result.defocus2D[0] = result.defocus2D[1] = result.defocus;
			result.defocus0axis = 0;
			ctfInfoWrite(info.fptOut, result, "", 0);
			ctfInfoWrite(info.fptOut, var,    "d", 0);
			break;
		}
		case 32 : {
			lctfDeterminationbyDifferentialMethods(&result, &mrc, &initial,&ThonRing, 0x0000000F&info.mode);
			result.defocus2D[0] = result.defocus2D[1] = result.defocus;
			result.defocus0axis = 0;
			ctfInfoWrite(info.fptOut, result, "", 0);
			break;
		}

		case 64 : {
			lctfDeterminationbyCovarianceMethods(&result, &mrc, &initial, &ThonRing,0x0000000F&info.mode);
			result.defocus2D[0] = result.defocus2D[1] = result.defocus;
			result.defocus0axis = 0;
			ctfInfoWrite(info.fptOut, result, "", 0);
			break;
		}

		case 96 : {
			lctfDeterminationbyMixMethods(&result, &mrc, &initial, &ThonRing,0x0000000F&info.mode);
			result.defocus2D[0] = result.defocus2D[1] = result.defocus;
			result.defocus0axis = 0;
			ctfInfoWrite(info.fptOut, result, "", 0);
			break;
		}
		case 128 : {
			lctfDeterminationbyMinSquareMethods(&result, &mrc, &initial, &ThonRing,&linfo,defocus,E,0x0000000F&info.mode);
			result.defocus2D[0] = result.defocus2D[1] = result.defocus;
			result.defocus0axis = 0;
			ctfInfoWrite(info.fptOut, result, "", 0);
			break;
		}
		case 160:{ /*with MinsquareMethod*/
			switch(0x000000F&info.mode) {
				case 0: {
					lctfDeterminationbyMinSquareMethods(&result, &mrc, &initial, &ThonRing,&linfo,defocus,E,0x0000000F&info.mode);
					lctfDeterminationByTangent(&result, &mrc, &initial,&linfo,defocus,E, 0x0000000F&info.mode);
					break;
				}
				case 1: {
					lctfDeterminationbyMinSquareMethods(&result, &mrc, &initial, &ThonRing,&linfo,defocus,E,0x0000000F&info.mode);
					lctfDeterminationByTangent(&result, &mrc, &initial,&linfo,defocus,E, 0x0000000F&info.mode);
					break;
				}
				case 3: {	
					lctfDeterminationbyMinSquareMethods(&result, &mrc, &initial, &ThonRing,&linfo,defocus,E,0x0000000F&info.mode);
					EnvelopeDetermine(&result, &mrc, &initial,&linfo,defocus,E, 0x0000000F&info.mode);
					break;
				}
				case 7: {
					lctfDeterminationbyMinSquareMethodsWithAcomp(&result, &mrc, &initial, &ThonRing,&linfo,defocus,E,0);
					break;
				}
				default: {
					fprintf(stderr, "Not supported Mode\n");
					break;
				}
			}
			result.defocus2D[0] = result.defocus2D[1] = result.defocus;
			result.defocus0axis = 0;
			ctfInfoWrite(info.fptOut, result, "", 0);
			ctfInfoWrite2(info.fptOut, linfo, "");
			break;
		}
		case 176 :{
			lastigmatismDetectionInfo llinfo;
			mrcSection          =  MemoryAllocate(mrcImage,info.section,"in ctfDetermine");
			defocusOfSection    =  MemoryAllocate(double,info.section,"in ctfDetermine");
			for(i = 0 ; i < info.section ; i++){
				mrcFileRead(&mrc, info.In, "in main", 0);
				info2ctfInfo(&initial, info, 0);
				mrcSection[i] = mrc;
				lmrcFSInfoScatteringAngularDistributionAverageSection(&mrcSection[i],(i-0.5)*180.0/info.section,(i+0.5)*180.0/info.section);

				lctfDeterminationbyMinSquareMethods(&result, &mrc, &initial, &ThonRing,&linfo,defocus,E,0x0000000F&info.mode);

				defocusOfSection[i] = lctfDeterminationByTangent(&result, &mrc, &initial,&linfo,defocus,E, /*0x0000000F&info.mode*/2);
				fprintf(stdout,"defocus = %lf\n",defocusOfSection[i]);
			}
			llinfo.defocus     = defocusOfSection;
			llinfo.sectionSize = info.section; 
			lastigmatismDetection(&result, llinfo, 0);
			ctfInfoWrite(info.fptOut, result, "", 0);
			//mrcFileWrite(&mrcSection[2], "test.mrc", "in main", 0);
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode\n");
			break;
		}
	}

	ctfInfoWrite(info.fptOut, result, "", 0);
	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, ">>> Mode <<< \n");
	fprintf(stderr, "	  0 : MinMax Methods (Henderson-like CTF determination) \n");
	fprintf(stderr, "	  16: Fitting Methods \n");
	fprintf(stderr, "	  32: Differential Methods \n");
	fprintf(stderr, "	  64: Covariance Methods \n");
	fprintf(stderr, "	  96: Differential & covariance  Methods \n");
	fprintf(stderr, "	 128: MinSquare Methods \n");
	fprintf(stderr, "	 160: Differential+MinSquare Methods by Imamura \n");
	fprintf(stderr, "	 161: Differential+MinSquare Methods+NoiseRemoval(+1) \n");
	fprintf(stderr, "	 163: Differential+MinSquare Methods+NoiseRemoval(+1)+EnvelopeFromLocalMaxima(+2) \n");
	fprintf(stderr, "\n");
}

void 
info2ctfInfo(ctfInfo* ctf, ctfDetermineInfo info, int mode)
{
	switch(mode) {
		case 0: {
			ctf->kV      = info.Ac;
			ctf->defocus = info.Defocus;
			ctf->Cs      = info.Cs;
			ctf->Cc      = info.Cc;
			ctf->dE      = info.dE;
			ctf->CutLow  = info.CutLow;
			ctf->CutHigh = info.CutHigh;
			ctf->I0      = info.I0;
			ctf->Ain     = info.Ai;
			ctf->ratioOfAmpToPhase = info.ratioOfAmpToPhase;
			ctf->BofMTF  = info.BofMTF;
			ctf->BofVibration = info.BofVibration;
			ctf->WhiteNoise  = info.WhiteNoise;
			ctf->WhiteNoise2 = info.WhiteNoise2;
			ctf->MolecEnv    = info.MolcEnv;
			ctf->Magnification = info.Magnification;
			ctf->flagVibration = info.flagBofVibration;
			ctf->flagWhiteNoise = info.flagWhiteNoise;
			ctf->flagWhiteNoise2 = info.flagWhiteNoise2;
			if(info.flagMolcEnvTable) {
				ctf->flagMolecEnvTable = 1;
				ctf->MolecEnvTable.filename = strdup(info.MolcEnvTable);
				lmolecularEnvelopeFileRead(info.fptMolcEnvTable, &(ctf->MolecEnvTable), 0); 
			}
			break;
		}
		case 1: {
			if(info.flagAc) {
				ctf->kV      = info.Ac;
			}
			if(info.flagDefocus) {
				ctf->defocus = info.Defocus;
			}
			if(info.flagCs) {
				ctf->Cs      = info.Cs;
			}
			if(info.flagCc) {
				ctf->Cc      = info.Cc;
			}
			if(info.flagdE) {
				ctf->dE      = info.dE;
			}
			if(info.flagCutLow) {
				ctf->CutLow  = info.CutLow;
			}
			if(info.flagCutHigh) {
				ctf->CutHigh = info.CutHigh;
			}
			if(info.flagI0) {
				ctf->I0      = info.I0;
			}
			if(info.flagAi) {
				ctf->Ain     = info.Ai;
			}
			if(info.flagratioOfAmpToPhase) {
				ctf->ratioOfAmpToPhase = info.ratioOfAmpToPhase;
			}
			if(info.flagBofMTF) {
				ctf->BofMTF  = info.BofMTF;
			}
			if(info.flagBofVibration) {
				ctf->BofVibration = info.BofVibration;
			}
			if(info.flagWhiteNoise) {
				ctf->WhiteNoise  = info.WhiteNoise;
			}	
			if(info.flagWhiteNoise2) {
				ctf->WhiteNoise2 = info.WhiteNoise2;
			}
			if(info.flagMolcEnv) {
				ctf->MolecEnv    = info.MolcEnv;
			}
			if(info.flagMagnification) {
				ctf->Magnification = info.Magnification;
			}
			if(info.flagMolcEnvTable == 1 && ctf->flagMolecEnvTable != 1) {
				ctf->flagMolecEnvTable = 1;
				ctf->MolecEnvTable.filename = strdup(info.MolcEnvTable);
				lmolecularEnvelopeFileRead(info.fptMolcEnvTable, &(ctf->MolecEnvTable), 0); 
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in info2linfo: %d \n", mode);
			break;
		}
	}
}

