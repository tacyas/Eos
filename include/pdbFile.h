#ifndef PDB_FILE_H
#define PDB_FILE_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbFile.h ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : pdbFile.h 
#%Z% Attention
#%Z%
*/
#include <stdio.h>
#include "Matrix3D.h"
#include "mrcImage.h"

/* constant begin */
#define PDB_FILE_RECORD_FULL_LENGTH (80)
#define PDB_FILE_RECORD_START       (0)
#define PDB_FILE_RECORD_LENGTH      (6)
#define PDB_FILE_ATOM_NUMBER_START  (6)
#define PDB_FILE_ATOM_NUMBER_LENGTH (5)
#define PDB_FILE_ATOM_NAME_START    (12)
#define PDB_FILE_ATOM_NAME_LENGTH   (4)
#define PDB_FILE_LOCATION_START     (16)
#define PDB_FILE_LOCATION_LENGTH    (1)
#define PDB_FILE_RESIDUE_START      (17)
#define PDB_FILE_RESIDUE_LENGTH     (3)
#define PDB_FILE_CHAIN_IDENT_START  (21)
#define PDB_FILE_CHAIN_IDENT_LENGTH (1)
#define PDB_FILE_RESNUM_START       (22)
#define PDB_FILE_RESNUM_LENGTH      (4)
#define PDB_FILE_INSERTION_START    (26)
#define PDB_FILE_INSERTION_LENGTH   (1)
#define PDB_FILE_X_START            (30)
#define PDB_FILE_X_LENGTH           (8)
#define PDB_FILE_Y_START            (38)
#define PDB_FILE_Y_LENGTH           (8)
#define PDB_FILE_Z_START            (46)
#define PDB_FILE_Z_LENGTH           (8)
#define PDB_FILE_OCCUPANCY_START    (54)
#define PDB_FILE_OCCUPANCY_LENGTH   (6)
#define PDB_FILE_TEMPERATURE_START  (60)
#define PDB_FILE_TEMPERATURE_LENGTH (6)
#define PDB_FILE_FOOT_START         (67)
#define PDB_FILE_FOOT_LENGTH        (3)
#define PDB_FILE_FOOTNOTE_START     (70)
#define PDB_FILE_FOOTNOTE_LENGTH    (10)
#define PDB_FILE_SEGID_START        (72)
#define PDB_FILE_SEGID_LENGTH       (4)
#define PDB_FILE_ELEMENT_START      (76)
#define PDB_FILE_ELEMENT_LENGTH     (2)
#define PDB_FILE_CHARGE_START       (78)
#define PDB_FILE_CHARGE_LENGTH      (2)
#define MAX_RESIDUE_NUMBER          (20)
#define RESIDUE_ONECHAR_MODE        (1)
#define RESIDUE_THREECHAR_MODE      (3)
#define PDB_FILE_ANISOU_U11_START   (28) 
#define PDB_FILE_ANISOU_U11_LENGTH  (7) 
#define PDB_FILE_ANISOU_U22_START   (35) 
#define PDB_FILE_ANISOU_U22_LENGTH  (7) 
#define PDB_FILE_ANISOU_U33_START   (42) 
#define PDB_FILE_ANISOU_U33_LENGTH  (7) 
#define PDB_FILE_ANISOU_U12_START   (49) 
#define PDB_FILE_ANISOU_U12_LENGTH  (7) 
#define PDB_FILE_ANISOU_U13_START   (56) 
#define PDB_FILE_ANISOU_U13_LENGTH  (7) 
#define PDB_FILE_ANISOU_U23_START   (63) 
#define PDB_FILE_ANISOU_U23_LENGTH  (7) 

#define pdbRecordAtom       ("ATOM  ")
#define pdbRecordHeteroAtom ("HETATM")
#define pdbRecordANISOU     ("ANISOU")
#define pdbRecordHelix      ("HELIX ")
#define pdbRecordSheet      ("SHEET ")
#define pdbRecordTurn       ("TURN  ")
#define pdbRecordEnd        ("END   ")

/* constant end */

/* struct begin */
typedef char  pdbFileParaTypeCharacter;
typedef long  pdbFileParaTypeInteger;
typedef float pdbFileParaTypeReal;

typedef struct residueName {
  char residueName3[4];
  char residueName1[2];
} residueName;

typedef struct pdbCoord {
  pdbFileParaTypeReal x;
  pdbFileParaTypeReal y;
  pdbFileParaTypeReal z;
} pdbCoord;

typedef enum pdbSecondaryStructureHelixClass {
	HelixClassRightHandedAlpha = 1,
	HelixClassRightHandedOmega = 2,
	HelixClassRightHandedPi    = 3,
	HelixClassRightHandedGammda= 4,
	HelixClassRightHanded310   = 5,
	HelixClassLeftHandedAlpha  = 6,
	HelixClassLeftHandedOmega  = 7,
	HelixClassLeftHandedGammda = 9,
	HelixClassPolyProline      = 10,
} pdbSecondaryStructureHelixClass;

typedef struct pdbSecondaryStructureHelix {
	int  serNum;     	/* Serial Number */
	char* helixID;   	/* HelixID : Three alpahnumeric characters */
/* informtion for the initial residue */
	char* initResName;/* Name of the initial residue : Three alpahnumeric characters */ 
	char initChainID;  	/* Chain identifier */ 
	int  initSeqNum;    /* Sequence number of the initial residue */
	char initICode; 
/* informtion for the terminal residue */
	char* endResName;/* Name of the initial residue : Three alpahnumeric characters */ 
	char endChainID;  	/* Chain identifier */ 
	int  endSeqNum;    /* Sequence number of the initial residue */
	char endICode; 

	pdbSecondaryStructureHelixClass helixClass;
	char* comment; 
	int  length;
} pdbSecondaryStructureHelix;

typedef struct pdbSecondaryStructureSheet {
	int  strand; 		/* Strand number which starts 1 for eache strand wihtin a sheet and increases by one */  
	char* sheetID;    /* Sheet ID */			
	int  numStrands;    /* Number of strands in sheet */

/* initial residue */
	char* initResName;/* Name of the initial residue : Three alpahnumeric characters */ 
	char initChainID;  	/* Chain identifier */ 
	int  initSeqNum;    /* Sequence number of the initial residue */
	char initICode; 

/* informtion for the terminal residue */
	char* endResName;/* Name of the initial residue : Three alpahnumeric characters */ 
	char endChainID;  	/* Chain identifier */ 
	int  endSeqNum;    /* Sequence number of the initial residue */
	char endICode; 

	int sense;  /* 0: first strand, 1: parallel, -1: anti-paralle */ 

	char* curAtom; /* Registration. Atom name in current strand */
	char* curResName; /* Registration. Residue name in current strand */
	char curChainID; /* Registration. Chain ID in current strand */
	int  curResSeq;  /* Registration. Res sequence in current strand */
	char curICode;  /* Registration. Insertion code in current strand */

	char* prevAtom; /* Registration. Atom name in current strand */
	char* prevResName; /* Registration. Residue name in current strand */
	char prevChainID; /* Registration. Chain ID in current strand */
	int prevResSeq;  /* Registration. Res sequence in current strand */
	char prevICode;  /* Registration. Insertion code in current strand */
}pdbSecondaryStructureSheet;


typedef struct pdbSecondaryStructureTurn {
	int  serNum;     	/* Serial Number */
	char* turnID;   	/* Turn ID : Three alpahnumeric characters */
/* informtion for the initial residue */
	char* initResName;/* Name of the initial residue : Three alpahnumeric characters */ 
	char initChainID;  	/* Chain identifier */ 
	int  initSeqNum;    /* Sequence number of the initial residue */
	char initICode; 
/* informtion for the terminal residue */
	char* endResName;/* Name of the initial residue : Three alpahnumeric characters */ 
	char endChainID;  	/* Chain identifier */ 
	int  endSeqNum;    /* Sequence number of the initial residue */
	char endICode; 

	char* comment; 
}pdbSecondaryStructureTurn;

typedef struct pdbSecondaryStructureNo {
	int   serNum;     	/* Serial Number */
	char* noID;   	    /* Turn ID : Three alpahnumeric characters */
/* informtion for the initial residue */
	char* initResName;/* Name of the initial residue : Three alpahnumeric characters */ 
	char initChainID;  	/* Chain identifier */ 
	int  initSeqNum;    /* Sequence number of the initial residue */
	char initICode; 
/* informtion for the terminal residue */
	char* endResName;/* Name of the initial residue : Three alpahnumeric characters */ 
	char endChainID;  	/* Chain identifier */ 
	int  endSeqNum;    /* Sequence number of the initial residue */
	char endICode; 

	char* comment; 
}pdbSecondaryStructureNo;

typedef enum pdbFileSecondaryStructureMode {
	pdbFileSecondaryStructureModeNo    = 0,
	pdbFileSecondaryStructureModeHelix = 1,
	pdbFileSecondaryStructureModeSheet = 2,
	pdbFileSecondaryStructureModeTurn  = 3
} pdbFileSecondaryStructureMode;

typedef struct pdbFileSecondaryStructureRecord pdbFileSecondaryStructureRecord; 
struct pdbFileSecondaryStructureRecord {
	pdbFileSecondaryStructureMode mode;
	pdbSecondaryStructureHelix*   helix;
	pdbSecondaryStructureSheet*   sheet;
	pdbSecondaryStructureTurn*    turn;
	pdbSecondaryStructureNo*      no;

	pdbFileSecondaryStructureRecord* prev;
	pdbFileSecondaryStructureRecord* next;
};

typedef struct pdbFileSecondaryStructure {
	int nSecondaryStructure;
	pdbFileSecondaryStructureRecord* top;
	pdbFileSecondaryStructureRecord* SecondaryStructure; 
} pdbFileSecondaryStructure;

typedef struct pdbRecord pdbRecord;

struct pdbRecord {
  pdbFileParaTypeCharacter FullRecord[PDB_FILE_RECORD_FULL_LENGTH+1];

  pdbFileParaTypeCharacter Record[PDB_FILE_RECORD_LENGTH+1];

/* ATOM and HETATM Record */
  pdbFileParaTypeInteger   AtomSerialNumber;
  pdbFileParaTypeCharacter AtomName[PDB_FILE_ATOM_NAME_LENGTH+1];
  pdbFileParaTypeCharacter LocationIndicator;
  pdbFileParaTypeCharacter ResidueName[PDB_FILE_RESIDUE_LENGTH+1];
  pdbFileParaTypeCharacter ChainIdentifier;
  pdbFileParaTypeInteger   ResidueSequenceNumber;
  pdbFileParaTypeCharacter InsertionCode;
  pdbCoord                 Coord;
  pdbFileParaTypeReal      Occupancy;
  pdbFileParaTypeReal      TemperatureFactor;
  pdbFileParaTypeInteger   FootnoteNumber;
  pdbFileParaTypeCharacter Footnote[PDB_FILE_FOOTNOTE_LENGTH+1];
  pdbFileParaTypeCharacter SegID[PDB_FILE_SEGID_LENGTH+1];
  pdbFileParaTypeCharacter Element[PDB_FILE_ELEMENT_LENGTH+1];
  pdbFileParaTypeCharacter Charge[PDB_FILE_CHARGE_LENGTH+1];

  int flagANISOU;
  pdbRecord*               pAtomforANISOU;
  pdbFileParaTypeReal      U11;
  pdbFileParaTypeReal      U22;
  pdbFileParaTypeReal      U33;
  pdbFileParaTypeReal      U12;
  pdbFileParaTypeReal      U13;
  pdbFileParaTypeReal      U23;

  pdbRecord*               prev;
  pdbRecord*               next;

};

typedef struct pdbFile {
  pdbRecord* top;
  pdbRecord* PDB;
  pdbFileParaTypeInteger nAtom;
  pdbFileSecondaryStructure second;
} pdbFile;
/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */
/* in pdbFileRead.c */
extern void pdbFileRead(FILE* fpt, pdbFile* pdb);
/* in pdbFileWrite.c */
extern void pdbFileWrite(FILE* fpt, pdbFile* pdb);
extern void pdbFileWriteCoord(FILE* fpt, pdbFile* pdb);
/*werewolf presents*/
extern void pdbFileTableWrite(FILE* fpt, pdbFile* pdb); 
extern void pdbFileWriteSecondaryStructure(FILE* fpt, pdbFileSecondaryStructure* second);


extern void pdbMatrixFileFormat(FILE* fpt);
extern void pdbMatrixFileRead(FILE* fpt, Matrix3D Matrix);
extern void pdbMatrixFileWrite(FILE* fpt, Matrix3D Matrix);

extern void pdbTrans(pdbFile* pdb, Matrix3D Matrix);
//extern void pdbTransCuda(pdbFile* pdb, Matrix3D Matrix);
extern void pdbTransCuda(float* hv, int n, Matrix3D Matrix);

extern void pdbFileResidueSequenceNumberIncrementAll(pdbFile* pdb, int n);
extern void pdbFileResidueSequenceNumberIncrement(pdbFile* pdb, int n);

extern void pdbFileChainIdentifierSetAll(pdbFile* pdb, unsigned char c);
extern void pdbFileChainIdentifierSet(pdbFile* pdb, unsigned char c);
extern unsigned char pdbFileChainIdentifierGet(pdbFile* pdb);

extern pdbFileParaTypeReal pdbFileTemperatureFactorGet(pdbFile* pdb);
extern void pdbFileTemperatureFactorSet(pdbFile* pdb, double temp);

extern pdbFileParaTypeReal pdbFileOccupancyGet(pdbFile* pdb);
extern void pdbFileOccupancySet(pdbFile* pdb, double temp);

extern long pdbFileCoordSet(pdbFile* pdb, pdbFileParaTypeReal x, pdbFileParaTypeReal y, pdbFileParaTypeReal z);

extern long pdbFileCoordGet(pdbFile* pdb, pdbFileParaTypeReal* x, pdbFileParaTypeReal* y, pdbFileParaTypeReal* z);
extern long pdbFileResidueSequenceNumberGet(pdbFile* pdb);
extern char* pdbFileResidueNameGet(pdbFile* pdb,int mode);

extern pdbRecord* pdbFileTop(pdbFile* pdb);
extern pdbRecord* pdbFileTopPointer(pdbFile* pdb);
extern pdbRecord* pdbFileNext(pdbFile* pdb);
extern pdbRecord* pdbFileNextAtom(pdbFile* pdb);
extern pdbRecord* pdbFileNextCA(pdbFile* pdb);
extern pdbRecord* pdbFilePrev(pdbFile* pdb);
extern pdbRecord* pdbFilePrevAtom(pdbFile* pdb);
extern pdbRecord* pdbFilePrevCA(pdbFile* pdb);
extern long pdbFileEnd(pdbFile* pdb);
extern long pdbFileGoToEnd(pdbFile* pdb);
extern long pdbFileIsEndLine(pdbFile* pdb);
extern long pdbFileIsAtom(pdbFile* pdb);
extern long pdbFileIsANISOU(pdbFile* pdb);
extern long pdbRecordIsNearby(pdbRecord record1,pdbRecord record2);
extern long pdbFileIsCA(pdbFile* pdb);
extern long pdbFileIsNegative(pdbFile* pdb);
extern long pdbFileIsPositive(pdbFile* pdb);
extern long pdbFileIsCharge(pdbFile* pdb);
extern long pdbFileIsSecondaryStructure(pdbFile* pdb);
extern long pdbFileIsHelix(pdbFile* pdb);
extern long pdbFileIsSheet(pdbFile* pdb);
extern long pdbFileIsTurn(pdbFile* pdb);
extern pdbRecord* pdbFileNew(pdbFile* pdb);
extern pdbRecord* pdbFileAppend(pdbFile* pdb);
extern pdbRecord* pdbFileFree(pdbFile* pdb);
extern pdbRecord* pdbFileRecordPrint(FILE* fpt, pdbFile* pdb);

extern pdbFileParaTypeInteger pdbZValueGet(pdbFile* pdb);
/*werewolf presented*/
extern pdbRecord* pdbFileRecordTablePrint(FILE* fpt, pdbFile* pdb);

extern pdbFileSecondaryStructureRecord* pdbFileSecondaryStructureRecordPrint(FILE* fpt, pdbFileSecondaryStructureRecord* second);
extern pdbRecord* pdbFileCAOnlyCopy(pdbFile* pdb, pdbFile* src);
extern void pdbFileCAOnlyCopyAll(pdbFile* pdb, pdbFile* src);
extern void pdbFileCopyAll(pdbFile* dst, pdbFile* src);
extern void pdbFileAppendAll(pdbFile* dst, pdbFile* src);
extern pdbRecord* pdbFileOneRecordCopy(pdbFile* dst, pdbFile* src);
extern void pdbFileOneProteinCopy(pdbFile* dst, pdbFile* src, long num);


extern void pdbRotationFollowingEulerAngle(pdbFile* pdb, char Mode[4], pdbFileParaTypeReal rot1, pdbFileParaTypeReal rot2, pdbFileParaTypeReal rot3);
extern void pdbRotationFollowingEulerAngleInverse(pdbFile* pdb, char Mode[4], pdbFileParaTypeReal rot1, pdbFileParaTypeReal rot2, pdbFileParaTypeReal rot3);
extern void pdbRotationXYZ(pdbFile* pdb, pdbFileParaTypeReal rotx, pdbFileParaTypeReal roty, pdbFileParaTypeReal rotz);
extern void pdbRotationZYX(pdbFile* pdb, pdbFileParaTypeReal rotx, pdbFileParaTypeReal roty, pdbFileParaTypeReal rotz);
extern void pdbRotationZXY(pdbFile* pdb, pdbFileParaTypeReal rotx, pdbFileParaTypeReal roty, pdbFileParaTypeReal rotz);
extern void pdbRotationYXZ(pdbFile* pdb, pdbFileParaTypeReal rotx, pdbFileParaTypeReal roty, pdbFileParaTypeReal rotz);

extern int pdbSecondaryStructureSetFromPDB(pdbFile* pdb, pdbFileSecondaryStructure* second);
extern int pdbNoSecondaryStructureSetFromPDB(pdbFile* pdb, pdbFileSecondaryStructure* second);
extern int pdbSecondaryStructureAppend(pdbFileSecondaryStructure* second);
extern pdbFileSecondaryStructureMode pdbFileWithSecondaryStructure(pdbFile* pdb, pdbFileSecondaryStructure* second);

/* prototype end */

#ifdef __cplusplus
}
#endif
#endif /* PDB_FILE_H */
