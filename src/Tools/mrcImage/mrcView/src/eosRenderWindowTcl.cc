// tcl wrapper for vtkRenderWindow object
//
#include "vtkSystemIncludes.h"
#include "vtkRenderWindow.h"

#include "vtkTclUtil.h"

int vtkRenderWindowCppCommand(vtkRenderWindow *op, Tcl_Interp *interp,int argc, char *argv[]);
int VTKTCL_EXPORT eosRenderWindowCppCommand(eosRenderWindow *op, Tcl_Interp *interp,int argc, char *argv[]);


ClientData vtkRenderWindowNewCommand()
{
  vtkRenderWindow *temp = vtkRenderWindow::New();
  return ((ClientData)temp);
}


int VTKTCL_EXPORT eosRenderWindowCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[])
{
  if ((argc == 2)&&(!strcmp("Delete",argv[1]))&& !vtkTclInDelete(interp))
    {
      Tcl_DeleteCommand(interp,argv[0]);
      return TCL_OK;
    }
  return eosRenderWindowCppCommand((vtkRenderWindow *)(((vtkTclCommandArgStruct *)cd)->Pointer),interp, argc, argv);
}


int VTKTCL_EXPORT eosRenderWindowCppCommand(vtkRenderWindow *op, Tcl_Interp *interp,
					    int argc, char *argv[])
{
  int    tempi;
  double tempd;
  static char temps[80];
  int    error;
  
  error = 0; error = error;
  tempi = 0; tempi = tempi;
  tempd = 0; tempd = tempd;
  temps[0] = 0; temps[0] = temps[0];
  
  if (argc < 2)
    {
      Tcl_SetResult(interp, (char *) "Could not find requested method.", TCL_VOLATILE);
      return TCL_ERROR;
    }
  
  if (!interp)
    {
      if (!strcmp("DoTypecasting",argv[0]))
	{
	  if (!strcmp("eosRenderWindow",argv[1]))
	    {
	      argv[2] = (char *)((void *)op);
	      return TCL_OK;
	    }
	  if (vtkRenderWindowCppCommand((vtkRenderWindow *)op,interp,argc,argv) == TCL_OK)
	    {
	      return TCL_OK;
	    }
	}
      return TCL_ERROR;
    }
  
  
  if ((!strcmp("StereoOn",argv[1]))&&(argc == 2))
    {
      vtkRenderWindow  *temp20;
      int eosRenderWindowCommand(ClientData, Tcl_Interp *, int, char *[]);
      error = 0;

      if (!error)
	{
	  temp20 = (op)->New();
	  vtkTclGetObjectFromPointer(interp,(void *)temp20,eosRenderWindowCommand);
	  return TCL_OK;
	}
    }
  
  if ((!strcmp("StereoOff",argv[1]))&&(argc == 2))
    {
      return TCL_OK;
    }
  
  if ((!strcmp("Rotate",argv[1]))&&(argc == 2))
    {
      return TCL_OK;
    }
  
  if ((!strcmp("Reset",argv[1]))&&(argc == 2))
    {
      return TCL_OK;
    }
  
  
  if (!strcmp("ListMethods",argv[1]))
    {
      vtkRenderWindowCppCommand(op,interp,argc,argv);
      Tcl_AppendResult(interp,"Methods from vtkRenderWindow:\n",NULL);
      Tcl_AppendResult(interp,"  New\n",NULL);
      
      return TCL_OK;
    }
  
  
  if (vtkRenderWindowCppCommand((eosRenderWindow *)op,interp,argc,argv) == TCL_OK)
    {
      return TCL_OK;
    }
  
  if ((argc >= 2)&&(!strstr(interp->result,"Object named:")))
    {
      char temps2[256];
      sprintf(temps2,"Object named: %s, could not find requested method: %s\nor the method was called with incorrect arguments.\n",argv[0],argv[1]);
      Tcl_AppendResult(interp,temps2,NULL);
    }
  return TCL_ERROR;
}


int
eosStereoCmd(ClientData clientData, Tcl_Interp *interp, int argc, char argv[])
{
  int error;
  
  if(argc >1){
    interp->result = "Usage: eosStereoWindowTcl";
    return TCL_ERROR;
  }  

}
