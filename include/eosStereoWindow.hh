#ifndef EOS_STEREO_MODE_ON_HH
#define EOS_STEREO_MODE_ON_HH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <vtkRenderer.h>  
#include <pdbFile.h>        

#include "tcl.h"
#include "tk.h"

#define GLOBAL_DECLARATION

//#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
//#include "vtkGraphicsFactory.h"

class eosInteractorMyStyle;

class eosStereoWindow{

  public:
         eosStereoWindow();
         ~eosStereoWindow();

         void SetFromMainWindow(vtkRenderWindow*);
         static eosStereoWindow* New();
         vtkRenderer* GetRendererLeft(void);
         vtkRenderer* GetRendererRight(void);
         vtkRenderWindow* GetStereoWindow(void);
		 vtkCamera* GetCameraRight(void);
		 vtkCamera* GetCameraLeft(void);
         vtkRenderWindowInteractor* GetRenderWindowInteractor(void);
		 void ShowWindow(void);
         void SetTclWindowInterp(Tcl_Interp*);
 private:
         void init0();
         void init();
         vtkRenderer     *ren,*renLeft,*renRight;
         vtkCamera       *cam,*camLeft,*camRight;
         vtkRenderWindow *renWin,*renWinStereo;
         vtkRenderWindowInteractor *irenStereo;
	 eosInteractorMyStyle *myiStereo;
};

#endif