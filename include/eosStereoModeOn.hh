#ifndef EOS_STEREO_MODE_ON_HH
#define EOS_STEREO_MODE_ON_HH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <vtk.h>  
#include <pdbFile.h>        
#define GLOBAL_DECLARATION

//#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
//#include "vtkGraphicsFactory.h"

class eosInteractorMyStyle;

class eosStereoModeOn{

  public:
         eosStereoModeOn();
         ~eosStereoModeOn();

         void SetFromMainWindow(vtkRenderWindow*);
         static eosStereoModeOn* New();
         vtkRenderer* GetRendererLeft(void);
         vtkRenderer* GetRendererRight(void);
         vtkRenderWindowInteractor* GetStereoWindowInteractor(void);
         vtkRenderWindow* GetStereoWindow(void);
		 vtkCamera* GetCameraRight(void);
		 vtkCamera* GetCameraLeft(void);
		 void ShowWindow(void);

    private:
         void init0();
         void init();
         vtkRenderer     *ren,*renLeft,*renRight;
         vtkCamera       *cam,*camLeft,*camRight;
         vtkRenderWindow *renWin,*renWinStereo;
         vtkRenderWindowInteractor *irenStereo;
	 eosInteractorMyStyle *myi,*myiStereo;
};

#endif
