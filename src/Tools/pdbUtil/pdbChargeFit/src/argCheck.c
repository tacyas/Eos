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
argCheck(pdbChargeFitInfo* info, int argc, char* argv[])
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
                SCASE("if") {
                    if(i+1<argc) {
                        info->InFix = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInFix++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("im") {
                    if(i+1<argc) {
                        info->InMove = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInMove++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o") {
                    if(i+1<argc) {
                        info->OutTxt = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutTxt++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("s") {
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
                SCASE("zmin") {
                    if(i+1<argc) {
                        info->zmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzmin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("zmax") {
                    if(i+1<argc) {
                        info->zmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("zDel") {
                    if(i+1<argc) {
                        info->zDel = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzDel++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mind") {
                    if(i+1<argc) {
                        info->mind = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmind++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maxd") {
                    if(i+1<argc) {
                        info->maxd = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxd++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("a[xis]") {
                    if(i+2<argc) {
                        info->axisX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagaxisX++;
                        info->axisY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagaxisY++;
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
