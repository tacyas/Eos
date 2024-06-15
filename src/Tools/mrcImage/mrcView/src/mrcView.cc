#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <vtk.h>  
#include <pdbFile.h>        
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "vtkXRenderWindow.h"
#include "vtkXRenderWindowInteractor.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
//#include "vtkGraphicsFactory.h"

#include "eosInteractorStyleStereo.hh"
#include "eosInteractorMyStyle.hh"
#include "eosStereoWindow.hh"

#define CONEHEIGHT           1.0
#define CONERADIUS           0.5
#define CONERESOLUTION       80

class mrcView {

  private:
	     eosInteractorMyStyle *myi;
		 eosInteractorStyleStereo *istereo;
		 vtkRenderer     *ren;
         vtkCamera       *cam;
         vtkLight        *light;
         vtkRenderWindow *renWin;
         vtkRenderWindowInteractor *iren;
	public:
         mrcView();
         void init();
         static mrcView* New();
         void eosStereoWindowSet(vtkActor*);
         void run();
         vtkRenderer* GetRenderer(void);
         vtkRenderWindow* GetRenderWindow(void);
};

mrcView::mrcView(){
         init();
}

void mrcView::init(){

     cam=vtkCamera::New();
	 cam->SetFocalPoint(0,0,0);
	 cam->SetPosition(0,0,10);
	 cam->SetEyeAngle(10.0);

	 light=vtkLight::New();
	 light->SetFocalPoint(0.21406,1.5,0);
	 light->SetPosition(8.3761,4.94858,4.1250);
	 light->SetLightType(1);
}


void mrcView::eosStereoWindowSet(vtkActor* eosActor){
     ren=vtkRenderer::New();
	 ren->SetActiveCamera(cam);
	 ren->AddLight(light);
	 ren->AddActor(eosActor);

	 renWin=vtkRenderWindow::New();
	 renWin->AddRenderer(ren);
	 renWin->SetWindowName("eosStereoWindow");
	 renWin->SetSize(300,300);

	 //myi = eosInteractorMyStyle::New();
	 iren=vtkRenderWindowInteractor::New();
	 iren->SetRenderWindow(renWin);
	 //iren->SetInteractorStyle(myi);
	 //myi->SetRenderWindowData(ren,iren);
	 istereo = eosInteractorStyleStereo::New();
	 iren->SetInteractorStyle(istereo);
	 istereo->SetRenderer(ren);
}

void mrcView::run(){
  	 renWin->Render();
	 printf("??\n");  
	 iren->Initialize();
	 iren->Enable();
	 iren->Start();
}

vtkRenderer* mrcView::GetRenderer(void)
{
  return(ren);
}

vtkRenderWindow* mrcView::GetRenderWindow(void)
{
  return(renWin);
}



int main(int argc, char* argv[])
{
	mrcViewInfo info;
	pdbFile pdb;

	init0(&info);
    	argCheck(&info, argc, argv);
    	init1(&info);

	DEBUGPRINT("Program Start\n");   

	vtkConeSource *cone=vtkConeSource::New();
	 cone->SetHeight(CONEHEIGHT);
	 cone->SetRadius(CONERADIUS);
	 cone->SetResolution(CONERESOLUTION);
	vtkPolyDataMapper *coneMapper=vtkPolyDataMapper::New();
	 coneMapper->SetInput(cone->GetOutput());
	vtkActor *coneActor=vtkActor::New();
	 coneActor->SetMapper(coneMapper);
	 coneActor->GetProperty()->SetColor(0.0,0.0,1.0);
	 coneActor->RotateZ(0.0);
	 coneActor->SetPosition(0.0,0.0,0.0);
	 coneActor->RotateY(0.0);
     
	 mrcView win;
	 win.eosStereoWindowSet(coneActor);
	 win.run();    
  
	 exit(EXIT_SUCCESS);
}


void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

