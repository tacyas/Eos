/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfZeroPoint ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfZeroPoint
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfZeroPoint ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "ctfInfo.h"
#include "ctfZeroPoint.h"

int
main(int argc, char* argv[]) 
{
	ctfZeroPointInfo info;
	ctfInfo CTFInfo;
	ctfInfoZeroPoint CTFInfoZeroPoint;
	float result;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	CTFInfo.Cs = info.Cs;
	CTFInfo.defocus = info.Defocus;
	CTFInfo.kV = info.kV;
	CTFInfo.mode = info.ctfMode;
	CTFInfo.ratioOfAmpToPhase = info.AoverP;
	CTFInfo.Ain = info.Ain;

	CTFInfoZeroPoint.RMax = info.RMax;
	CTFInfoZeroPoint.dR   = info.dR;
	CTFInfoZeroPoint.N    = info.N;

	fprintf(info.fptOut, "[ZeroPointResult] AmpContrast %15f \n", CTFInfo.ratioOfAmpToPhase);
	fprintf(info.fptOut, "Amount of Defocus [A]  Number          R [A] ......... \n");

	switch(info.mode) {
		case 0: {
			result = ctfZeroPoint(&CTFInfo, &CTFInfoZeroPoint, 0);
			fprintf(info.fptOut, "%15f %d %15f \n", info.Defocus, CTFInfoZeroPoint.N, result);
			break;
		}
		case 1: {
			int N;
			fprintf(info.fptOut, "%15f %d", info.Defocus, CTFInfoZeroPoint.N);
				for(N=1; N<=info.N; N++){ 				
				CTFInfoZeroPoint.N  = N;
				result = ctfZeroPoint(&CTFInfo, &CTFInfoZeroPoint, 0);
				fprintf(info.fptOut, "%15f", result);
				}
			fprintf(info.fptOut, "\n");
			break;
		}
		case 2: {
			int N;
			int Number;
			float Defocus;
			Number = info.N;
			for(Defocus=info.MinDefocus; Defocus<=info.MaxDefocus; Defocus+=info.DeltaDefocus){ 				
				CTFInfo.defocus = Defocus;
				fprintf(info.fptOut, "%15f %15d ", Defocus, Number);
					for(N=1; N<=info.N; N++){ 				
						CTFInfoZeroPoint.N  = N;
						result = ctfZeroPoint(&CTFInfo, &CTFInfoZeroPoint, 0);
						fprintf(info.fptOut, "%15f", result);
					}	
				fprintf(info.fptOut, "\n");
			}	
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode :%ld in CTFZeroPoint\n", info.mode);
			break;
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, ">>>> ctfMode <<<< \n");
	fprintf(stderr, " 0: Phase CTF \n");
	fprintf(stderr, " 1: PhaseCTF + ratio*AmpCTF \n");
	fprintf(stderr, ">>>> mode <<<< \n");
	fprintf(stderr, " Result Type \n");
	fprintf(stderr, " 0: One zero point \n");
	fprintf(stderr, " 1: All zero points \n");
	fprintf(stderr, " 2: All zero points along defocus \n");
}
