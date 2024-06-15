#include "./PickedDataStore.hh"
#include "./FunctionMode.hh"

PickedDataStore::PickedDataStore()
{

  CURRENT = TOP = NULL;
}

PickedDataStore::~PickedDataStore()
{
}


PickedDataStoreElement::PickedDataStoreElement() 
{
  text = vtkVectorText::New();
  TextMapper = vtkPolyDataMapper::New();
  TextActor  = vtkFollower::New();
  NEXT = NULL;
  PREV = NULL;
}

PickedDataStoreElement::~PickedDataStoreElement()
{
  fprintf(stderr, "in destructor for PickedDataStoreElement\n");
  text->Delete();
  TextActor->Delete();
  TextMapper->Delete();
}

void PickedDataStore::APPEND(vtkAbstractMapper3D* mapper)
{
  ToEnd();
  PickedDataStoreElement* tmp;
  tmp = new PickedDataStoreElement();
  tmp->PickedMapper = mapper;
  if(CURRENT==NULL){
    TOP = CURRENT = tmp;
    TOP->PREV = NULL;
  }else{
    CURRENT->NEXT = tmp;
    tmp->PREV = CURRENT;
  }
  tmp->NEXT = NULL;
  CURRENT = tmp;
}


void PickedDataStore::SetNewText(char* NewText , float x, float y, float z)
{
  printf("SetNewText+++++\n");

  CURRENT->text->SetText(NewText);
  CURRENT->TextMapper->SetInput(CURRENT->text->GetOutput());
  CURRENT->TextActor->SetMapper(CURRENT->TextMapper);
  CURRENT->TextActor->SetScale(0.3,0.3,0.3);
  CURRENT->TextActor->SetPosition(x,y,z);

  printf("PrintTextActor-%p Mapper-%p\n",CURRENT->TextActor,CURRENT->TextMapper);


}

void PickedDataStore::ToEnd()
{
  if(CURRENT!=NULL){
    while(CURRENT->NEXT!=NULL)
      {
	printf("SetCurrent.....\n");
	CURRENT=CURRENT->NEXT;
      }
  }
}


vtkFollower* PickedDataStore::GetTextActor()
{
  //SetCurrent(CURRENT);
  return CURRENT->TextActor;
}

//PickStatus PickedDataStore::NewOrDelete(vtkAbstractMapper3D* mapper, vtkRenderer* ren)

PickStatus PickedDataStore::NewOrDelete(vtkAbstractMapper3D* mapper, eosStereoRenderer* ren)
{
  PickedDataStoreElement* tmp;
  tmp = TOP;
  PickStatus status = Create;


  if(tmp!=NULL){
    while(tmp!=NULL){
      printf("in NewOrDelete Seaching!-%p-!!\n",tmp->PickedMapper);
      if(tmp->PickedMapper == mapper){
	printf("DELETE START!--- tmp->PickedMapper=%p  textActor= %p\n",
	       tmp->PickedMapper,tmp->TextActor);
	if(tmp->PREV==NULL){
	  if(tmp->NEXT == NULL){
	    TOP = CURRENT = NULL;
	  }else{
	    TOP = tmp->NEXT;
	    TOP->PREV =NULL;
	  }
	}else{
	  if(tmp->NEXT!=NULL){
	  tmp->NEXT->PREV = tmp->PREV;
	  }else{
	  }
	  CURRENT = tmp->PREV;
	  tmp->PREV->NEXT = tmp->NEXT;
	}
	ren->RemoveActor(tmp->TextActor);
	delete tmp;
	status = Delete;
	break;
      }
      tmp = tmp->NEXT;
    }
  }
  
  if(status == Create)    {
      printf("Create New List in NEWORDELETE!!\n");
      APPEND(mapper);
  }

  return status; 
}

