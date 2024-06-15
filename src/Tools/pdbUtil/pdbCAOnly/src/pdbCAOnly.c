#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "pdbFile.h"

void
main(int argc, char* argv[]) 
{
	long status;
	pdbCAOnlyInfo info;
	pdbFile pdbIn;
	pdbFile pdbOut;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	pdbFileRead(info.fptIn, &pdbIn);
	pdbFileCAOnlyCopyAll(&pdbOut, &pdbIn);
	if(info.flagOut) {
		pdbFileWrite(info.fptOut, &pdbOut);
	}
	if(info.flagOutCoord) {
		pdbFileWriteCoord(info.fptOutCoord, &pdbOut);
	}
}

void
additionalUsage()
{
}
