/*
# mrcMultiFFTCentralSectionsCompare : $Revision$
# $Date$
# Created by $Author$
# Usage : mrcMultiFFTCentralSectionsCompare
# Attention
#   $Loccker$
#  	$State$
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "lmrcFFTCentralSection.h"

/*
Example:
typedef struct lmrcMultiFFTCentralSectionsCompareInfo {
float a;
int   b;
} lmrcMultiFFTCentralSectionsCompareInfo;

typedef enum lmrcMultiFFTCentralSectionsCompareMode {
} lmrcMultiFFTCentralSectionsCompareMode;
*/

int
main(int argc, char* argv[])
{
    mrcMultiFFTCentralSectionsCompareInfo info;
    lmrcMultiFFTCentralSectionsCompareInfo linfo;
  //  lmrcMultiFFTCentralSectionsCompareInfoOut* Out;
    mrcImage in;
    mrcImage volume;
    //mrcImage sigma;
    int i,buf;
    clock_t start,end;
    char filename[256], fname[256], EAMode[5];
    double rot[3];
    char Buf[256];
    FILE* fpfp;

    start = clock();

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

    DEBUGPRINT("Program Start\n");
    mrcFileRead(&in, info.In2D, "in main", 0);

    strncpy(linfo.EulerMode, info.EulerMode, 4);
    strncpy(linfo.llinfo.llinfo.EulerMode, info.EulerMode, 4);
    linfo.llinfo.llinfo.TransX = info.TransX;
    linfo.llinfo.llinfo.TransY = info.TransY;
    linfo.llinfo.llinfo.InterpMode = info.InterpMode;

//Rot1
    linfo.llinfo.Rot1Start = info.Rot1Start*RADIAN;
    linfo.llinfo.Rot1End = info.Rot1End*RADIAN;
    linfo.llinfo.Rot1Delta = info.Rot1Delta*RADIAN;
    linfo.llinfo.nRot1 = MAX(1,(int)(fabs((linfo.llinfo.Rot1End - linfo.llinfo.Rot1Start)/linfo.llinfo.Rot1Delta)+0.5));

//Rot2
    linfo.llinfo.Rot2Start = info.Rot2Start*RADIAN;
    linfo.llinfo.Rot2End = info.Rot2End*RADIAN;
    linfo.llinfo.Rot2Delta = info.Rot2Delta*RADIAN;
    linfo.llinfo.nRot2 = MAX(1,(int)(fabs((linfo.llinfo.Rot2End - linfo.llinfo.Rot2Start)/linfo.llinfo.Rot2Delta)+0.5));

//Rot3
    linfo.llinfo.Rot3Start = info.Rot3Start*RADIAN;
    linfo.llinfo.Rot3End = info.Rot3End*RADIAN;
    linfo.llinfo.Rot3Delta = info.Rot3Delta*RADIAN;
    linfo.llinfo.nRot3 = MAX(1,(int)(fabs((linfo.llinfo.Rot3End - linfo.llinfo.Rot3Start)/linfo.llinfo.Rot3Delta)+0.5));

    linfo.llinfo.RotSize = ((linfo.llinfo.nRot1))*((linfo.llinfo.nRot2))*((linfo.llinfo.nRot3));
    DEBUGPRINT1("RotSize: %d\n",linfo.llinfo.RotSize);

    linfo.OutSize = 0;
    linfo.PriorSize = 0;

    while(fgets(Buf, 256, info.fptIn3D) != NULL){
        linfo.OutSize ++;
    }
    if(info.flagPrior) {
        while(fgets(Buf, 256, info.fptPrior) != NULL){
            linfo.PriorSize ++;
        }
    } else {
        linfo.PriorSize = linfo.OutSize;
    }
    DEBUGPRINT1("OutSize: %d\n",linfo.OutSize);
    DEBUGPRINT1("PriotSize: %d\n",linfo.PriorSize);

    linfo.Out = (lmrcMultiFFTCentralSectionsCompareInfoOut*)malloc(sizeof(lmrcMultiFFTCentralSectionsCompareInfoOut)*linfo.OutSize);
    if(linfo.Out == NULL){
        DEBUGPRINT("malloc error\n");
	return -1;
    }

    rewind(info.fptIn3D);
    if(info.flagPrior){
      rewind(info.fptPrior);
    }

    linfo.Prior = (lmrcMultiFFTCentralSectionsCompareInfoOut*)malloc(sizeof(lmrcMultiFFTCentralSectionsCompareInfoOut)*linfo.PriorSize);
    if(linfo.Prior==NULL) {
        DEBUGPRINT("malloc error\n");
	return -1;
    }

    i=0;
    while(fscanf(info.fptIn3D, "%s %s %lf %lf %lf %s %d", filename, linfo.Out[i].EulerMode, &linfo.Out[i].Rot[0], &linfo.Out[i].Rot[1], &linfo.Out[i].Rot[2], linfo.Out[i].volume, &linfo.Out[i].OriginNum) != EOF){
        sprintf(fname, "%s%s", info.volPath, filename);
        mrcFileRead(&(linfo.Out[i].out), fname, "in main", 0);
        //mrcFileRead(&(linfo.Out[i].volume), file3d, "in main", 0);
        linfo.Out[i].Rot[0] = linfo.Out[i].Rot[0]*RADIAN;
        linfo.Out[i].Rot[1] = linfo.Out[i].Rot[1]*RADIAN;
        linfo.Out[i].Rot[2] = linfo.Out[i].Rot[2]*RADIAN;
        if(!info.flagPrior){
            linfo.Prior[i].OriginNum = linfo.Out[i].OriginNum;
        }
        i++;
    }

	// 
    i=0;
    if(!info.flagPrior){
       lmrcMultiFFTCentralSectionsCompareInfoProbSet(&linfo ,0);
    }else{
        DEBUGPRINT("Prior In\n");
        while((buf = fscanf(info.fptPrior, "%s %s %lf %lf %lf %s %d %lf",filename, linfo.Prior[i].EulerMode, &linfo.Prior[i].Rot[0], &linfo.Prior[i].Rot[1], &linfo.Prior[i].Rot[2], linfo.Prior[i].volume, &linfo.Prior[i].OriginNum, &linfo.Prior[i].Prior)) != EOF){
            sprintf(fname, "%s%s", info.PriPath, filename);
           // mrcFileRead(&(linfo.Prior[i].out), fname, "in main", 0);
           // mrcFileRead(&(linfo.Prior[i].volume), file3d, "in main", 0);
            linfo.Prior[i].Rot[0] = linfo.Prior[i].Rot[0]/DEGREE;
            linfo.Prior[i].Rot[1] = linfo.Prior[i].Rot[1]/DEGREE;
            linfo.Prior[i].Rot[2] = linfo.Prior[i].Rot[2]/DEGREE;
            i++;
        }
    }

    DEBUGPRINT1("Prior: %f\n",linfo.Prior[0].Prior);
  //  lmrcMultiFFTCentralSectionsSigma(&sigma, &Out, &in, &linfo, info.Lcalcmode);
    DEBUGPRINT("Compare start:\n");
    lmrcMultiFFTCentralSectionsCompare(linfo.Out, &in, &volume, &linfo, info.Lcalcmode, 0);
    DEBUGPRINT("Compare end:\n");

    lmrcMultiFFTCentralSectionsCompareInfoUpdate(linfo.Out, &linfo); //Bayes
    lmrcMultiFFTCentralSectionsCompareNormalization(linfo.Out, &linfo, info.Lcalcmode);
    lmrcMultiFFTCentralSectionsCompareInfoSort(linfo.Out, 0, linfo.OutSize-1);
    lmrcMultiFFTCentralSectionsCompareInfoLimit(linfo.Out, &linfo, info.Lmode1, info.Lmode2);
    lmrcMultiFFTCentralSectionsCompareNormalization(linfo.Out, &linfo, info.Lcalcmode);

    DEBUGPRINT("InfoWrite\n");
    lmrcMultiFFTCentralSectionsCompareInfoWrite(info.fptOut1, info.In2D, linfo.Out, &linfo, info.Lmode1, info.Lmode2);
    lmrcMultiFFTCentralSectionsCompareInfoWriteLikelihood(info.fptOutLikelihood, info.In2D, linfo.Out, &linfo, info.Lmode1, info.Lmode2);
    lmrcMultiFFTCentralSectionsCompareInfoVariation(linfo.Out, &linfo);
 //   lmrcMultiFFTCentralSectionsCompareInfoProbSet(linfo.Out, &linfo ,1);

    DEBUGPRINT1("Prior: %f\n",linfo.Out[0].Prob);
    free(linfo.Out);
    free(linfo.Prior);

    end = clock();
    DEBUGPRINT1("time %f\n", (double)(end-start)/CLOCKS_PER_SEC);
    exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
    fprintf(stderr, "----- Additional Usage -----\n");
}
