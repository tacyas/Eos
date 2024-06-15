#ifndef PICKED_DATA_STORE_HH
#define PICKED_DATA_STORE_HH

#include "./FunctionMode.hh"
#include "vtk.h"

class PickedDataStoreElement;

class PickedDataStoreElement {
public:
  vtkVectorText* text;
  vtkAbstractMapper3D* PickedMapper;
  vtkPolyDataMapper* TextMapper;
  vtkFollower* TextActor;
  PickedDataStoreElement* NEXT;
  PickedDataStoreElement* PREV;
  PickedDataStoreElement();
  ~PickedDataStoreElement();
};

class PickedDataStore {
private:
  PickedDataStoreElement* TOP;
  PickedDataStoreElement* CURRENT;
  
public:
  PickedDataStore();
  void APPEND(vtkAbstractMapper3D* mapper);
  void SetNewText(char* c , float x, float y, float z);
  void ToEnd();
  vtkFollower* GetTextActor();
  ~PickedDataStore();
  PickStatus NewOrDelete(vtkAbstractMapper3D* mapper, vtkRenderer* ren);
  
};


#endif /* PICKED_DATA_STORE */
