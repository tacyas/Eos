/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% hf2000Write ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : hf2000Write 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%hf2000Write ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include "../inc/hf2000.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void
hf2000Write(hf2000Info* info, char* s)
{
	char* stmp;
	int res;
	int res0;

	stmp = strdup(s);
	res = strlen(stmp);
	DEBUGPRINT2("in hf2000Write %s: %d\n", stmp, res)

	if(stmp[res] == '\0') {
		stmp[res] = '\r';
	} else {
		stmp[res] = '\r';
		fprintf(stderr, "Something wrong in hf2000Write : last is not NULL, %s <- %s \n", stmp, s);
	}
	res0 = write(info->fd, stmp, res+1);

	if(res0 != (res+1)) {
		fprintf(stderr, "Something wrong in  hf2000Write : after write, size is different: %d != %d\n", res0, res+1);
	}
	free(stmp);
}
