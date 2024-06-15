/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% tkImgFmtMRC.c ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : tkImgFmtMRC 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%tkImgFmtMRC ver%I%; Date:%D% %Z%";

#undef DEBUG
#include <string.h>
#include "genUtil.h"
#include "./tkImgFmtMRC.h"

/*
int
TkCopyAndGlobalEval(Tcl_Interp* interp, CONST char* command)
{
	Tcl_EvalEx(interp, command, -1, TCL_EVAL_GLOBAL);	
}
*/

static int tkMRCFileMatch _ANSI_ARGS_((Tcl_Channel chan, CONST char *fileName,
			Tcl_Obj *formatString, int *widthPtr,
		    int *heightPtr, Tcl_Interp *interp));

static int tkMRCFileRead _ANSI_ARGS_((Tcl_Interp *interp,
			Tcl_Channel f, CONST char *fileName, Tcl_Obj *formatString,
			Tk_PhotoHandle imageHandle, int destX, int destY,
			int width, int height, int srcX, int srcY));

static int tkMRCFileWrite _ANSI_ARGS_((Tcl_Interp *interp,
			CONST char* fileName, Tcl_Obj *formatString,
			Tk_PhotoImageBlock *blockPtr));
															 
static tkmrcInfo __tkmrcInfo;

 Tk_PhotoImageFormat tkImgFmtMRC = {
	"MRC",          /* name */
	tkMRCFileMatch, /* fileMatchProc */
	NULL,           /* stringMatchProc */
	tkMRCFileRead,  /* fileReadProc */
	NULL,           /* stringReadProc */
	tkMRCFileWrite, /* fileWriteProc */
	NULL,           /* stringWriteProc */
};

int
tkmrcInfoCmdSet(Tcl_Interp* interp)
{
	Tcl_CreateCommand(interp, "mrcInfoSet", tkmrcInfoSetCmd, (ClientData)Tk_MainWindow(interp), (Tcl_CmdDeleteProc*)NULL);
	Tcl_CreateCommand(interp, "mrcInfoGet", tkmrcInfoGetCmd, (ClientData)Tk_MainWindow(interp), (Tcl_CmdDeleteProc*)NULL);
	Tk_CreatePhotoImageFormat(&tkImgFmtMRC);
	return 1;
}

#include <string.h>

/*
 *----------------------------------------------------------------------
 *
 * tkMRCFileMatch --
 *
 *	This procedure is invoked by the photo image type to see if
 *	a file contains image data in MRC format.
 *
 * Results:
 *	The return value is 1 when data is mrc-formatted, and 0 otherwise.
 *
 *----------------------------------------------------------------------
 */

static int
tkMRCFileMatch(f, fileName, format, widthPtr, heightPtr, interp)
    Tcl_Channel f;			    /* The image file, open for reading. */
    CONST char *fileName;		/* The name of the image file. */
    Tcl_Obj *format;		    /* User-specified format string, or NULL. */
    int *widthPtr, *heightPtr;	/* The dimensions of the image are
				 				* returned here if the file is a valid
				 				* raw MRC file. */
	Tcl_Interp *interp;
{
	int argc=0, i, index;
	Tcl_Obj **objv;
	int nBytes;
	static char *optionStrings[] = {
		"-index", NULL
	};
	static int flagInitial = 0;
/*
	extern char* strdup(const char*);
	extern size_t strlen(const char*);	
	extern int strcmp(const char*, const char*);	
	extern int strncmp(const char*, const char*, size_t);	
*/
	/* If first call */ 
	if(0==flagInitial) {
		__tkmrcInfo.fileName   = strdup(fileName);
		__tkmrcInfo.flagHeader = 0;
		flagInitial = 1;
	}

	/* When a different file was read, */ 
	if(0!=strncmp(fileName, __tkmrcInfo.fileName, strlen(fileName))) {
		/* Memory Free */
		if(__tkmrcInfo.flagImage==1) {	
			mrcImageFree(&(__tkmrcInfo.mrc), "in tkMRCFileMatch");
			__tkmrcInfo.flagImage = 0; 
		}
		__tkmrcInfo.flagHeader = 0;
	}

	/* When a header was not read */
	if(0==__tkmrcInfo.flagHeader) {
		/* Initialization */
		__tkmrcInfo.flagImage  = 0;		
		__tkmrcInfo.nhist      = 256;
		__tkmrcInfo.flagHist   = 0;
		__tkmrcInfo.flagScattering = 0;
		__tkmrcInfo.flagR          = 0;
		__tkmrcInfo.flagProjX  = 0;
		__tkmrcInfo.flagProjY  = 0;
		__tkmrcInfo.flagSectX  = 0;
		__tkmrcInfo.flagSectY  = 0;
		__tkmrcInfo.flagz      = 1;
		__tkmrcInfo.z          = 0.0;

    	mrcFileRead(&(__tkmrcInfo.mrc), __tkmrcInfo.fileName, "in FileMatchMRC", 0);
		__tkmrcInfo.flagHeader = 1;
		__tkmrcInfo.flagImage  = 1;
	}
	*widthPtr      = __tkmrcInfo.mrc.HeaderN.x;
	*heightPtr     = __tkmrcInfo.mrc.HeaderN.y;
	__tkmrcInfo.nz = __tkmrcInfo.mrc.HeaderN.z;
	
	/* Something Wrong for min-max */	
	if(__tkmrcInfo.mrc.HeaderAMax<=__tkmrcInfo.mrc.HeaderAMin) {
		mrcStatDataSet(&(__tkmrcInfo.mrc), 0);
	}
	if(__tkmrcInfo.mrc.HeaderAMax<=__tkmrcInfo.mrc.HeaderAMin) {
		fprintf(stderr, "### MAX %f<=MIN %f on this mrc-image %s! Something wrong !! Please Check\n", 
		__tkmrcInfo.mrc.HeaderAMax, __tkmrcInfo.mrc.HeaderAMin, fileName);
		exit(EXIT_FAILURE);	
	}
	if(__tkmrcInfo.flagContrast == 0) {
		__tkmrcInfo.Contrast = 2;
		__tkmrcInfo.flagContrast = 1;
	}
	if(0==__tkmrcInfo.flagMin || 0==__tkmrcInfo.flagMax) {
		if(IsImage(&(__tkmrcInfo.mrc), "in tk", 0)) {
			if(__tkmrcInfo.flagInfo == 0) {
				__tkmrcInfo.Info.mode = meanOfSparse;
				lmrcImageInformation(&(__tkmrcInfo.Info), &(__tkmrcInfo.mrc));
				__tkmrcInfo.flagInfo = 1;
			}
			__tkmrcInfo.Min     = MAX(__tkmrcInfo.Info.mean - __tkmrcInfo.Info.sd*__tkmrcInfo.Contrast,__tkmrcInfo.mrc.HeaderAMin);
			__tkmrcInfo.Max     = MIN(__tkmrcInfo.Info.mean + __tkmrcInfo.Info.sd*__tkmrcInfo.Contrast,__tkmrcInfo.mrc.HeaderAMax);
			DEBUGPRINT5("mean %f max %f min %f sd %f contrast %f\n", __tkmrcInfo.Info.mean, 
			                                                         __tkmrcInfo.mrc.HeaderAMax, 
																	 __tkmrcInfo.mrc.HeaderAMin, 
																	 __tkmrcInfo.Info.sd,
																	 __tkmrcInfo.Contrast);
			fprintf(stdout, "Default Contrast: %f <-> %f because mean %f max %f min %f sd %f contrast %f\n", 
																	 __tkmrcInfo.Min, 
																	 __tkmrcInfo.Max, 
																	 __tkmrcInfo.Info.mean, 
			                                                         __tkmrcInfo.mrc.HeaderAMax, 
																	 __tkmrcInfo.mrc.HeaderAMin, 
																	 __tkmrcInfo.Info.sd,
																	 __tkmrcInfo.Contrast);
		} else if(IsFT(&(__tkmrcInfo.mrc), "in tk", 0)) {
			if(__tkmrcInfo.flagFSInfo == 0) {
				lmrcFSInfo(&(__tkmrcInfo.FSInfo), &(__tkmrcInfo.mrc));		
				__tkmrcInfo.flagFSInfo = 1;
			}
			__tkmrcInfo.Min     = 0;
			__tkmrcInfo.Max     = __tkmrcInfo.FSInfo.MaxExceptForF00;
		} else {
			__tkmrcInfo.Min     = __tkmrcInfo.mrc.HeaderAMin;
			__tkmrcInfo.Max     = __tkmrcInfo.mrc.HeaderAMin;
		}
		__tkmrcInfo.flagMin = 1;
		__tkmrcInfo.flagMax = 1;

		if(__tkmrcInfo.Inverse) {
			if(__tkmrcInfo.Min<__tkmrcInfo.Max) {
				double tmp;
				tmp = __tkmrcInfo.Max;
				__tkmrcInfo.Max = __tkmrcInfo.Min;
				__tkmrcInfo.Min = tmp;
			}
		}
	}
	return 1;
}

int 
tkmrcInfoSetCmd(ClientData clientData, Tcl_Interp *interp, int argc, CONST char* argv[])
{
	mrcImage mrc;
	char s[1024];
	mrc = __tkmrcInfo.mrc; 
	SSWITCH((char*)argv[1]) 
		SCASE("z") {
			__tkmrcInfo.flagz=1;
			__tkmrcInfo.z = atof(argv[2]);
			DEBUGPRINT1("z:%f\n", __tkmrcInfo.z);
			SBREAK;
		}
		SCASE("HistNum") {
			__tkmrcInfo.nhist = atoi(argv[2]);
			if(1==__tkmrcInfo.flagHist) {
				free(__tkmrcInfo.histgram);
			}
			lmrcImageHistgram5(&(__tkmrcInfo.histgram), __tkmrcInfo.nhist, __tkmrcInfo.Min, __tkmrcInfo.Max, &mrc);
			__tkmrcInfo.flagHist = 1;
			SBREAK;
		}
		SCASE("Contrast") {
			__tkmrcInfo.flagContrast=1;
			__tkmrcInfo.Contrast= atof(argv[2]);
			__tkmrcInfo.Min     = MAX(__tkmrcInfo.Info.mean - __tkmrcInfo.Info.sd*__tkmrcInfo.Contrast,__tkmrcInfo.mrc.HeaderAMin);
			__tkmrcInfo.Max     = MIN(__tkmrcInfo.Info.mean + __tkmrcInfo.Info.sd*__tkmrcInfo.Contrast,__tkmrcInfo.mrc.HeaderAMax);
			SBREAK;
		}
		SCASE("min") {
			__tkmrcInfo.flagMin=1;
			__tkmrcInfo.Min = atof(argv[2]);
			SBREAK;
		}
		SCASE("max") {
			__tkmrcInfo.flagMax=1;
			__tkmrcInfo.Max = atof(argv[2]);
			SBREAK;
		}
		SCASE("inverse") {
			__tkmrcInfo.Inverse=atoi(argv[2]);
			SBREAK;
		}
		SCASE("log") {
			__tkmrcInfo.flagLog=1;
			if(__tkmrcInfo.flagMin <=0 ) {
				__tkmrcInfo.Min = 1e-6; 
			}
			SBREAK;
		}
		SCASE("pow") {
			__tkmrcInfo.flagPower=1;
			SBREAK;
		}
		SCASE("mag") {
			__tkmrcInfo.flagLog  =0;
			__tkmrcInfo.flagPower=0;
			SBREAK;
		}
		SDEFAULT {
			fprintf(stderr, "Not supported option : mrcInfoSet: %s\n", argv[1]);
			return TCL_ERROR;
			SBREAK;
		}
	SSWITCHEND;
	DEBUGPRINT2("%f %f\n", __tkmrcInfo.Min, __tkmrcInfo.Max);
	//sprintf(interp->result, "%d", 0);
	sprintf(s, "%d", 0);
	Tcl_SetResult(interp, s, TCL_VOLATILE); 
	return TCL_OK;
}

int 
tkmrcInfoGetCmd(ClientData clientData, Tcl_Interp *interp, int argc, CONST char* argv[])
{
	long i, x, y;
	char s[256];
	double data;
	mrcImage mrc;

	if(argc<3) {
		fprintf(stderr, "Arguments are too few.\n");	
		fprintf(stderr, "mrcInfoGet filename Nx|Ny|Nz|Mode|Lengthx|Lengthy|Lengthz|Max|Min|Mean|ProjX|ProjY|SectX|SectY [sectx|secty] \n");	
		return TCL_ERROR;
	} 

	/* File Open */
	mrc = __tkmrcInfo.mrc;
	if(0==__tkmrcInfo.flagHeader) { /* No Header */
		mrcFileRead(&mrc, (char*)argv[1], "in tkmrcInfoGetCmd", 0);
		__tkmrcInfo.mrc = mrc;
		__tkmrcInfo.flagHeader = 1;
		__tkmrcInfo.flagImage  = 1;
		DEBUGPRINT1("mrcFileRead for all: %s\n", argv[1]);
	} else if(0==__tkmrcInfo.flagImage) { /* No Image */
		mrcImageRead(&mrc, (char*)argv[1], "in tkmrcInfoGetCmd", 0);
		__tkmrcInfo.mrc = mrc;
		__tkmrcInfo.flagImage  = 1;
		DEBUGPRINT1("mrcFileRead for image: %s\n", argv[1]);
	}
	
	SSWITCH((char*)argv[2]) 
		SCASE("Nx") {
			//sprintf(interp->result, "%d", mrc.HeaderN.x);
			sprintf(s, "%d", mrc.HeaderN.x);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Ny") {
			//sprintf(interp->result, "%d", mrc.HeaderN.y);
			sprintf(s, "%d", mrc.HeaderN.y);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Nz") {
			//sprintf(interp->result, "%d", mrc.HeaderN.z);
			sprintf(s, "%d", mrc.HeaderN.z);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Mode") {
			if(IsImage(&mrc, "in tk", 0)) {
				//sprintf(interp->result, "%c", 'R');
				sprintf(s, "%c", 'R');
			} else {
				//sprintf(interp->result, "%c", 'F');
				sprintf(s, "%c", 'F');
			}
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Lengthx") {
			//sprintf(interp->result, "%g", mrc.HeaderLength.x);
			sprintf(s, "%g", mrc.HeaderLength.x);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Lengthy") {
			//sprintf(interp->result, "%g", mrc.HeaderLength.y);
			sprintf(s, "%g", mrc.HeaderLength.y);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Lengthz") {
			//sprintf(interp->result, "%g", mrc.HeaderLength.z);
			sprintf(s, "%g", mrc.HeaderLength.z);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("z") {
			//sprintf(interp->result, "%f", __tkmrcInfo.z);
			sprintf(s, "%f", __tkmrcInfo.z);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("thresLow") {
			//sprintf(interp->result, "%f", __tkmrcInfo.Min);
			sprintf(s, "%f", __tkmrcInfo.Min);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("thresHigh") {
			//sprintf(interp->result, "%f", __tkmrcInfo.Max);
			sprintf(s, "%f", __tkmrcInfo.Max);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Contrast") {
			//sprintf(interp->result, "%f", __tkmrcInfo.Contrast);
			sprintf(s, "%f", __tkmrcInfo.Contrast);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Max") {
			//sprintf(interp->result, "%f", mrc.HeaderAMax);
			sprintf(s, "%f", mrc.HeaderAMax);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Min") {
			//sprintf(interp->result, "%f", mrc.HeaderAMin);
			sprintf(s, "%f", mrc.HeaderAMin);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Mean") {
			//sprintf(interp->result, "%f", mrc.HeaderAMean);
			sprintf(s, "%f", mrc.HeaderAMean);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("SD") {
			if(0==__tkmrcInfo.flagInfo) {
				__tkmrcInfo.Info.mode = meanOfCentre;
				lmrcImageInformation(&(__tkmrcInfo.Info), &mrc);
			}
			//sprintf(interp->result, "%f", __tkmrcInfo.Info.sd);
			sprintf(s, "%f", __tkmrcInfo.Info.sd);
			Tcl_SetResult(interp, s, TCL_VOLATILE); 
			SBREAK;
		}
		SCASE("Hist") {
			if(0==__tkmrcInfo.flagHist) {
				lmrcImageHistgram5(&(__tkmrcInfo.histgram), __tkmrcInfo.nhist, __tkmrcInfo.Min, __tkmrcInfo.Max, &mrc);
				DEBUGPRINT1("%f", __tkmrcInfo.histgram[0]);
				__tkmrcInfo.flagHist = 1;
			}
			for(i=0; i<__tkmrcInfo.nhist; i++) {
				sprintf(s, "%f", __tkmrcInfo.histgram[i]); 
				Tcl_AppendElement(interp, s);
			}
			SBREAK;
		}
		SCASE("ReHist") {
			lmrcImageHistgram5(&(__tkmrcInfo.histgram), __tkmrcInfo.nhist, __tkmrcInfo.Min, __tkmrcInfo.Max, &mrc);
			__tkmrcInfo.flagHist = 1;
			for(i=0; i<__tkmrcInfo.nhist; i++) {
				sprintf(s, "%f", __tkmrcInfo.histgram[i]); 
				Tcl_AppendElement(interp, s);
			}
			SBREAK;
		}
		SCASE("Spectrum") {
			if(IsFT(&mrc, "in tk", 0)
			&& 0==__tkmrcInfo.flagScattering) {
				floatVector* fv;
				fv = lmrcFSInfoScatteringAngularDistributionAverage(&(__tkmrcInfo.mrc));
				__tkmrcInfo.scattering  = (double*)memoryAllocate(sizeof(double)*fv->size, "in tk");
				__tkmrcInfo.nScattering = fv->size; 
				DEBUGPRINT1("size: %d\n", fv->size);
				for(i=0; i<fv->size; i++) {
					__tkmrcInfo.scattering[i] = fv->data[i];	
				}
				free(fv);
				__tkmrcInfo.flagScattering = 1;
			} 
			for(i=0; i<__tkmrcInfo.nScattering; i++) {
				sprintf(s, "%f", __tkmrcInfo.scattering[i]); 
				Tcl_AppendElement(interp, s);
			}
			SBREAK;
		}
		SCASE("Spectrum2") {
			if(IsFT(&mrc, "in tk", 0)
			&& 0==__tkmrcInfo.flagScattering) {
				floatVector* fv;
				floatVector* R;
				fv = lmrcFSInfoScatteringAngularDistributionAverage(&(__tkmrcInfo.mrc));
				R  = lmrcFSInfoSpacing(&(__tkmrcInfo.mrc));
				if(fv->size!=R->size) {
					fprintf(stderr, "R!=Scat: Something wrong for Spectrum2 in tkForMRC\n");
				}
				__tkmrcInfo.nScattering = fv->size;
				DEBUGPRINT1("size: %d\n", fv->size);
				__tkmrcInfo.scattering  = (double*)memoryAllocate(sizeof(double)*__tkmrcInfo.nScattering, "in tk");
				__tkmrcInfo.R           = (double*)memoryAllocate(sizeof(double)*__tkmrcInfo.nScattering,  "in tk");
				for(i=0; i<__tkmrcInfo.nScattering; i++) {
					__tkmrcInfo.scattering[i] = fv->data[i];	
					__tkmrcInfo.R[i]          = R->data[i];	
				}
				floatVectorFree(fv);
				floatVectorFree(R);
				free(fv);
				free(R);
				__tkmrcInfo.flagScattering = 1;
				__tkmrcInfo.flagR          = 1;
			} 
			for(i=0; i<__tkmrcInfo.nScattering; i++) {
				sprintf(s, "%f", __tkmrcInfo.R[i]); 
				Tcl_AppendElement(interp, s);
				sprintf(s, "%f", __tkmrcInfo.scattering[i]); 
				Tcl_AppendElement(interp, s);
			}
			SBREAK;
		}
		SCASE("Spectrum2D") {
			int j;
			DEBUGPRINT("Spectrum2D\n");	
			if(IsFT(&mrc, "in tk", 0)) {
				DEBUGPRINT2("FFT %f %d\n", axis, n);	
				mrcImageParaTypeInteger n;
				mrcImageParaTypeReal    axis;
				floatVector** fv;
				floatVector* R;
				axis = atof(argv[3]);	
				n    = atoi(argv[4]);
				DEBUGPRINT2("axis %f number %d\n", axis, n);	
				fv = lmrcFSInfoScatteringAngularDistributionDivisionAverage(&(__tkmrcInfo.mrc), axis*RADIAN, n, 0);

				__tkmrcInfo.nScattering = fv[0]->size;

				DEBUGPRINT1("nScattering %d \n",  __tkmrcInfo.nScattering);
				if(__tkmrcInfo.flagR==0) {
					R  = lmrcFSInfoSpacing(&(__tkmrcInfo.mrc));
					__tkmrcInfo.R           = (double*)memoryAllocate(sizeof(double)*__tkmrcInfo.nScattering,  "in tk");
					for(i=0; i<__tkmrcInfo.nScattering; i++) {
						__tkmrcInfo.R[i]          = R->data[i];	
						DEBUGPRINT3("%d %f %f\n", i, R->data[i], __tkmrcInfo.R[i]);
					}
					if(fv[0]->size!=R->size) {
						fprintf(stderr, "R!=Scat: Something wrong for Spectrum2D in tkForMRC\n");
					}
					floatVectorFree(R);
					__tkmrcInfo.flagR            = 1;
				}

				if(fv[0]->size!=R->size) {
					fprintf(stderr, "R!=Scat: Something wrong for Spectrum2D in tkForMRC\n");
				}
				__tkmrcInfo.scattering2D  = (double**)memoryAllocate(sizeof(double*)*n, "in tk");
				for(j=0; j<n; j++) {
					__tkmrcInfo.scattering2D[j]  = (double*)memoryAllocate(sizeof(double)*__tkmrcInfo.nScattering, "in tk");
					for(i=0; i<__tkmrcInfo.nScattering; i++) {
						__tkmrcInfo.scattering2D[j][i] = fv[j]->data[i];	
						DEBUGPRINT4("%d %d %f %f\n", j, i, fv[j]->data[i],  __tkmrcInfo.scattering2D[j][i]);
					}
					//floatVectorFree(fv[j]);
				}
				//free(fv);
				__tkmrcInfo.numDivision = n;
				__tkmrcInfo.axis = axis;
				__tkmrcInfo.flagScattering2D = 1;
			} else {
				DEBUGPRINT1("NO FFT File: %d\n", mrc.HeaderMode);
			}

			for(j=0; j<__tkmrcInfo.numDivision; j++) {
				for(i=0; i<__tkmrcInfo.nScattering; i++) {
					sprintf(s, "%f", __tkmrcInfo.R[i]); 
					Tcl_AppendElement(interp, s);
					sprintf(s, "%f", __tkmrcInfo.scattering2D[j][i]); 
					Tcl_AppendElement(interp, s);
				}
				sprintf(s, "NULL");  Tcl_AppendElement(interp, s);
				sprintf(s, "NULL");  Tcl_AppendElement(interp, s);
			}
			SBREAK;
		}
		SCASE("Spectrum2DMag") {
			int j;
			DEBUGPRINT("Spectrum2DMag\n");	
			if(IsFT(&mrc, "in tk", 0)) {
				DEBUGPRINT2("FFT %f %d\n", axis, n);	
				mrcImageParaTypeInteger n;
				mrcImageParaTypeReal    axis;
				floatVector** fv;
				floatVector* R;
				axis = atof(argv[3]);	
				n    = atoi(argv[4]);
				DEBUGPRINT2("axis %f number %d\n", axis, n);	
				fv = lmrcFSInfoScatteringAngularDistributionDivisionAverage(&(__tkmrcInfo.mrc), axis*RADIAN, n, 0);

				__tkmrcInfo.nScattering = fv[0]->size;

				DEBUGPRINT1("nScattering %d \n",  __tkmrcInfo.nScattering);
				if(__tkmrcInfo.flagR==0) {
					R  = lmrcFSInfoSpacing(&(__tkmrcInfo.mrc));
					__tkmrcInfo.R           = (double*)memoryAllocate(sizeof(double)*__tkmrcInfo.nScattering,  "in tk");
					for(i=0; i<__tkmrcInfo.nScattering; i++) {
						__tkmrcInfo.R[i]          = R->data[i];	
						DEBUGPRINT3("%d %f %f\n", i, R->data[i], __tkmrcInfo.R[i]);
					}
					if(fv[0]->size!=R->size) {
						fprintf(stderr, "R!=Scat: Something wrong for Spectrum2D in tkForMRC\n");
					}
					floatVectorFree(R);
					__tkmrcInfo.flagR            = 1;
				}

				if(fv[0]->size!=__tkmrcInfo.nScattering) {
					fprintf(stderr, "R(%d)!=Scat(%d): Something wrong for Spectrum2D in tkForMRC\n", fv[0]->size, __tkmrcInfo.nScattering);
				}
				__tkmrcInfo.scattering2D  = (double**)memoryAllocate(sizeof(double*)*n, "in tk");
				for(j=0; j<n; j++) {
					__tkmrcInfo.scattering2D[j]  = (double*)memoryAllocate(sizeof(double)*__tkmrcInfo.nScattering, "in tk");
					for(i=0; i<__tkmrcInfo.nScattering; i++) {
						if(0<fv[j]->data[i]) {
							__tkmrcInfo.scattering2D[j][i] = sqrt(fv[j]->data[i]);	
						} else {
							__tkmrcInfo.scattering2D[j][i] = 0;
						}
						DEBUGPRINT4("%d %d %f %f\n", j, i, fv[j]->data[i],  __tkmrcInfo.scattering2D[j][i]);
					}
					//floatVectorFree(fv[j]);
				}
				//free(fv);
				__tkmrcInfo.numDivision = n;
				__tkmrcInfo.axis = axis;
				__tkmrcInfo.flagScattering2D = 1;
			} else {
				DEBUGPRINT1("NO FFT File: %d\n", mrc.HeaderMode);
			}

			for(j=0; j<__tkmrcInfo.numDivision; j++) {
				for(i=0; i<__tkmrcInfo.nScattering; i++) {
					sprintf(s, "%f", __tkmrcInfo.R[i]); 
					Tcl_AppendElement(interp, s);
					sprintf(s, "%f", __tkmrcInfo.scattering2D[j][i]); 
					Tcl_AppendElement(interp, s);
				}
				sprintf(s, "NULL");  Tcl_AppendElement(interp, s);
				sprintf(s, "NULL");  Tcl_AppendElement(interp, s);
			}
			SBREAK;
		}
		SCASE("ProjX") { /* projection to x-axis */
			if(0==__tkmrcInfo.flagProjX) {
				lmrcImageXProjection(&(__tkmrcInfo.projX), &mrc);
				__tkmrcInfo.flagProjX = 1;
			}
			for(i=0; i<__tkmrcInfo.projX.HeaderN.x; i++) {
				mrcPixelDataGet(&(__tkmrcInfo.projX), i, 0, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				sprintf(s, " %f ", data); 
				Tcl_AppendResult(interp, s, NULL);
			}
			SBREAK;
		}
		SCASE("ProjY") { /* projection to y-axis */
			if(__tkmrcInfo.flagProjY!=1) {
				lmrcImageYProjection(&(__tkmrcInfo.projY), &mrc);

				__tkmrcInfo.flagProjY = 1;
			}
			for(i=0; i<__tkmrcInfo.projY.HeaderN.y; i++) {
				mrcPixelDataGet(&(__tkmrcInfo.projY), 0, i, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				sprintf(s, " %f ", data); 
				Tcl_AppendResult(interp, s, NULL);
			}
			SBREAK;
		}
		SCASE("SectY") { /* Parallel to x-axis */ 
			float Y0;
			Y0 = atof(argv[3]); /* y = Y0 */
			DEBUGPRINT1("SectionY at %f\n", Y0);

			lmrcImageYSection(&(__tkmrcInfo.sectY), &mrc, Y0);

			for(i=0; i<__tkmrcInfo.sectY.HeaderN.x; i++) {
				if(__tkmrcInfo.flagz) {
					mrcPixelDataGet(&(__tkmrcInfo.sectY), 
						i, 0, __tkmrcInfo.z, &data, mrcPixelRePart, mrcPixelHowNearest);
				} else {
					mrcPixelDataGet(&(__tkmrcInfo.sectY), 
						i, 0, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				}
				sprintf(s, " %f ", data); 
				Tcl_AppendResult(interp, s, NULL);
			}
			SBREAK;
		}
		SCASE("SectX") { /* Parallel to y-axis */
			float X0;
			X0 = atof(argv[3]); /* x = X0 */
			DEBUGPRINT1("SectionX at %f\n", X0);
			
			lmrcImageXSection(&(__tkmrcInfo.sectX), &mrc, X0);

			for(i=0; i<__tkmrcInfo.sectX.HeaderN.y; i++) {
				if(__tkmrcInfo.flagz) {
					mrcPixelDataGet(&(__tkmrcInfo.sectX), 
						0, i, __tkmrcInfo.z, 
						&data, mrcPixelRePart, mrcPixelHowNearest);
				}  else {
					mrcPixelDataGet(&(__tkmrcInfo.sectX), 
						0, i, -1,
						&data, mrcPixelRePart, mrcPixelHowNearest);
				}
				sprintf(s, " %f ", data); 
				Tcl_AppendResult(interp, s, NULL);
			}
			SBREAK;
		}
		SCASE("Section") { /* Section Data Get */
			float X0;


			X0 = atof(argv[3]); /* x = X0 */
			DEBUGPRINT1("SectionX at %f\n", X0);
			
			lmrcImageXSection(&(__tkmrcInfo.sectX), &mrc, X0);

			for(i=0; i<__tkmrcInfo.sectX.HeaderN.y; i++) {
				if(__tkmrcInfo.flagz) {
					mrcPixelDataGet(&(__tkmrcInfo.sectX), 
						0, i, __tkmrcInfo.z, 
						&data, mrcPixelRePart, mrcPixelHowNearest);
				}  else {
					mrcPixelDataGet(&(__tkmrcInfo.sectX), 
						0, i, -1,
						&data, mrcPixelRePart, mrcPixelHowNearest);
				}
				sprintf(s, " %f ", data); 
				Tcl_AppendResult(interp, s, NULL);
			}
			SBREAK;
		}
		SDEFAULT {
			fprintf(stderr, "Not supported Option: %s\n", argv[2]);
			fprintf(stderr, "mrcInfoSet filename Nx|Ny|Nz\n");	
			return TCL_ERROR;
			SBREAK;
		}
	SSWITCHEND;
	return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * tkMRCFileRead--
 *
 *	This procedure is called by the photo image type to read
 *	MRC format data from a file and write it into a given
 *	photo image.
 *
 * Results:
 *	A standard TCL completion code.  If TCL_ERROR is returned
 *	then an error message is left in interp->result.
 *
 * Side effects:
 *	The access position in file f is changed, and new data is
 *	added to the image given by imageHandle.
 *
 *----------------------------------------------------------------------
 */

static int
tkMRCFileRead(interp, f, fileName, formatString, imageHandle, destX, destY, width, height, srcX, srcY)
    Tcl_Interp *interp;		    /* Interpreter to use for reporting errors. */
    Tcl_Channel f;			        /* The image file, open for reading. */
    CONST char *fileName;		        /* The name of the image file. */
    Tcl_Obj *formatString;		    /* User-specified format string, or NULL. */
    Tk_PhotoHandle imageHandle;	/* The photo image to write into. */
    int destX, destY;		    /* Coordinates of top-left pixel in photo image to be written to. */
    int width, height;		    /* Dimensions of block of photo image to be written to. */
    int srcX, srcY;		        /* Coordinates of top-left pixel to be used in image being read. */
{
    int fileWidth, fileHeight;
    int i, nLines, nBytes, h, w, type, count;
    unsigned char *pixelPtr;
    Tk_PhotoImageBlock block;
	double data;
	float X, Y, x, y;
	mrcImage mrc;

	DEBUGPRINT6("dest(%d,%d) Dim(%d,%d) src(%d,%d)\n", destX, destY, width, height, srcX, srcY);	
    if (__tkmrcInfo.mrc.HeaderN.z<=0) {
		Tcl_AppendResult(interp, "MRC image file \"", fileName,
			"\" has z-dimension(s) < 0", (char *) NULL);
		return TCL_ERROR;
    }

	mrc        = __tkmrcInfo.mrc;
	fileWidth  = mrc.HeaderN.x;
	fileHeight = mrc.HeaderN.y;

    if ((fileWidth <= 0) || (fileHeight <= 0)) {
		Tcl_AppendResult(interp, "MRC image file \"", fileName,
		"\" has dimension(s) <= 0", (char *) NULL);
		return TCL_ERROR;
    }

    if ((srcX + width) > fileWidth) {
		width = fileWidth - srcX;
    }
    if ((srcY + height) > fileHeight) {
		height = fileHeight - srcY;
    }
    if ((width <= 0) || (height <= 0) || (srcX >= fileWidth) || (srcY >= fileHeight)) {
		return TCL_OK;
    }

    block.pixelSize = 1;
    block.offset[0] = 0;
	block.offset[1] = 0;
	block.offset[2] = 0;
    block.width = width;
	block.height = 1;
    block.pitch = block.pixelSize * fileWidth;

    Tk_PhotoExpand(interp, imageHandle, destX + width, destY + height);

	nLines = 1;
	nBytes = nLines*block.pitch;
    pixelPtr = (unsigned char *) ckalloc((unsigned) nBytes);
    block.pixelPtr = pixelPtr + srcX * block.pixelSize;

    DEBUGPRINT1("z:%f in read\n", __tkmrcInfo.z);
    for (h = height; h > 0; h --) {
		if(h<nLines) {
			nLines = h;
			nBytes = nLines*block.pitch;
		}
		block.height = 1;
		for(w=srcX; w<fileWidth ; w++) {
			/* DEBUGPRINT2("%d, %d\n", w, h); */
			if(IsImage(&mrc, "in tk", 0)) {
				x = w;
				y = h - 1.0;
				mrcPixelDataGet(&mrc, 	(mrcImageParaTypeReal)x,
										(mrcImageParaTypeReal)y,	
										__tkmrcInfo.z,
										&data,
										mrcPixelMag, mrcPixelHowNearest);
			} else if(IsFT(&mrc, "in tk", 0)) {
				X = w - fileWidth/2.0;
				switch(mrc.HeaderMode) {
				    case mrcFloatRadonFT: {
						Y = h - 1;
						break;
					}
					default: {
						Y = h - fileHeight/2.0 - 1;
						break;
					}
				}	
				switch(mrc.HeaderMode) {
				    case mrcFloatRadonFT: {
						if(fileHeight <= Y
						|| Y < 0.0
						|| X < -fileWidth/2.0 
						|| fileWidth/2.0 <= X ) {
							fprintf(stderr, "too wide range: %g %g\n", X, Y);
							data = 0.0;
						} else {
							mrcPixelDataGet(&mrc,
								(mrcImageParaTypeReal)X,
								(mrcImageParaTypeReal)Y,
								__tkmrcInfo.z,
								&data,
								mrcPixelMag, mrcPixelHowNearest);
						}
						break;
				    }
			 	    default: {
						if(fileHeight/2.0 <= Y
						|| Y < -fileHeight/2.0
						|| X < -fileWidth/2.0 
						|| fileWidth/2.0 <= X ) {
							data = 0.0;
						} else {
							mrcPixelDataGet(&mrc, 	
								(mrcImageParaTypeReal)X,
								(mrcImageParaTypeReal)Y,	
								__tkmrcInfo.z,
								&data,
								mrcPixelMag, mrcPixelHowNearest);
						}
						break;
				    }
				}
			} else {
				fprintf(stderr, "Not supported Mode\n");
				exit(EXIT_FAILURE);
			}
			if(__tkmrcInfo.flagLog==0&&__tkmrcInfo.flagPower==0) {
				data = (data - __tkmrcInfo.Min)/(__tkmrcInfo.Max - __tkmrcInfo.Min)*255.0;	
			} else if(__tkmrcInfo.flagLog==1) {
				if(__tkmrcInfo.Min<=0) {
					__tkmrcInfo.Min = 1e-6;
				}
				//fprintf(stderr, "%f %f %f -> ", data, __tkmrcInfo.Min, __tkmrcInfo.Max);
				data = (log10(data) - log10(__tkmrcInfo.Min))/(log10(__tkmrcInfo.Max) - log10(__tkmrcInfo.Min))*255.0;	
				//fprintf(stderr, "%f \n ", data);
			} else if(__tkmrcInfo.flagLog==0&&__tkmrcInfo.flagPower==1) {
				data = (SQR(data) - SQR(__tkmrcInfo.Min))/(SQR(__tkmrcInfo.Max) - SQR(__tkmrcInfo.Min))*255.0;	
			} 
			if(255.0<data) {
				data = 255.0;
			} else if(data<0.0) {
				data = 0.0;
			} 
			block.pixelPtr[w] = (unsigned char)data;
		}
		Tk_PhotoPutBlock(interp, imageHandle, &block, destX, destY, width, 1, TK_PHOTO_COMPOSITE_SET);
		destY ++;
    }
    ckfree((char *) pixelPtr);
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * tkMRCFileWrite--
 *
 *	This procedure is invoked to write image data to a file in MRC 
 *	format.
 *
 * Results:
 *	A standard TCL completion code.  If TCL_ERROR is returned
 *	then an error message is left in interp->result.
 *
 * Side effects:
 *	Data is written to the file given by "fileName".
 *
 *----------------------------------------------------------------------
 */

static int
tkMRCFileWrite(interp, fileName, formatString, blockPtr)
    Tcl_Interp *interp;
    CONST char *fileName;
    Tcl_Obj *formatString;
    Tk_PhotoImageBlock *blockPtr;
{
    FILE *f;
    int w, h;
    int greenOffset, blueOffset, nBytes;
    unsigned char *pixelPtr, *pixLinePtr;
	mrcImage mrc;
	double data;

    mrc.HeaderN.x = blockPtr->width;
	mrc.HeaderN.y = blockPtr->height;
	mrc.HeaderN.z = 1;
	mrc.HeaderMode = mrcCharImage;
	mrcInit(&mrc, 0);

    pixLinePtr  = blockPtr->pixelPtr  + blockPtr->offset[0];
    greenOffset = blockPtr->offset[1] - blockPtr->offset[0];
    blueOffset  = blockPtr->offset[2] - blockPtr->offset[0];

	for (h = blockPtr->height; h > 0; h--, pixLinePtr+=blockPtr->pitch) {
	    for (w = blockPtr->width, pixelPtr = pixLinePtr; w > 0; w--, pixelPtr+=blockPtr->pixelSize) {
			data = *pixelPtr;
			mrcPixelDataSet(&mrc, 	(mrcImageParaTypeReal)(w),
									(mrcImageParaTypeReal)(h-1),	
									0.0,
									data,
									mrcPixelMag);
			
	    }
    }
	__tkmrcInfo.fileName = strdup(fileName);
	mrcFileWrite(&mrc, __tkmrcInfo.fileName, "in tkMRCFileWrite", 0);
	return TCL_OK;
}

