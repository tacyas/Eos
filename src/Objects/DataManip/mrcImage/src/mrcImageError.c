/*
*  mrcError.c
*  mrc image utility: Error
*/

#include "../inc/mrcImage.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef INTEL
#include <process.h>
#endif /* INTEL */

static char* __ErrorMessageReferFile[] = {
  "File Can Not Opened",
  "Image Header Can Not Read",
  "Image Data   Can Not Read",
  "Image Header Can Not Write",
  "Image Data   Can Not Write",
  "File Can Not Closed",
  ""
  };

static char* __ErrorMessageReferMemory[] = {
  "Memory Not Allocate",
  ""
  };

static char* __ErrorMessageMode[] = {
  "Mode Not Supported",
  "N.z != 1 at fft format Mode",
  ""
  };

static char* __ErrorMessageMRCInfo[] = {
  "Image Size N is Zero --> Substitute 0 to 1",
  ""
  };

/*                     
*  Routine Name : mrcError
*  Output error message into stderr
*/
mrcStatusType
mrcError(char* message, char* inRtnName, char* callRtnName, mrcStatusType st)
{
  FILE* fpt;
    
  fpt = stderr;
  mrcErrorMsg(fpt, message, inRtnName, callRtnName, st);
  return -1;
}

/*                     
*  Routine Name : mrcErrorMsg
*  Output error message into (FILE* fpt)
*/
mrcStatusType
mrcErrorMsg(FILE* fpt, char* message, char* inRtnName, char* callRtnName, mrcStatusType st)
{
  MRC_Status_t status;

  status.all = st;
  
  fprintf(fpt, "%s: %s: %s : error code %X\n", message, inRtnName, callRtnName, status);

/* Category Check */
  switch(status.status.category) {
    case 0: {
      break;
    }
    case 0x01: {
      fprintf(fpt, "%s\n", __ErrorMessageReferFile[status.status.detail]);
      break;
    }
    case 0x02: {
      fprintf(fpt, "%s\n", __ErrorMessageReferMemory[status.status.detail]);
      break;
    }
    case 0x04: {
      fprintf(fpt, "%s\n", __ErrorMessageMode[status.status.detail]);
      break;
    }
    case 0x08: {
      fprintf(fpt, "%s\n", __ErrorMessageMRCInfo[status.status.detail]);
      break;
    }
    default: {
      fprintf(fpt, "Not Supported Category Error\n");
      break;
    }
  }

  /* Error Level*/
  switch(status.status.level) {
    case 0x00: {
      break;
    }
    case 0x10: {
      fprintf(fpt, "Message Level Error\n");
      break;
    }
    case 0x20: {
      fprintf(fpt, "Information Level Error\n");
      break;
    }
    case 0x40: {
      fprintf(fpt, "Warning Level Error\n");
      break;
    }
    case 0x80: {
      fprintf(fpt, "Exit Level Error\n");
      exit(EXIT_FAILURE);
      break;
    }
    default: {
      fprintf(fpt, "Not Supported Level Error\n");
      break;
    }
  }
  return status.all;
}

