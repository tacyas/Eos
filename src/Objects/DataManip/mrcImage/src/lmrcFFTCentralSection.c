/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcFFTCentralSection ver %I%
#%Z% Created by
#%Z%
#%Z% Usage : lmrcFFTCentralSection
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcFFTCentralSection ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"

#include "Memory.h"
#include "./lmrcFFTCentralSection.h"
void
lmrcImageFFTRhoFilter(mrcImage* volFT, mrcImage* count, lmrcFFTCentralSectionInfo* linfo ,int mode)
 {
   mrcImageParaTypeReal X3d, Y3d, Z3d;
   double re3d, im3d, sum;

   for(Z3d = (-volFT->HeaderN.z/2.0)+0.5; Z3d < (volFT->HeaderN.z/2.0)-0.5; Z3d++){
   for(Y3d = (-volFT->HeaderN.y/2.0)+0.5; Y3d < (volFT->HeaderN.y/2.0)-0.5; Y3d++){
   for(X3d = 0; X3d < (volFT->HeaderN.x/2.0)-0.5; X3d++){
   mrcPixelDataGet(volFT, X3d, Y3d, Z3d, &re3d, mrcPixelRePart, linfo->InterpMode);
   mrcPixelDataGet(volFT, X3d, Y3d, Z3d, &im3d, mrcPixelImPart, linfo->InterpMode);
   mrcPixelDataGet(count, X3d, Y3d, Z3d, &sum, mrcPixelRePart, linfo->InterpMode);
   if(0 < sum){
     re3d /= sum;
     im3d /= sum;
   } else {
     re3d = 0;
     im3d = 0;
   }
   mrcPixelDataSet(volFT, X3d, Y3d, Z3d, re3d, mrcPixelRePart);
   mrcPixelDataSet(volFT, X3d, Y3d, Z3d, im3d, mrcPixelImPart);
   }
   }
   }
 }


void
lmrcImageFFTCentralSectionPut(mrcImage* volFT, mrcImage* count, mrcImage* template3D, mrcImage* in, lmrcFFTCentralSectionInfo* linfo, int* c, int mode)
{
  mrcImageParaTypeReal X2d, Y2d, Z2d;
  mrcImageParaTypeReal X3d, Y3d, Z3d;
  int i, n, k0;
  Matrix3D mat;
  double re3d, im3d;
  double re3d0=0, im3d0=0, counter=0;
  double re2d, im2d;
  double re2d0, im2d0;
  double phaseShift;
  //mrcImage* volFT;
  double w;

  DEBUGPRINT("SectionPut Start\n");

  if(linfo->flagWeight == 1) {
	w = linfo->weight;
  } else {
	w = 1;
  }

  if(c==0){
    volFT->Header = template3D->Header;
    count->Header = template3D->Header;
    mrcInit(volFT, NULL);
    mrcInit(count, NULL);
  }
  c++;
  lmrcImageFFTCenterChange(volFT, 0);

  matrix3DRotationAntiSetFollowingEulerAngle(mat, linfo->EulerMode, linfo->Rot1, linfo->Rot2, linfo->Rot3, MATRIX_3D_MODE_INITIALIZE);

  for(Y2d = -in->HeaderN.y/2.0; Y2d < in->HeaderN.y/2.0; Y2d++) {
  for(X2d = -in->HeaderN.y/2.0; X2d < in->HeaderN.x/2.0; X2d++) {
      X3d = mat[0][0]*X2d + mat[1][0]*Y2d; // + mat[2][0]*Z2d(0);
      Y3d = mat[0][1]*X2d + mat[1][1]*Y2d; // + mat[2][1]*Z2d(0);
      Z3d = mat[0][2]*X2d + mat[1][2]*Y2d; // + mat[2][2]*Z2d(0);

      if((-volFT->HeaderN.x/2)+0.5 < X3d && X3d < (volFT->HeaderN.x/2)-0.5
       &&(-volFT->HeaderN.y/2)+0.5 < Y3d && Y3d < (volFT->HeaderN.y/2)-0.5
	     &&(-volFT->HeaderN.z/2)+0.5 < Z3d && Z3d < (volFT->HeaderN.z/2)-0.5 ) {
		mrcPixelDataGet(volFT, X3d, Y3d, Z3d, &re3d, mrcPixelRePart, linfo->InterpMode);
		mrcPixelDataGet(volFT, X3d, Y3d, Z3d, &im3d, mrcPixelImPart, linfo->InterpMode);
      } else {
		re3d = 0;
		im3d = 0;
      }
      phaseShift = 2*M_PI*(-linfo->TransX*X2d/in->HeaderN.x - linfo->TransY*Y2d/in->HeaderN.y);

      re2d = re3d*cos(phaseShift) - im3d*sin(phaseShift);
      im2d = re3d*sin(phaseShift) + im3d*cos(phaseShift);

	mrcPixelDataGet(in, X2d, Y2d, 0, &re2d0, mrcPixelRePart, linfo->InterpMode);
      mrcPixelDataGet(in, X2d, Y2d, 0, &im2d0, mrcPixelImPart, linfo->InterpMode);

      //re3d = re2d+re2d0*probability;
      //im3d = im2d+im2d0*probability;
      re3d = re2d+re2d0*w;
      im3d = im2d+im2d0*w;

      re3d0 = re3d*cos(-phaseShift) - im3d*sin(-phaseShift);
      im3d0 = re3d*sin(-phaseShift) - im3d*cos(-phaseShift);

      if((-volFT->HeaderN.x/2)+1 < X3d && X3d < (volFT->HeaderN.x/2)-1
       &&(-volFT->HeaderN.y/2)+1 < Y3d && Y3d < (volFT->HeaderN.y/2)-1
	     &&(-volFT->HeaderN.z/2)+1 < Z3d && Z3d < (volFT->HeaderN.z/2)-1) {

         mrcPixelDataSet(volFT, X3d, Y3d, Z3d, re3d0, mrcPixelRePart);
       	 mrcPixelDataSet(volFT, X3d, Y3d, Z3d, im3d0, mrcPixelImPart);
      }

      if((-volFT->HeaderN.x/2)+1 < X3d && X3d < (volFT->HeaderN.x/2)-1
       &&(-volFT->HeaderN.y/2)+1 < Y3d && Y3d < (volFT->HeaderN.y/2)-1
 	     &&(-volFT->HeaderN.z/2)+1 < Z3d && Z3d < (volFT->HeaderN.z/2)-1) {

       mrcPixelDataGet(count, X3d, Y3d, Z3d, &counter, mrcPixelRePart, linfo->InterpMode);
       //mrcPixelDataSet(count, X3d, Y3d, Z3d, counter+probability, mrcPixelRePart);
       mrcPixelDataSet(count, X3d, Y3d, Z3d, counter+w, mrcPixelRePart);
     }
  }
  } 

  lmrcImageFFTCenterChange(volFT, 0);


  if(!IsFT(volFT, "lmrcFFTCentralSectionGet", 0)) {
    mrcImageFree(volFT, 0);
    memoryFree(volFT);
  }
}

void 
lmrcFFTCentralSectionGet(mrcImage* out, mrcImage* template, mrcImage* volume, lmrcFFTCentralSectionInfo* linfo, int mode)
{
         mrcImageParaTypeReal X2d, Y2d, Z2d;
         mrcImageParaTypeReal X3d, Y3d, Z3d;
         int i, n, k0;
         Matrix3D mat;
         double re3d, im3d;
         double re2d, im2d;
         double phaseShift;
         mrcImage* volFT;
         double weight;
 
         if(IsFT(volume, "lmrcFFTCentralSectionGet", 0)) {
                 volFT = volume;
         } else {
                 volFT = memoryAllocate(sizeof(mrcImage), "in lmrcFFTCentralSectionGet");
                 lmrcImageFFT(volFT, volume, 0);
         }
 
         out->Header = template->Header;
         mrcInit(out, NULL);
 
         weight = 1.0/sqrt(volFT->HeaderN.x*volFT->HeaderN.y*volFT->HeaderN.z)*sqrt(out->HeaderN.x*out->HeaderN.y);
         
         lmrcImageFFTCenterChange(volFT, 0);
 
         matrix3DRotationAntiSetFollowingEulerAngle(mat, linfo->EulerMode, linfo->Rot1, linfo->Rot2, linfo->Rot3, MATRIX_3D_MODE_INITIALIZE);    
 
         for(Y2d = -out->HeaderN.y/2.0; Y2d <  out->HeaderN.y/2.0; Y2d++) { 
         for(X2d = 0;                   X2d <= out->HeaderN.x/2.0; X2d++) { 
                 X3d = mat[0][0]*X2d + mat[1][0]*Y2d; // + mat[2][0]*Z2d(0);
                 Y3d = mat[0][1]*X2d + mat[1][1]*Y2d; // + mat[2][1]*Z2d(0); 
                 Z3d = mat[0][2]*X2d + mat[1][2]*Y2d; // + mat[2][2]*Z2d(0);
 
                 if(-volFT->HeaderN.x/2 < X3d && X3d < volFT->HeaderN.x/2 
                  &&-volFT->HeaderN.y/2 < Y3d && Y3d < volFT->HeaderN.y/2 
                  &&-volFT->HeaderN.z/2 < Z3d && Z3d < volFT->HeaderN.z/2) {
                         mrcPixelDataGet(volFT, X3d, Y3d, Z3d, &re3d, mrcPixelRePart, linfo->InterpMode);
                         mrcPixelDataGet(volFT, X3d, Y3d, Z3d, &im3d, mrcPixelImPart, linfo->InterpMode);
                 } else {
                         re3d = 0;
                         im3d = 0;
                 }
                 phaseShift = 2*M_PI*(-linfo->TransX*X2d/out->HeaderN.x - linfo->TransY*Y2d/out->HeaderN.y);                     
 
                 re2d = re3d*cos(phaseShift) - im3d*sin(phaseShift);
                 im2d = re3d*sin(phaseShift) + im3d*cos(phaseShift);
         
                 DEBUGPRINT5("coord: %f %f <- %f %f %f\n", X2d, Y2d, X3d, Y3d, Z3d); 
                 DEBUGPRINT4("data:  %f %f <- %f %f \n", re2d, im2d, re3d, im3d); 
                 DEBUGPRINT5("3d: %f %f at %f %f %f\n", re3d, im3d, X3d, Y3d, Z3d);
                 DEBUGPRINT4("2d: %f %f at %f %f \n", re2d, im2d, X2d, Y2d);
                 mrcPixelDataSet(out, X2d, Y2d, 0, re2d*weight, mrcPixelRePart);
                 mrcPixelDataSet(out, X2d, Y2d, 0, im2d*weight, mrcPixelImPart);
         }
         }
 
         lmrcImageFFTCenterChange(volFT, 0);     
         lmrcImageFFTCenterChange(out, 0);       
 
         if(!IsFT(volume, "lmrcFFTCentralSectionGet", 0)) {
                 mrcImageFree(volFT, 0);
                 memoryFree(volFT);
         }
 }
