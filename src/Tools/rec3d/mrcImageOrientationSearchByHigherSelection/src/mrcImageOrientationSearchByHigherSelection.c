/*
# mrcImageOrientationSearchByHigherSelection : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageOrientationSearchByHigherSelection
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#define WORDLEN 256
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"

typedef struct InputData{
	double LminAve;
	char*  FileName;
}InputData;

typedef struct lmrcImageOrientationSearchByHigherSelectionInfo {
	int SelectNum;
	int FileNum;

	InputData* input;
} lmrcImageOrientationSearchByHigherSelectionInfo;

/*
typedef enum lmrcImageOrientationSearchByHigherSelectionMode {
	a=0,
	b=1
} lmrcImageOrientationSearchByHigherSelectionMode;
*/

void
__InputFileRead(lmrcImageOrientationSearchByHigherSelectionInfo* linfo, FILE* fpt, int mode);

void
lmrcImageOrientationSearchByHigherSelection(lmrcImageOrientationSearchByHigherSelectionInfo* linfo, int mode);

extern int
cmp(const InputData* a, const InputData* b);

void
__ResultFileWrite(lmrcImageOrientationSearchByHigherSelectionInfo* linfo, FILE* fpt, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageOrientationSearchByHigherSelectionInfo  info;
	lmrcImageOrientationSearchByHigherSelectionInfo linfo;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.SelectNum     = info.n;
	linfo.FileNum = info.flagIn;
	linfo.input = MemoryAllocate(InputData, linfo.FileNum, "in main");
	for(i=0; i<linfo.FileNum; i++){
		linfo.input[i].FileName = MemoryAllocate(char, WORDLEN, "in main");
		strcpy(linfo.input[i].FileName, info.In[i]);
	}

	DEBUGPRINT("Program Start\n");
	__InputFileRead(&linfo, info.fptInList, 0);
	lmrcImageOrientationSearchByHigherSelection(&linfo, 0);
	__ResultFileWrite(&linfo, info.fptOut, 0);
	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- Input file format -----\n");
	fprintf(stderr, "filename LminAve\n");
	fprintf(stderr, "   .        .   \n");
	fprintf(stderr, "   .        .   \n");
	fprintf(stderr, "   .        .   \n");
	fprintf(stderr, "   .        .   \n");
	fprintf(stderr, "\n");
}

void
__InputFileRead(lmrcImageOrientationSearchByHigherSelectionInfo* linfo, FILE* fpt, int mode)
{
	int   i;
	char* s;

	s = MemoryAllocate(char, WORDLEN, "in __InputFileRead");
	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<linfo->FileNum; i++){
		stringGetFromFile(s, "", fpt, stdout, 3);
		linfo->input[i].LminAve = (double)stringGetNthRealData(s, 2, " ,\t");
	}
	fclose(fpt);
}

void
lmrcImageOrientationSearchByHigherSelection(lmrcImageOrientationSearchByHigherSelectionInfo* linfo, int mode)
{
	qsort(linfo->input, linfo->FileNum, sizeof(InputData), cmp);
}

void
__ResultFileWrite(lmrcImageOrientationSearchByHigherSelectionInfo* linfo, FILE* fpt, int mode)
{
	int i;

	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<linfo->SelectNum; i++){
		fprintf(fpt, "%s\n", linfo->input[i].FileName);
	}
}

extern int
cmp(const InputData* a, const InputData* b)
{
	double differential;
	int    value;

	differential = a->LminAve - b->LminAve;
	if(differential == 0){
		value = 0;
	}
	else if(differential > 0){
		value = 1;
	}
	else{
		value = -1;
	}
	return(value);
}
