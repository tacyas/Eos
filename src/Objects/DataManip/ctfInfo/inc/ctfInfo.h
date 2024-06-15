#ifndef CTF_INFO_H
#define CTF_INFO_H
#include <stdio.h>

/* constant begin */
#define ctfInfoModeWithAmplitudeContrast    0x0f
#define ctfInfoModeWithMTF                  0x10
#define ctfInfoModeWithIlluminationAngle    0x20
#define ctfInfoModeWithEnergySpread         0x40
#define ctfInfoModeAbsoluteValue            0x100 

typedef enum ctfInfoMode {
	ctfInfoModePhaseCTFOnly   = 0,
	ctfInfoModePhaseAndAmpCTF = 1 
} ctfInfoMode;

typedef enum ctfInfoMTFMode {
	ctfInfoMTFModeSingleExp = 0,
	ctfInfoMTFModeSingleLorentzian = 1,
	ctfInfoMTFModeBoth      = 2,
	ctfInfoMTFModeLinear    = 3, 
	ctfInfoMTFModeBothSum   = 4,
	ctfInfoMTFModePolynomial = 5
} ctfInfoMTFMode;
/* constant end */

/* struct begin */
typedef struct moleculrEnvelope {
	char* filename; 
	int   nR;
	float* R;
	float* Envelope;
	int    mode;	
} molecularEnvelope;

typedef struct ctfInfo {
	float kV;      /* kV */
	float defocus; /* A : Underfocus is plus, while overfocus is minus*/
	float Cc;      /* mm */
	float dE; 
	float Cs;      /* mm */
	float Ain;     /* mrad : Illumination Angle */
	long  flagWin; /* Windowing */ 
	float CutLow;  /* Windowing: CutLow  A-1 */
	float CutHigh; /* Windowing: CutHigh A-1 */

	float I0;      /* Intensity */
	float Isignal; /* Intensity of signal */

	float ratioOfAmpToPhase; /* The ratio of amp to phase */

	float Inoise;  /* Intensity of noise : Isignal*/
	long  flagWhiteNoise;
	float WhiteNoise;  /* Affected by MTF(R) */

	long  flagWhiteNoiseRaising; 	
	float WhiteNoiseRaising; /* WhiteNoise Raising depending upon R */

	long  flagMaxWhiteNoise; 	
	float MaxWhiteNoise; /* max White Noise*/

	long  flagNdependentWhiteNoise; 	
	float NdependentWhiteNoise; /* max White Noise*/

	float Inoise2; /* Intensity of noise */
	long  flagWhiteNoise2;
	float WhiteNoise2; /* Not Affected by MTF(R)*/

	int   flagAstigmatism;
	float defocus2D[2];      /* A : Normally [0]: Max [1]: Min */
	float defocus0axis;      /* radian : angle of the defocus2D[0]-axis */

	long mode;
	
	long  flagMagnification;	
	float Magnification;

	/* MTF(R): Modulation Transfer Function */ 
	ctfInfoMTFMode MTFMode;
	float BofMTF;  /* Exponential: exp(-B R)   */
	float BofMTF2; /* Lorentzian : 1/(B*B+R*R) */	
	float WeightOfSecondTermForMTF; /* 0 <-> 1 */
	/*for PolynomialExpNoise*//*d = degree*/
	float BofMTFd2;
	float BofMTFd3;
	float BofMTFd4;
	float BofMTFd5;
	float BofMTFd6;

	/* Molecular Envelope: Scattering Factor */
	/* For Gaussian */
	float MolecEnv;                   /* A : */
	/* For Table */
	long  flagMolecEnvTable;
	molecularEnvelope MolecEnvTable;
	/* For Lorentzian */
	long flagElastic;
	float Elastic;
	float ElasticShift;
	float ElasticWidth;
	float ElasticRing;
	float ElasticRingPosition;
	float ElasticRingWidth;

	/* Stage Vibration */
	long  flagVibration;
	long  VibrationMode;
	float BofVibration;

	/* Aliasing and Sampling */
	long flagAliasing;
	float NyquistFrequency;
	long flagSampling; 

	/* Inelastic Signal */
	/* For Gaussian */
	long flagWithInElastic;
	float InElasticGaussian;

	/* For Table */
	long flagWithInElasticTable;
	molecularEnvelope InElasticEnvTable;	

	/* Lorentzian */	
	long flagInElastic;
	float InElastic;
	float InElasticShift;
	float InElasticWidth;
	float InElasticRing;
	float InElasticRingPosition;
	float InElasticRingWidth;

	/* Phase Plate */
	long flagAdditionalPhase;
	float AdditionalPhase; // [radian] 
} ctfInfo;

/* struct end */


#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void ctfInfoSendByPVM(ctfInfo* info, int tid, long mode);
extern void ctfInfoRecieveByPVM(ctfInfo* info, int tid, long mode);
extern float ctfSignalFunction(ctfInfo* info, float R, long mode);
extern float ctfNoiseFunction(ctfInfo* info, float R, long mode);
extern float ctfNoise2Function(ctfInfo* info, float R, long mode);
extern float ctfSignalPowerFunction(ctfInfo* info, float R, long mode);
extern float ctfNoisePowerFunction(ctfInfo* info, float R, long mode);
extern float ctfNoise2PowerFunction(ctfInfo* info, float R, long mode);
extern float ctfScatteringFunction(ctfInfo* info, float R, long mode);
extern float ctfMolecularEnvelopeFunction(ctfInfo* info, float R, long mode);
extern float ctfMolecularEnvelopeInElasticFunction(ctfInfo* info, float R, long mode);
extern float ctfVibrationFunction(ctfInfo* info, float R, long mode);
extern float ctfFunction(ctfInfo* info, float R, long mode);
extern float ctfFunctionSampling(float R, float Nyquist, long mode);
extern void  ctfFunctionPVMStart(ctfInfo* info, float R, int tid, long mode);
extern float ctfFunctionPVMEnd(ctfInfo* info, float R, int tid, long mode);
extern void  ctfFunctionPVMServer();
extern float ctfEnvelopFunction(ctfInfo* info, float R, long mode);
extern float ctfMTFFunction(ctfInfo* info, float R, long mode);
extern float ctfFunction2D(ctfInfo* info, float X, float Y, long mode);
extern float wavelengthOfElectron(float E);
extern float defocusDeterminationFromThonRing(ctfInfo* info, float R, long n, long mode);
extern void ctfWeightForCorrectionUsage(FILE* fpt);
extern float ctfWeightForCorrection2D(ctfInfo* info, float X, float Y, long mode);
extern float ctfWeightForCorrection(ctfInfo* info, float R, long mode);
extern void lmolecularEnvelopeFileRead(FILE* fpt, molecularEnvelope* mol, int mode);
extern void lmolecularEnvelopeFileWrite(FILE* fpt, molecularEnvelope* mol, int mode);
extern void lmolecularEnvelopeResampling(molecularEnvelope* dst, molecularEnvelope* src, float dR, float RMax, int mode);
extern float lmolecularEnvelopeDataGet(molecularEnvelope* src, float R, int mode);
extern void ctfInfoRead(FILE* fpt, ctfInfo* ctf, char* pre, int mode);
extern void ctfInfoWrite(FILE* fpt, ctfInfo ctf, char* pre, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif
