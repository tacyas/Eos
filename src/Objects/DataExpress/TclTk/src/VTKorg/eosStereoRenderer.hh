#ifndef EOS_STEREO_RENDERER_HH
#define EOS_STEREO_RENDERER_HH

#include <vtkActor.h> 
#include <vtkRenderer.h>
#include <stdio.h>
#include <math.h>

#include "tcl.h" 
#include "tk.h"
#include "vtkVolumeCollection.h" // Needed for access in inline members 
#include "vtkActorCollection.h" // Needed for access in inline members 
#include "vtkAssemblyPath.h"
#include "vtkProp.h"
#include "vtkAssembly.h"
#include "vtkFollower.h"

extern int Vtktcl_SafeInit(Tcl_Interp *interp);
class VTK_RENDERING_EXPORT eosStereoRenderer
{
public:
	static eosStereoRenderer* New();

	eosStereoRenderer();
	~eosStereoRenderer();

	void AddLight(vtkLight*);
	void RemoveLight(vtkLight*);
	//vtkLightCollection* GetLights();

	//vtkVolumeCollection* GetVolumes();

	//vtkActorCollection* GetActors();

	//void SetActiveCamera(vtkCamera*);
	vtkCamera* GetActiveCamera();
    //vtkCamera* GetActiveCameraRight();
    //vtkCamera* GetActiveCameraLeft();

	//void Clear();

	void SetBackground(int,int,int);

	//void ResetCameraClippingRange();
	//void ResetCameraClippingRange(float bounds[6]);
	//void ResetCameraClippingRange(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
	void ResetCamera();
	//void ResetCamera(float bounds[6]);
	//void ResetCamera(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);

	//vtkAssemblyPath* PickProp(float selectionX, float selectionY);
    //vtkAssemblyPath* PickPropRight(float selectionX, float selectionY);
    //vtkAssemblyPath* PickPropLeft(float selectionX, float selectionY);
	
    vtkRenderer* GetMainRenderer();
	vtkRenderer* GetRightRenderer();
	vtkRenderer* GetLeftRenderer();	
	
	void AddActor(vtkActor*);
	//void AddVolume(vtkActor*);
	void RemoveActor(vtkActor*);
	void AddActor2D(vtkActor2D*);
	void RemoveActor2D(vtkActor2D*);
	void AddActor(vtkAssembly*);
	void RemoveActor(vtkAssembly*);
	void RemoveActor(vtkFollower*);
	
    //void SetLightFollowCamera (int);
    //int  GetLightFollowCamera ();
    //int  GetLightFollowCameraRight ();
    //int  GetLightFollowCameraLeft ();
    //void LightFollowCameraOn ();
    //void LightFollowCameraOff();

	//void SetInteractive (int);
	//int  GetInteractive ();
	//void InteractiveOn();
	//void InteractiveOff();
	
protected:
	vtkRenderer *Ren,*RenRight,*RenLeft;
private:

};

#endif


