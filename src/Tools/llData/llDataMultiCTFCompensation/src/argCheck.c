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
argCheck(llDataMultiCTFCompensationInfo* info, int argc, char* argv[])
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
                SCASE("M") {
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
                SCASE("l") {
                    if(i+1<argc) {
                        info->llInfo = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagllInfo++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("A") {
                    if(i+1<argc) {
                        info->Ave = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagAve++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o") {
                    if(i+1<argc) {
                        info->OutParam = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutParam++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("O") {
                    if(i+1<argc) {
                        info->OutList = stringGetNthWord(argv[i+1], 1, " ,");
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
                        info->OutParam2List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutParam2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("P2") {
                    if(i+1<argc) {
                        info->OutParamP2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutParamP2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("N") {
                    if(i+1<argc) {
                        info->Noise = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNoise++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("t") {
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
                SCASE("d") {
                    if(i+1<argc) {
                        info->deltaR = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeltaR++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("r") {
                    if(i+3<argc) {
                        info->rmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrmin++;
                        info->rmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrmax++;
                        info->dr = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdr++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("p") {
                    if(i+3<argc) {
                        info->phimin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagphimin++;
                        info->phimax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagphimax++;
                        info->dphi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdphi++;
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
                        info->dz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rmax") {
                    if(i+1<argc) {
                        info->Rmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRmax++;
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
