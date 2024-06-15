/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% hf2000Close ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : hf2000Close 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%hf2000Close ver%I%; Date:%D% %Z%";
#include "../inc/hf2000.h"

void
hf2000Close(hf2000Info* info)
{
	if(info->flagServer) {
		close(info->serverSocket);
		close(info->serverFD);
		tcsetattr(info->fd, TCSANOW, &(info->prevIO));
	} else if(info->flagClient) {
		close(info->fd);
	} else {
		tcsetattr(info->fd, TCSANOW, &(info->prevIO));
	}
}
