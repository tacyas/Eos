/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMultiCTFDetermination ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : mrcImageMultiCTFDetermination
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMultiCTFDetermination ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "mrcImage.h"

typedef struct lmrcImageMultiCTFDeterminationInfo {
	ctfInfo* val;
	ctfInfo* min;
	ctfInfo* max;
	ctfInfo* del;
	mrcImageParaTypeReal Rmax;
	mrcImage Dif;

	double  minPhase;
	double* minDef;
	double  minRatio;
	FILE*   Out;
} lmrcImageMultiCTFDeterminationInfo;


extern void lmrcImageMultiCTFDetermination(lmrcImageMultiCTFDeterminationInfo* linfo, mrcImage* in, int n);

int
main(int argc, char* argv[]) 
{
	mrcImage* in;
	mrcImageMultiCTFDeterminationInfo  info;
	lmrcImageMultiCTFDeterminationInfo linfo;
	int i;
	char s[1024];
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.val = (ctfInfo*)memoryAllocate(sizeof(ctfInfo)*info.flagIn, "in main");
	linfo.min = (ctfInfo*)memoryAllocate(sizeof(ctfInfo)*info.flagIn, "in main");
	linfo.max = (ctfInfo*)memoryAllocate(sizeof(ctfInfo)*info.flagIn, "in main");
	linfo.del = (ctfInfo*)memoryAllocate(sizeof(ctfInfo)*info.flagIn, "in main");
	fseek(info.fptInList, 0L, SEEK_SET);
	for(i=0; i<info.flagIn; i++) {
		linfo.val[i].Ain     = 0.0;
    	linfo.val[i].Cs      = info.Cs;
    	linfo.val[i].kV      = info.kV;
    	linfo.val[i].mode    = ctfInfoModePhaseAndAmpCTF;
		stringGetFromFile(s, "", info.fptInList, stdout, 3); 
    	linfo.min[i].defocus = stringGetNthRealData(s, 2, " \t,");
    	linfo.max[i].defocus = stringGetNthRealData(s, 3, " \t,");
    	linfo.del[i].defocus = stringGetNthRealData(s, 4, " \t,");
    	linfo.min[i].ratioOfAmpToPhase= info.minAoverP;
    	linfo.max[i].ratioOfAmpToPhase= info.maxAoverP;
    	linfo.del[i].ratioOfAmpToPhase= info.delAoverP;
	}
    linfo.Rmax        = info.Rmax;
    linfo.Out = info.fptOut;    
	
	DEBUGPRINT("Image Read");
	in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main");
	for(i=0; i<info.flagIn; i++) {
		mrcFileRead(&(in[i]), info.In[i], "in main", 0);
	}

	DEBUGPRINT("CTF Determination\n");
    lmrcImageMultiCTFDetermination(&linfo, in, info.flagIn);
	if(info.flagOut2) {
		mrcFileWrite(&(linfo.Dif), info.Out2, "main", 0);
	}

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">>>> inputfile format <<<<\n");
	fprintf(stderr, "filename minDef[A] maxDef[A] deltaDef[A]\n");
	fprintf(stderr, ".....\n");
}

void
lmrcImageMultiCTFDetermination(lmrcImageMultiCTFDeterminationInfo* linfo, mrcImage* in, int n)
{
	mrcImage* inFFT;
	mrcImageParaTypeReal X, Y, delX, delY;
	mrcImageParaTypeReal*  def;
	mrcImageParaTypeReal*  CTF;
	int i, j, k, iRatio;
	int* nDef;
	int* iDef;
	int  nnDef, nnTmp;
	ctfInfo* tmp;
	double* Phase;
	double tmpPhase;
	double phase;
	double sumPhase;
	double avgPhase;
	double R;
	int nPhase;

	if(n<2) {
		fprintf(stderr, "Not supported n<2\n");
		exit(EXIT_FAILURE);
	}
	inFFT = (mrcImage*)memoryAllocate(sizeof(mrcImage)*n, "in lmrcImageMultiCTFDetermination");

	for(i=0; i<n; i++) {
		if( in[0].HeaderN.x!=in[i].HeaderN.x
		  ||in[0].HeaderN.y!=in[i].HeaderN.y
		  ||in[0].HeaderN.z!=in[i].HeaderN.z) {
		  	fprintf(stderr, "Different Size : 0th image and %dth image\n", i);
		  	exit(EXIT_FAILURE);
		}
		if(1!=in[i].HeaderN.z) {
			fprintf(stderr, "2D Only Supported\n");
			exit(EXIT_FAILURE);
		}
		if(IsImage(&(in[i]), "", 0)) {
			lmrcImageFFT(&(inFFT[i]), &(in[i]), 0); 
		} else if(IsFT(&(in[i]), "", 0)) {
			inFFT[i] = in[i];
		} else {
			fprintf(stderr, "Not supported mode: %d\n", in[i].HeaderMode);
			exit(EXIT_FAILURE);
		}
	}
	
	delX = 1.0/(in[0].HeaderLength.x*in->HeaderN.x);	
	delY = 1.0/(in[0].HeaderLength.y*in->HeaderN.y);	
	
	def  = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*n, "in lmrcImageMultiCTFDetemination");
	CTF  = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*n, "in lmrcImageMultiCTFDetemination");
	Phase= (double*)memoryAllocate(sizeof(double)*n, "in lmrcImageMultiCTFDetemination");
	nDef = (int*)memoryAllocate(sizeof(int)*n, "in lmrcImageMultiCTFDetemination");
	iDef = (int*)memoryAllocate(sizeof(int)*n, "in lmrcImageMultiCTFDetemination");
	linfo->minDef = (double*)memoryAllocate(sizeof(double)*n, "in lmrcImageMultiCTFDetemination");
	nnDef = 1;
	for(i=0; i<n; i++) {	
		nDef[i] = (linfo->max[i].defocus - linfo->min[i].defocus)/linfo->del[i].defocus + 1;
		nnDef *= nDef[i];
	}
	
	linfo->Dif = in[0];
	linfo->Dif.HeaderN.x = nDef[0];
	linfo->Dif.HeaderN.y = nDef[1];
	linfo->Dif.HeaderN.z = (linfo->max[0].ratioOfAmpToPhase - linfo->min[0].ratioOfAmpToPhase)/linfo->del[0].ratioOfAmpToPhase + 1;	
	linfo->Dif.HeaderMode = mrcFloatImage;
	mrcInit(&(linfo->Dif), NULL);

	linfo->minPhase = M_PI;
	tmp = linfo->val;
	for(tmp[0].ratioOfAmpToPhase =linfo->min[0].ratioOfAmpToPhase, iRatio=0; 
		tmp[0].ratioOfAmpToPhase<=linfo->max[0].ratioOfAmpToPhase;
		tmp[0].ratioOfAmpToPhase+=linfo->del[0].ratioOfAmpToPhase, iRatio++) {
		for(i=1; i<n; i++) {
			tmp[i].ratioOfAmpToPhase = tmp[0].ratioOfAmpToPhase;	
		}
		for(i=0; i<nnDef; i++) {
			for(j=0; j<n; j++) {
				nnTmp = 1;
				for(k=1; k<=j; k++) {
					nnTmp *= nDef[k-1];
				}
				iDef[j] = (i/nnTmp)%nDef[j];
				fprintf(linfo->Out, "%d) nnTmp: %d : max %d\n", j, nnTmp, nnDef);
				def[j]  = linfo->min[j].defocus + iDef[j]*linfo->del[j].defocus;  
				tmp[j].defocus  = def[j];
				fprintf(linfo->Out, "%d %d <- %d\n", j, iDef[j], i);
			}
			sumPhase = 0.0;
			nPhase   = 0;
			for(X=0; X<=in[0].HeaderN.x/2.0; X++) {
				for(Y=-in[0].HeaderN.y/2.0; Y<in[0].HeaderN.y/2.0; Y++) {
					R = sqrt(SQR(X*delX) + SQR(Y*delY));
					if(R<linfo->Rmax) {
						for(j=0; j<n; j++) {
							CTF[j] = ctfFunction(&(tmp[j]), R, 0);
							mrcPixelDataGet(&(inFFT[j]), X, Y, 0.0, &(Phase[j]), mrcPixelPhase, mrcPixelHowNearest);
							if(CTF[j]<0) {
								Phase[j] = NORMAL_PHASE(Phase[j] + M_PI);
							}
						}
						phase = 0;	
						for(j=0; j<n; j++) {
							for(k=j+1; k<n; k++) {
								tmpPhase = NORMAL_PHASE(Phase[j] - Phase[k]);
								tmpPhase = MIN(tmpPhase, 2*M_PI-tmpPhase);
								phase += tmpPhase;
							}
						}
						phase = phase/(n*(n-1)/2);
						sumPhase += phase;
						nPhase++;
					}
				}
			}
			avgPhase = sumPhase/nPhase;
			if(avgPhase<linfo->minPhase) {
				linfo->minPhase = avgPhase;
				for(j=0; j<n; j++) {
					linfo->minDef[j] = tmp[j].defocus;
				}
				linfo->minRatio = tmp[0].ratioOfAmpToPhase;
			}
			fprintf(linfo->Out, "%15.6e: %15.6e ", avgPhase, tmp[0].ratioOfAmpToPhase);
			for(j=0; j<n; j++) {
				fprintf(linfo->Out, "%15.6e ", tmp[j].defocus);	
			}
			fprintf(linfo->Out, "\n");
			mrcPixelDataSet(&(linfo->Dif), iDef[0], iDef[1], iRatio, avgPhase, mrcPixelRePart);
		}
	}
}

