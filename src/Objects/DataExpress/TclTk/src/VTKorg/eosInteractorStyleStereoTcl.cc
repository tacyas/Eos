// tcl wrapper for eosInteractorStyleStereo object
//
#include "vtkSystemIncludes.h"
#include "vtkCamera.h"
#include "eosInteractorStyleStereo.hh"

#include "vtkTclUtil.h"

#define DEBUG
#include "genUtil.h"

ClientData eosInteractorStyleStereoNewCommand()
{
  	eosInteractorStyleStereo *temp = eosInteractorStyleStereo::New();
    return ((ClientData)temp);
}

int vtkInteractorStyleCppCommand(vtkInteractorStyle *op, Tcl_Interp *interp,
             int argc, char *argv[]);

int VTKTCL_EXPORT eosInteractorStyleStereoCppCommand(eosInteractorStyleStereo *op, Tcl_Interp *interp,
             int argc, char *argv[]);

int VTKTCL_EXPORT eosInteractorStyleStereoCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[])
{
	DEBUGPRINT("in eosInteractorStyleStereoCommand\n")
	DEBUGPRINT2("argv 0: %s 1:%s\n", argv[0], argv[1]);
	if ((argc == 2)&&(!strcmp("Delete",argv[1]))&& !vtkTclInDelete(interp)) {
		Tcl_DeleteCommand(interp,argv[0]);
					  return TCL_OK; 
	}
	return eosInteractorStyleStereoCppCommand((eosInteractorStyleStereo *)(((vtkTclCommandArgStruct *)cd)->Pointer), interp, argc, argv);
}

int VTKTCL_EXPORT eosInteractorStyleStereoCppCommand(eosInteractorStyleStereo *op, Tcl_Interp *interp,
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
	DEBUGPRINT1("argc %d in eosInteractorStyleStereoCppCommand\n", argc);
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
      if (!strcmp("eosInteractorStyleStereo",argv[1]))
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
	 eosInteractorStyleStereo *temp20;
	 int eosInteractorStyleStereoCommand(ClientData, Tcl_Interp *, int, char *[]);
	 error = 0;

	 if (!error)
	  {
	  temp20 = (op)->New();
	  vtkTclGetObjectFromPointer(interp,(void *)temp20,eosInteractorStyleStereoCommand);
	  return TCL_OK;
	  }
     }

  if((!strcmp("SetRenderer",argv[1]))&&(argc == 5))
  {
    vtkRenderer  *temp,*tempr,*templ;
    int error1 = 0;
    int error2 = 0;

    temp = (vtkRenderer *)(vtkTclGetPointerFromObject(argv[2],(char *) "vtkRenderer",interp,error1));
	tempr = (vtkRenderer *)(vtkTclGetPointerFromObject(argv[3],(char *) "vtkRenderer",interp,error1));
	templ = (vtkRenderer *)(vtkTclGetPointerFromObject(argv[4],(char *) "vtkRenderer",interp,error1));
    if (!error1 && !error2){
    	op->SetRenderer(temp,tempr,templ);
    	Tcl_ResetResult(interp);
    	return TCL_OK;
    }
  }

  if((!strcmp("SetRenderer",argv[1]))&&(argc == 3))
  {
  	printf("In eosInteractorStyleStereo SetRenderer argc=3 Start\n");
	
    vtkRenderer  *temp;
    int error1 = 0;

    temp = (vtkRenderer *)(vtkTclGetPointerFromObject(argv[2],(char *) "vtkRenderer",interp,error1));
    if (!error1){
        op->SetRenderer(temp);
        Tcl_ResetResult(interp);

		printf("In eosInteractorStyleStereo SetRenderer argc=3 finish\n");
		
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
  if((!strcmp("CameraMove",argv[1]))&&(argc == 5)){
  	error = 0;

	if (!error){
		op->CameraMove(atof(argv[2]),atof(argv[3]),atof(argv[4]));
		Tcl_ResetResult(interp);
		return TCL_OK;
	}
  }

  if((!strcmp("GetRightRenderer",argv[1]))&&(argc == 2)){ 
      vtkRenderer *renR;
      int vtkRendererCommand(ClientData, Tcl_Interp *, int, char *[]);
      error = 0;

      if (!error){
          renR = op->GetRightRenderer();
          vtkTclGetObjectFromPointer(interp,(void *)renR,vtkRendererCommand);
          return TCL_OK;
      }      
  }

  if((!strcmp("GetLeftRenderer",argv[1]))&&(argc == 2)){
      vtkRenderer *renL;
      int vtkRendererCommand(ClientData, Tcl_Interp *, int, char *[]);
      error = 0;

      if (!error){
          renL = op->GetLeftRenderer();
          vtkTclGetObjectFromPointer(interp,(void *)renL,vtkRendererCommand);
          return TCL_OK;
      }      
  }

  if (!strcmp("ListInstances",argv[1]))
    {
    vtkTclListInstances(interp,(ClientData)eosInteractorStyleStereoCommand);
    return TCL_OK;
    }
				
  if (!strcmp("ListMethods",argv[1]))
    {
    vtkInteractorStyleCppCommand(op,interp,argc,argv);
    Tcl_AppendResult(interp,"Methods from eosInteractorStyleStereo:\n",NULL);
    Tcl_AppendResult(interp,"  GetClassName\n",NULL);
    Tcl_AppendResult(interp,"  New\n",NULL);
    Tcl_AppendResult(interp,"  SetRenderer\t with 3 arg\n",NULL);
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