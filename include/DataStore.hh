#ifndef DATA_STORE_HH
#define DATA_STORE_HH

#include "pdbFile.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"

class DataStore{
private:

  pdbFile* PDB;
  int All;
  pdbRecord** Pdb;
  vtkActor** Actor;
  vtkPolyDataMapper** Mapper;

  struct CALIST{
    int AtomSerial;
    struct CALIST* NEXT;
  }*CaList;

  struct CALIST* CaTop;
  struct CALIST* tmp;

public:
  DataStore();
  DataStore(pdbFile* p);
  void SetArea(int i);
  void SET(pdbRecord* pdb, void* actor, void* mapper, int i);
  pdbRecord* GetPdb(int i);
  vtkPolyDataMapper* GetMapper(int i);
  char* GetOneCharacter(pdbRecord* pdb);
  char* GetOneCharacter(char* ResName);
  void ResetCaList();
  int GetCaListSerial();
  vtkActor* GetActor(int i);
  int GetAllNumber();
};

#endif /* DATA_STORE_HH */
