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
argCheck(mrcImageCTFCompensationInfo* info, int argc, char* argv[])
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
                SCASE("info") {
                    if(i+1<argc) {
                        info->Info = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInfo++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("info2") {
                    if(i+1<argc) {
                        info->Info2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInfo2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("kV") {
                    if(i+1<argc) {
                        info->kV = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagkV++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Cs") {
                    if(i+1<argc) {
                        info->Cs = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCs++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("df") {
                    if(i+1<argc) {
                        info->Defocus = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDefocus++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("white") {
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
                SCASE("whiteRaise") {
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
                SCASE("A") {
                    if(i+1<argc) {
                        info->Amp = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAmp++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Astig") {
                    if(i+3<argc) {
                        info->dfMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdfMin++;
                        info->dfMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdfMax++;
                        info->asAxis = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagasAxis++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("NoAstig") {
                    if(i+0<argc) {
                        info->NoAstigmatism++;
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
