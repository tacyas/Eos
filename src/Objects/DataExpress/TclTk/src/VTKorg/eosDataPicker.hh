#ifndef EOS_DATA_PICKER_HH
#define EOS_DATA_PICKER_HH

#include "DataSearcher.hh"
#include "DataStore.hh"
#include "PickedDataStore.hh"
#include "FunctionMode.hh"
#include "Property.hh"
#include "pdbFile.h"
#include "vtkActor.h"

#include "eosStereoRenderer.hh"

class eosDataPicker{
private:

  vtkActor* pickActor;
  vtkAbstractMapper3D* pickMapper;

  vtkFollower* tmpTextActor;
  vtkPolyDataMapper* textMapper;
  vtkVectorText* text;

  eosStereoRenderer* ren;
  //vtkRenderer* ren;
  vtkCellPicker* picker;

  pdbRecord* pdbData;
 
  DataStore* dataStore;
  DataSearcher* dataSearcher;

  PickedDataStore* pDataStore;
  Property* property;

public:
  eosDataPicker();

  vtkCellPicker* eosDataPicker::GetPicker();
  void SetData(void* renderer, void* data, Property* p);
  static void annotatePick(void* arg);
  void annotatePick0();
  vtkAbstractMapper3D* GetPickMapper();
};

#endif /* EOS_DATA_SEARCHER */
