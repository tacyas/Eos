#include "./FigureFactory.hh"


FigureFactory::FigureFactory()
{

}


void FigureFactory::SetData(void* data, void* p, void* render, Property* prop)
{
    dataStore = (DataStore*)data;
    pdb = (pdbFile*)p;
    ren = (vtkRenderer *)render;
    property = (Property*)prop;
}


void FigureFactory::MAKE()
{
  DisplayMode mode;
  mode = property->GetDisplayMode();
  actorMaker = new ActorMaker();
  actorMaker->SetProperty(property);
  
  pdbFileTop(pdb);
  //pdbFileNext(pdb);
  int min = pdb->PDB->ResidueSequenceNumber;
  int max = pdb->PDB->ResidueSequenceNumber;

  while(1){
    if(pdbFileIsAtom(pdb)){
      if((pdb->PDB->ResidueSequenceNumber) > max)
	max = pdb->PDB->ResidueSequenceNumber;
    }
    if(pdbFileEnd(pdb)){
      break;
    } else {
      pdbFileNext(pdb);
    }
  }
  /*
    while(1){
    if(pdbFileIsAtom(pdb)){
    if((pdb->PDB->ResidueSequenceNumber) < min)
    min = pdb->PDB->ResidueSequenceNumber;
      else if((pdb->PDB->ResidueSequenceNumber) > max)
      max = pdb->PDB->ResidueSequenceNumber;
      }
      if(pdbFileEnd(pdb)){
      break;
      } else {
      pdbFileNext(pdb);
      }
      }
    */
  
  dataStore->SetArea(pdb->nAtom);
  printf("min%d max%d\n",min,max);
    property->SetResNumMinAndMax(min, max);
    
    //actorMaker->SetMode((ColorMode)property->GetColorMode());
    
    switch(mode){
    case SpaceFill:
      sphereMaker = new SphereMaker();
      MakeSphere();
      break;
      
    case BackBone:
    sphereMaker = new SphereMaker();
    lineMaker = new LineMaker();
    MakeLine();
    break;
    }
}

void FigureFactory::MakeLine()
{
  float x;
  float y;
  float z;
  int i = 1;
  int j = 1;
  cout << form("PdbFile///// = %d\n",pdb->nAtom);
  dataStore->SetArea(pdb->nAtom);
  
  LineOnly = vtkAssembly::New();
  CaOnly = vtkAssembly::New();

  float BeforePoint[3] = {0, 0, 0};
  float AfterPoint[3] = {0, 0, 0};

  pdbFileTop(pdb);
  while(1){
    if(pdbFileIsAtom(pdb)){
      if(pdbFileIsCA(pdb)){
	pdbFileCoordGet(pdb, &x, &y, &z);
	if(j!=1){
	  AfterPoint[0] = x;
	  AfterPoint[1] = y;
	  AfterPoint[2] = z;
	  lineMaker->MAKE(BeforePoint,AfterPoint);
	  actorMaker->CreateActor();
	  //actorMaker = new ActorMaker();
	  actorMaker->SetMapper(lineMaker->GetMapper());
	  actorMaker->SetColor(pdb->PDB->AtomName,pdb->PDB->ResidueSequenceNumber);
	  //actorMaker->SetColor(0.5, 0.8, 0.9);
	  
	  LineOnly->AddPart(actorMaker->GetActor());
	  
	}
	BeforePoint[0] = x;
	BeforePoint[1] = y;
	BeforePoint[2] = z;
	
	sphereMaker->SetPosition(x, y, z);
	sphereMaker->SetResolution(2 , 2);
	sphereMaker->SetRadius(0.1);
	sphereMaker->MAKE();
	//actorMaker = new ActorMaker();
	actorMaker->CreateActor();
	actorMaker->SetMapper(sphereMaker->GetMapper());
	actorMaker->SetColor(0.5, 0.8, 0.9);
	CaOnly->AddPart(actorMaker->GetActor());
	dataStore->SET(pdb->PDB,actorMaker->GetActor(),sphereMaker->GetMapper(),i);
	j = j + 1;
      }
      i = i + 1;
    }
    if(pdbFileEnd(pdb)){
      break;
    } else {
      pdbFileNext(pdb);
    }
  }
   
  ren->AddActor(CaOnly);  
  ren->AddActor(LineOnly);  
  
  
}




void FigureFactory::MakeSphere()
{
  float x;
  float y;
  float z;
  int i=1;
  
  cout << form("PdbFile///// = %d\n",pdb->nAtom);
  dataStore->SetArea(pdb->nAtom);
  
  AllMolecule = vtkAssembly::New();
  CaOnly = vtkAssembly::New();
  
  pdbFileTop(pdb);
  while(1){
    if(pdbFileIsAtom(pdb)){
      pdbFileCoordGet(pdb, &x, &y, &z);
      sphereMaker->SetRadius(pdb->PDB->AtomName);
      sphereMaker->SetPosition(x, y, z);
      sphereMaker->SetResolution(10 , 10);
      sphereMaker->MAKE();
      actorMaker->CreateActor();
      //actorMaker = new ActorMaker();
      actorMaker->SetMapper(sphereMaker->GetMapper());
      actorMaker->SetColor(pdb->PDB->AtomName,pdb->PDB->ResidueSequenceNumber);
      //actorMaker->SetColor(0.5, 0.8, 0.9);
      AllMolecule->AddPart(actorMaker->GetActor());
      if(pdbFileIsCA(pdb))
	{
	  CaOnly->AddPart(actorMaker->GetActor());
	}
      dataStore->SET(pdb->PDB,actorMaker->GetActor(),sphereMaker->GetMapper(),i);
      
      i=i+1;
    }
    if(pdbFileEnd(pdb)){
      break;
    } else {
      pdbFileNext(pdb);
    }
  }

  if(property->GetAtomMode()==CA){
    ren->AddActor(CaOnly);
  }else{
    ren->AddActor(AllMolecule);
  }
}
