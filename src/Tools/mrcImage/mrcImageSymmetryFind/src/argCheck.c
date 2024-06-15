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
argCheck(mrcImageSymmetryFindInfo* info, int argc, char* argv[])
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
                SCASE("O") {
                    if(i+1<argc) {
                        info->Out2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("A") {
                    if(i+1<argc) {
                        info->Avg = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagAvg++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("centreMode") {
                    if(i+1<argc) {
                        info->centreMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcentreMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("t1") {
                    if(i+1<argc) {
                        info->threshold1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagthreshold1++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("t2") {
                    if(i+1<argc) {
                        info->threshold2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagthreshold2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("m1") {
                    if(i+1<argc) {
                        info->mode1 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmode1++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("m2") {
                    if(i+1<argc) {
                        info->mode2 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmode2++;
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
                SCASE("nRange") {
                    if(i+2<argc) {
                        info->nmin = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnmin++;
                        info->nmax = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("In") {
                    if(i+2<argc) {
                        info->ImageList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagImage++;
                        info->BackList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagBack++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rangex") {
                    if(i+3<argc) {
                        info->minx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminx++;
                        info->maxx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxx++;
                        info->delx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rangey") {
                    if(i+3<argc) {
                        info->miny = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminy++;
                        info->maxy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxy++;
                        info->dely = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdely++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rangez") {
                    if(i+3<argc) {
                        info->minz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminz++;
                        info->maxz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxz++;
                        info->delz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rrange") {
                    if(i+2<argc) {
                        info->rmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrmin++;
                        info->rmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Algorythm") {
                    if(i+0<argc) {
                        info->Algorythm++;
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
