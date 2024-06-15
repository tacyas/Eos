/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbTempFactorSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbTempFactorSet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbTempFactorSet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "pdbFile.h"

typedef struct lpdbTempFactorSetInfo {
	pdbFileParaTypeInteger ResidueSequenceNumber;
	pdbFileParaTypeReal    TemparatureFactor;
} lpdbTempFactorSetInfo;

/*
typedef enum lpdbTempFactorSetMode {

} lpdbTempFactorSetMode;
*/

extern int lpdbTempFactorTableGet(FILE* fpt, lpdbTempFactorSetInfo* info, int mode);
extern void lpdbTempFactorSet(pdbFile* pdb, lpdbTempFactorSetInfo* info, int mode);

int
main(int argc, char* argv[]) 
{
	pdbTempFactorSetInfo   info;
	lpdbTempFactorSetInfo linfo;
	pdbFile pdb;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	
	pdbFileRead(info.fptIn, &pdb);	

	while(0!=lpdbTempFactorTableGet(info.fptRef, &linfo, 0)) {
		lpdbTempFactorSet(&pdb, &linfo, 0);
	}
	
	pdbFileWrite(info.fptOut, &pdb);	

	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

int
lpdbTempFactorTableGet(FILE* fpt, lpdbTempFactorSetInfo* info, int mode)
{
	char s[1024];
	String stmp;
	String selection;

	stmp = stringGetFromFile(s, "", fpt, stdout, 3);
	if(0==stmp) {
		return 0;	
	} else {
		selection = stringGetNthWord(s, 1, " ,\t");
		info->ResidueSequenceNumber = atoi(selection);
		info->TemparatureFactor     = stringGetNthRealData(s, 2, " ,\t");
	}
	return 1;	
}

void
lpdbTempFactorSet(pdbFile* pdb, lpdbTempFactorSetInfo* info, int mode)
{
	pdbRecord* tmp;
	tmp = pdb->PDB;
	pdbFileTop(pdb);
	do {
		if(pdbFileIsAtom(pdb)) {
			if(pdb->PDB->ResidueSequenceNumber==info->ResidueSequenceNumber) { 
				pdbFileTemperatureFactorSet(pdb, info->TemparatureFactor);
			}
		}
	} while(NULL!=pdbFileNext(pdb));

	pdb->PDB = tmp;
}

