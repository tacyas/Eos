//出力されるアフィン変換の行列をつかって，座標を変換するためのプログラム

/*
# eosPointAffineTransform : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosPointAffineTransform
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

#define DEBUG
#include "genUtil.h"
#include "eosPoint.h"

/*
Example:
typedef struct leosPointAffineTransformInfo {
	float a;
	int   b;
} leosPointAffineTransformInfo;

typedef enum leosPointAffineTransformMode {
	a=0,
	b=1
} leosPointAffineTransformMode;
*/

int countPoint(eosPoint point)
{
    int count = 0;
    eosPointTop(&point);
    while(point.current != NULL){
        count++;
        eosPointNext(&point);
    }
    return count;
}

//アフィン変換行列を計算
void MakeAffine(eosPointIcpResult* icp_result_set, double rotation_matrix[3][3], double* translation)
{
    int i,j;
    Matrix3D affine_matrix;
    matrix3DInit(affine_matrix);
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            affine_matrix[i][j] = rotation_matrix[j][i];
        }
        affine_matrix[3][i] = translation[i];
    }
    matrix3DMultiplyInv(affine_matrix, icp_result_set->matrix);
}

//変換行列を適用
void applyMatrix(eosPoint *inP_upd, double rotation_mat[3][3], double qt[3], int cnt_in_point)
{
    int i = 0;
    eosPoint cacheP;
    eosPointCopy(&cacheP, inP_upd);
    eosPointTop(inP_upd);
    eosPointTop(&cacheP);
    for (i = 0; i < cnt_in_point; i++){
        inP_upd->current->p.coord.data[0] = rotation_mat[0][0] * cacheP.current->p.coord.data[0] +
                                            rotation_mat[0][1] * cacheP.current->p.coord.data[1] +
                                            rotation_mat[0][2] * cacheP.current->p.coord.data[2] +
                                            qt[0];

        inP_upd->current->p.coord.data[1] = rotation_mat[1][0] * cacheP.current->p.coord.data[0] +
                                            rotation_mat[1][1] * cacheP.current->p.coord.data[1] +
                                            rotation_mat[1][2] * cacheP.current->p.coord.data[2] +
                                            qt[1];

        inP_upd->current->p.coord.data[2] = rotation_mat[2][0] * cacheP.current->p.coord.data[0] +
                                            rotation_mat[2][1] * cacheP.current->p.coord.data[1] +
                                            rotation_mat[2][2] * cacheP.current->p.coord.data[2] +
                                            qt[2];
        eosPointNext(inP_upd);
        eosPointNext(&cacheP);
    }
}

int
main(int argc, char* argv[]) 
{
	eosPointAffineTransformInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
