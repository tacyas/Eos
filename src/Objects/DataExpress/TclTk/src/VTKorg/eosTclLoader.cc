#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcl.h" 
#include "tk.h"

extern int Vtktcl_SafeInit(Tcl_Interp *interp);
class eosTclLoader
{
public:
	Tcl_Interp* interp;
	char w[256];
	char* p;
	FILE* fp;

	eosTclLoader(char* argv);
	void application(Tcl_Interp* interp);
};
 
eosTclLoader::eosTclLoader(char* argv)
{
  interp = Tcl_CreateInterp();      
 
printf("interp=%p \n",interp);

  Tcl_FindExecutable(argv); 

printf("Tcl_Init(interp)=%d  TCL_ERROR=%d\n",Tcl_Init(interp),TCL_ERROR);

  if(Tcl_Init(interp) == TCL_ERROR){ 
    fprintf(stderr, "Tcl interpreter initialization failed.\n");
    return;
  }
  if(Tk_Init(interp) != TCL_OK){
    fprintf(stderr, "FATAL: Tk initialization error: %s\n",
	    Tcl_GetStringResult(interp)); return;
  }

  if(Vtktcl_SafeInit(interp) != TCL_OK){
    fprintf(stderr, "FATAL: Vtk initialization error: %s\n",
	    Tcl_GetStringResult(interp)); return;
  }
  
  application(interp);
  Tcl_DeleteInterp(interp);
  return;
}

void eosTclLoader::application(Tcl_Interp* interp){

  if(TCL_ERROR==Tcl_EvalFile(interp, "ViewWindow.tcl")) {
	//if(TCL_ERROR==Tcl_EvalFile(interp, "./LogFile/MainWindowTclLOG/MainWindowTcl.tcl.030130")){
//if(TCL_ERROR==Tcl_EvalFile(interp, "./LogFile/ViewWindowLOG/ViewWindow.tcl.030214")) {
	fprintf(stderr, "Error: On Evaluation of file\n");
	return;
  }

/*
  fp=fopen("ViewWindow.tcl","r");
  
  for(int i=1;;i++) 
    {
      //strcpy(window, "wm title . VTK<StereoModeWindow>\n button .exit -text EXIT -command exit \n pack .exit");

      if(fgets(w,256,fp)==NULL)break;

      if(Tcl_Eval(interp, w) == TCL_ERROR){
    fprintf(stderr, "Interpretaion error: %s at %d \n",Tcl_GetStringResult(interp),i);        
    return; 
      }       
    }
*/
  Tk_MainLoop();
}


int main(int argc, char* argv[]) 
{
	eosTclLoader *window = new  eosTclLoader(argv[0]);
	
}	
















