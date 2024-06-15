#ifndef DATA_STORE_HH
#define DATA_STORE_HH

#include "pdbFile.h"
#include "vtk.h"

class DataStore{
private:

  pdbFile* PDB;

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
  DataStore(pdbFile* p);
  void SetArea(int i);
  void SET(pdbRecord* pdb, void* actor, void* mapper, int i);
  pdbRecord* GetPdb(int i);
  vtkPolyDataMapper* GetMapper(int i);
  char* GetOneCharacter(pdbRecord* pdb);
  void ResetCaList();
  int GetCaListSerial();
  vtkActor* GetActor(int i);
};

#endif /* DATA_STORE_HH */
