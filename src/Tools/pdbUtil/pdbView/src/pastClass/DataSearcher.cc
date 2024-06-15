#include "./DataSearcher.hh"

DataSearcher::DataSearcher()
{

}

void DataSearcher::SetData(void* data, Property* p)
{
  dataStore = (DataStore*)data;
  property = (Property*)p;
}

void DataSearcher::ModeSet(PickMode m)
{
  pickMode = m;
}

char* DataSearcher::GetData(vtkAbstractMapper3D* mapper, PickStatus pStatus)
{
  vtkAbstractMapper3D* map;
  int i = 1;

  printf("%d+++%d+++\n",pStatus,property->GetAtomMode()); 

  AtomMode m;
  m = property->GetAtomMode();
  switch(m){
    
  case CA:  
    printf("DataSearcher->GetData---CA\n");
    dataStore->ResetCaList();
    while(i!=-1){
      i = dataStore->GetCaListSerial();
      map = dataStore->GetMapper(i);
      if(mapper == map){
	  return ReturnText(dataStore->GetPdb(i));
	  break;
      }
    }
    break;
    

  case All:
    printf("DataSearcher->GetData---All\n");
    for(i=1; i<1000000 ; i++){
      map = dataStore->GetMapper(i);
      if(mapper == map){
	  return ReturnText(dataStore->GetPdb(i));
	  break;
      }else if(map == NULL){
	break;
      }
    }
    break;
  }
  
  return NULL;
  
}


int DataSearcher::GetData(vtkAbstractMapper3D* mapper)
{
  vtkAbstractMapper3D* map;
  int i = 1;

  switch(property->GetAtomMode()){
    
  case CA:  
    dataStore->ResetCaList();
    while(i!=-1){
      i = dataStore->GetCaListSerial();
      map = dataStore->GetMapper(i);
      if(mapper == map){
	  return i;
	break;
      }
    }
    break;
    
  case All:
    for(i=1; i<1000000 ; i++){
      map = dataStore->GetMapper(i);
      if(mapper == map){
	return i;
	break;
      }else if(map == NULL){
	break;
      }
    }
    break;
  }  
  return 0;
}



void DataSearcher::SetActor(vtkActor* a)
{
  actor = (vtkActor*)a;
}


void DataSearcher::ResetColor(vtkAbstractMapper3D* mapper, PickStatus p)
{
  int i;
  printf("ResetColor!!!!\n");

  i = GetData(mapper);
  printf("---------------------------%d---------------------\n",i);
  ActorMaker* actorMaker;
  actorMaker = new ActorMaker();

  actorMaker->SetProperty(property);
  actorMaker->SetActor(dataStore->GetActor(i));
  actorMaker->SetColor(dataStore->GetPdb(i)->AtomName, dataStore->GetPdb(i)->ResidueSequenceNumber);
  delete actorMaker;
}


void DataSearcher::ChangeColor(int i)
{
  ActorMaker* actorMaker;
  actorMaker = new ActorMaker();
  printf("ChangeColor!!!!\n");
  actorMaker->SetActor(dataStore->GetActor(i));
  actorMaker->SetColor(0.0, 1.0, 1.0);
  delete actorMaker;
}

char* DataSearcher::ReturnText(pdbRecord* pdb)
{
  
  char* text;
  
  text = (char*)memoryAllocate(sizeof(char)*100, "in ReturnText");
  int ResNum = (int)pdb->ResidueSequenceNumber;
  HomologyStore* homoStore;
  DataBaseNote* dataNote;
  
  switch(pickMode){
  case ResNumber:
    sprintf(text, "%ld",pdb->ResidueSequenceNumber);
    break;
  case AtomName:
    sprintf(text, "%s",pdb->AtomName);
    break;
  case ResName:
    sprintf(text, "%s",pdb->ResidueName);
    break;
  case ChainID:
    sprintf(text, "%c",pdb->ChainIdentifier);
    break;
  case Default:
    sprintf(text, "%c:%s %ld:%s",pdb->ChainIdentifier,pdb->ResidueName,pdb->ResidueSequenceNumber,pdb->AtomName);
    ChangeColor((int)(pdb->AtomSerialNumber));
    break;

  case Homology:
    printf("start\n");
    char* PdbCode;
    PdbCode = (char*)memoryAllocate(sizeof(char)*10, "in ReturnText");
    PdbCode = strdup("0PPP");

    char* ResName;
    ResName = (char*)memoryAllocate(sizeof(char)*10, "in ReturnText");
    ResName = strdup(dataStore->GetOneCharacter(pdb));
    homoStore = new HomologyStore();
    homoStore->SetKey(ResNum,ResName,PdbCode, property->GetHomologyMode()); 
    printf("return\n");    
    printf("Pick --- %c:%s %ld:%s\n",pdb->ChainIdentifier,pdb->ResidueName,pdb->ResidueSequenceNumber,pdb->AtomName);
    sprintf(text, "-%s-",dataStore->GetOneCharacter(pdb));
    ChangeColor((int)(pdb->AtomSerialNumber));
    break;
    

  case Memo:
    
    printf("Memo!!!\n");
    printf("Pick --- %c:%s %ld:%s\n",pdb->ChainIdentifier,pdb->ResidueName,pdb->ResidueSequenceNumber,pdb->AtomName);
    sprintf(text, "Picked");
    
    dataNote = new DataBaseNote();
    dataNote->SetKey(pdb->AtomName,pdb->ResidueName,ResNum); 
    
    ChangeColor((int)(pdb->AtomSerialNumber));
    break;

  }
  return text;
}
