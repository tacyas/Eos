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
argCheck(mrcRadon2Dto3DInfo* info, int argc, char* argv[])
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
                SCASE("I") {
                    if(i+1<argc) {
                        info->In2List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Ib") {
                    if(i+1<argc) {
                        info->InBeforeList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInBefore++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ib") {
                    if(i+1<argc) {
                        info->inbefore = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flaginbefore++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("iwb") {
                    if(i+1<argc) {
                        info->inWbefore = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flaginWbefore++;
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
                SCASE("ow") {
                    if(i+1<argc) {
                        info->OutW = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutW++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dp") {
                    if(i+1<argc) {
                        info->dp = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdp++;
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
                SCASE("T") {
                    if(i+1<argc) {
                        info->T = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagT++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("InterpolationMode") {
                    if(i+1<argc) {
                        info->InterpolationMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagInterpolationMode++;
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
