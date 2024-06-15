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
argCheck(mrcImageAutoRotationCorrelationInfo* info, int argc, char* argv[])
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
                SCASE("r") {
                    if(i+1<argc) {
                        info->Ref = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRef++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nRot1") {
                    if(i+1<argc) {
                        info->nRot1 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot1++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nRot2") {
                    if(i+1<argc) {
                        info->nRot2 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nRot3") {
                    if(i+1<argc) {
                        info->nRot3 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dRot1") {
                    if(i+1<argc) {
                        info->dRot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdRot1++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dRot2") {
                    if(i+1<argc) {
                        info->dRot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdRot2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dRot3") {
                    if(i+1<argc) {
                        info->dRot3 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdRot3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("startRot1") {
                    if(i+1<argc) {
                        info->startRot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstartRot1++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("startRot2") {
                    if(i+1<argc) {
                        info->startRot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstartRot2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("startRot3") {
                    if(i+1<argc) {
                        info->startRot3 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstartRot3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("StackOrder") {
                    if(i+1<argc) {
                        info->StackOrder = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagStackOrder++;
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
                SCASE("O") {
                    if(i+1<argc) {
                        info->OutASC = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutASC++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("cor") {
                    if(i+1<argc) {
                        info->corFile = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagcorFile++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("cor2") {
                    if(i+1<argc) {
                        info->corFile2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagcorFile2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("corAll") {
                    if(i+1<argc) {
                        info->corAllFile = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagcorAllFile++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("fit") {
                    if(i+1<argc) {
                        info->fitFile = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagfitFile++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("fit2") {
                    if(i+1<argc) {
                        info->fitFile2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagfitFile2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RefineMode") {
                    if(i+1<argc) {
                        info->RefineMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRefineMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("n") {
                    if(i+1<argc) {
                        info->Rot = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("range") {
                    if(i+2<argc) {
                        info->minAngle = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminAngle++;
                        info->maxAngle = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxAngle++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("refStep1") {
                    if(i+1<argc) {
                        info->refStep1 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrefStep1++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("refStep2") {
                    if(i+1<argc) {
                        info->refStep2 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrefStep2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("refStep3") {
                    if(i+1<argc) {
                        info->refStep3 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrefStep3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nRot1Area") {
                    if(i+3<argc) {
                        info->nRot1AreaMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot1AreaMin++;
                        info->nRot1AreaMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot1AreaMax++;
                        info->nRot1AreaStep = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot1AreaStep++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nRot2Area") {
                    if(i+3<argc) {
                        info->nRot2AreaMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot2AreaMin++;
                        info->nRot2AreaMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot2AreaMax++;
                        info->nRot2AreaStep = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot2AreaStep++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nRot3Area") {
                    if(i+3<argc) {
                        info->nRot3AreaMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot3AreaMin++;
                        info->nRot3AreaMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot3AreaMax++;
                        info->nRot3AreaStep = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRot3AreaStep++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("MagRange") {
                    if(i+3<argc) {
                        info->MagRangeMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMagRangeMin++;
                        info->MagRangeMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMagRangeMax++;
                        info->MagRangeStep = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMagRangeStep++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Iter") {
                    if(i+1<argc) {
                        info->Iter = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagIter++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Method") {
                    if(i+1<argc) {
                        info->Method = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMethod++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("s") {
                    if(i+4<argc) {
                        info->sminx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsminx++;
                        info->sminy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsminy++;
                        info->smaxx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsmaxx++;
                        info->smaxy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsmaxy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Shift") {
                    if(i+0<argc) {
                        info->Shift++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RepeatX") {
                    if(i+1<argc) {
                        info->RepeatX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRepeatX++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RepeatXDelta") {
                    if(i+1<argc) {
                        info->RepeatXDelta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRepeatXDelta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RepeatY") {
                    if(i+1<argc) {
                        info->RepeatY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRepeatY++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RepeatYDelta") {
                    if(i+1<argc) {
                        info->RepeatYDelta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRepeatYDelta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Xshift") {
                    if(i+0<argc) {
                        info->Xshift++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("NoShift") {
                    if(i+0<argc) {
                        info->NoShift++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Log") {
                    if(i+1<argc) {
                        info->Log = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagLog++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("pvm") {
                    if(i+1<argc) {
                        info->pvm = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagpvm++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("pvmList") {
                    if(i+1<argc) {
                        info->pvmList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagpvmList++;
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
