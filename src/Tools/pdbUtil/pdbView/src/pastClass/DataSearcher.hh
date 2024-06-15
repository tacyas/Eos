#ifndef DATA_SEARCHER_HH
#define DATA_SEARCHER_HH

#include "DataSearcher.hh"
#include "FunctionMode.hh"
#include "Property.hh"
#include "pdbFile.h"
#include "vtk.h"

class DataSearcher{
private:
  DataStore* dataStore;
  pdbRecord* pdb;
  PickMode pickMode;
  vtkActor* actor;
  Property* property;
  
public:
  DataSearcher();
  void DataSearcher::SetData(void* data, Property* p);
  int DataSearcher::GetData(vtkAbstractMapper3D* mapper);
  char* DataSearcher::GetData(vtkAbstractMapper3D* mapper, PickStatus pStatus);
  void ModeSet(PickMode m);
  char* ReturnText(pdbRecord* pdb);
  void SetActor(vtkActor* a);
  void ChangeColor(vtkAbstractMapper3D* mapper);
  void ChangeColor(int i);
  void ResetColor(vtkAbstractMapper3D* mapper, PickStatus p);
};

#endif /* DATA_SEARCHER */
