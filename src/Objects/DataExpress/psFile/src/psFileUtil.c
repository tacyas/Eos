/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% psFileUtil ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : psFileUtil 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%psFileUtil ver%I%; Date:%D% %Z%";
#include "eosString.h"
#include "../inc/psFile.h"

long
psFileIsStartPage(psFile* ps, char* s)
{
	return stringIsSame("%%Page:", s, sizeof("%%Page:")-1);
}

long
psFileIsEndPage(psFile* ps, char* s)
{
	return stringIsSame("showpage", s, sizeof("showpage")-1);
}
