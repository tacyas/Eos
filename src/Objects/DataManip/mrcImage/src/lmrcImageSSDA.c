/*
# lmrcImageSSDA.c  1.1
# The latest update : 01/23/97 at 10:38:57
#
#@(#) lmrcImageSSDA ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : lmrcImageSSDA 
#@(#) Attention
#@(#)
*/

static char __sccs_id[] = "@(#)lmrcImageSSDA ver1.1; Date:97/01/23 @(#)";
#undef DEBUG
#include "genUtil.h"
#include "lmrcImageSSDA.h"
#include <math.h>

#ifdef PVM
#include <pvm3.h>	
#include "PVM.h"

void
lmrcImageSSDAInfoSendByPVM(lmrcImageSSDAInfo* linfo, int tid, int mode)
{
	int info;
	int msgtag;

	pvm_initsend(PvmDataDefault);	
	pvm_pkdouble(&(linfo->Threshold), 1, 1);
	pvm_pkdouble(&(linfo->Error), 1, 1);
	pvm_pkfloat (&(linfo->p.x), 1, 1);
	pvm_pkfloat (&(linfo->p.y), 1, 1);
	pvm_pkfloat (&(linfo->p.z), 1, 1);
	pvm_pkfloat (&(linfo->optimump.x), 1, 1);
	pvm_pkfloat (&(linfo->optimump.y), 1, 1);
	pvm_pkfloat (&(linfo->optimump.z), 1, 1);
	pvm_pkfloat (&(linfo->smin.x), 1, 1);
	pvm_pkfloat (&(linfo->smin.y), 1, 1);
	pvm_pkfloat (&(linfo->smin.z), 1, 1);
	pvm_pkfloat (&(linfo->smax.x), 1, 1);
	pvm_pkfloat (&(linfo->smax.y), 1, 1);
	pvm_pkfloat (&(linfo->smax.z), 1, 1);
	pvm_pkfloat (&(linfo->predict.x), 1, 1);
	pvm_pkfloat (&(linfo->predict.y), 1, 1);
	pvm_pkfloat (&(linfo->predict.z), 1, 1);
	pvm_pkint   (&(linfo->n), 1, 1);
	msgtag = 0; info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("lmrcImageSSDInfoSendByPVM:");
	}
}

void
lmrcImageSSDAInfoRecieveByPVM(lmrcImageSSDAInfo* info, int tid, int mode)
{
	int bufid;
	int msgtag;

	msgtag = 0;
	bufid = pvm_recv(tid, msgtag);
	if(bufid<0) {
		pvm_perror("lmrcImageSSDInfoReciveByPVM:");
	}
	pvm_initsend(PvmDataDefault);	
	pvm_upkdouble(&(info->Threshold), 1, 1);
	pvm_upkdouble(&(info->Error), 1, 1);
	pvm_upkfloat (&(info->p.x), 1, 1);
	pvm_upkfloat (&(info->p.y), 1, 1);
	pvm_upkfloat (&(info->p.z), 1, 1);
	pvm_upkfloat (&(info->optimump.x), 1, 1);
	pvm_upkfloat (&(info->optimump.y), 1, 1);
	pvm_upkfloat (&(info->optimump.z), 1, 1);
	pvm_upkfloat (&(info->smin.x), 1, 1);
	pvm_upkfloat (&(info->smin.y), 1, 1);
	pvm_upkfloat (&(info->smin.z), 1, 1);
	pvm_upkfloat (&(info->smax.x), 1, 1);
	pvm_upkfloat (&(info->smax.y), 1, 1);
	pvm_upkfloat (&(info->smax.z), 1, 1);
	pvm_upkfloat (&(info->predict.x), 1, 1);
	pvm_upkfloat (&(info->predict.y), 1, 1);
	pvm_upkfloat (&(info->predict.z), 1, 1);
	pvm_upkint   (&(info->n), 1, 1);
}

#endif

/*
#@(#) void lmrcImageSSDAAutomaticThresholdAndFineSearch
#@(#)

	lmrcImageSSDAInfo:
		Input:
			Threshold	: Initial Value			
			smin        : Search Region
			smax        : Search Region
		Output:
			Error		:
			optimump	: 


	Registration: SSDA (Seqential Similarity Detection Algorithm)
	References:
	1. Barnea, D.I., and Silverman, H.F., 
		"A Class of Algorithms for Fast Digital Image Registration", 
		IEEE. Trans., Vol.C-21, 179-186, FEB, 1972
	2. Onoe, M. and Saito, M.,
		"Automatic Threshold setting for the sequential similarity detection algorithm", 
		IBID., vol C-25, 10, 1052-1053, Oct. 1976
*/
void
lmrcImageSSDAAutomaticThresholdAndFineSearch(mrcImage* in,                 
											mrcImage* ref,
											lmrcImageSSDAInfo* info,
											mrcImageParaTypeInteger mode
											)
{
	DEBUGPRINT4("lmrcImageSSDAAutomaticThresholdAndFineSearch Start: (%f..%f, %f..%f) \n", info->smin.x, info->smax.x, info->smin.y, info->smax.y);
	for(info->p.x=info->smin.x; info->p.x<=info->smax.x; info->p.x++) {
		for(info->p.y=info->smin.y; info->p.y<=info->smax.y; info->p.y++) {

			__lmrcImageResidualDifferenceAdditionForSSDA(in, ref, info, mode); 

			DEBUGPRINT3("%g at %g %g", info->Error, info->p.x, info->p.y);

			if(info->Error < info->Threshold){ /* New Minimum Point */
				info->optimump  = info->p; 
				info->Threshold = info->Error;
				DEBUGPRINT3("MAX: %g at %g %g", info->Error, info->p.x, info->p.y);
			}
		}
	}
}

/*
	Calculation of residual between in and ref

		lmrcImageSSDAInfo info:
			Input:
				p			: Image Position
				Threshold	: Fixed threshold
			Output:
				n			: Point Number
				Error		: Sum of residual

	References:
	1. Barnea, D.I., and Silverman, H.F., 
		"A Class of Algorithms for Fast Digital Image Registration", 
		IEEE. Trans., Vol.C-21, 179-186, FEB, 1972
*/
void
__lmrcImageResidualDifferenceAdditionForSSDA(mrcImage* in, 					/* Input Image */ 
											mrcImage* ref,					/* Template Image */ 
											lmrcImageSSDAInfo* info,		/* Required Information */ 
											mrcImageParaTypeInteger mode)
{
	double a1, a2;
	mrcImageParaTypeReal x, y;
	mrcImageParaTypeReal ox, oy;

	/* Initialize */
	info->n = 0;	
	info->Error = 0;

	/* Calculation of residual */
	for(x=0; x<ref->HeaderN.x; x++) {
		for(y=0; y<ref->HeaderN.y; y++) {
			ox = fmod(x+info->p.x+in->HeaderN.x, in->HeaderN.x);
			oy = fmod(y+info->p.y+in->HeaderN.y, in->HeaderN.y);
			mrcPixelDataGet(in, ox, oy, 0.0, &a2, mrcPixelRePart, mrcPixelHowNearest);	
			mrcPixelDataGet(ref, x,  y, 0.0, &a1, mrcPixelRePart, mrcPixelHowNearest); 
			DEBUGPRINT3("In:(%f %f)  %f\n", ox, oy, a2);
			DEBUGPRINT3("Ref:(%f %f) %f\n", x, y, a1);
			info->n++; 						/* Point Count */
			info->Error += fabs(a1 - a2); 	/* Residual */
			if(info->Threshold < info->Error) { /* When error becomes greater than  threshold */
				return;
			}
		}
	}
}
