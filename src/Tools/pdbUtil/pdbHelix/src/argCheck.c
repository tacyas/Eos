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
argCheck(pdbHelixInfo* info, int argc, char* argv[])
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
                SCASE("3") {
                    if(i+1<argc) {
                        info->Out3D = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut3D++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("2") {
                    if(i+1<argc) {
                        info->Out2D = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut2D++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("d") {
                    if(i+1<argc) {
                        info->delta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("p") {
                    if(i+1<argc) {
                        info->delphi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelphi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dp") {
                    if(i+1<argc) {
                        info->deldelphi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeldelphi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("z") {
                    if(i+1<argc) {
                        info->delz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("n") {
                    if(i+1<argc) {
                        info->nMolecule = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnMolecule++;
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
                SCASE("Sx") {
                    if(i+1<argc) {
                        info->Startx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagStartx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Sy") {
                    if(i+1<argc) {
                        info->Starty = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagStarty++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Sz") {
                    if(i+1<argc) {
                        info->Startz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagStartz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("w") {
                    if(i+1<argc) {
                        info->Weight = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWeight++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dx") {
                    if(i+1<argc) {
                        info->dx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dy") {
                    if(i+1<argc) {
                        info->dy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dz") {
                    if(i+1<argc) {
                        info->dz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("startn") {
                    if(i+1<argc) {
                        info->startn = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstartn++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("startC") {
                    if(i+1<argc) {
                        info->startID = argv[i+1][0];
                        i++;
                        info->flagstartID++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("deltaSeq") {
                    if(i+1<argc) {
                        info->deltaSeq = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeltaSeq++;
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
