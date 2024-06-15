/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageCTFCompensation ver %I%
#%Z% Created by tacyas
#%Z%
#%Z%
*/
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "ctfInfo.h"

extern void __lmrcImageMultiCTFCompensationMode0(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long nfile, lmrcImageMultiCTFCompensationInfo info, long mode);
extern void __lmrcImageMultiCTFCompensationMode1(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long nfile, lmrcImageMultiCTFCompensationInfo info, long mode);

extern void lmrcImageMultiCTFCompensation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long nfile, lmrcImageMultiCTFCompensationInfo info, long mode);
extern void lmrcImageMultiCTFCompensationUsage(FILE* fpt);

extern void lmrcImageCTFCompensation(mrcImage* dstfft, ctfInfo* ctf, long mode);

