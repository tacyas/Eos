#ifndef ACTOR_MAKER_HH
#define ACTOR_MAKER_HH

#include "vtk.h"
#include "Property.hh"
#include "FunctionMode.hh"

class ActorMaker
{
private:
  vtkActor* actor;
  vtkPolyDataMapper* mapper;
  float color[3];
  float* R;
  float* G;
  float* B;
  Property* Prop;
  ColorMode colorMode;

  static const float Red[3];
  static const float CarbonColor[3];
  static const float HydrogenColor[3];
  static const float OxygenColor[3];
  static const float SulphurColor[3];
  static const float NitrogenColor[3];
  static const float DefaultColor[3];

public:
  ActorMaker();
  ActorMaker(vtkActor* a);
  void CreateActor();
  void SetActor(void* a);
  vtkActor* GetActor();
  void SetMapper(void* m);
  void SetPosition(float x, float y, float z);
  void SetColor(float c1, float c2, float c3);
  void SetProperty(Property* p);
  void SetMode(ColorMode m);
  void SetColor(char* AtomName);
  void SetColor(char* AtomName, int ResNum);
};

#endif /*ACTOR_MAKER_HH*/
