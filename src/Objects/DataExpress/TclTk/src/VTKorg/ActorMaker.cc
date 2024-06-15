#include "./ActorMaker.hh"

#include "./FunctionMode.hh"

#include <string.h>
#include <math.h>
#include "DataStore.hh"

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


void ActorMaker::ConectDataBase()
{
  dataStore = new DataStore();
  homoStore = new HomologyStore(Prop);
}


void ActorMaker::SetColor(char* AtomName, int ResNum, char* ResName, float x)
{

  switch(Prop->GetColorMode()){
    
  case Monochrome:
    actor->GetProperty()->SetColor(0.5, 0.5, 0.5);
    break;
    
  case CPK:
    CPKcolor(AtomName);
    break;
    
  case Group:
    RedToBlue( (double)(ResNum - Prop->GetResNumMin())/(float)(Prop->GetResNumMax() - Prop->GetResNumMin()) );
    break;

  case Amino:
    AminoColor( dataStore->GetOneCharacter(ResName) );
    break;


  case Temperature:
    printf(" :%d:: x = %f --- ",ResNum,x);
    RedToBlue( (double)(100 - x)/100 );
    break;
    
  case HomoColor:
    if(ResNum==0){
      printf("ResNum==NULL! Error---Color change to Gray");
      actor->GetProperty()->SetColor(0.5, 0.5, 0.5);
    }else if(Conect!=7){
      ConectDataBase();
      Conect = 7;
      RedToBlue(homoStore->GetPercent(ResNum,dataStore->GetOneCharacter(ResName))/100);
    }else{
      RedToBlue(homoStore->GetPercent(ResNum,dataStore->GetOneCharacter(ResName))/100);
     }
  }
}

void ActorMaker::CPKcolor(char* AtomName)
{
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
}


void ActorMaker::AminoColor(char* AminoAcidName)
{
  switch(AminoAcidName[strspn(AminoAcidName," ")]){
  case 'D':
    //bright red :minus charge coo-
    color[0]=1.0; color[1]=0.05; color[2]=0.05;
    break;

  case 'E':
    color[0]=1.0; color[1]=0.05; color[2]=0.05;
    break;

  case 'C':
    //yellow has S
    color[0]=1.0; color[1]=1.0; color[2]=0.02;
    break;

  case 'M':
    color[0]=1.0; color[1]=1.0; color[2]=0.02;
    break;

  case 'K':
    //Blue has PlusCharge
    color[0]=0.05; color[1]=0.1; color[2]=1.0;
    break;

  case 'R':
    color[0]=0.05; color[1]=0.1; color[2]=1.0;
    break;

  case 'S':
    //orange has OH
    color[0]=1.0; color[1]=0.8; color[2]=0.01;
    break;

  case 'T':
    color[0]=1.0; color[1]=0.8; color[2]=0.01;
    break;

  case 'F':
    //midBlue has Ring yaya-sosui
    color[0]=0.1; color[1]=0.1; color[2]=0.8;
    break;

  case 'Y':
    color[0]=0.1; color[1]=0.1; color[2]=0.8;
    break;

  case 'N':
    //cyan
    color[0]=0.01; color[1]=0.95; color[2]=0.95;
    break;

  case 'Q':
    color[0]=0.01; color[1]=0.95; color[2]=0.95;
    break;

  case 'G':
    //light gray
    color[0]=0.8; color[1]=0.8; color[2]=0.8;
    break;

  case 'L':
    //green So-sui
    color[0]=0.05; color[1]=0.7; color[2]=0.05;
    break;

  case 'V':
    color[0]=0.05; color[1]=0.7; color[2]=0.05;
    break;

  case 'I':
    color[0]=0.05; color[1]=0.7; color[2]=0.05;
    break;

  case 'A':
    //dark gray normal amino acid
    color[0]=0.5; color[1]=0.5; color[2]=0.5;
    break;

  case 'W':
    //pink
    color[0]=0.9; color[1]=0.5; color[2]=0.9;
    break;

  case 'H':
    //pale blue proton kuru kamo
    color[0]=0.5; color[1]=0.5; color[2]=0.9;
    break;

  case 'P':
    //flesh  tokushu
    color[0]=0.9; color[1]=0.5; color[2]=0.3;
    break;

  default :
    //supecial dark gray
    color[0]=0.3; color[1]=0.3; color[2]=0.3;
    break;
  }
  
  actor->GetProperty()->SetColor(color); 
}
 
void ActorMaker::RedToBlue(double per)
{
  float x;
  x = (float)per;
  
  printf(" ::: x = %f --- ",x);
  
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
}


void ActorMaker::SetHomoColor(double per)
{
  
  float x;
  x = (float)per;

  //x = (float)(ResNum - min)/(float)(max - min);
  
  printf(" ::: x = %f\n",x);
  
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
  
}
