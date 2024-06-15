// tcl wrapper for eosInteractorStyleStereo object
//
#include <stdio.h>
#include "vtkSystemIncludes.h"
#include "vtkRenderer.h"
#include "eosStereoRenderer.hh"

#include "vtkTclUtil.h"

#define DEBUG
#include "genUtil.h"

ClientData eosStereoRendererNewCommand()
{

printf("----------- eosStereoRenderer For Tcl NEW !!--------------\n");
  	eosStereoRenderer *temp = eosStereoRenderer::New();
printf("----------- eosStereoRenderer For Tcl NEW OK!!--------------\n");
    return ((ClientData)temp);
}

int vtkObjectCppCommand(vtkObject *op, Tcl_Interp *interp,
             int argc, char *argv[]);
			 
int VTKTCL_EXPORT eosStereoRendererCppCommand(eosStereoRenderer *op, Tcl_Interp *interp,
             int argc, char *argv[]);

int VTKTCL_EXPORT eosStereoRendererCommand(ClientData cd, Tcl_Interp *interp,
             int argc, char *argv[])
{
	DEBUGPRINT("in eosStereoRendererCommand\n")
	DEBUGPRINT2("argv 0: %s 1:%s\n", argv[0], argv[1]);
	if ((argc == 2)&&(!strcmp("Delete",argv[1]))&& !vtkTclInDelete(interp)) {
		Tcl_DeleteCommand(interp,argv[0]);
					  return TCL_OK; 
	}
	return eosStereoRendererCppCommand((eosStereoRenderer *)(((vtkTclCommandArgStruct *)cd)->Pointer), interp, argc, argv);
}

int VTKTCL_EXPORT eosStereoRendererCppCommand(eosStereoRenderer *op, Tcl_Interp *interp,
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
	DEBUGPRINT1("argc %d in eosStereoRendererCppCommand\n", argc);
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
      if (!strcmp("eosStereoRenderer",argv[1]))
        {       
        argv[2] = (char *)((void *)op);
        return TCL_OK; 
        }
	   if (vtkObjectCppCommand((vtkObject *)op,interp,argc,argv) == TCL_OK)
	    {
		return TCL_OK;
		}	   
      }
    return TCL_ERROR;
    }

	if((!strcmp("New",argv[1]))&&(argc == 2)){
		eosStereoRenderer *temp20;
		int eosStereoRendererCommand(ClientData, Tcl_Interp *, int, char *[]);
		error = 0;

		if (!error){
			temp20 = (op)->New();
			vtkTclGetObjectFromPointer(interp,(void *)temp20,eosStereoRendererCommand);
			return TCL_OK;
		}
	}
	
	if((!strcmp("AddActor",argv[1]))&&(argc == 3)){
		vtkActor  *temp0;
		error = 0;

		temp0 = (vtkActor *)(vtkTclGetPointerFromObject(argv[2],(char *) "vtkActor",interp,error));
    	if (!error){
      		op->AddActor(temp0);
      		Tcl_ResetResult(interp);
      		return TCL_OK; 
      	}
	
	}
	
	if((!strcmp("RemoveActor",argv[1]))&&(argc == 3)){
		vtkActor  *temp0;
    	error = 0;

		temp0 = (vtkActor *)(vtkTclGetPointerFromObject(argv[2],(char *) "vtkActor",interp,error));
    	if (!error){
			op->RemoveActor(temp0);
			Tcl_ResetResult(interp);
			return TCL_OK; 
		}
	}
 
    if((!strcmp("GetActiveCamera",argv[1]))&&(argc == 2)){ 
		vtkCamera *cam;
		int vtkCameraCommand(ClientData, Tcl_Interp *, int, char *[]);
        error = 0;

        if (!error){
            cam = op->GetActiveCamera();
			vtkTclGetObjectFromPointer(interp,(void *)cam,vtkCameraCommand);
            return TCL_OK; 
        }       
    }

    if((!strcmp("GetMainRenderer",argv[1]))&&(argc == 2)){ 
        vtkRenderer *ren;
        int vtkRendererCommand(ClientData, Tcl_Interp *, int, char *[]);
        error = 0;
        if (!error){
			fprintf(stdout, "in GetMainRenderer");	
            ren = op->GetMainRenderer();
			fprintf(stdout, "%p\n", ren);	
            vtkTclGetObjectFromPointer(interp,(void *)ren,vtkRendererCommand);
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
    vtkTclListInstances(interp,(ClientData)eosStereoRendererCommand);
    return TCL_OK;
    }
				
  if (!strcmp("ListMethods",argv[1]))
    {
    Tcl_AppendResult(interp,"Methods from eosStereoRenderer:\n",NULL);
    Tcl_AppendResult(interp,"  GetClassName\n",NULL);
    Tcl_AppendResult(interp,"  AddActor\t with 1 arg\n",NULL);
    Tcl_AppendResult(interp,"  RemoveActor\t with 1 arg\n",NULL);
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