#ifndef  LMRC_IMAGE_SPHERE_H 
#define  LMRC_IMAGE_SPHERE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#include "genUtil.h"
#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageSphereInfo {
		float size;
		float r;
		float w;
		long mode;
}lmrcImageSphereInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageSphere(lmrcImageSphereInfo* info, mrcImage* out);
/* prototype end */

#endif
