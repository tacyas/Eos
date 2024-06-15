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
argCheck(vector2pdbInfo* info, int argc, char* argv[])
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
                SCASE("v") {
                    if(i+3<argc) {
                        info->vx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagvx++;
                        info->vy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagvy++;
                        info->vz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagvz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("polar") {
                    if(i+2<argc) {
                        info->phi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagphi++;
                        info->theta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtheta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("polarz") {
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
                SCASE("polarx") {
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
                SCASE("ori") {
                    if(i+3<argc) {
                        info->sx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsx++;
                        info->sy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsy++;
                        info->sz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("step") {
                    if(i+1<argc) {
                        info->step = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstep++;
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
                SCASE("n") {
                    if(i+1<argc) {
                        info->n = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagn++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ID") {
                    if(i+1<argc) {
                        info->ID = argv[i+1][0];
                        i++;
                        info->flagID++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Res") {
                    if(i+1<argc) {
                        info->Res = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRes++;
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
