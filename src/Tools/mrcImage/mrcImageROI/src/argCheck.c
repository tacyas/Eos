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
argCheck(mrcImageROIInfo* info, int argc, char* argv[])
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
                SCASE("r") {
                    if(i+8<argc) {
                        info->blx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagblx++;
                        info->bly = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagbly++;
                        info->brx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagbrx++;
                        info->bry = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagbry++;
                        info->trx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtrx++;
                        info->try = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtry++;
                        info->tlx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtlx++;
                        info->tly = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtly++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("x") {
                    if(i+1<argc) {
                        info->WidthBeforeExpansion = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWidthBeforeExpansion++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("y") {
                    if(i+1<argc) {
                        info->HeightBeforeExpansion = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagHeightBeforeExpansion++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("a") {
                    if(i+1<argc) {
                        info->Angle = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAngle++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("W") {
                    if(i+1<argc) {
                        info->WidthAfterExpansion = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWidthAfterExpansion++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("H") {
                    if(i+1<argc) {
                        info->HeightAfterExpansion = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagHeightAfterExpansion++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Shift") {
                    if(i+2<argc) {
                        info->ShiftX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagShiftX++;
                        info->ShiftY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagShiftY++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("truePitch") {
                    if(i+1<argc) {
                        info->truePitch = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtruePitch++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dY") {
                    if(i+1<argc) {
                        info->dY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdY++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Ly") {
                    if(i+1<argc) {
                        info->Ly = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("S") {
                    if(i+1<argc) {
                        info->Shrink = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagShrink++;
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
                SCASE("M") {
                    if(i+1<argc) {
                        info->ROIShapeMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagROIShapeMode++;
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
