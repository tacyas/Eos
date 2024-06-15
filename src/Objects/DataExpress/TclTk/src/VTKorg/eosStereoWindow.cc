#include "./eosInteractorMyStyle.hh"
#include "./eosStereoWindow.hh"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define DEBUG
#include "genUtil.h"

eosStereoWindow::eosStereoWindow(){
  this->init();
}

void eosStereoWindow::init0() {
  renWinStereo = vtkRenderWindow::New();
  irenStereo   = vtkRenderWindowInteractor::New();
  irenStereo->SetRenderWindow(renWinStereo);
  renWinStereo->SetWindowName("StereoWindow(cross eye mode)");
  renWinStereo->SetSize(600,300);

  camLeft =vtkCamera::New();
  camRight=vtkCamera::New();

  renLeft =vtkRenderer::New();
  renRight=vtkRenderer::New();

  renLeft->SetViewport(0,0,0.5,1.0);
  renLeft->SetActiveCamera(camRight);

  renRight->SetViewport(0.5,0,1.0,1.0);
  renRight->SetActiveCamera(camLeft);

  renWinStereo->AddRenderer(renLeft);
  renWinStereo->AddRenderer(renRight);
}

void eosStereoWindow::init(){
  init0();
  myiStereo = eosInteractorMyStyle::New();
  myiStereo->SetStereoInteractor(irenStereo);
  myiStereo->SetPriority(1.0);
  irenStereo->SetInteractorStyle(myiStereo);
  myiStereo->SetInteractor(irenStereo);
}

eosStereoWindow::~eosStereoWindow(){
  //this->renLeft->Delete();
  //this->renRight->Delete();
  //this->camLeft->Delete();
  //this->camRight->Delete();
  //this->myiStereo->Delete();
  //this->irenStereo->Delete();
  this->renWinStereo->Delete();

#ifdef DEBUG
            fprintf(stderr, "In eosStereoWindow::~eosStereoWindow()  Close the stereoWindow\n");
#endif
}

eosStereoWindow *eosStereoWindow::New()
{
  return new eosStereoWindow;
}

void eosStereoWindow::SetFromMainWindow(vtkRenderWindow* renwin) {
    renWin = renwin;
    ren = (vtkRenderer*)renWin->GetRenderers()->GetItemAsObject(0);

    /***** set up cameras *****/
    cam = ren->GetActiveCamera();

    camRight->SetFocalPoint(cam->GetFocalPoint());
    camRight->SetPosition(cam->GetPosition());
    camRight->SetEyeAngle(cam->GetEyeAngle());
	camRight->SetViewUp(cam->GetViewUp());
	camRight->SetDistance(cam->GetDistance());
	camRight->SetParallelProjection(cam->GetParallelProjection());
    camRight->SetViewAngle(cam->GetViewAngle());
	camRight->SetClippingRange(cam->GetClippingRange());
	
    camLeft->SetFocalPoint(cam->GetFocalPoint());
    camLeft->SetPosition(cam->GetPosition());
    camLeft->SetEyeAngle(cam->GetEyeAngle());
    camLeft->SetViewUp(cam->GetViewUp());
    camLeft->SetDistance(cam->GetDistance());
    camLeft->SetParallelProjection(cam->GetParallelProjection());
    camLeft->SetViewAngle(cam->GetViewAngle());
    camLeft->SetClippingRange(cam->GetClippingRange());

    /***** set up Renderers *****/
    renLeft->AddLight((vtkLight*)ren->GetLights()->GetItemAsObject(0));
    renLeft->AddActor((vtkActor*)ren->GetActors()->GetItemAsObject(0));
    
    renRight->AddLight((vtkLight*)ren->GetLights()->GetItemAsObject(0));
    renRight->AddActor((vtkActor*)ren->GetActors()->GetItemAsObject(0));

    /***** create and set up StereoRenderWindow *****/
  
    /***** set up StereoInteractor *****/
	myiStereo->SetRenderWindowData(ren, renwin->GetInteractor()); 
	//myiStereo->TclWindowInterp = (eosInteractorMyStyle *)(renwin->GetInteractor()->GetInteractorStyle())->GetTclWindowInterp();

#ifdef DEBUG
    fprintf(stderr, "== In StereoWindow ==\n"); 
	fprintf(stderr, "Psition camRight:%f,%f,%f   camLeft:%f,%f,%f \n",camRight->GetPosition()[0],camRight->GetPosition()[1],camRight->GetPosition()[2],camLeft->GetPosition()[0],camLeft->GetPosition()[1],camLeft->GetPosition()[2]);
#endif

}

void eosStereoWindow::SetTclWindowInterp(Tcl_Interp* interp)
{
 if(interp!=NULL){
    myiStereo->SetTclWindowInterp(interp);
  }
}

vtkRenderer* eosStereoWindow::GetRendererRight(void)
{
  return(this->renRight);
}
vtkRenderer* eosStereoWindow::GetRendererLeft(void)
{
  return(this->renLeft);
}

vtkRenderWindow* eosStereoWindow::GetStereoWindow(void)
{
  return(this->renWinStereo);
}

vtkCamera* eosStereoWindow::GetCameraRight(void)
{
  return(this->camRight);
}

vtkCamera* eosStereoWindow::GetCameraLeft(void)
{
  return(this->camLeft);
}

vtkRenderWindowInteractor* eosStereoWindow::GetRenderWindowInteractor(void)
{
  return(this->irenStereo);
}

void eosStereoWindow::ShowWindow(void)
{
  irenStereo->Initialize();
  //irenStereo->Render();
  irenStereo->Enable();
  irenStereo->Start();
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
