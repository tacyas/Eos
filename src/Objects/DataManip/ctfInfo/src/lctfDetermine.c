/*
# lctfDetermine : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lctfDetermine 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#define DEBUG
#include "genUtil.h" 

#include "Memory.h"
#include "Vector.h"
//#include "nr2.h"
#include "mrcImage.h"
#include "lmrcFSInfoScatteringAngularDistributionAverageSection.h"
#include "./lctfDetermination.h"
#include "./lastigmatismDetection.h"

void
lctfDetermineUsage(FILE* fpt)
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
	fprintf(stderr, ">>>> Attention <<<\n");
	fprintf(stderr, "Change mode determined by Imamural\n");
}

void
lctfDetermine(ctfInfo* result, ctfInfo* var, mrcImage* mrc, lctfDetermineInfo* linfo, long mode)
{
	int i;
	long ThonRing;
	floatVector* E;
	floatVector* defocus;
	lastigmatismDetectionInfo llinfo;
	double* defocusOfSection;

	defocus = floatVectorInit(NULL, MAX(mrc->HeaderN.x, mrc->HeaderN.y)); 
	E		= floatVectorInit(NULL, MAX(mrc->HeaderN.x, mrc->HeaderN.y)); 
	defocusOfSection    =  MemoryAllocate(double, linfo->section, "in ctfDetermine");

	result->defocus0axis = 0;

	switch(mode&0x000000F0) {
		case 0: {
			lctfDeterminationbyMinMaxMethods(result, mrc, &linfo->initial, 0x0000000F&mode);
			result->defocus2D[0] = result->defocus2D[1] = result->defocus;
			break;
		}
		case 16: {
			fprintf(stdout, "Fitting Start!!!");
			lctfDeterminationbyFittingMethods(result, var, mrc, &linfo->initial, 0x0000000F&mode);
			result->defocus2D[0] = result->defocus2D[1] = result->defocus;
			break;
		}
		case 32 : {
			lctfDeterminationbyDifferentialMethods(result, mrc, &linfo->initial, &linfo->ThonRing, 0x0000000F&mode);
			result->defocus2D[0] = result->defocus2D[1] = result->defocus;
			break;
		}

		case 64 : {
			lctfDeterminationbyCovarianceMethods(result, mrc, 
					&linfo->initial, 
					&ThonRing, 
					0x0000000F&mode);
			result->defocus2D[0] = result->defocus2D[1] = result->defocus;
			break;
		}

		case 96 : {
			lctfDeterminationbyMixMethods(result, mrc, 
					&linfo->initial, 
					&ThonRing, 
					0x0000000F&mode);
			result->defocus2D[0] = result->defocus2D[1] = result->defocus;
			break;
		}
		case 128 : {
			lctfDeterminationbyMinSquareMethods(result, mrc, 
					&linfo->initial, 
					&ThonRing,
					linfo,
					defocus,
					E,
					0x0000000F&mode);
			result->defocus2D[0] = result->defocus2D[1] = result->defocus;
			break;
		}
		case 160:{ /*with MinsquareMethod*/
			switch(0x000000F&mode) {
				case 0: 
				case 1: 
				case 3:  {	
					lctfDeterminationbyMinSquareMethods(result, mrc, 
							&linfo->initial, 
							&ThonRing,
							linfo,
							defocus,
							E,
							0x0000000F&mode);
					EnvelopeDetermine(result, mrc, 
							&linfo->initial,
							linfo,
							defocus,
							E, 
							0x0000000F&mode);
					break;
				}
				case 7: {
					lctfDeterminationbyMinSquareMethodsWithAcomp(result, mrc, 
							&linfo->initial, 
							&ThonRing,
							linfo,
							defocus,
							E,
							0);
					break;
				}
				default: {
					fprintf(stderr, "Not supported Mode\n");
					break;
				}
			}
			result->defocus2D[0] = result->defocus2D[1] = result->defocus;
			break;
		}
		case 176 :{
			for(i = 0 ; i < linfo->section ; i++){
				lmrcFSInfoScatteringAngularDistributionAverageSection(
						mrc,
						(i-0.5)*180.0/linfo->section,
						(i+0.5)*180.0/linfo->section);

				lctfDeterminationbyMinSquareMethods(result, mrc, 
						&linfo->initial, 
						&ThonRing,
						linfo,
						defocus,
						E,
						0x0000000F&mode);

				defocusOfSection[i] = lctfDeterminationByTangent(result, mrc, 
						&linfo->initial, 
						linfo,
						defocus, 
						E, 
						0x0000000F&mode);
				fprintf(stdout,"defocus = %lf\n",defocusOfSection[i]);
			}
			llinfo.defocus     = defocusOfSection;
			llinfo.sectionSize = linfo->section; 
			lastigmatismDetection(result, llinfo, 0);
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode\n");
			break;
		}
	}
}

