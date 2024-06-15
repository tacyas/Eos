/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrc3Dto2D ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : mrc3Dto2D
#%Z% Attention
#%Z%
*/

#include "File.h"
#include "Memory.h"
#include "eosPThread.h"
#include "./lmrc3Dto2D.h"


typedef struct lmrcImage3Dto2DSingleForPThreadArg {
	mrcImage* dst;
	FILE* fptInfo;
	mrcImage* out2D;
	mrcImage* in3D;
	char   Mode[4];
	double Rot1;
	double Rot2;
	double Rot3;
	lmrc3Dto2DInfo* linfo;
	lmrc3Dto2DSingleInfo* llinfo;
	int mode;
	int outSection;
	eosPThread pthread;
} lmrcImage3Dto2DSingleForPThreadArg;


extern void lmrcImage3Dto2DSingleForPThread(void* arg);
extern void lmrcImage3Dto2DSinglePost(FILE* fptInfo, mrcImage* dst, int outSection, mrcImage* out, lmrc3Dto2DInfo* linfo, int mode);

void
lmrcImage3Dto2DSingle(mrcImage* out2D, mrcImage* in3D, 
			char   Mode[4],
			double Rot1,	
			double Rot2,	
			double Rot3,	
			lmrc3Dto2DInfo* linfo,
			lmrc3Dto2DSingleInfo* llinfo,
			int mode)
{
	int max;
	int i, j, k;
	double sum;
	mrcImageParaTypeReal gx, gy, gz;
	mrcImageParaTypeReal g3x, g3y, g3z;
	mrcImageParaTypeReal r3x, r3y, r3z;
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal prjx, prjy, prjz;
	floatVector v;
	Matrix3D MatrixAnti;
	double data;

	max = MAX(in3D->HeaderN.x, MAX(in3D->HeaderN.y, in3D->HeaderN.z));

	if(llinfo->flagInit) {
		out2D->Header = in3D->Header;
		out2D->HeaderN.x = max;
		out2D->HeaderN.y = max;
		out2D->HeaderN.z = 1;
		out2D->HeaderMode = mrcFloatImage;
		mrcInit(out2D, NULL);
	} 

	floatVectorInit(&v, 4);
	r3x = g3x = (in3D->HeaderN.x - 1)/2.0;
	r3y = g3y = (in3D->HeaderN.y - 1)/2.0;
	r3z = g3z = (in3D->HeaderN.z - 1)/2.0;
	gx  = (max - 1)/2.0;
	gy  = (max - 1)/2.0;
	gz  = (max - 1)/2.0;

	matrix3DRotationAntiSetFollowingEulerAngle(MatrixAnti,
		Mode, Rot1, Rot2, Rot3, MATRIX_3D_MODE_INITIALIZE);

	v.data[3] = 1;

	for(prjx=0; prjx<max; prjx++) {
	for(prjy=0; prjy<max; prjy++) {
		sum =0.0;
		for(prjz=0; prjz<max; prjz++) {
			v.data[0] = prjx - gx;
			v.data[1] = prjy - gy;
			v.data[2] = prjz - gz;

			x = g3x;
			y = g3y;
			z = g3z;
			//matrix3DMultiplyVector(&v, MatrixAnti);
			for(i=0; i<3; i++) {
				x += MatrixAnti[i][0]*v.data[i];
				y += MatrixAnti[i][1]*v.data[i];
				z += MatrixAnti[i][2]*v.data[i];
			}
			switch(linfo->AreaMode) {
				lmrc3Dto2DInfoAreaModeGlobular: {
					if(SQR((x - g3x)/r3x) 
					 + SQR((y - g3y)/r3y) 
					 + SQR((z - g3z)/r3z) <= 1.0) {
						mrcPixelDataGet(in3D, x, y, z, &data, 
							mrcPixelRePart, linfo->InterpolationMode);
					} else {
						data = 0;
					}
					break;
				}
				lmrc3Dto2DInfoAreaModeCubic: 
				default: {
					if(-0.5<=x && x<in3D->HeaderN.x-0.5
			 		 &&-0.5<=y && y<in3D->HeaderN.y-0.5
					 &&-0.5<=z && z<in3D->HeaderN.z-0.5) {
						mrcPixelDataGet(in3D, x, y, z, &data, 
							mrcPixelRePart, linfo->InterpolationMode);
					} else {
						data = 0;
					}
					break;
				}
			}
			sum+=data;
		}
		out2D->ImageFloatImage[(int)(prjx+prjy*out2D->HeaderN.x)] = sum/max;
		//mrcPixelDataSet(out2D, prjx,  prjy, llinfo->section, sum/max, mrcPixelRePart);
		//mrcPixelDataSet(out2D, prjx,  prjy, 0, sum/max, mrcPixelRePart);
	}
	}
}

void
lmrcImage3Dto2DFollowingTailer(mrcImage* out2Ds, mrcImage* in3D, mrcImage* ref2Ds, 
	lmrc3Dto2DInfo* linfo, 
	int mode)
{
	int max;
	int count;
	lmrc3Dto2DSingleInfo llinfo;

	out2Ds->Header = ref2Ds->Header;
	mrcInit(out2Ds, 0);
	max = ref2Ds->HeaderN.z;  
	out2Ds->numTailer = max;
	mrcTailerInit(out2Ds, 0);

	llinfo.flagInit = 0;
	for(count=0; count<max; count++) {
		llinfo.section = count;

		out2Ds->Tailer[count] = ref2Ds->Tailer[count]; 

		lmrcImage3Dto2DSingle(out2Ds, in3D,  
			out2Ds->Tailer[count].Cont.EulerAngleMode,
			out2Ds->Tailer[count].Cont.Rot1,
			out2Ds->Tailer[count].Cont.Rot2,
			out2Ds->Tailer[count].Cont.Rot3,
			linfo, &llinfo, mode);

	}
}

void
lmrcImage3Dto2D(mrcImage* dst, mrcImage* in, lmrc3Dto2DInfo* linfo, int mode)
{
	mrcImage* out;
	int* outSection;
	int threadNum;
	int iThread;
	lmrcImage3Dto2DSingleForPThreadArg* pthreadArg;
	eosPThread pthread;	
	int i, j, n;
	int max;
	int count;
	int section;
	double Rot1, Rot2, Rot3;
	double RatiodRot1=1;
	double RatiodRot2=1;
	double RatiodRot3=1;
	int    nRot1, nRot2, nRot3;
	int    iRot1, iRot2, iRot3;
	lmrc3Dto2DSingleInfo* llinfo;
	char informationFile[1024]; 
	FILE* fptInfo;
	int ret;

	if(__eosPThread__) {
		threadNum = __eosPThreadNum__; 
		eosPThreadInit(&pthread, threadNum, 0);
		eosPThreadMutexInit(&pthread);
	} else {
		threadNum = 1;
	}
	out        = (mrcImage*)memoryAllocate(sizeof(mrcImage)*threadNum, "in lmrcImage3Dto2D");
	outSection = (int*)     memoryAllocate(sizeof(int)*threadNum, "in lmrcImage3Dto2D");
	llinfo     = (lmrc3Dto2DSingleInfo*)memoryAllocate(sizeof(lmrc3Dto2DSingleInfo)*threadNum, "in lmrcImage3Dto2D");
	pthreadArg = (lmrcImage3Dto2DSingleForPThreadArg*)memoryAllocate(sizeof(lmrcImage3Dto2DSingleForPThreadArg)*threadNum, "in lmrcImage3Dto2D"); 

	sprintf(informationFile, "%s.%s", linfo->filenamePrefix, linfo->filenameSuffix);
	fptInfo = fileOpen(informationFile, "w");

	n=linfo->nRot1*linfo->nRot2*linfo->nRot3;
	max = MAX(in->HeaderN.x, MAX(in->HeaderN.y, in->HeaderN.z));
	for(iThread=0; iThread<threadNum; iThread++) {
		// Header Information 
		out[iThread].Header.Cont = in->Header.Cont;
		mrcDefaultHeaderValueSetOnlyFixedValue(&out[iThread]);
		out[iThread].HeaderN.x = max;
		out[iThread].HeaderN.y = max;
		out[iThread].HeaderN.z = 1;
		out[iThread].HeaderMode = mrcFloatImage;
		// Image Allocation 
		mrcInit(&out[iThread], NULL);

		// Tailer Information 
		out[iThread].numTailer = 1;
		// Tailer Allocation
		mrcTailerInit(&out[iThread], 0);
	}

	if(!linfo->flagFileList) {
		dst->Header.Cont = in->Header.Cont;
		mrcDefaultHeaderValueSetOnlyFixedValue(dst);
		dst->HeaderN.x = max;
		dst->HeaderN.y = max;
		dst->HeaderN.z = n;	
		dst->HeaderMode = mrcFloatImage;
		mrcInit(dst, NULL);
		dst->numTailer = n;	
		mrcTailerInit(dst, 0);
	}

	if(__eosPThread__) {
		for(i=0; i<threadNum; i++) {
			pthreadArg[i].in3D  = in;
			pthreadArg[i].linfo = linfo;
			pthreadArg[i].mode = mode;
			pthreadArg[i].dst  = dst;
			pthreadArg[i].fptInfo = fptInfo;
			pthreadArg[i].pthread = pthread;
			for(j=0; j<4; j++) pthreadArg[i].Mode[j] = linfo->EulerAngleMode[j]; 
			pthreadArg[i].out2D = &(out[i]);
		}
	}

	count = 0;
	nRot1 = linfo->nRot1;
	for(iRot1=0; iRot1<nRot1; iRot1++) {
		Rot1 = linfo->Rot1Start + iRot1*linfo->Rot1Delta*RatiodRot1;
		if(0x01&mode) {
			nRot2 = MAX(1,(int)(linfo->nRot2*fabs(sin(Rot1))+0.5));
			RatiodRot2 = 2*M_PI/nRot2/linfo->Rot2Delta;
		} else {
			nRot2 = linfo->nRot2;		
		}	

	for(iRot2=0; iRot2<nRot2; iRot2++) {
		Rot2 = linfo->Rot2Start + iRot2*linfo->Rot2Delta*RatiodRot2;
		nRot3 = linfo->nRot3;

	for(iRot3=0; iRot3<linfo->nRot3; iRot3++) {
		Rot3 = linfo->Rot3Start + iRot3*linfo->Rot3Delta*RatiodRot3;
		if(linfo->flagFileList) {
			section = 0;
		} else {
			section = count;
		}

		// Thread
		iThread = count%threadNum;

		if(__eosPThread__) {
			if(pthread.status[iThread] == eosPThreadStatusRunning) { 
				eosPThreadJoin(&pthread, iThread, 0);	
			}
		}

		fprintf(stderr, "%d / %d iThread: %d\n", count, n, iThread);
		DEBUGPRINT3("%d / %d iThread: %d\n", count, n, iThread);

		// 
		out[iThread].Tailer[0].Cont.Mode = mrcImageTailerMode2DProjection;
		for(i=0; i<4; i++) out[iThread].Tailer[0].Cont.EulerAngleMode[i] = linfo->EulerAngleMode[i]; 
		out[iThread].Tailer[0].Cont.Rot1 = Rot1;
		out[iThread].Tailer[0].Cont.Rot2 = Rot2;
		out[iThread].Tailer[0].Cont.Rot3 = Rot3;
		llinfo[iThread].flagInit = 0;
		llinfo[iThread].section  = section;
		outSection[iThread] = count;


		//
		if(__eosPThread__) {
			//
			pthreadArg[iThread].Rot1  = out[iThread].Tailer[0].Cont.Rot1;
			pthreadArg[iThread].Rot2  = out[iThread].Tailer[0].Cont.Rot2;
			pthreadArg[iThread].Rot3  = out[iThread].Tailer[0].Cont.Rot3;	
			pthreadArg[iThread].llinfo = &(llinfo[iThread]); 
			pthreadArg[iThread].outSection = outSection[iThread];
			// 
			DEBUGPRINT3(">>> Thread: %d Count: %d outSection: %d\n", iThread, count, outSection[iThread]);
			eosPThreadCreate(&pthread, iThread, (void*)lmrcImage3Dto2DSingleForPThread, &(pthreadArg[iThread]), 0);
			DEBUGPRINT1("Thread Created: %d\n", iThread);
		} else {
			DEBUGPRINT5("lmrcImage3Dto2DSingle: %d %s %f %f %f\n", iThread,
				out[iThread].Tailer[0].Cont.EulerAngleMode,
				out[iThread].Tailer[0].Cont.Rot1,
				out[iThread].Tailer[0].Cont.Rot2,
				out[iThread].Tailer[0].Cont.Rot3);
			lmrcImage3Dto2DSingle(&(out[iThread]), in, 
				out[iThread].Tailer[0].Cont.EulerAngleMode,
				out[iThread].Tailer[0].Cont.Rot1,
				out[iThread].Tailer[0].Cont.Rot2,
				out[iThread].Tailer[0].Cont.Rot3,
				linfo, 
				&(llinfo[iThread]), 
				mode);
			lmrcImage3Dto2DSinglePost(fptInfo, dst, outSection[iThread], &out[iThread], linfo, mode);
		}
	
		count++;
		if(n<count) {
			fprintf(stderr, "Something wrong: count %d n %d\n", count, n);
			exit(EXIT_FAILURE);
		}
	}
	}
	}
	if(__eosPThread__) {
		eosPThreadJoinAll(&pthread, 0); 
	}
	//
	if(linfo->flagFileList) {
		dst->HeaderN.z = 1;
		dst->numTailer = 1;
	} else {
		dst->HeaderN.z = count;
		dst->numTailer = count;
	}
}


void
lmrcImage3Dto2DSingleForPThread(void* arg)
{
	lmrcImage3Dto2DSingleForPThreadArg* thisArg;

	thisArg = arg;

	DEBUGPRINT1("lmrcImage3Dto2DSingle Start: %d\n", thisArg->outSection);
	lmrcImage3Dto2DSingle(
			thisArg->out2D, thisArg->in3D, 
			thisArg->Mode,  thisArg->Rot1,		thisArg->Rot2,	thisArg->Rot3,	
			thisArg->linfo,	thisArg->llinfo,	thisArg->mode);
	DEBUGPRINT("lmrcImage3Dto2DSingle End\n");
	DEBUGPRINT1("lmrcImage3Dto2DSinglePost Start: %d\n", thisArg->outSection);
	lmrcImage3Dto2DSinglePost(
			thisArg->fptInfo, thisArg->dst, thisArg->outSection, thisArg->out2D, thisArg->linfo, thisArg->mode);
	DEBUGPRINT("lmrcImage3Dto2DSinglePost End\n");
}

void
lmrcImage3Dto2DSinglePost(FILE* fptInfo, mrcImage* dst, int outSection, mrcImage* out, lmrc3Dto2DInfo* linfo, int mode) 
{
	int i;
	char filename[1024];
	char Mode[5];

	if(linfo->flagFileList) {
		sprintf(filename, linfo->filenameNumberFormat, linfo->filenamePrefix, outSection, linfo->filenameSuffix);
		DEBUGPRINT2("%d: %s\n", outSection, filename);	
		DEBUGPRINT2("Nz: %d numTailer: %d\n", out->HeaderN.z, out->numTailer);	
		mrcFileWrite(out, filename, "in lmrc3Dto2D", 0);
		for(i=0; i<4; i++) {
			Mode[i] = out->Tailer[0].Cont.EulerAngleMode[i];
		}
		Mode[4] = '\0';
		fprintf(fptInfo, "%s %4s %15.6f %15.6f %15.6f\n", 
				filename, 
				Mode,
				out->Tailer[0].Cont.Rot1*DEGREE, 
				out->Tailer[0].Cont.Rot2*DEGREE, 
				out->Tailer[0].Cont.Rot3*DEGREE);
	} else {
		DEBUGPRINT1("Section(%d) Set for dst\n", outSection);
		for(i=0; i<4; i++) dst->Tailer[outSection].Cont.EulerAngleMode[i]  = out->Tailer[0].Cont.EulerAngleMode[i];
		dst->Tailer[outSection].Cont.Rot1  = out->Tailer[0].Cont.Rot1;
		dst->Tailer[outSection].Cont.Rot2  = out->Tailer[0].Cont.Rot2;
		dst->Tailer[outSection].Cont.Rot3  = out->Tailer[0].Cont.Rot3;	
		DEBUGPRINT1("Section Set Start: %d\n", outSection);
#ifdef DEBUG 
		mrcInfoPrint(stderr, out, 0);
		DEBUGPRINT3("Image %p Tailer %p num %d\n", out->Image, out->Tailer, out->numTailer);
#endif
		mrcImageSectionSet(dst, out, outSection, mode);
		DEBUGPRINT1("Section Set End  : %d\n", outSection);
	}
}

