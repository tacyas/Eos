/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfInfoRead ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfInfoRead 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfInfoRead ver%I%; Date:%D% %Z%";
#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "../inc/ctfInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
ctfInfoRead(FILE* fpt, ctfInfo* ctf, char* head, int mode)
{
	char s[STRING_MAX_LENGTH];
	char* label;
	char* headlabel;
	static int METcounter = 0;

	ctf->flagAstigmatism = 0;
	while(NULL!=stringGetFromFile(s, "", fpt, stdout, 3)) {
		label     = stringGetNthWord(s, 1, ": ,\t");	
		if(NULL==label) {
			fprintf(stderr, "skip\n");	
		} else {
			headlabel = strdup(label);
			headlabel[strlen(head)] = '\0'; 	
			DEBUGPRINT2("%s %s\n", label, headlabel);
			if(0==strncmp(head, headlabel, sizeof(head))) {
			SSWITCH(label+strlen(head)) 
				SCASE("I") {
					ctf->I0 = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("defocus") {
					ctf->defocus = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("defocus2D0") {
					ctf->defocus2D[0] = stringGetNthRealData(s, 2, ": ,\t");
					ctf->flagAstigmatism = 1;
					SBREAK;
				}
				SCASE("defocus2D1") {
					ctf->defocus2D[1] = stringGetNthRealData(s, 2, ": ,\t");
					ctf->flagAstigmatism = 1;
					SBREAK;
				}
				SCASE("defocus0axis") {
					ctf->defocus0axis = stringGetNthRealData(s, 2, ": ,\t");
					ctf->flagAstigmatism = 1;
					SBREAK;
				}
				SCASE("kV") {
					ctf->kV = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("AoverP") {
					ctf->ratioOfAmpToPhase = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("Cs") {
					ctf->Cs = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("Cc") {
					ctf->Cc = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("dE") {
					ctf->dE = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("Ai") {
					ctf->Ain = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("MTF") {
					ctf->BofMTF = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("MTF2") {
					ctf->BofMTF2 = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("BofVibration") {
					ctf->BofVibration = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("SN") {
					ctf->WhiteNoise = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("SN2") {
					ctf->WhiteNoise2 = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("Isignal") {
					ctf->Isignal = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("Inoise") {
					ctf->Inoise = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("Inoise2") {
					ctf->Inoise2 = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("Magnification") {
					ctf->Magnification = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("CutLow") {
					ctf->CutLow = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("CutHigh") {
					ctf->CutHigh = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("flagMolecEnvTable") {
					ctf->flagMolecEnvTable = stringGetNthIntegerData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("MolecEnv") {
					ctf->MolecEnv = stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("NyquistFrequency") {
					ctf->NyquistFrequency= stringGetNthRealData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("flagAliasing") {
					ctf->flagAliasing = stringGetNthIntegerData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("flagSampling") {
					ctf->flagSampling = stringGetNthIntegerData(s, 2, ": ,\t");
					SBREAK;
				}
				SCASE("MET-File") {
					if(ctf->flagMolecEnvTable==1) {
						FILE* fpt;
						ctf->MolecEnvTable.filename = stringGetNthWord(s, 2, ": ,\t");
						fpt = fopen(ctf->MolecEnvTable.filename, "r");
						if(fpt==NULL) {
							fprintf(stderr, "MolecEnvTable cannot be read: %s\n", ctf->MolecEnvTable.filename); 
						} else {
							lmolecularEnvelopeFileRead(fpt, &(ctf->MolecEnvTable), 0); 
						}
					} else {
						fprintf(stderr, "flagMolecEnvTable is %d.  Therefore, MET-File (%s) is ignored\n", ctf->flagMolecEnvTable, ctf->MolecEnvTable.filename); 
					}
					SBREAK;
				}
				SCASE("MET-nR") {
					if(ctf->flagMolecEnvTable==2) {
						ctf->MolecEnvTable.nR       = stringGetNthIntegerData(s, 2, ": ,\t");
						ctf->MolecEnvTable.R        = memoryAllocate(sizeof(float)*ctf->MolecEnvTable.nR, "");
						ctf->MolecEnvTable.Envelope = memoryAllocate(sizeof(float)*ctf->MolecEnvTable.nR, "");
						METcounter = 0;
					} else {
						fprintf(stderr, "flagMolecEnvTable is %d.  Therefore, MET-nR (%d) is ignored\n", ctf->flagMolecEnvTable, ctf->MolecEnvTable.nR); 
					}
					SBREAK;
				}
				SCASE("MET-mode") {
					if(ctf->flagMolecEnvTable==2) {
						ctf->MolecEnvTable.mode = stringGetNthIntegerData(s, 2, ": ,\t");
					} else {
						fprintf(stderr, "flagMolecEnvTable is %d.  Therefore, MET-mode (%d) is ignored\n", ctf->flagMolecEnvTable, ctf->MolecEnvTable.mode); 
					}
					SBREAK;
				}
				SCASE("MET-Table") {
					if(ctf->flagMolecEnvTable==2) {
						ctf->MolecEnvTable.R[METcounter]        = stringGetNthRealData(s, 2, ": ,\t");
						ctf->MolecEnvTable.Envelope[METcounter] = stringGetNthRealData(s, 3, ": ,\t");
						METcounter++;
					} else {
						fprintf(stderr, "flagMolecEnvTable is %d.  Therefore, MET-Table is ignored\n", ctf->flagMolecEnvTable); 
					}
					SBREAK;
				}
			SSWITCHEND;
		}
		}
			
	}
}
