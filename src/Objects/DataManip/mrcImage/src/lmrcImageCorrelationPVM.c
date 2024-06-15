/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageCorrelationPVM ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageCorrelationPVM 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageCorrelationPVM ver%I%; Date:%D% %Z%";

#ifdef PVM

#include "Memory.h"
#include "PVM.h"
#include "mrcImage.h"
#include "mrcImagePVM.h"
#include "./lmrcImageCorrelation.h"

void
lmrcImageCorrelationServerStart(lmrcImageCorrelationPVMInfo* linfo, FILE* fpt, int numTask)
{
	int my_tid;
	char* arg[] = { (char*) 0 };

	/* PVM Start */
	pvm_catchout(stdout);
	my_tid = pvm_mytid();

	pvm_catchout(stdout);
	if(NULL!=fpt) {
		linfo->tids = pvmServerStart("mrcImageCorrelationServer", arg, fpt, &numTask, 0);
	} else {
		linfo->tids = pvmServerStart("mrcImageCorrelationServer", arg, NULL, &numTask, 0);
	}
	linfo->numTask = numTask;
}

void
lmrcImageCorrelationServerEnd(lmrcImageCorrelationPVMInfo linfo)
{
	int i;

	for(i=0; i<linfo.numTask; i++) {
		pvm_kill(linfo.tids[i]);
	}
	pvm_exit();
}

void
lmrcImageCorrelationPVMStart(mrcImage* in, mrcImage* ref, lmrcImageAutoRotationCorrelationInfo* linfo, int tid, long mode)
{
	int msgtag;
	int info;

	DEBUGPRINT("lmrcImageCorrelationPVMStart Start")
	
	/* Send */
	mrcImageSendByPVM(in, tid, 0);
	mrcImageSendByPVM(ref, tid, 0);
	lmrcImageAutoRotationCorrelationInfoSendByPVM(linfo, tid, 0);

	msgtag = 0;
	pvm_initsend(PvmDataDefault);
	pvm_pklong(&mode, 1, 1);
	info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("lmrcImageCorrelationPVMStart:");
	}	
}

void
lmrcImageCorrelationPVMEnd(mrcImage* out, mrcImage* cor, lmrcImageAutoRotationCorrelationInfo* linfo, int tid, long mode)
{
	DEBUGPRINT("lmrcImageCorrelationPVMEnd Start");

	mrcImageSendByPVM(out, tid, 0);
	mrcImageSendByPVM(cor, tid, 0);
	lmrcImageAutoRotationCorrelationInfoSendByPVM(linfo, tid, 0);	
	fflush(stdout);
	fflush(stderr);
}

void
lmrcImageCorrelationServer()
{
	mrcImage in;
	mrcImage ref;
	mrcImage out;
	mrcImage cor;
	lmrcImageAutoRotationCorrelationInfo linfo;
	int mode = 0;
	int tid;

	while(1) {
		DEBUGPRINT("lmrcImageCorrelationServer Start");

		memoryClear(&in, sizeof(mrcImage), 0);
		memoryClear(&ref, sizeof(mrcImage), 0);
		memoryClear(&out, sizeof(mrcImage), 0);
		memoryClear(&cor, sizeof(mrcImage), 0);
		memoryClear(&linfo, sizeof(lmrcImageAutoRotationCorrelationInfo), 0);

		tid = pvm_parent();

		/* Recieve */	
		mrcImageRecieveByPVM(&in, tid, 0);
		mrcImageRecieveByPVM(&ref, tid, 0);
		lmrcImageAutoRotationCorrelationInfoRecieveByPVM(&linfo, tid, 0);

		/* Calc */
		lmrcImageAutoRotationCorrelation(&out, &cor, &in, &ref, &linfo, mode);

		/* Send */
		mrcImageSendByPVM(&out, tid, 0);
		mrcImageSendByPVM(&cor, tid, 0);
		lmrcImageAutoRotationCorrelationInfoSendByPVM(&linfo, tid, 0);	

		/* Memory Free */
		mrcImageFree(&in, "");
		mrcImageFree(&ref, "");
	}	
}

void
lmrcImageAutoRotationCorrelationInfoSendByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid, long mode)
{
	int info;
	int msgtag;

	pvm_initsend(PvmDataDefault);
	pvm_pkint  (&(linfo->iter), 1, 1);
	pvm_pkint  (&(linfo->nRot), 1, 1);
	pvm_pkint  (&(linfo->Method), 1, 1);
	pvm_pkfloat(&(linfo->max), 1, 1);
	pvm_pkfloat(&(linfo->maxTheta), 1, 1);
	pvm_pkfloat(&(linfo->maxP.x), 1, 1);
	pvm_pkfloat(&(linfo->maxP.y), 1, 1);
	pvm_pkfloat(&(linfo->maxP.z), 1, 1);

	msgtag = 0; info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("lmrcImageAutoRotationCorrelationInfoSend");
	}

	mrcImageInformationSendByPVM(&(linfo->corInfo), tid, mode);
	lmrcImageSSDAInfoSendByPVM(&(linfo->SSDAInfo), tid, mode);

	pvm_initsend(PvmDataDefault);

	pvm_pkfloat(&(linfo->EuclidDistance), 1, 1);
	pvm_pkfloat(&(linfo->LinearCorrelation), 1, 1);

	pvm_pkint  (&(linfo->flagRestrictionArea), 1, 1);
	pvm_pkfloat(&(linfo->thetaMin), 1, 1);
	pvm_pkfloat(&(linfo->thetaMax), 1, 1);

	pvm_pkint  (&(linfo->flagXshiftOnly), 1, 1);
	msgtag = 0; info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("lmrcImageAutoRotationCorrelationInfoSend");
	}
}

void
lmrcImageAutoRotationCorrelationInfoRecieveByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid, long mode)
{
	int info;
	int msgtag;
	int bufid;

	msgtag = 0;
	bufid  = pvm_recv(tid, msgtag);
	if(bufid<0) {
		pvm_perror("lmrcImageAutoRotationCorrelationInfoRecieveByPVM:");
	}
	pvm_upkint  (&(linfo->iter), 1, 1);
	pvm_upkint  (&(linfo->nRot), 1, 1);
	pvm_upkint  (&(linfo->Method), 1, 1);
	pvm_upkfloat(&(linfo->max), 1, 1);
	pvm_upkfloat(&(linfo->maxTheta), 1, 1);
	pvm_upkfloat(&(linfo->maxP.x), 1, 1);
	pvm_upkfloat(&(linfo->maxP.y), 1, 1);
	pvm_upkfloat(&(linfo->maxP.z), 1, 1);

	mrcImageInformationRecieveByPVM(&(linfo->corInfo), tid, mode);
	lmrcImageSSDAInfoRecieveByPVM(&(linfo->SSDAInfo), tid, mode);

	msgtag = 0;
	bufid  = pvm_recv(tid, msgtag);
	if(bufid<0) {
		pvm_perror("lmrcImageAutoRotationCorrelationInfoRecieveByPVM:");
	}
	pvm_upkfloat(&(linfo->EuclidDistance), 1, 1);
	pvm_upkfloat(&(linfo->LinearCorrelation), 1, 1);

	pvm_upkint  (&(linfo->flagRestrictionArea), 1, 1);
	pvm_upkfloat(&(linfo->thetaMin), 1, 1);
	pvm_upkfloat(&(linfo->thetaMax), 1, 1);

	pvm_upkint  (&(linfo->flagXshiftOnly), 1, 1);
}

#endif /* PVM */
