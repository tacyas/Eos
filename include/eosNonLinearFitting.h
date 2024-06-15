/*
# eosNonLinearFitting.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosNonLinearFitting.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef EOS_NON_LINEAR_FITTING_H
#define EOS_NON_LINEAR_FITTING_H

#include <stdio.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlinear.h>

/* constant begin */
typedef enum eosNonLinearFittingMode {
    eosNonLinearFittingModeSingleExpDecay = 0
}  eosNonLinearFittingMode;

/* constant end */

/* struct begin */
typedef struct eosNonLinearFittingParams {
    /* Input */    
    size_t maxIter;
    double xtol;
    double gtol;
    double ftol;

    //
    char** message;

    /* Output */
    size_t numOfp;
    char* method;
    char* iterationStopReason;
    int iter;
    double functionEvaluations;
    double JacobianEvaluations;
    double initialChisq;
    double finalChisq;
    char*  reason;
    char*  status;
    double c;
    double degreeOfFreedom;
    double chisq_per_degreeOfFreedom;

    /* exp */
    /* y = A* exp (K* x) + B */
    // In
    double Ainit;
    double Kinit;
    double Binit;
    double High;
    double Low;

    // Out
    double A;
    double sigA;
    double K;
    double sigK;
    double B;
    double sigB;
} eosNonLinearFittingParams;

/*
summary from method 'trust-region/levenberg-marquardt'
number of iterations: 11
function evaluations: 16
Jacobian evaluations: 12
reason for stopping: small gradient
initial |f(x)| = 88.444756
final   |f(x)| = 10.477801
chisq/dof = 1.1318
A      = 4.79653 +/- 0.18704
lambda = 1.43937 +/- 0.07390
b      = 1.00368 +/- 0.03473
status = success

*/

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern int                            
eosNonLinearFitting(eosNonLinearFittingParams* out, double* t, double* y, double* sigy, int n, int mode);


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
