/*
# lmrcImageFileListAndEulerAngleDataRead.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFileListAndEulerAngleDataRead.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#ifndef LMRC_IMAGE_FILELISTANDEULERANGLEDATAREAD_H
#define LMRC_IMAGE_FILELISTANDEULERANGLEDATAREAD_H

#include <stdlib.h>
#include "Memory.h" 
#include "eosString.h"
#include "mrcImage.h"
#include "genUtil.h"

/* prototype begin */
extern void lmrcImageFileListAndEulerAngleDataRead(mrcImage* out, char** filename, int number, FILE* fptInfo, int mode);
/* prototype end */

#endif
