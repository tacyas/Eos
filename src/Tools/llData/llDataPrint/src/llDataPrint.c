#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <libgen.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#include "tk.h"
#include "blt.h"

#if (TK_MAJOR_VERSION > 3)
#if HAVE_ITCL_H
#include "itcl.h"
#endif
#if HAVE_ITK_H
#include "itk.h"
#endif
#endif

#if (TK_MAJOR_VERSION > 3)
/*
 * The following variable is a special hack that is needed in order for
 * Sun shared libraries to be used for Tcl.
 */

#ifdef NEED_MATHERR
extern int matherr();
int *tclDummyMathPtr = (int *) matherr;
#endif
#endif

extern int Tcl_AppInit _ANSI_ARGS_((Tcl_Interp *interp));

#undef DEBUG
#include  "genUtil.h"
#include  "Memory.h"
#include  "llData.h"
static llData llIn;
static llData* llIns;
static llData llNea;
static llData llFar;

static llDataPrintInfo info;

void
main(int argc, char* argv[]) 
{
	llDataParaTypeInteger status;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	if(info.flagIn) {
		llDataFileRead(info.fptIn, &llIn, &status); 
	} 

	if(info.flagNea) {
		llDataFileRead(info.fptNea, &llNea, &status); 
		llDataFileRead(info.fptFar, &llFar, &status); 
	} 
	if(info.flagIns) {
		llIns = (llData*)memoryAllocate(sizeof(llData)*info.flagIns, "in main");
		for(i=0; i<info.flagIns; i++) {
			llDataFileRead(info.fptIns[i], &(llIns[i]), &status); 
		}
	}

	if((!info.flagIn)
	 &&(!info.flagNea)
	 &&(!info.flagIns)) {
		fprintf(stderr, "Either -i, -i2, or -is is required.\n");
		exit(EXIT_FAILURE);
	}

	Tk_Main(argc, argv, Tcl_AppInit);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}


int
Tcl_AppInit(interp)
    Tcl_Interp *interp;     /* Interpreter for application. */
{
	char s[1024];
	char s2[1024];
	char sR[1024];
	char sA[1024];
	char sP[1024];
	int l, k, nR, llMax, i, total;
	Blt_Vector** R;
	Blt_Vector** A;
	Blt_Vector** P;
	double** RData;
	double** AData;
	double** PData;

    if (Tcl_Init(interp) == TCL_ERROR) {
    return TCL_ERROR;
    }
    if (Tk_Init(interp) == TCL_ERROR) {
    return TCL_ERROR;
    }
    /*
     * Call the init procedures for included packages.  Each call should
     * look like this:
     *
     * if (Mod_Init(interp) == TCL_ERROR) {
     *     return TCL_ERROR;
     * }
     *
     * where "Mod" is the name of the module.
     */

#if defined(ITCL_MAJOR_VERSION) && (ITCL_MAJOR_VERSION == 2)
    if (Itcl_Init(interp) == TCL_ERROR) {
    return TCL_ERROR;
    }
    if (Itk_Init(interp) == TCL_ERROR) {
    return TCL_ERROR;
    }
#endif
    if (Blt_Init(interp) == TCL_ERROR) {
    	return TCL_ERROR;
    }

/* 
*/
	if(info.flagIn) {
		nR = llIn.nRMax;
		sprintf(s, "%s", basename(info.In));
		Tcl_SetVar(interp, "inFileName", s, TCL_GLOBAL_ONLY);
		Tcl_SetVar(interp, "Mode", "Single", TCL_GLOBAL_ONLY);
	} else if(info.flagNea) {
		llIn  = llNea;
		nR = llNea.nRMax + llFar.nRMax - 1;
		sprintf(s, "%s", basename(info.Nea));
		Tcl_SetVar(interp, "inFileName", s, TCL_GLOBAL_ONLY);
		Tcl_SetVar(interp, "Mode", "Single", TCL_GLOBAL_ONLY);
	} else if(info.flagIns) {
		llIn = llIns[0];
		nR = llIn.nRMax;
		sprintf(s, "%s", basename(info.InsList));
		Tcl_SetVar(interp, "inFileName", s, TCL_GLOBAL_ONLY);
		Tcl_SetVar(interp, "Mode", "Multi", TCL_GLOBAL_ONLY);
	}
	if(info.flagOut) {
		sprintf(s, "%s", basename(info.Out));
		Tcl_SetVar(interp, "outFileName", s, TCL_GLOBAL_ONLY);
	} else {
		sprintf(s, "%s", "");
		Tcl_SetVar(interp, "outFileName", s, TCL_GLOBAL_ONLY);
	}
	
	sprintf(s, "%f", info.Rmax);
	Tcl_SetVar(interp, "Rmax", s, TCL_GLOBAL_ONLY);

	if(info.flagIn || info.flagIns) {
		sprintf(s, "%f", 0.0);
		Tcl_SetVar(interp, "Rmin", s, TCL_GLOBAL_ONLY);
	} else if(info.flagNea) {
		sprintf(s, "%f", -info.Rmax);
		Tcl_SetVar(interp, "Rmin", s, TCL_GLOBAL_ONLY);
	}
	sprintf(s, "%ld", llIn.llMax);
	Tcl_SetVar(interp, "llMax", s, TCL_GLOBAL_ONLY);

	sprintf(s, "%f", llIn.truePitch);
	Tcl_SetVar(interp, "truePitch", s, TCL_GLOBAL_ONLY);

	sprintf(s, "%d", nR);
	Tcl_SetVar(interp, "nRMax", s, TCL_GLOBAL_ONLY);

	R = (Blt_Vector**)memoryAllocate(sizeof(Blt_Vector*)*llIn.llMax, "R");
	A = (Blt_Vector**)memoryAllocate(sizeof(Blt_Vector*)*llIn.llMax, "A");
	P = (Blt_Vector**)memoryAllocate(sizeof(Blt_Vector*)*llIn.llMax, "P");

	DEBUGPRINT("Create\n");
	for(l=0; l<llIn.llMax; l++) {
		/* (n, l) Information */
		sprintf(s, "%d", l);
		sprintf(s2, "%+ld", llIn.LL[l].nn);
    	Tcl_SetVar2(interp, "NN", s, s2, TCL_GLOBAL_ONLY);
		sprintf(s2, "%+ld", llIn.LL[l].nl);
    	Tcl_SetVar2(interp, "NL", s, s2, TCL_GLOBAL_ONLY);
		sprintf(s2, "%+ld", llIn.LL[l].nR);
    	Tcl_SetVar2(interp, "nR", s, s2, TCL_GLOBAL_ONLY);

		sprintf(sR, "vR%d", l);
		sprintf(sA, "vA%d", l);
		sprintf(sP, "vP%d", l);
		if(info.flagIn) {
			if( (Blt_CreateVector(interp, sR, llIn.LL[l].nR, &(R[l])) != TCL_OK) 
			  ||(Blt_CreateVector(interp, sA, llIn.LL[l].nR, &(A[l])) != TCL_OK) 
			  ||(Blt_CreateVector(interp, sP, llIn.LL[l].nR, &(P[l])) != TCL_OK)){
				return TCL_ERROR;
			}
		} else if(info.flagNea) {
			if( (Blt_CreateVector(interp, sR, llNea.LL[l].nR + llFar.LL[l].nR - 1, &(R[l])) != TCL_OK) 
			  ||(Blt_CreateVector(interp, sA, llNea.LL[l].nR + llFar.LL[l].nR - 1, &(A[l])) != TCL_OK) 
			  ||(Blt_CreateVector(interp, sP, llNea.LL[l].nR + llFar.LL[l].nR - 1, &(P[l])) != TCL_OK)){
				return TCL_ERROR;
			}
		} else if(info.flagIns) {
			total = 0;
			for(i=0; i<info.flagIns; i++) {
				total+=llIns[i].LL[l].nR;
			}
			if( (Blt_CreateVector(interp, sR, total, &(R[l])) != TCL_OK) 
			  ||(Blt_CreateVector(interp, sA, total, &(A[l])) != TCL_OK) 
			  ||(Blt_CreateVector(interp, sP, total, &(P[l])) != TCL_OK)){
				return TCL_ERROR;
			}
		}
	}
	DEBUGPRINT("Data Set\n");
	if(info.flagIn) {
		RData = (double**)memoryAllocate(sizeof(double*)*llIn.llMax, "in");
		AData = (double**)memoryAllocate(sizeof(double*)*llIn.llMax, "in");
		PData = (double**)memoryAllocate(sizeof(double*)*llIn.llMax, "in");
		for(l=0; l<llIn.llMax; l++) { /* Layer Line Data */	
			RData[l] = (double*)memoryAllocate(sizeof(double)*llIn.LL[l].nR, "in");
			AData[l] = (double*)memoryAllocate(sizeof(double)*llIn.LL[l].nR, "in");
			PData[l] = (double*)memoryAllocate(sizeof(double)*llIn.LL[l].nR, "in");
			for(k=0; k<llIn.LL[l].nR; k++) {
				RData[l][k] = llIn.LL[l].data[k].RR;
				AData[l][k] = llIn.LL[l].data[k].F;
				PData[l][k] = llIn.LL[l].data[k].PHI*DEGREE;
			}
		}
	} else if(info.flagIns) {
		RData = (double**)memoryAllocate(sizeof(double*)*llIn.llMax, "in");
		AData = (double**)memoryAllocate(sizeof(double*)*llIn.llMax, "in");
		PData = (double**)memoryAllocate(sizeof(double*)*llIn.llMax, "in");
		for(l=0; l<llIn.llMax; l++) { /* Layer Line Data */	
			total = 0;
			for(i=0; i<info.flagIns; i++) {
				total+=llIns[i].LL[l].nR;
			}
			RData[l] = (double*)memoryAllocate(sizeof(double)*total, "in");
			AData[l] = (double*)memoryAllocate(sizeof(double)*total, "in");
			PData[l] = (double*)memoryAllocate(sizeof(double)*total, "in");
			total = 0;
			for(k=0; k<llIn.LL[l].nR; k++) {
				for(i=0; i<info.flagIns; i++) {
					RData[l][total] = llIns[i].LL[l].data[k].RR;
					AData[l][total] = llIns[i].LL[l].data[k].F;
					PData[l][total] = llIns[i].LL[l].data[k].PHI*DEGREE;
					total++;
				}
			}
		}
	} else if(info.flagNea) {
		RData = (double**)memoryAllocate(sizeof(double*)*llIn.llMax, "in");
		AData = (double**)memoryAllocate(sizeof(double*)*llIn.llMax, "in");
		PData = (double**)memoryAllocate(sizeof(double*)*llIn.llMax, "in");
		for(l=0; l<llNea.llMax; l++) {
			RData[l] = (double*)memoryAllocate(sizeof(double)*(llNea.LL[l].nR+llFar.LL[l].nR-1), "in");
			AData[l] = (double*)memoryAllocate(sizeof(double)*(llNea.LL[l].nR+llFar.LL[l].nR-1), "in");
			PData[l] = (double*)memoryAllocate(sizeof(double)*(llNea.LL[l].nR+llFar.LL[l].nR-1), "in");
			if(llNea.LL[l].nn<0) {
				for(k=0; k<llNea.LL[l].nR; k++) {
					RData[l][k+llFar.LL[l].nR-1] =  llNea.LL[l].data[k].RR;
					AData[l][k+llFar.LL[l].nR-1] =  llNea.LL[l].data[k].F;
					PData[l][k+llFar.LL[l].nR-1] =  llNea.LL[l].data[k].PHI*DEGREE;
				}
				for(k=0; k<llFar.LL[l].nR; k++) {
					RData[l][llNea.LL[l].nR-k-1] = -llFar.LL[l].data[k].RR;
					AData[l][llNea.LL[l].nR-k-1] =  llFar.LL[l].data[k].F;
					PData[l][llNea.LL[l].nR-k-1] =  llFar.LL[l].data[k].PHI*DEGREE;
				}
			} else {
				for(k=0; k<llFar.LL[l].nR; k++) {
					RData[l][k+llNea.LL[l].nR-1] =  llFar.LL[l].data[k].RR;
					AData[l][k+llNea.LL[l].nR-1] =  llFar.LL[l].data[k].F;
					PData[l][k+llNea.LL[l].nR-1] =  llFar.LL[l].data[k].PHI*DEGREE;
				}
				for(k=0; k<llNea.LL[l].nR; k++) {
					RData[l][llFar.LL[l].nR-k-1] = -llNea.LL[l].data[k].RR;
					AData[l][llFar.LL[l].nR-k-1] =  llNea.LL[l].data[k].F;
					PData[l][llFar.LL[l].nR-k-1] =  llNea.LL[l].data[k].PHI*DEGREE;
				}
			}
		}
	}
	DEBUGPRINT("Reset\n");
	for(l=0; l<llIn.llMax; l++) { 
		int numValues;
		int arraySize;
		
		if(info.flagIn) {
			numValues = llIn.LL[l].nR;
		} else if(info.flagIns) {
			total = 0;
			for(i=0; i<info.flagIns; i++) {
				total+=llIns[i].LL[l].nR;
			}
			numValues = total;
		} else if(info.flagNea) {
			numValues = llNea.LL[l].nR + llFar.LL[l].nR - 1;
		}
		arraySize = numValues;
		sprintf(sR, "vR%d", l);
		sprintf(sA, "vA%d", l);
		sprintf(sP, "vP%d", l);
		if( (Blt_ResetVector(R[l], RData[l], numValues, arraySize, TCL_DYNAMIC) != TCL_OK) 
		 || (Blt_ResetVector(A[l], AData[l], numValues, arraySize, TCL_DYNAMIC) != TCL_OK) 
		 || (Blt_ResetVector(P[l], PData[l], numValues, arraySize, TCL_DYNAMIC) != TCL_OK) ) {
			return TCL_ERROR;
		}
	}
#if (TCL_MAJOR_VERSION >= 7) && (TCL_MINOR_VERSION >= 5)
    Tcl_SetVar(interp, "tcl_rcFileName", "~/.wishrc", TCL_GLOBAL_ONLY);
#else
/*
    tcl_RcFileName = "~/.wishrc";
	*/
#endif
    return TCL_OK;
}

