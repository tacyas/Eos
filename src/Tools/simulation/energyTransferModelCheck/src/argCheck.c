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
argCheck(energyTransferModelCheckInfo* info, int argc, char* argv[])
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
                SCASE("p") {
                    if(i+1<argc) {
                        info->PDB = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagPDB++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("P") {
                    if(i+1<argc) {
                        info->PDBsList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagPDBs++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("PW") {
                    if(i+0<argc) {
                        info->PDBsWithInfo++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sigma") {
                    if(i+1<argc) {
                        info->sigma = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsigma++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sigmaA") {
                    if(i+1<argc) {
                        info->sigmaA = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsigmaA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mrc") {
                    if(i+1<argc) {
                        info->MRC = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagMRC++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("MRC") {
                    if(i+1<argc) {
                        info->MRCsList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagMRCs++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("MRCW") {
                    if(i+0<argc) {
                        info->MRCWithInfo++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("C") {
                    if(i+1<argc) {
                        info->EContour = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagEContour++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Near") {
                    if(i+1<argc) {
                        info->ENear = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagENear++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("NearA") {
                    if(i+1<argc) {
                        info->ENearA = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagENearA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("r") {
                    if(i+1<argc) {
                        info->Rest = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRest++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("R") {
                    if(i+1<argc) {
                        info->RestsList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRests++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("contour") {
                    if(i+1<argc) {
                        info->Contour = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagContour++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("near") {
                    if(i+1<argc) {
                        info->Near = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNear++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nearA") {
                    if(i+1<argc) {
                        info->NearA = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNearA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RW") {
                    if(i+0<argc) {
                        info->RestrictWithInfo++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rP") {
                    if(i+1<argc) {
                        info->RestP = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRestP++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RP") {
                    if(i+1<argc) {
                        info->RestsPList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRestsP++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sigmaP") {
                    if(i+1<argc) {
                        info->SigmaP = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSigmaP++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sigmaPA") {
                    if(i+1<argc) {
                        info->SigmaPA = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSigmaPA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nearP") {
                    if(i+1<argc) {
                        info->NearP = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNearP++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nearPA") {
                    if(i+1<argc) {
                        info->NearPA = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNearPA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RPW") {
                    if(i+0<argc) {
                        info->RestrictPW++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("delta") {
                    if(i+3<argc) {
                        info->deltax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeltax++;
                        info->deltay = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeltay++;
                        info->deltaz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeltaz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sdelta") {
                    if(i+3<argc) {
                        info->sdeltax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsdeltax++;
                        info->sdeltay = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsdeltay++;
                        info->sdeltaz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsdeltaz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("start") {
                    if(i+3<argc) {
                        info->startx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstartx++;
                        info->starty = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstarty++;
                        info->startz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstartz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("end") {
                    if(i+3<argc) {
                        info->endx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagendx++;
                        info->endy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagendy++;
                        info->endz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagendz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maxIter") {
                    if(i+1<argc) {
                        info->maxIter = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxIter++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("startIter") {
                    if(i+1<argc) {
                        info->startIter = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstartIter++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("neglect") {
                    if(i+1<argc) {
                        info->neglect = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagneglect++;
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
