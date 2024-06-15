/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% hf2000Read ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : hf2000Read 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%hf2000Read ver%I%; Date:%D% %Z%";
#include <unistd.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/hf2000.h"

void
hf2000Read(hf2000Info* info, char* s)
{
	int res;

	DEBUGPRINT("hf2000Read\n");
	s[0] = '\0';
	res = read(info->fd, s, 255); 
	if(res<0) {
		perror("hf2000Read");
	}
	if(s[res-1] == '\n') {
		s[res-1] = '\0';
		DEBUGPRINT1("%s\n", s);
	} else {
		fprintf(stderr, "Something wrong in hf2000Read: %d %c\n", s[res-1], s[res-1]);
		s[res-1] = '\0';
		DEBUGPRINT1("%s\n", s);
	}
}

