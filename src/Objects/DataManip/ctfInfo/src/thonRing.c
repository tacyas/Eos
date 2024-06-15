/*
# thonRing.c  1.3
# The latest update : 01/20/97 at 11:44:16
#
#@(#) thonRing ver 1.3
#@(#) Created by 
#@(#)
#@(#) Usage : thonRing 
#@(#) Attention
#@(#)
*/

static char __sccs_id[] = "@(#)thonRing ver1.3; Date:97/01/20 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include "../inc/ctfInfo.h"
#define UNDEBUG
#include "genUtil.h"

/*
# thonRing.c  1.3
# The latest update : 01/20/97 at 11:44:16
#
#@(#) defocusDeterminationFromThonRing ver 1.3
#@(#) Created by 
#@(#)
#@(#) Usage : float defocusDeterminationFromThonRing(ctfInfo* info, float R, long n, long mode)
#@(#) Attention
#@(#)
*/
static char __sccs_id0[] = "@(#)defocusDeterninationFromThonRing ver1.3; Date:97/01/20 @(#)";
float 
defocusDeterminationFromThonRing(ctfInfo* info, float R, long n, long mode)
{
	float defocus;
	float lambda;
	float RR, Cs, Rlim;
	float phi;  /* CTF = -[sin(a) + Acos(a)] = sqrt(A*A + 1) * sin (a + phi) */
	float A;    /* Amplitude Contrast */ 

	lambda = wavelengthOfElectron(info->kV*1000);
	RR = R*1e10;
	Cs = info->Cs*1.0e-3;
	A  = info->ratioOfAmpToPhase;

	switch((ctfInfoModeWithAmplitudeContrast & info->mode)) {
		case ctfInfoModePhaseCTFOnly: {
			defocus = (n/(lambda*SQR(RR)) + 1.0/2.0*Cs*SQR(lambda)*SQR(RR));
			DEBUGPRINT4("%15.6e %15.6e %15.6e %15.6e\n", lambda, RR, Cs, defocus);
		}
		case ctfInfoModePhaseAndAmpCTF: {
			phi  = acos(1/(sqrt(A*A+1)));
			defocus = (n/(lambda*SQR(RR)) + 1.0/2.0*Cs*SQR(lambda)*SQR(RR) - phi/(lambda*SQR(RR)*M_PI));
			DEBUGPRINT6("%15.6e %15.6e %15.6e %15.6e %15.6e %15.6e \n", lambda, RR, Cs, defocus, phi, phi2);
			break;
		}
		default: {
			defocus = 0.0;
			fprintf(stderr, "Not supported ctf mode in defocusDeterminationFromThonRing: %d\n", info->mode);
			exit(EXIT_FAILURE);
		}
	}				

	if(0<n) { 
		Rlim = sqrt(defocus/Cs/lambda/lambda);
		if(Rlim < RR) {
			fprintf(stderr, "defocusDeterminationFromThonRing : not supported R(%15.6e) > Rlim(%15.6e)\n", RR, Rlim);	
		}
	}
	info->defocus = defocus*1.0e10;
	return defocus;
}
