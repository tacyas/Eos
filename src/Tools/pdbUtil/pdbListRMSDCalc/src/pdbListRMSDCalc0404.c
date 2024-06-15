/*
# pdbListRMSDCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : pdbListRMSDCalc
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
#include "genUtil.h"
#include "pdbFile.h"

/*
Example:
typedef struct lpdbListRMSDCalcInfo {
	float a;
	int   b;
} lpdbListRMSDCalcInfo;

typedef enum lpdbListRMSDCalcMode {
	a=0,
	b=1
} lpdbListRMSDCalcMode;
*/

int
main(int argc, char* argv[]) 
{
	pdbListRMSDCalcInfo info;
	pdbFile* pdbArray;
	pdbFile* pdbRMSD;
	int n=0;
	init0(&info);
	argCheck(&info, argc, argv);
  	init1(&info);
	
	info.fptIn=fileOpen(info.In, "r");
	lpdbFileListRead(info.fptIn, pdbArray, &n);
	lpdbRMSDCalc(pdbRMSD, pdbArray, n, &linfo, info.mode);
	fclose(info.fptIn);

	info.fptOut=fileOpen(info.Out, "w")
	pdbFileWrite(info.fptOut, pdbRMSD);
	fclose(info.fptOut);

	DEBUGPRINT("Program Start\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
void lpdbFileListRead(File* List, pdbFile* pdbArray, int* n)
{
	FILE* ListfptIn;
	char listname[256];
	while(fgets(listname,256,List) == NULL){
	fprintf(stdout,"FILENAME:%s",listname);
	ListfptIn=fileOpen(listname, "r");	
	(pdbArray+n)= (pdbFile*)malloc(sizeof(pdbFile));
	pdbFileRead(ListfptIn, pdbArray+n);
	fclose(Listname);
	n++;
	}
}
void lpdbRMSDCalc(pdbFile* pdbRMSD, pdbFile* pdbArray, int n, lpdbRMSDCalcInfo* linfo, int mode)
{
	int i;
	int an;
	int max;
	max=pdbArray->nAtom;
	pdbCoord ATOMsum[max];
	pdbFileParaTypeReal RMSD[max];

	for(i=0;i<max;i++){
		ATOMsum[i]=0;
	}

	fprintf(stdout, "Average and RMSD Calculation Start ---- \n");
	for(i=0;i<n;i++){
		an=0;
		(pdbArray+i)->PDB=(pdbArray+i)->top;
		while(NULL!=(pdbArray+i)->PDB){
			if(strncmp((pdbList+i)->PDB->Record, "ATOM  ", 6)==0 || strncmp((pdbList+i)->PDB->Record, "HETATM", 6)==0){
				ATOMsum[an].x+=(pdbList+i)->PDB->Coord.x;
				ATOMsum[an].y+=(pdbList+i)->PDB->Coord.y;
				ATOMsum[an].z+=(pdbList+i)->PDB->Coord.z;			
			}
			(pdbArray+i)->PDB=(pdbArray+i)->PDB->next;
			an++;
		}
	}
	pdbRMSD=(pdbArray+0);
	an=0;
	pdbRMSD->PDB=pdbRMSD->top;
	while(NULL!=pdbRMSD->PDB){
		if(strncmp(pdbRMSD->PDB->Record, "ATOM  ", 6)==0 || strncmp(pdbRMSD->PDB->Record, "HETATM", 6)==0){
			pdbRMSD->PDB->Coord.x=ATOMsum[an].x/n;
			pdbRMSD->PDB->Coord.y=ATOMsum[an].y/n;
			pdbRMSD->PDB->Coord.z=ATOMsum[an].z/n;
			if(strncmp(pdbRMSD->PDB->Record, "ATOM  ", 6)==0)
			{
				pdbRMSD->PDB->TemperatureFactor=ATOMsum[an].x/n;
			}			
		}
	pdbRMSD->PDB=pdbRMSD->PDB->next;
	an++;
	}

}

