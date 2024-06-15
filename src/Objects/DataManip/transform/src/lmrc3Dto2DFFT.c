/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrc3Dto2DFFT ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrc3Dto2DFFT 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrc3Dto2DFFT ver%I%; Date:%D% %Z%";

#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include "./lmrc3Dto2D.h"


void
lmrc3Dto2DFFT(lmrc3Dto2DFFTInfoOut* Out, mrcImage* template, mrcImage* volume, lmrc3Dto2DFFTInfo* linfo, int mode){

    float x,y,z;
    int i=0;

    if(mode == 0){
        for(x = linfo->llinfo.Rot1Start; x < (linfo->llinfo.Rot1End ); x += linfo->llinfo.Rot1Delta){
        for(y = linfo->llinfo.Rot2Start; y < (linfo->llinfo.Rot2End ); y += linfo->llinfo.Rot2Delta){
        for(z = linfo->llinfo.Rot2Start; z < (linfo->llinfo.Rot3End ); z += linfo->llinfo.Rot3Delta){

            linfo->llinfo.llinfo.Rot1 = x;
            linfo->llinfo.llinfo.Rot2 = y;
            linfo->llinfo.llinfo.Rot3 = z;
        
           lmrcFFTCentralSectionGet(&Out[i].out, template, volume, &linfo->llinfo.llinfo, 0);
        
            Out[i].Rot[0]= x;
            Out[i].Rot[1]= y;
            Out[i].Rot[2]= z;

            i++;
        }
        }
        }
    }else{
        for(i=0;i<linfo->llinfo.RotSize;i++){
 //           if(Out[i].Prior != 0.0){
                linfo->llinfo.llinfo.Rot1 = Out[i].Rot[0];
                linfo->llinfo.llinfo.Rot2 = Out[i].Rot[1];
                linfo->llinfo.llinfo.Rot3 = Out[i].Rot[2];
                
                lmrcFFTCentralSectionGet(&Out[i].out, template, volume, &linfo->llinfo.llinfo, 0);
   //         }
        }
    }

}

void
lmrc3Dto2DFFTInfoWrite(FILE* fpt, char* filename, char* file3d, lmrc3Dto2DFFTInfoOut* Out, lmrc3Dto2DFFTInfo* linfo, int mode){
    int i;
    char fileNAME[256];

    linfo->llinfo.llinfo.EulerMode[4] = '\0';
    for(i=0; i< linfo->llinfo.RotSize; i++){
        sprintf(fileNAME, "%s-%05d.fft2d", filename,i);
        fprintf(fpt,"%s %4s %15.4f %15.4f %15.4f %s %d\n", fileNAME, linfo->llinfo.llinfo.EulerMode, Out[i].Rot[0]*DEGREE, Out[i].Rot[1]*DEGREE, Out[i].Rot[2]*DEGREE, file3d, i);
    }

}

