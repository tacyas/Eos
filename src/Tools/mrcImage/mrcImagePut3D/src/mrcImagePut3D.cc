/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImagePut3D ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImagePut3D
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%mrcImagePut3D ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION

#include "../inc/config.h"

#include "vtk.hh"
#include "vtkmrcImageReader.hh"

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImagePut3DInfo info;
    vtkRenderMaster rm;
	vtkCamera   *camera1;
	vtkCamera   *camera2;
	vtkLight    *light1;
	vtkActor    *actor1, *actor2;
	vtkStructuredPoints *volume;
	vtkFloatScalars *scalars;
	vtkContourFilter *cf;
	vtkPolyMapper *mapper, *omapper;
	vtkOutlineFilter *outline;
	vtkmrcImageReader* aVolume;

	vtkRenderWindow 			*renWin;
	vtkRenderWindowInteractor 	*iren;
	vtkRenderer 				*aren;
	vtkRenderer 				*aren2;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	aVolume = new vtkmrcImageReader;
	aVolume->SetFilename(info.In);
	aVolume->Update();
	// cout << "Our Volume: " << *aVolume;

	// Renderer Set 
	renWin  = rm.MakeRenderWindow();
	iren    = renWin->MakeRenderWindowInteractor();
	aren    = renWin->MakeRenderer();
	// aren2   = renWin->MakeRenderer();

	// renWin->StereoRenderOn();

	// Contour
    cf = new vtkContourFilter;
   	cf->DebugOn();
	cf->SetInput(aVolume->GetOutput());
	cf->SetValue(0, info.Contour);

	// PolyMapper
	mapper = new vtkPolyMapper;
	mapper->SetInput(cf->GetOutput());
	
	// Actor(Contour)
	actor1 = new vtkActor;
	actor1->SetMapper(mapper);
	actor1->GetProperty()->SetColor(1.0, 1.0, 1.0);
	
	// draw an outline
	outline = new vtkOutlineFilter;
	outline->SetInput(aVolume->GetOutput());
	
	// Outline --> Polygon
	omapper = new vtkPolyMapper;
	omapper->SetInput(outline->GetOutput());

    // Actor(Outline) 
	actor2 = new vtkActor;
	actor2->SetMapper(omapper);
	actor2->GetProperty()->SetColor(1,1,1);
	
    // Light 
	light1 = new vtkLight;
    light1->SetColor(1.0, 1.0, 1.0);
    light1->SetPosition(info.xLight,info.yLight,info.zLight);

	// Camera
/*
	camera1 = new vtkCamera;
	camera1->SetViewUp(0.0, 0.0, -1.0);
	camera1->SetPosition(0.0, -1.0, 0.0);
	camera1->SetFocalPoint(0.0, 0.0, 0.0);
	camera1->GetStereo();
	camera1->SetEyeAngle(-6.0);
	camera2 = new vtkCamera;
	camera2->SetViewUp(0.0, 0.0, -1.0);
	camera2->SetPosition(0.0, -1.0, 0.0);
	camera2->SetFocalPoint(0.0, 0.0, 0.0);
	camera2->GetStereo();
	camera2->SetEyeAngle(-6.0);
*/
	// cout << "Our Camera: " << *camera1;


	// Tell a renderer our lights and actors
	aren->AddLights(light1);
	aren->AddActors(actor2);
	aren->AddActors(actor1);
	// aren->SetActiveCamera(camera1);
	aren->SetBackground(0.8,0.8,1.0);

/*
	aren2->AddLights(light1);
	aren2->AddActors(actor2);
	aren2->AddActors(actor1);
	aren2->SetActiveCamera(camera2);
	aren2->SetBackground(0.8,0.8,1.0);

	aren2->GetActiveCamera()->Azimuth(6);
*/
	// Renderer
	renWin->Render();

	// interact with data
	iren->SetDesiredUpdateRate(10);
	iren->Start();
	
 	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{

}
