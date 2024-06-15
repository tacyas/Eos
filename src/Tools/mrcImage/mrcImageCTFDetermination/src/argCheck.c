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
argCheck(mrcImageCTFDeterminationInfo* info, int argc, char* argv[])
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
                SCASE("r") {
                    if(i+1<argc) {
                        info->Ref = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRef++;
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
                SCASE("oP") {
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
                SCASE("oC") {
                    if(i+1<argc) {
                        info->OutC = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutC++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("oF") {
                    if(i+1<argc) {
                        info->OutF = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutF++;
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
                SCASE("W") {
                    if(i+1<argc) {
                        info->WhiteNoise = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWhiteNoise++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("df") {
                    if(i+3<argc) {
                        info->mindf = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmindf++;
                        info->maxdf = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxdf++;
                        info->deldf = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeldf++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("AoverP") {
                    if(i+3<argc) {
                        info->minAoverP = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminAoverP++;
                        info->maxAoverP = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxAoverP++;
                        info->delAoverP = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelAoverP++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rmin") {
                    if(i+1<argc) {
                        info->Rmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRmin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rmax") {
                    if(i+1<argc) {
                        info->Rmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRmax++;
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
                SCASE("mF") {
                    if(i+1<argc) {
                        info->mF = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmF++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mW") {
                    if(i+1<argc) {
                        info->mW = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmW++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mS") {
                    if(i+1<argc) {
                        info->mS = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmS++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mC") {
                    if(i+1<argc) {
                        info->mC = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmC++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("M") {
                    if(i+1<argc) {
                        info->M = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagM++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("PixelSize") {
                    if(i+1<argc) {
                        info->PixelSize = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagPixelSize++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Width") {
                    if(i+1<argc) {
                        info->Width = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWidth++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("truePitch") {
                    if(i+1<argc) {
                        info->truePitch = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtruePitch++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dfRef") {
                    if(i+2<argc) {
                        info->firstDf = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagfirstDf++;
                        info->withinDf = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagwithinDf++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("AoverPRef") {
                    if(i+2<argc) {
                        info->firstAoverP = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagfirstAoverP++;
                        info->withinAoverP = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagwithinAoverP++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("MaxIter") {
                    if(i+1<argc) {
                        info->maxiter = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxiter++;
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
