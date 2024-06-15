/*
# pdbView : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : pdbView
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vtk.h>
              
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"

#include "pdbFile.h"



/*
Example:
typedef struct lpdbViewInfo {
	float a;
	int   b;
} lpdbViewInfo;

typedef enum lpdbViewMode {
	a=0,
	b=1
} lpdbViewMode;
*/

int
main(int argc, char* argv[]) 
{
	pdbViewInfo info;
	pdbFile pdb;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

    pdbFileRead(info.fptIn, &pdb);

    vtkRenderer *ren = vtkRenderer::New();
    vtkRenderWindow *renWindow = vtkRenderWindow::New();
    renWindow->AddRenderer(ren);
    vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
    iren->SetRenderWindow(renWindow);

    //Create an actor and give it cone geometry
    vtkConeSource *cone = vtkConeSource::New();
    cone->SetResolution(30);
    vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
    coneMapper->SetInput(cone->GetOutput());
    vtkActor *coneActor = vtkActor::New();
    coneActor->SetMapper(coneMapper);

    //assign our actor to the renderer
    ren->AddActor(coneActor);

    //draw the resulting scene
    renWindow->Render();

    //Begin mouse interaction
    iren->Start();

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
