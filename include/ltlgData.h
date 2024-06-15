#ifndef LTLG_DATA_H
#define LTLG_DATA_H

/*
* ltlgData.h
*
*
*/
#include <stdio.h>

/* constant begin */                        
#define LTLG_TITLE_LENGTH (80)
#define LTLG_SIDE_LENGTH  ( 4)
#define LTLG_FTN_RECORD   (64*4)
/* constant end */

/* struct begin */
typedef short ltlgDataParaTypeInteger; 
typedef float ltlgDataParaTypeReal; 

typedef enum ltlgDataHow {
	ltlgDataHowNearest,
	ltlgDataHowLinear
} ltlgDataHow;

typedef enum ltlgDataType {
	ltlgDataTypeRePart,
	ltlgDataTypeImPart,
	ltlgDataTypeMag,
	ltlgDataTypePhase
} ltlgDataType;

typedef struct ltlgDataLLDataInfo {
    ltlgDataParaTypeInteger  NN;
    ltlgDataParaTypeInteger  NL;
    ltlgDataParaTypeReal     WT;
} ltlgDataLLDataInfo;

typedef struct ltlgDataLLData {
	ltlgDataParaTypeReal r;
    ltlgDataParaTypeReal Re;
    ltlgDataParaTypeReal Im;
}ltlgDataLLData;

typedef struct ltlgDataParaInfo {
    ltlgDataParaTypeReal    d;
    ltlgDataParaTypeReal    Min;
    ltlgDataParaTypeReal    Max;
    ltlgDataParaTypeInteger n;
    ltlgDataParaTypeInteger dummy;
} ltlgDataParaInfo;

typedef struct ltlgData {
    char title1[LTLG_TITLE_LENGTH+1];
    char title2[LTLG_TITLE_LENGTH+1];
    char side[LTLG_SIDE_LENGTH+1];
    ltlgDataParaInfo R;
    ltlgDataParaInfo ll;
    ltlgDataParaInfo r;
    ltlgDataLLDataInfo* llInfo;
    ltlgDataLLData** ltlg;
} ltlgData;
/* struct end */

/* prototype begin */
/* Utilty Funcitions */
#define ltlgDataFileRead  ltlgDataReadFile
#define ltlgDataFileWrite ltlgDataWriteFile

extern void ltlgDataReadFile(FILE* fpt, ltlgData* ltlg, ltlgDataParaTypeInteger mode, ltlgDataParaTypeInteger* status);
extern void ltlgDataWriteFile(FILE* fpt, ltlgData* ltlg, ltlgDataParaTypeInteger mode, ltlgDataParaTypeInteger* status);

extern void ltlgDataPrint(FILE* fpt, ltlgData ltlg, ltlgDataParaTypeInteger mode);
extern void ltlgDataPrintInfo(FILE* fpt, ltlgData ltlg);
extern void ltlgDataPrintllInfo(FILE* fpt, ltlgData ltlg);
extern void ltlgDataPrintllData(FILE* fpt, ltlgData ltlg);

extern void ltlgDataAllocate(ltlgData* ltlg, ltlgDataParaTypeInteger* status);
extern void ltlgDataFree(ltlgData* ltlg);

extern void ltlgDataWeightModifyFromFile(ltlgData* ltlg, FILE* fpt, long mode);
extern void ltlgDataWeightModify(ltlgData* ltlg, ltlgDataLLDataInfo Weight, long mode);
extern void ltlgDataWeightOfNEqualLOnly(ltlgData* ltlg);



extern long
ltlgDataLNumberGet(ltlgData* ltlg,
			 ltlgDataParaTypeInteger n,
			 ltlgDataParaTypeInteger l);

extern ltlgDataParaTypeReal
ltlgDataGet(ltlgData* ltlg,
			 ltlgDataParaTypeInteger n,
			 ltlgDataParaTypeInteger l,
			 ltlgDataParaTypeReal r,
			 ltlgDataParaTypeReal* data,
		     ltlgDataType type, ltlgDataHow how);
						 

extern ltlgDataParaTypeReal
ltlgDataGet2(ltlgData* ltlg,
			 long ll,                       /* layer */
			 ltlgDataParaTypeReal r,
			 ltlgDataParaTypeReal* data,
		     ltlgDataType type, ltlgDataHow how);

/* prototype end */
#endif /* LTLG_DATA_H */