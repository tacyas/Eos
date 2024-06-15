/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageStudentCalculate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageStudentCalculate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageStudentCalculate ver%I%; Date:%D% %Z%";

#include "lmrcImageStudentCalculate.h"

/* summation of 1/(sigma*sigma) by mrcImage */

double
lmrcImageStudentCalculate(mrcImage* in, double sigma)
{
  int x,y,z;
  double s=0;
  
  for (z=0; z<in->HeaderN.z; z++){
    for (y=0; y<in->HeaderN.y; y++){
      for (x=0; x<in->HeaderN.x; x++){
        s=s+1/(sigma*sigma);
      }
    }
  }
  return s;
}
