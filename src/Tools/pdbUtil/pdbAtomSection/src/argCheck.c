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
argCheck(pdbAtomSectionInfo* info, int argc, char* argv[])
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
                SCASE("if") {
                    if(i+1<argc) {
                        info->InFlags = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInFlags++;
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
                SCASE("dist") {
                    if(i+1<argc) {
                        info->distance = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdistance++;
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
                SCASE("fm") {
                    if(i+1<argc) {
                        info->flagMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagflagMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("r") {
                    if(i+1<argc) {
                        info->radius = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagradius++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("clw") {
                    if(i+1<argc) {
                        info->clinewidth = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagclinewidth++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("plw") {
                    if(i+1<argc) {
                        info->plinewidth = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagplinewidth++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("fontsize") {
                    if(i+1<argc) {
                        info->fontsize = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagfontsize++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("AS") {
                    if(i+1<argc) {
                        info->scale = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagscale++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("shiftx") {
                    if(i+1<argc) {
                        info->shiftx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagshiftx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("shifty") {
                    if(i+1<argc) {
                        info->shifty = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagshifty++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("shiftz") {
                    if(i+1<argc) {
                        info->shiftz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagshiftz++;
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
