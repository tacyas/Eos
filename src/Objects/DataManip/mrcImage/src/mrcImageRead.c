/*
# mrcImageRead.c  1.5
# The latest update : 03/07/97 at 20:36:50
#
#@(#) mrcImageRead ver 1.5
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageRead 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageRead ver1.5; Date:97/03/07 @(#)";

/* 
*  mrcReadFile.c
*  Read MRC formated image file.
*  int
*  mrcReadFile(
*      char* filename,   : Name of a file to read.
*      mrcImage* mrc,    : mrc Image 
*      char* message,    : error message
*      long  mode        : read mode
*      )
*     mode 0x00000000: default
*          0x*******1: print data information to stdout.
*/
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
#include "lmrcImagePrint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* mrcImageGeneralTypeList[] = {
	"Eos",
	"CCP4-2000",
	"IMODextendedMRC",
	"FEIextendedMRC",
	""
};

#define RTN_NAME  "mrcFileReadGeneral"
mrcStatusType
mrcFileReadGeneral(mrcImage* mrc, char* filename, char* type, char* message, long mode)
{
	SSWITCH(type) 
		SCASE("Eos") {
			mrcFileRead(mrc, filename, message, mode);
			SBREAK;
		}
		SCASE("IMODextendedMRC") {
			mrcFileReadFEIextendedMRC(mrc, filename, message, mode);
			SBREAK;
		}
		SCASE("FEIextendedMRC") {
			mrcFileReadFEIextendedMRC(mrc, filename, message, mode);
			SBREAK;
		}
		SDEFAULT {
			fprintf(stderr, "Not supported type in mrcFileReadGeneral: %s\n", type);
			fprintf(stderr, "Try Eos type\n");
			mrcFileRead(mrc, filename, message, mode);
			SBREAK;
		}
	SSWITCHEND;	

	return MRC_Status_OK;
}
#undef RTN_NAME

#define RTN_NAME  "mrcFileGeneralListPrint"
mrcStatusType
mrcFileGeneralListPrint(FILE* fpt) 
{
	int i=0;
	while(0!=strlen(mrcImageGeneralTypeList[i])) {
		fprintf(fpt, "%s\n", mrcImageGeneralTypeList[i]);
		i++;
	}
	return MRC_Status_OK; 
}
#undef RTN_NAME

#define RTN_NAME  "mrcFileRead"
mrcStatusType
mrcFileRead(mrcImage* mrc, char* filename, char* message, long mode)
{
	DEBUGPRINT("in mrcFileRead\n");
	DEBUGPRINT("mrcInit:HeaderRead and Initialize\n");
    mrcInit(mrc, filename);
	DEBUGPRINT("mrcImageRead:Image Read\n");
    mrcImageRead(mrc, filename, "in mrcReadFile", mode);
	mrcTailerRead(mrc, filename, "in mrcReadFile", mode);
    switch(0x0000000f&mode) {
        case 0 : {
            return MRC_Status_OK;
        }
        case 1 : {
            mrcInfoPrint(stdout, mrc, 0);
       	    return MRC_Status_OK;
        }
  	    default: {
  	        return mrcError(message, RTN_NAME, 
  	  		    "mrcReadFile Mode", 
  	  	        (mrcStatusType)mrcStatusMask_ExitFailure);
        }
    }
}
#undef RTN_NAME

#define RTN_NAME  "mrcFileReadFEIextendedMRC"
mrcStatusType
mrcFileReadFEIextendedMRC(mrcImage* mrc, char* filename, char* message, long mode)
{
	DEBUGPRINT("in mrcFileRead\n");
	DEBUGPRINT("mrcInit:HeaderRead and Initialize\n");
    mrcInit(mrc, filename);
	DEBUGPRINT("mrcImageRead:Image Read\n");
    mrcImageReadFEIextendedMRC (mrc, filename, "in mrcReadFile", mode);
	mrcTailerReadFEIextendedMRC(mrc, filename, "in mrcReadFile", mode);
    switch(0x0000000f&mode) {
        case 0 : {
            return MRC_Status_OK;
        }
        case 1 : {
            mrcInfoPrint(stdout, mrc, 0);
       	    return MRC_Status_OK;
        }
  	    default: {
  	        return mrcError(message, RTN_NAME, 
  	  		    "mrcReadFile Mode", 
  	  	        (mrcStatusType)mrcStatusMask_ExitFailure);
        }
    }
}
#undef RTN_NAME
#define RTN_NAME  "mrcFileReadIMODextendedMRC"
mrcStatusType
mrcFileReadIMODextendedMRC(mrcImage* mrc, char* filename, char* message, long mode)
{
	DEBUGPRINT("in mrcFileRead\n");
	DEBUGPRINT("mrcInit:HeaderRead and Initialize\n");
    mrcInit(mrc, filename);
	DEBUGPRINT("mrcImageRead:Image Read\n");
    mrcImageReadIMODextendedMRC (mrc, filename, "in mrcReadFile", mode);
	mrcTailerReadIMODextendedMRC(mrc, filename, "in mrcReadFile", mode);
    switch(0x0000000f&mode) {
        case 0 : {
            return MRC_Status_OK;
        }
        case 1 : {
            mrcInfoPrint(stdout, mrc, 0);
       	    return MRC_Status_OK;
        }
  	    default: {
  	        return mrcError(message, RTN_NAME, 
  	  		    "mrcReadFile Mode", 
  	  	        (mrcStatusType)mrcStatusMask_ExitFailure);
        }
    }
}
#undef RTN_NAME

#define RTN_NAME  "mrcImageRead"
mrcStatusType
mrcImageReadGeneral(mrcImage* mrc, char* filename, char* type, char* message, long mode)
{
	SSWITCH(type) 
		SCASE("Eos") {
			mrcImageRead(mrc, filename, message, mode);
			SBREAK;
		}
		SCASE("IMODextenedMRC") {
			mrcImageRead(mrc, filename, message, mode);
			SBREAK;
		}
		SCASE("FEIextendedMRC") {
			mrcImageReadFEIextendedMRC(mrc, filename, message, mode);
			SBREAK;
		}
		SDEFAULT {
			fprintf(stderr, "Not supported type in mrcFileReadGeneral: %s\n", type);
			fprintf(stderr, "Try Eos type\n");
			mrcImageRead(mrc, filename, message, mode);
			SBREAK;
		}
	SSWITCHEND;	

	return MRC_Status_OK;

}
#undef RTN_NAME

#define RTN_NAME  "mrcImageRead"
mrcStatusType
mrcImageRead(mrcImage* mrc, char* filename, char* message, long mode)
{
    FILE* fpt;
    size_t bufsize;

    /* file open */
    if(NULL==(fpt=fopen(filename, "rb"))) {
        return mrcError(message, RTN_NAME, filename, 
		        (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotOpened);
    }

    //fseek(fpt, MRC_HEADER, SEEK_SET);
    fseek(fpt, mrc->ImageOffset, SEEK_SET);
    bufsize = mrc->BytePerImage;
    if((bufsize)!=fread(mrc->Image, sizeof(char), bufsize, fpt)) {
        return mrcError(message, RTN_NAME, "mrc->Image",
	          (mrcStatusType)mrcStatusMask_ExitFailure|MRC_ImageDataCanNotRead);
    }
	mrcImageByteSwap(mrc, 0);	
  /* File Close */
    if(EOF==fclose(fpt)) {
      return mrcError(message, RTN_NAME, filename, 
		    (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotClosed);
    }
	return 1;
}

#undef RTN_NAME

#define RTN_NAME  "mrcImageReadFEIextendedMRC"
mrcStatusType
mrcImageReadFEIextendedMRC(mrcImage* mrc, char* filename, char* message, long mode)
{
    FILE* fpt;
    size_t bufsize;

    /* file open */
    if(NULL==(fpt=fopen(filename, "rb"))) {
        return mrcError(message, RTN_NAME, filename, 
		        (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotOpened);
    }

    //fseek(fpt, MRC_HEADER, SEEK_SET);
    fseek(fpt, mrc->ImageOffset+mrc->Header.Cont.NSYMBT, SEEK_SET);
    bufsize = mrc->BytePerImage;
    if((bufsize)!=fread(mrc->Image, sizeof(char), bufsize, fpt)) {
		fprintf(stderr, "Offset: %d %d\n", mrc->ImageOffset, mrc->Header.Cont.NSYMBT);
        return mrcError(message, RTN_NAME, "mrc->Image",
	          (mrcStatusType)mrcStatusMask_ExitFailure|MRC_ImageDataCanNotRead);
    }
	mrcImageByteSwap(mrc, 0);	

  /* File Close */
    if(EOF==fclose(fpt)) {
      return mrcError(message, RTN_NAME, filename, 
		    (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotClosed);
    }
	return 1;
}
#undef RTN_NAME

#define RTN_NAME  "mrcImageReadIMODextendedMRC"
mrcStatusType
mrcImageReadIMODextendedMRC(mrcImage* mrc, char* filename, char* message, long mode)
{
    FILE* fpt;
    size_t bufsize;

    /* file open */
    if(NULL==(fpt=fopen(filename, "rb"))) {
        return mrcError(message, RTN_NAME, filename, 
		        (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotOpened);
    }

    //fseek(fpt, MRC_HEADER, SEEK_SET);
    fseek(fpt, mrc->ImageOffset+mrc->Header.Cont.NSYMBT, SEEK_SET);
    bufsize = mrc->BytePerImage;
    if((bufsize)!=fread(mrc->Image, sizeof(char), bufsize, fpt)) {
		fprintf(stderr, "Offset: %d %d\n", mrc->ImageOffset, mrc->Header.Cont.NSYMBT);
        return mrcError(message, RTN_NAME, "mrc->Image",
	          (mrcStatusType)mrcStatusMask_ExitFailure|MRC_ImageDataCanNotRead);
    }
	mrcImageByteSwap(mrc, 0);	
  /* File Close */
    if(EOF==fclose(fpt)) {
      return mrcError(message, RTN_NAME, filename, 
		    (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotClosed);
    }
	return 1;
}
#undef RTN_NAME
#define RTN_NAME  "mrcImageByteSwap"
int
mrcImageByteSwap(mrcImage* mrc, long mode)
{
    size_t bufsize;
    bufsize = mrc->BytePerImage;

	if(mrc->flagByteSwap) {
		switch(mrc->HeaderMode) {
			case mrcCharImage: {
				memoryByteSwap(mrc->Image, 1, bufsize/1);
				break;
			}

			case mrcShortImage:
			case mrcComplexShortFT: {
				memoryByteSwap(mrc->Image, 2, bufsize/2);
				break;
			}

			case mrcFloatImage: 
			case mrcComplexFloatFT: 
			case mrcLongImage:  {
				memoryByteSwap(mrc->Image, 4, bufsize/4);
				break;
			}

			case mrcDoubleImage:
			case mrcComplexDoubleFT: {
				memoryByteSwap(mrc->Image, 8, bufsize/8);
				break;
			}

			default: {
				fprintf(stderr, "Not supported mode\n");
				exit(EXIT_FAILURE);
				break;
			}
		}
	}
	return 0; 
}

#undef RTN_NAME

#define RTN_NAME  "mrcHeaderRead"
mrcStatusType
mrcHeaderReadGeneral(mrcImage* mrc, char* filename, char* type, char* message, long mode)
{
	SSWITCH(type) 
		SCASE("Eos") {
			mrcHeaderRead(mrc, filename, message, mode);
			SBREAK;
		}
		SCASE("IMODextendedMRC") {
			mrcHeaderRead(mrc, filename, message, mode);
			SBREAK;
		}
		SCASE("FEIextendedMRC") {
			mrcHeaderRead(mrc, filename, message, mode);
			SBREAK;
		}
		SDEFAULT {
			fprintf(stderr, "Not supported type in mrcHeaderReadGeneral: %s\n", type);
			fprintf(stderr, "Try Eos type\n");
			mrcHeaderRead(mrc, filename, message, mode);
			SBREAK;
		}
	SSWITCHEND;	

	return MRC_Status_OK;
}
#undef RTN_NAME

#define RTN_NAME  "mrcHeaderRead"
mrcStatusType
mrcHeaderRead(mrcImage* mrc, char* filename, char* message, long mode)
{
  FILE* fpt;
	
  /* file open */
  if(NULL==(fpt=fopen(filename, "rb"))) {
    return mrcError(message, RTN_NAME, filename, 
		    (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotOpened);
  }
  /* file header open */
  if((MRC_HEADER)!=fread(mrc->Header.All, sizeof(char), MRC_HEADER, fpt)) {
    return mrcError(message, RTN_NAME, filename, 
             	    (mrcStatusType)mrcStatusMask_ExitFailure
             	                  |MRC_ImageHeaderCanNotRead);
  }

  /* File Format Check */
  if(mrc->Header.ContCCP4.MAP[0]=='M'
   &&mrc->Header.ContCCP4.MAP[1]=='A'
   &&mrc->Header.ContCCP4.MAP[2]=='P'
   &&mrc->Header.ContCCP4.MAP[3]==' ') {
   	mrc->flagCCP4=1;
  } else {
   	mrc->flagCCP4=0;
  }

  /* ByteSwap */
#ifdef M68 /* mode should be 0x000000ff */ 
  DEBUGPRINT ("M68\n");
  DEBUGPRINT2("Lower %d Upper %d\n", 0x000000ff&mrc->HeaderMode, 0xff000000&mrc->HeaderMode);
  if(0!=(0xff000000&mrc->HeaderMode) && 0==(0x000000ff&mrc->HeaderMode)) {
#else      /* mode should be 0xff000000 */ 
  DEBUGPRINT ("INTEL\n");
  DEBUGPRINT3("All: %d Lower %d Upper %d\n", 
  	mrc->HeaderMode,
  	0x000000ff&mrc->HeaderMode, 0xff000000&mrc->HeaderMode);
  if(0==(0x000000ff&mrc->HeaderMode) && 0!=(0xff000000&mrc->HeaderMode)) {
#endif
	fprintf(stdout, "BYTESWAP\n"); fflush(stdout);
	DEBUGPRINT("BYTESWAP"); 
  	memoryByteSwap(mrc->Header.All, 4, MRC_HEADER/4);
  	mrc->flagByteSwap = 1;
  } else {
	DEBUGPRINT("BYTESWAP-NO"); 
  	mrc->flagByteSwap = 0;
  }

  /* CCP4-2000 Symmetry Operator Bytes */
  if(mrc->flagCCP4) {
  	mrc->ImageOffset = MRC_HEADER+mrc->Header.ContCCP4.NSYMBT;
	mrc->SymmetryOperator = (mrcImageSymmetryOperator*)memoryAllocate(mrc->Header.ContCCP4.NSYMBT, "SymmetryOperator");
	fseek(fpt, MRC_HEADER, SEEK_SET); 
    if(mrc->Header.ContCCP4.NSYMBT!=fread(mrc->SymmetryOperator, sizeof(char), mrc->Header.ContCCP4.NSYMBT, fpt)) {
      return mrcError(message, RTN_NAME, filename, 
             	    (mrcStatusType)mrcStatusMask_ExitFailure
             	                  |MRC_ImageHeaderCanNotRead);
    }
  } else {
  	mrc->ImageOffset = MRC_HEADER;
  }

  if(EOF==fclose(fpt)) {
    return mrcError(message, RTN_NAME, filename, 
                    (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotClosed);
  }
  return 1;
}
#undef RTN_NAME


#define RTN_NAME  "mrcTailerReadGeneral"
mrcStatusType
mrcTailerReadGeneral(mrcImage* mrc, char* filename, char* type, char* message, long mode)
{
	SSWITCH(type) 
		SCASE("Eos") {
			mrcTailerRead(mrc, filename, message, mode);
			SBREAK;
		}
		SCASE("FEIextendedMRC") {
			mrcTailerReadFEIextendedMRC(mrc, filename, message, mode);
			SBREAK;
		}
		SCASE("IMODextendedMRC") {
			mrcTailerReadIMODextendedMRC(mrc, filename, message, mode);
			SBREAK;
		}
		SDEFAULT {
			fprintf(stderr, "Not supported type in mrcFileReadGeneral: %s\n", type);
			fprintf(stderr, "Try Eos type\n");
			mrcTailerRead(mrc, filename, message, mode);
			SBREAK;
		}
	SSWITCHEND;	

	return MRC_Status_OK;
}
#undef RTN_NAME

#define RTN_NAME  "mrcTailerRead"
mrcStatusType
mrcTailerRead(mrcImage* mrc, char* filename, char* message, long mode)
{
  FILE*  fpt;
  size_t seek;
  size_t bufsize;
  int num, i;
  /* file open */
  if(NULL==(fpt=fopen(filename, "rb"))) {
    return mrcError(message, RTN_NAME, filename, 
		    (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotOpened);
  }
  /* file tailer check */
  bufsize = mrc->BytePerImage;
  fseek(fpt, 0L, SEEK_END); 
  seek = ftell(fpt);
  DEBUGPRINT2("bufsize:%ld seek:%d in mrcTailerRead\n", bufsize, seek);
  if(mrc->ImageOffset + bufsize < seek) {
    num = (seek - (mrc->ImageOffset + bufsize))/MRC_TAILER;
	mrc->numTailer = num;
  } else {
	mrc->numTailer = 0;
  	if(EOF==fclose(fpt)) {
    	return mrcError(message, RTN_NAME, filename, 
                   (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotClosed);
  	}	
	return 1;
  }
  DEBUGPRINT1("Tailer Number:%d in mrcTailerRead\n", num);
  mrcTailerInit(mrc, 0);
  fseek(fpt, mrc->ImageOffset+bufsize, SEEK_SET);
  for(i=0; i<num; i++) {
    if((MRC_TAILER)!=fread(mrc->Tailer[i].All, sizeof(char), MRC_TAILER, fpt)) {
      return mrcError(message, RTN_NAME, filename, 
             	    (mrcStatusType)mrcStatusMask_ExitFailure
             	                  |MRC_ImageHeaderCanNotRead);
	}
	if(mrc->flagByteSwap) {
		memoryByteSwap(mrc->Tailer[i].All, sizeof(mrcImageParaTypeInteger), MRC_TAILER/sizeof(mrcImageParaTypeInteger));
	}
  }
  if(EOF==fclose(fpt)) {
    return mrcError(message, RTN_NAME, filename, 
                    (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotClosed);
  }	
  return 0;
}
#undef RTN_NAME

#define RTN_NAME  "mrcTailerReadFEIextendedMRC"
mrcStatusType
mrcTailerReadFEIextendedMRC(mrcImage* mrc, char* filename, char* message, long mode)
{
	FILE* fpt;

	mrc->numTailer = 0;
	if(NULL==(fpt=fopen(filename, "rb"))) {
		return mrcError(message, RTN_NAME, filename,
			(mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotOpened);
	}
	
	mrc->numFEIHeader = mrc->Header.Cont.NSYMBT/FEI_EXTENDED_HEADER_EACH;
	DEBUGPRINT2("%ld %d\n", mrc->Header.Cont.NSYMBT/sizeof(FEIextendedHeader), mrc->numFEIHeader); 
	mrc->Header.Cont.NSYMBT = 0;
	
	mrc->FEIHeader = (FEIextendedHeader*)memoryAllocate(mrc->numFEIHeader*sizeof(FEIextendedHeader), "in mrcTailerReadFEIextendedMRC");
	fseek(fpt, mrc->ImageOffset, SEEK_SET);
	if(sizeof(FEIextendedHeader)*mrc->numFEIHeader
	   !=fread(mrc->FEIHeader, sizeof(char),  sizeof(FEIextendedHeader)*mrc->numFEIHeader, fpt)) {
		return mrcError(message, RTN_NAME, filename,
			(mrcStatusType)mrcStatusMask_ExitFailure|MRC_ImageHeaderCanNotRead);
	}

	if(EOF==fclose(fpt)) {
		return mrcError(message, RTN_NAME, filename, 
				(mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotClosed);
	}	
	return 0;
}

#undef RTN_NAME

#define RTN_NAME  "mrcTailerReadIMODextendedMRC"
mrcStatusType
mrcTailerReadIMODextendedMRC(mrcImage* mrc, char* filename, char* message, long mode)
{
	FILE* fpt;

	mrc->numTailer = 0;
	if(NULL==(fpt=fopen(filename, "rb"))) {
		return mrcError(message, RTN_NAME, filename,
			(mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotOpened);
	}
	
	mrc->dummyHeaderByte = mrc->Header.Cont.NSYMBT;
	mrc->Header.Cont.NSYMBT = 0;
	
	mrc->dummyHeader = (char*)memoryAllocate(mrc->dummyHeaderByte*sizeof(char), "in mrcTailerReadIMODextendedMRC");
	fseek(fpt, mrc->ImageOffset, SEEK_SET);
	if((sizeof(char)*mrc->dummyHeaderByte)
	   !=fread(mrc->dummyHeader, sizeof(char),  sizeof(char)*mrc->dummyHeaderByte, fpt)) {
		return mrcError(message, RTN_NAME, filename,
			(mrcStatusType)mrcStatusMask_ExitFailure|MRC_ImageHeaderCanNotRead);
	}

	if(EOF==fclose(fpt)) {
		return mrcError(message, RTN_NAME, filename, 
				(mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotClosed);
	}	
	return 0;
}

#undef RTN_NAME
