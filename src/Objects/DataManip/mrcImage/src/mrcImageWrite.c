/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageWrite ver %I%
#%Z% Created by tacyas@tkyemghp.phys.s.u-tokyo.ac.jp 
#%Z%
#%Z% Usage : mrcImageWrite 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%mrcImageWrite ver%I%; Date:%D% %Z%";

/* 
*  mrcWriteFile.c
*  Write MRC formated image file.
*  int
*  mrcWriteFile(
*      mrcImage* mrc,    : mrc Image 
*      char* filename,   : Name of a file to write
*      char* message,    : error message
*      long  mode        : read mode
*      )
*     mode 0x00000000: default
*          0x*******1: print data information to stdout.
*          0x*******2: No call for mrcStatDataSet.
*/
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "File.h"
#include "../inc/mrcImage.h"
#include <stdio.h>
#include <stdlib.h>

#define RTN_NAME  "mrcFileWrite"

mrcStatusType
mrcFileWrite(mrcImage* mrc, char* filename, char* message, long mode)
{
    size_t bufsize;

	DEBUGPRINT("mrcFileWrite\n");
	mrcHiddenDataSet(mrc, 0);
    if(mrcFileWriteMode_InfoPrint        &mrcFileWriteModeGet(mode)){
    	mrcInfoPrint(stdout, mrc, 0);
	} else {
		DEBUGPRINT("NoInfoPrint\n");
	}
    if(mrcFileWriteMode_NoCallForStatData&mrcFileWriteModeGet(mode)){
		DEBUGPRINT("NoCallForStatData\n");
	} else {
		mrcStatDataSet(mrc, 0);
	}
    if(NULL==mrc) { 
		fprintf(stderr, "Something Wrong!!");
    }
	{
	FILE* fpt;	
	fpt = fileOpen(filename, "w");
	fclose(fpt);
	}
    mrcHeaderWrite(mrc, filename, "in mrcWriteFile", mode);
#ifdef DEBUG
	{
	FILE* fpt;
	fpt = fileOpen(filename, "r+");
	DEBUGPRINT1("Check Header %d\n", ftell(fpt));
	fseek(fpt, 0L, SEEK_END);
	DEBUGPRINT1("Check Header %d\n", ftell(fpt));
	}
#endif
    mrcImageWrite (mrc, filename, "in mrcWriteFile", mode);
#ifdef DEBUG
	{
	FILE* fpt;
	fpt = fileOpen(filename, "r+");
	DEBUGPRINT1("Check Image %d\n", ftell(fpt));
	fseek(fpt, 0L, SEEK_END);
	DEBUGPRINT1("Check Image %d\n", ftell(fpt));
	}
#endif
    mrcTailerWrite(mrc, filename, "in mrcWriteFile", mode);
#ifdef DEBUG
	{
	FILE* fpt;

	fpt = fileOpen(filename, "r+");
	DEBUGPRINT1("Check Last %d\n", ftell(fpt));
	fseek(fpt, 0L, SEEK_END);
	DEBUGPRINT1("Check Last %d\n", ftell(fpt));
	}
#endif

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


    return MRC_Status_OK;
}
#undef RTN_NAME

#define RTN_NAME  "mrcImageWrite"
mrcStatusType
mrcImageWrite(mrcImage* mrc, char* filename, char* message, long mode)
{
    FILE* fpt;
    size_t bufsize;

	DEBUGPRINT("mrcImageWrite Start\n");

	if(mrc->flagCCP4) {
		mrc->ImageOffset = MRC_HEADER + mrc->Header.ContCCP4.NSYMBT;
	} else {
		mrc->ImageOffset = MRC_HEADER;
	}
    /* file open */
    if(NULL==(fpt=fopen(filename, "rb+"))) {
        return mrcError(message, RTN_NAME, filename, 
		        (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotOpened);
    }
    fseek(fpt, mrc->ImageOffset, SEEK_SET);
    bufsize = mrc->BytePerImage;
    if((bufsize)!=fwrite(mrc->Image, sizeof(char), bufsize, fpt)) {
        return mrcError(message, RTN_NAME, "mrc->Image",
	          (mrcStatusType)mrcStatusMask_ExitFailure|MRC_ImageDataCanNotWrite);
    }
  /* File Close */
    if(EOF==fclose(fpt)) {
      return mrcError(message, RTN_NAME, filename, 
		    (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotClosed);
	}
	DEBUGPRINT("mrcImageWrite End\n");
	return 0;
}
#undef RTN_NAME

#define RTN_NAME  "mrcHeaderWrite"
mrcStatusType
mrcHeaderWrite(mrcImage* mrc, char* filename, char* message, long mode)
{
  FILE* fpt;

  /* file open */
	DEBUGPRINT("mrcHeaderWrite Start\n");

  if(NULL==(fpt=fopen(filename, "rb+"))) {
  	if(NULL==(fpt=fopen(filename, "w"))) {
    	return mrcError(message, RTN_NAME, filename, 
		    (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotOpened);
	}
  }
  /* file header open */

  if((MRC_HEADER)!=fwrite(mrc->Header.All, sizeof(unsigned char), MRC_HEADER, fpt)) {
    return mrcError(message, RTN_NAME, filename, 
             	    (mrcStatusType)mrcStatusMask_ExitFailure
             	                  |MRC_ImageHeaderCanNotWrite);
  }

  /* Symmetry Operator */
  if(mrc->flagCCP4 
   &&0    < mrc->Header.ContCCP4.NSYMBT
   &&NULL!= mrc->SymmetryOperator) {
  		
    if((mrc->Header.ContCCP4.NSYMBT)!=fwrite(mrc->SymmetryOperator, sizeof(char), mrc->Header.ContCCP4.NSYMBT, fpt)) {
      return mrcError(message, RTN_NAME, filename, 
             	    (mrcStatusType)mrcStatusMask_ExitFailure
             	                  |MRC_ImageHeaderCanNotWrite);
    }
  }

  if(EOF==fclose(fpt)) {
    return mrcError(message, RTN_NAME, filename,
		    (mrcStatusType)mrcStatusMask_ExitFailure
				  |MRC_ImageHeaderCanNotWrite);
  }
  DEBUGPRINT("mrcHeaderWrite End\n");

  return 0;
}
#undef RTN_NAME

#define RTN_NAME  "mrcTailerWrite"
mrcStatusType
mrcTailerWrite(mrcImage* mrc, char* filename, char* message, long mode)
{
  FILE* fpt;
  size_t bufsize;
  long i;
  /* file open */
	DEBUGPRINT("mrcTailerWrite Start\n");
  if(NULL==(fpt=fopen(filename, "rb+"))) {
    return mrcError(message, RTN_NAME, filename, 
		    (mrcStatusType)mrcStatusMask_ExitFailure|MRC_FileCanNotOpened);
  }
  bufsize = mrc->BytePerImage;
	DEBUGPRINT2("mrcTailerWrite : Offset %d bufsize %d\n", mrc->ImageOffset, bufsize);
  fseek(fpt, mrc->ImageOffset+bufsize, SEEK_SET);
	DEBUGPRINT1("mrcTailerWrite : Last %d \n", ftell(fpt));
	DEBUGPRINT1("mrcTailerWrite : numTailer %d \n", mrc->numTailer);
  for(i=0; i<mrc->numTailer; i++) {
    if((MRC_TAILER)!=fwrite(mrc->Tailer[i].All, sizeof(char), MRC_TAILER, fpt)) {
     return mrcError(message, RTN_NAME, filename,
		             (mrcStatusType)mrcStatusMask_ExitFailure
				      |MRC_ImageHeaderCanNotWrite);
	}
  }
	DEBUGPRINT1("mrcTailerWrite : Last %d \n", ftell(fpt));
	fseek(fpt, 0L, SEEK_END);
	DEBUGPRINT1("mrcTailerWrite : Last %d \n", ftell(fpt));
  if(EOF==fclose(fpt)) {
    return mrcError(message, RTN_NAME, filename,
		    (mrcStatusType)mrcStatusMask_ExitFailure
				  |MRC_ImageHeaderCanNotWrite);
  }
  DEBUGPRINT("mrcTailerWrite End\n");

  return 0;
}
#undef RTN_NAME
