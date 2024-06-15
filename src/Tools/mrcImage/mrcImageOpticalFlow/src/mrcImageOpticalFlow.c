/*
# mrcImageOpticalFlow : $Revision$
# $Date$
# Created by $Author$
# Usage : mrcImageOpticalFlow
# Attention
#   $Loccker$
#  	$State$
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_errno.h>

#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcImageOpticalFlow.h"

/*
Example:
typedef struct lmrcImageOpticalFlowInfo {
	float a;
	int   b;
} lmrcImageOpticalFlowInfo;

typedef enum lmrcImageOpticalFlowMode {
	a=0,
	b=1
} lmrcImageOpticalFlowMode;
*/

typedef struct calculationData {
    float x;
    float y;
    float z;
    double fx;
    double fy;
    double fz;
    double di;

    struct calculationData* next;
} calculationData;


double differential(double a, double b){
    double k;
    k = (b-a)/2;
    return k;
}

double difference(double a, double b){
    double k;
    k = -(b-a);
    return k;
}

struct calculationData* addList(struct calculationData *calc, float x, float y, float z, double a, double b, double c, double d){
    struct calculationData *top;
    struct calculationData *item;
    
    item = (struct calculationData*)malloc(sizeof(struct calculationData));
    item->x = x;
    item->y = y;
    item->z = z;
    item->fx = a;
    item->fy = b;
    item->fz = c;
    item->di = d;
    item->next = NULL;
    
    if(calc == NULL){
        
        calc = item;
        top = calc;
        
        return calc;
        
    }
    
    while(calc->next != NULL){
            calc = calc->next;
    }
    
    calc->next = item;
    
    return item;
}


int main(int argc, char* argv[])
{
	mrcImageOpticalFlowInfo info;
    struct calculationData *calc;
    
    mrcImage in1;
    mrcImage in2;
    mrcImage in3;
    mrcImage outFx;
    mrcImage outFy;
    mrcImage outFz;
    mrcImage outDi;
    mrcImage Vx;
    mrcImage Vy;
    mrcImage Vz;
    mrcImage Size;
    //mrcImage Det;
    
    float x,y,z;
    x = y = z = 1;
    double data1,data2;
    double fx, fy, fz, di;
    fx = fy = fz = di = 0;
    
    int i,j,k;
    int signum;
    int count;
    
    double vx, vy, vz;
    double size;
    //double det;
    
    double min, max, med, half;
    max = 1.0;
    min = 0.1;
    half = (max - min)/2;
    med = min + half;
    double R, G, B;
    

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    
    mrcFileRead(&in1, info.In1, "in main", 0);
    mrcFileRead(&in2, info.In2, "in main", 0);
    if(info.flagIn3) { 
      mrcFileRead(&in3, info.In3, "in main", 0);
    }
    
    outFx.Header = in1.Header;
    outFy.Header = in1.Header;
    outFz.Header = in1.Header;
    outDi.Header = in1.Header;
    Vx.Header = in1.Header;
    Vy.Header = in1.Header;
    Vz.Header = in1.Header;
    Size.Header = in1.Header;

    mrcInit(&outFx, NULL);
    mrcInit(&outFy, NULL);
    mrcInit(&outFz, NULL);
    mrcInit(&outDi, NULL);
    mrcInit(&Vx, NULL);
    mrcInit(&Vy, NULL);
    mrcInit(&Vz, NULL);
    mrcInit(&Size, NULL);
    
    calc = NULL;
    
    for(z=1; z<in1.HeaderN.z - 2; z++){
         for(y=1; y<in1.HeaderN.y - 2; y++){
              for(x=1; x<in1.HeaderN.x - 2; x++){
                if(info.flagIn3) {
                  mrcPixelDataGet(&in2, x+1,y,z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                  mrcPixelDataGet(&in2, x-1,y,z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                  fx = differential(data1, data2);

                  mrcPixelDataGet(&in2, x,y+1,z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                  mrcPixelDataGet(&in2, x,y-1,z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                  fy = differential(data1, data2);

                  mrcPixelDataGet(&in2, x,y,z+1, &data1, mrcPixelRePart, mrcPixelHowNearest);
                  mrcPixelDataGet(&in2, x,y,z-1, &data2, mrcPixelRePart, mrcPixelHowNearest);
                  fz = differential(data1, data2);

                  mrcPixelDataGet(&in1, x,y,z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                  mrcPixelDataGet(&in3, x,y,z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                  di = +1*differential(data1, data2);
                } else {
                  mrcPixelDataGet(&in1, x+1,y,z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                  mrcPixelDataGet(&in1, x-1,y,z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                  fx = differential(data1, data2);

                  mrcPixelDataGet(&in1, x,y+1,z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                  mrcPixelDataGet(&in1, x,y-1,z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                  fy = differential(data1, data2);

                  mrcPixelDataGet(&in1, x,y,z+1, &data1, mrcPixelRePart, mrcPixelHowNearest);
                  mrcPixelDataGet(&in1, x,y,z-1, &data2, mrcPixelRePart, mrcPixelHowNearest);
                  fz = differential(data1, data2);
              
                  mrcPixelDataGet(&in1, x,y,z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                  mrcPixelDataGet(&in2, x,y,z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                  di = -1*difference(data1, data2);
                }     
                  calc = addList(calc, x, y, z, fx, fy, fz, di);
                  
                  //DEBUGPRINT("Program Start %f", &x);
                  
                  mrcPixelDataSet(&outFx, x,y,z, fx, mrcPixelRePart);
                  mrcPixelDataSet(&outFy, x,y,z, fy, mrcPixelRePart);
                  mrcPixelDataSet(&outFz, x,y,z, fz, mrcPixelRePart);
                  mrcPixelDataSet(&outDi, x,y,z, di, mrcPixelRePart);
              
              }
         }
    }
    //printf("finish\n");
    
    free(calc);
    
    if(info.flagOutFx) {
        mrcFileWrite(&outFx, info.OutFx, "in main", 0);
        mrcFileWrite(&outFy, info.OutFy, "in main", 0);
        mrcFileWrite(&outFz, info.OutFz, "in main", 0);
        mrcFileWrite(&outDi, info.OutDi, "in main", 0);
    }
    
    gsl_matrix * m = gsl_matrix_alloc(27,3);
    gsl_matrix * b = gsl_matrix_alloc(27,1);
    gsl_matrix * mp_result = gsl_matrix_alloc(3,3);
    gsl_matrix * mp_result2 = gsl_matrix_alloc(3,27);
    gsl_matrix * inv = gsl_matrix_alloc(3, 3);
    gsl_matrix * final = gsl_matrix_alloc(3, 1);
    
    gsl_permutation * p = gsl_permutation_alloc(3);
    
    //FILE * f = fopen("test.dat","wb");
    
    
    for(z=1; z<in1.HeaderN.z - 2; z++){
    for(y=1; y<in1.HeaderN.y - 2; y++){
    for(x=1; x<in1.HeaderN.x - 2; x++){
        mrcPixelDataGet(&in1, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(&in2, x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
        if(data1 < info.BG || data2< info.BG) {
            mrcPixelDataSet(&Vx, x, y, z, 0, mrcPixelRePart);
            mrcPixelDataSet(&Vy, x, y, z, 0, mrcPixelRePart);
            mrcPixelDataSet(&Vz, x, y, z, 0, mrcPixelRePart);
            mrcPixelDataSet(&Size, x, y, z, 0, mrcPixelRePart);
            DEBUGPRINT5("data1-data2: %f  %f at %f %f %f\n", data1, data2, x, y, z);
        } else {
            count = 0;

            for(k=z-1; k<z+2; k++){
            for(j=y-1; j<y+2; j++){
            for(i=x-1; i<x+2; i++){
                mrcPixelDataGet(&outFx, i, j, k, &fx, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&outFy, i, j, k, &fy, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&outFz, i, j, k, &fz, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&outDi, i, j, k, &di, mrcPixelRePart, mrcPixelHowNearest);
                //行列の入力
                gsl_matrix_set(m, count, 0, fx);
                gsl_matrix_set(m, count, 1, fy);
                gsl_matrix_set(m, count, 2, fz);
                DEBUGPRINT1("%d\n",count);
                DEBUGPRINT3("%g %g %g\n",gsl_matrix_get(m, count, 0), gsl_matrix_get(m, count, 1), gsl_matrix_get(m, count, 2));
                              
                gsl_matrix_set(b, count, 0, di);
                DEBUGPRINT1("%g\n", gsl_matrix_get(b, count, 0));
                              
                //countは27回で1セット
                count++;
                if(count == 27){
                    break;
                }
            }
            }
            }
                  
            //転置行列[3×27] × 元の行列[27×3]
            gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1.0, m, m, 0.0, mp_result);
            //gsl_matrix_fwrite(f, mp_result);
                  
            //LU分解
            gsl_linalg_LU_decomp(mp_result, p, &signum);
            gsl_linalg_LU_invert(mp_result, p, inv);
                  
            //det = gsl_linalg_LU_det(mp_result, signum);
            //mrcPixelDataSet(&Det, x, y, z, det, mrcPixelRePart);

            //逆行列×転置行列
            gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, inv, m, 0.0, mp_result2);
            //bをかける
            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, mp_result2, b, 0.0, final);
                  
            DEBUGPRINT3("%f %f %f\n", x, y, z);
            vx = gsl_matrix_get(final, 0, 0);
            vy = gsl_matrix_get(final, 1, 0);
            vz = gsl_matrix_get(final, 2, 0);
            size = sqrt(vx*vx + vy*vy + vz*vz);

            mrcPixelDataSet(&Vx, x, y, z, vx, mrcPixelRePart);
            mrcPixelDataSet(&Vy, x, y, z, vy, mrcPixelRePart);
            mrcPixelDataSet(&Vz, x, y, z, vz, mrcPixelRePart);
            mrcPixelDataSet(&Size, x, y, z, size, mrcPixelRePart);
        }
    }
    }
    }
    
    if(info.flagOutBILD) {
        min = FLT_MAX;
        max = FLT_MIN;
        for(z=1; z<in1.HeaderN.z - 2; z++){
        for(y=1; y<in1.HeaderN.y - 2; y++){
        for(x=1; x<in1.HeaderN.x - 2; x++){
            mrcPixelDataGet(&Size, x, y, z, &size, mrcPixelRePart, mrcPixelHowNearest);
            mrcPixelDataGet(&in1, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
            if(info.BG < data1) {
                if(size<min) min = size;          
                if(max<size) max= size;          
            }
        }
        }
        }
        if(info.flagBildThresLow) {
            min = info.BildThresLow;
        }
        if(info.flagBildThresHigh) {
            max= info.BildThresHigh;
        }
        half = (max - min)/2;
        med = min + half;

        for(z=1; z<in1.HeaderN.z - 2; z++){
        for(y=1; y<in1.HeaderN.y - 2; y++){
        for(x=1; x<in1.HeaderN.x - 2; x++){
            mrcPixelDataGet(&in1, x, y, z,  &data1, mrcPixelRePart, mrcPixelHowNearest);
            mrcPixelDataGet(&Size, x, y, z, &size,  mrcPixelRePart, mrcPixelHowNearest);
            if(info.flagBildRangeLow  && size < info.BildRangeLow 
            || info.flagBildRangeHigh && info.BildRangeLow < size) {

            } else {
                if(info.BG < data1 
                && size < min){
                    fprintf(info.fptOutBILD, ".color blue\n");
                    //fprintf(info.fptOutBILD, ".color light gray\n");
                } else if(min <= size && size < med){
                    R = 0;
                    G = (size/half);
                    B = ((-size+half)/half);
                    fprintf(info.fptOutBILD, ".color %f %f %f\n", fabs(R), fabs(G), fabs(B));
                    //fprintf(info.fptOutBILD, ".color light gray\n");
                } else if(med <=size && size < max){
                    R = ((vx-half)/half);
                    G = ((-vy+2*half)/half);
                    B = 0;
                    fprintf(info.fptOutBILD, ".color %f %f %f\n", fabs(R), fabs(G), fabs(B));
                    //fprintf(info.fptOutBILD, ".color light gray\n");
                } else {
                    fprintf(info.fptOutBILD, ".color red\n");
                }
                mrcPixelDataGet(&Vx, x, y, z,  &vx, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&Vy, x, y, z,  &vy, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&Vz, x, y, z,  &vz, mrcPixelRePart, mrcPixelHowNearest);
                fprintf(info.fptOutBILD, ".arrow %g %g %g %g %g %g %g %g\n",
                    (x   +Vx.HeaderStartN.x)*Vx.HeaderLength.x,  (y   +Vy.HeaderStartN.y)*Vy.HeaderLength.y, (z   +Vz.HeaderStartN.z)*Vz.HeaderLength.z,
                    (x+vx+Vx.HeaderStartN.x)*Vx.HeaderLength.x,  (y+vy+Vy.HeaderStartN.y)*Vy.HeaderLength.y, (z+vz+Vz.HeaderStartN.z)*Vz.HeaderLength.z,
                    Vx.HeaderLength.x*0.02, Vx.HeaderLength.x*0.02);
            }
        }
        }
        }
    }
    if(info.flagOutCOMMAND) {    
        fprintf(info.fptOutCOMMAND, "movie record supersample 3\n");
        fprintf(info.fptOutCOMMAND, "open /Users/enokidayuya/Eos/src/Tools/test/mrcImageOpticalFlow/src/test/data/anaphase_s-8_all/0_8-s.bild\n");
        fprintf(info.fptOutCOMMAND, "movie stop\n");
        fprintf(info.fptOutCOMMAND, "movie encode output /Users/enokidayuya/Eos/src/Tools/test/mrcImageOpticalFlow/src/test/data/anaphase_s-8_all/turn1.mp4 bitrate 6000\n");
    }
    
    //fclose(f);
    gsl_matrix_free(m);
    gsl_matrix_free(b);
    gsl_matrix_free(mp_result);
    gsl_matrix_free(mp_result2);
    gsl_matrix_free(inv);
    gsl_matrix_free(final);
    gsl_permutation_free(p);
    
    if(info.flagVx) {
        mrcFileWrite(&Vx, info.Vx, "in main", 0);
        mrcFileWrite(&Vy, info.Vy, "in main", 0);
        mrcFileWrite(&Vz, info.Vz, "in main", 0);
    }
    if(info.flagSize) {
        mrcFileWrite(&Size, info.Size, "in main", 0);
    }

    /*
    if(info.flagDet) {
        mrcFileWrite(&Det, info.Det, "in main", 0);
    }
    */
    return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
