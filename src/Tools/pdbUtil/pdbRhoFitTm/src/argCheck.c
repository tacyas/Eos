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
argCheck(pdbRhoFitTmInfo* info, int argc, char* argv[])
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
                SCASE("ipdb") {
                    if(i+1<argc) {
                        info->InPdb = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInPdb++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("imrc") {
                    if(i+1<argc) {
                        info->InMrc = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInMrc++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("omrc") {
                    if(i+1<argc) {
                        info->OutMrc = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutMrc++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Sx") {
                    if(i+1<argc) {
                        info->Sx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Sy") {
                    if(i+1<argc) {
                        info->Sy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Sz") {
                    if(i+1<argc) {
                        info->Sz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("otxt") {
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
                SCASE("opdb") {
                    if(i+1<argc) {
                        info->OutPDB = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutPDB++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("xmin") {
                    if(i+1<argc) {
                        info->xmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxmin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("xmax") {
                    if(i+1<argc) {
                        info->xmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("xd") {
                    if(i+1<argc) {
                        info->xDelta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxDelta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ymin") {
                    if(i+1<argc) {
                        info->ymin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagymin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ymax") {
                    if(i+1<argc) {
                        info->ymax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagymax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("yd") {
                    if(i+1<argc) {
                        info->yDelta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagyDelta++;
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
                SCASE("zd") {
                    if(i+1<argc) {
                        info->zDelta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzDelta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("EA") {
                    if(i+1<argc) {
                        info->EulerAngle = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagEulerAngle++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("phimin") {
                    if(i+1<argc) {
                        info->phimin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagphimin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("phimax") {
                    if(i+1<argc) {
                        info->phimax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagphimax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("phid") {
                    if(i+1<argc) {
                        info->phiDelta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagphiDelta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("psimin") {
                    if(i+1<argc) {
                        info->psimin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagpsimin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("psimax") {
                    if(i+1<argc) {
                        info->psimax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagpsimax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("psid") {
                    if(i+1<argc) {
                        info->psiDelta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagpsiDelta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("thetamin") {
                    if(i+1<argc) {
                        info->thetamin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagthetamin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("thetamax") {
                    if(i+1<argc) {
                        info->thetamax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagthetamax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("thetad") {
                    if(i+1<argc) {
                        info->thetaDelta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagthetaDelta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nw") {
                    if(i+1<argc) {
                        info->normalizeWeight = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnormalizeWeight++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nC") {
                    if(i+1<argc) {
                        info->normalizeContour = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnormalizeContour++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("I") {
                    if(i+0<argc) {
                        info->Inverse++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Z") {
                    if(i+0<argc) {
                        info->Zminus++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("T") {
                    if(i+0<argc) {
                        info->Tfactor++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Tlim") {
                    if(i+1<argc) {
                        info->Tlim = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagTlim++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Centre") {
                    if(i+0<argc) {
                        info->Centre++;
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
                SCASE("C") {
                    if(i+1<argc) {
                        {
                        int j, nv, check, count, nitem;
                        nv    = argc - i - 1;
                        nitem = 1 ;
