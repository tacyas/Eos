/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImagePVM ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImagePVM 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImagePVM ver%I%; Date:%D% %Z%";

#ifdef PVM

#include "pvm3.h"
#include "PVM.h"
#include "../inc/mrcImage.h"
#include "mrcImagePVM.h"

void 
mrcImageSendByPVM(mrcImage* mrc, int tid, int mode)
{
	mrcImageSendHeaderByPVM(mrc, tid, mode);
	mrcImageSendImageByPVM(mrc, tid, mode);
	mrcImageSendTailerByPVM(mrc, tid, mode);

}

void 
mrcImageRecieveByPVM(mrcImage* mrc, int tid, int mode)
{
	mrcImageRecieveHeaderByPVM(mrc, tid, mode);
	mrcImageRecieveImageByPVM(mrc, tid, mode);
	mrcImageRecieveTailerByPVM(mrc, tid, mode);
}

void
mrcImageSendHeaderByPVM(mrcImage* mrc, int tid, int mode)
{
	int i;
	int msgtag;
	int info;

	pvm_initsend(PvmDataDefault);
	pvm_pkint(&(mrc->Header.Cont.N.x), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.N.y), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.N.z), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.Mode), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.StartN.x), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.StartN.y), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.StartN.z), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.M.x), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.M.y), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.M.z), 1, 1);
	pvm_pkfloat(&(mrc->Header.Cont.Length.x), 1, 1);
	pvm_pkfloat(&(mrc->Header.Cont.Length.y), 1, 1);
	pvm_pkfloat(&(mrc->Header.Cont.Length.z), 1, 1);
	pvm_pkfloat(&(mrc->Header.Cont.Alpha), 1, 1);
	pvm_pkfloat(&(mrc->Header.Cont.Beta), 1, 1);
	pvm_pkfloat(&(mrc->Header.Cont.Gamma), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.MAPC), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.MAPR), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.MAPS), 1, 1);
	pvm_pkfloat(&(mrc->Header.Cont.AMin), 1, 1);
	pvm_pkfloat(&(mrc->Header.Cont.AMax), 1, 1);
	pvm_pkfloat(&(mrc->Header.Cont.AMean), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.ISPG), 1, 1);
	pvm_pkint(&(mrc->Header.Cont.NSYMBT), 1, 1);
	for(i=0; i<MRC_MAX_EXTRA; i++) {
		pvm_pkfloat(&(mrc->Header.Cont.EXTRA[i]), 1, 1);
	}
	pvm_pkfloat(&(mrc->Header.Cont.OriginX), 1, 1);
	pvm_pkfloat(&(mrc->Header.Cont.OriginY), 1, 1);
	pvm_pkbyte(mrc->Header.Cont.Label, MRC_MAX_LABEL_N*MRC_MAX_LABEL_LEN, 1);   
	msgtag = 1;
	info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("mrcImageSendHeaderByPVM");
	}
}

void
mrcImageRecieveHeaderByPVM(mrcImage* mrc, int tid, int mode)
{
	int i;
	int msgtag;
	int info;
	int bufid;

	msgtag = 1;
	bufid = pvm_recv(tid, msgtag);
	/* block the process until messages with msgtag has arrived from tid */
	if(bufid<0) {
		pvm_perror("mrcImageRecieveHeaderByPVM");
		return;
	}
	pvm_upkint(&(mrc->Header.Cont.N.x), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.N.y), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.N.z), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.Mode), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.StartN.x), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.StartN.y), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.StartN.z), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.M.x), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.M.y), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.M.z), 1, 1);
	pvm_upkfloat(&(mrc->Header.Cont.Length.x), 1, 1);
	pvm_upkfloat(&(mrc->Header.Cont.Length.y), 1, 1);
	pvm_upkfloat(&(mrc->Header.Cont.Length.z), 1, 1);
	pvm_upkfloat(&(mrc->Header.Cont.Alpha), 1, 1);
	pvm_upkfloat(&(mrc->Header.Cont.Beta), 1, 1);
	pvm_upkfloat(&(mrc->Header.Cont.Gamma), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.MAPC), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.MAPR), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.MAPS), 1, 1);
	pvm_upkfloat(&(mrc->Header.Cont.AMin), 1, 1);
	pvm_upkfloat(&(mrc->Header.Cont.AMax), 1, 1);
	pvm_upkfloat(&(mrc->Header.Cont.AMean), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.ISPG), 1, 1);
	pvm_upkint(&(mrc->Header.Cont.NSYMBT), 1, 1);
	for(i=0; i<MRC_MAX_EXTRA; i++) {
		pvm_upkfloat(&(mrc->Header.Cont.EXTRA[i]), 1, 1);
	}
	pvm_upkfloat(&(mrc->Header.Cont.OriginX), 1, 1);
	pvm_upkfloat(&(mrc->Header.Cont.OriginY), 1, 1);
	pvm_upkbyte(mrc->Header.Cont.Label, MRC_MAX_LABEL_N*MRC_MAX_LABEL_LEN, 1);   
}


void
mrcImageSendTailerByPVM(mrcImage* mrc, int tid, int mode)
{
	int i;
	int msgtag;
	int info;

	pvm_initsend(PvmDataDefault);
	pvm_pkint(&(mrc->numTailer), 1, 1);

	msgtag = 1;
	info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("mrcImageSendHeaderByPVM");
	}

	for(i=0; i<mrc->numTailer; i++) {
		pvm_initsend(PvmDataDefault);
		pvm_pkbyte(mrc->Tailer[i].Cont.Code, 4, 1);   
		pvm_pkint(&(mrc->Tailer[i].Cont.Mode), 1, 1);   
		pvm_pkbyte(mrc->Tailer[i].Cont.EulerAngleMode, 4, 1);   
		pvm_pkfloat(&(mrc->Tailer[i].Cont.Rot1), 1, 1);   
		pvm_pkfloat(&(mrc->Tailer[i].Cont.Rot2), 1, 1);   
		pvm_pkfloat(&(mrc->Tailer[i].Cont.Rot3), 1, 1);   
		pvm_pkfloat(&(mrc->Tailer[i].Cont.Mirror), 1, 1);   
	}
	msgtag = 1;
	info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("mrcImageSendHeaderByPVM");
	}
}

void
mrcImageRecieveTailerByPVM(mrcImage* mrc, int tid, int mode)
{
	int i;
	int msgtag;
	int info;
	int bufid;
	int oldNumTailer;

	oldNumTailer = mrc->numTailer;
	msgtag = 1;
	bufid = pvm_recv(tid, msgtag);
	/* block the process until messages with msgtag has arrived from tid */
	if(bufid<0) {
		pvm_perror("mrcImageRecieveHeaderByPVM");
		return;
	}
	pvm_upkint(&(mrc->numTailer), 1, 1);
	if(mrc->numTailer != oldNumTailer) {
		if(0<oldNumTailer) {
			free(mrc->Tailer);
		}
		mrcTailerInit(mrc, 0);
	}

	for(i=0; i<mrc->numTailer; i++) {
		msgtag = 1;
		bufid = pvm_recv(tid, msgtag);
		if(bufid<0) {
			pvm_perror("mrcImageRecieveHeaderByPVM");
			return;
		}
		pvm_upkbyte(mrc->Tailer[i].Cont.Code, 4, 1);   
		pvm_upkint(&(mrc->Tailer[i].Cont.Mode), 1, 1);   
		pvm_upkbyte(mrc->Tailer[i].Cont.EulerAngleMode, 4, 1);   
		pvm_upkfloat(&(mrc->Tailer[i].Cont.Rot1), 1, 1);   
		pvm_upkfloat(&(mrc->Tailer[i].Cont.Rot2), 1, 1);   
		pvm_upkfloat(&(mrc->Tailer[i].Cont.Rot3), 1, 1);   
		pvm_upkfloat(&(mrc->Tailer[i].Cont.Mirror), 1, 1);   
	}
}

void
mrcImageSendImageByPVM(mrcImage* mrc, int tid, int mode)
{
	int i;
	int msgtag;
	int info;

	pvm_initsend(PvmDataDefault);
	pvm_pkint(&(mrc->BytePerImage), 1, 1);
	pvm_pkint(&(mrc->BytePerBand), 1, 1);
	pvm_pkint(&(mrc->BandPerPixel), 1, 1);
	pvm_pkint(&(mrc->PixelPerImage), 1, 1);
	pvm_pkint(&(mrc->status), 1, 1);
	msgtag = 1;
	info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("mrcImageSendImageByPVM");
	}

	pvm_initsend(PvmDataDefault);
	switch(mrc->HeaderMode) {
		case mrcCharImage: {
			pvm_pkbyte(mrc->ImageCharImage, mrc->BytePerImage/sizeof(unsigned char), 1);
			break;
		}
		case mrcComplexShortFT: 
		case mrcShortImage: {
			pvm_pkshort(mrc->ImageShortImage, mrc->BytePerImage/sizeof(unsigned short), 1);
			break;
		}
		case mrcComplexLongFT: 
		case mrcLongImage: {
			pvm_pklong(mrc->ImageLongImage, mrc->BytePerImage/sizeof(unsigned long), 1);
			break;
		}
		case mrcComplexFloatFT: 
		case mrcFloatImage: {
			pvm_pkfloat(mrc->ImageFloatImage, mrc->BytePerImage/sizeof(float), 1);
			break;
		}
		case mrcComplexDoubleFT: 
		case mrcDoubleImage: {
			pvm_pkdouble(mrc->ImageDoubleImage, mrc->BytePerImage/sizeof(double), 1);
			break;
		}
	}	
	msgtag = 1;
	info = pvm_send(tid, msgtag);
	if(info<0) {
		pvm_perror("mrcImageSendImageByPVM");
		return;
	}	
}

void
mrcImageRecieveImageByPVM(mrcImage* mrc, int tid, int mode)
{
	int i;
	int msgtag;
	int info;
	int oldBytePerImage;
	int bufid;

	oldBytePerImage = mrc->BytePerImage;
	msgtag = 1;
	bufid = pvm_recv(tid, msgtag);
	/* block the process until messages with msgtag has arrived from tid */
	if(bufid<0) {
		pvm_perror("mrcImageRecieveImageByPVM");
		return;
	}	
	pvm_upkint(&(mrc->BytePerImage), 1, 1);
	pvm_upkint(&(mrc->BytePerBand), 1, 1);
	pvm_upkint(&(mrc->BandPerPixel), 1, 1);
	pvm_upkint(&(mrc->PixelPerImage), 1, 1);
	pvm_upkint(&(mrc->status), 1, 1);
	if(mrc->BytePerImage != oldBytePerImage) {
		mrcInit(mrc, NULL);
	}

	msgtag = 1;
	bufid = pvm_recv(tid, msgtag);
	/* block the process until messages with msgtag has arrived from tid */
	if(bufid<0) {
		pvm_perror("mrcImageRecieveImageByPVM");
		return;
	}
	switch(mrc->HeaderMode) {
		case mrcCharImage: {
			pvm_upkbyte(mrc->ImageCharImage, mrc->BytePerImage/sizeof(unsigned char), 1);
			break;
		}
		case mrcComplexShortFT: 
		case mrcShortImage: {
			pvm_upkshort(mrc->ImageShortImage, mrc->BytePerImage/sizeof(unsigned short), 1);
			break;
		}
		case mrcComplexLongFT: 
		case mrcLongImage: {
			pvm_upklong(mrc->ImageLongImage, mrc->BytePerImage/sizeof(unsigned long), 1);
			break;
		}
		case mrcComplexFloatFT: 
		case mrcFloatImage: {
			pvm_upkfloat(mrc->ImageFloatImage, mrc->BytePerImage/sizeof(float), 1);
			break;
		}
		case mrcComplexDoubleFT: 
		case mrcDoubleImage: {
			pvm_upkdouble(mrc->ImageDoubleImage, mrc->BytePerImage/sizeof(double), 1);
			break;
		}	
	}	
}

void
mrcImageInformationSendByPVM(mrcImageInformation* info, int tid, int mode)
{
	int msgtag;
	int inf;

	pvm_initsend(PvmDataDefault);
	pvm_pkdouble(&(info->mean), 1,1);
	pvm_pkdouble(&(info->rootMeanSquare), 1,1);
	pvm_pkdouble(&(info->meanOfSphereSurface), 1,1);
	pvm_pkdouble(&(info->meanOfCylinderSurface), 1,1);
	pvm_pkdouble(&(info->meanOfEdge), 1,1);
	pvm_pkdouble(&(info->sdOfEdge), 1,1);
	pvm_pkdouble(&(info->seOfEdge), 1,1);
	pvm_pkdouble(&(info->max), 1,1);
	pvm_pkfloat (&(info->maxCoord.x), 1,1);
	pvm_pkfloat (&(info->maxCoord.y), 1,1);
	pvm_pkfloat (&(info->maxCoord.z), 1,1);
	pvm_pkdouble(&(info->min), 1,1);
	pvm_pkfloat (&(info->minCoord.x), 1,1);
	pvm_pkfloat (&(info->minCoord.y), 1,1);
	pvm_pkfloat (&(info->minCoord.z), 1,1);
	pvm_pkdouble(&(info->sd), 1,1);
	pvm_pkdouble(&(info->se), 1,1);
	pvm_pkdouble(&(info->rmax), 1,1);
	pvm_pklong  (&(info->flagrmax), 1,1);
	pvm_pkint   (&(info->mode), 1,1);
	msgtag = 0; inf = pvm_send(tid, msgtag);
	if(inf<0) {
		pvm_perror("mrcImageInformationSendByPVM");
		return;
	}
}

void
mrcImageInformationRecieveByPVM(mrcImageInformation* info, int tid, int mode)
{
	int msgtag;
	char s[1024];
	int bufid;

	msgtag = 0; bufid = pvm_recv(tid, msgtag);
	if(bufid<0) {
		pvm_perror("mrcImageInformationSendByPVM:");
		return;
	}
	pvm_upkdouble(&(info->mean), 1,1);
	pvm_upkdouble(&(info->rootMeanSquare), 1,1);
	pvm_upkdouble(&(info->meanOfSphereSurface), 1,1);
	pvm_upkdouble(&(info->meanOfCylinderSurface), 1,1);
	pvm_upkdouble(&(info->meanOfEdge), 1,1);
	pvm_upkdouble(&(info->sdOfEdge), 1,1);
	pvm_upkdouble(&(info->seOfEdge), 1,1);
	pvm_upkdouble(&(info->max), 1,1);
	pvm_upkfloat (&(info->maxCoord.x), 1,1);
	pvm_upkfloat (&(info->maxCoord.y), 1,1);
	pvm_upkfloat (&(info->maxCoord.z), 1,1);
	pvm_upkdouble(&(info->min), 1,1);
	pvm_upkfloat (&(info->minCoord.x), 1,1);
	pvm_upkfloat (&(info->minCoord.y), 1,1);
	pvm_upkfloat (&(info->minCoord.z), 1,1);
	pvm_upkdouble(&(info->sd), 1,1);
	pvm_upkdouble(&(info->se), 1,1);
	pvm_upkdouble(&(info->rmax), 1,1);
	pvm_upklong  (&(info->flagrmax), 1,1);
	pvm_upkint   (&(info->mode), 1,1);
}


#endif /* PVM */
