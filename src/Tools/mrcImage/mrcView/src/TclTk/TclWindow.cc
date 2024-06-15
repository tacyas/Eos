#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcl.h" 
#include "tk.h"

class eosTclWindowForStereo
{
 public:
  Tcl_Interp* interp;
  char window[256];
  char* p;
  FILE* fp;

  eosTclWindowForStereo(char* argv[]);
  void application(Tcl_Interp* interp);
  
};
 
eosTclWindowForStereo::eosTclWindowForStereo(char* argv[])
{
  interp = Tcl_CreateInterp();      
  
  Tcl_FindExecutable(argv[0]); 
      
  if(Tcl_Init(interp) == TCL_ERROR){ 
    fprintf(stderr, "Tcl interpreter initialization failed.\n");
    return;
  }
  if(Tk_Init(interp) != TCL_OK){
    fprintf(stderr, "FATAL: Tk initialization error: %s\n",
	    Tcl_GetStringResult(interp)); return;
  }
  application(interp);
  Tcl_DeleteInterp(interp);
  return;
}

void eosTclWindowForStereo::application(Tcl_Interp* interp){

  fp=fopen("eosWindow.tcl","r");
  
  for(;;)
    {
      //strcpy(window, "wm title . VTK<StereoModeWindow>\n button .exit -text EXIT -command exit \n pack .exit");

      if(fgets(window,256,fp)==NULL)break;

      if(Tcl_Eval(interp, window) == TCL_ERROR){
	fprintf(stderr, "Interpretaion error: %s\n",
		Tcl_GetStringResult(interp) );           
	return;
      }  
    }
  Tk_MainLoop();
}


int main(int argc, char* argv[]) 
{
	eosTclWindowForStereo window(argv);
	
}	



