#ifndef FIGURE_FACTORY_HH
#define FIGURE_FACTORY_HH

#include "pdbFile.h"
#include "vtkActor.h"
#include "vtkSphere.h"
#include "Property.hh"
#include "DataStore.hh"
#include "ShapeMaker.hh"
#include "ActorMaker.hh"

#include "eosStereoRenderer.hh"

class FigureFactory
{
private:
  pdbFile* pdb;
  vtkPolyDataMapper* mapper;
  vtkActor* actor;
  DataStore* dataStore;
  SphereMaker* sphereMaker;
  LineMaker* lineMaker;
  ActorMaker* actorMaker;
  eosStereoRenderer* ren;
  //vtkRenderer* ren;
  vtkAssembly* AllMolecule;
  vtkAssembly* CaOnly;
  vtkAssembly* LineOnly;
  Property* property;

  PointMaker* pointMaker;

public:
  FigureFactory();
  void SetData(void* data, void* p, void* render, Property* prop);
  void MAKE();
  void MakeSphere();
  void MakeLine();
  void MakePoint();
};

#endif /* FIGURE_FACTORY_HH */
