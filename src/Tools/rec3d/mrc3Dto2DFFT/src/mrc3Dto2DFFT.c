/*
# mrc3Dto2DFFT : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrc3Dto2DFFT
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
#include "lmrc3Dto2D.h"
//#include "Class.h"

/*
Example:
typedef struct lmrc3Dto2DFFTInfo {
	float a;
	int   b;
} lmrc3Dto2DFFTInfo;

typedef enum lmrc3Dto2DFFTMode {
	a=0,
	b=1
} lmrc3Dto2DFFTMode;
*/

int
main(int argc, char* argv[]) 
{
    mrc3Dto2DFFTInfo info;
    lmrc3Dto2DFFTInfo linfo;
    mrcImage volume;
    mrcImage template;
    char filename[256], fname[256];
    char* pch;
    char* temp;
    int i,ret;
    clock_t start, end;
    char EAMode[5];
    double Prior;

    start = clock();

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

    DEBUGPRINT("Program Start\n");
    
    mrcFileRead(&template, info.Template, "in main", 0);
    mrcFileRead(&volume, info.In, "in main", 0);
    
    strncpy(linfo.llinfo.llinfo.EulerMode, info.EulerMode, 4); linfo.llinfo.llinfo.EulerMode[4] = 0;
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
   
    linfo.Out = (lmrc3Dto2DFFTInfoOut*)malloc(sizeof(lmrc3Dto2DFFTInfoOut)*linfo.llinfo.RotSize);
    if(linfo.Out == NULL){
        DEBUGPRINT("malloc error\n");
    }
/*
    i=0;
    if( info.InPri != NULL){
        while((ret = fscanf(info.fptInPri, "%s %s %lf %lf %lf %lf",filename, EAMode, &linfo.Out[i].Rot[0], &linfo.Out[i].Rot[1], &linfo.Out[i].Rot[2], &Prior)) != EOF){
            linfo.Out[i].Rot[0] = linfo.Out[i].Rot[0]/DEGREE;
            linfo.Out[i].Rot[1] = linfo.Out[i].Rot[1]/DEGREE;
            linfo.Out[i].Rot[2] = linfo.Out[i].Rot[2]/DEGREE;
            i++;
        }
        linfo.llinfo.RotSize = i;
    }
*/
   // linfo.Out = (lmrc3Dto2DFFTInfoOut*)malloc(sizeof(lmrc3Dto2DFFTInfoOut)*linfo.llinfo.RotSize);
   // if(linfo.Out == NULL){
   //     DEBUGPRINT("malloc error\n");
   // }

/*
    if(info.InPri == NULL){
        lmrc3Dto2DFFT(linfo.Out, &template, &volume, &linfo, 0);//first 
    }else{
        DEBUGPRINT("mode 1\n");

        lmrc3Dto2DFFT(linfo.Out, &template, &volume, &linfo, 1);  
    }
*/
 
    lmrc3Dto2DFFT(linfo.Out, &template, &volume, &linfo, 0);
    pch = NULL;
    DEBUGPRINT("1\n");
    for(temp = info.Out; (temp = strchr(temp, '.')) != NULL; temp ++) pch = temp;
    if(pch != NULL) *pch = '\0';
    for(i=0; i< linfo.llinfo.RotSize; i++){
        sprintf(filename, "%s-%05d.fft2d",info.Out, i);
       	mrcFileWrite(&linfo.Out[i].out, filename, "in main", 0);
    }
    DEBUGPRINT("2\n");
    lmrc3Dto2DFFTInfoWrite(info.fptOut, info.Out, info.In, linfo.Out, &linfo, info.mode);
    free(linfo.Out);
    end = clock();
    DEBUGPRINT1("time: %f\n",(double)(end - start)/CLOCKS_PER_SEC);

    exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
