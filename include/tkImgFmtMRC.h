#ifndef TK_IMG_FMT_MRC_H
#define TK_IMG_FMT_MRC_H

/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% tkImgFmtMRC ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : tkImgFmtMRC 
#%Z% Attention
#%Z%
*/

#include <tk.h>

#undef DEBUG
#include "genUtil.h"
#include "Vector.h"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcFFTInfo.h"

/*
 * Define MRC, i.e. gray images and color images.
 */

/* constant begin */
#define MRC 1
/* constant end */


/*
 * The format record for the MRC file format:
 */
/* struct begin */
typedef struct tkmrcInfo {
	mrcImage mrc;
	char*    fileName;  /* File Name to be treated */ 
	long     flagHeader;
	long     flagImage; /* Image Array Free or not */

	long flagnz;
	mrcImageParaTypeInteger nz;

	long flagz;
	mrcImageParaTypeReal z;

	long  flagMin;
	float Min;
	long  flagMax;
	float Max;
	long  Inverse; 
	long  flagLog;
	long  flagPower;
	long  flagInfo;
	mrcImageInformation Info;
	long  flagFSInfo;
	mrcFSInfo FSInfo;
	long  flagContrast;
	float Contrast;

	long    flagHist;
	long    nhist;
	double* histgram;
	
	long    flagScattering;
	long    flagR;
	long    flagScattering2D;
	long    nScattering;
	double* scattering;
	double** scattering2D;
	double  axis;
	double  numDivision;
	double* R;

	long flagProjX;
	mrcImage projX;
	long flagProjY;
	mrcImage projY;

	long flagSectX;
	mrcImage sectX;
	long flagSectY;
	mrcImage sectY;
} tkmrcInfo;
/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */
extern int tkmrcInfoCmdSet(Tcl_Interp*  interp); 
extern int tkmrcInfoSetCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[]);
extern int tkmrcInfoGetCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[]);
extern Tk_PhotoImageFormat tkImgFmtMRC;

extern int TkCopyAndGlobalEval(Tcl_Interp* interp, CONST char* command);

/* prototype end */

#ifdef __cplusplus
};
#endif
#endif /* */

