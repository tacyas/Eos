#include "./ActorMaker.hh"

#include "./FunctionMode.hh"

#include <string.h>
#include <math.h>
/*
float ActorMaker::Red[3] = {1.0 ,0.0, 0.0};
float ActorMaker::CarbonColor[3] = {0.5 ,0.5, 0.5}; //lightGray
float ActorMaker::HydrogenColor[3] = {1.0 ,1.0, 1.0}; //white
float ActorMaker::OxygenColor[3] = {0.9 ,0.1, 0.0}; //Red
float ActorMaker::SulphurColor[3] = {0.9 ,0.85, 0.1}; //Yellow
float ActorMaker::NitrogenColor[3] = {0.5 ,0.5, 0.8}; //lightBlue
float ActorMaker::DefaultColor[3] = {0.3 ,0.3, 0.3}; //darkGray
*/

const float ActorMaker::Red[3] = {1.0 ,0.0, 0.0};
const float ActorMaker::CarbonColor[3] = {0.5 ,0.5, 0.5}; //lightGray
const float ActorMaker::HydrogenColor[3] = {1.0 ,1.0, 1.0}; //white
const float ActorMaker::OxygenColor[3] = {0.9 ,0.1, 0.0}; //Red
const float ActorMaker::SulphurColor[3] = {0.9 ,0.85, 0.1}; //Yellow
const float ActorMaker::NitrogenColor[3] = {0.5 ,0.5, 0.8}; //lightBlue
const float ActorMaker::DefaultColor[3] = {0.3 ,0.3, 0.3}; //darkGray

ActorMaker::ActorMaker()
{

  actor = vtkActor::New();
  color[0] = 0.5;
  color[1] = 0.5;
  color[2] = 0.5;

  SetColor(0.5, 0.5, 0.5);
}

ActorMaker::ActorMaker(vtkActor* a)
{
  color[0] = 0.5;
  color[1] = 0.5;
  color[2] = 0.5;
  actor = (vtkActor*)a;
  SetColor(0.5, 0.5, 0.5);
}

void ActorMaker::CreateActor()
{
  actor = vtkActor::New();
  color[0] = 0.5;
  color[1] = 0.5;
  color[2] = 0.5;
  SetColor(0.5, 0.5, 0.5);
}

void ActorMaker::SetActor(void* a)
{
  actor = (vtkActor*)a;
}

vtkActor* ActorMaker::GetActor()
{
  return actor;
}

void ActorMaker::SetMapper(void* m)
{
  mapper = (vtkPolyDataMapper*)m;
  actor->SetMapper(mapper);
}

void ActorMaker::SetPosition(float x, float y, float z)
{
      actor->SetPosition(x,y,z);
      //  cout << form("Position = %f : %f : %f\n",x,y,z);
}

void ActorMaker::SetColor(float c1, float c2, float c3)
{
  if(c1 < 1.0)
    color[0] = c1;
  if (c2 < 1.0)
    color[1] = c2;
  if (c3 < 1.0)
    color[2] = c3;
  actor->GetProperty()->SetColor(color);
}

void ActorMaker::SetMode(ColorMode m)
{
  colorMode = (ColorMode)m;
}

void ActorMaker::SetProperty(Property* p)
{
  Prop = p;
}

/*
void ActorMaker::SetColor(char* AtomName)
{
    switch(property->GetColorMode()){
      
      case Monochrome:
      actor->GetProperty()->SetColor(0.5, 0.5, 0.5);
      break;
      
      case CPK:
      if(strchr(AtomName,'C')!=NULL){
	//lightgray
	color[0]=0.8; color[1]=0.8; color[2]=0.8;
      }else if(strchr(AtomName,'H')!=NULL){
	//white
	color[0]=1.0; color[1]=1.0; color[2]=1.0;
      }else if(strchr(AtomName,'O')!=NULL){
	//red
	color[0]=0.9; color[1]=0.2; color[2]=0.0;
      }else if(strchr(AtomName,'S')!=NULL){
	//yellow
	color[0]=0.9; color[1]=0.85; color[2]=0.1;
      }else if(strchr(AtomName,'N')!=NULL){
	//lightblue
	color[0]=0.5; color[1]=0.5; color[2]=0.8;
      }else{
	//darkgray
	color[0]=0.3; color[1]=0.3; color[2]=0.3;
      }
      actor->GetProperty()->SetColor(color);
      break;
      
    }
}

*/

void ActorMaker::SetColor(char* AtomName)
{
    switch(Prop->GetColorMode()){
      
      case Monochrome:
      actor->GetProperty()->SetColor(0.5, 0.5, 0.5);
      break;
      
      case CPK:
	switch(AtomName[strspn(AtomName," ")]){
	case 'C':
	//lightgray
	color[0]=0.5; color[1]=0.5; color[2]=0.5;
	break;

	case 'H':
	//white
	color[0]=1.0; color[1]=1.0; color[2]=1.0;
	break;

	case 'O':
	//red
	color[0]=0.9; color[1]=0.2; color[2]=0.0;
	break;

	case 'S':
	//yellow
	color[0]=0.9; color[1]=0.85; color[2]=0.1;
	break;

	case 'N':
	//lightblue
	color[0]=0.5; color[1]=0.5; color[2]=0.8;
	break;

	default:
	//darkgray
	color[0]=0.3; color[1]=0.3; color[2]=0.3;
	break;

	}
	actor->GetProperty()->SetColor(color);
	break;

    case Group:
      break;
      
    }
}

void ActorMaker::SetColor(char* AtomName, int ResNum)
{

  switch(Prop->GetColorMode()){
    
  case Monochrome:
    actor->GetProperty()->SetColor(0.5, 0.5, 0.5);
    break;
    
  case CPK:
    switch(AtomName[strspn(AtomName," ")]){

    case 'C':
      actor->GetProperty()->SetColor((float*)CarbonColor);
      break;
      
    case 'H':
      actor->GetProperty()->SetColor((float*)HydrogenColor);
      break;
      
    case 'O':
      actor->GetProperty()->SetColor((float*)OxygenColor);
      break;
      
    case 'S':
      actor->GetProperty()->SetColor((float*)SulphurColor);
      break;
      
    case 'N':
      actor->GetProperty()->SetColor((float*)NitrogenColor);
      break;
      
    default:
      actor->GetProperty()->SetColor((float*)DefaultColor);
      break;
      
    }
    //actor->GetProperty()->SetColor(color);
    //break;
    /*

    case 'C':
      //lightgray
      color[0]=0.5; color[1]=0.5; color[2]=0.5;
      break;
      
    case 'H':
      //white
      color[0]=1.0; color[1]=1.0; color[2]=1.0;
      break;
      
    case 'O':
      //red
      color[0]=0.9; color[1]=0.2; color[2]=0.0;
      break;
      
    case 'S':
      //yellow
      color[0]=0.9; color[1]=0.85; color[2]=0.1;
      break;
      
    case 'N':
      //lightblue
      color[0]=0.5; color[1]=0.5; color[2]=0.8;
      break;
      
    default:
      //darkgray
      color[0]=0.3; color[1]=0.3; color[2]=0.3;
      break;
      
    }
    actor->GetProperty()->SetColor(color);
    break;
    */
    break;
    
  case Group:
    float x;
    x = (float)(ResNum - Prop->GetResNumMin())/(float)(Prop->GetResNumMax() - Prop->GetResNumMin());

    printf("ResNum %d ::: x = %f\n",ResNum,x);

    color[0] = (float)-4*fabs(x)+2;
    color[1] = (float)-4*fabs(x-0.5)+2;
    color[2] = (float)-4*fabs(x-1)+2;

    if(color[0]>1){color[0] = 1;}
    if(color[1]>1){color[1] = 1;}
    if(color[2]>1){color[2] = 1;}

    if(color[0]<0){color[0] = 0;}
    if(color[1]<0){color[1] = 0;}
    if(color[2]<0){color[2] = 0;}


    printf("R %f  G %f  B %f\n",color[0],color[1],color[2]);
   
    actor->GetProperty()->SetColor(color);
    break;
  }
}

/*


	switch(AtomName[strspn(AtomName," ")]){
	case 'C':
	actor->GetProperty()->SetColor(CarbonColor);
	break;

	case 'H':
	actor->GetProperty()->SetColor(HydrogenColor);
	break;

	case 'O':
	actor->GetProperty()->SetColor(OxygenColor);
	break;

	case 'S':
	actor->GetProperty()->SetColor(SulphurColor);
	break;

	case 'N':
	actor->GetProperty()->SetColor(NitrogenColor);
	break;

	default:
	actor->GetProperty()->SetColor(DefaultColor);
	break;

	}
	actor->GetProperty()->SetColor(color);
	break;

*/
