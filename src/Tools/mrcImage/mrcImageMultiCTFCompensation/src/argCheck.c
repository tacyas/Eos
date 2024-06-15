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
argCheck(mrcImageMultiCTFCompensationInfo* info, int argc, char* argv[])
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
                SCASE("info2") {
                    if(i+1<argc) {
                        info->CTFList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagCTF++;
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
                SCASE("f") {
                    if(i+1<argc) {
                        info->fftOut = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagfftOut++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("W") {
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
                SCASE("WR") {
                    if(i+1<argc) {
                        info->WhiteNoiseRaising = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWhiteNoiseRaising++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maxWR") {
                    if(i+1<argc) {
                        info->MaxWhiteNoise = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMaxWhiteNoise++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("NdepWR") {
                    if(i+1<argc) {
                        info->NdependentWhiteNoise = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNdependentWhiteNoise++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("SinWin") {
                    if(i+2<argc) {
                        info->SinWinRmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSinWinRmin++;
                        info->SinWinRmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSinWinRmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("MaxIter") {
                    if(i+1<argc) {
                        info->MaxIter = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMaxIter++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ctfMode") {
                    if(i+1<argc) {
                        info->CTFMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCTFMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("solventMode") {
                    if(i+1<argc) {
                        info->solventMode = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsolventMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("solventSTD") {
                    if(i+1<argc) {
                        info->solventSTD = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsolventSTD++;
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
