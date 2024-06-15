#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/gifFile.h"

void
gifFileWrite(FILE* fpt, gifFile* gif, char* message, long mode) 
{
	long i, j;
	long ncol;

	fseek(fpt, 0L, SEEK_SET);
	fwrite(&(gif->Header),  sizeof(gifFileHeader),     1, fpt);
	fwrite(&(gif->ScrDesc), sizeof(gifFileScreenDesc), 1, fpt);
	if((scdGCT&gif->ScrDesc.flags)==scdGCT) {
		ncol = pow(2, (scdGCTsize&gif->ScrDesc.flags) + 1);
		for(i=0; i<ncol; i++) {
			fwrite(&(gif->GCT[i]), sizeof(gifFileColorTable), 1, fpt);
		}
	}
	for(i=0; i<gif->nImage; i++) {
		fwrite(&(gif->ImageDef[i].Desc), sizeof(gifFileImageDesc), 1, fpt);
		if((imdLCT&gif->ImageDef[i].Desc.flags)==imdLCT) {
			ncol = pow(2, (imdLCTsize&gif->ScrDesc.flags) + 1);
			for(j=0; j<ncol; j++) {
				fwrite(&(gif->ImageDef[i].LCT[j]), sizeof(gifFileColorTable), 1, fpt);
			}
		}
	}
}
