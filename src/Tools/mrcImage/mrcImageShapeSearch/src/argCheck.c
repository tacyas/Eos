#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../inc/config.h"
#include "genUtil.h"
#include "eosString.h"
#include "File.h"
#include "Memory.h"


void
argCheck(mrcImageShapeSearchInfo* info, int argc, char* argv[])
{
    long i;
    char s[1024];
    FILE* fpt;
    
    if(NULL==(fpt=fopen(".EosLog", "a+"))) { 
        
    } else {
        for(i=0; i<argc; i++) {
            fprintf(fpt, "%s ", argv[i]);
        }
        fprintf(fpt, "\n");
        fclose(fpt);
    }
    for(i=1; i<argc; i++) {
        if(OPTION_FLAG==argv[i][OPTION_FLAG_POS]) {
            SSWITCH(argv[i]+OPTION_POS)
                SCASE("i") {
                    if(i+1<argc) {
                        info->In = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o") {
                    if(i+1<argc) {
                        info->Out = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Shape") {
                    if(i+1<argc) {
                        info->Shape = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagShape++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("n") {
                    if(i+1<argc) {
                        info->nCube = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnCube++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Refine") {
                    if(i+0<argc) {
                        info->Refine++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("r") {
                    if(i+3<argc) {
                        info->minR = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminR++;
                        info->maxR = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxR++;
                        info->delR = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelR++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("l") {
                    if(i+3<argc) {
                        info->minL = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminL++;
                        info->maxL = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxL++;
                        info->delL = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelL++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Phi") {
                    if(i+3<argc) {
                        info->minPhi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminPhi++;
                        info->maxPhi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxPhi++;
                        info->delPhi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelPhi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Theta") {
                    if(i+3<argc) {
                        info->minTheta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminTheta++;
                        info->maxTheta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxTheta++;
                        info->delTheta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelTheta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Psi") {
                    if(i+3<argc) {
                        info->minPsi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminPsi++;
                        info->maxPsi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxPsi++;
                        info->delPsi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelPsi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("thres") {
                    if(i+1<argc) {
                        info->thresZscore = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagthresZscore++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("interp") {
                    if(i+1<argc) {
                        info->interpMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flaginterpMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("OVMode") {
                    if(i+1<argc) {
                        info->OVMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagOVMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("OVBILD") {
                    if(i+1<argc) {
                        info->OutVectorBILD = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutVectorBILD++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("OV") {
                    if(i+1<argc) {
                        info->OutVector = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutVector++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("arrow") {
                    if(i+3<argc) {
                        info->ArrowR1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagArrowR1++;
                        info->ArrowR2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagArrowR2++;
                        info->ArrowRho = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagArrowRho++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("zoom") {
                    if(i+1<argc) {
                        info->ZoomVector = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagZoomVector++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("arrowColorDisk") {
                    if(i+3<argc) {
                        info->ArrowColorDisk0 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagArrowColorDisk0++;
                        info->ArrowColorDisk1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagArrowColorDisk1++;
                        info->ArrowColorDisk2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagArrowColorDisk2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("arrowColorSylinder") {
                    if(i+3<argc) {
                        info->ArrowColorSylinder0 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagArrowColorSylinder0++;
                        info->ArrowColorSylinder1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagArrowColorSylinder1++;
                        info->ArrowColorSylinder2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagArrowColorSylinder2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("c") {
                    if(i+1<argc) {
                        info->configFile = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagconfigFile++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("m") {
                    if(i+1<argc) {
                        info->mode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("h") {
                    usage(argv[0]);
                    exit(EXIT_SUCCESS);
                    break;
                }
                SCASE("html") {
                    htmlBeforeUsage(argv[0]);
                    usage(argv[0]);
                    htmlAfterUsage(argv[0]);
                    exit(EXIT_SUCCESS);
                    break;
                }
                SDEFAULT {
                    fprintf(stderr, "Not Supported Options: :%s\n", argv[i]);
                    usage(argv[0]);
                    exit(EXIT_FAILURE);
                    break;
                }
            SSWITCHEND;
        } 
    } 
} 
