#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stream.h>
#include "vtk.h"

#include <pgsql/libpq-fe.h>

#include "eosInteractorStyleStereo.hh"

#define GLOBAL_DECLARATION
#include "../inc/config.h"

#include "FigureFactory.hh"
#include "ShapeMaker.hh"
#include "DataBase.hh"
#include "DataBaseMaker.hh"
#include "DataBaseNote.hh"
#include "PickedDataStore.hh"
#include "FunctionMode.hh"
#include "Property.hh"
#include "HomologyStore.hh"
#include "DataSearcher.hh"
#include "eosDataPicker.hh"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "DCDFile.h"
#include "Memory.h"

#include "DataStore.hh"
#include "ActorMaker.hh"


#include "vtkTextMapper.h"
#include "vtkPicker.h"


/*
  Example:
  typedef struct lpdbViewInfo {
  float a;
  int   b;
  } lpdbViewInfo;
  
  typedef enum lpdbViewMode {
  a=0,
  b=1
  } lpdbViewMode;
*/


int
main(int argc, char* argv[]) 
{

  pdbViewInfo info;
  pdbFile pdb;
  pdbFile* ppdb;
  DCD    dcd;

  ppdb = &pdb;
  
  init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);
  
  DEBUGPRINT("Program Start\n");

  //cout << "start C++\n";
  pdbFileRead(info.fptIn, &pdb);

  if(info.flagInDCD) {
  	dcd.Open(info.InDCD, "r");
	dcd.HeaderRead(info.InDCD);
	dcd.Read(info.Step);
    dcd.CoordinatesIntoPDB(&pdb, info.Step);	
  }  

  Property property;

  property.SetDisplayMode((DisplayMode)info.DisplayMode);
  property.SetAtomMode((AtomMode)info.AtomMode);
  property.SetColorMode((ColorMode)info.ColorMode);

  //property.SetPickMode(Memo);
  property.SetPickMode(Default);
  //property.SetPickMode(Memo);

  //property.SetHomologyMode(AllData);
  //property.SetHomologyMode(EachData);
  //property.SetHomologyMode(Percentage);

  //FILE* TabFile;
  //DataBaseMaker dataBaseMaker(TabFile, ppdb);

  /* Renderer/RenderWindow/Interactor Created */
  //vtkRenderer *ren = vtkRenderer::New();
  eosStereoRenderer *ren = eosStereoRenderer::New();
  vtkRenderWindow *renWindow = vtkRenderWindow::New();
  //renWindow->AddRenderer(ren);
  renWindow->AddRenderer(ren->GetMainRenderer());
  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWindow);

  DataStore dataStore(ppdb);

  FigureFactory figureFactory;
  figureFactory.SetData(&dataStore, ppdb ,ren, &property);
  figureFactory.MAKE();
  
  eosDataPicker dataPicker;
  dataPicker.SetData(ren,&dataStore,&property);
  iren->SetPicker(dataPicker.GetPicker());


  //SET TEXT 2D VERSION
  vtkTextMapper* tMapper = vtkTextMapper::New();
  tMapper->SetInput("pdbView");
  tMapper->ShadowOn();

  vtkActor2D* tActor = vtkActor2D::New();
  tActor->SetMapper(tMapper);
  tActor->SetPosition(0,0);

  ren->AddActor2D(tActor);


  //Axes
  vtkAxes* axes = vtkAxes::New();
  axes->SetOrigin(0,0,0);
  vtkPolyDataMapper* axesMapper = vtkPolyDataMapper::New();
  axesMapper->SetInput(axes->GetOutput());
  vtkActor* axesActor = vtkActor::New();
  axesActor->SetMapper(axesMapper);
  ren->AddActor(axesActor);


  /*

  //Glay SetColor(0.5,0.5,0.5);
  //red ->SetColor(0.9,0.2,0.0);
  //blue ->SetColor(0.0,0.2,0.8);
  //yellow ->SetColor(0.9,0.85,0.1);
  //cyan ->SetColor(0.0,0.95,0.95);
  //white ->SetColor(1.0,1.0,1.0);
  //pink ->SetColor(0.95,0.2,0.55);
  //green ->SetColor(0.0,0.8,0.3);
  
  //Cube ->SetColor(0.8,0.4,0.7);
  vtkCubeSource *cube2 = vtkCubeSource::New();
  cube2->SetCenter(5,5,5);
  cube2->SetXLength(3);
  cube2->SetYLength(3);
  cube2->SetZLength(3);
  //cube->SetBounds(0.0,0.5,0.0,0.3,0.0,0.2);
  vtkPolyDataMapper *cubeMapper2 = vtkPolyDataMapper::New();
  cubeMapper2->SetInput(cube2->GetOutput());
  vtkActor *cubeActor2 = vtkActor::New();
  cubeActor2->SetMapper(cubeMapper2);
  cubeActor2->GetProperty()->SetOpacity(0.5);
  cubeActor2->GetProperty()->SetColor(0.8,0.4,0.7);

  */
  
  //assign our actor to the renderer
  
  //ren->AddActor(cubeActor);
  //ren->AddActor(cubeActor2);
  ren->SetBackground(0,0,0);
  
  ren->ResetCamera();
  
  renWindow->PolygonSmoothingOff();
  renWindow->PointSmoothingOff();
  renWindow->LineSmoothingOff();
  
  renWindow->SetSize(500,500);
  

  
  eosInteractorStyleStereo* istereo = eosInteractorStyleStereo::New();
  iren->SetInteractorStyle(istereo);
  vtkLight* light = vtkLight::New();
  light->SetFocalPoint(0,0,0);
  light->SetPosition(100,100,100);
  light->SetLightType(1);
  ren->AddLight(light);
  istereo->SetRenderer(ren);
  
  //draw the resulting scene
  renWindow->Render();
  
  //Begin mouse interaction
  iren->Start();
  
  //picker->Pick( 200, 200, 0, ren);
  
  exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
  fprintf(stderr, "----- Additional Usage -----\n");
  Property::PrintDisplayMode(stderr);
  Property::PrintAtomMode(stderr);
  Property::PrintColorMode(stderr);
}

