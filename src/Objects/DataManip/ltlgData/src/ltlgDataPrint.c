/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ltlgDataPrint ver %I%
#%Z% Created by tacyas/hashiba
#%Z%
#%Z% Usage : ltlgDataPrint 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ltlgDataPrint ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../inc/ltlgData.h"

#define PI     (3.141592653589793238)
#define DEGREE (180.0/PI)

void
ltlgDataPrintUsage(FILE* fpt, ltlgData ltlg)
{
	fprintf(fpt, " 1: Header Information\n");
	fprintf(fpt, " 2: (N, L) Information\n");
	fprintf(fpt, " 4: (N, L) Data       \n");
}

void
ltlgDataPrint(FILE* fpt, ltlgData ltlg, ltlgDataParaTypeInteger mode) 
{
    if((mode&0x0001)!=0) {
        ltlgDataPrintInfo(fpt, ltlg);
    }
    if((mode&0x0002)!=0) {
        ltlgDataPrintllInfo(fpt, ltlg);
    }
    if((mode&0x0004)!=0) {
        ltlgDataPrintllData(fpt, ltlg);
    }
}

void
ltlgDataPrintInfo(FILE* fpt, ltlgData ltlg)
{
    fprintf(fpt, "#### ltlgDataFile Information ####\n");
    fprintf(fpt, "TITLE1 : %80s\n", ltlg.title1);
    fprintf(fpt, "TITLE2 : %80s\n", ltlg.title2);
    fprintf(fpt, "SIDE   : %4s\n",  ltlg.side);
    fprintf(fpt, "dR[/A] : %15.6g\n", ltlg.R.d);
    fprintf(fpt, "llMax  : %15g\n",   ltlg.ll.Max);
    fprintf(fpt, "dr[A]  : %15.6g\n", ltlg.r.d);
    fprintf(fpt, "rMax[A]: %15.6g\n", ltlg.r.Max);
    fprintf(fpt, "nr     : %15d\n",   ltlg.r.n);
    fprintf(fpt, "##################################\n");
}

void
ltlgDataPrintllInfo(FILE* fpt, ltlgData ltlg)
{
    ltlgDataParaTypeInteger i;

    fprintf(fpt, "#### ltlgDataFile Layer Line Information ####\n");
    fprintf(fpt, "%10s) %5s %5s %15s\n", "LayerCount", "N","L","Weight");
    for(i=0; i<ltlg.ll.Max; i++) {
        fprintf(fpt, "%10d) %5d %5d %15.6g\n", i, ltlg.llInfo[i].NN, ltlg.llInfo[i].NL, ltlg.llInfo[i].WT);
    }
    fprintf(fpt, "#############################################\n");
}

void
ltlgDataPrintllData(FILE* fpt, ltlgData ltlg)
{
    ltlgDataParaTypeInteger i, j;
	ltlgDataParaTypeReal    r, data;

    fprintf(fpt, "#### ltlgDataFile Layer Line Data Information ####\n");
    for(i=0; i<ltlg.ll.Max; i++) {
        fprintf(fpt, "##################################################\n");
        fprintf(fpt, "%15s) %15s %15s %15s\n",  "LayerCount", "N",               "L",               "Weight");
        fprintf(fpt, "%15d) %15d %15d %15.6g\n", i,           ltlg.llInfo[i].NN, ltlg.llInfo[i].NL, ltlg.llInfo[i].WT);
        fprintf(fpt, "%15s) %15s %15s %15s %15s\n", "r", "Re", "Im", "Magitude", "Phase");
        for(j=0; j<ltlg.r.n; j++) {
			r = j*ltlg.r.d;	
            fprintf(fpt, "%15.6g) %15.6g %15.6g %15.6g %15.6g\n"
						 ,r 
						 ,ltlgDataGet2(&ltlg, i, r, &data, ltlgDataTypeRePart, ltlgDataHowNearest)  
						 ,ltlgDataGet2(&ltlg, i, r, &data, ltlgDataTypeImPart, ltlgDataHowNearest)  
						 ,ltlgDataGet2(&ltlg, i, r, &data, ltlgDataTypeMag,    ltlgDataHowNearest)  
						 ,ltlgDataGet2(&ltlg, i, r, &data, ltlgDataTypePhase,  ltlgDataHowNearest)*DEGREE);
        }
    }
    fprintf(fpt, "#################################################\n");
}

