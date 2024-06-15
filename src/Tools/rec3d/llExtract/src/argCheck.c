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
argCheck(llExtractInfo* info, int argc, char* argv[])
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
                SCASE("t") {
                    if(i+1<argc) {
                        info->Title = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagTitle++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("s") {
                    if(i+2<argc) {
                        info->xStep = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxStep++;
                        info->yStep = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagyStep++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("M") {
                    if(i+2<argc) {
                        info->MaxX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMaxX++;
                        info->MaxY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMaxY++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
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
                SCASE("1") {
                    if(i+1<argc) {
                        info->Nea = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagNea++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("2") {
                    if(i+1<argc) {
                        info->Far = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagFar++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("R") {
                    if(i+1<argc) {
                        info->RotationAngle = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRotationAngle++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("O") {
                    if(i+1<argc) {
                        info->Omega = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagOmega++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("S") {
                    if(i+1<argc) {
                        info->Shear = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagShear++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("I") {
                    if(i+1<argc) {
                        info->ievery = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagievery++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("axl") {
                    if(i+1<argc) {
                        info->axl = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagaxl++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ayl") {
                    if(i+1<argc) {
                        info->ayl = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagayl++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("x") {
                    if(i+1<argc) {
                        info->xShift = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxShift++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("l") {
                    if(i+1<argc) {
                        info->llMax = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagllMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("d") {
                    if(i+1<argc) {
                        info->delRInv = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelRInv++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("f") {
                    if(i+0<argc) {
                        info->flagOutputInfo++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("L") {
                    if(i+8<argc) {
                        {
                        int j, nv, check, count, nitem;
                        nv    = argc - i - 1;
                        nitem = 8 ;
                        check = nv%nitem ;
                        count = nv/nitem ;
                        if(0!=check) { fprintf(stderr, "Variable Number is strange. The number must be %d-times. nv: %d i\n", nitem, nv); usage(argv[0]); exit(EXIT_FAILURE);} 
                        info->n = (long*)memoryAllocate(sizeof(long)*count, "in argCheck");
                        info->l = (long*)memoryAllocate(sizeof(long)*count, "in argCheck");
                        info->Y = (float*)memoryAllocate(sizeof(float)*count, "in argCheck");
                        info->leftMin = (float*)memoryAllocate(sizeof(float)*count, "in argCheck");
                        info->leftMax = (float*)memoryAllocate(sizeof(float)*count, "in argCheck");
                        info->rightMin = (float*)memoryAllocate(sizeof(float)*count, "in argCheck");
                        info->rightMax = (float*)memoryAllocate(sizeof(float)*count, "in argCheck");
                        info->weight = (float*)memoryAllocate(sizeof(float)*count, "in argCheck");
                        for(j=0; j<count; j++) {
                            info->n[j] = stringGetNthIntegerData(argv[i+j*nitem+1], 1, " ,");
                        }
                        i++;
                        info->flagn=count;
                        for(j=0; j<count; j++) {
                            info->l[j] = stringGetNthIntegerData(argv[i+j*nitem+1], 1, " ,");
                        }
                        i++;
                        info->flagl=count;
                        for(j=0; j<count; j++) {
                            info->Y[j] = stringGetNthRealData(argv[i+j*nitem+1], 1, " ,");
                        }
                        i++;
                        info->flagY=count;
                        for(j=0; j<count; j++) {
                            info->leftMin[j] = stringGetNthRealData(argv[i+j*nitem+1], 1, " ,");
                        }
                        i++;
                        info->flagleftMin=count;
                        for(j=0; j<count; j++) {
                            info->leftMax[j] = stringGetNthRealData(argv[i+j*nitem+1], 1, " ,");
                        }
                        i++;
                        info->flagleftMax=count;
                        for(j=0; j<count; j++) {
                            info->rightMin[j] = stringGetNthRealData(argv[i+j*nitem+1], 1, " ,");
                        }
                        i++;
                        info->flagrightMin=count;
                        for(j=0; j<count; j++) {
                            info->rightMax[j] = stringGetNthRealData(argv[i+j*nitem+1], 1, " ,");
                        }
                        i++;
                        info->flagrightMax=count;
                        for(j=0; j<count; j++) {
                            info->weight[j] = stringGetNthRealData(argv[i+j*nitem+1], 1, " ,");
                        }
                        i++;
                        info->flagweight=count;
                        }
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
