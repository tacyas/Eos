#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <vtk.h>  
#include <pdbFile.h>        
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

#define CONEHEIGHT            0.1
#define CONERADIUS            0.05
#define CONERESOLUTION        80
#define CONECOLORR            1.0 
#define CONECOLORG            0.0  
#define CONECOLORB            0.0 
#define CONEROTATEX          -30.0 
#define CONEROTATEY           90.0 
#define CONEROTATEZ           0.0 
#define CONEOPACITY           0.2 
#define SPHERERADIUS          0.03
#define SPHERETHETARESOLUTION 30
#define SPHEREPHIRESOLUTION   30 
#define SPHERECOLORR          1.0 
#define SPHERECOLORG          0.0  
#define SPHERECOLORB          1.0 
#define SPHEREOPACITY           0.2 

class eosPicker{
private:
  float x;
  float y;
  float z;
public:
  vtkActor *Actor;
  vtkPolyDataMapper *Mapper;

private:
  void init(void){
    x=y=z=0.0;
    Actor=vtkActor::New();
    Mapper=vtkPolyDataMapper::New();
    Actor->SetPosition(x,y,z);
  }
         
public:
  eosPicker() {
    init();
  }

  eosPicker(float a,float b,float c){
    init();
    x=a;
    y=b;
    z=c;
    Actor->SetPosition(x,y,z);
  }

  vtkActor* GetActor(void){
    return Actor;
  } 

};

/***** class eosConePicker start *****/

class eosConePicker :public eosPicker{
  protected:
         vtkConeSource *cone;

  public:
         eosConePicker(void);
         eosConePicker(float,float,float);
         void eosConePickerSet(void);
};

eosConePicker::eosConePicker(void):eosPicker(){ 
         eosConePickerSet();
}

eosConePicker::eosConePicker(float a,float b,float c):eosPicker(a,b,c){
         eosConePickerSet();
}

void eosConePicker::eosConePickerSet(void){
         cone=vtkConeSource::New();

  	 cone->SetHeight(CONEHEIGHT);
	 cone->SetRadius(CONERADIUS);
	 cone->SetResolution(CONERESOLUTION);

 	 Mapper->SetInput(cone->GetOutput());
	 Actor->SetMapper(Mapper);
	 Actor->GetProperty()->SetColor(CONECOLORR,CONECOLORG,CONECOLORB);
	 //Actor->GetProperty()->SetOpacity(CONEOPACITY);
	 Actor->RotateY(CONEROTATEY);
	 Actor->RotateX(CONEROTATEX);
	 Actor->RotateZ(CONEROTATEZ);
}


/***** class eosSpherePicker start *****/

class eosSpherePicker :public eosPicker{
  protected:
         vtkSphereSource *sphere;

  public:
         eosSpherePicker(void);
         eosSpherePicker(float,float,float);
         void eosSphereSet(void);

};

eosSpherePicker::eosSpherePicker(void):eosPicker(){
  eosSphereSet();
}

eosSpherePicker::eosSpherePicker(float a,float b,float c):eosPicker(a,b,c){
  eosSphereSet();
}

void eosSpherePicker::eosSphereSet(void){
         sphere=vtkSphereSource::New();

	 sphere->SetRadius(SPHERERADIUS);
	 sphere->SetCenter(0.0,0.0,0.0);
	 sphere->SetThetaResolution(SPHERETHETARESOLUTION);
	 sphere->SetPhiResolution(SPHEREPHIRESOLUTION);

 	 Mapper->SetInput(sphere->GetOutput());
	 Actor->SetMapper(Mapper);
	 Actor->GetProperty()->SetColor(SPHERECOLORR,SPHERECOLORG,SPHERECOLORB);
	 Actor->GetProperty()->SetOpacity(SPHEREOPACITY);
}

/***** class WindowPicker start *****/

class eosWindowPicker {
     public:
        vtkRenderer  *ren;
	vtkRenderWindow   *renWindow;
	vtkRenderWindowInteractor  *iren;
	vtkLight *Light;

        eosWindowPicker(void);

        vtkRenderer* GetRenderer(void);
        vtkRenderWindow*  GetRenWin(void);
        vtkRenderWindowInteractor* GetRenWinInte(void);
};

eosWindowPicker::eosWindowPicker(void){
        ren=vtkRenderer::New();
        renWindow=vtkRenderWindow::New();
        iren=vtkRenderWindowInteractor::New();
        Light=vtkLight::New();

        renWindow->AddRenderer(ren);
	renWindow->SetSize(600,600);
	renWindow->StereoRenderOn();
	renWindow->SetStereoTypeToLeft();
	iren->SetRenderWindow(renWindow);
	 
	Light->SetPosition(100,100,100);
	Light->SetFocalPoint(0,0,0);
	ren->AddLight(Light);
      
} 

vtkRenderer* eosWindowPicker::GetRenderer(void){
        return ren; 
}

vtkRenderWindow* eosWindowPicker:: GetRenWin(void){ 
        return renWindow; 
}

vtkRenderWindowInteractor* eosWindowPicker::GetRenWinInte(void){
        return iren; 
}
 

/***** main start *****/

int main(void){

  eosWindowPicker ren;
  eosConePicker cone1(0.1,0.0,0.0),cone2(0,0,0.1),cone3(0,0.1,0);
  eosSpherePicker sphere(0.0,0.0,0.0);

  ren.GetRenderer()->AddActor(cone1.GetActor());
  ren.GetRenderer()->AddActor(cone2.GetActor());
  ren.GetRenderer()->AddActor(cone3.GetActor());
  ren.GetRenderer()->AddActor(sphere.GetActor());

  ren.GetRenderer()->ResetCamera();
  ren.GetRenWin()->Render();
  
  ren.GetRenWinInte()->Start();

  exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
