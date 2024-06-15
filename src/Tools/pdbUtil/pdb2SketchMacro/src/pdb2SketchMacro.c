/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdb2SketchMacro ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdb2SketchMacro
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdb2SketchMacro ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"

typedef enum lpdb2SketchMacroInfoMode {
	lpdb2SketchMacroInfoModeHelix = 1,
	lpdb2SketchMacroInfoModeSheet = 2,
	lpdb2SketchMacroInfoModeTurn  = 4, 
	lpdb2SketchMacroInfoModeNo    = 8 
}lpdb2SketchMacroInfoMode; 

extern void lpdb2SketchMacroInfo(FILE* fpt, pdbFile* pdb, char* filename, char* molname, int mode);

int
main(int argc, char* argv[]) 
{
	pdb2SketchMacroInfo info;
	pdbFile pdb;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptIn, &pdb);
	pdbNoSecondaryStructureSetFromPDB(&pdb, &(pdb.second));
	lpdb2SketchMacroInfo(info.fptOut, &pdb, info.In, info.MolName, info.mode);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">>>> -m \n");
	fprintf(stderr, "  %d : Helix sketched with spirals \n", lpdb2SketchMacroInfoModeHelix);
	fprintf(stderr, "  %d : Sheet sketched with arrows  \n", lpdb2SketchMacroInfoModeSheet);
	fprintf(stderr, "  %d : Turn  sketched with rattler \n", lpdb2SketchMacroInfoModeTurn);
	fprintf(stderr, "  %d : No structure sketched with rattler \n", lpdb2SketchMacroInfoModeNo);

}

void
lpdb2SketchMacroInfo(FILE* fpt, pdbFile* pdb, char* filename, char* MolName,  int mode)
{
	int i;
	char s[4];
	int flag;

	fprintf(fpt, "sam_atom_in %s %3s\n", filename, MolName); 
	if(lpdb2SketchMacroInfoModeHelix&mode) {
		pdb->second.SecondaryStructure = pdb->second.top;	
		while(1) {
			if(pdbFileSecondaryStructureModeHelix==pdb->second.SecondaryStructure->mode) {
				for(i=0; i<4; i++) {
					if(pdb->second.SecondaryStructure->helix->helixID[i]==' ') {
						s[i] = '_';
					} else {
						s[i] = pdb->second.SecondaryStructure->helix->helixID[i];
					}
				}
				fprintf(fpt, "sketch_object %2sH%-3s\n", MolName, s);
				fprintf(fpt, "sketch_setup  Spiral solid 2.5 0.5 0.5 2 7 3 2\n");
				fprintf(fpt, "sketch_type   Spiral\n");
				fprintf(fpt, "paint_zone %2s %c%-3d %c%-3d red\n", 
					MolName,
					pdb->second.SecondaryStructure->helix->initChainID, pdb->second.SecondaryStructure->helix->initSeqNum,
					pdb->second.SecondaryStructure->helix->endChainID,  pdb->second.SecondaryStructure->helix->endSeqNum
					);
				fprintf(fpt, "sketch_add    %2s %c%-3d %c%-3d\n", 
					MolName,
					pdb->second.SecondaryStructure->helix->initChainID, pdb->second.SecondaryStructure->helix->initSeqNum,
					pdb->second.SecondaryStructure->helix->endChainID,  pdb->second.SecondaryStructure->helix->endSeqNum
					);
				fprintf(fpt, "end_object\n");
			}
			if(NULL!=pdb->second.SecondaryStructure->next) {
				pdb->second.SecondaryStructure = pdb->second.SecondaryStructure->next;
			} else {
				break;
			}
		}
	}
	if(lpdb2SketchMacroInfoModeSheet&mode) {
		pdb->second.SecondaryStructure = pdb->second.top;	
		flag = 0;
		while(1) {
			if(pdbFileSecondaryStructureModeSheet==pdb->second.SecondaryStructure->mode) {
				/* Sheet Start */
				if(NULL!=pdb->second.SecondaryStructure->prev) {
					if(NULL==pdb->second.SecondaryStructure->prev->sheet) {
						flag = 1;
					} else if(0!=strncmp(pdb->second.SecondaryStructure->prev->sheet->sheetID, 
									  pdb->second.SecondaryStructure->sheet->sheetID, 3)) {
						flag = 1;	
					} else { /* The same sheet */
						flag = 2;
					}
				} else {
					flag = 1;
				}
				if(flag==1) {
					for(i=0; i<4; i++) {
						if(pdb->second.SecondaryStructure->sheet->sheetID[i]==' ') {
							s[i] = '_';
						} else {
							s[i] = pdb->second.SecondaryStructure->sheet->sheetID[i];
						}
					}
					fprintf(fpt, "sketch_object %2sS%-3s\n", MolName, s);
					fprintf(fpt, "sketch_setup  Arrow solid 2.5 0.5 3.75 2 7 3 2\n");
					fprintf(fpt, "sketch_type   Arrow \n");
					flag = 2;
				}
				fprintf(fpt, "paint_zone %2s %c%-3d %c%-3d blue\n", 
					MolName,
					pdb->second.SecondaryStructure->sheet->initChainID, pdb->second.SecondaryStructure->sheet->initSeqNum,
					pdb->second.SecondaryStructure->sheet->endChainID,  pdb->second.SecondaryStructure->sheet->endSeqNum
					);
				fprintf(fpt, "sketch_add    %2s %c%-3d %c%-3d\n", 
					MolName,
					pdb->second.SecondaryStructure->sheet->initChainID, pdb->second.SecondaryStructure->sheet->initSeqNum,
					pdb->second.SecondaryStructure->sheet->endChainID,  pdb->second.SecondaryStructure->sheet->endSeqNum
					);

				if(NULL!=pdb->second.SecondaryStructure->next) {
				if(NULL!=pdb->second.SecondaryStructure->next->sheet) {
				if(0!=strncmp(pdb->second.SecondaryStructure->next->sheet->sheetID,
						  	  pdb->second.SecondaryStructure->sheet->sheetID, 
							  3)) {				
					flag = 0;
					fprintf(fpt, "end_oject\n");
				}	
				} else {
					flag = 0;
					fprintf(fpt, "end_oject\n");
				}
				} else {
					flag = 0;
					fprintf(fpt, "end_oject\n");
				}
			}
			if(NULL!=pdb->second.SecondaryStructure->next) {
				pdb->second.SecondaryStructure = pdb->second.SecondaryStructure->next;
			} else {
				break;
			}
		}
	}
	if(lpdb2SketchMacroInfoModeTurn&mode) {
		pdb->second.SecondaryStructure = pdb->second.top;
		while(1) {
			if(pdbFileSecondaryStructureModeTurn==pdb->second.SecondaryStructure->mode) {
				for(i=0; i<4; i++) {
					if(pdb->second.SecondaryStructure->turn->turnID[i]==' ') {
						s[i] = '_';
					} else {
						s[i] = pdb->second.SecondaryStructure->turn->turnID[i];
					}
				}
				fprintf(fpt, "sketch_object %2sT%-3s\n", MolName, s);
				fprintf(fpt, "sketch_setup  Rattler solid 0.5 7 2\n");
				fprintf(fpt, "sketch_type   Rattler \n");
				fprintf(fpt, "paint_zone %2s %c%-3d %c%-3d yellow\n", 
					MolName,
					pdb->second.SecondaryStructure->turn->initChainID, pdb->second.SecondaryStructure->turn->initSeqNum,
					pdb->second.SecondaryStructure->turn->endChainID,  pdb->second.SecondaryStructure->turn->endSeqNum
					);
				fprintf(fpt, "sketch_add    %2s %c%-3d %c%-3d\n", 
					MolName,
					pdb->second.SecondaryStructure->turn->initChainID, pdb->second.SecondaryStructure->turn->initSeqNum,
					pdb->second.SecondaryStructure->turn->endChainID,  pdb->second.SecondaryStructure->turn->endSeqNum
					);
				fprintf(fpt, "end_object\n");
			}
			if(NULL!=pdb->second.SecondaryStructure->next) {
				pdb->second.SecondaryStructure = pdb->second.SecondaryStructure->next;
			} else {
				break;
			}
		}
	}
	if(lpdb2SketchMacroInfoModeNo&mode) {
		pdb->second.SecondaryStructure = pdb->second.top;
		while(1) {
			if(pdbFileSecondaryStructureModeNo==pdb->second.SecondaryStructure->mode) {
				for(i=0; i<4; i++) {
					if(pdb->second.SecondaryStructure->no->noID[i]==' ') {
						s[i] = '_';
					} else {
						s[i] = pdb->second.SecondaryStructure->no->noID[i];
					}
				}
				fprintf(fpt, "sketch_object %2sN%-3s\n", MolName, s);
				fprintf(fpt, "sketch_setup  Rattler solid 0.5 7 2\n");
				fprintf(fpt, "sketch_type   Rattler \n");
				fprintf(fpt, "paint_zone %2s %c%-3d %c%-3d white\n", 
					MolName,
					pdb->second.SecondaryStructure->no->initChainID, pdb->second.SecondaryStructure->no->initSeqNum,
					pdb->second.SecondaryStructure->no->endChainID,  pdb->second.SecondaryStructure->no->endSeqNum
					);
				fprintf(fpt, "sketch_add    %2s %c%-3d %c%-3d\n", 
					MolName,
					pdb->second.SecondaryStructure->no->initChainID, pdb->second.SecondaryStructure->no->initSeqNum,
					pdb->second.SecondaryStructure->no->endChainID,  pdb->second.SecondaryStructure->no->endSeqNum
					);
				fprintf(fpt, "end_object\n");
			}
			if(NULL!=pdb->second.SecondaryStructure->next) {
				pdb->second.SecondaryStructure = pdb->second.SecondaryStructure->next;
			} else {
				break;
			}
		}
	}
}

