/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% tkctfInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : tkctfInfo 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%tkctfInfo ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#undef DEBUG
#undef DEBUG2
#include "genUtil.h"
#include <tk.h>
#include "eosString.h"
#include "File.h"
#include "tkctfInfo.h"
#include "ctfZeroPoint.h"

static tkctfInfo __tkctfInfo;

int
tkctfInfoCmdSet(Tcl_Interp* interp)
{
	Tcl_CreateCommand(interp, "ctfInfoFile",   tkctfInfoFileCmd,        (ClientData)Tk_MainWindow(interp), (Tcl_CmdDeleteProc*)NULL);
	Tcl_CreateCommand(interp, "ctfInfoSet",    tkctfInfoSetCmd,         (ClientData)Tk_MainWindow(interp), (Tcl_CmdDeleteProc*)NULL);
	Tcl_CreateCommand(interp, "ctfInfoGet",    tkctfInfoGetCmd,         (ClientData)Tk_MainWindow(interp), (Tcl_CmdDeleteProc*)NULL);
	Tcl_CreateCommand(interp, "ctfInfoCalc",   tkctfInfoCalculateCmd,   (ClientData)Tk_MainWindow(interp), (Tcl_CmdDeleteProc*)NULL);
	Tcl_CreateCommand(interp, "ctfInfoCalc2D", tkctfInfoCalculate2DCmd, (ClientData)Tk_MainWindow(interp), (Tcl_CmdDeleteProc*)NULL);
	Tcl_CreateCommand(interp, "ctfInfoEval",   tkctfInfoEvaluateCmd,    (ClientData)Tk_MainWindow(interp), (Tcl_CmdDeleteProc*)NULL);
	return TCL_OK;
}

int 
tkctfInfoFileCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[])
{
	FILE* fpt;

	DEBUGPRINT3("%s %s %s\n", argv[0], argv[1], argv[2]);	
	SSWITCH((char*)argv[1]) 
		SCASE("write") {
			fpt = fileOpen((char*)argv[2], "a");
			ctfInfoWrite(fpt, __tkctfInfo.ctf, "", 0);    
			SBREAK;
		}
		SCASE("read") {
			fpt = fileOpen((char*)argv[2], "r");
			ctfInfoRead(fpt, &(__tkctfInfo.ctf), "", 0);    
			SBREAK;
		}
		SDEFAULT {
			fprintf(stderr, "Not supported argument: %s\n", argv[1]); 
			SBREAK;
		}
	SSWITCHEND;
	return 1;
}

int 
tkctfInfoSetCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[])
{
	DEBUGPRINT3("%s %s %s\n", argv[0], argv[1], argv[2]);	
	SSWITCH((char*)argv[1]) 
		SCASE("kV") {
			__tkctfInfo.ctf.kV = atof(argv[2]);
			SBREAK;
		}
		SCASE("defocus") {
			__tkctfInfo.ctf.defocus = atof(argv[2]);
			SBREAK;
		}
		SCASE("defocus2D0") {
			__tkctfInfo.ctf.defocus2D[0] = atof(argv[2]);
			SBREAK;
		}
		SCASE("defocus2D1") {
			__tkctfInfo.ctf.defocus2D[1] = atof(argv[2]);
			SBREAK;
		}
		SCASE("defocus0axis") {
			__tkctfInfo.ctf.defocus0axis = atof(argv[2])*RADIAN;
			SBREAK;
		}
		SCASE("Cc") {
			__tkctfInfo.ctf.Cc = atof(argv[2]);
			SBREAK;
		}
		SCASE("dE") {
			__tkctfInfo.ctf.dE = atof(argv[2]);
			SBREAK;
		}
		SCASE("Cs") {
			__tkctfInfo.ctf.Cs = atof(argv[2]);
			SBREAK;
		}
		SCASE("Ai") {
			__tkctfInfo.ctf.Ain = atof(argv[2]);
			SBREAK;
		}
		SCASE("Mode") {
			__tkctfInfo.ctf.mode = atoi(argv[2]);
			SBREAK;
		}
		SCASE("MTFMode") {
			__tkctfInfo.ctf.MTFMode = atoi(argv[2]);
			SBREAK;
		}
		SCASE("MTF") {
			__tkctfInfo.ctf.BofMTF = atof(argv[2]);
			SBREAK;
		}
		SCASE("MTF2") {
			__tkctfInfo.ctf.BofMTF2 = atof(argv[2]);
			SBREAK;
		}
		SCASE("MTF2Weight") {
			__tkctfInfo.ctf.WeightOfSecondTermForMTF = atof(argv[2]);
			SBREAK;
		}
		SCASE("Noise") {
			__tkctfInfo.ctf.flagWhiteNoise = 1;
			__tkctfInfo.ctf.WhiteNoise = atof(argv[2]);
			SBREAK;
		}
		SCASE("Noise2") {
			__tkctfInfo.ctf.flagWhiteNoise2 = 1;
			__tkctfInfo.ctf.WhiteNoise2 = atof(argv[2]);
			SBREAK;
		}
		SCASE("AoverP") {
			__tkctfInfo.ctf.ratioOfAmpToPhase = atof(argv[2]);
			SBREAK;
		}
		SCASE("I") {
			__tkctfInfo.ctf.I0 = atof(argv[2]);
			SBREAK;
		}
		SCASE("Mag") {
			__tkctfInfo.ctf.Magnification = atof(argv[2]);
			__tkctfInfo.ctf.flagMagnification = 1;
			SBREAK;
		}
		SCASE("R") {
			int i,j;
			char* s;
			if(__tkctfInfo.flagR != 0) {
				free(__tkctfInfo.R);
			}
			__tkctfInfo.nR = atoi(argv[2]);
			__tkctfInfo.R  = (float*)malloc(sizeof(float)*(__tkctfInfo.nR));
			DEBUGPRINT1("%s\n", argv[3]);
			s = (char*)argv[3];	
			j = 0;
			for(i=0; i<__tkctfInfo.nR; i++) {
				while(' ' == s[j]) {
					j++;
				}
				__tkctfInfo.R[i] = atof(s+j);
				DEBUGPRINT2("R(%d): %g\n", i, __tkctfInfo.R[i])
				while(' ' != s[j]) {
					j++;
				}
			}
			__tkctfInfo.flagR = 1;
			SBREAK;
		}
		SCASE("flagVibration") {
			__tkctfInfo.ctf.flagVibration = atoi(argv[2]);
			SBREAK;
		}
		SCASE("BofVibration") {
			__tkctfInfo.ctf.BofVibration  = atof(argv[2]);
			SBREAK;
		}
		SCASE("VibrationMode") {
			__tkctfInfo.ctf.VibrationMode = atoi(argv[2]);
#ifdef DEBUG2
			fprintf(stderr, "VibrationMode %ld\n", __tkctfInfo.ctf.VibrationMode);
#endif
			SBREAK;
		}
		SCASE("Aliasing") { 
			__tkctfInfo.ctf.flagAliasing     = atoi(argv[2]);
			if(3<argc) {
				__tkctfInfo.ctf.NyquistFrequency = atof(argv[3]);
			}
			SBREAK;
		}
		SCASE("Sampling") { 
			__tkctfInfo.ctf.flagSampling     = atoi(argv[2]);
			if(3<argc) {
				__tkctfInfo.ctf.NyquistFrequency = atof(argv[3]);
			}
			SBREAK;
		}
		SCASE("MolecEnv") {
			__tkctfInfo.ctf.MolecEnv = atof(argv[2]);
			SBREAK;
		}
		SCASE("MolecEnvMode") {
			__tkctfInfo.ctf.flagMolecEnvTable = atoi(argv[2]);
			SBREAK;
		}
		SCASE("MolecEnvTable") {
			FILE* fpt;
			fpt = fileOpen((char*)argv[2], "r");
			lmolecularEnvelopeFileRead(fpt, &(__tkctfInfo.ctf.MolecEnvTable), 0);
			fclose(fpt);
			SBREAK;
		}
		SCASE("InElasticMode") {
			__tkctfInfo.ctf.flagWithInElastic = atoi(argv[2]);
		}
		SCASE("InElaMolecEnv") {
			__tkctfInfo.ctf.InElasticGaussian = atof(argv[2]);
			SBREAK;
		}
		SCASE("InElaMolecEnvMode") {
			__tkctfInfo.ctf.flagWithInElasticTable = atoi(argv[2]);
			SBREAK;
		}
		SCASE("InElaMolecEnvTable") {
			FILE* fpt;
			fpt = fileOpen((char*)argv[2], "r");
			lmolecularEnvelopeFileRead(fpt, &(__tkctfInfo.ctf.InElasticEnvTable), 0);
			fclose(fpt);
			SBREAK;
		}
		SCASE("InElastic") { 
			__tkctfInfo.ctf.flagInElastic = atoi(argv[2]);
			if(3<argc) {
				__tkctfInfo.ctf.InElastic             = atof(argv[3]);
				__tkctfInfo.ctf.InElasticShift        = atof(argv[4]);
				__tkctfInfo.ctf.InElasticWidth        = atof(argv[5]);
				__tkctfInfo.ctf.InElasticRing         = atof(argv[6]);
				__tkctfInfo.ctf.InElasticRingPosition = atof(argv[7]);
				__tkctfInfo.ctf.InElasticRingWidth    = atof(argv[8]);
			}
			SBREAK;
		}
		SCASE("Elastic") { 
			__tkctfInfo.ctf.flagElastic = atoi(argv[2]);
			if(3<argc) {
				__tkctfInfo.ctf.Elastic               = atof(argv[3]);
				__tkctfInfo.ctf.ElasticShift          = atof(argv[4]);
				__tkctfInfo.ctf.ElasticWidth          = atof(argv[5]);
				__tkctfInfo.ctf.ElasticRing           = atof(argv[6]);
				__tkctfInfo.ctf.ElasticRingPosition   = atof(argv[7]);
				__tkctfInfo.ctf.ElasticRingWidth      = atof(argv[8]);
			}
			SBREAK;
		}

		SCASE("MTFd2") {
			__tkctfInfo.ctf.BofMTFd2 = atoi(argv[2]);
			SBREAK;
		}
		SCASE("MTFd3") {
			__tkctfInfo.ctf.BofMTFd3 = atoi(argv[2]);
			SBREAK;
		}
		SCASE("MTFd4") {
			__tkctfInfo.ctf.BofMTFd4 = atoi(argv[2]);
			SBREAK;
		}
		SCASE("MTFd5") {
			__tkctfInfo.ctf.BofMTFd5 = atoi(argv[2]);
			SBREAK;
		}
		SCASE("MTFd6") {
			__tkctfInfo.ctf.BofMTFd6 = atoi(argv[2]);
			SBREAK;
		}
		SDEFAULT {
			fprintf(stderr, "Not supported Command: %s\n", argv[1]);
			SBREAK;
		}
	SSWITCHEND;
	
	return TCL_OK;
}

int 
tkctfInfoGetCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[])
{
	char s[1024];
	int i;

	SSWITCH((char*)argv[1]) 
		SCASE("kV") {
			sprintf(s, "%g", __tkctfInfo.ctf.kV);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("defocus") {
			sprintf(s, "%g", __tkctfInfo.ctf.defocus);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("defocus2D0") {
			sprintf(s, "%g", __tkctfInfo.ctf.defocus2D[0]);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("defocus2D1") {
			sprintf(s, "%g", __tkctfInfo.ctf.defocus2D[1]);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("defocus0axis") {
			sprintf(s, "%g", __tkctfInfo.ctf.defocus0axis*DEGREE);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("Cc") {
			sprintf(s, "%g", __tkctfInfo.ctf.Cc);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("dE") {
			sprintf(s, "%g", __tkctfInfo.ctf.dE);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("Cs") {
			sprintf(s, "%g", __tkctfInfo.ctf.Cs);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("Ain") {
			sprintf(s, "%g", __tkctfInfo.ctf.Ain);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("Mode") {
			sprintf(s, "%ld", __tkctfInfo.ctf.mode);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("MTFMode") {
			sprintf(s, "%d", __tkctfInfo.ctf.MTFMode);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("MTF") {
			sprintf(s, "%g", __tkctfInfo.ctf.BofMTF);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("MTF2") {
			sprintf(s, "%g", __tkctfInfo.ctf.BofMTF2);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("WeightForMTF") {
			sprintf(s, "%g", __tkctfInfo.ctf.WeightOfSecondTermForMTF);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("MolecEnv") {
			sprintf(s, "%g", __tkctfInfo.ctf.MolecEnv);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("Noise") {
			sprintf(s, "%g", __tkctfInfo.ctf.WhiteNoise);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("Noise2") {
			sprintf(s, "%g", __tkctfInfo.ctf.WhiteNoise2);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("AoverP") {
			sprintf(s, "%g", __tkctfInfo.ctf.ratioOfAmpToPhase);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("I") {
			sprintf(s, "%g", __tkctfInfo.ctf.I0);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("Mag") {
			sprintf(s, "%g", __tkctfInfo.ctf.Magnification);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("R") {
			int i;
			for(i=0; i<__tkctfInfo.nR; i++) {
				sprintf(s, "%g", __tkctfInfo.R[i]);
				Tcl_AppendElement(interp, s);
			}
			SBREAK;
		}
		SCASE("Zero") {
			int i;
			int Nmax;
			ctfInfoZeroPoint zero;
			float R, data, data1;
			if(argc<5) {
				fprintf(stderr, "%s %s RMax Nmax dR\n", argv[0], argv[1]);
				return TCL_ERROR;
			}
			zero.RMax = atof(argv[2]); 
			Nmax      = atoi(argv[3]); 
			zero.dR   = atof(argv[4]);
			for(i=0; i<Nmax; i++) { 
				zero.N = i+1;
				R = ctfZeroPoint(&(__tkctfInfo.ctf), &zero, 0);
				if(0<=R) {
					data  = ctfNoiseFunction (&(__tkctfInfo.ctf), R, 0);
					data1 = ctfNoise2Function(&(__tkctfInfo.ctf), R, 0);
					sprintf(s, "%g", R);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%g", data);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%g", data1);
					Tcl_AppendElement(interp, s);
				} else {
					break;
				}
			}
			SBREAK;	
		}
		SCASE("Zero0") {
			int i;
			int Nmax;
			ctfInfoZeroPoint zero;
			float R, data, data1;
			ctfInfo tmp;

			if(argc<5) {
				fprintf(stderr, "%s %s RMax Nmax dR\n", argv[0], argv[1]);
				return TCL_ERROR;
			}
			zero.RMax = atof(argv[2]); 
			Nmax      = atoi(argv[3]); 
			zero.dR   = atof(argv[4]);

			tmp = __tkctfInfo.ctf;
			tmp.defocus = tmp.defocus2D[0];
			for(i=0; i<Nmax; i++) { 
				zero.N = i+1;
				R = ctfZeroPoint(&tmp, &zero, 0);
				if(0<=R) {
					data  = ctfNoiseFunction (&tmp, R, 0);
					data1 = ctfNoise2Function(&tmp, R, 0);
					sprintf(s, "%g", R);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%g", data);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%g", data1);
					Tcl_AppendElement(interp, s);
				} else {
					break;
				}
			}
			SBREAK;	
		}
		SCASE("Zero1") {
			int i;
			int Nmax;
			ctfInfoZeroPoint zero;
			float R, data, data1;
			ctfInfo tmp;

			if(argc<5) {
				fprintf(stderr, "%s %s RMax Nmax dR\n", argv[0], argv[1]);
				return TCL_ERROR;
			}
			zero.RMax = atof(argv[2]); 
			Nmax      = atoi(argv[3]); 
			zero.dR   = atof(argv[4]);

			tmp = __tkctfInfo.ctf;
			tmp.defocus = tmp.defocus2D[1];
			for(i=0; i<Nmax; i++) { 
				zero.N = i+1;
				R = ctfZeroPoint(&tmp, &zero, 0);
				if(0<=R) {
					data  = ctfNoiseFunction (&tmp, R, 0);
					data1 = ctfNoise2Function(&tmp, R, 0);
					sprintf(s, "%g", R);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%g", data);
					Tcl_AppendElement(interp, s);
					sprintf(s, "%g", data1);
					Tcl_AppendElement(interp, s);
				} else {
					break;
				}
			}
			SBREAK;	
		}
		SCASE("flagVibration") {
			sprintf(s, "%ld", __tkctfInfo.ctf.flagVibration);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("BofVibration") {
			sprintf(s, "%g", __tkctfInfo.ctf.BofVibration);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("VibrationMode") {
			sprintf(s, "%ld", __tkctfInfo.ctf.VibrationMode);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("Aliasing") {
			sprintf(s, "%ld %f", __tkctfInfo.ctf.flagAliasing, __tkctfInfo.ctf.NyquistFrequency);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("Sampling") {
			sprintf(s, "%ld %f", __tkctfInfo.ctf.flagSampling, __tkctfInfo.ctf.NyquistFrequency);
			Tcl_SetResult(interp, s, TCL_VOLATILE);
			SBREAK;
		}
		SCASE("Elastic") { 
			Tcl_AppendElement(interp, "flagElastic");
			sprintf(s, "%ld", __tkctfInfo.ctf.flagElastic);         Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "Elastic");
			sprintf(s, "%g", __tkctfInfo.ctf.Elastic);             Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "ElasticShift");
			sprintf(s, "%g", __tkctfInfo.ctf.ElasticShift);        Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "ElasticWidth");
			sprintf(s, "%g", __tkctfInfo.ctf.ElasticWidth);        Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "ElasticRing");
			sprintf(s, "%g", __tkctfInfo.ctf.ElasticRing);         Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "ElasticRingPosition");
			sprintf(s, "%g", __tkctfInfo.ctf.ElasticRingPosition); Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "ElasticRingWidth");
			sprintf(s, "%g", __tkctfInfo.ctf.ElasticRingWidth);    Tcl_AppendElement(interp, s);
			SBREAK;
		}
		SCASE("InElastic") { 
			Tcl_AppendElement(interp, "flagInElastic");
			sprintf(s, "%ld", __tkctfInfo.ctf.flagInElastic);         Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "InElastic");
			sprintf(s, "%g", __tkctfInfo.ctf.InElastic);             Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "InElasticShift");
			sprintf(s, "%g", __tkctfInfo.ctf.InElasticShift);        Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "InElasticWidth");
			sprintf(s, "%g", __tkctfInfo.ctf.InElasticWidth);        Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "InElasticRing");
			sprintf(s, "%g", __tkctfInfo.ctf.InElasticRing);         Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "InElasticRingPosition");
			sprintf(s, "%g", __tkctfInfo.ctf.InElasticRingPosition); Tcl_AppendElement(interp, s);
			Tcl_AppendElement(interp, "InElasticRingWidth");
			sprintf(s, "%g", __tkctfInfo.ctf.InElasticRingWidth);    Tcl_AppendElement(interp, s);
			SBREAK;
		}
		SDEFAULT {
			fprintf(stderr, "Not supported Command: %s\n", argv[1]);
			SBREAK;
		}
	SSWITCHEND;
	return TCL_OK;	
}

int
tkctfInfoCalculateCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[])
{
	int size;
	int i;
	int offset;
	char s[10240];
	float data, data1, data2;
	float R;

	DEBUGPRINT2("%s %s\n", argv[0], argv[1]);
	if(!__tkctfInfo.flagR) {
		return TCL_ERROR;
	}
	for(i=0; i<__tkctfInfo.nR; i++) {
		R = __tkctfInfo.R[i];
		SSWITCH((char*)argv[1]) 
			SCASE("CTF") {
				data = ctfScatteringFunction(&(__tkctfInfo.ctf), R, 0);
				SBREAK;
			}
			SCASE("CTFPower") {
				data  = ctfSignalPowerFunction(&(__tkctfInfo.ctf), R, 0);
				data1 = ctfNoisePowerFunction(&(__tkctfInfo.ctf), R, 0);
				data2 = ctfNoise2PowerFunction(&(__tkctfInfo.ctf), R, 0);
				data  = data + data1 + data2;
				SBREAK;
			}
			SCASE("CTFcore") {
				data = ctfFunction(&(__tkctfInfo.ctf), R, 0);
				SBREAK;
			}
			SCASE("CTFcorePower") {
				data = ctfFunction(&(__tkctfInfo.ctf), R, 0);
				data = SQR(data);
				SBREAK;
			}
			SCASE("CTFNoise") {
				data  = ctfNoiseFunction(&(__tkctfInfo.ctf), R, 0);
				data1 = ctfNoise2Function(&(__tkctfInfo.ctf), R, 0);
				data  = data + data1;
				SBREAK;
			}
			SCASE("CTFNoisePower") {
				data  = ctfNoisePowerFunction(&(__tkctfInfo.ctf), R, 0);
				data1 = ctfNoise2PowerFunction(&(__tkctfInfo.ctf), R, 0);
				data = data + data1;
				SBREAK;
			}
			SCASE("CTFSignal") {
				data = ctfSignalFunction(&(__tkctfInfo.ctf), R, 0);
				SBREAK;
			}
			SCASE("CTFSignalPower") {
				data = ctfSignalPowerFunction(&(__tkctfInfo.ctf), R, 0);
				SBREAK;
			}
			SDEFAULT {
				data = 0;
				fprintf(stderr, "Not supported Command: %s\n", argv[1]);
				SBREAK;
			}
		SSWITCHEND;
		sprintf(s, "%g", data); 
		Tcl_AppendElement(interp, s);
	}
	return TCL_OK;
}

int
tkctfInfoCalculate2DCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[])
{
	int size;
	int i;
	int offset;
	char s[1024];
	float data, data1, data2;
	float R;
	int which;
	ctfInfo tmp;

	DEBUGPRINT2("%s %s\n", argv[0], argv[1]);
	if(!__tkctfInfo.flagR) {
		return TCL_ERROR;
	}

	tmp = __tkctfInfo.ctf; 
	which = atoi(argv[2]);
	tmp.defocus = tmp.defocus2D[which];

	for(i=0; i<__tkctfInfo.nR; i++) {
		R = __tkctfInfo.R[i];
		
		SSWITCH((char*)argv[1]) 
			SCASE("CTF") {
				data = ctfScatteringFunction(&tmp, R, 0);
				SBREAK;
			}
			SCASE("CTFPower") {
				data  = ctfSignalPowerFunction(&tmp, R, 0);
				data1 = ctfNoisePowerFunction(&tmp, R, 0);
				data2 = ctfNoise2PowerFunction(&tmp, R, 0);
				data  = data + data1 + data2;
				SBREAK;
			}
			SCASE("CTFcore") {
				data = ctfFunction(&tmp, R, 0);
				SBREAK;
			}
			SCASE("CTFcorePower") {
				data = ctfFunction(&tmp, R, 0);
				data = SQR(data);
				SBREAK;
			}
			SCASE("CTFNoise") {
				data  = ctfNoiseFunction(&tmp, R, 0);
				data1 = ctfNoise2Function(&tmp, R, 0);
				data  = data + data1;
				SBREAK;
			}
			SCASE("CTFNoisePower") {
				data  = ctfNoisePowerFunction(&tmp, R, 0);
				data1 = ctfNoise2PowerFunction(&tmp, R, 0);
				data = data + data1;
				SBREAK;
			}
			SCASE("CTFSignal") {
				data = ctfSignalFunction(&tmp, R, 0);
				SBREAK;
			}
			SCASE("CTFSignalPower") {
				data = ctfSignalPowerFunction(&tmp, R, 0);
				SBREAK;
			}
			SDEFAULT {
				data = 0;
				fprintf(stderr, "Not supported Command: %s\n", argv[1]);
				SBREAK;
			}
		SSWITCHEND;
		sprintf(s, "%g", data); 
		Tcl_AppendElement(interp, s);
	}
	return TCL_OK;
}

int
tkctfInfoEvaluateCmd(ClientData clientData, Tcl_Interp* interp, int argc, CONST char* argv[])
{
	return TCL_OK;
}

