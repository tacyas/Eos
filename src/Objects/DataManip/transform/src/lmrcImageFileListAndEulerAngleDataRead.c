/*
# lmrcImageFileListAndEulerAngleDataRead : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFileListAndEulerAngleDataRead 
# Attention
#   $Loccker$
#  	$State$ 
#
*/

#define DEBUG
#include "lmrcImageFileListAndEulerAngleDataRead.h"

void
lmrcImageFileListAndEulerAngleDataRead(mrcImage* out, char** filename, int number, FILE* fptInfo, int mode)
{
     long i;
     mrcImage* in;
     mrcImageParaTypeInteger Nx, Ny;
     mrcImageParaTypeReal LengthX, LengthY;
     mrcImageParaTypeReal srcx, srcy;
     mrcImageParaTypeReal dstx, dsty, dstz;
     char s[1024];
     double data;

     in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*number, "in lmrcImageFileListAndEulerAngleDataRead");
     Nx = 0;
     Ny = 0;
     LengthX = 1e6;
     LengthY = 1e6;

     for(i=0; i<number; i++) {

	     mrcFileRead(&(in[i]), filename[i], "in lmrcImageFileListAndEulerAngleDataRead", 0);
         if(Nx < in[i].HeaderN.x) {
             Nx = in[i].HeaderN.x;
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
         mrcPixelDataGet(&(in[(int)dstz]), srcx, srcy,  0.0, &data, mrcPixelRePart, mrcPixelHowLinear);
         mrcPixelDataSet(out,              dstx, dsty, dstz,  data, mrcPixelRePart);
     }
     }
     }

	out->numTailer = number;
    out->Tailer = (mrcImageTailer*)memoryAllocate(sizeof(mrcImageTailer)*number, "in lmrcImageFileListAndEulerAngleDataRead");
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
        mrcImageFree(&(in[i]), "in lmrcImageFileListAndEulerAngleDataRead");
    }
    free(in);
}																
