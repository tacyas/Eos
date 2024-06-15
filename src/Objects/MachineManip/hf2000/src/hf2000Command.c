/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% hf2000Command ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : hf2000Command 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%hf2000Command ver%I%; Date:%D% %Z%";

#include "../inc/hf2000.h"

void
hf2000Command(hf2000Info* hf2000, char* command, char* result)
{
	hf2000Write(hf2000, command);	
	hf2000Read (hf2000, result);	
}
