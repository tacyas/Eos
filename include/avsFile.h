#ifndef AVS_FILE_H
#define AVS_FILE_H
#include <stdio.h>

/* struct begin */
typedef int avsFileParaTypeInteger;
typedef float avsFileParaTypeReal;
/* struct end */

/* constant begin */
typedef enum avsFileType {
	avsFileTypeField=0,
	avsFileTypeUCD=1
} avsFileType;
/*
	Field Format
*/
typedef enum avsFileFieldDataType {
	avsFileFieldDataTypeByte    = 0,
	avsFileFieldDataTypeShort   = 1,
	avsFileFieldDataTypeFloat   = 2,
	avsFileFieldDataTypeInteger = 3,
	avsFileFieldDataTypeDouble  = 4
} avsFileFieldDataType;

typedef enum avsFileFieldType {
	avsFileFieldTypeUniform     = 0,
	avsFileFieldTypeRectilinear = 1,
	avsFileFieldTypeIrregular   = 2
} avsFileFieldType;
/* constant end */

/* struct begin */
typedef struct avsFileField {
	avsFileParaTypeInteger ndim;	
	avsFileParaTypeInteger dim1;	
	avsFileParaTypeInteger dim2;	
	avsFileParaTypeInteger dim3;	
	avsFileParaTypeInteger nspace;
	avsFileParaTypeInteger veclen;
	avsFileFieldDataType   dataType;
	avsFileFieldType       type;
	char**                 Label;
	void*                  Image;
	float**                Coord;
} avsFileField;
/* struct end */

/*
	UCD Format
*/
/* struct begin */
typedef struct avsFileUCDComponentData {
	avsFileParaTypeReal* data;
} avsFileUCDComponentData;

typedef struct avsFileUCDComponent {
	char* Label;
	char* Unit;
	avsFileParaTypeInteger nElement;
} avsFileUCDComponent;

typedef struct avsFileUCDNode {
	avsFileParaTypeInteger   ID;
	avsFileParaTypeReal      x;
	avsFileParaTypeReal      y;
	avsFileParaTypeReal      z;
	avsFileUCDComponentData* Component;
} avsFileUCDNode;
/* struct end */

/* constant begin */
typedef enum avsFileUCDCellType {
	avsFileUCDCellTypePoint        	=0,
	avsFileUCDCellTypeLine   		=1,
	avsFileUCDCellTypeTriangle		=2,
	avsFileUCDCellTypeQuadrilateral	=3,
	avsFileUCDCellTypeTetrahedron	=4,
	avsFileUCDCellTypePyramid		=5,
	avsFileUCDCellTypePrism			=6,
	avsFileUCDCellTypeHexahedron	=7
} avsFileUCDCellType;
/* constant end */

/* struct begin */
typedef struct avsFileUCDCell {
	avsFileParaTypeInteger ID;
	avsFileParaTypeInteger MaterialID;
	avsFileUCDCellType     Type;
	avsFileUCDNode**       Node;
	avsFileUCDComponentData* Component;
} avsFileUCDCell;

typedef struct avsFileUCD {
	/* Node */
	avsFileParaTypeInteger nNode;
	avsFileUCDNode*        Node;
	avsFileParaTypeInteger nNodeComponent;
	avsFileUCDComponent*   NodeComponent;

	/* Cell */
	avsFileParaTypeInteger nCell;
	avsFileUCDCell*        Cell;
	avsFileParaTypeInteger nCellComponent;
	avsFileUCDComponent*   CellComponent;

	/* Model */
	avsFileParaTypeInteger nModel;
} avsFileUCD;
		
typedef struct avsFile {
    avsFileType FileType;
	avsFileField field;
	avsFileUCD   UCD;
} avsFile;
/* constant end */

#ifdef __cplusplus
extern "C" {
#endif
/* prototype begin */
/* avsFileInit.c */
extern void avsFileInit(avsFile* avs, long mode);
extern void avsFileFieldInit(avsFileField* avs, long mode);
extern void avsFileUCDInit(avsFileUCD* avs, long mode);
extern void avsFileUCDGlobalInit(avsFileUCD* avs, long mode);
extern void avsFileUCDNodeComponentInit(avsFileUCD* avs, int ID, int nElement, char* Label, char* Unit, long mode);
extern void avsFileUCDCellComponentInit(avsFileUCD* avs, int ID, int nElement, char* Label, char* Unit, long mode);

/* avsFileWrite.c */
extern void avsFileWrite(avsFile* avs, FILE* fpt, long mode);
extern void avsFileUCDWrite(avsFileUCD* avs, FILE* fpt, long mode);
extern void avsFileFieldWrite(avsFileField* avs, FILE* fpt, long mode);

/* avsFileSet.c */
extern void avsFileUCDNodeSet(avsFileUCD* avs, 
                  avsFileParaTypeInteger NodeID, 
                  avsFileParaTypeReal x, 
                  avsFileParaTypeReal y, 
                  avsFileParaTypeReal z);
extern void avsFileUCDNodeDataSet(avsFileUCD* avs, 
                      avsFileParaTypeInteger NodeID, 
                      avsFileParaTypeInteger indexComponent,
                      avsFileParaTypeInteger indexElement, 
                      double data);
extern void
avsFileUCDLineTypeCellSet(avsFileUCD* avs, 
                  avsFileParaTypeInteger CellID, 
                  avsFileParaTypeInteger MaterialID,
                  avsFileUCDNode* NodeID0,
                  avsFileUCDNode* NodeID1);
extern void
avsFileUCDCellDataSet(avsFileUCD* avs, 
                      avsFileParaTypeInteger CellID, 
                      avsFileParaTypeInteger indexComponent,
                      avsFileParaTypeInteger indexElement, 
                      double data);

/* prototype end */

#ifdef __cplusplus
};
#endif
#endif /* AVS_FILE_H */