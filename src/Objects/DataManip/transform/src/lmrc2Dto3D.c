/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrc2Dto3D.c ver %I%
#%Z% Created by tacyas 
#%Z%
#%Z% Usage : mrc2Dto3D.c
#%Z% Attention
#%Z%
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "mrcImage.h"
#include "Matrix3D.h"
#include "eosPThread.h"
#include "./lmrc2Dto3D.h"
#include "./lmrcImageRhoFiltering.h"

typedef struct lmrcImage2Dto3DSingleForPThreadArg {
	int iSection;
	mrcImage* inProjection;
	mrcImage* out3D;
	mrcImage* counter; 
	int counterNum; 
	lmrc2Dto3DInfo* linfo;
	int mode;
} lmrcImage2Dto3DAingleForPThreadArg;

extern void lmrcImage2Dto3DSingleForPThread(void* arg);
extern void lmrcImage2Dto3DSingle(mrcImage* out, mrcImage* counter, int counterNum, mrcImage* in, int iSection, lmrc2Dto3DInfo* linfo, int mode);


void
lmrcImage2Dto3DSingleForPThread(void* arg)
{
	lmrcImage2Dto3DAingleForPThreadArg* Arg ;
	Arg = (lmrcImage2Dto3DAingleForPThreadArg*)arg;

	DEBUGPRINT("Start lmrcImage2Dto3DSingleForPThread\n")
	lmrcImage2Dto3DSingle(Arg->out3D, Arg->counter, Arg->counterNum, Arg->inProjection, Arg->iSection, Arg->linfo, Arg->mode);
	DEBUGPRINT("End lmrcImage2Dto3DSingleForPThread\n")
}

void
lmrcImage2Dto3DSingle(mrcImage* out, mrcImage* counter, int counterNum, mrcImage* in, int iSection, lmrc2Dto3DInfo* linfo, int mode)
{
	mrcImage tmp;
	mrcImage prj;
	mrcImage kernel;
	Matrix3D Matrix;
	Matrix3D MatrixAnti;

	DEBUGPRINT("Start lmrcImage2Dto3DSingle\n")
	if(NULL!=in) {
		tmp.Header    = prj.Header    = in->Header;
		tmp.HeaderMode = prj.HeaderMode = mrcFloatImage;
		tmp.HeaderN.z = prj.HeaderN.z = 1;
		mrcInit(&tmp, NULL); mrcInit(&prj, NULL); 

		/* Projection Data Set */
		mrcImageSectionGet(&tmp, in, iSection, 0); 

		DEBUGPRINT("Start SetMatrix\n");
		/* Set Matrix */
		matrix3DRotationSetFollowingEulerAngle(Matrix,
										in->Tailer[iSection].Cont.EulerAngleMode,
										in->Tailer[iSection].Cont.Rot1, 
										in->Tailer[iSection].Cont.Rot2, 
										in->Tailer[iSection].Cont.Rot3, 
										MATRIX_3D_MODE_INITIALIZE);


		if(linfo->flagDouble && linfo->flagPlusXrot) {
			matrix3DRotationSetFollowingEulerAngle(Matrix,
											"XEYS",
											180*RADIAN, 
											0, 
											0, 
											MATRIX_3D_MODE_NOT_INITIALIZE);
		}
		if(linfo->flagDouble && linfo->flagPlusXrot) {
			matrix3DRotationSetFollowingEulerAngle(MatrixAnti,
											"XEYS",
											-180*RADIAN, 
											0, 
											0, 
											MATRIX_3D_MODE_INITIALIZE);
			matrix3DRotationAntiSetFollowingEulerAngle(MatrixAnti,
											in->Tailer[iSection].Cont.EulerAngleMode,
											in->Tailer[iSection].Cont.Rot1, 
											in->Tailer[iSection].Cont.Rot2, 
											in->Tailer[iSection].Cont.Rot3, 
											MATRIX_3D_MODE_NOT_INITIALIZE);
		} else {
			matrix3DRotationAntiSetFollowingEulerAngle(MatrixAnti,
											in->Tailer[iSection].Cont.EulerAngleMode,
											in->Tailer[iSection].Cont.Rot1, 
											in->Tailer[iSection].Cont.Rot2, 
											in->Tailer[iSection].Cont.Rot3, 
											MATRIX_3D_MODE_INITIALIZE);
		}
		DEBUGPRINT("End SetMatrix\n");
	} else {
		fprintf(stderr, "%s %d\n", linfo->inFileList[iSection], iSection); fflush(stderr);
		mrcFileRead(&tmp, linfo->inFileList[iSection], "in lmrcImage2Dto3DSingle", 0);
		prj.Header = tmp.Header;
		mrcInit(&prj, NULL);

		matrix3DRotationSetFollowingEulerAngle(Matrix,
										linfo->Tailer[iSection].Cont.EulerAngleMode,
										linfo->Tailer[iSection].Cont.Rot1, 
										linfo->Tailer[iSection].Cont.Rot2, 
										linfo->Tailer[iSection].Cont.Rot3, 
										MATRIX_3D_MODE_INITIALIZE);


		if(linfo->flagDouble && linfo->flagPlusXrot) {
			matrix3DRotationSetFollowingEulerAngle(Matrix,
											"XEYS",
											180*RADIAN, 
											0, 
											0, 
											MATRIX_3D_MODE_NOT_INITIALIZE);
		}
		if(linfo->flagDouble && linfo->flagPlusXrot) {
			matrix3DRotationSetFollowingEulerAngle(MatrixAnti,
											"XEYS",
											-180*RADIAN, 
											0, 
											0, 
											MATRIX_3D_MODE_INITIALIZE);
			matrix3DRotationAntiSetFollowingEulerAngle(MatrixAnti,
											linfo->Tailer[iSection].Cont.EulerAngleMode,
											linfo->Tailer[iSection].Cont.Rot1, 
											linfo->Tailer[iSection].Cont.Rot2, 
											linfo->Tailer[iSection].Cont.Rot3, 
											MATRIX_3D_MODE_NOT_INITIALIZE);

		} else {
			matrix3DRotationAntiSetFollowingEulerAngle(MatrixAnti,
											linfo->Tailer[iSection].Cont.EulerAngleMode,
											linfo->Tailer[iSection].Cont.Rot1, 
											linfo->Tailer[iSection].Cont.Rot2, 
											linfo->Tailer[iSection].Cont.Rot3, 
											MATRIX_3D_MODE_INITIALIZE);
		}
	}

	DEBUGPRINT("Start Filtering\n");
	/* Filtering */
	switch(linfo->mode) {
		case mrc2Dto3DModeSimpleBackProjection: {
			prj = tmp;
			break;
		}
		case mrc2Dto3DModeFilteredBackProjection: {
			if(linfo->flagDouble) {
				/* Preparing Rho Filtering */
				DEBUGPRINT("Start RhoFiltering2\n");
				//linfo->rhoInfo.Rmax = linfo->Rmax;
				lmrcImageRhoFiltering2(out, counter, counterNum, Matrix, &linfo->rhoInfo, 0);
				DEBUGPRINT("End RhoFiltering2\n");
				prj = tmp;
			} else {
				prj = tmp;
				mrcInit(&prj, NULL);
				linfo->rhoInfo1.Rmax = linfo->Rmax;
				linfo->rhoInfo1.filterMode = linfo->singleFilterMode;
				lmrcImageRhoFiltering(&prj, &tmp, MatrixAnti, linfo->rhoInfo1, linfo->singleTiltMode);
			}
			break;
		}
		case mrc2Dto3DModeWeightedBackProjection: {
			prj = tmp;
			mrcInit(&prj, NULL);
			kernel = tmp;
			kernel.HeaderMode = mrcFloatImage;
			kernel.HeaderN.z = 1;   
			if(linfo->flagDouble) {
				kernel.HeaderN.x = 3;  
				kernel.HeaderN.y = 3;
				mrcInit(&kernel, NULL);
				mrcPixelDataSet(&kernel, 0, 0, 0,  0,     mrcPixelRePart);
				mrcPixelDataSet(&kernel, 0, 1, 0, -0.125, mrcPixelRePart);
				mrcPixelDataSet(&kernel, 0, 2, 0,  0,     mrcPixelRePart);
				mrcPixelDataSet(&kernel, 1, 0, 0, -0.125, mrcPixelRePart);
				mrcPixelDataSet(&kernel, 1, 1, 0,  0.50,   mrcPixelRePart);
				mrcPixelDataSet(&kernel, 1, 2, 0, -0.125, mrcPixelRePart);
				mrcPixelDataSet(&kernel, 2, 0, 0,  0,     mrcPixelRePart);
				mrcPixelDataSet(&kernel, 2, 1, 0, -0.125, mrcPixelRePart);
				mrcPixelDataSet(&kernel, 2, 2, 0,  0,     mrcPixelRePart);
			} else {
				switch(linfo->singleTiltMode) {
					case 0: { // x-axix
						kernel.HeaderN.x = 1;  
						kernel.HeaderN.y = 3;
						mrcInit(&kernel, NULL);
						mrcPixelDataSet(&kernel, 0, 0, 0, -0.25, mrcPixelRePart);
						mrcPixelDataSet(&kernel, 0, 1, 0,  0.5,  mrcPixelRePart);
						mrcPixelDataSet(&kernel, 0, 2, 0, -0.25, mrcPixelRePart);
						break;
					} 
					case 1: { // y-axis
						kernel.HeaderN.x = 3;  
						kernel.HeaderN.y = 1;
						mrcInit(&kernel, NULL);
						mrcPixelDataSet(&kernel, 0, 0, 0, -0.25, mrcPixelRePart);
						mrcPixelDataSet(&kernel, 1, 0, 0,  0.5,  mrcPixelRePart);
						mrcPixelDataSet(&kernel, 2, 0, 0, -0.25, mrcPixelRePart);
						break;
					} 
					default: {
						fprintf(stderr, "Not supported singleTiltMode : %ld\n", linfo->singleTiltMode);
						exit(EXIT_FAILURE);
						break;
					}
				}

			}
			lmrcImageConvolution(&prj, &tmp, &kernel, 0);
			break;
		}
		default: {
			break;
		}
	}
	DEBUGPRINT("End Filtering\n");

	/* */
	DEBUGPRINT("Backprojection Start\n");
	DEBUGPRINT1("prj: %f\n", prj.ImageFloatImage[prj.HeaderN.x/2 + prj.HeaderN.y/2*prj.HeaderN.x]);
	switch(linfo->mode) {
		case mrc2Dto3DModeSimpleBackProjection: { /* Backprojection */
			lmrc2Dto3DSimpleBackProjectionForEach(out, &prj, linfo, Matrix, mode);
			break;
		}
		case mrc2Dto3DModeFilteredBackProjection: {
			lmrc2Dto3DFilteredBackProjectionForEach(out, &prj, linfo, Matrix, mode);
			if(!linfo->flagDouble) {
				mrcImageFree(&tmp, "in lmrc2Dto3DSingle");
			}
			break;
		}
		case mrc2Dto3DModeWeightedBackProjection: {
			lmrc2Dto3DFilteredBackProjectionForEach(out, &prj, linfo, Matrix, mode);
			if(!linfo->flagDouble) {
				mrcImageFree(&tmp, "in lmrc2Dto3DSingle");
			}
			break;
		}
		default: {
			break;
		}
	}
	DEBUGPRINT1("out: %f\n", out->ImageFloatImage[out->HeaderN.x/2 + out->HeaderN.y/2*out->HeaderN.x + out->HeaderN.z/2*out->HeaderN.x*out->HeaderN.y]);

	DEBUGPRINT("Backprojection End\n");
	mrcImageFree(&prj, "in lmrc2Dto3DSingle");
	DEBUGPRINT("End lmrcImage2Dto3DSingle\n")
}

void 
lmrc2Dto3D(mrcImage* out, mrcImage* in, lmrc2Dto3DInfo* linfo, long mode)
{
	mrcImage tmp2D;
	mrcImageParaTypeInteger i;
	long j;
	mrcImageParaTypeInteger numProjection;
	Matrix3D Matrix;
	mrcImage*               tmp3D=NULL;
	int threadNum   = 1;        /* Thrad Number */
	int iThread     = 0;        /* Thread ID */
	mrcImage* counter;          /* Counter for eacha Thread */
	int* threadCounter;         /* Counter for each thread */ 
	eosPThread pthread;
	lmrcImage2Dto3DAingleForPThreadArg* pthreadArg=NULL;

	if(__eosPThread__) {
		threadNum = __eosPThreadNum__;
		eosPThreadInit(&pthread, threadNum, 0);
		eosPThreadMutexInit(&pthread);
		pthreadArg = (lmrcImage2Dto3DAingleForPThreadArg*)
		memoryAllocate(sizeof(lmrcImage2Dto3DAingleForPThreadArg)*threadNum, "in lmrc2Dto3D");
	} else {
		threadNum = 1;
	}

	counter                 = (mrcImage*)memoryAllocate(sizeof(mrcImage)*threadNum, "in lmrc2Dto3D");
	threadCounter           = (int*)memoryAllocate(sizeof(int)*threadNum, "in lmrc2Dto3D");
	linfo->CounterForWeight = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrc2Dto3D");

	// 3D-Area Allocation
	if(NULL!=in) {
		out->Header = in->Header;
	} else {
		DEBUGPRINT("Each Mode\n");
		if(0<linfo->inFileNum) {
			mrcFileRead(&tmp2D, linfo->inFileList[0], "in lmrc2Dto3D", 0);
			out->Header = tmp2D.Header;	
		} else {
			fprintf(stderr, "Projection Files not defined. in lmrc2Dto3D\n");
			exit(EXIT_FAILURE);
		}
	}
	if(linfo->flagOutputSize) {
		out->HeaderN.x = linfo->Nx;
		out->HeaderN.y = linfo->Ny;
		out->HeaderN.z = linfo->Nz;
	} else { 
		if(NULL!=in) {
			out->HeaderN.x = MAX(in->HeaderN.x, in->HeaderN.y);
			out->HeaderN.y = MAX(in->HeaderN.x, in->HeaderN.y);
			out->HeaderN.z = MAX(in->HeaderN.x, in->HeaderN.y);
		} else {
			out->HeaderN.x = MAX(tmp2D.HeaderN.x, tmp2D.HeaderN.y);
			out->HeaderN.y = MAX(tmp2D.HeaderN.x, tmp2D.HeaderN.y);
			out->HeaderN.z = MAX(tmp2D.HeaderN.x, tmp2D.HeaderN.y);
			DEBUGPRINT3("Size: %d %d %d\n",out->HeaderN.x, out->HeaderN.y, out->HeaderN.z);
		}
	}
	out->HeaderLength.z = out->HeaderLength.x;
	mrcInit(out, NULL);

	if(__eosPThread__) {
		tmp3D = (mrcImage*)memoryAllocate(sizeof(mrcImage)*threadNum, "in lmrc2Dto3D");
		for(i=0; i<threadNum; i++) {
			tmp3D[i].Header = 	out->Header;
			mrcInit(&(tmp3D[i]), NULL);

			pthreadArg[i].inProjection = in;
			pthreadArg[i].linfo        = linfo;
			pthreadArg[i].mode         = mode;
		}
	}

	if(NULL!=in) {
		numProjection = in->numTailer;
	} else {
		numProjection = linfo->inFileNum;
	}

	for(i=0; i<numProjection; i++) {
		iThread = i%threadNum; 

		if(__eosPThread__) {
			if(pthread.status[iThread] == eosPThreadStatusRunning) {
				eosPThreadJoin(&pthread, iThread, 0);
			}
		}

		fprintf(stderr, "%d / %d : thread %d count %d\n", i, numProjection, iThread, threadCounter[iThread]);

		//DEBUGPRINT4("%d: %g %g %g\n", i, in->Tailer[i].Cont.Rot1*DEGREE, in->Tailer[i].Cont.Rot2*DEGREE, in->Tailer[i].Cont.Rot3*DEGREE);

		if(__eosPThread__) {
			pthreadArg[iThread].iSection = i;
			pthreadArg[iThread].out3D = &(tmp3D[iThread]);
			pthreadArg[iThread].counter = &(counter[iThread]);
			pthreadArg[iThread].counterNum = threadCounter[iThread];

			eosPThreadCreate(&pthread, iThread, (void*)lmrcImage2Dto3DSingleForPThread, &(pthreadArg[iThread]), 0);
			//lmrcImage2Dto3DSingleForPThread(&(pthreadArg[iThread]));
	 	} else {
			DEBUGPRINT("No threading: lmrcImage2Dto3DSingle\n");
			lmrcImage2Dto3DSingle(out, &(counter[iThread]), threadCounter[iThread], in, i, linfo, mode);
			DEBUGPRINT1("out before filter: %f\n", out->ImageFloatImage[out->HeaderN.x/2 + out->HeaderN.y/2*out->HeaderN.x + out->HeaderN.z/2*out->HeaderN.x*out->HeaderN.y]);
		}
		threadCounter[iThread]++;
		
	}

	// Join
	if(__eosPThread__) {
		DEBUGPRINT("JOIN\n");
		eosPThreadJoinAll(&pthread, 0);
		DEBUGPRINT("JOINED\n");
	}


	// Post-filtering: 
	// Rho-Filtering and/or Density Averaging 
	if(linfo->flagDouble && linfo->mode==mrc2Dto3DModeFilteredBackProjection) {
		/* Perform RhoFiltering */
#ifdef DEBUG
		mrcFileWrite(out, "/tmp/RawDataforDebug.mrc3d", "in main", 0);
		mrcFileWrite(&(counter[0]), "/tmp/counter0", "in main", 0);
#endif
		for(i=0, j=0; i<threadNum; i++) {
			lmrcImageAdd(linfo->CounterForWeight, &(counter[i]), &j);	
			if(__eosPThread__) {
				j-=1;
				lmrcImageAdd(out,                     &(tmp3D[i]),   &j);	
			}
		}
		if(i!=j) {
			fprintf(stderr, "i(%d)!=j(%ld)\n", i, j);
		}
		// Perform Filtering 
		lmrcImageRhoFiltering2(out, linfo->CounterForWeight, threadNum, Matrix, &linfo->rhoInfo, 1);
		DEBUGPRINT1("out after filter: %f\n", out->ImageFloatImage[out->HeaderN.x/2 + out->HeaderN.y/2*out->HeaderN.x + out->HeaderN.z/2*out->HeaderN.x*out->HeaderN.y]);
	} else {
		lmrcImageDividedByReal(out, numProjection);
	}

	// Statistics
	mrcStatDataSet(out, 0);
}

void
lmrcImage2Dto3DInitProcess()
{
}


void 
lmrc2Dto3DSimpleBackProjectionForEach(mrcImage* out, mrcImage* prj, lmrc2Dto3DInfo* linfo, Matrix3D Matrix, long mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal tmpx, tmpy, tmpz;
	mrcImageParaTypeReal prjx, prjy, prjz;
	double projdata, data;
	mrcImageParaTypeReal    gx, gy, gz;
	mrcImageParaTypeReal    g3x, g3y, g3z;
	floatVector v; 
	int index;

	floatVectorInit(&v, 4);
	v.data[3] = 1.0;

	g3x = (out->HeaderN.x - 1)/2.0;
	g3y = (out->HeaderN.y - 1)/2.0;
	g3z = (out->HeaderN.z - 1)/2.0;
	gx  = (prj->HeaderN.x - 1)/2.0;
	gy  = (prj->HeaderN.y - 1)/2.0;
	gz  = 0.0;

	for(z=0; z<out->HeaderN.z; z++) {
		v.data[2] = z-g3z;
	for(y=0; y<out->HeaderN.y; y++) {
		v.data[1] = y-g3y; 
	for(x=0; x<out->HeaderN.x; x++) {
		index = x + y*out->HeaderN.x + z*out->HeaderN.x*out->HeaderN.y; 
		v.data[0] = x-g3x; 
		//matrix3DMultiplyVector(&v, Matrix);

		tmpx = Matrix[0][0]*v.data[0]+ Matrix[1][0]*v.data[1] +  Matrix[2][0]*v.data[2]; 	
		tmpy = Matrix[0][1]*v.data[0]+ Matrix[1][1]*v.data[1] +  Matrix[2][1]*v.data[2]; 	
		tmpz = Matrix[0][2]*v.data[0]+ Matrix[1][2]*v.data[1] +  Matrix[2][2]*v.data[2]; 	

		prjx = tmpx + gx; 
		prjy = tmpy + gy;
		prjz = tmpz + g3z;
		//prjx = v.data[0] + gx; 
		//prjy = v.data[1] + gy;
		//prjz = v.data[2] + g3z;
		//mrcPixelDataGet(out, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);

		if( -0.5<=prjx && prjx<prj->HeaderN.x-0.5
		  &&-0.5<=prjy && prjy<prj->HeaderN.y-0.5) {
				data = out->ImageFloatImage[index];
				mrcPixelDataGet(prj, prjx, prjy, 0.0, &projdata, mrcPixelRePart, linfo->InterpolationMode);
				//mrcPixelDataSet(out, x, y, z, data + projdata, mrcPixelRePart);
				out->ImageFloatImage[index] = data + projdata;
		}
	}
	}
	}
}

void
lmrc2Dto3DFilteredBackProjectionForEach(mrcImage* out, mrcImage* prj, lmrc2Dto3DInfo* linfo, Matrix3D Matrix, long mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal tmpx, tmpy, tmpz;
	mrcImageParaTypeReal tmpxx, tmpyx, tmpzx;
	mrcImageParaTypeReal tmpxy, tmpyy, tmpzy;
	mrcImageParaTypeReal tmpxz, tmpyz, tmpzz;
	mrcImageParaTypeReal prjx, prjy, prjz;
	double projdata, data, normz;
	mrcImageParaTypeReal    gx, gy, gz;
	mrcImageParaTypeReal    g3x, g3y, g3z;
	floatVector v; 
	int index3d;
	int index2d;

	floatVectorInit(&v, 4);
	v.data[3] = 1.0;

	g3x = (out->HeaderN.x - 1)/2.0;
	g3y = (out->HeaderN.y - 1)/2.0;
	g3z = (out->HeaderN.z - 1)/2.0;
	gx  = (prj->HeaderN.x - 1)/2.0;
	gy  = (prj->HeaderN.y - 1)/2.0;
	gz  = 0.0;

	for(z=0; z<out->HeaderN.z; z++) {
		v.data[2] = z-g3z;
		tmpxz = Matrix[2][0]*v.data[2]; 
		tmpyz = Matrix[2][1]*v.data[2]; 
		tmpzz = Matrix[2][2]*v.data[2]; 

	for(y=0; y<out->HeaderN.y; y++) {
		v.data[1] = y-g3y; 
		tmpxy = Matrix[1][0]*v.data[1]; 
		tmpyy = Matrix[1][1]*v.data[1]; 
		tmpzy = Matrix[1][2]*v.data[1]; 

	for(x=0; x<out->HeaderN.x; x++) {
		index3d = x + y*out->HeaderN.x + z*out->HeaderN.x*out->HeaderN.y; 
		v.data[0] = x-g3x; 
		tmpxx = Matrix[0][0]*v.data[0]; 
		tmpyx = Matrix[0][1]*v.data[0]; 
		tmpzx = Matrix[0][2]*v.data[0]; 
		//matrix3DMultiplyVector(&v, Matrix);
		tmpx = tmpxx + tmpxy +  tmpxz; 	
		tmpy = tmpyx + tmpyy +  tmpyz; 	
		tmpz = tmpzx + tmpzy +  tmpzz; 	

		//prjx = v.data[0] + gx; 
		//prjy = v.data[1] + gy;
		//prjz = v.data[2] + g3z;
		prjx = tmpx + gx; 
		prjy = tmpy + gy;
		prjz = tmpz + g3z;
		if(-0.5<=prjz && prjz < out->HeaderN.z - 0.5) {	
			//mrcPixelDataGet(out, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if( -0.5<=prjx && prjx<prj->HeaderN.x-0.5
			  &&-0.5<=prjy && prjy<prj->HeaderN.y-0.5) {
				data = out->ImageFloatImage[index3d];
				mrcPixelDataGet(prj, prjx, prjy, 0.0, &projdata, mrcPixelRePart, linfo->InterpolationMode);
				if(linfo->flagDouble && linfo->rhoInfo.flagThicknessWeight) {
					normz = fabs(tmpz/g3z); 
					if(normz < 0.9) {
					
					} else if(normz < 1) { 
						projdata *=  (cos(M_PI*(normz-0.9)/0.1)+1.0)/2.0;
					} else {
						projdata = 0; 
					}
				} 
			//	mrcPixelDataSet(out, x, y, z, data + projdata, mrcPixelRePart);
				out->ImageFloatImage[index3d] = data + projdata;
			}
		}
	}
	}
	}
}
