/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% dmFileInit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : dmFileInit 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%dmFileInit ver%I%; Date:%D% %Z%";

#include "../inc/dmFile.h"
void
dmFileInit(dmFile* dm, int mode)
{
	mrcDefaultHeaderValueSet(&dm->thumnail);
	mrcDefaultHeaderValueSet(&dm->image);
}
