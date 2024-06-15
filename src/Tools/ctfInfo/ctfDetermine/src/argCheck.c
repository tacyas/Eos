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
argCheck(ctfDetermineInfo* info, int argc, char* argv[])
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
                SCASE("D") {
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
                SCASE("Cc") {
                    if(i+1<argc) {
                        info->Cc = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCc++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dE") {
                    if(i+1<argc) {
                        info->dE = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdE++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Ac") {
                    if(i+1<argc) {
                        info->Ac = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAc++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("CutLow") {
                    if(i+1<argc) {
                        info->CutLow = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCutLow++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("CutHigh") {
                    if(i+1<argc) {
                        info->CutHigh = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCutHigh++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("I0") {
                    if(i+1<argc) {
                        info->I0 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagI0++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ratio") {
                    if(i+1<argc) {
                        info->ratioOfAmpToPhase = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagratioOfAmpToPhase++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Ai") {
                    if(i+1<argc) {
                        info->Ai = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("BofMTF") {
                    if(i+1<argc) {
                        info->BofMTF = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBofMTF++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("BofV") {
                    if(i+1<argc) {
                        info->BofVibration = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBofVibration++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Mag") {
                    if(i+1<argc) {
                        info->Magnification = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMagnification++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Noise") {
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
                SCASE("Noise2") {
                    if(i+1<argc) {
                        info->WhiteNoise2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWhiteNoise2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("MolcEnv") {
                    if(i+1<argc) {
                        info->MolcEnv = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMolcEnv++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("MolcEnv2") {
                    if(i+1<argc) {
                        info->MolcEnvTable = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagMolcEnvTable++;
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
                SCASE("min") {
                    if(i+1<argc) {
                        info->min = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("max") {
                    if(i+1<argc) {
                        info->max = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("s") {
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
                SCASE("d") {
                    if(i+1<argc) {
                        info->degree = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdegree++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("S") {
                    if(i+1<argc) {
                        info->section = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsection++;
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
