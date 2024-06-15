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
argCheck(llExtractWithLayerSeparationInfo* info, int argc, char* argv[])
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
                        info->InList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("I") {
                    if(i+2<argc) {
                        info->InLLNeaList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInLLNea++;
                        info->InLLFarList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInLLFar++;
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
                SCASE("o2") {
                    if(i+1<argc) {
                        info->Out2List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o3") {
                    if(i+1<argc) {
                        info->Out3List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o4") {
                    if(i+1<argc) {
                        info->Out4List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut4++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o5") {
                    if(i+1<argc) {
                        info->Out5List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut5++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o6") {
                    if(i+1<argc) {
                        info->Out6List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut6++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o7") {
                    if(i+1<argc) {
                        info->Out7 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut7++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o8") {
                    if(i+1<argc) {
                        info->Out8 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut8++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o9") {
                    if(i+1<argc) {
                        info->Out9List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut9++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("comment") {
                    if(i+1<argc) {
                        info->InComment = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInComment++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("symmetry") {
                    if(i+1<argc) {
                        info->symmetry = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsymmetry++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("l") {
                    if(i+1<argc) {
                        info->llInfoList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagllInfo++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("lfinal") {
                    if(i+1<argc) {
                        info->llInfoFinal = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagllInfoFinal++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("li") {
                    if(i+1<argc) {
                        info->llInfoImpList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagllInfoImp++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("liw") {
                    if(i+1<argc) {
                        info->liWeight = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagliWeight++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("liwStart") {
                    if(i+1<argc) {
                        info->liWeightStart = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagliWeightStart++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("liwStep") {
                    if(i+1<argc) {
                        info->liWeightStep = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagliWeightStep++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("la") {
                    if(i+1<argc) {
                        info->llInfoAxisList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagllInfoAxis++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("law") {
                    if(i+1<argc) {
                        info->laWeight = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flaglaWeight++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("lawStart") {
                    if(i+1<argc) {
                        info->laWeightStart = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flaglaWeightStart++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("lawStep") {
                    if(i+1<argc) {
                        info->laWeightStep = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flaglaWeightStep++;
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
                SCASE("rMax") {
                    if(i+1<argc) {
                        info->rMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rMaxMin") {
                    if(i+1<argc) {
                        info->rMaxMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrMaxMin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RMax") {
                    if(i+1<argc) {
                        info->RMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RMaxFirst") {
                    if(i+1<argc) {
                        info->RMaxFirst = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRMaxFirst++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RMaxStep") {
                    if(i+1<argc) {
                        info->RMaxStep = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRMaxStep++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RRMax") {
                    if(i+1<argc) {
                        info->RRMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRRMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RRMaxFirst") {
                    if(i+1<argc) {
                        info->RRMaxFirst = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRRMaxFirst++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RRMaxStep") {
                    if(i+1<argc) {
                        info->RRMaxStep = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRRMaxStep++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("delBR") {
                    if(i+1<argc) {
                        info->delBR = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelBR++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rms") {
                    if(i+1<argc) {
                        info->rms = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrms++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("narrowSearch") {
                    if(i+1<argc) {
                        info->narrowSearch = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnarrowSearch++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nextTimes") {
                    if(i+1<argc) {
                        info->nextTimes = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnextTimes++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maxIter") {
                    if(i+1<argc) {
                        info->MaxIteration = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMaxIteration++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maxIter2") {
                    if(i+1<argc) {
                        info->MaxIter2 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMaxIter2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maxIter3") {
                    if(i+1<argc) {
                        info->MaxIter3 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMaxIter3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("lambda") {
                    if(i+1<argc) {
                        info->lambda = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flaglambda++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ctf") {
                    if(i+1<argc) {
                        info->CTF = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCTF++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("WhiteNoise") {
                    if(i+1<argc) {
                        info->WhiteNoise = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWhiteNoise++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("below") {
                    if(i+1<argc) {
                        info->below = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagbelow++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("noantipole") {
                    if(i+0<argc) {
                        info->noantipole++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("magLimit") {
                    if(i+0<argc) {
                        info->magLimit++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("eachTime") {
                    if(i+0<argc) {
                        info->eachTime++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("continue") {
                    if(i+1<argc) {
                        info->Continue = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagContinue++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("forContinue") {
                    if(i+1<argc) {
                        info->ForContinue = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagForContinue++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("phi") {
                    if(i+3<argc) {
                        info->phimin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagphimin++;
                        info->phimax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagphimax++;
                        info->delphi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelphi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("z") {
                    if(i+3<argc) {
                        info->zmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzmin++;
                        info->zmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzmax++;
                        info->delz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("shift") {
                    if(i+3<argc) {
                        info->shiftmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagshiftmin++;
                        info->shiftmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagshiftmax++;
                        info->delshift = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelshift++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("log") {
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
                SCASE("Normalization") {
                    if(i+0<argc) {
                        info->Normalization++;
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
                SCASE("pvmServer") {
                    if(i+0<argc) {
                        info->pvmServer++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("pvmClient") {
                    if(i+0<argc) {
                        info->pvmClient++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("wd") {
                    if(i+1<argc) {
                        info->WorkingDir = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagWorkingDir++;
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
