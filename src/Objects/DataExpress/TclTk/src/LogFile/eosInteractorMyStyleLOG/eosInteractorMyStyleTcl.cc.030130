// tcl wrapper for eosInteractorMyStyle object
//
#include "vtkSystemIncludes.h"
#include "vtkCamera.h"
#include "eosInteractorMyStyle.hh"

#include "vtkTclUtil.h"

#define DEBUG
#include "genUtil.h"

ClientData eosInteractorMyStyleNewCommand()
{
  	eosInteractorMyStyle *temp = eosInteractorMyStyle::New();
    return ((ClientData)temp);
}

int vtkInteractorStyleCppCommand(vtkInteractorStyle *op, Tcl_Interp *interp,
             int argc, char *argv[]);

int VTKTCL_EXPORT eosInteractorMyStyleCppCommand(eosInteractorMyStyle *op, Tcl_Interp *interp,
             int argc, char *argv[]);

int VTKTCL_EXPORT eosInteractorMyStyleCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[])
{
	DEBUGPRINT("in eosInteractorMyStyleCommand\n")
	DEBUGPRINT2("argv 0: %s 1:%s\n", argv[0], argv[1]);
	if ((argc == 2)&&(!strcmp("Delete",argv[1]))&& !vtkTclInDelete(interp)) {
		Tcl_DeleteCommand(interp,argv[0]);
					  return TCL_OK; 
	}
	return eosInteractorMyStyleCppCommand((eosInteractorMyStyle *)(((vtkTclCommandArgStruct *)cd)->Pointer), interp, argc, argv);
}

int VTKTCL_EXPORT eosInteractorMyStyleCppCommand(eosInteractorMyStyle *op, Tcl_Interp *interp,
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

#ifdef DEBUG
	DEBUGPRINT1("argc %d in eosInteractorMyStyleCppCommand\n", argc);
	{int i;
	for(i=0; i<argc; i++) {
		DEBUGPRINT2("%d : %s\n", i, argv[i]);
	}
	}
#endif
  if (argc < 2)
    {
    Tcl_SetResult(interp, (char *) "Could not find requested method.", TCL_VOLATILE);
    return TCL_ERROR;
    }

  if (!interp)
    {
    if (!strcmp("DoTypecasting",argv[0]))
      {
	   DEBUGPRINT1("<<%s\n",argv[1]);
      if (!strcmp("eosInteractorMyStyle",argv[1]))
        {       
        argv[2] = (char *)((void *)op);
        return TCL_OK; 
        }
      if (vtkInteractorStyleCppCommand((vtkInteractorStyle *)op,interp,argc,argv) == TCL_OK)
        {
        return TCL_OK;
        }
      }
    return TCL_ERROR;
    }

   if(!strcmp("GetSuperClassName",argv[1])) {
        Tcl_SetResult(interp,(char *) "vtkInteractorStyle", TCL_VOLATILE);
        return TCL_OK; 
    }

    if ((!strcmp("GetClassName",argv[1]))&&(argc == 2)) {
      const char    *temp20;
      error = 0;
      }


  if ((!strcmp("New",argv[1]))&&(argc == 2))
     {
	 eosInteractorMyStyle *temp20;
	 int eosInteractorMyStyleCommand(ClientData, Tcl_Interp *, int, char *[]);
	 error = 0;

	 if (!error)
	  {
	  temp20 = (op)->New();
	  vtkTclGetObjectFromPointer(interp,(void *)temp20,eosInteractorMyStyleCommand);
	  return TCL_OK;
	  }
     }

  if((!strcmp("SetRenderWindowData",argv[1]))&&(argc == 4))
  {
    vtkRenderer  *temp2;
    vtkRenderWindowInteractor *tempI2;
    int error1 = 0;
    int error2 = 0;

    temp2 = (vtkRenderer *)(vtkTclGetPointerFromObject(argv[2],(char *) "vtkRenderer",interp,error1));
    tempI2 = (vtkRenderWindowInteractor *)(vtkTclGetPointerFromObject(argv[3],(char *) "vtkRenderWindowInteractor",interp,error2));

    if (!error1 && !error2)
      {
      op->SetRenderWindowData(temp2,tempI2);
      Tcl_ResetResult(interp);
      return TCL_OK;
      }
   }

  if((!strcmp("OnButtonFromWindow",argv[1]))&&(argc == 3))
  {
    error = 0;

    if (!error)
      {
	  DEBUGPRINT1("OnButtonFromWindowStart: %s\n", argv[2]);
      op->OnButtonFromWindow(argv[2]);
	  DEBUGPRINT("OnButtonFromWindowEnd\n");
      Tcl_ResetResult(interp);
      return TCL_OK; 
      }
   }

  if((!strcmp("SetTclWindowInterp",argv[1]))&&(argc == 2))
  {
    error = 0;

    if (!error)
      {
      DEBUGPRINT1("SetTclWindowInterp: %s\n", argv[1]);
      op->SetTclWindowInterp(interp);
      DEBUGPRINT("SetTclWindowInterpEnd\n");
      Tcl_ResetResult(interp);
      return TCL_OK; 
      }
   }
		
  if (!strcmp("ListInstances",argv[1]))
    {
    vtkTclListInstances(interp,(ClientData)eosInteractorMyStyleCommand);
    return TCL_OK;
    }
				
  if (!strcmp("ListMethods",argv[1]))
    {
    vtkInteractorStyleCppCommand(op,interp,argc,argv);
    Tcl_AppendResult(interp,"Methods from eosInteractorMyStyle:\n",NULL);
    Tcl_AppendResult(interp,"  GetClassName\n",NULL);
    Tcl_AppendResult(interp,"  New\n",NULL);
    Tcl_AppendResult(interp,"  SetStereoRenderWindows\t with 3 or 2 arg\n",NULL);
    Tcl_AppendResult(interp,"SetTclWindowInterp\t with 1 arg\n",NULL);
    return TCL_OK;
    }

  if (vtkInteractorStyleCppCommand((vtkInteractorStyle *)op,interp,argc,argv) == TCL_OK)
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
