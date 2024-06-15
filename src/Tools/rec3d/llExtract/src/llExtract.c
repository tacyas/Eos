/*
# llExtract.c  1.1
# The latest update : 05/29/97 at 20:23:26
#
#@(#) llExtract ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : llExtract
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)llExtract ver1.1; Date:97/05/29 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "llData.h"
#include "lllExtract.h"

extern void configFileRead(FILE* fpt, llExtractInfo* info);
extern void configFileUsage(FILE* fpt);
extern void infoCopyTolinfo(lllExtractInfo* linfo, llExtractInfo* info);

void
main(int argc, char* argv[]) 
{
	long status;
	llExtractInfo info;
	lllExtractInfo linfo;

    mrcImage in;
    llData   near;
	llData	 far;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

#ifdef DEBUG
	{ int i;

	for(i=0; i<info.flagn; i++) { 
		DEBUGPRINT2("N[%d]: %d\n", i, info.n[i]);
	}
	}
#endif
	if(info.flagconfigFile) {
		configFileRead(info.fptconfigFile, &info);
	}
	infoCopyTolinfo(&linfo, &info);
	
    mrcFileRead(&in, info.In, "main routine", 0);

    lllExtract(&near, &far, &in, &linfo);
	
    llDataFileWrite(info.fptNea, &near, &status);
    llDataFileWrite(info.fptFar, &far, &status);

	exit(EXIT_SUCCESS);
}

void 
infoCopyTolinfo(lllExtractInfo* linfo, llExtractInfo* info)
{
    linfo->Title = info->Title;
    linfo->xStep = info->xStep;
    linfo->yStep = info->yStep;
    linfo->MaxX  = info->MaxX;
    linfo->MaxY  = info->MaxY;
    linfo->RotationAngle = info->RotationAngle;
    linfo->Omega = info->Omega;
    linfo->Shear = info->Shear;
    linfo->ievery = info->ievery;
    linfo->axl   = info->axl;
    linfo->ayl   = info->ayl;
    linfo->xShift = info->xShift;
    linfo->llMax = info->llMax;
    linfo->delRInv = info->delRInv;
    linfo->flagOutputInfo = linfo->flagOutputInfo;
    linfo->n     = info->n;
    linfo->l     = info->l;
    linfo->Y     = info->Y;
    linfo->leftMin = info->leftMin;
    linfo->leftMax = info->leftMax;
    linfo->rightMin = info->rightMin;
    linfo->rightMax = info->rightMax;
    linfo->weight   = info->weight;
}

void
additionalUsage()
{
	configFileUsage(stderr);
}

#include <stdio.h>
#include "eosString.h"
#include "Memory.h"
#include "File.h"
void
configFileRead(FILE* fpt, llExtractInfo* info)
{
    char s[1024];
    long i, j, k;
    fseek(fpt, 0L, SEEK_SET);
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagTitle) {
        info->Title = stringGetNthWord(s, 1, " \t,");
        info->flagTitle++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagxStep) {
        info->xStep = stringGetNthRealData(s, 1, " \t,");
        info->flagxStep++;
    }
    
    if(!info->flagyStep) {
        info->yStep = stringGetNthRealData(s, 2, " \t,");
        info->flagyStep++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagMaxX) {
        info->MaxX = stringGetNthRealData(s, 1, " \t,");
        info->flagMaxX++;
    }
    
    if(!info->flagMaxY) {
        info->MaxY = stringGetNthRealData(s, 2, " \t,");
        info->flagMaxY++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagIn) {
        info->In = stringGetNthWord(s, 1, " \t,");
        info->fptIn = fileOpen(info->In, "r");
        info->flagIn++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagNea) {
        info->Nea = stringGetNthWord(s, 1, " \t,");
        info->fptNea = fileOpen(info->Nea, "w");
        info->flagNea++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagFar) {
        info->Far = stringGetNthWord(s, 1, " \t,");
        info->fptFar = fileOpen(info->Far, "w");
        info->flagFar++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagRotationAngle) {
        info->RotationAngle = stringGetNthRealData(s, 1, " \t,");
        info->flagRotationAngle++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagOmega) {
        info->Omega = stringGetNthRealData(s, 1, " \t,");
        info->flagOmega++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagShear) {
        info->Shear = stringGetNthRealData(s, 1, " \t,");
        info->flagShear++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagievery) {
        info->ievery = stringGetNthIntegerData(s, 1, " \t,");
        info->flagievery++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagaxl) {
        info->axl = stringGetNthRealData(s, 1, " \t,");
        info->flagaxl++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagayl) {
        info->ayl = stringGetNthRealData(s, 1, " \t,");
        info->flagayl++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagxShift) {
        info->xShift = stringGetNthRealData(s, 1, " \t,");
        info->flagxShift++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagllMax) {
        info->llMax = stringGetNthIntegerData(s, 1, " \t,");
        info->flagllMax++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagdelRInv) {
        info->delRInv = stringGetNthRealData(s, 1, " \t,");
        info->flagdelRInv++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagOutputInfo) {
        info->flagOutputInfo = stringGetNthIntegerData(s, 1, " \t,");
    }
    
    if(!info->flagn) {
        j = ftell(fpt);
        k = 0; 
        while(NULL!=stringGetFromFile(s, "", fpt, stdout, 3)) {
            k++;
        }
        fseek(fpt, j, SEEK_SET);
        j = 0;
        while(NULL!=stringGetFromFile(s, "", fpt, stdout, 3)) {
			DEBUGPRINT2("%d:%s\n", j, s);
            if(0==j) {
                info->n = (long*)memoryAllocate(sizeof(long)*k,"configFileRead");
            }
            info->n[j] = stringGetNthIntegerData(s, 1, " \t,");
            info->flagn++;
    
            if(0==j) {
                info->l = (long*)memoryAllocate(sizeof(long)*k,"configFileRead");
            }
            info->l[j] = stringGetNthIntegerData(s, 2, " \t,");
            info->flagl++;
    
            if(0==j) {
                info->Y = (float*)memoryAllocate(sizeof(long)*k,"configFileRead");
            }
            info->Y[j] = stringGetNthRealData(s, 3, " \t,");
            info->flagY++;
    
            if(0==j) {
                info->leftMin = (float*)memoryAllocate(sizeof(long)*k,"configFileRead");
            }
            info->leftMin[j] = stringGetNthRealData(s, 4, " \t,");
            info->flagleftMin++;
    
            if(0==j) {
                info->leftMax = (float*)memoryAllocate(sizeof(long)*k,"configFileRead");
            }
            info->leftMax[j] = stringGetNthRealData(s, 5, " \t,");
            info->flagleftMax++;
    
            if(0==j) {
                info->rightMin = (float*)memoryAllocate(sizeof(long)*k,"configFileRead");
            }
            info->rightMin[j] = stringGetNthRealData(s, 6, " \t,");
            info->flagrightMin++;
    
            if(0==j) {
                info->rightMax = (float*)memoryAllocate(sizeof(long)*k,"configFileRead");
            }
            info->rightMax[j] = stringGetNthRealData(s, 7, " \t,");
            info->flagrightMax++;
    
            if(0==j) {
                info->weight = (float*)memoryAllocate(sizeof(long)*k,"configFileRead");
            }
            info->weight[j] = stringGetNthRealData(s, 8, " \t,");
            info->flagweight++;

			j++;
        }
    }
    
}

#include <stdio.h>
#include "eosString.h"
#include "File.h"
void
configFileUsage(FILE* fpt)
{
    fprintf(fpt, "----- Control File -----\n");
    fprintf(fpt, "Title[String:NULL]\t\t\t\t#Title[80]\n");
    fprintf(fpt, "xStep[Real:1.0]\tyStep[Real:1.0]\t\t\t\t#Step[A]\n");
    fprintf(fpt, "MaxX[Real:1.0]\tMaY[Real:1.0]\t\t\t\t#Max[GridUnit]\n");
    fprintf(fpt, "In[inFile:NULL]\t\t\t\t#InputDataFile[mrcImage]\n");
    fprintf(fpt, "Nea[outFile:NULL]\t\t\t\t#NearSide[llData]\n");
    fprintf(fpt, "Far[outFile:NULL]\t\t\t\t#FarSide [llData]\n");
    fprintf(fpt, "RotationAngle[Real:0.0]\t\t\t\t#Ratation Angle [Degree]\n");
    fprintf(fpt, "Omega[Real:0.0]\t\t\t\t#Omega[Degree]\n");
    fprintf(fpt, "Shear[Real:0.0]\t\t\t\t#Shear[Degree]\n");
    fprintf(fpt, "ievery[Integer:0]\t\t\t\t#ievery\n");
    fprintf(fpt, "axl[Real:0.0]\t\t\t\t#axl\n");
    fprintf(fpt, "ayl[Real:0.0]\t\t\t\t#ayl\n");
    fprintf(fpt, "xShift[Real:0.0]\t\t\t\t#[GridUnit]\n");
    fprintf(fpt, "llMax[Integer:0]\t\t\t\t#\n");
    fprintf(fpt, "delRInv[Real:0.0]\t\t\t\t#[A]\n");
    fprintf(fpt, "flagOutputInfo[0or1]");
    fprintf(fpt, "\t\t\t#\n");
    fprintf(fpt, "n[Integer:0]\tl[Integer:0]\tY[Real:0.0]\tleftMin[Real:0.0]\tleftMax[Real:0.0]\trightMin[Real:0.0]\trightMax[Real:0.0]\tweight[Real:1.0]\t\t\t\t#\n");
    fprintf(fpt, "...............\n");
}
