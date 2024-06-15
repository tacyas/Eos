/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lFRET.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lFRET.h 
#%Z% Attention
#%Z%
*/
#include "mrcImage.h"

/* constant begin */
/* Point Status Mode */ 
typedef enum energyTransferPointMode {
    energyTransferPointModeFixedPoint   = 0,
    energyTransferPointModeUnfixedPoint = 1,
    energyTransferPointModeConnect      = 2,     
    energyTransferPointModeFar          = 3,   
    energyTransferPointModeNear         = 4     
} energyTransferPointMode;
/* constant end */

/* struct begin */
typedef double energyTransferParaTypeReal;

/* Point Information */
typedef struct energyTransferPoint {
    int nID;
    char* ID;
    energyTransferPointMode mode;
    energyTransferParaTypeReal x;
    energyTransferParaTypeReal y;
    energyTransferParaTypeReal z;
    energyTransferParaTypeReal rootB;
    energyTransferParaTypeReal radius; 
    energyTransferParaTypeReal probability;
} energyTransferPoint;

/* Connection Information */
typedef struct energyTransferConnect {
    int nID;
    char* ID;
    int nID2;
    char* ID2;
    energyTransferPointMode    mode;   
    energyTransferParaTypeReal length; 
    energyTransferParaTypeReal estimatedLength;
    energyTransferParaTypeReal rootB;
    energyTransferParaTypeReal estimatedRootB;
} energyTransferConnect;

/* Energy Transfer Data */ 
typedef struct energyTransferData {
    int numFix; 
    energyTransferPoint* fix;
    int numUnfix;
    energyTransferPoint* unfix;
    int numConnect;
    energyTransferConnect* connect;
    energyTransferParaTypeReal rms;
    energyTransferParaTypeReal rmsRootB;
} energyTransferData;

/* Information for model checking */
typedef struct lenergyTransferModelCheckInfo {
    int flagStartingDelta;
    energyTransferParaTypeReal sdx;
    energyTransferParaTypeReal sdy;
    energyTransferParaTypeReal sdz;
    energyTransferParaTypeReal neglect;
    int excludedPDB;
	int restriction;
    int iter;
} lenergyTransferModelCheckInfo;

/* struct end */

/* prototype begin */
extern void lenergyTransferModelCheck(
		energyTransferData* src, 
		mrcImage* unfix, mrcImage* fix,
        lenergyTransferModelCheckInfo linfo, int mode);

extern void lenergyTransferModelExpectedFRET(
		FILE* fpt, 
		energyTransferData* src, 
		mrcImage* unfix,
        lenergyTransferModelCheckInfo linfo, 
		int mode);

extern void lenergyTransferModelExpectedFRET2(
		FILE* fpt, 
		energyTransferData* src, 
		mrcImage* unfix,
        lenergyTransferModelCheckInfo linfo, 
		int mode);

extern void lenergyTransferModelExpectedFRETSD(
		FILE* fpt, 
		energyTransferData* src, 
		mrcImage* unfix,
        lenergyTransferModelCheckInfo linfo, 
		int mode);

extern void energyTransferDataWrite(
		energyTransferData* dst, 
		FILE* fpt, 
		int lmode);
extern void energyTransferDataRead(
		energyTransferData* dst, 
		FILE* fpt, 
		int lmode);

/* prototype end */
