#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPLOT3DReader.h"
#include "vtkStructuredGridOutlineFilter.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkCursor3D.h"
#include "vtkProbeFilter.h"
#include "vtkConeSource.h"
#include "vtkGlyph3D.h"

#include "SaveImage.h"

#define CONEHEIGHT           1.0
#define CONERADIUS           0.5
#define CONERESOLUTION       80

int main(int argc, char* argv[])
{
	mrcViewInfo info;
	pdbFile pdb;

	init0(&info);
    	argCheck(&info, argc, argv);
    	init1(&info);

	DEBUGPRINT("Program Start\n");   

	vtkRenderer *renderer = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(renderer);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);


	// read data
        vtkPLOT3DReader *reader=vtkPLOT3DReader::New();
	 reader->SetXYZFileName("/net/hp01/workC24/home/people/nishida/Eos/util/srcI386LINUX/TclTk/VTKData/Data/combxyz.bin");
	 reader->SetQFileName("/net/hp01/workC24/home/people/nishida/Eos/util/srcI386LINUX/TclTk/VTKData/Data/combq.bin");
	 reader->SetFileFormat(VTK_WHOLE_SINGLE_GRID_NO_IBLANKING);
	 reader->Update;

	 // create outline
	 vtkStructuredGridOutlineFilter *outlineF = vtkStructuredGridOutlineFilter::New();
	 outlineF->SetInput(reader->GetOutput());
	 vtkPolyDataMapper *outlineMapper = vtkPolyDataMapper::New();
	 outlineMapper->SetInput(outlineF->GetOutput());
	 vtkActor *outline = vtkActor::New();
	 outline->SetMapper(outlineMapper);
	 outline->GetProperty()->SetColor(0,0,0);

	 // create cursor	 
	vtkCursor3D *cursor=vtkCursor3D::New();
	 cursor->SetFocalPoint(reader->GetOutput()->GetCenter());
	 cursor->SetModelBounds(reader->GetOutput()->GetBounds());
	 cursor->AxesOn;
	 cursor->OutlineOn;
	 cursor->XShadowsOn;
	 cursor->YShadowsOn;
	 cursor->ZShadowsOn;


    cursor->OutlineOff();
    cursor->XShadowsOff();
    cursor->YShadowsOff();
    cursor->ZShadowsOff();
  vtkPolyDataMapper *cursorMapper = vtkPolyDataMapper::New();
    cursorMapper->SetInput(cursor->GetOutput());
  vtkActor *cursorActor = vtkActor::New();
    cursorActor->SetMapper(cursorMapper);
    cursorActor->GetProperty()->SetColor(1,0,0);

  // create probe
  vtkProbeFilter *probe = vtkProbeFilter::New();
    probe->SetSource(reader->GetOutput());
    probe->SetInput(cursor->GetFocus());

  // create a cone geometry for glyph
  vtkConeSource *cone = vtkConeSource::New();
    cone->SetResolution(16);
    cone->SetRadius(0.25);

  // create glyph
  vtkGlyph3D *glyph = vtkGlyph3D::New();
    glyph->SetInput(probe->GetOutput());
    glyph->SetSource(cone->GetOutput());
    glyph->SetVectorModeToUseVector();
    glyph->SetScaleModeToScaleByScalar();
    glyph->SetScaleFactor(10);
  vtkPolyDataMapper *glyphMapper = vtkPolyDataMapper::New();
    glyphMapper->SetInput(glyph->GetOutput());
  vtkActor *glyphActor = vtkActor::New();
    glyphActor->SetMapper(glyphMapper);

  renderer->AddActor(outline);
  renderer->AddActor(cursorActor);
  renderer->AddActor(glyphActor);
  renderer->SetBackground(1.0,1.0,1.0);
  renWin->SetSize(300,300);
  renWin->Render();

  SAVEIMAGE( renWin );

  iren->Start();

  // Clean up
  renderer->Delete();
  renWin->Delete();
  iren->Delete();
  reader->Delete();
  outlineF->Delete();
  outlineMapper->Delete();
  outline->Delete();
  cursor->Delete();
  cursorMapper->Delete();
  cursorActor->Delete();
  probe->Delete();
  cone->Delete();
  glyph->Delete();
  glyphMapper->Delete();
  glyphActor->Delete();	

  /*	vtkCamera *camera=vtkCamera::New();
	 camera->SetFocalPoint(0,0,0);
	 camera->SetPosition(0,0,10);
	 
	vtkLight *light=vtkLight::New();
	 light->SetFocalPoint(0.21406,1.5,0);
	 light->SetPosition(8.3761,4.94858,4.1250);

	vtkRenderer *ren=vtkRenderer::New();
	 ren->ResetCamera();
	 ren->SetActiveCamera(camera);
	 ren->AddLight(light);

	 vtkRenderWindow *renWin=vtkRenderWindow::New();
	  renWin->AddRenderer(ren);
	  renWin->SetWindowName("eosStereoWindow");
	  renWin->SetSize(300,300);

	 vtkRenderWindowInteractor *iren=vtkRenderWindowInteractor::New();
	 iren->SetRenderWindow(renWin);

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
	

	 ren->AddActor(coneActor);
	 
	 renWin->Render();
	 
	 iren->Start();
*/

  // Clean up
  renderer->Delete();
  renWin->Delete();
  iren->Delete();
  reader->Delete();
  outlineF->Delete();
  outlineMapper->Delete();
  outline->Delete();
  cursor->Delete();
  cursorMapper->Delete();
  cursorActor->Delete();
  probe->Delete();
  cone->Delete();
  glyph->Delete();
  glyphMapper->Delete();
  glyphActor->Delete();
	 
	 exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
