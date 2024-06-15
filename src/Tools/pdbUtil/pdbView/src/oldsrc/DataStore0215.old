#include "./DataStore.hh"
#include <stdlib.h>
#include <string.h>
#include "genUtil.h"


DataStore::DataStore(pdbFile* p)
{
  PDB = p;
  CaList = (struct CALIST*)malloc(sizeof(struct CALIST));
  CaList->AtomSerial = 0;
  CaList->NEXT = NULL;
  CaTop = CaList;
}

void DataStore::SetArea(int i)
{
  Pdb = new pdbRecord*[i];
  Actor = new vtkActor*[i];
  Mapper = new vtkPolyDataMapper*[i];
}

void DataStore::SET(pdbRecord* pdb, void* actor, void* mapper, int i)
{
  Pdb[i] = (pdbRecord*)pdb;
  Actor[i] = (vtkActor*)actor;
  Mapper[i] = (vtkPolyDataMapper*)mapper;

  if(pdbFileIsCA(PDB)){
      tmp = (struct CALIST*)malloc(sizeof(struct CALIST));
      tmp->AtomSerial = i;
      tmp->NEXT = NULL;
      
      CaList->NEXT = tmp;
      CaList = tmp;
      
      cout << form("CA::SET[%d] pickMapper = %d : pdb = %d : Actor = %d\n",i,Mapper[i],Pdb[i],Actor[i]);
      cout << form("LIST AtomSerial= %d \n" ,CaList->AtomSerial);
      
      /*
 
      while(1){
	if(CaList->NEXT == NULL){
	  CaList->NEXT = tmp;
	  break;
	}else{
	  CaList->NEXT = CaList;
	}
      }
      */
      printf("AtomName = %s\n",Pdb[i]->AtomName);
  }
}

vtkPolyDataMapper* DataStore::GetMapper(int i)
{
  cout << form("DataStore:GetActor[%d]....%d :::: GetMapper....%d\n",i,Actor[i],Mapper[i]);
  return Mapper[i];
}

/*
pdbRecord* DataStore::GetMapper(vtkAbstractMapper3D* mapper)
{

  CaList = CaTop;
  for(CaList = CaTop ; CaList->NEXT != NULL ; CaList = CaList->NEXT){
    if(Mapper[CaList->AtomSerial] == mapper){
      return Pdb[CaList->AtomSerial];
      break;
    }
  } 
  return NULL;
}
*/

pdbRecord* DataStore::GetPdb(int i)
{
  //cout << form("DataStore::GetPdb:%d:i=%d:%s\n",Pdb[i],i,Pdb[i]->ResidueName);
  return Pdb[i];
}

vtkActor* DataStore::GetActor(int i)
{
  return Actor[i];
}


void DataStore::ResetCaList()
{
  CaList = CaTop;
}

int DataStore::GetCaListSerial()
{
  CaList = CaList->NEXT;

  if(CaList!=NULL){
    return CaList->AtomSerial;
  }else{
    return -1;
  }
}


char* DataStore::GetOneCharacter(pdbRecord* pdb)
{
  char* temp;
  temp = strdup(pdb->ResidueName);
  
  SSWITCH(temp)
    SCASE("LYS") {
      return "K";
      SBREAK;
    }
    SCASE("ARG") {
      return "R";
      SBREAK;
    }
    SCASE("HIS") {
      return "H";
      SBREAK;
    }
    SCASE("ASP") {
      return "D";
      SBREAK;
    }
    SCASE("GLU") {
      return "E";
      SBREAK;
    }
    SCASE("ASN") {
      return "N";
      SBREAK;
    }
    SCASE("SER") {
      return "S";
      SBREAK;
    }
    SCASE("THR") {
      return "T";
      SBREAK;
    }
    SCASE("TYR") {
      return "Y";
      SBREAK;
    }
    SCASE("ALA") {
      return "A";
      SBREAK;
    }
    SCASE("VAL") {
      return "V";
      SBREAK;
    }
    SCASE("LEU") {
      return "L";
      SBREAK;
    }
    SCASE("ILE") {
      return "I";
      SBREAK;
    }
    SCASE("PRO") {
      return "P";
      SBREAK;
    }
    SCASE("PHE") {
      return "F";
      SBREAK;
    }
    SCASE("MET") {
      return "M";
      SBREAK;
    }
    SCASE("TRP") {
      return "W";
      SBREAK;
    }
    SCASE("GLY") {
      return "G";
      SBREAK;
    }
    SCASE("CYS") {
      return "C";
      SBREAK;
    }

    SDEFAULT {
      SBREAK;
    }
  SSWITCHEND;
   
  return "NULL";
}
