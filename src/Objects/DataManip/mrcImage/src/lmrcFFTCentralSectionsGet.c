/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcFFTCentralSectionsGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcFFTCentralSectionsGet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcFFTCentralSectionsGet ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./lmrcFFTCentralSection.h"
 #include "../inc/mrcImage.h"

void
lmrcFFTCentralSectionsGet(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, mrcImage* template, mrcImage* volume, lmrcMultiFFTCentralSectionsCompareInfo* linfo, int mode, int nummode){

    int i=0;
    float x, y, z;
    
    if(nummode == 0){    
        for(x = linfo->llinfo.Rot1Start; x < (linfo->llinfo.Rot1End - linfo->llinfo.Rot1Delta); x += linfo->llinfo.Rot1Delta){
        for(y = linfo->llinfo.Rot2Start; y < (linfo->llinfo.Rot2End - linfo->llinfo.Rot2Delta); y += linfo->llinfo.Rot2Delta){
        for(z = linfo->llinfo.Rot3Start; z < (linfo->llinfo.Rot3End - linfo->llinfo.Rot3Delta); z += linfo->llinfo.Rot3Delta){
        
            linfo->llinfo.llinfo.Rot1 = x;
            linfo->llinfo.llinfo.Rot2 = y;
            linfo->llinfo.llinfo.Rot3 = z;
            
            lmrcFFTCentralSectionGet(&Out[i].out, template, volume, &linfo->llinfo.llinfo, mode);
            
            Out[i].Rot[0] = x;
            Out[i].Rot[1] = y;
            Out[i].Rot[2] = z;
        
            i++;
        }
        }
        }
    }else{
        for(i=0; i<linfo->llinfo.RotSize; i++){
            if(Out[i].Prior == 0){
            }else{
            linfo->llinfo.llinfo.Rot1 = Out[i].Rot[0];
            linfo->llinfo.llinfo.Rot2 = Out[i].Rot[1];
            linfo->llinfo.llinfo.Rot3 = Out[i].Rot[2];

            lmrcFFTCentralSectionGet(&Out[i].out, template, volume, &linfo->llinfo.llinfo, mode);
            }
        }
    }
}
