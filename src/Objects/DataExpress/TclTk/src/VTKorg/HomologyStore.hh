#ifndef HOMOLOGY_STORE_HH
#define HOMOLOGY_STORE_HH

#include "DataBase.hh"
#include "FunctionMode.hh"

#include "Property.hh"
#include "DataStore.hh"

#include "vtkActor.h"

class HomologyStore : public DataBase{
private:
  Property* Prop;

public:
  HomologyStore(Property* p);
  void SetKey(int ResNum, char* ResName,vtkActor* actor);
  //void ChangeColor(int ResNum, char* ResName, DataStore* dataStore);
  double GetPercent(int ResNum, char* ResName);
};

#endif /* HOMOLOGY_STORE */
