/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImagePVM.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImagePVM.h 
#%Z% Attention
#%Z%
*/
#ifndef  MRC_IMAGE_PVM_H 
#define  MRC_IMAGE_PVM_H

#ifdef PVM
#include <pvm3.h>
#include "mrcImage.h"

/* prototype begin */
extern void mrcImageSendByPVM(mrcImage* mrc, int tid, int mode);
extern void mrcImageSendHeaderByPVM(mrcImage* mrc, int tid, int mode);
extern void mrcImageSendImageByPVM(mrcImage* mrc, int tid, int mode);
extern void mrcImageSendTailerByPVM(mrcImage* mrc, int tid, int mode);

extern void mrcImageRecieveByPVM(mrcImage* mrc, int tid, int mode);
extern void mrcImageRecieveHeaderByPVM(mrcImage* mrc, int tid, int mode);
extern void mrcImageRecieveImageByPVM(mrcImage* mrc, int tid, int mode);
extern void mrcImageRecieveTailerByPVM(mrcImage* mrc, int tid, int mode);

extern void mrcImageInformationSendByPVM(mrcImageInformation* linfo, int tid, int mode);
extern void mrcImageInformationRecieveByPVM(mrcImageInformation* linfo, int tid, int mode);
/* prototype end */

#endif /* PVM */

#endif /* MRC_IMAGE_PVM_H */
