/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% leosPointPositionCorrection ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : leosPointPositionCorrection 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%leosPointPositionCorrection ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION

#undef DEBUG
#include "genUtil.h"
#include "../inc/eosPoint.h"
#include "./leosPointPositionCorrection.h"
#include "gsl/gsl_math.h"
#include "gsl/gsl_vector.h"
#include "gsl/gsl_matrix.h"
#include "gsl/gsl_permutation.h"
#include "gsl/gsl_blas.h"
#include "gsl/gsl_linalg.h"

int 
leosPointPositionCorrection(eosPoint* outP, eosPoint* inP, leosPointPositionCorrectionInfo* linfo, int mode)
{
    gsl_vector* r;
    gsl_vector* dr;
    gsl_vector* b; 
    gsl_vector* db; 
    gsl_matrix* A;
    gsl_matrix* AtA;
    gsl_permutation* p;
    int signum;
    gsl_matrix* AtAInv;
    gsl_matrix* AtAInvAt;
    int count = 0;    
    int i, j, k, l;
    eosPointCoord pc;

    linfo->m = linfo->n*(linfo->n - 1)/2;

    DEBUGPRINT1("VECTOR: %d \n", (linfo->n-1)*3);
    r = gsl_vector_alloc((linfo->n-1)*3); 
    dr = gsl_vector_alloc((linfo->n-1)*3); 
    DEBUGPRINT1("VECTOR: %d \n", linfo->m*3);
    b = gsl_vector_alloc(linfo->m*3); 
    db = gsl_vector_alloc(linfo->m*3); 

    eosPointCoordInit(&pc, 0);
    eosPointTop(inP);
    count=0;
    while(inP->current != NULL){
        count++;
        eosPointNext(inP);
    }
    if(count!=linfo->m) {
        fprintf(stderr, "n %d: m %d is different from data number %d\n", linfo->n, linfo->m, count);
        return -1;
    }
    eosPointTop(inP);
    count=0;
    while(inP->current != NULL){
        DEBUGPRINT4("%d: %f %f %f\n", count, inP->current->p.coord.data[0], inP->current->p.coord.data[1], inP->current->p.coord.data[2])
        gsl_vector_set(b, count*3,   inP->current->p.coord.data[0]);
        gsl_vector_set(b, count*3+1, inP->current->p.coord.data[1]);
        gsl_vector_set(b, count*3+2, inP->current->p.coord.data[2]);
        count++;
        eosPointNext(inP);
    }

/*
 ri = shift(i, i+1)
 i = 1...n;

 B1 = b12 = r1
 B2 = b13 = r1 + r2
 ...
      b23 =      r2
      b24 =      r2 + r3
      b25 =      r2 + r3 + r4
 ...
 Bk = bij =           ri + ...+ rj-1
...
 Bm =                                rn-1
  m = 1...n(n-1)/2

 b = A r
 r <- (At A)-1 At b 

*/
    A  = gsl_matrix_calloc(linfo->m*3, (linfo->n-1)*3);
    DEBUGPRINT2("MATRIX: %d %d\n", linfo->m*3, (linfo->n-1)*3);
    k = 0;
    for(i=0;   i< linfo->n-1; i++) { 
    for(j=i+1; j< linfo->n;   j++) { // bij  
        DEBUGPRINT3("%d (%d, %d)\n", k, i, j);
        for(l=i; l<j; l++) { //ri+...+rj-1 
            DEBUGPRINT5("(%d %d) - %d mean shift(%d, %d)\n", i, j, l, l, l+1);
            gsl_matrix_set(A, k*3,   l*3,   1);   
            gsl_matrix_set(A, k*3+1, l*3+1, 1);   
            gsl_matrix_set(A, k*3+2, l*3+2, 1);   
        }
        k++;
    }
    }
    if(k==linfo->m) {
        DEBUGPRINT("SUCCESS\n");
        DEBUGPRINT1("Count: %d\n", k);
#ifdef DEBUG
        //gsl_matrix_fprintf(stderr, A, "%g");
#endif
    } else {
        return -1;
    }

    // Least Square 
    // r = (At A)-1 At b
    AtA = gsl_matrix_calloc((linfo->n-1)*3, (linfo->n-1)*3);
    p = gsl_permutation_alloc((linfo->n-1)*3);
    AtAInv = gsl_matrix_calloc((linfo->n-1)*3, (linfo->n-1)*3);
    AtAInvAt = gsl_matrix_calloc((linfo->n-1)*3, linfo->m*3);

    gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1, A, A, 0.0, AtA);
    gsl_linalg_LU_decomp(AtA, p, &signum); // LU decomp
    gsl_linalg_LU_invert(AtA, p, AtAInv);  // Inv
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1, AtAInv, A, 0.0, AtAInvAt);
    gsl_blas_dgemv(CblasNoTrans, 1.0, AtAInvAt, b, 1.0, r);

    // db = A r - b
    gsl_blas_dgemv(CblasNoTrans, 1.0, A, r, 0.0, db);
    gsl_blas_daxpy(-1.0, b, db);

    eosPointInit(&(linfo->db), NULL);
    for(k=0; k<linfo->m; k++) {
        eosPointCoordSet(&pc, fabs(gsl_vector_get(db, k*3)), 
                              fabs(gsl_vector_get(db, k*3+1)), 
                              fabs(gsl_vector_get(db, k*3+2))); 
        eosPointAppend(&(linfo->db), &pc, 0);
    }
    // r  = (At A)-1 At b
    // |dr| = sqrt((At A)-1) At |db|^2)
    gsl_vector_mul(db, db);
    gsl_matrix_mul_elements(AtAInvAt, AtAInvAt);
    gsl_blas_dgemv(CblasNoTrans, 1.0, AtAInvAt, db, 0.0, dr);

    // eosPoint
    eosPointInit(outP, NULL);
    for(k=0; k<linfo->n-1; k++) {
        eosPointCoordSet(&pc, gsl_vector_get(r, k*3), 
                              gsl_vector_get(r, k*3+1), 
                              gsl_vector_get(r, k*3+2)); 
        eosPointCoordSigSet(&pc, sqrt(gsl_vector_get(dr, k*3  )),
                                 sqrt(gsl_vector_get(dr, k*3+1)),
                                 sqrt(gsl_vector_get(dr, k*3+2)));
        eosPointAppend(outP, &pc, 0);
    }

    gsl_vector_free(r);
    gsl_vector_free(dr);
    gsl_vector_free(b);
    gsl_vector_free(db);
    gsl_matrix_free(A);
    gsl_matrix_free(AtA);
    gsl_matrix_free(AtAInv);
    gsl_matrix_free(AtAInvAt);
    gsl_permutation_free(p);
    return count;    
}
