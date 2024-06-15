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
argCheck(pdb2mrc2dWithCTFInfo* info, int argc, char* argv[])
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
                SCASE("N") {
                    if(i+2<argc) {
                        info->Nx = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNx++;
                        info->Ny = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("d") {
                    if(i+2<argc) {
                        info->dx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdx++;
                        info->dy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Centre") {
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
                SCASE("n") {
                    if(i+2<argc) {
                        info->nx = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnx++;
                        info->ny = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagny++;
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
                SCASE("A") {
                    if(i+1<argc) {
                        info->AoverP = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAoverP++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Ain") {
                    if(i+1<argc) {
                        info->Ain = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ctfMode") {
                    if(i+1<argc) {
                        info->ctfMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagctfMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("EA") {
                    if(i+4<argc) {
                        info->EulerAngle = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagEulerAngle++;
                        info->Rot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot1++;
                        info->Rot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot2++;
                        info->Rot3 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot3++;
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
