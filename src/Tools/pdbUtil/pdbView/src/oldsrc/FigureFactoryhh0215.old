#ifndef FIGURE_FACTORY_HH
#define FIGURE_FACTORY_HH

#include "pdbFile.h"
#include "vtk.h"
#include "./Property.hh"
#include "./DataStore.hh"
#include "./ShapeMaker.hh"
#include "./ActorMaker.hh"

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
  vtkRenderer* ren;
  vtkAssembly* AllMolecule;
  vtkAssembly* CaOnly;
  vtkAssembly* LineOnly;
  Property* property;

public:
  FigureFactory();
  void SetData(void* data, void* p, void* render, Property* prop);
  void MAKE();
  void MakeSphere();
  void MakeLine();
};

#endif /* FIGURE_FACTORY_HH */
