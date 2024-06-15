#include "eosStereoRenderer.hh"
#include "vtkRenderWindowInteractor.h"
#include "vtkProp3D.h"
#include "vtkCellPicker.h"
#include "vtkMath.h"

#define DEBUG
#include "genUtil.h"

//vtkStandardNewMacro(eosStereoRenderer);

eosStereoRenderer::eosStereoRenderer()
{
	Ren      = vtkRenderer::New();
	RenRight = vtkRenderer::New();
	RenLeft  = vtkRenderer::New();
	RenRight -> SetViewport(0.0,0.0,0.5,1);
	RenLeft  -> SetViewport(0.5,0.0,1.0,1.0);
}

eosStereoRenderer::~eosStereoRenderer()
{
	Ren     ->Delete();
	RenRight->Delete();
	RenLeft ->Delete();
}


eosStereoRenderer *eosStereoRenderer::New()
{
	//vtkObject* ret = vtkObjectFactory::CreateInstance("eosStereoRenderer");
	return new eosStereoRenderer();	
	//return (eosStereoRenderer*)ret;
}

void eosStereoRenderer::AddLight(vtkLight* light)
{
	Ren     ->AddLight(light);
    RenRight->AddLight(light);
    RenLeft ->AddLight(light);
}


void eosStereoRenderer::RemoveLight(vtkLight* light)
{
    Ren     ->RemoveLight(light);
    RenRight->RemoveLight(light);
    RenLeft ->RemoveLight(light);
}

/*
vtkLightCollection* eosStereoRenderer::GetLights()
{
    return Ren->GetLights();
}
*/
/*
vtkVolumeCollection* eosStereoRenderer::GetVolumes()
{
	return Ren->GetVolumes();
}
*/

void eosStereoRenderer::AddActor(vtkActor* actor)
{
	Ren     ->AddActor(actor);
	RenRight->AddActor(actor);
	RenLeft ->AddActor(actor);
}

void eosStereoRenderer::RemoveActor(vtkActor* actor)
{
	Ren     ->RemoveActor(actor);
	RenRight->RemoveActor(actor);
	RenLeft ->RemoveActor(actor);
}

void eosStereoRenderer::AddActor2D(vtkActor2D* actor)
{
    Ren     ->AddActor2D(actor);
    RenRight->AddActor2D(actor);
    RenLeft ->AddActor2D(actor);
}

void eosStereoRenderer::RemoveActor2D(vtkActor2D* actor)
{
    Ren     ->RemoveActor2D(actor);
    RenRight->RemoveActor2D(actor);
    RenLeft ->RemoveActor2D(actor);
}

void eosStereoRenderer::AddActor(vtkAssembly* actor)
{
    Ren     ->AddActor(actor);
    RenRight->AddActor(actor);
    RenLeft ->AddActor(actor);
}

void eosStereoRenderer::RemoveActor(vtkAssembly* actor)
{
    Ren     ->RemoveActor(actor);
    RenRight->RemoveActor(actor);
    RenLeft ->RemoveActor(actor);
}

void eosStereoRenderer::RemoveActor(vtkFollower* actor)
{
    Ren     ->RemoveActor(actor);
	RenRight->RemoveActor(actor);
	RenLeft ->RemoveActor(actor);
}

void eosStereoRenderer::SetBackground(int r,int g,int b)
{
	Ren     ->SetBackground(r,g,b);
	RenRight->SetBackground(r,g,b);
	RenLeft ->SetBackground(r,g,b);
}

/*
vtkActorCollection* eosStereoRenderer::GetActors()
{
    return Ren->GetActors();
}
*/
/*
void eosStereoRenderer::SetActiveCamera(vtkCamera* cam)
{
	Ren     ->SetActiveCamera(cam);
    RenRight->SetActiveCamera(cam);
    RenLeft ->SetActiveCamera(cam);
}
*/

vtkCamera* eosStereoRenderer::GetActiveCamera()
{
	return Ren->GetActiveCamera();
}

/*
vtkCamera* eosStereoRenderer::GetActiveCameraRight()
{
    return RenRight->GetActiveCamera();
}
*/
/*
vtkCamera* eosStereoRenderer::GetActiveCameraLeft()
{
    return RenLeft->GetActiveCamera();
}
*/
/*
void eosStereoRenderer::Clear()
{
    Ren     ->Clear();
    RenRight->Clear();
    RenLeft ->Clear();
}
*/
/*
void eosStereoRenderer::ResetCameraClippingRange()
{
	Ren     ->ResetCameraClippingRange();
	RenRight->ResetCameraClippingRange();
	RenLeft ->ResetCameraClippingRange();
}
*/
/*
void eosStereoRenderer::ResetCameraClippingRange(float* bounds)
{
    Ren     ->ResetCameraClippingRange(bounds);
    RenRight->ResetCameraClippingRange(bounds);
    RenLeft ->ResetCameraClippingRange(bounds);
}
*/
/*
void eosStereoRenderer::ResetCameraClippingRange(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
    Ren     ->ResetCameraClippingRange(xmin,xmax,ymin,ymax,zmin,zmax);
    RenRight->ResetCameraClippingRange(xmin,xmax,ymin,ymax,zmin,zmax);
    RenLeft ->ResetCameraClippingRange(xmin,xmax,ymin,ymax,zmin,zmax);
}
*/

void eosStereoRenderer::ResetCamera()
{
	Ren     ->ResetCamera();
	RenRight->ResetCamera();
	RenLeft ->ResetCamera();
}

/*
void eosStereoRenderer::ResetCamera(float* bounds)
{
    Ren     ->ResetCamera(bounds);
    RenRight->ResetCamera(bounds);
    RenLeft ->ResetCamera(bounds);
}
*/
/*
void eosStereoRenderer::ResetCamera(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax)
{
    Ren     ->ResetCamera(xmin,xmax,ymin,ymax,zmin,zmax);
    RenRight->ResetCamera(xmin,xmax,ymin,ymax,zmin,zmax);
    RenLeft ->ResetCamera(xmin,xmax,ymin,ymax,zmin,zmax);
}
*/
/*
vtkAssemblyPath* eosStereoRenderer::PickProp(float selectionX, float selectionY)
{
	return Ren->PickProp(selectionX,selectionY);
}
*/
/*
vtkAssemblyPath* eosStereoRenderer::PickPropRight(float selectionX, float selectionY)
{
	return RenRight->PickProp(selectionX,selectionY);
}
*/
/*
vtkAssemblyPath* eosStereoRenderer::PickPropLeft(float selectionX, float selectionY)
{
	return RenLeft ->PickProp(selectionX,selectionY);
}
*/
/*
void eosStereoRenderer::SetLightFollowCamera(int a)
{
	Ren     ->SetLightFollowCamera(a);
	RenRight->SetLightFollowCamera(a);
	RenLeft ->SetLightFollowCamera(a);
}
*/
/*
int  eosStereoRenderer::GetLightFollowCamera ()
{
	return Ren->GetLightFollowCamera();
}
*/
/*
int  eosStereoRenderer::GetLightFollowCameraRight()
{
    return RenRight->GetLightFollowCamera();
}
*/
/*
int  eosStereoRenderer::GetLightFollowCameraLeft()
{
    return RenLeft->GetLightFollowCamera();
}
*/
/*
void eosStereoRenderer::LightFollowCameraOn ()
{
	Ren     ->LightFollowCameraOn();
	RenRight->LightFollowCameraOn();
	RenLeft ->LightFollowCameraOn();
}
*/
/*
void eosStereoRenderer::LightFollowCameraOff()
{
    Ren     ->LightFollowCameraOff();
    RenRight->LightFollowCameraOff();
    RenLeft ->LightFollowCameraOff();
}
*/
/*
void eosStereoRenderer::SetInteractive (int a)
{
	Ren     ->SetInteractive(a);
    RenRight->SetInteractive(a);
    RenLeft ->SetInteractive(a);
}
*/
/*
int  GetInteractive ()
{
	return Ren->GetInteractive();
}
*/
/*
void eosStereoRenderer::InteractiveOn()
{
	Ren     ->InteractiveOn();
	RenRight->InteractiveOn();
	RenLeft ->InteractiveOn();
}
*/
/*
void eosStereoRenderer::InteractiveOff()
{
    Ren     ->InteractiveOff();
    RenRight->InteractiveOff();
    RenLeft ->InteractiveOff();
}
*/

vtkRenderer* eosStereoRenderer::GetMainRenderer()
{
    return Ren;
}

vtkRenderer* eosStereoRenderer::GetRightRenderer()
{
	return RenRight;
}

vtkRenderer* eosStereoRenderer::GetLeftRenderer()
{
	return RenLeft;
}


