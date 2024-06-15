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
argCheck(mrcImagePrint3DInfo* info, int argc, char* argv[])
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
                SCASE("stereo") {
                    if(i+1<argc) {
                        info->Stereo = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagStereo++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rotation") {
                    if(i+2<argc) {
                        info->nRotation = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnRotation++;
                        info->RotationAngle = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRotationAngle++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("eye") {
                    if(i+3<argc) {
                        info->eyeX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flageyeX++;
                        info->eyeY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flageyeY++;
                        info->eyeZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flageyeZ++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("plane") {
                    if(i+3<argc) {
                        info->planeX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagplaneX++;
                        info->planeY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagplaneY++;
                        info->planeZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagplaneZ++;
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
