#ifndef MRC_IMAGE_H
#define MRC_IMAGE_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImage.h ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : mrcImage.h
#%Z% Attention
#%Z%
*/

/* mrcImage.h
*    Language:   C or CC(c++)
*    Editor  :   tacyas.tkyemg.u_tokyo
*    Date    :   1990-1992
*    Modified:   2012 for CCP4(2000)
*/

/*
*	Header File for MRC Format
*	Edited by Tac
*/

#include <stdio.h>
#include <math.h>
#include "genUtil.h"
#include "Matrix3D.h"

/* struct begin */

/* Status Mask */
#ifdef M68
typedef unsigned int mrcStatusMask;
#else
typedef unsigned int mrcStatusMask;
#endif

/* Status */
#ifdef M68
typedef unsigned int mrcStatusType;
#else
typedef unsigned int mrcStatusType;
#endif

/* struct end */

/* constant begin */

#define  mrcStatusMask_ExitFailure  ((mrcStatusMask)0x80000000L)
#define  mrcStatusMask_Warning      ((mrcStatusMask)0x40000000L)
#define  mrcStatusMask_Information  ((mrcStatusMask)0x20000000L)
#define  mrcStatusMask_Message      ((mrcStatusMask)0x10000000L)
#define  mrcStatusMask_1B           ((mrcStatusMask)0x08000000L)
#define  mrcStatusMask_1A           ((mrcStatusMask)0x04000000L)
#define  mrcStatusMask_19           ((mrcStatusMask)0x02000000L)
#define  mrcStatusMask_18           ((mrcStatusMask)0x01000000L)
#define  mrcStatusMask_17           ((mrcStatusMask)0x00800000L)
#define  mrcStatusMask_16           ((mrcStatusMask)0x00400000L)
#define  mrcStatusMask_15           ((mrcStatusMask)0x00200000L)
#define  mrcStatusMask_14           ((mrcStatusMask)0x00100000L)
#define  mrcStatusMask_ReferMRCInfo ((mrcStatusMask)0x00080000L)
#define  mrcStatusMask_Mode         ((mrcStatusMask)0x00040000L)
#define  mrcStatusMask_ReferMemory  ((mrcStatusMask)0x00020000L)
#define  mrcStatusMask_ReferFile    ((mrcStatusMask)0x00010000L)

#define  MRC_Status_OK              ((mrcStatusType)0x00000000L)

#define  MRC_FileCanNotOpened       ((mrcStatusType)0x00000000L|mrcStatusMask_ReferFile)
#define  MRC_ImageHeaderCanNotRead  ((mrcStatusType)0x00000001L|mrcStatusMask_ReferFile)
#define  MRC_ImageDataCanNotRead    ((mrcStatusType)0x00000002L|mrcStatusMask_ReferFile)
#define  MRC_ImageHeaderCanNotWrite ((mrcStatusType)0x00000003L|mrcStatusMask_ReferFile)
#define  MRC_ImageDataCanNotWrite   ((mrcStatusType)0x00000004L|mrcStatusMask_ReferFile)
#define  MRC_FileCanNotClosed       ((mrcStatusType)0x00000005L|mrcStatusMask_ReferFile)

#define  MRC_MemoryNotAllocate      ((mrcStatusType)0x00000000L|mrcStatusMask_ReferMemory)

#define  MRC_ModeNotSupported       ((mrcStatusType)0x00000000L|mrcStatusMask_Mode)
#define  MRC_ModeZNot1FFTMode       ((mrcStatusType)0x00000001L|mrcStatusMask_Mode)

#define  MRC_SizeOfZero             ((mrcStatusType)0x00000000L|mrcStatusMask_ReferMRCInfo)


extern char* mrcImageGeneralTypeList[];

/* constant end */

/* struct begin */
typedef union MRC_Status_t {
    mrcStatusType all;
    struct Content {
#ifdef M68
        unsigned char level;
        unsigned char category;
        short detail;
#else
        short detail;
        unsigned char category;
        unsigned char level;
#endif
	} status;
} MRC_Status_t;

#ifdef M68
typedef int mrcImageParaTypeInteger;
#else
typedef int mrcImageParaTypeInteger;
#endif

typedef float mrcImageParaTypeReal;
typedef unsigned char mrcImageParaTypeCharacter;

typedef struct mrcImageParaTypeIntegerCoord {
	mrcImageParaTypeInteger x;
	mrcImageParaTypeInteger y;
	mrcImageParaTypeInteger z;
} mrcImageParaTypeIntegerCoord;

typedef struct mrcImageParaTypeRealCoord {
	mrcImageParaTypeReal x;
	mrcImageParaTypeReal y;
	mrcImageParaTypeReal z;
} mrcImageParaTypeRealCoord;
/* struct end */

/*
*  MRC Image Header
*  Edited by Tac
*/
/* Header Size */
/* constant begin */
#define MRC_HEADER (1024)
#define MRC_TAILER (1024)

/* Image Data Type */
/* for compatibility */
typedef mrcImageParaTypeInteger mrcImageMode;
#define MRC_char_image	    	 ((mrcImageMode)0)
#define	MRC_short_image	    	 ((mrcImageMode)1)
#define	MRC_float_image	    	 ((mrcImageMode)2)
#define	MRC_complex_short_ft     ((mrcImageMode)3)
#define	MRC_complex_float_ft     ((mrcImageMode)4)
#define	MRC_long_image	         ((mrcImageMode)101)
#define	MRC_double_image	     ((mrcImageMode)102)
#define	MRC_complex_long_ft      ((mrcImageMode)103)
#define	MRC_complex_double_ft    ((mrcImageMode)104)
#define	MRC_complex_short_fft    ((mrcImageMode)1003)
#define	MRC_complex_float_fft    ((mrcImageMode)1004)
#define	MRC_complex_long_fft     ((mrcImageMode)1103)
#define	MRC_complex_double_fft   ((mrcImageMode)1104)
#define MRC_NotSuppotedMode      ((mrcImageMode)0xffffffffL)

#define mrcCharImage	    	 ((mrcImageMode)0)
#define	mrcShortImage	    	 ((mrcImageMode)1)
#define	mrcFloatImage	    	 ((mrcImageMode)2)
#define	mrcComplexShortFT        ((mrcImageMode)3)
#define	mrcComplexFloatFT        ((mrcImageMode)4)
#define	mrcComplexFloatOneDimFT  ((mrcImageMode)5)
// Change of IMOD
#define	mrcUShortImage           ((mrcImageMode)6)
#define	mrcCharImageRGB          ((mrcImageMode)16)
// Change for IMOD: (6,7) -> (26,27)
#define	mrcFloatRadonImage       ((mrcImageMode)26)
#define	mrcFloatRadonFT          ((mrcImageMode)27)
#define	mrcLongImage	         ((mrcImageMode)101)
#define	mrcDoubleImage	         ((mrcImageMode)102)
#define	mrcComplexLongFT         ((mrcImageMode)103)
#define	mrcComplexDoubleFT       ((mrcImageMode)104)
#define	mrcComplexShortFFT       ((mrcImageMode)1003)
#define	mrcComplexFloatFFT       ((mrcImageMode)1004)
#define	mrcComplexLongFFT        ((mrcImageMode)1103)
#define	mrcComplexDoubleFFT      ((mrcImageMode)1104)
#define mrcNotSuppotedMode       ((mrcImageMode)0xffffffffL)

#define MRC_MAX_LABEL_N    (10)
#define MRC_MAX_LABEL_LEN  (80)
#define MRC_MAX_EXTRA      (29)
#define MRC_MAX_EXTRA_CCP4 (15)
/* constant end */

/* struct begin */

/* Image Header */
typedef struct _mrcImageHeader {
	mrcImageParaTypeIntegerCoord        N;	    /* Data Numbers */
	mrcImageMode                        Mode;   /* Data Type */
	mrcImageParaTypeIntegerCoord        StartN; /* First in map */
	mrcImageParaTypeIntegerCoord        M;	    /* Number of Intervals */
	mrcImageParaTypeRealCoord           Length; /* Cell Dimensions : Angstrom */
	mrcImageParaTypeReal                Alpha;  /* Cell Angle : Degree */
	mrcImageParaTypeReal                Beta;
	mrcImageParaTypeReal                Gamma;
	mrcImageParaTypeInteger             MAPC;   /* Which Axis Corresponds to Columns */
	mrcImageParaTypeInteger             MAPR;   /* Which Axis Corresponds to Rows */
	mrcImageParaTypeInteger             MAPS;   /* Which Axis Corresponds to Sections */
	mrcImageParaTypeReal                AMin;   /* Minimum Density Value */
	mrcImageParaTypeReal                AMax;   /* Maximum Density Value */
	mrcImageParaTypeReal                AMean;  /* Mean Density Value */
	mrcImageParaTypeInteger             ISPG;   /* Space Group */
	mrcImageParaTypeInteger             NSYMBT; /* Number of bytes */
	mrcImageParaTypeReal                EXTRA[MRC_MAX_EXTRA]; /* Extra, user defined storage space */
    mrcImageParaTypeReal                OriginX;
    mrcImageParaTypeReal                OriginY;
    mrcImageParaTypeInteger             LabelN;
    char                                Label[MRC_MAX_LABEL_N][MRC_MAX_LABEL_LEN];
} _mrcImageHeader;

/* For CCP4 2000 : Current New */
typedef struct _mrcImageHeaderCCP4 {
	mrcImageParaTypeIntegerCoord        N;	    /* Data Numbers */
	mrcImageMode                        Mode;   /* Data Type */
	mrcImageParaTypeIntegerCoord        StartN; /* First in map */
	mrcImageParaTypeIntegerCoord        NI;	    /* Number of Intervals */
	mrcImageParaTypeRealCoord           Length; /* Cell Dimensions : Angstrom */
	mrcImageParaTypeReal                Alpha;  /* Cell Angle : Degree */
	mrcImageParaTypeReal                Beta;
	mrcImageParaTypeReal                Gamma;
	mrcImageParaTypeInteger             MAPC;   /* Which Axis Corresponds to Columns */
	mrcImageParaTypeInteger             MAPR;   /* Which Axis Corresponds to Rows */
	mrcImageParaTypeInteger             MAPS;   /* Which Axis Corresponds to Sections */
	mrcImageParaTypeReal                AMin;   /* Minimum Density Value */
	mrcImageParaTypeReal                AMax;   /* Maximum Density Value */
	mrcImageParaTypeReal                AMean;  /* Mean Density Value */
	mrcImageParaTypeInteger             ISPG;   /* Space Group */
	mrcImageParaTypeInteger             NSYMBT; /* Number of bytes used for storing symmetry operators */
	mrcImageParaTypeInteger             LSKFLG; /* Flag for Skew transformation */
	mrcImageParaTypeReal 				SKWMAT[9]; /* Skew matrix S */
	mrcImageParaTypeReal 				SKWTRN[3]; /* Skew translation */
	mrcImageParaTypeReal                EXTRA[MRC_MAX_EXTRA_CCP4]; /* Extra, user defined storage space */
    mrcImageParaTypeCharacter  			MAP[4];
    mrcImageParaTypeInteger  			MARCHST;
    mrcImageParaTypeReal                ARMS;
    mrcImageParaTypeInteger             LabelN;
    char                                Label[MRC_MAX_LABEL_N][MRC_MAX_LABEL_LEN];
} _mrcImageHeaderCCP4;

/* For IMOD: Current New */
typedef struct _mrcImageHeaderIMOD {
	mrcImageParaTypeIntegerCoord        N;	    /* Data Numbers */
	mrcImageMode                        Mode;   /* Data Type */
	mrcImageParaTypeIntegerCoord        StartN; /* First in map */
	mrcImageParaTypeIntegerCoord        M;	    /* Number of Intervals */
	mrcImageParaTypeRealCoord           Length; /* PixelSize=Len/M: Angstrom */
	mrcImageParaTypeReal                Alpha;  /* Cell Angle : Degree */
	mrcImageParaTypeReal                Beta;
	mrcImageParaTypeReal                Gamma;
	mrcImageParaTypeInteger             MAPC;   /* Which Axis Corresponds to Columns */
	mrcImageParaTypeInteger             MAPR;   /* Which Axis Corresponds to Rows */
	mrcImageParaTypeInteger             MAPS;   /* Which Axis Corresponds to Sections */
	mrcImageParaTypeReal                AMin;   /* Minimum Density Value */
	mrcImageParaTypeReal                AMax;   /* Maximum Density Value */
	mrcImageParaTypeReal                AMean;  /* Mean Density Value */
	mrcImageParaTypeInteger             ISPG;   /* Space Group */
	mrcImageParaTypeInteger             NSYMBT; /* Number of bytes used for extended header */
	short                               creatid; /* Flag for Skew transformation */
	short                               extra1[15]; /* Flag for Skew transformation */
	short                               nint;
	short                               nreal; /*l Skew matrix S */
	mrcImageParaTypeReal                extra2[5]; /* Extra, user defined storage space */
	mrcImageParaTypeInteger             imodStamp;
	mrcImageParaTypeInteger             imodFlags;
	short                               idtype;
	short                               lnes;
	short                               nd1;
	short                               nd2;
	short                               vd1;
	short                               vd2;
	mrcImageParaTypeReal                tiltangles[6]; /* Extra, user defined storage space */
	mrcImageParaTypeReal                xorg; /* Extra, user defined storage space */
	mrcImageParaTypeReal                yorg; /* Extra, user defined storage space */
	mrcImageParaTypeReal                zorg; /* Extra, user defined storage space */
    mrcImageParaTypeCharacter  			MAP[4];
    mrcImageParaTypeInteger  			MARCHST;
    mrcImageParaTypeReal                ARMS;
    mrcImageParaTypeInteger             LabelN;
    char                                Label[MRC_MAX_LABEL_N][MRC_MAX_LABEL_LEN];
} _mrcImageHeaderIMOD;


typedef union mrcImageHeader {
  unsigned char           All[MRC_HEADER];
  mrcImageParaTypeInteger Int[MRC_HEADER/4];
  mrcImageParaTypeReal    Real[MRC_HEADER/4];
  _mrcImageHeader         Cont;
  _mrcImageHeaderCCP4     ContCCP4;
  _mrcImageHeaderIMOD     ContIMOD;
} mrcImageHeader;


#define FEI_EXTENDED_HEADER_EACH (128)

typedef struct _FEIextendedHeader {
	mrcImageParaTypeReal aTilt;   // Alpha tilt, in degrees
	mrcImageParaTypeReal bTilt;   // Beta tilt, in degrees
	mrcImageParaTypeReal xStage;  // Stage x position.
								  // Normally in SI units (meters),
								  // but some older files may be in micrometers.
								  // Check by looking at values for x,y,z.
								  // If one of these exceeds 1, it will be micrometers.
	mrcImageParaTypeReal yStage;  // Stage y position. For testing of units see x_stage.
	mrcImageParaTypeReal zStage;  // Stage z position. For testing of units see x_stage.
	mrcImageParaTypeReal xShift;  // Image shift x. For testing of units see x_stage.
	mrcImageParaTypeReal yShift;  // Image shift y. For testing of units see x_stage.
	mrcImageParaTypeReal defocus;
	mrcImageParaTypeReal expTime;
	mrcImageParaTypeReal mean;
	mrcImageParaTypeReal tiltAxis;
	mrcImageParaTypeReal pixelSize;
	mrcImageParaTypeReal magnification;
	mrcImageParaTypeReal ht;
	mrcImageParaTypeReal binning;
	mrcImageParaTypeReal appliedDefocus;
	mrcImageParaTypeReal reminder[FEI_EXTENDED_HEADER_EACH/4-16];
} _FEIextendedHeader;

typedef union FEIextendedHeader {
	mrcImageParaTypeReal Real[FEI_EXTENDED_HEADER_EACH/4];
	_FEIextendedHeader   Cont;
} FEIextendedHeader;


/* struct end */

/*
	Tailer
*/
/* constant begin */
#define  mrcImageTailerMode2DProjection 0
/* constant end */

/* struct begin */
typedef struct _mrcImageTailer {
	char                 		Code[4];
	mrcImageParaTypeInteger		Mode;
	char                        EulerAngleMode[4];
	mrcImageParaTypeReal 		Rot1;
	mrcImageParaTypeReal 		Rot2;
	mrcImageParaTypeReal 		Rot3;
	mrcImageParaTypeInteger 	Mirror;
} _mrcImageTailer;


typedef union mrcImageTailer {
  unsigned char           All[MRC_TAILER];
  mrcImageParaTypeInteger Int[MRC_TAILER/4];
  mrcImageParaTypeReal    Real[MRC_TAILER/4];
  _mrcImageTailer         Cont;
} mrcImageTailer;


typedef char mrcImageSymmetryOperator;

/*
mrcImage Structure
*/
typedef struct mrcImage {
    mrcImageHeader          Header;
    size_t BytePerImage;
    mrcImageParaTypeInteger BytePerBand;
    mrcImageParaTypeInteger BandPerPixel;
    size_t PixelPerImage;
    mrcStatusType           status;
    char*           Image;
    unsigned char*  ImageCharImage;
    unsigned short* ImageShortImage;
    signed   long*  ImageLongImage;
    unsigned long*  ImageULongImage;
    float*          ImageFloatImage;
    double*         ImageDoubleImage;

	/* Tailer */
	mrcImageTailer*         Tailer;
	mrcImageParaTypeInteger numTailer;

	/* FEIextendedHeader */
	FEIextendedHeader*      FEIHeader;
	mrcImageParaTypeInteger numFEIHeader;

 	/* Dummy */
	char*     dummyHeader;
	mrcImageParaTypeInteger dummyHeaderByte;

	/* Swap Bytes */
	mrcImageParaTypeInteger flagByteSwap;

	/* flag CCP4-2000 */
	mrcImageParaTypeInteger   flagCCP4;
	mrcImageParaTypeInteger   ImageOffset;
	mrcImageSymmetryOperator* SymmetryOperator;

    /* flag signed char/short */
    int flagSigned;
} mrcImage;

typedef struct mrcImagePyramidList {
    mrcImage mrc;
    mrcImage* up;
    mrcImage* down;
} mrcImagePyramidList;

typedef struct mrcImagePyramid {
    mrcImagePyramidList* top;
    mrcImagePyramidList* current;
} mrcImagePyramid;

typedef struct mrcImageInformation {
    double mean;
    double rootMeanSquare;
    double meanOfSphereSurface;
    double sdOfSphereSurface;
    double seOfSphereSurface;
    double meanOfCylinderSurface;
    double sdOfCylinderSurface;
    double seOfCylinderSurface;
    double meanOfEdge;
    double sdOfEdge;
    double seOfEdge;
    double max;
	mrcImageParaTypeRealCoord maxCoord;
    double min;
	mrcImageParaTypeRealCoord minCoord;
    double sd;
    double se;
	double rmax;
	long flagrmax;
	double RMS; /* Root mean square */
	int mode;
	mrcImageParaTypeRealCoord sdOfAllAxis;
	mrcImageParaTypeRealCoord aveOfAllAxis;
    // Value Area
    // High Value
    double thresOfHighValueArea;
    double meanOfHighValueArea;
    double sdOfHighValueArea;
    double seOfHighValueArea;
    double maxOfHighValueArea;
    double minOfHighValueArea;
    double medianOfHighValueArea;
    // Low Value
    double thresOfLowValueArea;
    double meanOfLowValueArea;
    double sdOfLowValueArea;
    double seOfLowValueArea;
    double maxOfLowValueArea;
    double minOfLowValueArea;
    double medianOfLowValueArea;

	/* For Search Area */
	int flagXrange;
	int flagYrange;
	int flagZrange;
	double XrangeMin;
	double XrangeMax;
	double YrangeMin;
	double YrangeMax;
	double ZrangeMin;
	double ZrangeMax;

	int flagCentre;
	double CentreX;
	double CentreY;
	double CentreZ;

    /* For Search Value Area: 0-1 */
    double thresHigh;
    double thresLow;
} mrcImageInformation;

/* struct end */

/* constant begin */
typedef enum mrcImageInformationMode {
	meanOfAll             = 0,
    meanOfSphereSurface   = 1,
    meanOfCylinderSurface = 2,
    meanOfEdge            = 3,
    meanOfCentre          = 4,
    meanOfSparse          = 5,
	meanOf2DEdgeY         = 6,
	RMSofAllPixels        = 7,
	sdOfAllAxis           = 8,
    meanOfHighValueArea   = 9,
    meanOfLowValueArea    = 10,
    meanOfLowValueAreaAndHighValueArea = 11
} mrcImageInformationMode;

/*
*  Define
*/
#define HeaderN       Header.Cont.N
#define HeaderMode    Header.Cont.Mode
#define HeaderStartN  Header.Cont.StartN
#define HeaderM       Header.Cont.M
#define HeaderLength  Header.Cont.Length
#define HeaderAlpha   Header.Cont.Alpha
#define HeaderBeta    Header.Cont.Beta
#define HeaderGamma   Header.Cont.Gamma
#define HeaderMAPC    Header.Cont.MAPC
#define HeaderMAPR    Header.Cont.MAPR
#define HeaderMAPS    Header.Cont.MAPS
#define HeaderAMin    Header.Cont.AMin
#define HeaderAMax    Header.Cont.AMax
#define HeaderAMean   Header.Cont.AMean
#define HeaderISPG    Header.Cont.ISPG
#define HeaderNSYMBT  Header.Cont.NSYMBT
#define HeaderLSKFLG  Header.ContCCP4.LSKFLG
#define HeaderEXTRA   Header.Cont.EXTRA
#define HeaderOriginX Header.Cont.OriginX
#define HeaderOriginY Header.Cont.OriginY
#define HeaderLabelN  Header.Cont.LabelN
#define HeaderLabel   Header.Cont.Label

typedef enum mrcPixelDataType {
    mrcPixelRePart = 0,
    mrcPixelImPart,
    mrcPixelSigmaPart,
    mrcPixelMag,
    mrcPixelPow,
    mrcPixelLogMag,
    mrcPixelLogPow,
    mrcPixelPhase
} mrcPixelDataType;

typedef enum mrcPixelDataHowToGet {
    mrcPixelHowNearest = 0,
    mrcPixelHowLinear,
    mrcPixelHowCubicConv,
    mrcPixelHowPolySig
} mrcPixelDataHowToGet;

/* constant end */

/* struct begin */
typedef struct lmrcImageSmoothingInfo  {
	long mode;
	mrcImageParaTypeReal sx; /* Filter kernel size */
	mrcImageParaTypeReal sy;
	mrcImageParaTypeReal sz;
	double sigma;            /* for Lee-Sigma filter  */
} lmrcImageSmoothingInfo;

typedef struct lmrcImageCVEInfo {
	long sx; /* CVE domain size. */
	long sy; /* Apr.30,1996 */
	long sz;
} lmrcImageCVEInfo;

typedef struct lmrcImageTfunctionInfo {
	long sx; /* Tfunction domain size. */
	long sy; /* June 11,1996 */
	long sz;
} lmrcImageTfunctionInfo;

typedef struct lmrcImageHighlightInfo {
	long mode;
	float Bias; /* May 1,1996 */
	float Grad;
} lmrcImageHighlightInfo;

typedef struct lmrcImageLowPassFilterInfo
{
	long mode; /* June 4,1996 */
	float hvp, width;
} lmrcImageLowPassFilterInfo;

typedef struct lmrcImageHighPassFilterInfo
{
	long mode; /* June 5,1996 */
	float hvp, width;
	float pathWindowLow;
	float pathWindowHigh;
} lmrcImageHighPassFilterInfo;

typedef struct lmrcImageBandPassFilterInfo
{
	long mode; /* June 5,1996 */
	float hvl, hvh, wl, wh;
	int flagLowWeight;
	double lowWeight;
} lmrcImageBandPassFilterInfo;

/* struct end */
/* Utility Routines */
#ifdef __cplusplus
extern "C" {
#endif
/* prototype begin */
/* in mrcInit.c */
extern mrcStatusType mrcInit(mrcImage* mrc, char* filaname);
extern mrcStatusType mrcDefaultHeaderValueSet(mrcImage* mrc);
extern mrcStatusType mrcDefaultHeaderValueSetOnlyFixedValue(mrcImage* mrc);
extern mrcStatusType mrcHiddenDataSet(mrcImage* mrc, long mode);
extern void mrcImageFree(mrcImage* mrc, char* message);
/* in mrcTailer.c */
extern void mrcTailerInit(mrcImage* mrc, long mode);
extern void mrcTailerCopy(mrcImage* dst, mrcImage* src, long mode);
  /* mode 1: Tailer Memory Allocation */
/* in mrcRead.c */
extern mrcStatusType mrcFileReadGeneral  (mrcImage* mrc, char* filename, char* type, char* message, long mode);
extern mrcStatusType mrcImageReadGeneral  (mrcImage* mrc, char* filename, char* type, char* message, long mode);
extern mrcStatusType mrcHeaderReadGeneral(mrcImage* mrc, char* filename, char* type, char* message, long mode);
extern mrcStatusType mrcTailerReadGeneral(mrcImage* mrc, char* filename, char* type, char* message, long mode);
extern mrcStatusType mrcFileGeneralListPrint(FILE* fpt);

extern mrcStatusType mrcFileRead  (mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcImageRead (mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcHeaderRead(mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcTailerRead(mrcImage* mrc, char* filename, char* message, long mode);

extern mrcStatusType mrcFileReadFEIextendedMRC  (mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcImageReadFEIextendedMRC (mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcHeaderReadFEIextendedMRC(mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcTailerReadFEIextendedMRC(mrcImage* mrc, char* filename, char* message, long mode);

extern mrcStatusType mrcFileReadIMODextendedMRC  (mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcImageReadIMODextendedMRC (mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcHeaderReadIMODextendedMRC(mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcTailerReadIMODextendedMRC(mrcImage* mrc, char* filename, char* message, long mode);

extern int mrcImageByteSwap(mrcImage* mrc, long mode);
/* in mrcWrite.c */
#define mrcFileWriteModeGet(x)     BYTE4GETBYTE(x,0)
#define mrcImageWriteModeGet(x)    BYTE4GETBYTE(x,1)
#define mrcHeaderWriteModeGet(x)   BYTE4GETBYTE(x,2)
#define mrcTailerWriteModeGet(x)   BYTE4GETBYTE(x,3)

#define	mrcFileWriteMode_InfoPrint         1
#define	mrcFileWriteMode_NoCallForStatData 2

extern mrcStatusType mrcFileWrite  (mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcImageWrite (mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcHeaderWrite(mrcImage* mrc, char* filename, char* message, long mode);
extern mrcStatusType mrcTailerWrite(mrcImage* mrc, char* filename, char* message, long mode);
/* in mrcWrite.c */
extern mrcStatusType mrcFileWriteLowerResolution(mrcImage* mrc, char* filename, char* message, long sample , long mode);
/* in mrcGet.c */
extern double mrcImageDataGetbyAU(mrcImage* mrc,
			      mrcImageParaTypeReal x /* Angstrom */,
			      mrcImageParaTypeReal y /* Angstrom */,
			      mrcImageParaTypeReal z /* Angstrom */,
			      double* data,
			      mrcPixelDataType mode,
			      mrcPixelDataHowToGet how);
extern double mrcPixelDataGet(mrcImage* mrc,
			      mrcImageParaTypeReal x /* Pixel Unit */,
			      mrcImageParaTypeReal y /* Pixel Unit */,
			      mrcImageParaTypeReal z /* Pixel Unit */,
			      double* data,
			      mrcPixelDataType mode,
			      mrcPixelDataHowToGet how);

extern void mrcPixelsDataGet(float* data, mrcImageParaTypeRealCoord* inCoord, int nPixel, mrcImage* in, mrcPixelDataType type, mrcPixelDataHowToGet howto);
extern void mrcPixelDataGetbyMatrix3D(mrcImage* out, mrcImage* in, Matrix3D mat, mrcPixelDataHowToGet mode, int mode2);

static inline double mrcPixelDataGetFloatImage(mrcImage* img,
		mrcImageParaTypeInteger x, mrcImageParaTypeInteger y, mrcImageParaTypeInteger z)
{
	return img->ImageFloatImage[x + y*img->HeaderN.x + z*img->HeaderN.x*img->HeaderN.y];
}

static inline double mrcPixelDataGetFloatFTRe(mrcImage* fft,
		mrcImageParaTypeInteger x, mrcImageParaTypeInteger y, mrcImageParaTypeInteger z)
{
	return fft->ImageFloatImage[2*(x + y*(fft->HeaderN.x/2+1) + z*(fft->HeaderN.x/2+1)*fft->HeaderN.y)];
}
static inline double mrcPixelDataGetFloatFTIm(mrcImage* fft,
		mrcImageParaTypeInteger x, mrcImageParaTypeInteger y, mrcImageParaTypeInteger z)
{
	return fft->ImageFloatImage[2*(x + y*(fft->HeaderN.x/2+1) + z*(fft->HeaderN.x/2+1)*fft->HeaderN.y)+1];
}

/* in mrcImageSet.c */
extern void mrcInfoSet(mrcImage* mrc, FILE* fptIn, FILE* fptOut, mrcImageParaTypeInteger mode);

/* prototype end */

/* struct begin */
/* in mrcImageDataSet.c */
typedef enum mrcImageDataSetMode {
	mrcImageDataSetModeCentre = 0,
	mrcImageDataSetModeOrigin = 1
} mrcImageDataSetMode;
/* struct end */

/* prototype begin */
extern void mrcImageDataSet(mrcImage* out,
							mrcImage* in,
							mrcImageParaTypeReal x,
							mrcImageParaTypeReal y,
							mrcImageParaTypeReal z,
							float phi,
							mrcImageDataSetMode  mode);

/* in mrcSet.c */
extern double mrcImageDataSetbyAU(mrcImage* mrc,
			      mrcImageParaTypeReal x /* Angstrom */,
			      mrcImageParaTypeReal y /* Angstrom */,
			      mrcImageParaTypeReal z /* Angstrom */,
			      double data,
			      mrcPixelDataType mode);
extern double mrcPixelDataSet(mrcImage* mrc,
			      mrcImageParaTypeReal x /* Pixel Unit */,
			      mrcImageParaTypeReal y /* Pixel Unit */,
			      mrcImageParaTypeReal z /* Pixel Unit */,
			      double data,
			      mrcPixelDataType mode);

static inline void mrcPixelDataSetFloatImage(mrcImage* img,
		mrcImageParaTypeInteger x, mrcImageParaTypeInteger y, mrcImageParaTypeInteger z, double data)
{
	img->ImageFloatImage[x + y*img->HeaderN.x + z*img->HeaderN.x*img->HeaderN.y] = (float)data;
}

static inline void mrcPixelDataSetFloatFTRe(mrcImage* fft,
		mrcImageParaTypeInteger x, mrcImageParaTypeInteger y, mrcImageParaTypeInteger z, double data)
{
	fft->ImageFloatImage[2*(x + y*(fft->HeaderN.x/2+1) + z*(fft->HeaderN.x/2+1)*fft->HeaderN.y)] = (float)data;
}

static inline void mrcPixelDataSetFloatFTIm(mrcImage* fft,
		mrcImageParaTypeInteger x, mrcImageParaTypeInteger y, mrcImageParaTypeInteger z, double data)
{
	fft->ImageFloatImage[2*(x + y*(fft->HeaderN.x/2+1) + z*(fft->HeaderN.x/2+1)*fft->HeaderN.y)+1] = (float)data;
}


extern void mrcStatDataSet(mrcImage* mrc, mrcImageParaTypeInteger mode);



/* in mrcImageInfo.c */
extern void lmrcImageXSection(mrcImage* proj, mrcImage* img, double Y);
extern void lmrcImageYSection(mrcImage* proj, mrcImage* img, double X);
extern void lmrcImageXProjection(mrcImage* proj, mrcImage* img);
extern void lmrcImageYProjection(mrcImage* proj, mrcImage* img);
extern void lmrcImageZProjection(mrcImage* proj, mrcImage* img);
extern void lmrcImageXYProjection(mrcImage* proj, mrcImage* img);
extern void lmrcImageYZProjection(mrcImage* proj, mrcImage* img);
extern void lmrcImageZXProjection(mrcImage* proj, mrcImage* img);
	/* Histgram */
	/* Frequecy max -> 1 */
extern void lmrcImageHistgram(double** hist, unsigned long nlevel, mrcImage* img);
extern void lmrcImageHistgram2(double** hist, double delta, mrcImage* img);
extern void lmrcImageHistgram5(double** hist, unsigned long nlevel, double Low, double High, mrcImage* img);
	/* Frequency */
extern void lmrcImageHistgram3(double** hist, unsigned long nlevel, mrcImage* img);
extern void lmrcImageHistgram4(double** hist, double delta, mrcImage* img);
extern void lmrcImageHistgram6(double** hist, double delta, double Low, double High, mrcImage* img);
extern void lmrcImageInformation(mrcImageInformation* info, mrcImage* img);


/* in mrcImageCopy.c */
extern void lmrcImageCopy(mrcImage* dst, mrcImage* src, mrcImageParaTypeRealCoord to);

/* in mrcUtil.c */
extern int IsFloatImage(mrcImage* mrc, char* message, mrcImageParaTypeInteger mode);
extern int IsFloatFT(mrcImage* mrc, char* message, mrcImageParaTypeInteger mode);
extern int IsImage(mrcImage* mrc, char* message, mrcImageParaTypeInteger mode);
extern int IsFT(mrcImage* mrc, char* message, mrcImageParaTypeInteger mode);
extern int IsFFT(mrcImage* mrc, char* message, mrcImageParaTypeInteger mode);
extern void mrcImageInfoSet(mrcImage* mrc, FILE* fptIn, FILE* fptOut, long mode);

/* in mrcImageOperation.c */
extern void lmrcImageDividedByImage(mrcImage* img, mrcImage* i1, mrcImage* i2);
extern void lmrcImagetMapForZero(mrcImage* t, mrcImage* avg, mrcImage* se);
extern void lmrcImageSN(mrcImage* sn, mrcImage* avg, mrcImage* sig);
extern void lmrcImageDividedByReal(mrcImage* img, double d);
extern void lmrcImageDividedByRealForOnlyPositive(mrcImage* img, double d);
extern void lmrcImageAddedByReal(mrcImage* img, double d);
extern void lmrcImageStdDev(mrcImage* sig, mrcImage* avg, mrcImage* avg2, long num);
extern void lmrcImageStdErr(mrcImage* sig, mrcImage* avg, mrcImage* avg2, long num);
extern void lmrcImageAdd(mrcImage* img2, mrcImage* img1, long* num);
extern void lmrcSQRImageAdd(mrcImage* img2, mrcImage* img1, long* num);
extern void lmrcImageSquare(mrcImage* in);
extern void lmrcImageRoot(mrcImage* in ,double eps);
extern void lmrcImageAbs(mrcImage* out, mrcImage* in);
extern void lmrcImageConvolution(mrcImage* out, mrcImage* in,  mrcImage* kernel, int mode);

/* in mrcImageToIntImage.c */
extern void lmrcImageToIntImage(mrcImage* dst, mrcImage* src, mrcImageParaTypeInteger mode);


extern void lfft2d(mrcImage* fft, mrcImage* img);

extern void lmrcImageFFT(mrcImage* fft, mrcImage* img, long mode);
extern void lmrcImageFFTFirstDimensionOnly(mrcImage* fft, mrcImage* img, long mode);
#ifdef FFTW
extern void lmrcImageFFTWFlagSet(unsigned int flag);
#endif
extern void lmrcFFTFGconj(mrcImage* out, mrcImage* in1, mrcImage* in2);
extern void lmrcFFTFxG(mrcImage* out, mrcImage* in1, mrcImage* in2);
extern void lmrcImageCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, long mode);
extern void lmrcImageCorrelationModePrint(FILE* fpt);

extern void lmrcImageFFTCenterChange(mrcImage* fft, int mode);

/* in lMrcImagePattersonFunctionCalc.c */
extern void lmrcImagePattersonFunctionCalc(mrcImage* out, mrcImage* outFFT, mrcImage* in);
extern void lmrcImagePattersonFunctionPrint(FILE* fpt, mrcImage* in, int mode);
extern void lmrcImageGuinierFunctionPrint(FILE* fpt, mrcImage* in, int mode);

#include "ctfInfo.h"
extern void lmrcImageCorrelationWithCTFCompensation(mrcImage* out, mrcImage* in, ctfInfo* inctf, mrcImage* ref, ctfInfo* refctf, long mode);


/* in mrcError.c */
extern mrcStatusType mrcError(char* message, char* inRtnName, char* callRtnName, mrcStatusType status);
extern mrcStatusType mrcErrorMsg(FILE* fpt, char* message, char* inRtnName, char* callRtnName, mrcStatusType status);
/* in lmrcFFTInfo.c */
#include "Vector.h"
extern floatVector* lmrcFSInfoXAxisMag(mrcImage* fft);
extern floatVector* lmrcFSInfoXAxisPhase(mrcImage* fft);
extern floatVector* lmrcFSInfoYAxisMag(mrcImage* fft);
extern floatVector* lmrcFSInfoYAxisPhase(mrcImage* fft);
/* The returned values are not magnitudes but powers */
extern floatVector* lmrcFSInfoScatteringAngularDistribution(mrcImage* fft);
extern floatVector* lmrcFSInfoScatteringAngularDistributionAverage(mrcImage* fft);
extern floatVector* lmrcFSInfoScatteringAngularDistributionSD(mrcImage* fft);
extern floatVector* lmrcFSInfoSpacing(mrcImage* fft);
extern floatVector** lmrcFSInfoScatteringAngularDistributionDivisionAverage(mrcImage* fft, mrcImageParaTypeReal axis, mrcImageParaTypeInteger n, int mode);
extern floatVector** lmrcFSInfoScatteringAngularDistributionDivisionSD(mrcImage* fft, mrcImageParaTypeReal axis, mrcImageParaTypeInteger n, int mode);
extern floatVector** lmrcFSInfoScatteringAngularDistributionDivisionAverageDelR(mrcImage* fft, mrcImageParaTypeReal axis, mrcImageParaTypeInteger n, mrcImageParaTypeReal delR, int mode);
extern floatVector** lmrcFSInfoScatteringAngularDistributionDivisionSDDelR(mrcImage* fft, mrcImageParaTypeReal axis, mrcImageParaTypeInteger n, mrcImageParaTypeReal delR, int mode);
/* in mrcImageCheckSameSize.c */
extern void lmrcImageCheckSameSize(mrcImage* in, mrcImage* ref);

/* in mrcImageCheckFFT.c */
extern void lmrcImageCheckFFT(mrcImage* in, mrcImage* ref);

/* in lmrcImageSmoothing */
extern void lmrcImageSmoothingModeInfo(FILE* fpt);
extern void lmrcImageSmoothing(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info, long mode);

/* in lmrcImageCVE */
extern void lmrcImageCVE(mrcImage* dst, mrcImage* src, lmrcImageCVEInfo* info);

/* in lmrcImageTfunction */
extern void lmrcImageTfunction(mrcImage* dst, mrcImage* src, lmrcImageTfunctionInfo* info, long mode);

/* in lmrcImageHighlighting */
extern void lmrcImageHighlightingInfoPrint(FILE* fpt);
extern void lmrcImageHighlighting(mrcImage* dst, mrcImage* src, lmrcImageHighlightInfo* info);

/* in lmrcImageLowPassFilter */
extern void lmrcImageLowPassFilter(mrcImage* dst, mrcImage* src, lmrcImageLowPassFilterInfo* info, long mode);

/* in lmrcImageHighPassFilter */
extern void lmrcImageHighPassFilter(mrcImage* dst, mrcImage* src, lmrcImageHighPassFilterInfo* info, long mode);

/* in lmrcImageBandPassFilter */
extern void lmrcImageBandPassFilter(mrcImage* dst, mrcImage* src, lmrcImageBandPassFilterInfo* info, long mode);

/* in lmrcImageShrink */
extern void lmrcImageShrink(mrcImage* dst, mrcImage* src, mrcImageParaTypeIntegerCoord S, long mode);

/* in lmrcImageShift */
extern void lmrcImageShift(mrcImage* out, mrcImage* in, mrcImageParaTypeRealCoord shift, mrcPixelDataHowToGet mode);
extern void lmrcImageShiftFollowingGC(mrcImage* out, mrcImage* in, int mode);

/* in mrcImagePrint */
extern  void mrcInfoPrint(FILE* fpt, mrcImage* mrc, mrcImageParaTypeInteger mode);


/* prototype end */

/* in lmrcImageMultiCTFCompensation.c */
/* struct begin */
#include "ctfInfo.h"
typedef enum lmrcImageMultiCTFCompensationSolventFlatteningMode {
	lmrcImageMultiCTFCompensationSolventFlatteningModeDensityPeakIsSolvent=0,
	lmrcImageMultiCTFCompensationSolventFlatteningModeDefinedSTDIsSolvent=1
} lmrcImageMultiCTFCompensationSolventFlatteningMode;

typedef struct lmrcImageMultiCTFCompensationInfo {
	long   maxiteration;
	double okrms;
	long   diversefactor;
	double z;
	long   nhist;
	FILE*  logfile;
	lmrcImageMultiCTFCompensationSolventFlatteningMode solventMode;
	float  definedSTD;
} lmrcImageMultiCTFCompensationInfo;
/* struct end */

#include "ctfInfo.h"

/* prototype begin */

extern void lmrcImageMultiCTFCompensationInfoInit(lmrcImageMultiCTFCompensationInfo* info);
extern void lmrcImageMultiCTFCompensationInfoSet(lmrcImageMultiCTFCompensationInfo* info);
extern void lmrcImageMultiCTFCompensation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long nfile, lmrcImageMultiCTFCompensationInfo info, long mode);

/* in lmrcImageCTFObservation.c */
extern void lmrcImageCTFObservation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long mode);
extern void lmrcImagesCTFObservation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long mode);

/* in lmrcImageCTFCompensation.c */
extern void lmrcImageCTFCompensation(mrcImage* src, ctfInfo* ctf, long mode);

/* prototype end */


/* in lmrcImageCTFSN.c */
/* struct begin */
typedef struct lmrcImageCTFSNInfo
{
	long mode, deg1, deg2;
	ctfInfo ctf;
} lmrcImageCTFSNInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageCTFSN(mrcImage *outMrc, const mrcImage *inMrc, lmrcImageCTFSNInfo *info, long mode);
/* prototype end */

/* in lmrcImageFourierPowerSpectrum.c */
/* struct begin */
typedef struct mrcImageFourierPowerSpectrum
{
	long n;
	double d, *h;
} mrcImageFourierPowerSpectrum;

typedef struct lmrcImageFourierPowerSpectrumInfo
{
	double dX, dY, dZ;
} lmrcImageFourierPowerSpectrumInfo;
/* struct end */

/* prototype begin */

extern mrcImageFourierPowerSpectrum lmrcImageFourierPowerSpectrumMakeSpectrum(const mrcImage *inFFT, lmrcImageFourierPowerSpectrumInfo *info);
extern void lmrcImageFourierPowerSpectrumDeleteSpectrum(mrcImageFourierPowerSpectrum theSpectrum);
extern mrcImageFourierPowerSpectrum lmrcImageFourierPowerSpectrum(const mrcImage *inMrc, lmrcImageFourierPowerSpectrumInfo *info, long mode);

extern void lmrcImageRotation3DModePrint(FILE* fpt);
extern void lmrcImageRotation3DFollowingEulerAngle(mrcImage* dst, mrcImage* src, const char* m,
	mrcImageParaTypeReal rot1, mrcImageParaTypeReal rot2, mrcImageParaTypeReal rot3, mrcPixelDataHowToGet mode, int mode2);

#include "Matrix3D.h"
extern void lmrcImageRotation3DFollowingMatrix3D(mrcImage* dst, mrcImage* src, Matrix3D mat, mrcPixelDataHowToGet mode, int mode2);

extern void lmrcImageRotation3DFollowingEulerAngle2(mrcImage* dst, mrcImage* src, const char* m,
	mrcImageParaTypeReal rot1, mrcImageParaTypeReal rot2, mrcImageParaTypeReal rot3, mrcPixelDataHowToGet mode, int mode2);

#include "Matrix3D.h"
extern void lmrcImageRotation3DFollowingMatrix3D2(mrcImage* dst, mrcImage* src, Matrix3D mat, mrcPixelDataHowToGet mode, int mode2);

extern void lmrcImageRotation3DZXY(mrcImage* dst, mrcImage* src,
	mrcImageParaTypeReal rotx, mrcImageParaTypeReal roty, mrcImageParaTypeReal rotz, mrcPixelDataHowToGet mode, int mode2);

extern void lmrcImageRotation2D(mrcImage* dst, mrcImage* src, double angle, mrcPixelDataHowToGet mode);
extern void lmrcImageRotation2DPeriodicBoundary(mrcImage* dst, mrcImage* src, double angle, mrcPixelDataHowToGet mode);

/* in mrcImageSectionGet.c */
extern char* mrcImageSectionGetModeDescription(long mode);
extern void mrcImageSectionGet(mrcImage* dst, mrcImage* src, mrcImageParaTypeReal z, long mode);

/* in mrcImageSectionSet.c */
extern void mrcImageSectionSet(mrcImage* dst, mrcImage* src, mrcImageParaTypeReal z, long mode);

extern double lmrcImageMaxDataGet(mrcImage* src, long mode);

/* in lmrcImageStack.c */
extern void lmrcImageStackAlloc(mrcImage* dst, mrcImage* src, int N, int* sp, int mode);
extern void lmrcImageStackPush(mrcImage* dst, mrcImage* src, int* sp, int mode);

// in lmrcImagePixelValueSort.c 
extern void lmrcImagePixelValueSort(double* dst, mrcImage* src, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* MRC_IMAGE_H */