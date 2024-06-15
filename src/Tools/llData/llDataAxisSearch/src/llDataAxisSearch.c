/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataAxisSearch ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataAxisSearch
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataAxisSearch ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "llData.h"
#include "lllDataAxisSearch.h"

extern void llDataAxisSearchResultWrite(llDataAxisSearchInfo info, llDataFittedParam paraFit);
extern void configFileRead(FILE* fpt, llDataAxisSearchInfo* info);
extern void configFileUsage(FILE* fpt);

int
main(int argc, char* argv[]) 
{
	llDataAxisSearchInfo info;
    llData   llInNea;
    llData   llInFar;
    llData   llOutNea;
    llData   llOutFar;
	llData   llAvg;
	llDataParaTypeInteger status;
	llDataFittedParam paraFit;
    int l;
	

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	if(info.flagconfigFile) {
		configFileRead(info.fptconfigFile, &info);
	}

	llDataFileRead(info.fptIn1, &llInNea, &status);
	llDataFileRead(info.fptIn2, &llInFar, &status);
    lllDataWeightSet(info.fptL, &llInNea, 0.0, 0);
    lllDataWeightSet(info.fptL, &llInFar, 0.0, 0);
	llInNea.truePitch = llInFar.truePitch = info.truePitch;
	paraFit.Para.x.Min = info.xmin;
	paraFit.Para.x.Max = info.xmax;
	paraFit.Para.x.Delta = info.xdelta;
	paraFit.Para.Omega.Min = info.Omin*RADIAN;
	paraFit.Para.Omega.Max = info.Omax*RADIAN;
	paraFit.Para.Omega.Delta = info.Odelta*RADIAN;
	paraFit.Para.Resolution = info.R;
	paraFit.Para.flagLLTable = 0;

	if(info.flagOutP2) {
		lllDataAxisSearchWithFile(&llInNea, &llInFar, &(paraFit), info.OutP2, info.mode|QVALUE_MODE);
	} else {
		DEBUGPRINT("---lllDataAxisSearch---");
		lllDataAxisSearch(&llInNea, &llInFar, &(paraFit), info.mode|QVALUE_MODE);
	}
    llOutNea = llInNea; llDataInit(&llOutNea); lllDataAttributeCopy(&llOutNea, &llInNea);
    llOutFar = llInFar; llDataInit(&llOutFar); lllDataAttributeCopy(&llOutFar, &llInFar);
	paraFit.Para = paraFit.QPara;
    lllDataPhaseShiftIntra(&llOutNea, &llInNea, &paraFit);
    lllDataPhaseShiftIntra(&llOutFar, &llInFar, &paraFit);

	llDataFileWrite(info.fptOut1, &llOutNea, &status);
	llDataFileWrite(info.fptOut2, &llOutFar, &status);
	llDataAxisSearchResultWrite(info, paraFit);
	if(info.flagAvg) {
		llAvg = llInNea; llDataInit(&llAvg); lllDataAttributeCopy(&llAvg, &llInNea);
		lllDataSideSet(&llAvg, AverageSide);
		lllDataClear(&llAvg);
		lllDataAdd(&llAvg, &llOutNea);
		lllDataAdd(&llAvg, &llOutFar);
		lllDataDevidedByReal(&llAvg, 2.0);
		llDataFileWrite(info.fptAvg, &llAvg, &status);
	}
	exit(EXIT_SUCCESS);
}

void 
llDataAxisSearchResultWrite(llDataAxisSearchInfo info, llDataFittedParam paraFit)
{
	fprintf(info.fptOut, "%s %s %f %f %f\n", 
			info.In1, info.In2, paraFit.Para.R*DEGREE, paraFit.Para.x.Value, paraFit.Para.Omega.Value);
	fprintf(stderr, "%s %s %f %f %f\n", 
			info.In1, info.In2, paraFit.Para.R*DEGREE, paraFit.Para.x.Value, paraFit.Para.Omega.Value);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Layer Line Information File ----- \n");
	fprintf(stderr, "L N Weight\n");
	fprintf(stderr, "..........\n");
	fprintf(stderr, "\n");
	configFileUsage(stderr);
}

#include <stdio.h>
#include "eosString.h"
#include "File.h"
void
configFileRead(FILE* fpt, llDataAxisSearchInfo* info)
{
    char s[1024];
    long i, j;
    fseek(fpt, 0L, SEEK_SET);
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagIn1) {
        info->In1 = stringGetNthWord(s, 1, " \t,");
        info->fptIn1 = fileOpen(info->In1, "r");
        info->flagIn1++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagIn2) {
        info->In2 = stringGetNthWord(s, 1, " \t,");
        info->fptIn2 = fileOpen(info->In2, "r");
        info->flagIn2++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagOut1) {
        info->Out1 = stringGetNthWord(s, 1, " \t,");
        info->fptOut1 = fileOpen(info->Out1, "w");
        info->flagOut1++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagOut2) {
        info->Out2 = stringGetNthWord(s, 1, " \t,");
        info->fptOut2 = fileOpen(info->Out2, "w");
        info->flagOut2++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagAvg) {
        info->Avg = stringGetNthWord(s, 1, " \t,");
        info->fptAvg = fileOpen(info->Avg, "w");
        info->flagAvg++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagOut) {
        info->Out = stringGetNthWord(s, 1, " \t,");
        info->fptOut = fileOpen(info->Out, "w");
        info->flagOut++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagtruePitch) {
        info->truePitch = stringGetNthRealData(s, 1, " \t,");
        info->flagtruePitch++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagL) {
        info->L = stringGetNthWord(s, 1, " \t,");
        info->fptL = fileOpen(info->L, "r");
        info->flagL++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagOmin) {
        info->Omin = stringGetNthRealData(s, 1, " \t,");
        info->flagOmin++;
    }
    
    if(!info->flagOmax) {
        info->Omax = stringGetNthRealData(s, 2, " \t,");
        info->flagOmax++;
    }
    
    if(!info->flagOdelta) {
        info->Odelta = stringGetNthRealData(s, 3, " \t,");
        info->flagOdelta++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagxmin) {
        info->xmin = stringGetNthRealData(s, 1, " \t,");
        info->flagxmin++;
    }
    
    if(!info->flagxmax) {
        info->xmax = stringGetNthRealData(s, 2, " \t,");
        info->flagxmax++;
    }
    
    if(!info->flagxdelta) {
        info->xdelta = stringGetNthRealData(s, 3, " \t,");
        info->flagxdelta++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagR) {
        info->R = stringGetNthRealData(s, 1, " \t,");
        info->flagR++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!info->flagmode) {
        info->mode = stringGetNthIntegerData(s, 1, " \t,");
        info->flagmode++;
    }
    
}
#include <stdio.h>
#include "eosString.h"
#include "File.h"
void
configFileUsage(FILE* fpt)
{
    fprintf(fpt, "----- Control File -----\n");
    fprintf(fpt, "In1[inFile:NULL]\t\t\t\t#In: NearSide\n");
    fprintf(fpt, "In2[inFile:NULL]\t\t\t\t#In: FarSide\n");
    fprintf(fpt, "Out1[outFile:NULL]\t\t\t\t#Out: NearSide\n");
    fprintf(fpt, "Out2[outFile:NULL]\t\t\t\t#Out: FarSide\n");
    fprintf(fpt, "Avg[outFile:NULL]\t\t\t\t#Out: Average\n");
    fprintf(fpt, "Out[outFile:NULL]\t\t\t\t#Out: FitParam\n");
    fprintf(fpt, "truePitch[Real:NULL]\t\t\t\t#TruePitch[A]\n");
    fprintf(fpt, "L[inFile:NULL]\t\t\t\t#LayerInfo\n");
    fprintf(fpt, "Omin[Real:0.0]\tOmax[Real:0.0]\tOdelta[Real:1.0]\t\t\t\t#Omega[degree]\n");
    fprintf(fpt, "xmin[Real:-10.0]\txmax[Real:10.0]\txdelta[Real:0.1]\t\t\t\t#shiftx[A]\n");
    fprintf(fpt, "R[Real:10.0]\t\t\t\t#Resolution[A]\n");
    fprintf(fpt, "mode[Integer:0]\t\t\t\t#Mode\n");
    fprintf(fpt, "----- Inside Axis Search Parameter File -----\n");
	fprintf(fpt, "info.In1, info.In2, paraFit.Para.R*DEGREE, paraFit.Para.x.Value, paraFit.Para.Omega.Value\n");
}
