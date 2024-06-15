#ifndef   TGA_FILE_H 
#define   TGA_FILE_H

typedef enum tgaFileColorMap {
	tgaFileColorMapNoColorMap=0,
	tgaFileColorMapColorMap=1
} tgaFileColorMap;

typedef enum tgaFileImageType {
	tgaFileImageTypeNoImage  = 0,	
	tgaFileImageTypeColorMappedImage = 1,
	tgaFileImageTypeTrueColorImage   = 2,
	tgaFileImageTypeBlackAndWhite    = 3,
	tgaFileImageTypeRLEColorMappedImage = 9,
	tgaFileImageTypeRLETrueColorImage   = 10,
	tgaFileImageTypeRLEBlackAndWhite    = 11
} tgaFileImageType;

typedef struct tgaFileColorMapSpecification {
	short FirstEntryIndex;
	short ColorMapLength;
	unsigned char ColorMapEntrySize;
} tgaFileColorMapSpecification;

typedef enum tgaFileImageOrigin {
	tgaFileImageOriginBottomLeft  = 0,
	tgaFileImageOriginBottomRight = 1,
	tgaFileImageOriginTopLeft     = 2,
	tgaFileImageOriginTopRight    = 3 
} tgaFileImageOrigin;

typedef union tgaFileDescriptor {
	unsigned char All;
	struct {
		unsigned char AlphaChannelBits:4;
		unsigned char ImageOrigin:2;
		unsigned char Unused:2;
	} Bit;
} tgaFileDescriptor;

typedef struct tgaFileImageSpecification {
	short Xorigin;
	short Yorigin;
	short Width;
	short Height;
	unsigned char Depth;
	tgaFileDescriptor Descriptor;
} tgaFileImageSpecification;

typedef struct tgaFileHeader {
	unsigned char IDLength;                        /*  1 Byte */
	unsigned char ColorMapType;                    /*  1 Byte */              
	unsigned char ImageType;                       /*  1 Byte */
	tgaFileColorMapSpecification ColorMapSpec;     /*  5 Bytes */
	tgaFileImageSpecification ImageSpec;           /* 10 Bytes */
} tgaFileHeader;                                   /* 18 Bytes */ 

typedef unsigned char tgaFileImageID;
typedef unsigned char tgaFileColorMapData;
typedef unsigned char tgaFileImageData;
typedef unsigned char tgaFileDeveloperData;

typedef struct tgaFile {
	tgaFileHeader        Header;                   /* Field 1-5 : fixed: 18 Bytes */
	tgaFileImageID*      ImageID;                  /* Field 6: variable */
	tgaFileColorMapData* ColorMapData;             /* Field 7: variable */
	tgaFileImageData*    Image;                /* Field 8: variable */
	tgaFileDeveloperData* DeveloperData;           /* Field 9: variable */ 

	/* Additional Information */
	int flagHeader; 
	int ImageDataOffset;
	int ImageDataBytes;
} tgaFile;

#ifdef __cplusplust
extern "C" {
#endif
extern tgaFile* tgaFileInit(tgaFile* tga, FILE* fpt, int mode);
extern tgaFile* tgaFileImageInit(tgaFile* tga, FILE* fpt, int mode);

/* in tgaFileRead.c */
extern tgaFile* tgaFileHeaderRead(tgaFile* tga, FILE* fpt, int mode);
extern tgaFile* tgaFileImageDataRead(tgaFile* tga, FILE* fpt, int mode);
extern tgaFile* tgaFileRead(tgaFile* tga, FILE* fpt, int mode);

/* in tgaFilePrint */
extern void tgaFileHeaderPrint(tgaFile* tga, FILE* out, int mode);

#ifdef __cplusplust
};
#endif

#endif /* TGA_FILE_H */
