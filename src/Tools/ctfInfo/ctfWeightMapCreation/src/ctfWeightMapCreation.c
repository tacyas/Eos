#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#include "genUtil.h"
#include "Vector.h"
#include "ctfInfo.h"

void
main(int argc, char* argv[]) 
{
	ctfWeightMapCreationInfo info;
	long nR, iR;
	ctfInfo CTFInfo;
	float dR, RMax;
	floatVector* R;
	floatVector* CTF;
	floatVector* Weight;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	RMax = 1/info.dRmaxInv;
	dR   = 1/info.dRinv;
	nR = RMax/dR + 1;
	CTFInfo.Cs      = info.Cs;
	CTFInfo.defocus = info.Defocus;
	CTFInfo.kV      = info.kV;

	R = floatVectorInit(NULL, nR);
	CTF = floatVectorInit(NULL, nR);
	Weight = floatVectorInit(NULL, nR);

	switch(info.mode) {
		case 0:
		case 1: 
		case 2:
		case 3:
		case 4: {
			CTFInfo.mode = 0;
			R->data[0]   = 0;
			CTF->data[0] = 1.0;
			Weight->data[0] = 1.0;
			for(iR=1; iR<nR; iR++) {
				R->data[iR]   = iR*dR;
				CTF->data[iR] = ctfFunction(&CTFInfo, R->data[iR], 0);
				Weight->data[iR] = ctfWeightForCorrection(&CTFInfo, R->data[iR], info.mode);
			}
			break;
		}
		case 5: { /* Winer filter : noise and splun power spectrum */
			mrcImage     mrcG;
			mrcImage     mrcN;
			floatVector* G;
			floatVector* N;
			if(!info.flagNoise || !info.flagSplusN) {
				fprintf(stderr, "This mode (%ld) requires the -noise and -splusn options\n", info.mode);
				usage(argv[0]);
			} else {
				mrcFileRead(&mrcG, info.SplusN, "in winer filter splusn", 0);	
				mrcFileRead(&mrcN, info.Noise,  "in winer filter splusn", 0);	
				R = lmrcFSInfoSpacing(&mrcG);
				G = lmrcFSInfoScatteringAngularDistributionAverage(&mrcG);
				N = lmrcFSInfoScatteringAngularDistributionAverage(&mrcN);
			}
			if(info.flagdRmaxInv || info.flagdRinv) {
				fprintf(stderr, "This mode will ignore -dRmax and -dR options\n");
			}
			CTFInfo.mode = 0;
			CTF->data[0] = 1.0;
			Weight->data[0] = 1.0;
			for(iR=1; iR<nR; iR++) {
				CTF->data[iR] = ctfFunction(&CTFInfo, R->data[iR], 0);
				Weight->data[iR] = CTF->data[iR]/fabs(CTF->data[iR])*(fabs(G->data[iR] - N->data[iR])/G->data[iR]);
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode : %ld\n", info.mode);
			exit(EXIT_FAILURE);
		}
	}
	/*Windowing*/
	if(info.flagSinWinRminInv && info.flagSinWinRmaxInv) {
		float RMin, RMax;
		RMin = 1/info.SinWinRminInv;
		RMax = 1/info.SinWinRmaxInv;
		for(iR=0; iR<nR; iR++) {
			if(RMin<=R->data[iR] && R->data[iR]<=RMax) {
				Weight->data[iR] = Weight->data[iR]*(0.5+0.5*cos((R->data[iR] - RMin)/(RMax - RMin)*M_PI));
			} else if(RMax<R->data[iR]) {
				Weight->data[iR] = 0.0;
			}
		}

	}
	/* Output*/
	for(iR=0; iR<nR; iR++) {
		fprintf(info.fptOut, "%15.6f %15.6f %15.6f\n", R->data[iR], Weight->data[iR], CTF->data[iR]);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "Mode:\n");
	fprintf(stderr, "      0: No correction  : F = G\n");
	fprintf(stderr, "      1: Phase contrast : F = G*(H/abs(H))(Only 1 or -1)\n");
	fprintf(stderr, "      2: Phase contrast : F = G*H (Winer filter (S/N << 1))\n");
	fprintf(stderr, "      3: Phase contrast : F = G/H (Inverse filter)\n");
	fprintf(stderr, "      4: Phase contrast : F = G*(H/(H*H + N*N)) (Winer filter (white noise : Required Option -white))\n");
	fprintf(stderr, "      5: Phase contrast : F = G*(H/abs(H)*abs(G*G-N*N)/(G*G)) (Winer filter: Required Option -noise, -splusn))\n");
}
