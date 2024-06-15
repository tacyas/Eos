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
argCheck(mrcImageModelCreateInfo* info, int argc, char* argv[])
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
                SCASE("nx") {
                    if(i+1<argc) {
                        info->nx = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ny") {
                    if(i+1<argc) {
                        info->ny = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagny++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nz") {
                    if(i+1<argc) {
                        info->nz = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("r") {
                    if(i+1<argc) {
                        info->r = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagr++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("l") {
                    if(i+1<argc) {
                        info->l = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagl++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("lx") {
                    if(i+1<argc) {
                        info->lx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flaglx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ly") {
                    if(i+1<argc) {
                        info->ly = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagly++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("lz") {
                    if(i+1<argc) {
                        info->lz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flaglz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("radius") {
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
                SCASE("n") {
                    if(i+1<argc) {
                        info->nHelix = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnHelix++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dz") {
                    if(i+1<argc) {
                        info->zPitch = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzPitch++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dphi") {
                    if(i+1<argc) {
                        info->deltaPhi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeltaPhi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("phi") {
                    if(i+1<argc) {
                        info->phiAngle = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagphiAngle++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sz") {
                    if(i+1<argc) {
                        info->startZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstartZ++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ez") {
                    if(i+1<argc) {
                        info->endZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagendZ++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sphi") {
                    if(i+1<argc) {
                        info->startPhi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstartPhi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sphi2") {
                    if(i+1<argc) {
                        info->startPhi2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstartPhi2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("inMode") {
                    if(i+1<argc) {
                        info->inMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flaginMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("units") {
                    if(i+1<argc) {
                        info->units = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagunits++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("fm") {
                    if(i+1<argc) {
                        info->fm = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagfm++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("range") {
                    if(i+2<argc) {
                        info->min = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmin++;
                        info->max = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmax++;
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
