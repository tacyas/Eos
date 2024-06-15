/*
# ctfDeterminationByBayes : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : ctfDeterminationByBayes
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "eosBayes.h"
#include "ctfInfo.h"
#include "ctffuncforbayes.h"


#define DEBUG
#include "genUtil.h"
#include "ctfDeterminationByBayes.h"
#include "eosString.h"

/*
Example:
typedef struct lctfDeterminationByBayesInfo {
	float a;
	int   b;
} lctfDeterminationByBayesInfo;

typedef enum lctfDeterminationByBayesMode {
	a=0,
	b=1
} lctfDeterminationByBayesMode;
*/

void DefocusEstimationLoop(ctfDeterminationByBayesInfo info, eosBayes* out, ctfInfo* ctfinfo, ctfforbayes* ctf, intensityforbayes* intensity, defocuslikelihoodforbayes* likelihood, int count, int mode);

int
main(int argc, char* argv[]) 
{
  
  int i;

  ctfDeterminationByBayesInfo info;
  ctfInfo ctfinfo;
  eosBayesDistributionInfo llinfo;
  
  eosBayes out;

  ctfforbayes ctf;
  intensityforbayes intensity;
  defocuslikelihoodforbayes likelihood;

  float Rmax;
  float Rmin;
  float Rintermediate;
  float Rfirstpeak;


  init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);

  DEBUGPRINT("Program Start\n");
  DEBUGPRINT("local binary:MTF plus\n");

  ctfinfo.mode = 33;

  /*For Prior*/
  leosBayesInit(&out, info.numDistribution, info.numLikelihood, info.mode);
  eosBayesCondition(info.fptIn, &out, &llinfo, 0);
  eosBayesPriorWrite(&out,0);
  DistributionChangeCheck(&out, 0, 0);


  /*For CTF and intensity*/
  ctfforbayesInit(info.fptIn2,&ctf,0);
  intensityforbayesInit(&intensity,ctf.n,info.MTFmode,info.Ainmode,0);
  spatialfrequencyRead(info.fptIn2,&ctf,info.rmax,info.rmin,0);
  ctfInfoRead(info.fptIn3,&ctfinfo,"",0);
  DEBUGPRINT6("kV:%f  Cs:%f  Ain:%f Cc:%f MTF:%f ctfMode:%ld\n",ctfinfo.kV,ctfinfo.Cs,ctfinfo.Ain,ctfinfo.Cc,ctfinfo.BofMTF,ctfinfo.mode);


  /*ctfInfoflagcheck*/
  DEBUGPRINT2("flagAliasing:%ld flagSampling:%ld\n",ctfinfo.flagAliasing,ctfinfo.flagSampling);
  DEBUGPRINT1("NyquistFrequency:%f\n",ctfinfo.NyquistFrequency);

  ctfinfo.flagMolecEnvTable = 0;
  DEBUGPRINT1("flagMolecEnvTable:%ld\n",ctfinfo.flagMolecEnvTable);
  ctfinfo.flagElastic = 0;
  DEBUGPRINT1("flagElastic:%ld\n",ctfinfo.flagElastic);

  ctfinfo.flagWithInElasticTable = 0;
  DEBUGPRINT1("flagWithInElasticEnvTable:%ld\n",ctfinfo.flagWithInElasticTable);
  ctfinfo.flagInElastic = 0;
  DEBUGPRINT1("flagInElastic:%ld\n",ctfinfo.flagInElastic);
  ctfinfo.flagWithInElastic = 0;
  DEBUGPRINT1("flagWithInElastic:%ld\n",ctfinfo.flagWithInElastic);

  ctfinfo.flagVibration = 0;
  DEBUGPRINT1("flagVibration:%ld\n",ctfinfo.flagVibration);
  ctfinfo.VibrationMode = 0;
  DEBUGPRINT1("VibrationMode:%ld\n",ctfinfo.VibrationMode);
 
  ctfinfo.Magnification = 0;
  DEBUGPRINT1("Magnification:%f\n",ctfinfo.Magnification);
  ctfinfo.flagMagnification = 0;
  DEBUGPRINT1("flagMagnification:%ld\n",ctfinfo.flagMagnification);


  DEBUGPRINT1("flagIn4:%ld\n",info.flagIn4);

  Rmax = ctf.rmax;
  Rmin = ctf.rmin;
  Rintermediate = info.rintermediate;
  Rfirstpeak = info.rfirstpeak;

  /*global carse search B*/
  DEBUGPRINT("carse search start\n");
  ctf.rmax = Rmax;
  ctf.rmin = Rintermediate;
  DEBUGPRINT2("set R range:%f~%f\n",ctf.rmin,ctf.rmax);
  DefocusEstimationLoop(info,&out,&ctfinfo,&ctf,&intensity,&likelihood,0,0);
  DEBUGPRINT("carse search finish\n");
  ctfforbayescheckIntensityOfMaxPosterior(ctf,out.posterior,out.numDistribution,&ctfinfo,intensity.MTFmode,intensity.Ainmode,1,1);

  /*MTF serch start\n*/
  DEBUGPRINT("MTF,B search start\n");
  ctf.rmax = Rmax;
  ctf.rmin = Rintermediate;
  DEBUGPRINT2("set R range:%f~%f\n",ctf.rmin,ctf.rmax);
  DEBUGPRINT("----maxflagcheck----\n");
  #ifdef DEBUG
  for(i=0;i<out.numDistribution;i++){
	printf("dist%d:%d\n",i,(out.posterior[i].maxposteriorflag));
  }
  #endif

  DEBUGPRINT("set canstantflag of Ain");
  out.posterior[0].constantflag = 1;
  out.posterior[1].constantflag = 1;
  out.posterior[3].constantflag = 1;
  out.posterior[5].constantflag = 1;

  DEBUGPRINT("set resetflag of \n");
  out.prior[4].resetflag = 1;
  eosBayesProbabilityReset(info.fptIn,&out,10,0);

  DEBUGPRINT("set rangechangeflag of B\n");
  eosBayesRangeChangeflagSet(&out,2,0.95,100);
  eosBayesProbabilityRangeChange(&out,0);

  DistributionChangeCheck(&out, 1, 0);

  DefocusEstimationLoop(info,&out,&ctfinfo,&ctf,&intensity,&likelihood,1,1);
  DEBUGPRINT("MTF,B search finish\n");
  
  DEBUGPRINT("----maxflagcheck----\n");
  #ifdef DEBUG
  for(i=0;i<out.numDistribution;i++){
	printf("dist%d:%d\n",i,(out.posterior[i].maxposteriorflag));
  }
  #endif

  ctfforbayescheckIntensityOfMaxPosterior(ctf,out.posterior,out.numDistribution,&ctfinfo,intensity.MTFmode,intensity.Ainmode,1,1);


  /*df,A B serch*/
  DEBUGPRINT("df, A, B search start\n");
  ctf.rmax = Rintermediate;
  ctf.rmin = Rmin;
  DEBUGPRINT2("set R range:%f~%f\n",ctf.rmin,ctf.rmax);

  DEBUGPRINT("set maxposteriorflag of MTF,B\n");
  eosBayesMaxposteriorflagSet(&out,4);

  DEBUGPRINT("set canstantflag of Ain");
  out.posterior[3].constantflag = 1;
  out.posterior[5].constantflag = 1;

  DEBUGPRINT("set resetflag of df,k\n");
  out.prior[0].resetflag = 1;
  out.prior[1].resetflag = 1;
  eosBayesProbabilityReset(info.fptIn,&out,1,0);

  DEBUGPRINT("set rangechangeflag of B\n");
  eosBayesRangeChangeflagSet(&out,2,0.95,20);
  eosBayesProbabilityRangeChange(&out,0);


  DistributionChangeCheck(&out, 4, 0);
  DEBUGPRINT("----maxflagcheck----\n");
  #ifdef DEBUG
  for(i=0;i<out.numDistribution;i++){
	printf("dist%d:%d\n",i,(out.posterior[i].maxposteriorflag));
  }
  #endif

  DefocusEstimationLoop(info,&out,&ctfinfo,&ctf,&intensity,&likelihood,4,1);
  DEBUGPRINT("A,B,df search finish\n");
  ctfforbayescheckIntensityOfMaxPosterior(ctf,out.posterior,out.numDistribution,&ctfinfo,intensity.MTFmode,intensity.Ainmode,1,1);


  /*df,A, B 2 serch*/
  DEBUGPRINT("df, A, B search 2 start\n");
  ctf.rmax = Rintermediate;
  ctf.rmin = Rmin;
  DEBUGPRINT2("set R range:%f~%f\n",ctf.rmin,ctf.rmax);

  DEBUGPRINT("set maxposteriorflag of MTF,B\n");
  eosBayesMaxposteriorflagSet(&out,4);

  DEBUGPRINT("set canstantflag of Ain");
  out.posterior[3].constantflag = 1;
  out.posterior[5].constantflag = 1;

  DEBUGPRINT("set resetflag of df,k\n");
  out.prior[0].resetflag = 1;
  eosBayesProbabilityReset(info.fptIn,&out,5,0);


  DEBUGPRINT("set rangechangeflag of A\n");
  eosBayesRangeChangeflagSet(&out,1,0.95,20);
  eosBayesRangeChangeflagSet(&out,2,0.95,20);
  eosBayesProbabilityRangeChange(&out,0);

  DistributionChangeCheck(&out, 5, 0);
  DEBUGPRINT("----maxflagcheck----\n");
  #ifdef DEBUG
  for(i=0;i<out.numDistribution;i++){
	printf("dist%d:%d\n",i,(out.posterior[i].maxposteriorflag));
	printf("rangechange%d:%d\n",i,(out.posterior[i].rangechangeflag));

  }
  #endif

  DefocusEstimationLoop(info,&out,&ctfinfo,&ctf,&intensity,&likelihood,5,1);
  DEBUGPRINT("A,df,k search finish\n");
  ctfforbayescheckIntensityOfMaxPosterior(ctf,out.posterior,out.numDistribution,&ctfinfo,intensity.MTFmode,intensity.Ainmode,1,1);


  /*Defocus ref*/
  DEBUGPRINT("defocus refinement start\n");
  ctf.rmax = Rmax;
  ctf.rmin = Rfirstpeak;
  DEBUGPRINT2("set R range:%f~%f\n",ctf.rmin,ctf.rmax);

  DEBUGPRINT("set maxposteriorflag of defocus,A,B,MTF\n");
  out.posterior[0].maxposteriorflag = 0;
  out.posterior[1].maxposteriorflag = 0;
  out.posterior[3].maxposteriorflag = 0;
  out.posterior[4].maxposteriorflag = 0;
  out.posterior[5].maxposteriorflag = 0;
  // eosBayesMaxposteriorflagSet(&out,4);

  DEBUGPRINT("set canstantflag of Ain");
  out.posterior[3].constantflag = 0;
  out.posterior[5].constantflag = 0;

  DEBUGPRINT("set resetflag of df,k\n");
  out.prior[3].resetflag = 1;
  out.prior[5].resetflag = 1;
  eosBayesProbabilityReset(info.fptIn,&out,1,0);

  DEBUGPRINT("set rangechangeflag of A\n");
  eosBayesRangeChangeflagSet(&out,0,0.70,10);
  eosBayesRangeChangeflagSet(&out,1,0.95,20);
  eosBayesRangeChangeflagSet(&out,2,0.95,20);
  eosBayesRangeChangeflagSet(&out,4,0.40,5);
  eosBayesProbabilityRangeChange(&out,0);

  DistributionChangeCheck(&out, 6, 0);
  defocusLikelihoodInit(&likelihood,&out,1);

  DefocusEstimationLoop(info,&out,&ctfinfo,&ctf,&intensity,&likelihood,6,1);
  DEBUGPRINT("defocus refinement finish\n");
  ctfforbayescheckIntensityOfMaxPosterior(ctf,out.posterior,out.numDistribution,&ctfinfo,intensity.MTFmode,intensity.Ainmode,1,1);

  eosBayesPosteriorWrite(&out,0);
  
  ctfforbayesFree(&ctf,&intensity,&likelihood,out.numLikelihood);

  eosBayesFree(&out);

  exit(EXIT_SUCCESS);
}

void DefocusEstimationLoop(ctfDeterminationByBayesInfo info, eosBayes* out, ctfInfo* ctfinfo, ctfforbayes* ctf, intensityforbayes* intensity, defocuslikelihoodforbayes* likelihood, int count,int mode){
  int i;

  defocusLikelihoodInit(likelihood,out,mode);
  DEBUGPRINT("In DefocusEstimationLoop\n");
  for(i=0;i<info.flagIn4;i++){

	intensityRead(info.In4[i],intensity,i,0);
	DEBUGPRINT("ctf start\n");
	ctfFunctionforbayes(ctf,intensity,out,ctfinfo,likelihood,count,1);

	DEBUGPRINT("estimate start\n");
	eosBayesEstimation(out,0);
	DistributionChangeCheck(out,count,1);
  
	DEBUGPRINT("change start\n");
	eosBayesPosteriortoPrior(out,0);

  }

}

void
additionalUsage()
{
  fprintf(stderr, "----- Additional Usage -----\n");
}

