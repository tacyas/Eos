/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosMathStatistics ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosMathStatistics 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosMathStatistics ver%I%; Date:%D% %Z%";

#include "../inc/eosMath.h"
#include "genUtil.h"
#include "Memory.h"


void
eosMathSorting(double* v, int n)
{
  int i, j;
  double tmp;
  for(i=0; i<n-1; i++) {
    for(j=0; j<n-1; j++) {
      if(v[j]>v[j+1]) {
        tmp = v[j];
        v[j] = v[j+1];
        v[j+1] = tmp;
      }
    }
  }
}

double
eosMathMedian(double* v, int n)
{
  int i;
  double* tmp;
  double med;
  tmp = memoryAllocate(sizeof(double)*n, "in eosMathMedian");
  for(i=0; i<n; i++) {
    tmp[i] = v[i];
  }
  eosMathSorting(tmp, n);
  if(n%2) {
    med = (tmp[n/2-1]+tmp[n/2])/2.0;
  } else {
    med = tmp[n/2]; 
  }

  free(tmp);
  return med;
}


double
eosMathAverage(double* v, int n)
{
  int i;
  double sum;
  sum = 0;
  for(i=0; i<n; i++) {
    sum += v[i];
  }
  return sum/n;  
}

double
eosMathStdDev(double* v, double mean, int n)
{
  int i;
  double sum;
  sum = 0;
  for(i=0; i<n; i++) {
    sum += SQR(v[i]-mean);
  }
  if(0<sum) {
    return sqrt(sum/n);
  } else {
    return 0;
  }
}


double
eosMathMedianAbsoluteDeviation(double* v, double med, int n)
{
  int i;
  double mad;
  double* tmp;

  tmp = (double*)memoryAllocate(sizeof(double)*n, "in MAD");

  for(i=0; i<n; i++) {
    tmp[i] = fabs(v[i]-med);
  } 

  mad = eosMathMedian(tmp, n);

  free(tmp);

  return mad;
}


double
eosMathMedianAbsoluteDeviationNormal(double* v, double med, int n)
{
  return eosMathMedianAbsoluteDeviation(v, med, n)/0.675;
}

double
eosMathInterquntileRange(double* v, int n)
{
  int i;
  double* tmp;
  double IQ1, IQ3;
  
  tmp = (double*)memoryAllocate(sizeof(double)*n, "in IRQ");
  for(i=0; i<n; i++) {
    tmp[i] = v[i];
  }
  eosMathSorting(tmp, n);

  if(n%4) {
    IQ1 = (tmp[  n/4] + tmp[  n/4+1])/2.0;
    IQ3 = (tmp[3*n/4] + tmp[3*n/4+1])/2.0;
  } else {
    IQ1 = tmp[  n/4];
    IQ3 = tmp[3*n/4];
  }
  
  free(tmp);
  return fabs(IQ3-IQ1);
}


double
eosMathInterquntileRangeNormal(double* v, int n)
{
  return eosMathInterquntileRange(v, n)/1.349; 
}
double
eosMathWeightedAverage(double* v, int n)
{
  int i;
  double avg;
  double sum;
  double weight;
  double sd;
  double w;
  double ss;
  double avg2;

  avg = eosMathAverage(v, n);
  sd = eosMathStdDev(v, avg, n);

  sum = 0;
  weight = 0;
  if(0<sd) {
    ss = 1.0/2/SQR(sd);
  } else {
    ss = 1;
  }
  for(i=0; i<n; i++) {
    w = exp(-SQR(v[i]-avg)*ss);
    weight += w;
    sum += w*v[i];
  }
  if(0<weight) {
    avg2 = sum/weight;
  } else {
    avg2 = avg;
  }
  return avg2;
}

double
eosMathTrimmedAverage(double* v, int n, double trim)
{

  int i;
  int nn;
  int iStart;
  double* tmp;
  double* tmp2;
  double avg;

  nn = (int)(n*(1-trim*2)+0.5);
  iStart = (int)(n*trim+0.5) ;

  tmp = memoryAllocate(sizeof(double)*n, "in eosMathMedian");
  tmp2 = memoryAllocate(sizeof(double)*nn, "in eosMathMedian");
  for(i=0; i<n; i++) {
    tmp[i] = v[i];
  }
  eosMathSorting(tmp, n);

  for(i=0; i<nn; i++) {
    tmp2[i] = tmp[i+iStart];
  }
  avg = eosMathAverage(tmp2, nn);

  free(tmp);
  free(tmp2);

  return avg;
}

double*
eosMathTrimming(double** trimmedV, int*nn,  double* v, int n, double trim)
{

  int i;
  int iStart;
  double* tmp;
  double* tmp2;
  double avg;

  *nn = (int)(n*(1-trim*2)+0.5);
  iStart = (int)(n*trim+0.5) ;

  tmp = memoryAllocate(sizeof(double)*n, "in eosMathMedian");
  tmp2 = memoryAllocate(sizeof(double)*(*nn), "in eosMathMedian");
  for(i=0; i<n; i++) {
    tmp[i] = v[i];
  }
  eosMathSorting(tmp, n);

  for(i=0; i<*nn; i++) {
    tmp2[i] = tmp[i+iStart];
  }
  free(tmp);

  if(trimmedV!=NULL) {
    *trimmedV = tmp2;
  } 

  return tmp2;
}


double
eosMathHodgesLehmannEstimator(double* v, int n)
{

  int i, j, k;
  int nn;
  double* tmp;
  double avg;

  nn = n*(n-1)/2;
  tmp = memoryAllocate(sizeof(double)*nn, "in eosMathMedian");

  k=0;
  for(i=0; i<n; i++) {
  for(j=1; j<n; j++) {
    tmp[k] = (v[i] + v[j])/2.0;
    k++;
  }
  }
  eosMathSorting(tmp, nn);

  if(nn%2) {
    avg = (tmp[nn/2-1]+tmp[nn/2])/2.0;
  } else {
    avg = tmp[nn/2]; 
  }

  free(tmp);
  return avg;
}


