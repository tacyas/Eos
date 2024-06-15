/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pngFileInit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pngFileInit 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pngFileInit ver%I%; Date:%D% %Z%";

#include "../inc/pngFile.h"

void
pngFileInit(pngFile* png, int mode)
{
	memset(&png->pngImage, 0, sizeof(png->pngImage));
	png->pngImage.version = PNG_IMAGE_VERSION;
}
