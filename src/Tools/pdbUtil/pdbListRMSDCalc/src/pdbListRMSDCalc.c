/*
  # pdbListRMSDCalc : $Revision$  
  # $Date$ 
  # Created by $Author$
  # Usage : pdbListRMSDCalc
  # Attention
  #   $Loccker$
  #  	$State$ 
  #
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "pdbFile.h"

typedef struct lpdbRMSDCalcInfo {
  float a;
  int   b;
} lpdbRMSDCalcInfo;
/* 
   typedef enum lpdbListRMSDCalcMode {
   a=0,
   b=1
   } lpdbListRMSDCalcMode;
*/
FILE** lFileListRead(char * InList,int n);
void lpdbFileListRead(FILE** fpt, pdbFile** pdbArray, int n, int mode);
void lpdbRMSDCalc(pdbFile* pdbRMSD, pdbFile* pdbArray, int n,lpdbRMSDCalcInfo* linfo, FILE* fptRef, int mode);
void additionalUsage();

int
main(int argc, char* argv[]) 
{
  pdbListRMSDCalcInfo info;
  lpdbRMSDCalcInfo linfo;
  pdbFile* pdbArray;
  pdbFile  pdbRMSD;
  int n=0;

  init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);

  fprintf(stderr,"test1:%s\n",info.Ref);
  info.fptIn=lFileListRead(info.InList,info.flagIn);
  lpdbFileListRead(info.fptIn, &pdbArray, info.flagIn, 0); 
  if(info.flagRef) {
  	fprintf(stderr,"test2:%s\n",info.Ref);
  } else {
    if(1==info.mode) {
	  usage(stderr);
    }	
  }

  lpdbRMSDCalc(&pdbRMSD, pdbArray, info.flagIn , &linfo, info.fptRef,info.mode);
  pdbFileWrite(info.fptOut, &pdbRMSD);
  fclose(info.fptOut);

  DEBUGPRINT("Program Start\n");
  return 0; 
}

void
additionalUsage()
{
  fprintf(stderr, "----- Additional Usage -----\n");
  fprintf(stderr, ">> -m  \n");
  fprintf(stderr, " 0: -i only   : against average \n");
  fprintf(stderr, " 1: -i and -r : against reference \n");
  fprintf(stderr, ">> -o \n");
  fprintf(stderr, " Coord: Averged Coord\n");
  fprintf(stderr, " TempFactor: against average or reference\n");
}

FILE** 
lFileListRead(char * InList,int n)
{
  fprintf(stdout,"Linstnum:%d\n",n);
  FILE** fpt;
  FILE* fptList;
  char ss[256];
  int i=0;
  fpt = (FILE**)memoryAllocate(sizeof(FILE*)*n, "in info.fptIn");
  
  if(NULL==(fptList=fopen(InList, "r"))) {
    fprintf(stderr, "File not Opened : %s mode %s\n", InList, "r");
    exit(EXIT_FAILURE);
  }
  while(NULL!=fgets(ss,256,fptList))
    {
      fprintf(stdout,"%d-OpenedFile:%s",i,ss);
      ss[strlen(ss) - 1]='\0';
      fpt[i]=fopen(ss, "r");
      if(NULL==fpt[i]) 
	{
	  fprintf(stderr, "File not Opened : %s mode %s\n", ss, "r");
	  exit(EXIT_FAILURE);
	}
      i++;
    }
  return fpt;
}

void 
lpdbFileListRead(FILE** fptList, pdbFile** pdbArray, int n,int mode)
{
  int i;
  *pdbArray = (pdbFile*)memoryAllocate(sizeof(pdbFile)*n, "in lpdbFileListRead");
  for(i=0; i<n; i++) {
    pdbFileRead(fptList[i], &((*pdbArray)[i]));
  }
  return;
}

void 
lpdbRMSDCalc(pdbFile* pdbRMSD, pdbFile* pdbArray, int n, lpdbRMSDCalcInfo* linfo, FILE* fptRef,int mode)
{
  int i;
  int an;
  int max;
  int nline;
  pdbFile ref;
  int old=0,now=0;

  // fptRef
  if(mode==1) {
    pdbFileRead(fptRef, &ref);
    pdbFileTop(&ref);
  }

  if(n<2) {
    fprintf(stderr, "too few files of PDB\n");
    exit(EXIT_FAILURE);
  }
  
  nline=0;
  for(i=0; i<n; i++) {
    pdbFileTop(&pdbArray[i]);
  }
 
  while(1) {
    now=(int)pdbArray[1].PDB->ChainIdentifier;
    // New
    if(0==nline) {
      pdbFileNew(pdbRMSD);
    } else {
      pdbFileAppend(pdbRMSD);
    }
    nline++;
    // Copy	
    pdbFileOneRecordCopy(pdbRMSD, &pdbArray[0]);
    
    if(pdbFileIsAtom(&pdbArray[0])) {
      // Check
      for(i=1; i<n; i++) {
        if(pdbArray[0].PDB->AtomSerialNumber != pdbArray[i].PDB->AtomSerialNumber) {
          fprintf(stderr, "Not same atom: %d in %d against %d in 0 \n", 
		  pdbArray[i].PDB->AtomSerialNumber, i, 
		  pdbArray[0].PDB->AtomSerialNumber);
	      break;
        }
      }
      // Calc Average Coord
      pdbRMSD->PDB->Coord.x = 0;
      pdbRMSD->PDB->Coord.y = 0;
      pdbRMSD->PDB->Coord.z = 0;
      for(i=0; i<n; i++) {
        pdbRMSD->PDB->Coord.x += pdbArray[i].PDB->Coord.x;
        pdbRMSD->PDB->Coord.y += pdbArray[i].PDB->Coord.y;
        pdbRMSD->PDB->Coord.z += pdbArray[i].PDB->Coord.z;
      }
      pdbRMSD->PDB->Coord.x /= n;
      pdbRMSD->PDB->Coord.y /= n;
      pdbRMSD->PDB->Coord.z /= n;

      // mode_0 Average Coord 
      if(mode==0){
        if(0==nline) {
          pdbFileNew(&ref);
        } else {
          pdbFileAppend(&ref);
        }
        pdbFileOneRecordCopy(&ref,pdbRMSD);
      }

      // RMSD 
      pdbRMSD->PDB->TemperatureFactor = 0; 
      for(i=0; i<n; i++) {
        pdbRMSD->PDB->TemperatureFactor += SQR(pdbArray[i].PDB->Coord.x - ref.PDB->Coord.x);
        pdbRMSD->PDB->TemperatureFactor += SQR(pdbArray[i].PDB->Coord.y - ref.PDB->Coord.y);
        pdbRMSD->PDB->TemperatureFactor += SQR(pdbArray[i].PDB->Coord.z - ref.PDB->Coord.z);
      }
      if(0<pdbRMSD->PDB->TemperatureFactor) {
        pdbRMSD->PDB->TemperatureFactor = sqrt(pdbRMSD->PDB->TemperatureFactor/n);
      }
	}
		
	if(pdbFileEnd(&pdbArray[0]) ) {
	  break;
	} else {
	  for(i=0; i<n; i++) {
	    pdbFileNext(&pdbArray[i]);
	}
	if(mode==1){
	  pdbFileNext(&ref);
	}
  }
  old=now;
}
  return;
}
