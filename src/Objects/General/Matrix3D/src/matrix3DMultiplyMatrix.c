/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% matrix3DMultiplyMatrix ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : matrix3DMultiplyMatrix 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%matrix3DMultiplyMatrix ver%I%; Date:%D% %Z%";

#include <stdlib.h>
#include "../inc/Matrix3D.h"
#include "Array.h"

void
matrix3DMultiplyMatrix(Matrix3D mat3D, Array a)
{
	if(2!=a.dim) {
		exit(EXIT_FAILURE);
	}

}
