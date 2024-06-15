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
argCheck(ctfDeterminationByBayesInfo* info, int argc, char* argv[])
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
                SCASE("i2") {
                    if(i+1<argc) {
                        info->In2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i3") {
                    if(i+1<argc) {
                        info->In3 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i4") {
                    if(i+1<argc) {
                        info->In4List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn4++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("n") {
                    if(i+2<argc) {
                        info->numDistribution = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnumDistribution++;
                        info->numLikelihood = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnumLikelihood++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rmax") {
                    if(i+1<argc) {
                        info->rmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rintermediate") {
                    if(i+1<argc) {
                        info->rintermediate = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrintermediate++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rfirstpeak") {
                    if(i+1<argc) {
                        info->rfirstpeak = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrfirstpeak++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rmin") {
                    if(i+1<argc) {
                        info->rmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrmin++;
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
                SCASE("MTFmode") {
                    if(i+1<argc) {
                        info->MTFmode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMTFmode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Ainmode") {
                    if(i+1<argc) {
                        info->Ainmode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAinmode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Intensitymode") {
                    if(i+1<argc) {
                        info->Intensitymode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagIntensitymode++;
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
