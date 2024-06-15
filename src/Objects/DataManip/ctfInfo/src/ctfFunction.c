/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfFunction ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfFunction 
#%Z% Attention
#%Z%      Mode 
#%Z%        0: Phase CTF
#%Z%        1: PhaseCTF + ratio*AmpCTF
#%Z%
*/
static char __sccs_id[] = "%Z%ctfFunction ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#undef DEBUG
#undef DEBUG2
#include "../inc/ctfInfo.h"
#include "genUtil.h"

/*
	info->mode
		0 : Only Phase Contrast
*/

#ifdef PVM
#include "pvm3.h"

void
ctfFunctionPVMStart(ctfInfo* info, float R, int tid, long mode)
{
	int msgtag;
	int linfo;

	DEBUGPRINT2("ctfFunctionPVMStart: %f to %x\n", R, tid);
	ctfInfoSendByPVM(info, tid, 0);
	pvm_initsend(PvmDataDefault);	
	pvm_pkfloat(&R,    1, 1);
	pvm_pklong (&mode, 1, 1);
	msgtag = 0; linfo = pvm_send(tid, msgtag);
	switch(linfo) {
		case PvmBadParam: {
			DEBUGPRINT("in ctfFunctionPVMStart\n");
		}
		case PvmSysErr: {
			DEBUGPRINT("PvmSysErr in ctfFunctionPVMStart\n");
		}
		case PvmNoBuf: {
			DEBUGPRINT("PvmNoBuf in ctfFunctionPVMStart\n");
		}
	}
}

float
ctfFunctionPVMEnd(ctfInfo* info, float R, int tid, long mode)
{
	float CTF;
	int msgtag;
	
	DEBUGPRINT1("ctfFunctionPVMEnd: %f\n", R);
	msgtag = 0; pvm_recv(tid, msgtag);
	pvm_upkfloat(&CTF,    1, 1);

	return CTF;
}

void
ctfFunctionPVMServer()
{
	ctfInfo info;
	float   R;
	long    mode;
	float   CTF;
	int tid;
	int msgtag;
	int linfo;

	DEBUGPRINT("ctfFunctionPVMServer \n");
	tid = pvm_parent();

	ctfInfoRecieveByPVM(&info, tid, 0); 
	msgtag = 0; pvm_recv(tid, msgtag);
	pvm_upkfloat(&R,    1, 1);
	pvm_upklong (&mode, 1, 1);

	CTF = ctfFunction(&info, R, mode);

	pvm_initsend(PvmDataDefault);
	pvm_pkfloat(&CTF,    1, 1);
	msgtag = 0; linfo = pvm_send(tid, msgtag);

	return;
}

#endif
float
ctfSignalFunction(ctfInfo* info, float R, long mode) 
{
	float Signal;
	float SignalIn;
	float SignalAliasing = 0;
	float SignalAliasingIn = 0;
	float OtherWeight = 1.0;
	
	Signal = info->I0
	        *fabs(ctfFunction(info, R, mode))
			*ctfMolecularEnvelopeFunction(info, R, mode)
			*ctfVibrationFunction(info, R, mode)
			*ctfMTFFunction(info, R, mode);
	SignalIn = info->I0
			*ctfMolecularEnvelopeInElasticFunction(info, R, mode)
			*ctfVibrationFunction(info, R, mode)
			*ctfMTFFunction(info, R, mode);

	if(1==info->flagAliasing) {
		SignalAliasing = info->I0
	        *fabs(ctfFunction(info, info->NyquistFrequency*2-R, mode))
			*ctfMolecularEnvelopeFunction(info, info->NyquistFrequency*2-R, mode)
			*ctfVibrationFunction(info, info->NyquistFrequency*2-R, mode)
			*ctfMTFFunction(info, info->NyquistFrequency*2-R, mode);
		SignalAliasingIn = info->I0
		    *ctfMolecularEnvelopeInElasticFunction(info, info->NyquistFrequency*2-R, mode) 
			*ctfVibrationFunction(info, info->NyquistFrequency*2-R, mode)
			*ctfMTFFunction(info, info->NyquistFrequency*2-R, mode);
	}
	Signal = Signal + SignalIn + SignalAliasing + SignalAliasingIn;

	return Signal;
}


float
ctfSignalPowerFunction(ctfInfo* info, float R, long mode) 
{
	float Signal;
	float SignalIn;
	float SignalAliasing = 0;
	float SignalAliasingIn = 0;
	DEBUGPRINT("ctfSignalPowerFunction \n");

	Signal = info->I0
	        *fabs(ctfFunction(info, R, mode))
			*ctfMolecularEnvelopeFunction(info, R, mode)
			*ctfVibrationFunction(info, R, mode)
			*ctfMTFFunction(info, R, mode);
	SignalIn = info->I0
			*ctfMolecularEnvelopeInElasticFunction(info, R, mode)
			*ctfVibrationFunction(info, R, mode)
			*ctfMTFFunction(info, R, mode); 
	if(info->flagAliasing) {
		SignalAliasing = info->I0
	        *fabs(ctfFunction(info, info->NyquistFrequency*2-R, mode))
			*ctfMolecularEnvelopeFunction(info, info->NyquistFrequency*2-R, mode)
			*ctfVibrationFunction(info, info->NyquistFrequency*2-R, mode)
			*ctfMTFFunction(info, info->NyquistFrequency*2-R, mode);
		SignalAliasingIn = info->I0
		    *ctfMolecularEnvelopeInElasticFunction(info, info->NyquistFrequency*2-R, mode) 
			*ctfVibrationFunction(info, info->NyquistFrequency*2-R, mode)
			*ctfMTFFunction(info, info->NyquistFrequency*2-R, mode);
	}
	Signal = SQR(Signal)+SQR(SignalIn)+SQR(SignalAliasing)+SQR(SignalAliasingIn);

	return Signal;
}

float
ctfNoiseFunction(ctfInfo* info, float R, long mode) 
{
	float Noise;
	float NoiseAliasing = 0;

	Noise = info->I0
	       *info->WhiteNoise
		   *ctfMTFFunction(info, R, mode);

	if(info->flagAliasing) {
		NoiseAliasing = info->I0
	       *info->WhiteNoise
		   *ctfMTFFunction(info, info->NyquistFrequency*2-R, mode);
	}
	Noise = Noise + NoiseAliasing;
	return Noise;
}

float
ctfNoisePowerFunction(ctfInfo* info, float R, long mode) 
{
	float Noise;
	float NoiseAliasing = 0;
	DEBUGPRINT("ctfNoisePowerFunction \n");
	Noise = info->I0
	       *info->WhiteNoise
		   *ctfMTFFunction(info, R, mode);

	if(info->flagAliasing) {
		NoiseAliasing = info->I0
	       *info->WhiteNoise
		   *ctfMTFFunction(info, info->NyquistFrequency*2-R, mode);
	}
	Noise = SQR(Noise)+SQR(NoiseAliasing);
	return Noise;
}

float
ctfNoise2Function(ctfInfo* info, float R, long mode) 
{
	float Noise;
	float NoiseAliasing = 0;
	Noise = info->I0
	       *info->WhiteNoise2;
	if(info->flagAliasing) {
		NoiseAliasing = info->I0
	       *info->WhiteNoise2;
	}
	Noise = Noise + NoiseAliasing;
	return Noise;
}

float
ctfNoise2PowerFunction(ctfInfo* info, float R, long mode) 
{
	float Noise;
	float NoiseAliasing = 0;

	Noise = info->I0
	       *info->WhiteNoise2;
	if(info->flagAliasing) {
		NoiseAliasing = info->I0
	       *info->WhiteNoise2;
	}
	Noise = SQR(Noise)+SQR(NoiseAliasing);
	return Noise;
}

float
ctfScatteringFunction(ctfInfo* info, float R, long mode) 
{
	float Signal;
	float Noise;
	float Scattering;

	Signal = ctfSignalFunction(info, R, mode);
	Noise  = ctfNoiseFunction(info, R, mode);
	Scattering = Signal + Noise;	
	return Scattering;
}

float
ctfMolecularEnvelopeFunction(ctfInfo* info, float R, long mode) 
{
	float  MolecEnv;
	double molecEnv;
	DEBUGPRINT("ctfMorecurlarFunction \n");	
	R = R*1e10;
	if(1==info->flagMagnification && 0!=info->Magnification) {
		R *= info->Magnification;
	}

	if(info->flagMolecEnvTable) {
		MolecEnv = lmolecularEnvelopeDataGet(&(info->MolecEnvTable), R*1e-10, 0);
	} else if(info->flagElastic) {
		double A            = info->Elastic;
		double Shift        = info->ElasticShift*1e10;
		double Width        = info->ElasticWidth*1e10; 
		double Ring         = info->ElasticRing;
		double RingWidth    = info->ElasticRingWidth*1e10;	
		double RingPosition = info->ElasticRingPosition*1e10; 
		MolecEnv = A/(1+SQR((R-Shift)/(Width)))*(1+Ring/(1+SQR((R-RingPosition*1)/RingWidth))
		                                          +Ring/(1+SQR((R-RingPosition*2)/RingWidth)));
	} else {
		molecEnv = info->MolecEnv*1e-10; 
		MolecEnv = exp(-molecEnv*molecEnv*R*R/2);
	}
	return MolecEnv;	
}

float
ctfMolecularEnvelopeInElasticFunction(ctfInfo* info, float R, long mode) 
{
	float  MolecEnv;
	double molecEnv;
	
	DEBUGPRINT("ctfMolecularEnvelopeInElasticFunction \n");
	R = R*1e10;
	if(1==info->flagMagnification && 0!=info->Magnification) {
		R *= info->Magnification;
	}

	if(info->flagWithInElasticTable) {
		MolecEnv = lmolecularEnvelopeDataGet(&(info->InElasticEnvTable), R*1e-10, 0);
	} else if(info->flagInElastic) {
		double A            = info->InElastic;
		double Shift        = info->InElasticShift*1e10;
		double Width        = info->InElasticWidth*1e10; 
		double Ring         = info->InElasticRing;
		double RingWidth    = info->InElasticRingWidth*1e10;	
		double RingPosition = info->InElasticRingPosition*1e10; 
		MolecEnv = A/(1+SQR((R-Shift)/(Width)))*(1+Ring/(1+SQR((R-RingPosition*1)/RingWidth))
		                                          +Ring/(1+SQR((R-RingPosition*2)/RingWidth)));
	} else if(info->flagWithInElastic) {
		molecEnv = info->MolecEnv*1e-10; 
		MolecEnv = info->InElastic*exp(-molecEnv*molecEnv*R*R/2);
	} else {
		MolecEnv = 0;
	}
	return MolecEnv;	
}

float
ctfVibrationFunction(ctfInfo* info, float R, long mode) 
{
	float  Env;
	double B;
	DEBUGPRINT("ctfVibrationFunction \n");
	if(1==info->flagMagnification && 0!=info->Magnification) {
		R *= info->Magnification;
	}

	if(info->flagVibration) {
		B = info->BofVibration;
		switch(info->VibrationMode) {
			case 0: {
				Env = exp(-B*B*R*R/2.0); 
				break;
			}
			default: {
				fprintf(stderr, "Not supported mode in ctfVibrationFunction: %d\n", info->VibrationMode);
				Env = 1.0;
			}
		}
	} else {
		Env = 1.0;	
	}
	return Env;	
}

float
ctfFunctionSampling(float R, float Nyquist, long mode)
{
	double RR;
	if(Nyquist==0.0) {
		return 1.0;
	}
	RR = M_PI*R/Nyquist/2.0;
	if(RR==0) {
		return 1.0;
	} else {
		return sin(RR)/RR;	
	}
}

float 
ctfFunction(ctfInfo* info, float R, long mode)
{
	float CTF, dF;
	float Env;
	float lambda, E, Cs;
	float Ain;
	double Kai;
	double Total; 
/*
	if(R==0.0) {
		return 1.0;
	}
	fprintf(stderr, "%d", mode);
*/

	Env = 1.0;
	R = R*1e10;
	E = info->kV*1000;
	Cs = info->Cs*1e-3;
	dF = info->defocus*1e-10;
	lambda = wavelengthOfElectron(E);
	Ain = info->Ain*1e-3;
	
	if(1==info->flagMagnification && 0!=info->Magnification) {
		R *= info->Magnification;
	}
	Kai = - M_PI*(dF*lambda - 0.5*Cs*lambda*lambda*lambda*R*R)*R*R; 
	switch((ctfInfoModeWithAmplitudeContrast & info->mode)) { 
		case ctfInfoModePhaseCTFOnly: { 
			CTF = sin(Kai); 
			break; 
		} 
		case ctfInfoModePhaseAndAmpCTF: { 
			CTF = sin(Kai) - info->ratioOfAmpToPhase*cos(Kai);
			break;
		}
		default: {
			CTF = 0;
			DEBUGPRINT6("mode:%ld R:%e E:%e Cs:%e dF:%e lambda:%e\n", info->mode, R, E, Cs, dF, lambda);
			fprintf(stderr, "Not supported Mode :%ld in CTFFucntion\n", info->mode);
			break;
		}
	}
	
	Env *= (ctfEnvelopFunction(info, R*1e-10, mode));

	Total = Env*CTF;
	DEBUGPRINT3("R %f CTF %f Env %f\n", R, CTF, Env);
	if(0x100&info->mode) {
		//fprintf(stderr, "Ab");
		Total = fabs(Total);
	}

	return Total;
}

float 
ctfEnvelopFunction(ctfInfo* info, float R, long mode)
{
	float dF;
	float Env;
	float Env1;
	float Env2;
	float Env4;
	float lambda, E, Cs, Cc, dE, E0;
	float Ain;
	double dKai;	
	DEBUGPRINT1("ctfEnvelopFunction: mode %ld\n", mode);

	Env = Env1 = Env2 = Env4 = 1.0;
	R   = R*1e10;         		/* [/A]   -> [/m]  */
	E   = info->kV*1000;  		/* [keV] -> [eV] */
	dE  = info->dE;       		/* [eV]  -> [eV] */
	E0  = 511*1e3;        		/* [eV]  -> [eV] */
	Cs  = info->Cs*1e-3;  		/* [mm]  -> [m]  */
	Cc  = info->Cc*1e-3;  		/* [mm]  -> [m]  */
	dF  = info->defocus*1e-10;  /* [A]   -> [m]  */
	lambda = wavelengthOfElectron(E); /*    [m]  */
	Ain    = info->Ain*1e-3;    /* [mm]  -> [m]  */    

	if(0!=(ctfInfoModeWithMTF&info->mode)) {
		Env1 = ctfMTFFunction(info, R*1e-10, mode);
	}

	if(1==info->flagMagnification && 0!=info->Magnification) {
		R *= info->Magnification;
	}

	dKai   = M_PI*(Cs*lambda*lambda*R*R - dF)*R; 

	if(0!=(ctfInfoModeWithIlluminationAngle&info->mode)) {
		Env2 = (exp(-SQR(dKai)*SQR(Ain)/log(2)));
		DEBUGPRINT2("Env(Spatial) : %e at %e\n", Env2, R);
	}
	if(0!=(ctfInfoModeWithEnergySpread&info->mode)) {
		Env4 = (exp(-SQR(M_PI*lambda*R*R*Cc*dE/E*((1+E/E0)/(1+E/E0/2))/4/sqrt(log(2)))));
		DEBUGPRINT2("Env(Temporal): %e at %e\n", Env4, R);
	}
	return Env*Env1*Env2*Env4;
}

float
ctfMTFFunction(ctfInfo* info, float R, long mode)
{
	float MTF;
	float MTF2;
	float MTF3;
	float Env1;
	float MTFd2;
	float MTFd3;
	float MTFd4;
	float MTFd5;
	float MTFd6;
	
	R    = R*1e10;         		/* [/A]   -> [/m]  */
	MTF  = info->BofMTF*1e-10;   /* [ A]   -> [m]   */
	MTF2 = info->BofMTF2*1e-10;  /* [ A]   -> [m]   */
	MTF3 = info->WeightOfSecondTermForMTF; 
	MTFd2 = info->BofMTFd2*1e-20; /*[ A^2] -> [m^2]*/
	MTFd3 = info->BofMTFd3*1e-30; /*[ A^3] -> [m^3]*/
	MTFd4 = info->BofMTFd4*1e-40; /*[ A^4] -> [m^4]*/
	MTFd5 = info->BofMTFd5*1e-50; /*[ A^5] -> [m^5]*/
	MTFd6 = info->BofMTFd6*1e-60; /*[ A^6] -> [m^6]*/
		
	if(1==info->flagMagnification && 0!=info->Magnification) {
		R *= info->Magnification;
	}

	switch(info->MTFMode) {
		case ctfInfoMTFModeSingleExp: {
			Env1 = exp(-MTF*R);
			break;
		}
		case ctfInfoMTFModeSingleLorentzian: {
			Env1 = 1/(1+R*R*MTF2*MTF2); 
			break;
		}
		case ctfInfoMTFModeBoth: {
			Env1 = exp(-MTF*R)/(1+R*R*MTF2*MTF2);
			break;
		}
		case ctfInfoMTFModeLinear: {
			Env1 = MAX(1 - MTF*R, 0);
			break;
		}
		case ctfInfoMTFModeBothSum: {
			Env1 = (1-MTF3)*exp(-MTF*R)+MTF3/(1+R*R*MTF2*MTF2);
			break;
		}
		case ctfInfoMTFModePolynomial: {
			Env1 = exp(-MTF*R + MTFd2*R*R +MTFd3*R*R*R + MTFd4*R*R*R*R +MTFd5*R*R*R*R*R + MTFd6*R*R*R*R*R*R );
			break;
		}
		default: {
			fprintf(stderr, "Not supported MTFmode in ctfMTFFuction: %ld \n", info->MTFMode);
			Env1 = 1;
			fprintf(stderr, "Assign as MTF = %f\n", Env1);
			break;
		}
	}
	DEBUGPRINT2("Env(MTF) : %e at %e\n", Env1, R);
	if(1==info->flagSampling) {
		Env1 *= ctfFunctionSampling(R*1e-10, info->NyquistFrequency, mode);
	}
	return Env1;
}

float
ctfFunction2D(ctfInfo* info, float X /* A-1 */, float Y /* A-1 */, long mode)
{
	float angle;
	float R;
	float CTF;
	ctfInfo tmp;
	double avg;
	double diff;

	R     = sqrt(SQR(X)+SQR(Y));
	angle = atan2(Y, X) - info->defocus0axis;
	DEBUGPRINT2("Angle: %f %f\n", angle*DEGREE, info->defocus0axis);
	tmp = *info;
	if(tmp.flagAstigmatism) {
		avg  = (info->defocus2D[0] + info->defocus2D[1])/2.0;
		diff = (info->defocus2D[0] - info->defocus2D[1])/2.0;
		tmp.defocus = avg + diff*cos(2.0*angle);
		/*
		tmp.defocus = info->defocus2D[1]
			*sqrt(1 + (SQR(info->defocus2D[0])/SQR(info->defocus2D[1]) - 1)*cos(angle)); 
		*/
	}
	CTF = ctfFunction(&tmp, R, mode);
	return CTF;
}

float
wavelengthOfElectron(float E)
{
	return 12.26/sqrt(E*(1.0+0.9788e-6*E))*1e-10;
}

