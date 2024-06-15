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
argCheck(mrcImageOpticalFlowInfo* info, int argc, char* argv[])
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
                SCASE("i1") {
                    if(i+1<argc) {
                        info->In1 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn1++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i2") {
                    if(i+1<argc) {
                        info->In2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i3") {
                    if(i+1<argc) {
                        info->In3 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o") {
                    if(i+3<argc) {
                        info->Vx = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagVx++;
                        info->Vy = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagVy++;
                        info->Vz = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagVz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("oF") {
                    if(i+4<argc) {
                        info->OutFx = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutFx++;
                        info->OutFy = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutFy++;
                        info->OutFz = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutFz++;
                        info->OutDi = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutDi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("oSize") {
                    if(i+1<argc) {
                        info->Size = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagSize++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("oCOMMAND") {
                    if(i+1<argc) {
                        info->OutCOMMAND = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutCOMMAND++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("oBILD") {
                    if(i+1<argc) {
                        info->OutBILD = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutBILD++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("bg") {
                    if(i+1<argc) {
                        info->BG = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBG++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("bildThresLow") {
                    if(i+1<argc) {
                        info->BildThresLow = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBildThresLow++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("bildThresHigh") {
                    if(i+1<argc) {
                        info->BildThresHigh = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBildThresHigh++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("bildRangeLow") {
                    if(i+1<argc) {
                        info->BildRangeLow = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBildRangeLow++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("bildRangeHigh") {
                    if(i+1<argc) {
                        info->BildRangeHigh = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBildRangeHigh++;
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
