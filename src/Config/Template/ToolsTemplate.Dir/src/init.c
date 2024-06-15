#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../inc/config.h"
#include "genUtil.h"
#include "String.h"
#include "File.h"


void
init0(THIS_PROGRAM\
Info* info)
{
	info->inFileName[0]   = '\0'; info->fptIn   = NULL;   info->flagInFile   = 0;
	info->outFileName[0]  = '\0'; info->fptOut  = stdout; info->flagOutFile  = 0;
	info->layer = -1;
	info->mode  = DEFAULT_MODE;
}

void
init1(THIS_PROGRAM\
Info* info)
{
	char s[100];

	if(!info->flagInFile) {
		stringGetFromFile(info->inFileName, "mrcInputFileName", stdin, stdout, 0);
	}
	info->fptIn = fileOpen(info->inFileName, "r");
	if(info->flagOutFile) {
		info->fptOut = fileOpen(info->outFileName, "w");
	}
}
