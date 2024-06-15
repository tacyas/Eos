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
argCheck(mrcImageTransformDescartesIntoPolarInfo* info, int argc, char* argv[])
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
                SCASE("dr") {
                    if(i+1<argc) {
                        info->dr = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdr++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dtheta") {
                    if(i+1<argc) {
                        info->dtheta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdtheta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dphi") {
                    if(i+1<argc) {
                        info->dphi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdphi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("zaxis") {
                    if(i+3<argc) {
                        info->zx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzx++;
                        info->zy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzy++;
                        info->zz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("xaxis") {
                    if(i+3<argc) {
                        info->xx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxx++;
                        info->xy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxy++;
                        info->xz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("centre") {
                    if(i+3<argc) {
                        info->cx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcx++;
                        info->cy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcy++;
                        info->cz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rweight") {
                    if(i+0<argc) {
                        info->rweight++;
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
