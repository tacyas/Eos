#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../inc/config.h"
#include "ltlgData.h"

void
main(int argc, char* argv[]) 
{
    ltlgData ltlg;
	ltlgDataInfoInfo info;
    ltlgDataParaTypeInteger status;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
    ltlgDataReadFile(info.fptIn, &ltlg, 0, &status);
    ltlgDataPrint(info.fptOut, ltlg, info.mode);
}

void
additionalUsage()
{
    fprintf(stderr, "----- mode -----\n");
    fprintf(stderr, " 1: Header Information\n");
	fprintf(stderr, " 2: (N, L) Information\n");
	fprintf(stderr, " 4: (N, L) Data       \n");

}
