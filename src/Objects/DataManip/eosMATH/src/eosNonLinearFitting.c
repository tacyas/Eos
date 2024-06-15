/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosNonLinearFitting ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosNonLinearFitting 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosNonLinearFitting ver%I%; Date:%D% %Z%";
#define DEBUG
#include "genUtil.h"
#include "Vector.h"
#include "./eosNonLinearFitting.h"

struct data {
    size_t n;
    double* t;
    double* y;
};

static int
_expb_f(const gsl_vector * x, void *data, gsl_vector * f)
{
    size_t n = ((struct data *)data)->n;
    double* t = ((struct data *)data)->t;
    double* y = ((struct data *)data)->y;
    double Yi;

    double A = gsl_vector_get (x, 0);
    double K = gsl_vector_get (x, 1);
    double B = gsl_vector_get (x, 2);

    size_t i;

    for (i = 0; i < n; i++) {
        /* Model Yi = A * exp(-K * t_i) + B */
        Yi = A * exp (- K * t[i]) + B;
        gsl_vector_set (f, i, Yi - y[i]); // f: difference
        //DEBUGPRINT5("%zu %f %f %f %f\n", i, t[i], y[i], Yi, Yi-y[i]);
    }

    return GSL_SUCCESS;
}

static int
_expb_df(const gsl_vector * x, void *data, gsl_matrix * J)
{
  size_t n = ((struct data *)data)->n;
  double *t = ((struct data *)data)->t;

  double A = gsl_vector_get (x, 0);
  double K = gsl_vector_get (x, 1);
  double B = gsl_vector_get (x, 2);

  size_t i;

  for (i = 0; i < n; i++) {
      /* Jacobian matrix J(i,j) = dfi / dxj, */
      /* where fi = (Yi - yi)/sigma[i],      */
      /*       Yi = A * exp(-lambda * t_i) + b  */
      /* and the xj are the parameters (A,K,B) */
      double e = exp( - K * t[i]);
      gsl_matrix_set (J, i, 0, e);              // df/dA
      gsl_matrix_set (J, i, 1, - t[i] * A * e); // df/dK
      gsl_matrix_set (J, i, 2, 1.0);            // df/dB
      //DEBUGPRINT5("%zu %f %f %f %f\n", i, t[i], e,  - t[i] * A * e, 1.0);
    }

  return GSL_SUCCESS;
}

static void
_callback(const size_t iter, void *params,
         const gsl_multifit_nlinear_workspace *w)
{
  gsl_vector *f = gsl_multifit_nlinear_residual(w);
  gsl_vector *x = gsl_multifit_nlinear_position(w);
  double rcond;
  char stmp[1024];

  /* compute reciprocal condition number of J(x) */
  gsl_multifit_nlinear_rcond(&rcond, w);
  //
  eosNonLinearFittingParams* param;
  param = (eosNonLinearFittingParams*)params;

  if(0!=rcond) { 
    sprintf(stmp, "iter %2zu: A = %.4f, K = %.4f, B = %.4f, cond(J) = %8.4f, |f(x)| = %.4f",
          iter, 
          gsl_vector_get(x, 0),
          gsl_vector_get(x, 1),
          gsl_vector_get(x, 2),
          1.0 / rcond,
          gsl_blas_dnrm2(f));

    DEBUGPRINT6("iter %2zu: A = %.4f, K = %.4f, B = %.4f, cond(J) = %8.4f, |f(x)| = %.4f\n",
          iter,
          gsl_vector_get(x, 0),
          gsl_vector_get(x, 1),
          gsl_vector_get(x, 2),
          1.0 / rcond,
          gsl_blas_dnrm2(f));
  } else {
    sprintf(stmp, "iter %2zu: A = %.4f, K = %.4f, B = %.4f, cond(J) = %8.4f, |f(x)| = %.4f",
          iter, 
          gsl_vector_get(x, 0),
          gsl_vector_get(x, 1),
          gsl_vector_get(x, 2),
          0.0,
          gsl_blas_dnrm2(f));

    DEBUGPRINT6("iter %2zu: A = %.4f, K = %.4f, B = %.4f, cond(J) = %8.4f, |f(x)| = %.4f\n",
          iter,
          gsl_vector_get(x, 0),
          gsl_vector_get(x, 1),
          gsl_vector_get(x, 2),
          0.0,
          gsl_blas_dnrm2(f));
  } 

  param->message[iter] = strdup(stmp);
}


int
eosNonLinearFitting(eosNonLinearFittingParams* out, double* t, double* y, double* sigy, int n, int mode)
{
    // data 
    double* weights;
    struct data d;
    d.n = n;
    d.t = (double*)malloc(sizeof(double)*n);
    d.y = (double*)malloc(sizeof(double)*n);
    weights = (double*)malloc(sizeof(double)*n);
    gsl_vector_view wts = gsl_vector_view_array(weights, n);

    double* x_init;
    size_t maxIter = out->maxIter;
    double xtol = out->xtol;
    double gtol = out->gtol;
    double ftol = out->ftol;


    char s[1024];
    gsl_vector *f;
    gsl_matrix *J;
    int status, info;
    size_t i;

    for(i=0; i<n; i++) {
        d.t[i] = t[i];
        d.y[i] = y[i];
        //weights[i] = sigy[i];
        weights[i] = 1.0;
    }

    //
    const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
    gsl_multifit_nlinear_workspace *w;
    gsl_multifit_nlinear_fdf fdf;
    gsl_multifit_nlinear_parameters fdf_params =  gsl_multifit_nlinear_default_parameters();

    // depending upon  n, p
    gsl_matrix* covar;
    gsl_vector_view x;

    // p
    size_t p;

    // function 
    out->message = (char**)malloc(sizeof(char*)*(maxIter+1));
    for(i=0; i<=maxIter; i++) {
        out->message[i] = NULL;
    }
    switch(mode) {
        case eosNonLinearFittingModeSingleExpDecay: {
            out->numOfp = p = 3;
            fdf.f   = _expb_f;
            fdf.df  = _expb_df;
            fdf.fvv = NULL; // Not using geodesic acceleration 
            fdf.n = n;
            fdf.p = p;
            fdf.params = &d;
            x_init = (double*)malloc(sizeof(double)*p);
            x_init[0] = out->Ainit;
            x_init[1] = out->Kinit;
            x_init[2] = out->Binit;

            break;
        }
        default: {
            fprintf(stderr, "Not supported mode: %d in eosNonLinearFitting\n", mode);
            exit(EXIT_FAILURE);
            break;
        }
    }
    covar = gsl_matrix_alloc (p, p);
    x = gsl_vector_view_array (x_init, p);

    /* allocate workspace with default parameters */
    w = gsl_multifit_nlinear_alloc(T, &fdf_params, n, p);

    /* initialize solver with starting point and weights */
    gsl_multifit_nlinear_winit (&x.vector, &wts.vector, &fdf, w);

    /* compute initial cost function */
    f = gsl_multifit_nlinear_residual(w);
    gsl_blas_ddot(f, f, &out->initialChisq); // 

    /* solve the system with a maximum of 100 iterations */
    DEBUGPRINT("Start  gsl_multifit_nlinear_driver\n");
    status = gsl_multifit_nlinear_driver(maxIter, xtol, gtol, ftol,
                                       _callback, out, &info, w);

    /* compute covariance of best fit parameters */
    DEBUGPRINT("Start  gsl_multifit_nlinear_jac\n");
    J = gsl_multifit_nlinear_jac(w);
    gsl_multifit_nlinear_covar (J, 0.0, covar);

    /* compute final cost */
    gsl_blas_ddot(f, f, &out->finalChisq);   //

    //
    sprintf(s, "%s/%s", gsl_multifit_nlinear_name(w), gsl_multifit_nlinear_trs_name(w));
    out->method = strdup(s);
    out->iter = gsl_multifit_nlinear_niter(w);
    out->functionEvaluations = fdf.nevalf;
    out->JacobianEvaluations = fdf.nevaldf;
    out->reason = strdup((info == 1) ? "small step size" : "small gradient");
    out->status = strdup(gsl_strerror(status));
    out->degreeOfFreedom = n-p; 
    out->c = GSL_MAX_DBL(1,sqrt(out->finalChisq/out->degreeOfFreedom));
    out->chisq_per_degreeOfFreedom = out->finalChisq/out->degreeOfFreedom;

    switch(mode) {
        case eosNonLinearFittingModeSingleExpDecay: {
            out->A = gsl_vector_get(w->x, 0);
            out->sigA = sqrt(gsl_matrix_get(covar, 0, 0));
            out->K = gsl_vector_get(w->x, 1);
            out->sigK = sqrt(gsl_matrix_get(covar, 1, 1));
            out->B = gsl_vector_get(w->x, 2);
            out->sigB = sqrt(gsl_matrix_get(covar, 2, 2));
            break;
        }
        default: {
            fprintf(stderr, "Not supported mode: %d in eosNonLinearFitting\n", mode);
            exit(EXIT_FAILURE);
            break;
        }
    }

    gsl_multifit_nlinear_free (w);
    gsl_matrix_free (covar);

    return status;
}


