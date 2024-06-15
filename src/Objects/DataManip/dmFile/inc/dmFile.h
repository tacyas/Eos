/*
# dmFile.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dmFile.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef DMFILE_H 
#define DMFILE_H 

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef __int64_t dmFileInteger8; 
typedef __int32_t dmFileInteger4; 
typedef __int16_t dmFileInteger2; 
typedef __int8_t  dmFileInteger1; 

typedef enum dmFileTagDirType {
	dmFileTagDirTypeFileEnd = 0x00,
	dmFileTagDirTypeTagDir  = 0x14, 
	dmFileTagDirTypeTag     = 0x15
} dmFileTagDirType;

static char* __dmFileTagDirTypeChar[] = {
	"FileEnd", "", "", "", "", "", "", "", 
	"", "", "", "", "", "", "", "",
	"", "", "", "", "TagDir", "Tag"
};

typedef enum dmFileTagDataType {
	dmFileTagDataTypeInt2   =2,
	dmFileTagDataTypeInt4   =3,
	dmFileTagDataTypeUInt2  =4,
	dmFileTagDataTypeUInt4  =5,
	dmFileTagDataTypeReal4  =6,
	dmFileTagDataTypeReal8  =7,
	dmFileTagDataTypeBool1  =8,
	dmFileTagDataTypeChar1  =9,
	dmFileTagDataTypeInt1   =0xa,
	dmFileTagDataTypeInt8   =0xb,
	dmFileTagDataTypeUInt8  =0xc,
	dmFileTagDataTypeStruct =0xf,
	dmFileTagDataTypeString =0x12,
	dmFileTagDataTypeArray  =0x14,
	dmFileTagDataTypeTags   =0x15,
} dmFileTagDataType;

typedef enum dmFileImageDataType {
	dmFileImageDataTypeInt2     = 1, 
	dmFileImageDataTypeReal4    = 2, 
	dmFileImageDataTypeComplex8 = 3, 
	dmFileImageDataTypeUnknown  = 4, 
	dmFileImageDataTypePackedComplex  = 5, 
	dmFileImageDataTypeUInt1    = 6, 
	dmFileImageDataTypeInt4     = 7, 
	dmFileImageDataTypeRGBInt4  = 8, 
	dmFileImageDataTypeInt1     = 9, 
	dmFileImageDataTypeUInt2    = 10, 
	dmFileImageDataTypeUInt4    = 11, 
	dmFileImageDataTypeReal8    = 12, 
	dmFileImageDataTypeComplex16= 13, 
	dmFileImageDataTypeBool1    = 14,
	dmFileImageDataTypeIRGInt4Thumnail = 23 
} dmFileImageDataType;

static size_t __dmFileImageDataTypeSize[] = {
	0, 2, 3, 8, 0,  4, 1, 4, 
	4, 1, 2, 4, 6, 16, 1, 0,
	0, 0, 0, 0, 0,  0, 0, 4 
};

static size_t __dmFileTagDataTypeSize[] = {
 0, 0, 2, 4, 2, 4, 4, 8, 
 1, 1, 1, 8, 8, 0, 0, 0, 
 0, 0, 0, 0, 0, 0, 0, 0
}; 

/*
static char* __dmFileTagDataTypeFormat[] = {
    0,    0, "%d",   "%d",   "%u", "%u", "%f", "%f", 
 "%d", "%c", "%d", "%lld", "%llu",     0,   0,	  0, 
    0,    0,    0,      0,      0,     0,   0,    0
}; 
*/

static char* __dmFileTagDataTypeFormat[] = {
    0,    0,  "%#0x", "%#0x",   "%#0X", "%#0X", "%f", "%f", 
 "%#0x", "%c", "%#0x", "%#0x", "%#0llX",     0,    0,	 0, 
    0,    0,      0,     0,       0,     0,    0,    0
}; 


static char* __dmFileTagDataTypeChar[] = {
     "",      "", "Int2",   "Int4", "UInt2", "UInt4", "Real4",  "Real8", 
"Bool1", "Char1", "Int1",   "Int8", "UInt8",      "",      "", "Struct", 
     "",      "", "String",     "", "Array",  "Tags",      "",       ""
}; 



// Header
typedef struct dmFile3Header {
	dmFileInteger4 version;
	dmFileInteger4 rootLength;
	dmFileInteger4 byteOrder;
} __attribute__((__packed__)) dmFile3Header;

typedef struct dmFile4Header {
	dmFileInteger4 version;
	dmFileInteger8 rootLength;
	dmFileInteger4 byteOrder;
} __attribute__((__packed__)) dmFile4Header;

typedef struct dmFile3TagDirectory dmFile3TagDirectory;
typedef struct dmFile4TagDirectory dmFile4TagDirectory; 

// Tag 
typedef struct dmFile3Tag {
	dmFileInteger1 tagID;
	dmFileInteger2 tagNameLength; // Bytes
	char*          tagName;
	// Tag
	char           seperator[4];
	dmFileInteger4 ninfo; 
	dmFileInteger4* info; 
	long            pValue; // Offset	
	long*           pValue2; // Offset	
	long*           pValue3; // Offset	
	void*           value;  // Array or value 
	void**          value2; // Struct
	void**          value3; // Array of Struct
	// TagDirectory 
	dmFile3TagDirectory* tagDir;
} dmFile3Tag;

typedef struct dmFile4Tag {
	dmFileInteger1 tagID;
	dmFileInteger2 tagNameLength; // Bytes
	char*          tagName;
	dmFileInteger8 tagLength;
	// Tag
	char           seperator[4];
	dmFileInteger8 ninfo; 
	dmFileInteger8* info; 
	long            pValue;
	long*           pValue2;
	long*           pValue3;
	void*           value;  // Array or value 
	void**          value2; // Struct
	void**          value3; // Array of Struct
	// TagDirectory
	dmFile4TagDirectory* tagDir;
} dmFile4Tag;

// Root Tag Directory
struct dmFile3TagDirectory {
	dmFileInteger1 sortf;
	dmFileInteger1 closef;
	dmFileInteger4 numberOfTags;
	dmFile3Tag* Tags;
} ;  

struct dmFile4TagDirectory {
	dmFileInteger1 sortf;
	dmFileInteger1 closef;
	dmFileInteger8 numberOfTags;
	dmFile4Tag* Tags;
} ; 

typedef struct dmFile {
	// Header
	dmFileInteger4 version;
	dmFile3Header Header3;
	dmFile4Header Header4;
	// Root Tag
	dmFile3TagDirectory RootTag3;
	dmFile4TagDirectory RootTag4;
	// Tail
	dmFileInteger8 Tail;

	// Control
	mrcImage thumnail;
	mrcImage image;
} dmFile;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

// in dfFileInfo.c
extern void dmFileInfo(FILE* fpt, dmFile dm, int mode);
extern void dmFileHeaderInfo(FILE* fpt, dmFile dm, int mode);
extern void dmFile3TagDirectoryInfo(FILE* fpt, dmFile3TagDirectory tagDir, int layer, int mode);
extern void dmFile3TagInfo(FILE* fpt, dmFile3Tag tagr, int layer, int mode);
extern void dmFile4TagDirectoryInfo(FILE* fpt, dmFile4TagDirectory tagDir, int layer, int mode);
extern void dmFile4TagInfo(FILE* fpt, dmFile4Tag tag, int layer, int mode);

// in dmFileRead.c
extern void dmFileRead(FILE* fpt, dmFile* dm, char* message, int mode);
// DM Header and End Read: check file format
extern void dmFileHeaderTailRead(FILE* fpt, dmFile* dm, char* message, int mode);
// DM3
// Header 
extern void dmFile3HeaderRead(FILE* fpt, dmFile* dm, char* message, int mode);
//
extern void dmFile3TagDirectoryHeaderRead(FILE* fpt, dmFile3TagDirectory* dmRoot, char* message, int mode);
extern void dmFile3TagHeaderRead(FILE* fpt, dmFile3Tag* dmTag, char* message, int mode);
extern void dmFile3TagRead(FILE* fpt, dmFile3Tag* dmTag, char* message, int mode);
extern void dmFile3TagDirectoryRead(FILE* fpt, dmFile3TagDirectory* dmTagDir, char* message, int mode);

// DM4
// Header
extern void dmFile4HeaderRead(FILE* fpt, dmFile* dm, char* message, int mode);
//  
extern void dmFile4TagDirectoryHeaderRead(FILE* fpt, dmFile4TagDirectory* dmRoot, char* message, int mode);
extern void dmFile4TagHeaderRead(FILE* fpt, dmFile4Tag* dmTag, char* message, int mode);
extern void dmFile4TagRead(FILE* fpt, dmFile4Tag* dmTag, char* message, int mode);
extern void dmFile4TagDirectoryRead(FILE* fpt, dmFile4TagDirectory* dmTagDir, char* message, int mode);

// in dmFileUtil.c
extern void dmFileValuePrint(FILE* fpt, void* value, dmFileTagDataType valueType, int n); 

// in dm2mrc.c 
extern void ldm2mrc(mrcImage* mrc, dmFile* dm, int mode);
extern void dmFile3TagDirectory2mrc(dmFile* fpt, dmFile3TagDirectory tagDir, int layer, int mode);
extern void dmFile4TagDirectory2mrc(dmFile* fpt, dmFile4TagDirectory tagDir, int layer, int mode);

// in dmFileInit.c
extern void dmFileInit(dmFile* dm, int mode);

// in ldm2mrc.c

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* DMFILE_H */ 