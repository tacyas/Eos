#ifndef EOS_BAYES_H
#define EOS_BAYES_H


typedef enum eosBayesDistributionRefinementMode{
	 eosBayesDistributionRefinementModeGaussian=0,
	 eosBayesDistributionRefimentModelinear=1,
	 eosBayesDistributionRefinementModeConstant=2
} eosBayesDistributionRefinementMode;

typedef struct eosBayesDistribution {
  //char* name;
  float min;
  float max;
  float delta;
  int   n;
  float* value;
  float* prob;
  float valueofmaxposterior;
  float probofmaxposterior;
  int iofmaxposterior;
  int resetflag;
  int rangechangeflag;
  float percentageofrange;
  int nofpartitions;
  int maxposteriorflag;
  int constantflag;
  eosBayesDistributionRefinementMode refmode;
} eosBayesDistribution;

 
typedef struct eosBayes {
	int numDistribution;
	eosBayesDistribution* prior;
	eosBayesDistribution* posterior;

	int numLikelihood;
	eosBayesDistribution* likelihood;
} eosBayes;


typedef enum eosBayesDistributionInfoMode {
	 eosBayesDistributionInfoModeGaussian=0,
	 eosBayesDistributionInfoModeConstant=1
} eosBayesDistributionInfoMode;

typedef struct eosBayesDistributionInfo {
  float min;
  float max;
  float delta;
  eosBayesDistributionInfoMode mode;
  // For Gaussian
  float mean;
  float sigma;
  float constant;
} eosBayesDistributionInfo;


/* eosBayesInit.c */
// Initialization of eosBays
extern void leosBayesInit(eosBayes* d, int numDistribution, int numLikelihood, int mode);

/*eosBayesCondition.c*/
extern void eosBayesCondition(FILE* fptIn, eosBayes* d, eosBayesDistributionInfo* llinfo, int mode);
extern void eosBayesRefinementCondition(FILE* fptIn, eosBayes* d, eosBayesDistributionInfo* llinfo, int n, int mode);
extern void eosBayesGettopthreepoint(eosBayesDistribution* d, float* value, float* prob);
extern void eosBayesLiniearinterpolationofTopthreepoint(eosBayesDistribution* d, float* value, float* prob);

// Initialize Each distribution of eosBayesDistributions
extern void eosBayesDistributionInit(eosBayesDistribution* d,eosBayesDistributionInfo* info, int mode);


// Initialize probe of Each distribution of eosBayesDistriubutions
extern void eosBayesDistributionInitialProbabilitySet(eosBayesDistribution* d, eosBayesDistributionInfo* info, int mode);
extern void eosBayesProbabilityReset(FILE* fptIn,eosBayes* d, int n, int mode);
extern void eosBayesProbabilitysetLinear(eosBayesDistribution* d, float a, float b);
extern void eosBayesProbabilityRangeChange(eosBayes* d, int mode);

/* eosBayesEstimation.c */
extern void eosBayesEstimation(eosBayes* d, int mode);
extern void eosBayesPosteriortoPrior(eosBayes* d, int mode);
extern void eosBayesloop(eosBayesDistribution* d, int* L, int numDist, int length);

/* eosBayesWrite.c */
extern void eosBayesDistribututionWrite(FILE* fpt, eosBayesDistribution* d, int mode);
extern void eosBayesPriorWrite(eosBayes* d, int mode);
extern void eosBayesPosteriorWrite(eosBayes* d, int mode);
extern void eosBayesLikelihoodWrite(eosBayes* d, int mode);
extern void eosBayesWrite(FILE* fpt, eosBayes* d, int mode);
// FileFormat
// 0 min0 max0 delta0 n0 out.prior[0].prob[0] ...... prob[n-1]
// 1 min1 max1 delta1 n1 out.prior[1].prob[0] ...... prob[n-1]

extern void DistributionChangeCheck(eosBayes* d, int count, int mode);
extern void LikelihoodChangeCheck(eosBayes* d, int count, int mode);
//FileFoemat
//min max delta n
//value prob
//value prob
//.........


/* eosBayesRead.c */
extern void eosBayesDistributioncheck(FILE* fpt, eosBayes* d, int mode);
extern void eosBayesDistributionRead(FILE* fpt, eosBayesDistribution* d, int mode);
extern void eosBayesPriorRead(FILE* fpt, eosBayes* d, int mode);
extern void eosBayesPosteriorRead(FILE* fpt, eosBayes* d, int mode);
extern void eosBayesLikelihoodRead(FILE* fpt, eosBayes* d, int mode);
extern void eosBayesRead(FILE* fpt, eosBayes* d, int mode);

/* eosBayesParameterOfMaxPosterior.c*/
extern void eosBayesParameterOfMaxPosteriorGet(eosBayesDistribution* d, int nunDistribution, int mode);
extern void leosBayesParameterOfMaxPosteriorGet(eosBayesDistribution* d, int mode);

extern void eosBayesFree(eosBayes* d);
extern void eosBayesMaxposteriorflagSet(eosBayes* d, int Distnum);
extern void eosBayesRangeChangeflagSet(eosBayes*d, int Distnum, float percentageofrange, int nofpartitions);
#endif /* EOS_BAYES_H */
