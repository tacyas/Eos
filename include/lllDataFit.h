/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataFit.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataFit.h 
#%Z% Attention
#%Z%
*/
#ifndef LL_DATA_FIT_H
#define LL_DATA_FIT_H

#include "llData.h"
#include "ctfInfo.h"

/* contant begin */
#define lllDataFitResidual (0x0f) 
#define PVALUE_MODE  (0x01)
#define QVALUE_MODE  (0x02)
#define RVALUE_MODE  (0x04)
#define Q2VALUE_MODE (0x08)

#define lllDataFitFitProcess                (0xf0)
#define lllDataFitFitProcessPrint           (0x10)
#define lllDataFitFitProcessSameLLStructure (0x20)
#define lllDataFitFitProcessMergedLL        (0x40)
/* contant end */

/* struct begin */
typedef struct llDataParaTypeRegion {
	llDataParaTypeReal Max;
	llDataParaTypeReal Min;
    llDataParaTypeReal Delta;
	llDataParaTypeReal Value;
} llDataParaTypeRegion;

typedef struct llDataParamToFit {
    /* IntraMolecule Fit Parameters */
    llDataParaTypeRegion Omega;
    llDataParaTypeRegion x;   /* Axis Position */
    /* InterMolecule Fit Parameters */
    llDataParaTypeRegion  z;
    llDataParaTypeRegion  r;
    llDataParaTypeRegion  phi;
    llDataPole            Pole;
    /* Residue */
    llDataParaTypeReal   R;
    /* Control Parameters */
    llDataParaTypeInteger flagResolution;
    llDataParaTypeReal    Resolution;

	int 			   flagCTF;
	int                ctfCompensationMode;
	ctfInfo            CTF;
	llDataParaTypeReal ctfCutOff;
	int                flagllCTF;
	llData             llCTF;

	int flagLLTable;
	llDataParaTypeInteger* llTable; 
} llDataParamToFit;

typedef struct llDataFittedParam {
    llDataParamToFit   Para;
	llDataParamToFit   PPara;
    llDataParamToFit   QPara;
    llDataParamToFit   Q2Para;
    llDataParamToFit   RPara;
	llDataParamToFit   PParaInv;
    llDataParamToFit   QParaInv;
    llDataParamToFit   Q2ParaInv;
    llDataParamToFit   RParaInv;
	
	int flagFitFile;
	char* fitFileName;
	char* fitFileNameAnti;
} llDataFittedParam;
/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

/* in lllDataFit.c */
extern void lllDataFitOfSeparatedLL(llData* ll1, llDataBoth* ll2, llDataFittedParam* p, long mode);

/* in lllDataFit.c */
extern void lllDataFit(llData* ll1, llData* ll2, llDataFittedParam* p, long mode);
extern void lllDataFitWithFile(llData* ll1, llData* ll2, llDataFittedParam* p, char* paramFileName, long mode);

/* in lllDataFit2.c */
extern void lllDataFit2(llData* ll1, llData* ll2, llDataFittedParam* p, long mode);

/* in lllDataFitOut.c */
extern void lllDataFitParamOutput(FILE* fpt, char* ref, char* dat, llDataFittedParam* para, long mode);


/* in lllDataAxisSearch.c */
extern void lllDataAxisSearch(llData* ll1, llData* ll2, llDataFittedParam* p, long mode);
extern void lllDataAxisSearchWithFile(llData* ll1, llData* ll2, llDataFittedParam* p, char* paramFileName, long mode);

/* in lllDataAxisSearch2.c */
extern void lllDataAxisSearch2(llData* ll1, llData* ll2, llDataFittedParam* p, long mode);

/* in llDataPhaseShift.c */
extern void lllDataPhaseShiftInverse(llData* ll1, llData* ll2, llDataFittedParam* p);
extern void lllDataPhaseShift(llData* ll1, llData* ll2, llDataFittedParam* p);
extern void lllDataPhaseShiftIntra(llData* ll1, llData* ll2, llDataFittedParam* p);
extern void lllDataPhaseShiftInter(llData* ll1, llData* ll2, llDataFittedParam* p);

/* in lllDataFitUtil.c */
extern void lllDataFitllCTFSet(llData* ll, ctfInfo ctf, int mode);
extern void lllDataNewFittedParameterSet(llDataParamToFit* param);
extern void lllDataNewFittedParameterSet0(llDataParaTypeRegion* param);
extern void lllDataFittedParameterSet(llDataParamToFit* param, llDataParamToFit* range);
extern void lllDataFittedParameterSet0(llDataParaTypeRegion* param, llDataParaTypeRegion* region);
extern void lllDataFittedParameterFree(llDataFittedParam* param);
extern void lllDataFittedParameterFree0(llDataParamToFit* param);

/* prototype end */

/* struct begin */
typedef struct lllDataFitPVMInfo {
	int* tids;
	int  numTask;
} lllDataFitPVMInfo;
/* struct end */

/* prototype begin */

extern void lllDataFitServerStart(lllDataFitPVMInfo* linfo, FILE* fpt, int numTask);
extern void lllDataFitServerEnd(lllDataFitPVMInfo linfo);

extern void lllDataFitPVMStart(llData* llref, llData* llp, llDataFittedParam* p, int tid, long mode);
extern void lllDataFitPVMEnd(llData* llref, llData* llp, llDataFittedParam* p, int tid, long mode);
extern void lllDataFitPVMServer();
extern void lllDataFitWithFilePVMStart(llData* llref, llData* llp, llDataFittedParam* p, char* filename, int tid, long mode);
extern void lllDataFitWithFilePVMEnd(llData* llref, llData* llp, llDataFittedParam* p, char* filename, int tid, long mode);

extern void lllDataFittedParamSendByPVM(llDataFittedParam* p, int tid, int mode);
extern void lllDataFittedParamRecieveByPVM(llDataFittedParam* p, int tid, int mode);
extern void lllDataParamToFitSendByPVM(llDataParamToFit* p, int tid, int mode);
extern void lllDataParamToFitSendByPVM2(llDataParamToFit* p, int tid, int mode);
extern void lllDataParamToFitRecieveByPVM(llDataParamToFit* p, int tid, int mode);
extern void lllDataParamToFitRecieveByPVM2(llDataParamToFit* p, int tid, int mode);


extern void lllDataParaTypeRegionSendByPVM(llDataParaTypeRegion* p, int tid, int mode);
extern void lllDataParaTypeRegionRecieveByPVM(llDataParaTypeRegion* p, int tid, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif /* LL_DATA_FIT_H */ 

