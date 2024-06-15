/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageShapeModePrint ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageShapeModePrint 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageShapeModePrint ver%I%; Date:%D% %Z%";

#include "../inc/mrcImageShape.h"

void
lmrcImageShapeModePrint(FILE* fpt)
{
    fprintf(fpt, "%d: Cylinder with radius and length\n", lmrcImageShapeModeSylinder);
    fprintf(fpt, "%d: Disk with radius and length(thickness)\n", lmrcImageShapeModeDisk);
    fprintf(fpt, "%d: Sphere with radius \n", lmrcImageShapeModeSphere);
    fprintf(fpt, "OutputVector(BILD) for chimera\n");
    fprintf(fpt, "  mode 0 : Cylinder(direction vector) and Disk(normal vector)\n");
    fprintf(fpt, "  mode 1 : Cylinder(direction vector)\n");
    fprintf(fpt, "  mode 2 : Disk(normal vector)\n");
}

