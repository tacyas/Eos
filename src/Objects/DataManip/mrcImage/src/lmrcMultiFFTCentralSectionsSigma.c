/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcMultiFFTCentralSectionsCompare ver %I%
#%Z% Created by
#%Z%
#%Z% Usage : lmrcMultiFFTCentralSectionsCompare
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcMultiFFTCentralSectionsSigma ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "lmrcFFTCentralSection.h"
#include "../inc/mrcImage.h"

void
lmrcMultiFFTCentralSectionsSigma(mrcImage* sigma,lmrcMultiFFTCentralSectionsCompareInfoOut* Out, mrcImage* in, lmrcMultiFFTCentralSectionsCompareInfo* linfo, int mode){

  mrcImageParaTypeReal x, y;
  double likelihood, prelikelihood;
  double rein, imin;
  double inOrigin, inlim;
  double revol, imvol;
  int i, j, flag;
  clock_t start, end;
  int sig_x, sig_y;
  double sigma1, sigma2, sigMax = 0, sigMin = 100;
  double sum2d, sum3d;
  int count;

  DEBUGPRINT("lmrcMultiFFTCentralSectionsCompareSigma start\n");

  linfo->Sigma = malloc(sizeof(double*)*(in->HeaderN.x));
  if(linfo->Sigma == NULL){
      DEBUGPRINT("malloc error\n");
  }

  sigma = 1;
  sig_x = 0;
  sum2d = 0.0;
  sum3d = 0.0;

  count = 0;
  for(x=0; x<=0; x++){
      for(y=0; y<=0; y++){
        mrcPixelDataGet(in, x, y, 0, &rein, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
        mrcPixelDataGet(in, x, y, 0, &imin, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
        mrcPixelDataGet(&Out[i].out, x, y, 0, &revol, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
        mrcPixelDataGet(&Out[i].out, x, y, 0, &imvol, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
        count++;
        sum2d += rein*rein + imin*imin;
        sum3d += revol*revol + imvol*imvol;
      }
    }
    sum2d = sqrt(sum2d/count);
    sum3d = sqrt(sum3d/count);

  for(x=0; x<=in->HeaderN.x/2.0; x++){
      sig_y=0;
      for(y=-in->HeaderN.y/2.0; y<in->HeaderN.y/2.0; y++){
        for(j=0; j<linfo->PriorSize; j++){
          flag = 0;
          for(i=0; i<linfo->OutSize; i++){
            if(Out[i].OriginNum == linfo->Prior[j].OriginNum){
              mrcPixelDataGet(in, x, y, 0, &rein, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
              mrcPixelDataGet(in, x, y, 0, &imin, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
              mrcPixelDataGet(&Out[i].out, x, y, 0, &revol, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
              mrcPixelDataGet(&Out[i].out, x, y, 0, &imvol, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);

              rein/=sum2d;
              imin/=sum3d;
              revol/=sum2d;
              imvol/=sum3d;

              sigma1 = ((rein - revol)*(rein - revol) + (imin - imvol)*(imin - imvol));
              sigma2 += Out[i].Prior*sigma1;
              flag = 1;
            }
          }
        }
        mrcPixelDataSet(sigma, x, y, 0, sigma2/2.0, mrcPixelSigmaPart);
        linfo->Sigma[sig_x][sig_y]=sigma2/2.0;
        sig_y++;
      }
      sig_x++;
    }

    //mrcPixelDataSet(Sigma, x, y, 0, sigma2/2.0, mrcPixelSigmaPart);

    DEBUGPRINT("lmrcMultiFFTCentralSectionsCompareSigma end\n");
  }
