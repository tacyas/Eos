#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

int
main(int argc, char* argv[]) 
{
	long status;
	mrcInfoInfo info;
	mrcImage mrc;


	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("mrcFileRead\n");
	mrcHeaderReadGeneral(&mrc, info.In, info.InType, "in main", 0);
	mrcHiddenDataSet(&mrc, 0);
	mrcTailerReadGeneral(&mrc, info.In, info.InType, "in main", 0);

	DEBUGPRINT("mrcInfoPrint\n");
	mrcInfoPrint(info.fptOut, &mrc, info.mode);

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "-mode\n ");
	fprintf(stderr, " +16: one line Tailer information \n ");
	fprintf(stderr, ">> MRC Mode\n ");
	mrcFileGeneralListPrint(stderr);
}
