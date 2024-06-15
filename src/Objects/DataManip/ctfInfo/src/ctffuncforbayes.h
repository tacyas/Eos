/*
# ctffuncforbayes.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : ctffuncforbayes.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#ifndef CTFFUNCFORBAYES_H 
#define CTFFUNCFORBAYES_H


/* constant begin */


/* constant end */

/* struct begin */

typedef struct ctfforbayes{
  int n;
  float* R;
  float rmax;
  float rmin;
  float* I;
  float* Ii;
} ctfforbayes;

typedef enum intensityforbayesMode{
  normal = 0,
  logarithm  = 1,
} intensityforbayesMode;


typedef struct intensityforbayes{
  float* normI;
  float* logI;
  float* normII;
  float* logII;

  int MTFmode;
  int Ainmode;
  
  intensityforbayesMode mode;

} intensityforbayes;


typedef enum xoflikelihoodforbayesMode{
  difference = 0,
  correlation = 1
} xoflikelihoodforbayesMode;

typedef enum widthoflikelihoodforbayesMode{
  mean = 0,
  median = 1
} widthoflikelihoodforbayesMode;

typedef enum defocuslikelihoodMode{
  lorentz = 0
} defocuslikelihoodMode;


typedef struct defocuslikelihoodforbayes{
  float** x;
  double* width;

  xoflikelihoodforbayesMode mode0;
  widthoflikelihoodforbayesMode mode1;
  defocuslikelihoodMode mode2;

} defocuslikelihoodforbayes;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */


/* prototype end */

/* prototype begin */
/*ctfforbayes.c*/
extern void ctfforbayesInit(FILE* fpt, ctfforbayes* ctf, int mode);
extern void intensityforbayesInit(intensityforbayes* intensity,int Inum, int MTFmode, int Ainmode, int mode);
extern void intensitySet(ctfforbayes* ctf, intensityforbayes* intensity, int mode);
extern void spatialfrequencyRead(FILE* fpt, ctfforbayes* ctf, float rmax, float rmin, int mode);
extern void intensityRead(char* filename, intensityforbayes* intensity, int count, int mode);

extern void ctfFunctionforbayes(ctfforbayes* ctf, intensityforbayes* intensity, eosBayes* d, ctfInfo* info, defocuslikelihoodforbayes* l, int count, int mode);
extern float ctfforbayesIntensityCalculation(float* parameter, float R, ctfInfo* info, int MTFmode, int Ainmode,  int mode);
extern void ctfforbayesFree(ctfforbayes* ctf, intensityforbayes* intensity, defocuslikelihoodforbayes* likedihood, int numLikelihood);


  /*defocuslikelihood.c*/
extern void defocusLikelihoodInit(defocuslikelihoodforbayes* l, eosBayes* d, int mode);
extern void ctfforbayesXofLikelihoodCalculation(defocuslikelihoodforbayes* l, ctfforbayes* ctf, eosBayes* d, int* L, int count, int mode);
extern void defocusLikelihood(defocuslikelihoodforbayes* l, ctfforbayes* ctf, eosBayes* d, int count, int mode);
extern void ctfforBayesDifferenceCalculation(defocuslikelihoodforbayes* l, ctfforbayes* ctf, eosBayesDistribution* d, int numLikelihood, int* L, int count, int mode);
extern void ctfforBayesMeanCalculation(defocuslikelihoodforbayes* l, eosBayesDistribution* d, int numLikelihood, int count, int mode);
extern void defocusLikelihoodCalculationLorentz(defocuslikelihoodforbayes* l, eosBayesDistribution* d, int numLikelihood, int count, int mode);

/*ctfforbayescheck.c*/
extern void ctfforbayescheckRvsValue(char* filename, float R,float value, int count);
extern void ctfforbayescheckdifference(char* filename, defocuslikelihoodforbayes* l, eosBayesDistribution* d, int numLikelihood, int count, int mode);
extern void ctfforbayescheckintensity(ctfforbayes ctf, eosBayesDistribution* d, int numLikelihood, int count, int mode);
extern void ctfforbayescheckIntensityOfMaxPosterior(ctfforbayes ctf, eosBayesDistribution* d, int numDistribution, ctfInfo* info, int MTFmode, int Ainmode, int Intensitymode, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* CTFFUNCFORBAYES_H */ 
