#include "eosDataPicker.hh"
#include <stream.h>

eosDataPicker::eosDataPicker()
{
  picker = vtkCellPicker::New();  
  tmpTextActor = vtkFollower::New();
  //textMapper = vtkPolyDataMapper::New();
  text = vtkVectorText::New();
  dataSearcher = new DataSearcher;
  pDataStore = new PickedDataStore;

  //cout << form("eosDataPicker::eosDataPicker!!\n");

  picker->SetEndPickMethod(&annotatePick, this);
}


void eosDataPicker::SetData(void* renderer, void* data, Property* p)
{

  //ren = (vtkRenderer*)renderer;
  ren = (eosStereoRenderer*)renderer;
  dataStore = (DataStore*)data;
  property = (Property*)p;
  dataSearcher->SetData(dataStore, property);

  //cout << form("eosDataPicker::GetData!!\n");
}

void eosDataPicker::annotatePick(void* picker)
{
  //vtkRenderer* ren = (vtkRenderer*)arg;

  //cout << form("eosDataPicker::annotatePick!!\n");

  ((eosDataPicker*)picker)->annotatePick0();
}

vtkCellPicker* eosDataPicker::GetPicker()
{
  return picker;
}

vtkAbstractMapper3D* eosDataPicker::GetPickMapper()
{
  return pickMapper;
}

void eosDataPicker::annotatePick0()
{

  float xp;
  float yp;
  float zp;
  float* pickPos;
  char* temp;

  PickStatus status;


  //-p1=nothings was picked
  if((picker->GetCellId()) < 0)
    {
      tmpTextActor->VisibilityOff();
    }else{
      tmpTextActor->VisibilityOn();
      pickPos = picker->GetPickPosition();
	
      xp = pickPos[0];
      yp = pickPos[1];
      zp = pickPos[2];
      
      pickMapper = picker->GetMapper();
      pickActor = picker->GetActor();  
      dataSearcher->ModeSet(property->GetPickMode());
      //cout << form("address+++A=%d,M=%d\n",pickActor , pickMapper);
      
      if(pDataStore->NewOrDelete(pickMapper, ren)==Delete){
	status = Delete;
	dataSearcher->ResetColor(pickMapper,status);
	printf("Delete!!\n");
	//Color-Change!!

      }else{
	status = Search;
	temp = dataSearcher->GetData(pickMapper,status);
	
	printf("TEXT-YOTEI===========%s\n",temp);
	
	if(pdbData!=NULL){
	  
	  //text->SetText(temp);  
	  
	  pDataStore->SetNewText(temp,xp,yp,zp);	
	  
	}else{
	  text->SetText("Not Identified");
	}
	
	//3D TEXT VERSION
	
	//text->SetText(form("%f,%f,%f",xp,yp,zp));
	
	
	//SetNewText(tmp,xp,yp,zp);
	
      /*
      textMapper->SetInput(text->GetOutput());
      textActor->SetMapper(textMapper);
      textActor->SetScale(0.3,0.3,0.3);
      textActor->SetPosition(xp,yp,zp);
      */
      
      pDataStore->GetTextActor()->SetCamera(ren->GetActiveCamera()); 
      ren->AddActor(pDataStore->GetTextActor());
      }
    }
}
