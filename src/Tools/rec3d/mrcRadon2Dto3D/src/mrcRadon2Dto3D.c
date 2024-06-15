/*
  # mrcRadon2Dto3D : $Revision$  
  # $Date$ 
  # Created by $Author$
  # Usage : mrcRadon2Dto3D
  # Attention
  #   $Loccker$
  #  	$State$ 
  #
*/
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
#include "Matrix3D.h"
#include "lmrcImageRhoFiltering.h"

typedef enum lmrc2Dto3DMode {
	mrc2Dto3DModeNearestNeighborInterpolation = 0,
	mrc2Dto3DModeHigherOrderInterpolation     = 1
} lmrc2Dto3DMode;

typedef struct lmrcRadon2Dto3DInfo {
  double dp;
  double dtheta;
  double dphi;
  //int    dthetaDEGREE;
  double    dthetaDEGREE;
  //int    dphiDEGREE;
  double    dphiDEGREE;
  double T;
  lmrc2Dto3DMode mode;
  int            InterpolationMode;
  char* fnameW;
  mrcImage number;
} lmrcRadon2Dto3DInfo;

typedef struct Angleitem{
	double  angle; /*radian*/
	double  d;
	double* N;     /*3Dnumber*/
	   int  PlusN;
	   int  MinusN;
	   int  TotalN;
    double  check;
	   int  flag;
	   int  n; /*count*/
}Angleitem;

typedef struct Deltaitem{
	double angle;
	double d;
	double moveangle;
	double movecos;
	double movesin;
}Deltaitem;

typedef struct AngleSet{
	Angleitem* theta;
	Angleitem* phi;
	Deltaitem* delta;
}AngleSet;

extern void lmrcRadon2Dto3D(mrcImage* Out, mrcImage* in, lmrcRadon2Dto3DInfo* linfo, long mode);

extern void lmrcRadon2Dto2DMulti(mrcImage* out, char** filename, int number, FILE* fptInfo, int mode);

extern void lmrcRadon2Dto2DMulti2(mrcImage* out, char** filename, char** fnameBefore, int number, int numberBefore, FILE* fptInfo, int mode);

int
main(int argc, char* argv[]) 
{
  mrcRadon2Dto3DInfo info;
  static lmrcRadon2Dto3DInfo linfo;
  static mrcImage In;
  static mrcImage Out;
  
  init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);	
  
  linfo.dp     = info.dp;
  linfo.dtheta = info.dtheta*RADIAN;
  linfo.dphi   = info.dphi*RADIAN;
  linfo.dthetaDEGREE = info.dtheta;
  linfo.dphiDEGREE   = info.dphi;
  linfo.T      = info.T;

  linfo.mode              = info.mode;
  linfo.InterpolationMode = info.InterpolationMode;
   
	linfo.fnameW = MemoryAllocate(char, 256, "in main");
	strcpy(linfo.fnameW, info.OutW);

  DEBUGPRINT("Program Start !!\n");

	if(info.flagInBefore){
		if(info.flagIn2){
			lmrcRadon2Dto2DMulti2(&In, info.In2, info.InBefore, info.flagIn2, info.flagInBefore, info.fptIn2List, 0);
			lmrcRadon2Dto3D(&Out, &In, &linfo, 0);
		}
		else{
			fprintf(stderr,"-I is required\n");
			exit(EXIT_FAILURE);
		}
	}
	else{
		if(info.flagIn2){
			lmrcRadon2Dto2DMulti(&In, info.In2, info.flagIn2, info.fptIn2List, 0);
			lmrcRadon2Dto3D(&Out, &In, &linfo, 0);
		}
		else{
			fprintf(stderr,"-I is required\n");
			exit(EXIT_FAILURE);
		}
	}

	if(info.flaginbefore){
		static mrcImage before;
		static mrcImage append;
		static mrcImage numberBefore;
		int x, y, z;
		double data, data1, data2;
		double weight, weight1, weight2;
		mrcImageParaTypeRealCoord to;

		to.x = to.y = to.z = 0;
		mrcFileRead(&before, info.inbefore, "in main", 0);
		mrcFileRead(&numberBefore, info.inWbefore, "in main", 0);
		append.Header = Out.Header;
		mrcInit(&append, NULL);
		lmrcImageCopy(&append, &Out, to);
		mrcImageFree(&Out, "in main");
		mrcInit(&Out, NULL);
		for(x=0; x<Out.HeaderN.x; x++){
		for(y=0; y<Out.HeaderN.y; y++){
		for(z=0; z<Out.HeaderN.z; z++){
			mrcPixelDataGet(&before, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&append, x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&numberBefore, x, y, z, &weight1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo.number, x, y, z, &weight2, mrcPixelRePart, mrcPixelHowNearest);
			data1  = data1 * weight1;
			data2  = data2 * weight2;
			data   = data1 + data2;
			weight = weight1 + weight2;
			data   = data / weight;
			mrcPixelDataSet(&Out, x, y, z, data, mrcPixelRePart);
		}
		}
		}
	}
	
  mrcFileWrite(&Out, info.Out, "in main", 0);
  
  DEBUGPRINT("Program End !!\n");
  
  exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, " 0 = NearestNeighbor\n");
	fprintf(stderr, " 1 = HigherOrder     (-T)\n");
}

void
lmrcRadon2Dto2DMulti2(mrcImage* out, char** filename, char** fnameBefore, int number, int numberBefore, FILE* fptInfo, int mode)
{
  long i, j, count;
  mrcImage* in;
  mrcImageParaTypeInteger Nx, Ny;
  mrcImageParaTypeReal LengthX, LengthY;
  mrcImageParaTypeReal srcx, srcy;
  mrcImageParaTypeReal dstx, dsty, dstz;
  char s[1024];
  double data;
  int* flag;

	flag = MemoryAllocate(int, number, "in lmrcRadon2Dto2DMulti");
	for(i=0; i<number; i++) {
		flag = 0;
	}
	for(i=0; i<number; i++) {
		for(j=0; j<numberBefore; j++){
			if(strcoll(fnameBefore[j], filename[i]) == 0){
				flag[i] = 1;
			}
			else{
			}
		}
	}
	count = 0;
	for(i=0; i<number; i++) {
		if(flag[i] == 0) count++;
	}

  in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*count, "in lmrcRadon2Dto2DMulti");
  Nx = 0;
  Ny = 0;
  LengthX = 1e6;
  LengthY = 1e6;
	
	count = 0;
	for(i=0; i<number; i++) {
		if(flag[i] == 0){
			mrcFileRead(&(in[count]), filename[i], "in lmrcRadon2Dto2DMulti", 0);
			if(Nx < in[count].HeaderN.x) Nx = in[count].HeaderN.x;
			if(Ny < in[count].HeaderN.y) Ny = in[count].HeaderN.y;
			if(in[count].HeaderLength.x < LengthX) LengthX = in[count].HeaderLength.x;
			if(in[count].HeaderLength.y < LengthY) LengthY = in[count].HeaderLength.y;
			count++;
		}
	}      
  out->HeaderN.x = Nx;
  out->HeaderN.y = Ny;
  out->HeaderN.z = count;
  out->HeaderMode = mrcFloatRadonImage;
  out->HeaderLength.x = LengthX;
  out->HeaderLength.y = LengthY;
  out->HeaderLength.z = 1;
  mrcInit(out, NULL);
  for(dstz=0; dstz<number; dstz++) {
  for(dstx=0; dstx<in->HeaderN.x; dstx++) {
  for(dsty=0; dsty<in->HeaderN.y; dsty++) {
    srcx = dstx - (out->HeaderN.x - in->HeaderN.x)/2.0;
    srcy = dsty - (out->HeaderN.y - in->HeaderN.y)/2.0;
	/* change in 2004/12/04 */
	srcy = out->HeaderN.y - srcy;
    mrcPixelDataGet(&(in[(int)dstz]), srcx, srcy,  0.0, &data, mrcPixelRePart, mrcPixelHowLinear);
    mrcPixelDataSet(out,              dstx, dsty, dstz,  data, mrcPixelRePart);
  }
  }
  }
  out->numTailer = count;
  out->Tailer = (mrcImageTailer*)memoryAllocate(sizeof(mrcImageTailer)*count, "in lmrcRadon2Dto2DMulti");

  fseek(fptInfo, 0L, SEEK_SET);
	count = 0;
	for(i=0; i<number; i++) {
		if(flag[i] == 0){
			stringGetFromFile(s, "", fptInfo, stdout, 3);
			out->Tailer[count].Cont.Mode = mrcImageTailerMode2DProjection;
			stringCopy(out->Tailer[count].Cont.EulerAngleMode, stringGetNthWord(s, 2, " \t,"), 4);
			out->Tailer[count].Cont.Rot1 = stringGetNthRealData(s, 3, " ,\t")*RADIAN;
			out->Tailer[count].Cont.Rot2 = stringGetNthRealData(s, 4, " ,\t")*RADIAN;
			out->Tailer[count].Cont.Rot3 = stringGetNthRealData(s, 5, " ,\t")*RADIAN;
			count++;
		}
	}
  for(i=0; i<number; i++) {
    mrcImageFree(&(in[i]), "in lmrcRadon2Dto2DMulti");
  }
  free(in);  
}

void
lmrcRadon2Dto2DMulti(mrcImage* out, char** filename, int number, FILE* fptInfo, int mode)
{
  long i;
  mrcImage* in;
  mrcImageParaTypeInteger Nx, Ny;
  mrcImageParaTypeReal LengthX, LengthY;
  mrcImageParaTypeReal srcx, srcy;
  mrcImageParaTypeReal dstx, dsty, dstz;
  char s[1024];
  double data;

  in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*number, "in lmrcRadon2Dto2DMulti");
  Nx = 0;
  Ny = 0;
  LengthX = 1e6;
  LengthY = 1e6;

  for(i=0; i<number; i++) {

    mrcFileRead(&(in[i]), filename[i], "in lmrcRadon2Dto2DMulti", 0);
    if(Nx < in[i].HeaderN.x) {
      Nx = in[i].HeaderN.x;
	  DEBUGPRINT2("i=%d Nx=%d\n", i, Nx);
    }
    if(Ny < in[i].HeaderN.y) {
      Ny = in[i].HeaderN.y;
    }
    if(in[i].HeaderLength.x < LengthX) {
      LengthX = in[i].HeaderLength.x;
    }
    if(in[i].HeaderLength.y < LengthY) {
      LengthY = in[i].HeaderLength.y;
    }
  }      
  out->HeaderN.x = Nx;
  out->HeaderN.y = Ny;
  out->HeaderN.z = number;
  out->HeaderMode = mrcFloatRadonImage;
  out->HeaderLength.x = LengthX;
  out->HeaderLength.y = LengthY;
  out->HeaderLength.z = 1;
  mrcInit(out, NULL);
  for(dstz=0; dstz<number; dstz++) {
  for(dstx=0; dstx<in->HeaderN.x; dstx++) {
  for(dsty=0; dsty<in->HeaderN.y; dsty++) {
    srcx = dstx - (out->HeaderN.x - in->HeaderN.x)/2.0;
    srcy = dsty - (out->HeaderN.y - in->HeaderN.y)/2.0;
	/* change in 2004/12/04 */
	srcy = out->HeaderN.y - srcy;
    mrcPixelDataGet(&(in[(int)dstz]), srcx, srcy,  0.0, &data, mrcPixelRePart, mrcPixelHowLinear);
    mrcPixelDataSet(out,              dstx, dsty, dstz,  data, mrcPixelRePart);
  }
  }
  }
  out->numTailer = number;
  out->Tailer = (mrcImageTailer*)memoryAllocate(sizeof(mrcImageTailer)*number, "in lmrcRadon2Dto2DMulti");
  fseek(fptInfo, 0L, SEEK_SET);
  for(i=0; i<number; i++) {
    stringGetFromFile(s, "", fptInfo, stdout, 3);
    out->Tailer[i].Cont.Mode = mrcImageTailerMode2DProjection;
    stringCopy(out->Tailer[i].Cont.EulerAngleMode, stringGetNthWord(s, 2, " \t,"), 4);
    out->Tailer[i].Cont.Rot1 = stringGetNthRealData(s, 3, " ,\t")*RADIAN;
    out->Tailer[i].Cont.Rot2 = stringGetNthRealData(s, 4, " ,\t")*RADIAN;
    out->Tailer[i].Cont.Rot3 = stringGetNthRealData(s, 5, " ,\t")*RADIAN;
  }
  for(i=0; i<number; i++) {
    mrcImageFree(&(in[i]), "in lmrcRadon2Dto2DMulti");
  }
  free(in);  
}

void
__lmrcRadon2Dto3DImageSizeSet(mrcImage* out, mrcImage* in, lmrcRadon2Dto3DInfo* linfo, long mode)
{
  out->Header         = in->Header;
  out->HeaderN.x      = in->HeaderN.x*in->HeaderLength.x/linfo->dp;
  out->HeaderN.y      = 180/linfo->dthetaDEGREE;
  out->HeaderN.z      = 360/linfo->dphiDEGREE;
  out->HeaderLength.x = linfo->dp;
  out->HeaderLength.y = linfo->dtheta*DEGREE;
  out->HeaderLength.z = linfo->dphi*DEGREE;
  DEBUGPRINT5("in N %d L %f dp %f out N %d L %f\n",in->HeaderN.x, in->HeaderLength.x, linfo->dp, out->HeaderN.x, out->HeaderLength.x);
}

void
__lmrcImageRadon2Dto3DSinoToRadon3DHigherOrderInterpolation(mrcImage* out, mrcImage* number, 
					   mrcImageParaTypeReal x3, 
					   AngleSet* angleset,
					   double projdata, double* WW, int mode)
{
    int j, k, l;
    double* Wprojdata; 
    double data, count;

	Wprojdata = (double*)memoryAllocate(sizeof(double)*angleset->theta->TotalN*angleset->phi->TotalN, "Wprojdata");
    for(j=0; j<angleset->theta->TotalN*angleset->phi->TotalN; j++) {
      Wprojdata[j] = projdata*WW[j];
	}
 
    l=0;
    for(j=0; j<angleset->theta->TotalN; j++){
    for(k=0; k<angleset->phi->TotalN; k++){
      mrcPixelDataGet(out, x3, angleset->theta->N[j], angleset->phi->N[k], &data, mrcPixelRePart, mrcPixelHowNearest);
      data += Wprojdata[l];
      mrcPixelDataSet(out, x3, angleset->theta->N[j], angleset->phi->N[k], data, mrcPixelRePart);
      
      mrcPixelDataGet(number, x3, angleset->theta->N[j], angleset->phi->N[k], &count, mrcPixelRePart, mrcPixelHowNearest);
      count += WW[l];
      mrcPixelDataSet(number, x3, angleset->theta->N[j], angleset->phi->N[k], count, mrcPixelRePart);
      l++;
    }
    }
    free(Wprojdata);
}

void
__lmrcImageRadon2Dto3DSinoToRadon3DNearest(mrcImage* out, mrcImage* number, 
					   mrcImageParaTypeReal x3, 
					   mrcImageParaTypeReal y3, 
					   mrcImageParaTypeReal z3, 
					   double projdata, int mode)
{
  double data;
  double count;

  if(1==mode) {
    mrcImageParaTypeReal tmpy3;

    for(tmpy3=0; tmpy3<out->HeaderN.y; tmpy3++) {
      mrcPixelDataGet(out, x3, tmpy3, z3, &data, mrcPixelRePart, mrcPixelHowNearest);
      data = data+projdata;
      mrcPixelDataSet(out, x3, tmpy3, z3, data, mrcPixelRePart);

      mrcPixelDataGet(number, x3, tmpy3, z3, &count, mrcPixelRePart, mrcPixelHowNearest);
      count += 1;
      mrcPixelDataSet(number, x3, tmpy3, z3, count, mrcPixelRePart);
    }
  } else {
    mrcPixelDataGet(out, x3, y3, z3, &data, mrcPixelRePart, mrcPixelHowNearest);
    data = data+projdata;
    mrcPixelDataSet(out, x3, y3, z3, data, mrcPixelRePart);
    
    mrcPixelDataGet(number, x3, y3, z3, &count, mrcPixelRePart, mrcPixelHowNearest);
    count += 1;
    mrcPixelDataSet(number, x3, y3, z3, count, mrcPixelRePart);
  }
}


void
__lmrcRadon2Dto3DNormalization(mrcImage* out, mrcImage number, int mode)
{
  int    i, j, k;
  double data, count;

  for(i=0; i<out->HeaderN.x; i++){
  for(j=0; j<out->HeaderN.y; j++){
  for(k=0; k<out->HeaderN.z; k++){
    switch(mode){
    case mrc2Dto3DModeNearestNeighborInterpolation:
      mrcPixelDataGet(&number, i, j, k, &count, mrcPixelRePart, mrcPixelHowNearest);
      if(count>1.0){
		mrcPixelDataGet(out, i, j, k, &data, mrcPixelRePart, mrcPixelHowNearest);
		data = data/count;
		mrcPixelDataSet(out, i, j, k, data, mrcPixelRePart);
      }
      break;
      
    case mrc2Dto3DModeHigherOrderInterpolation:
      mrcPixelDataGet(&number, i, j, k, &count, mrcPixelRePart, mrcPixelHowNearest);
      if(count<1){
		data = 0;
      } else {
		mrcPixelDataGet(out, i, j, k, &data, mrcPixelRePart, mrcPixelHowNearest);
		data /= count; 
      }
      mrcPixelDataSet(out, i, j, k, data, mrcPixelRePart);
      break;
    }
  }
  }
  }
}

double*
__WeightCalculation(mrcImage* in ,AngleSet* angleset ,mrcImageParaTypeInteger i ,lmrcRadon2Dto3DInfo* linfo )
{

    double *WW;
	//double sumWW=0;
	int    l=0;
	int    j;
	double tau;
	double Tau;
	double dmax;
	floatVector v;
	Matrix3D    MatrixForInterpolation;

  	floatVectorInit(&v, 4);
	WW = (double*)memoryAllocate(sizeof(double)*angleset->theta->TotalN*angleset->phi->TotalN, "angleset->theta->angle*angleset->phi->angle");

  	dmax = MAX(angleset->theta->d,angleset->phi->d);

	for(angleset->theta->n=0; angleset->theta->n<angleset->theta->TotalN; angleset->theta->n++){	
	  for(angleset->phi->n=0; angleset->phi->n<angleset->phi->TotalN; angleset->phi->n++){
	    /* calculate tau */
	    if(angleset->theta->angle < -M_PI) { /* phi = PI/2 or 3/2 PI */
			tau = fabs(angleset->phi->angle-angleset->phi->N[angleset->phi->n]*angleset->phi->d);
		} else {
	      /*
		            1   cos(delta) -sin(delta) 0   1    cos(delta)                                      eta1
	  RotZ(-delta)* 0 = sin(delta)  cos(delta) 0 * 0 = -sin(delta) = RotZ(gamma)*RotY(beta)*RotZ(alpha)*eta2
		            0      0           0       1   0       0                                            eta3
	      */
	      v.data[0] = cos(angleset->theta->N[angleset->theta->n]*angleset->theta->d)*cos(angleset->phi->N[angleset->phi->n]*angleset->phi->d);
	      v.data[1] = -sin(angleset->phi->N[angleset->phi->n]*angleset->phi->d);
	      v.data[2] = sin(angleset->theta->N[angleset->theta->n]*angleset->theta->d)*cos(angleset->phi->N[angleset->phi->n]*angleset->phi->d);
	      v.data[3] = 1.0;
	      
	      matrix3DRotationSetFollowingEulerAngle(MatrixForInterpolation,
						     in->Tailer[i].Cont.EulerAngleMode,
						     in->Tailer[i].Cont.Rot1,
						     in->Tailer[i].Cont.Rot2,
						     in->Tailer[i].Cont.Rot3,
						     MATRIX_3D_MODE_INITIALIZE);
	      
	      matrix3DMultiplyVector(&v, MatrixForInterpolation);
	      
	      angleset->delta->movecos = v.data[0];
	      angleset->delta->movesin = -v.data[1];
	      
	      angleset->delta->moveangle = acos(angleset->delta->movecos);	
	      if(angleset->delta->movesin<0){
		angleset->delta->moveangle = 2*M_PI-angleset->delta->moveangle;
	      }
	      tau = fabs(angleset->delta->angle-angleset->delta->moveangle);
	    }
	    
	    tau = MIN(fmod(2*M_PI-tau+2*M_PI,2*M_PI), fmod(tau+2*M_PI, 2*M_PI));
	    Tau = tau/dmax;

	    if(0<Tau && Tau<linfo->T){
	      WW[l] = sin(M_PI*Tau)*exp(-SQR(M_PI*Tau)/9.2023)/(M_PI*Tau);
	    } else if(Tau>-linfo->T && Tau<0){
	      WW[l] = sin(M_PI*Tau)*exp(-SQR(M_PI*Tau)/9.2023)/(M_PI*Tau);
	    } else if(Tau==0){
		  WW[l] = 1;
	    }
	    //sumWW += WW[l];
	    l++;	    
	  }
	}

	/*	
	if(angleset->theta->angle > -M_PI){
		for(j=0; j<l; j++){
	  		WW[j] /= sumWW;
		}
	}
	*/
	return WW;
}

void
__AngleCalculation(mrcImage* in ,mrcImage* out ,mrcImageParaTypeInteger i , mrcImageParaTypeInteger y2 ,AngleSet* angleset)
{
 		
	Matrix3D    Matrix;
	floatVector v;
	double      eta1 ,eta2 ,eta3;

	floatVectorInit(&v,4);

	angleset->delta->angle = y2*angleset->delta->d;

      /* Set Matrix 
	 
	 	1                                                     eta1    eta1                                                     1
		0  = angleset->delta->angle * gamma * beta * alpha *  eta2 -> eta2 = -alpha * -beta * -gamma * -angleset->delta->angle 0
		0                                                     eta3    eta3                                                     0
      */
      matrix3DRotationSetFollowingEulerAngle(Matrix, "ZOYS", -angleset->delta->angle, 0, 0, MATRIX_3D_MODE_INITIALIZE);

	matrix3DRotationAntiSetFollowingEulerAngle(Matrix,
					     in->Tailer[i].Cont.EulerAngleMode,
					     in->Tailer[i].Cont.Rot1, 
					     in->Tailer[i].Cont.Rot2, 
					     in->Tailer[i].Cont.Rot3, 
					     MATRIX_3D_MODE_NOT_INITIALIZE);

   	  v.data[0] = 1.0;
      v.data[1] = 0.0;
      v.data[2] = 0.0;
      v.data[3] = 1.0;

      matrix3DMultiplyVector(&v, Matrix);
      
      eta1  = v.data[0];
      eta2  = v.data[1];
      eta3  = v.data[2];

      /*
	/eta1\    /  cos(theta)*cos(phi) \    /cos(theta) 0 -sin(theta)\/ cos(phi) sin(phi) 0 \ /1\
	|eta2|  = | -sin(phi)            | =  |  0        1    0       ||-sin(phi) cos(phi) 0 | |0|
	\eta3/    \  sin(theta)*cos(phi) /    \sin(theta) 0  cos(theta)/\   0        0      1 / \0/
      */

      if(fabs(eta1)<1e-3 && fabs(eta3)<1e-3) {
	angleset->theta->angle = -2*M_PI;
      } else if(fabs(eta1)<1e-3) {
	angleset->theta->angle = M_PI/2.0;
      } else if(eta1*eta3<0) {
	angleset->theta->angle = atan(eta3/eta1) + M_PI;
      } else {
	angleset->theta->angle = atan(eta3/eta1);
      }
	  
      if(out->HeaderN.y == (int)(angleset->theta->angle/angleset->theta->d+0.5)) {
	//angleset->theta->angle -= M_PI;
	angleset->theta->angle = 0;
      } else if(out->HeaderN.y < (int)(angleset->theta->angle/angleset->theta->d+0.5)) {
	DEBUGPRINT2("Something wrong for calculating theta in lmrcRadon2Dto3D:out->HeaderN.y=%d angleset->theta->angle = %g\n",out->HeaderN.y,angleset->theta->angle);
      }
	  
      angleset->phi->angle   = asin(-eta2);           /* -PI/2 < phi   < PI/2  */
      if((fabs(cos(angleset->theta->angle))< fabs(sin(angleset->theta->angle)) && eta3*sin(angleset->theta->angle)<0) 
       ||(fabs(cos(angleset->theta->angle))>=fabs(sin(angleset->theta->angle)) && eta1*cos(angleset->theta->angle)<0)) {
	angleset->phi->angle = M_PI-angleset->phi->angle;
      }

      angleset->phi->angle   = fmod(angleset->phi->angle+2*M_PI, 2*M_PI);
      if(out->HeaderN.z == (int)(angleset->phi->angle/angleset->phi->d+0.5)) {
	//angleset->phi->angle -= 2*M_PI;
	angleset->phi->angle = 0;
      } else if(out->HeaderN.z < (int)(angleset->phi->angle/angleset->phi->d+0.5)) {
	DEBUGPRINT2("Something wrong for calculating phi in lmrcRadon2Dto3D:out->HeaderN.z=%d angleset->phi->angle = %g\n",out->HeaderN.z,angleset->phi->angle);
      }
}

void
__AngleItemSet(mrcImage* out ,AngleSet* angleset ,lmrcRadon2Dto3DInfo* linfo )
{
	double dmax;

  	dmax = MAX(angleset->theta->d,angleset->phi->d);

	angleset->theta->flag = 0;
	angleset->phi->flag   = 0;

	if(angleset->theta->angle < -M_PI){

	  angleset->theta->PlusN  = out->HeaderN.y-1;
	  angleset->theta->MinusN = 0;
	  angleset->theta->TotalN = out->HeaderN.y;
	  
	  //angleset->phi->angle   = fabs(angleset->phi->angle);
	  angleset->phi->check   = fmod(angleset->phi->angle,angleset->phi->d);
	  
	  if(angleset->phi->check<0.000001){
	    angleset->phi->PlusN  = angleset->phi->MinusN = angleset->phi->angle/angleset->phi->d;
	    angleset->phi->TotalN = 1;
	  }else if(angleset->phi->check>angleset->phi->d-0.000001){
	    angleset->phi->PlusN  = angleset->phi->MinusN = angleset->phi->angle/angleset->phi->d+1;
	    angleset->phi->TotalN = 1;
	  } else{
	    angleset->phi->PlusN    = ceil((angleset->phi->angle+dmax*linfo->T)/angleset->phi->d)-1;
	    angleset->phi->MinusN   = ceil((angleset->phi->angle-dmax*linfo->T)/angleset->phi->d);
	    angleset->phi->TotalN   = angleset->phi->PlusN-angleset->phi->MinusN+1;
	    angleset->phi->flag     = 0; 
	    
	    if(angleset->phi->PlusN>out->HeaderN.z-1){
	      angleset->phi->PlusN  -= out->HeaderN.z;  
	      angleset->phi->TotalN  = out->HeaderN.z-angleset->phi->MinusN+angleset->phi->PlusN+1;
	      angleset->phi->flag    = 1;
	    } 
	    if(angleset->phi->MinusN<0){
	      angleset->phi->MinusN += out->HeaderN.z;
	      angleset->phi->TotalN  = out->HeaderN.z-angleset->phi->MinusN+angleset->phi->PlusN+1;
	      angleset->phi->flag    = 1;
	    }
	  }
	} else {

	  //angleset->theta->angle = fabs(angleset->theta->angle); 
	  //angleset->phi->angle   = fabs(angleset->phi->angle);   	 
	  angleset->theta->check = fmod(angleset->theta->angle,angleset->theta->d);
	  angleset->phi->check   = fmod(angleset->phi->angle,angleset->phi->d);

	  if(angleset->theta->check<0.000001){
	    angleset->theta->PlusN  = angleset->theta->MinusN = angleset->theta->angle/angleset->theta->d;
	    angleset->theta->TotalN = 1;
	  }else if(angleset->theta->check>angleset->theta->d-0.000001){
	      angleset->theta->PlusN = angleset->theta->MinusN = angleset->theta->angle/angleset->theta->d+1;
	      angleset->theta->TotalN = 1;
	  } else {
	    angleset->theta->PlusN  = ceil((angleset->theta->angle+dmax*linfo->T)/angleset->theta->d)-1;
	    angleset->theta->MinusN = ceil((angleset->theta->angle-dmax*linfo->T)/angleset->theta->d);
	    angleset->theta->TotalN = angleset->theta->PlusN-angleset->theta->MinusN+1;
	    angleset->theta->flag   = 0;	 
	    
	    if(angleset->theta->PlusN>out->HeaderN.y-1){
	      angleset->theta->PlusN  -= out->HeaderN.y;  
	      angleset->theta->TotalN  = out->HeaderN.y-angleset->theta->MinusN+angleset->theta->PlusN+1;
	      angleset->theta->flag    = 1;
	    } 
	    if(angleset->theta->MinusN<0){
	      angleset->theta->MinusN += out->HeaderN.y;
	      angleset->theta->TotalN  = out->HeaderN.y-angleset->theta->MinusN+angleset->theta->PlusN+1;
	      angleset->theta->flag    = 1;
	    }
	  }
	    
	  if(angleset->phi->check<0.000001){
	    angleset->phi->PlusN  = angleset->phi->MinusN = angleset->phi->angle/angleset->phi->d;
	    angleset->phi->TotalN = 1;
	  }else if(angleset->phi->check>angleset->phi->d-0.000001){
	    angleset->phi->PlusN  = angleset->phi->MinusN = angleset->phi->angle/angleset->phi->d+1;
	    angleset->phi->TotalN = 1;
	  } else{
	    angleset->phi->PlusN    = ceil((angleset->phi->angle+dmax*linfo->T)/angleset->phi->d)-1;
	    angleset->phi->MinusN   = ceil((angleset->phi->angle-dmax*linfo->T)/angleset->phi->d);
	    angleset->phi->TotalN   = angleset->phi->PlusN-angleset->phi->MinusN+1;
	    angleset->phi->flag     = 0; 
	    
	    if(angleset->phi->PlusN>out->HeaderN.z-1){
	      angleset->phi->PlusN  -= out->HeaderN.z;  
	      angleset->phi->TotalN  = out->HeaderN.z-angleset->phi->MinusN+angleset->phi->PlusN+1;
	      angleset->phi->flag    = 1;
	    } 
	    if(angleset->phi->MinusN<0){
	      angleset->phi->MinusN += out->HeaderN.z;
	      angleset->phi->TotalN  = out->HeaderN.z-angleset->phi->MinusN+angleset->phi->PlusN+1;
	      angleset->phi->flag    = 1;
	    }
	  }
	}  
}

void
__3DRadonCoordinateSet(mrcImage* out ,AngleSet* angleset)
{
	int l=0;

	if(angleset->theta->flag==1){
	  for(angleset->theta->n=angleset->theta->MinusN; angleset->theta->n<out->HeaderN.y; angleset->theta->n++){
	    angleset->theta->N[l] = angleset->theta->n;
	    l++;
	  }
	  for(angleset->theta->n=0; angleset->theta->n<angleset->theta->PlusN; angleset->theta->n++){
	    angleset->theta->N[angleset->theta->n+l] = angleset->theta->n;
	  }
	} else {
	  for(angleset->theta->n=angleset->theta->MinusN; angleset->theta->n<=angleset->theta->PlusN; angleset->theta->n++){
	    angleset->theta->N[angleset->theta->n-angleset->theta->MinusN] = angleset->theta->n;
	  }
	}
	
	l = 0;
	if(angleset->phi->flag==1){
	  for(angleset->phi->n=angleset->phi->MinusN; angleset->phi->n<out->HeaderN.z; angleset->phi->n++){
	    angleset->phi->N[l] = angleset->phi->n;
	    l++;
	  }
	  for(angleset->phi->n=0; angleset->phi->n<=angleset->phi->PlusN; angleset->phi->n++){
	    angleset->phi->N[angleset->phi->n+l] = angleset->phi->n;
	  }
	} else {
	  for(angleset->phi->n=angleset->phi->MinusN; angleset->phi->n<=angleset->phi->PlusN; angleset->phi->n++){
	    angleset->phi->N[angleset->phi->n-angleset->phi->MinusN] = angleset->phi->n;
	  } 
	}
}

void 
lmrcRadon2Dto3D(mrcImage* out, mrcImage* in, lmrcRadon2Dto3DInfo* linfo, long mode)
{

  mrcImageParaTypeInteger i,y2,x2;
  mrcImageParaTypeInteger num;
  mrcImageParaTypeReal    prjx, x3, y3, z3;
  double*                 WW;
  mrcImageParaTypeReal    g2x,g3x;
  mrcImage                tmp;
  mrcImage                sino; /* Sinogram */
  //mrcImage                number;
  double                  projdata;
  double                  dmax;
  AngleSet*               angleset;

	angleset        = (AngleSet*)memoryAllocate(sizeof(AngleSet),"angleset");
    angleset->theta = (Angleitem*)memoryAllocate(sizeof(Angleitem),"theta");	
    angleset->phi   = (Angleitem*)memoryAllocate(sizeof(Angleitem),"phi");
    angleset->delta = (Deltaitem*)memoryAllocate(sizeof(Deltaitem),"delta");

  __lmrcRadon2Dto3DImageSizeSet(out, in, linfo, mode);
  linfo->number.Header = out->Header;
  mrcInit(out, NULL);
  mrcInit(&linfo->number, NULL);

  num = in->numTailer;

  /*Determination of Image Center*/    
  g3x = (out->HeaderN.x - 1)/2;    
  g2x = (in->HeaderN.x  - 1)/2;

	angleset->delta->d =  in->HeaderLength.y*RADIAN;
	angleset->theta->d = out->HeaderLength.y*RADIAN;
	angleset->phi->d   = out->HeaderLength.z*RADIAN;

  	dmax = MAX(angleset->theta->d,angleset->phi->d);

 for(i=0; i<num; i++) {

	if(fmod(i,num/10)==0){
		DEBUGPRINT("*");
	}
    /* Projection Data Set */
    mrcImageSectionGet(&tmp, in, i, 1); 	

    /*Filtering*/
    sino=tmp;

    /*Interpolation*/
    for(y2=0; y2<sino.HeaderN.y; y2++){ 
    
		__AngleCalculation(in ,out ,i ,y2 ,angleset );
 
      /*Weight calculation*/      
      switch(linfo->mode){
      case mrc2Dto3DModeHigherOrderInterpolation: {

		__AngleItemSet(out ,angleset ,linfo);
	
	angleset->theta->N    = (double*)memoryAllocate(sizeof(double)*angleset->theta->TotalN,"angleset->theta->angle ");
	angleset->phi->N      = (double*)memoryAllocate(sizeof(double)*angleset->phi->TotalN, "angleset->phi->angle  ");

		__3DRadonCoordinateSet(out ,angleset);

		WW = __WeightCalculation(in ,angleset ,i ,linfo );

	break;
      }
      default: {
	break;
      }
      }

    for(x2=0; x2<sino.HeaderN.x; x2++){
		prjx = sino.HeaderLength.x*(x2-g2x);
		mrcPixelDataGet(&sino, x2, y2, 0.0, &projdata, mrcPixelRePart, linfo->InterpolationMode);
		x3 = (prjx+g3x*out->HeaderLength.x)/out->HeaderLength.x;
	
		switch(linfo->mode){
		case mrc2Dto3DModeNearestNeighborInterpolation:
	  		y3 = angleset->theta->angle/angleset->theta->d;
	  		z3 = angleset->phi->angle  /angleset->phi->d;
	  		if(angleset->theta->angle<-M_PI) {
	    		__lmrcImageRadon2Dto3DSinoToRadon3DNearest(out, &linfo->number, x3, y3, z3, projdata, 1);
	  		} else {
	    		__lmrcImageRadon2Dto3DSinoToRadon3DNearest(out, &linfo->number, x3, y3, z3, projdata, 0);
	  		}
	  	break;
		case mrc2Dto3DModeHigherOrderInterpolation:

			__lmrcImageRadon2Dto3DSinoToRadon3DHigherOrderInterpolation(out, &linfo->number, 
								      									x3, 
								      									angleset,
									  									projdata, WW, 0);
      	break;
		}
    }
	switch(linfo->mode){
	case mrc2Dto3DModeHigherOrderInterpolation:
      free(WW);
	  break;
    case mrc2Dto3DModeNearestNeighborInterpolation:
	  break;
	}
      free(angleset->phi->N);
      free(angleset->theta->N);
    }
  }
  DEBUGPRINT("\n");
  __lmrcRadon2Dto3DNormalization(out, linfo->number, linfo->mode);
	mrcFileWrite(&linfo->number, linfo->fnameW, "in main", 0);
  mrcStatDataSet(out,0);
}
