/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pngFileWrite ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pngFileWrite 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pngFileWrite ver%I%; Date:%D% %Z%";
#include "../inc/pngFile.h"

void
pngFileWrite(pngFile* png, char* filename, int mode)
{
	png_image_write_to_file(&png->pngImage, filename, 0, png->byteImage, png->flagHanded*png->stride, NULL);
}
