/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfInfoWrite ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfInfoWrite 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfInfoWrite ver%I%; Date:%D% %Z%";
#include "genUtil.h"
#include "eosString.h"
#include "../inc/ctfInfo.h"
#include <stdio.h>
#include <stdlib.h>

void
ctfInfoWrite(FILE* fpt, ctfInfo ctf, char* head, int mode)
{
	int i;

    fprintf(fpt, "%sI:             %15.6g\n", head, ctf.I0);
    fprintf(fpt, "%sIsignal:       %15.6g\n", head, ctf.I0);
    fprintf(fpt, "%sMagnification: %15.6g\n", head, ctf.Magnification);
    fprintf(fpt, "%sdefocus:       %15.6g\n", head, ctf.defocus);
    fprintf(fpt, "%sAoverP:        %15.6g\n", head, ctf.ratioOfAmpToPhase);
    fprintf(fpt, "%sCs:            %15.6g\n", head, ctf.Cs);
    fprintf(fpt, "%sCc:            %15.6g\n", head, ctf.Cc);
    fprintf(fpt, "%sdE:            %15.6g\n", head, ctf.dE);
    fprintf(fpt, "%sAi:            %15.6g\n", head, ctf.Ain);
    fprintf(fpt, "%sMTFMode:       %15d\n",   head, ctf.MTFMode);
    fprintf(fpt, "%sMTF:           %15.6g\n", head, ctf.BofMTF);
    fprintf(fpt, "%sMTF2:          %15.6g\n", head, ctf.BofMTF2);
    fprintf(fpt, "%sflagVibration: %15d\n", head, ctf.flagVibration);
    fprintf(fpt, "%sBofVibration:  %15.6g\n", head, ctf.BofVibration);
    fprintf(fpt, "%sflagSN:        %15d  \n", head, ctf.flagWhiteNoise);
    fprintf(fpt, "%sSN:            %15.6g\n", head, ctf.WhiteNoise);
    fprintf(fpt, "%sInoise:        %15.6g\n", head, ctf.I0*ctf.WhiteNoise);
    fprintf(fpt, "%sflagSN2:       %15d  \n", head, ctf.flagWhiteNoise2);
    fprintf(fpt, "%sSN2:           %15.6g\n", head, ctf.WhiteNoise2);
    fprintf(fpt, "%sInoise2:       %15.6g\n", head, ctf.I0*ctf.WhiteNoise2);
    fprintf(fpt, "%sNyquistFrequency: %15.6g\n", head, ctf.NyquistFrequency);
    fprintf(fpt, "%sflagAliasing:  %15d\n", head, ctf.flagAliasing);
    fprintf(fpt, "%sflagSampling:  %15d\n", head, ctf.flagSampling);
    fprintf(fpt, "%sflagMolecEnvTable: %15d\n", head, ctf.flagMolecEnvTable);
	switch(ctf.flagMolecEnvTable) {
		case 0: { /* No Table */
    		fprintf(fpt, "%sMolecEnv:      %15.6g\n", head, ctf.MolecEnv);
			break;
		}
		case 1: { 
			fprintf(fpt, "%sMET-File:      %s\n", head, ctf.MolecEnvTable.filename);
			break;
		}
		case 2: {	
    		fprintf(fpt, "%sMET-nR:        %15d\n",   head, ctf.MolecEnvTable.nR);
    		fprintf(fpt, "%sMET-mode:      %15d\n",   head, ctf.MolecEnvTable.mode);
			for(i=0; i<ctf.MolecEnvTable.nR; i++) {
				fprintf(fpt, "%sMET-Table: %15.6g %15.6g\n", head, ctf.MolecEnvTable.R[i], ctf.MolecEnvTable.Envelope[i]);
			}
			break;
		}
		default: {
			break;
		}
	}
    fprintf(fpt, "%sdefocus2D0:    %15.6g\n", head, ctf.defocus2D[0]);
    fprintf(fpt, "%sdefocus2D1:    %15.6g\n", head, ctf.defocus2D[1]);
    fprintf(fpt, "%sdefocus0axis:  %15.6g\n", head, ctf.defocus0axis);
    fprintf(fpt, "%skV:            %15.6g\n", head, ctf.kV);
    fprintf(fpt, "%sflagWin:       %15d  \n", head, ctf.flagWin);
    fprintf(fpt, "%sCutLow:        %15.6g\n", head, ctf.CutLow);
    fprintf(fpt, "%sCutHigh:       %15.6g\n", head, ctf.CutHigh);
}

