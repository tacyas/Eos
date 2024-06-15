/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageClusterAnalysisPVMSlave ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageClusterAnalysisPVMSlave
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageClusterAnalysisPVMSlave ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "lmrcImageMultiplying.h"
#include "lmrcImageCorrelation.h"
#include "pvm3.h"
#include "mrcImagePVM.h"
#include "nr2.h"

/* prototypes */
void lmrcImagelAutoRotationCorrelationInfoSendByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid);
void lmrcImagelAutoRotationCorrelationInfoReceiveByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid);
float lmrcImageDistanceCalcByWardMethodWithAutoRotationPVM(mrcImage* out, mrcImage* cor, mrcImage* in1, mrcImage* in2, int num1, int num2, lmrcImageAutoRotationCorrelationInfo* linfo, int lmode, int flagmirror, int* mirrorresult, int mode);

int
main(int argc, char* argv[]) 
{
/* variables */
	mrcImageClusterAnalysisPVMSlaveInfo info;
	mrcImage in1;
	mrcImage in2;
	mrcImage out;
	mrcImage cor;
	int num1,num2,lmode,flagmirror,mode;
	lmrcImageAutoRotationCorrelationInfo linfo;
	float distance;
	int mirrorresult;
	int ptid;
	int status;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	printf("Program Start\n");
	ptid = pvm_parent();
	pvm_recv(-1, -1);
	pvm_upkint(&num1, 1, 1);
	pvm_upkint(&num2, 1, 1);
	pvm_upkint(&lmode, 1, 1);
	pvm_upkint(&flagmirror, 1, 1);
	pvm_upkint(&mode, 1, 1);
	printf("%d %d %d %d %d\n",num1,num2,lmode,flagmirror,mode);
       	mrcImageRecieveByPVM(&in1, ptid, 0);
	pvm_recv(-1, -1);
	mrcImageRecieveByPVM(&in2, ptid, 0);
	pvm_recv(-1, -1);
	lmrcImagelAutoRotationCorrelationInfoReceiveByPVM(&linfo, ptid);

	
	distance = lmrcImageDistanceCalcByWardMethodWithAutoRotationPVM(&out, &cor, &in1, &in2, num1, num2, &linfo, lmode, flagmirror, &mirrorresult, mode);
	printf("distance: %g mirror: %d \n",distance,mirrorresult);

	
	pvm_initsend(PvmDataDefault);
	pvm_pkfloat(&distance, 1, 1);
	pvm_pkint(&mirrorresult , 1, 1);
	status=pvm_send(ptid,1);
	if (0<status){
	      pvm_error("mrcImageClusterAnalysisPVMSlave");
	}
	
	
	pvm_exit();
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

float 
lmrcImageDistanceCalcByWardMethodWithAutoRotationPVM(mrcImage* out, mrcImage* cor, mrcImage* in1, mrcImage* in2, int num1, int num2, lmrcImageAutoRotationCorrelationInfo* linfo, int lmode, int flagmirror, int* mirrorresult, int mode)
{
	double distance,distance2;
	mrcImage tmpout;
	mrcImage tmpcor;
	mrcImage tmpin1;
	lmrcImageAutoRotationCorrelationInfo tmplinfo;

	if (flagmirror){
	  tmplinfo=*linfo;
	  lmrcImageAutoRotationCorrelation(out, cor, in1, in2, linfo, lmode); 
	  distance = SQR(linfo->EuclidDistance)*(num1*num2)/(num1+num2);
	  lmrcMirrorImageCreate(&tmpin1, in1, 0);
	  lmrcImageAutoRotationCorrelation(&tmpout, &tmpcor, &tmpin1, in2, &tmplinfo, lmode); 
	  distance2 = SQR(tmplinfo.EuclidDistance)*(num1*num2)/(num1+num2);
	  if (distance2 < distance){
	    *linfo = tmplinfo;
	    *out = tmpout;
	    *cor = tmpcor;
	    distance = distance2;
	    *mirrorresult=1;
	  } else {
	    *mirrorresult=0;
	  }
	} else {
	  lmrcImageAutoRotationCorrelation(out, cor, in1, in2, linfo, lmode); 
	  distance = SQR(linfo->EuclidDistance)*(num1*num2)/(num1+num2);
	}
	return distance;
}

void lmrcImagelAutoRotationCorrelationInfoSendByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid)
{
  int info;

  pvm_initsend(PvmDataDefault);
  pvm_pkint(&(linfo->iter), 1, 1);
  pvm_pkint(&(linfo->nRot), 1, 1);
  pvm_pkint(&(linfo->Method), 1, 1);
  pvm_pkfloat(&(linfo->max), 1, 1);
  pvm_pkfloat(&(linfo->maxTheta), 1, 1);
  pvm_pkfloat(&(linfo->maxP.x), 1, 1);
  pvm_pkfloat(&(linfo->maxP.y), 1, 1);
  pvm_pkfloat(&(linfo->maxP.z), 1, 1);
  pvm_pkfloat(&(linfo->EuclidDistance), 1, 1);
  pvm_pkfloat(&(linfo->LinearCorrelation), 1, 1);
  pvm_pkint(&(linfo->flagRestrictionArea), 1, 1);
  pvm_pkfloat(&(linfo->thetaMin), 1, 1);
  pvm_pkfloat(&(linfo->thetaMax), 1, 1);
  pvm_pkint(&(linfo->flagXshiftOnly), 1, 1);
  info = pvm_send(tid, 1);
  if (info<0){
    pvm_error("lmrcImagelAutoRotationCorrelationInfoSendByPVM");
  }
}

void lmrcImagelAutoRotationCorrelationInfoReceiveByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid)
{
  int bufid;

  bufid = pvm_recv(tid, -1);
  if(bufid<0) {
    pvm_error("lmrcImagelAutoRotationCorrelationInfoReceiveByPVM");
    return;
  }
  pvm_upkint(&(linfo->iter), 1, 1);
  pvm_upkint(&(linfo->nRot), 1, 1);
  pvm_upkint(&(linfo->Method), 1, 1);
  pvm_upkfloat(&(linfo->max), 1, 1);
  pvm_upkfloat(&(linfo->maxTheta), 1, 1);
  pvm_upkfloat(&(linfo->maxP.x), 1, 1);
  pvm_upkfloat(&(linfo->maxP.y), 1, 1);
  pvm_upkfloat(&(linfo->maxP.z), 1, 1);
  pvm_upkfloat(&(linfo->EuclidDistance), 1, 1);
  pvm_upkfloat(&(linfo->LinearCorrelation), 1, 1);
  pvm_upkint(&(linfo->flagRestrictionArea), 1, 1);
  pvm_upkfloat(&(linfo->thetaMin), 1, 1);
  pvm_upkfloat(&(linfo->thetaMax), 1, 1);
  pvm_upkint(&(linfo->flagXshiftOnly), 1, 1);
}

