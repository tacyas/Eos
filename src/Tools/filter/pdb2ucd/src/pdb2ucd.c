/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdb2ucd ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdb2ucd
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdb2ucd ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "avsFile.h"
/*
Example:
typedef struct lpdb2ucd {
	float a;
	int   b;
} lpdb2ucd;

typedef enum lpdb2ucdMode {
	a=0,
	b=1
} lpdb2ucdMode;
*/

extern void lpdb2avsFileUCD(avsFileUCD* avs, pdbFile* pdb, long mode);
int
main(int argc, char* argv[]) 
{
	avsFileUCD avs;
	pdbFile pdb;
	pdb2ucdInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptIn, &pdb);

	DEBUGPRINT("lpdb2avsFileUCD\n");
	lpdb2avsFileUCD(&avs, &pdb, info.mode);

	DEBUGPRINT("avsFileUCDWrite\n");
	avsFileUCDWrite(&avs, info.fptOut, 0);  
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
lpdb2avsFileUCD(avsFileUCD* avs, pdbFile* pdb, long mode)
{
	pdbFile pdbCA;
	int iNode, iCell;
	char orgChainID;
	char newChainID;
	int  orgResNum;
	int  newResNum;
	double data;
	pdbFileParaTypeReal x, y, z;

	DEBUGPRINT("pdbFIleCAOnlyCopyAll\n");
	pdbFileCAOnlyCopyAll(&pdbCA, pdb);

	DEBUGPRINT("avsFileUCD Init\n");
	avs->nNode  = pdbCA.nAtom;
	avs->nCell  = avs->nNode - 1;	
	avs->nModel = 0;
	avs->nNodeComponent = 4;
	avs->nCellComponent = 0;

	DEBUGPRINT("avsFileUCDInit--");
	avsFileUCDInit(avs, 0);

	DEBUGPRINT("avsFileUCDNodeComponentInit--");
	avsFileUCDNodeComponentInit(avs, 0, 1, "TemperatureFactor", "A2", 0);
	avsFileUCDNodeComponentInit(avs, 1, 1, "ChainID", "", 0);
	avsFileUCDNodeComponentInit(avs, 2, 1, "ResNum", "", 0);
	avsFileUCDNodeComponentInit(avs, 3, 1, "CA", "", 0);

	/*
	avsFileUCDCellComponentInit(avs, 0, 0, "Unknown", "Unknown", 0);
	*/
	DEBUGPRINT2("%s %s\n", avs->NodeComponent[0].Label, avs->NodeComponent[0].Unit);

	pdbFileTop(&pdbCA);
	iCell=0;
	iNode=0;
	orgChainID = pdbFileChainIdentifierGet(&pdbCA);
    orgResNum  = pdbCA.PDB->ResidueSequenceNumber; 	
	pdbFileCoordGet(&pdbCA, &x, &y, &z);
	DEBUGPRINT3("(%f, %f, %f)\n", x, y, z);
	avsFileUCDNodeSet(avs, iNode, x, y, z);
	avsFileUCDNodeDataSet(avs, iNode, 0, 0, pdbFileTemperatureFactorGet(&pdbCA));
	avsFileUCDNodeDataSet(avs, iNode, 1, 0, pdbFileChainIdentifierGet(&pdbCA));
	avsFileUCDNodeDataSet(avs, iNode, 2, 0, pdbCA.PDB->ResidueSequenceNumber);
	avsFileUCDNodeDataSet(avs, iNode, 3, 0, 1); 
	pdbFileNext(&pdbCA);
	for(iNode=1; iNode<avs->nNode; iNode++) {
		pdbFileCoordGet(&pdbCA, &x, &y, &z);
		avsFileUCDNodeSet(avs, iNode, x, y, z);
		avsFileUCDNodeDataSet(avs, iNode, 0, 0, pdbFileTemperatureFactorGet(&pdbCA));
		avsFileUCDNodeDataSet(avs, iNode, 1, 0, pdbFileChainIdentifierGet(&pdbCA));
		avsFileUCDNodeDataSet(avs, iNode, 2, 0, pdbCA.PDB->ResidueSequenceNumber);
		avsFileUCDNodeDataSet(avs, iNode, 3, 0, 1);
		newChainID = pdbFileChainIdentifierGet(&pdbCA);
    	newResNum  = pdbCA.PDB->ResidueSequenceNumber; 	
		if(orgChainID==newChainID && orgResNum+1==newResNum) {
			avsFileUCDLineTypeCellSet(avs, iCell, 1, &(avs->Node[iNode-1]), &(avs->Node[iNode]));
			iCell++;
		} 
		orgChainID = newChainID;
		orgResNum  = newResNum;
		pdbFileNext(&pdbCA);
	}
	avs->nCell = iCell;
}
