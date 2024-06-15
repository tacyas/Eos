/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% vtkmrcImageReaderTcl.cc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : vtkmrcImageReaderTcl.cc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%vtkmrcImageReaderTcl.cc ver%I%; Date:%D% %Z%";

//
// tcl wrapper for vtkmrcImageReader object
//
#include <sstream>
#include "vtkSystemIncludes.h"
#include "vtkmrcImageReader.hh"
#include "vtkTclUtil.h"


ClientData vtkmrcImageReaderNewCommand()
{
	vtkmrcImageReader *tmp = vtkmrcImageReader::New();
	return ((ClientData)tmp);
}

int VTKTCL_EXPORT vtkVolumeReaderCppCommand(vtkVolumeReader* op, Tcl_Interp* interp,
	int argc, char *argv[]);

int VTKTCL_EXPORT vtkmrcImageReaderCppCommand(vtkmrcImageReader* op, Tcl_Interp* interp,
	int argc, char *argv[]);

int vtkStructuredPointsCommand(ClientData, Tcl_Interp*, int, char* []);

int 
vtkmrcImageReaderCommand(
	ClientData cd, 
	Tcl_Interp *interp,
    int argc, 
	char *argv[])
{
    // fprintf(stderr, "in vtkmrcImageReaderCommand");
	if ((!strcmp("Delete",argv[1]))&&(argc == 2) &&!vtkTclInDelete(interp)) {
		Tcl_DeleteCommand(interp,argv[0]);
		return TCL_OK;
	}
	return vtkmrcImageReaderCppCommand((vtkmrcImageReader *)(((vtkTclCommandArgStruct *)cd)->Pointer), interp, argc, argv);
}

int vtkmrcImageReaderCppCommand(
	vtkmrcImageReader *op, 
	Tcl_Interp *interp,
    int argc, 
	char *argv[])
{
	int    tempi;
	double tempd;
	static char temps[80];
	int    error;

	tempi = 0;
	tempd = 0;
	error = 0;
	temps[0] = 0;

	if(argc<2) {
		Tcl_SetResult(interp, 
			(char*) "Could not find requested method.", TCL_VOLATILE);
		return TCL_ERROR;
	}
	//  fprintf(stderr, "%s %s in Cpp\n ", argv[0], argv[1]);
	if(!interp) {
		// fprintf(stderr, "!interp %s %s in Cpp\n ", argv[0], argv[1]);
		if(!strcmp("DoTypecasting", argv[0])) {
			if(!strcmp("vtkmrcImageReader", argv[1])) {
		  		argv[2] = (char*)((void*)op);
				return TCL_OK;
			}
	    	if(vtkVolumeReaderCppCommand((vtkVolumeReader*)op,interp,argc,argv)==TCL_OK) {
		  		return TCL_OK;
			}
		}
	  	return TCL_ERROR;
	} 
	if((!strcmp("GetSuperClassName",argv[1]))) {
		Tcl_SetResult(interp,(char *) "vtkVolumeReader", TCL_VOLATILE);
		return TCL_OK;
	}

	if ((!strcmp("GetClassName",argv[1]))&&(argc == 2)) {
	  const char    *temp20;
	  error = 0;

	  if (!error) {
	    temp20 = (op)->GetClassName();
	    if (temp20) {
	      Tcl_SetResult(interp, (char*)temp20, TCL_VOLATILE);
	    } else {
	      Tcl_ResetResult(interp);
	    }
	    return TCL_OK;
	  }
	}

	if ((!strcmp("IsA",argv[1]))&&(argc == 3)) {
		char    *temp0;
	  	int      temp20;
	  	error = 0;
	  
		temp0 = argv[2];
		if (!error) {
	    	temp20 = (op)->IsA(temp0);
	    	char tempResult[1024];
	    	sprintf(tempResult,"%i",temp20);
	    	Tcl_SetResult(interp, tempResult, TCL_VOLATILE);
	    	return TCL_OK;
	  	}
	}

	if ((!strcmp("New",argv[1]))&&(argc == 2)) {
		vtkmrcImageReader *temp20;
		error = 0;

		if (!error) {
			temp20 = (op)->New();
			vtkTclGetObjectFromPointer(interp, (void *)temp20, vtkmrcImageReaderCommand);
			return TCL_OK;
		}
	} 
	 
	if((!strcmp("SetFilename", argv[1]))&&(argc == 3)) {
		(op)->SetFilename(argv[2]); 
	  	return TCL_OK;
	}

	if((!strcmp("SetDataType", argv[1]))) {
		int temp0;
		error = 0;

	  	if(Tcl_GetInt(interp, argv[2], &tempi) != TCL_OK) {
			error = 1;
		}
		temp0 = tempi; 
		if(!error) {
			op->SetDataType((mrcPixelDataType)temp0); 
			Tcl_ResetResult(interp);
			return TCL_OK;
		}
	} 

	if((!strcmp("SetDataHow",argv[1]))) {
		int temp0;
		error = 0;
	  	if(Tcl_GetInt(interp,argv[2],&tempi) != TCL_OK) {
			error = 1;
		}
		temp0 = tempi; 
		if(!error) {
			op->SetDataHow((mrcPixelDataHowToGet)temp0); 
			Tcl_ResetResult(interp);
			return TCL_OK;
		}
	} 
	
	if((!strcmp("GetImage",argv[1]))&&(argc==3)) {
		int      temp0;
		vtkImageData *temp20;
		error = 0;
		if (Tcl_GetInt(interp,argv[2],&tempi) != TCL_OK) {
			error = 1;
		}
		temp0 = tempi;
		if (!error) {
	    	temp20 = (op)->GetImage(temp0);
			vtkTclGetObjectFromPointer(interp,(void *)temp20,vtkStructuredPointsCommand);
	    	return TCL_OK;
		}
	} 

	if(!strcmp("ListInstances",argv[1])) {
		vtkTclListInstances(interp,(ClientData)vtkmrcImageReaderCommand);
		return TCL_OK;
	} 

	if (!strcmp("ListMethods",argv[1])) {
	  vtkVolumeReaderCppCommand(op,interp,argc,argv);
	  Tcl_AppendResult(interp,"Methods from vtkmrcImageReader:\n",NULL);
	  Tcl_AppendResult(interp,"  GetSuperClassName\n",NULL);
	  Tcl_AppendResult(interp,"  GetClassName\n",NULL);
	  Tcl_AppendResult(interp,"  IsA\n",NULL);
	  Tcl_AppendResult(interp,"  New\n",NULL);
	  Tcl_AppendResult(interp,"  SetFilename\n",NULL);
	  Tcl_AppendResult(interp,"  SetFilename\n",NULL);
	  Tcl_AppendResult(interp,"  SetFilename\n",NULL);
	  Tcl_AppendResult(interp,"  SetDataType\n",NULL);
	  Tcl_AppendResult(interp,"  SetDataHow\n",NULL);
	  return TCL_OK;
	}

	if(vtkVolumeReaderCppCommand((vtkVolumeReader *)op,interp,argc,argv) == TCL_OK) {
	  return TCL_OK;
	}

	if ((argc >= 2)&&(!strstr(interp->result,"Object named:"))) {
		char temps2[256];
	  	sprintf(temps2,"Object named: %s, could not find requested method: %s\n",argv[0],argv[1]);
		Tcl_AppendResult(interp, temps2, NULL);
	} 
	return TCL_ERROR;
}
