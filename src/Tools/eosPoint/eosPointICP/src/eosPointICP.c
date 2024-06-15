/*
# eosPointICP : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosPointICP
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG

static int __debug_mode__=0;

/*
Example:
typedef struct leosPointICPInfo {
	float a;
	int   b;
} leosPointICPInfo;

typedef enum leosPointICPMode {
	a=0,
	b=1
} leosPointICPMode;
*/

// trace of matrix
double trace(int cnt_row, double matrix[cnt_row][cnt_row])
{
	int i, j;
	double sum = 0.0;

	for (i = 0; i < cnt_row; i++) {
		sum += matrix[i][i];
	}
	return sum;
}

//座標数カウント
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

//inP_updに対するrefPの最近傍点の特定　-線形探索
void identifyCP(eosPoint *inP, eosPoint *refP, int *closest_index_pair)
{
	int i = 0, j = 1;
	double pair[2]; //0:index 1:distance
	double distance;
	eosPoint *_inP, *_refP;
	eosPointTop(inP);
	eosPointTop(refP);
	for (_inP = inP;; eosPointNext(_inP)) {
		pair[0] = 0;
		pair[1] = sqrt( SQR(refP->top->p.coord.data[0] - _inP->current->p.coord.data[0]) + 
						SQR(refP->top->p.coord.data[1] - _inP->current->p.coord.data[1]) + 
						SQR(refP->top->p.coord.data[2] - _inP->current->p.coord.data[2]));
		if (j == 1) {
			eosPointTop(refP);
			eosPointNext(refP);
		}
		for (_refP = refP;; eosPointNext(_refP)){
			distance = sqrt(SQR(refP->current->p.coord.data[0] - _inP->current->p.coord.data[0]) + 
							SQR(refP->current->p.coord.data[1] - _inP->current->p.coord.data[1]) + 
							SQR(refP->current->p.coord.data[2] - _inP->current->p.coord.data[2]));
			if (pair[1] > distance){
				pair[0] = j;
				pair[1] = distance;
			}
			j++;
			if (_refP->current == refP->bottom){
				break;
			}
		}
		closest_index_pair[i] = (int)pair[0];
		i++;
		j = 1;
		if (_inP->current == inP->bottom){
			break;
		}
	}
}

//重心計算
eosPointCoord calculatePointsG(eosPoint *P, int count)
{
	int i, j;
	eosPointCoord g;
	eosPointCoordInit(&g, 4); //第２引数は意味なし
	eosPointTop(P);
	for (i = 0; i < 3; i++){
		g.coord.data[0] = 0;
	}
	for (i = 0; i < count; i++){
		for (j = 0; j < 3; j++){
			g.coord.data[j] += P->current->p.coord.data[j];
		}
		eosPointNext(P);
	}
	for (i = 0; i < 3; i++){
		g.coord.data[i] /= count;
	}
	return g;
}

//in_updに対する最近傍点であるrefに対応するようにrefのポインタを移動
void moveRefAccordingToCP(int closest_index_pair_value, eosPoint *refP)
{
	int i;
	eosPointTop(refP);
	for (i = 0; i < closest_index_pair_value; i++){
		eosPointNext(refP);
	}
}

//共分散行列の生成
void generateCovM(double covm[3][3], int cnt_in_point, int *closest_index_pair, eosPoint *inP_upd, eosPoint *refP, eosPointCoord inP_upd_G, eosPointCoord refP_G)
{
	int i, j;
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			covm[i][j] = 0;
		}
	}
	eosPointTop(inP_upd);
	for (i = 0; i < cnt_in_point; i++){
		moveRefAccordingToCP(closest_index_pair[i], refP);
		covm[0][0] += refP->current->p.coord.data[0] * inP_upd->current->p.coord.data[0] - refP_G.coord.data[0] * inP_upd_G.coord.data[0];
		covm[0][1] += refP->current->p.coord.data[0] * inP_upd->current->p.coord.data[1] - refP_G.coord.data[0] * inP_upd_G.coord.data[1];
		covm[0][2] += refP->current->p.coord.data[0] * inP_upd->current->p.coord.data[2] - refP_G.coord.data[0] * inP_upd_G.coord.data[2];

		covm[1][0] += refP->current->p.coord.data[1] * inP_upd->current->p.coord.data[0] - refP_G.coord.data[1] * inP_upd_G.coord.data[0];
		covm[1][1] += refP->current->p.coord.data[1] * inP_upd->current->p.coord.data[1] - refP_G.coord.data[1] * inP_upd_G.coord.data[1];
		covm[1][2] += refP->current->p.coord.data[1] * inP_upd->current->p.coord.data[2] - refP_G.coord.data[1] * inP_upd_G.coord.data[2];

		covm[2][0] += refP->current->p.coord.data[2] * inP_upd->current->p.coord.data[0] - refP_G.coord.data[2] * inP_upd_G.coord.data[0];
		covm[2][1] += refP->current->p.coord.data[2] * inP_upd->current->p.coord.data[1] - refP_G.coord.data[2] * inP_upd_G.coord.data[1];
		covm[2][2] += refP->current->p.coord.data[2] * inP_upd->current->p.coord.data[2] - refP_G.coord.data[2] * inP_upd_G.coord.data[2];
		eosPointNext(inP_upd);
	}
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			covm[i][j] /= cnt_in_point;
		}
	}
}

//対称行列の生成
void generateSymM(double symm[4][4], double covm[3][3])
{
	int i, j;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			symm[i][j] = 0;
		}
	}

	symm[0][0] = trace(3, covm);
	symm[0][1] = covm[1][2] - covm[2][1];
	symm[0][2] = covm[2][0] - covm[0][2];
	symm[0][3] = covm[0][1] - covm[1][0];

	symm[1][0] = covm[1][2] - covm[2][1];
	symm[1][1] = 2 * covm[0][0] - trace(3, covm);
	symm[1][2] = covm[0][1] - covm[1][0];
	symm[1][3] = covm[0][2] - covm[2][0];

	symm[2][0] = covm[2][0] - covm[0][2];
	symm[2][1] = covm[0][1] - covm[1][0];
	symm[2][2] = 2 * covm[1][1] - trace(3, covm);
	symm[2][3] = covm[1][2] - covm[2][1];

	symm[3][0] = covm[0][1] - covm[1][0];
	symm[3][1] = covm[0][2] - covm[2][0];
	symm[3][2] = covm[1][2] - covm[2][1];
	symm[3][3] = 2 * covm[2][2] - trace(3, covm);
}

//対称行列から絶対値最大の固有値に対応する固有ベクトル(正規化)を求める。
void jacobi(double symm[4][4], double *eigen_vector)
{
	int i, j, k, p, q;
	double max;
	int max_columns;
	double theta;
	double P[4][4];		   //ギブンス回転行列
	double Ps[4][4];	   //Pの積み重ね
	double Ps_cache[4][4]; //Psのキャッシュ
	double B[4][4];		   //更新される行列
	double B_cache[4][4];  //Bの更新で一つ前のBを使うのでキャッシュする
	int end_flag = 0;
	double norm;
	int loop_count = 1;

	//Bの生成,Psを単位行列で初期化
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			B[i][j] = symm[i][j];
			Ps[i][j] = 0;
		}
		Ps[i][i] = 1.0;
	}

	while (1){
		//行列の絶対値最大のnondiagonal-indexを探索-線形探索
		max = 0;
		p = 0;
		q = 0;
		for (i = 0; i < 4; i++){
			for (j = 0; j < 4; j++){
				if (i != j && max < fabs(B[i][j])){
					p = i;
					q = j;
					max = fabs(B[i][j]);
				}
			}
		}
		// printf("max=B[%d][%d]\n", p, q);
		//maxindexが更新されない　maxがない
		if (p == 0 && q == 0){
			end_flag = 1;
		}

		if (!end_flag){
			//B,Psをキャッシュ
			for (i = 0; i < 4; i++){
				for (j = 0; j < 4; j++){
					B_cache[i][j] = B[i][j];
					Ps_cache[i][j] = Ps[i][j];
				}
			}

			//θを計算
			if (B[p][p] != B[q][q]){
				theta = atan(-1 * 2 * B[p][q] / (B[p][p] - B[q][q])) / 2;
			}else{
				theta = PI / 4.0;
			}

			//Bの更新
			for (i = 0; i < 4; i++){
				for (j = 0; j < 4; j++){
					if ((i == p && j == q) || (i == q && j == p)){
						B[i][j] = 0;
					}else if (i == p && j == p){
						B[i][j] = (B_cache[p][p] + B_cache[q][q]) / 2.0 + (B_cache[p][p] - B_cache[q][q]) / 2.0 * cos(2.0 * theta) - B_cache[p][q] * sin(2.0 * theta);
					}else if (i == q && j == q){
						B[i][j] = (B_cache[p][p] + B_cache[q][q]) / 2.0 - (B_cache[p][p] - B_cache[q][q]) / 2.0 * cos(2.0 * theta) + B_cache[p][q] * sin(2.0 * theta);
					}else if (i == p || j == p){
						if (i == p){
							B[i][j] = B_cache[p][j] * cos(theta) - B_cache[q][j] * sin(theta);
						}else{ //j==p
							B[i][j] = B_cache[i][p] * cos(theta) - B_cache[i][q] * sin(theta);
						}
					}else if (i == q || j == q){
						if (i == q){
							B[i][j] = B_cache[p][j] * sin(theta) + B_cache[q][j] * cos(theta);
						}else{//j==q
							B[i][j] = B_cache[i][p] * sin(theta) + B_cache[i][q] * cos(theta);
						}
					}else{
						B[i][j] = B_cache[i][j];
					}
				}
			}

			//ギブンス回転行列の構築
			for (i = 0; i < 4; i++){
				P[i][i] = 1.0;
				for (j = 3; j > i; j--){
					P[i][j] = P[j][i] = 0;
				}
			}
			P[p][p] = cos(theta);
			P[p][q] = (q > p) ? sin(theta) : -1 * sin(theta);
			P[q][p] = (q > p) ? -1 * sin(theta) : sin(theta);
			P[q][q] = cos(theta);

			//ギブンスの積み重ね 行列の掛け算 P = P1・P2...Pn
			for (i = 0; i < 4; i++){
				for (j = 0; j < 4; j++){
					Ps[i][j] = 0;
					for (k = 0; k < 4; k++){
						Ps[i][j] += Ps_cache[i][k] * P[k][j];
					}
				}
			}
		}

		//非対角成分が0判定
		end_flag = 1;
		for (i = 0; i < 4; i++){
			for (j = 3; j > i; j--){
				if (fabs(B[j][i]) >= 0.00001 || fabs(B[i][j]) >= 0.00001){
					end_flag = 0;
					break;
				}
			}
		}
		if (end_flag || loop_count >= 50){
			// 対角化された行列に現れる固有値の絶対値最大が現れる列に対応する固有ベクトルを正規化してeigen_vectorにする。
			max = fabs(B[0][0]);
			max_columns = 0;
			for (i = 1; i < 4; i++){
				if (max < fabs(B[i][i])){
					max = fabs(B[i][i]);
					max_columns = i;
				}
			}
			norm = sqrt(SQR(Ps[0][max_columns]) + SQR(Ps[1][max_columns]) + SQR(Ps[2][max_columns]) + SQR(Ps[3][max_columns]));
			// printf("norm=%lf\n",norm);
			for (i = 0; i < 4; i++){
				eigen_vector[i] = Ps[i][max_columns] / norm;
				// printf("eigen_vec[%d]=%lf\n", i, eigen_vector[i]);
			}
			break;
		}
		loop_count++;
	}
}

//回転行列の生成
void generateRotationMatrix(double rotation_mat[3][3], double qr[4])
{
	rotation_mat[0][0] = SQR(qr[0]) + SQR(qr[1]) - SQR(qr[2]) - SQR(qr[3]);
	rotation_mat[0][1] = 2 * (qr[1] * qr[2] - qr[0] * qr[3]);
	rotation_mat[0][2] = 2 * (qr[1] * qr[3] + qr[0] * qr[2]);
	rotation_mat[1][0] = 2 * (qr[1] * qr[2] + qr[0] * qr[3]);
	rotation_mat[1][1] = SQR(qr[0]) + SQR(qr[2]) - SQR(qr[1]) - SQR(qr[3]);
	rotation_mat[1][2] = 2 * (qr[2] * qr[3] - qr[0] * qr[1]);
	rotation_mat[2][0] = 2 * (qr[1] * qr[3] - qr[0] * qr[2]);
	rotation_mat[2][1] = 2 * (qr[2] * qr[3] + qr[0] * qr[1]);
	rotation_mat[2][2] = SQR(qr[0]) + SQR(qr[3]) - SQR(qr[1]) - SQR(qr[2]);
}

//平行移動パラメータの算出
void calculateTranslation(eosPointCoord *inP_upd_G, eosPointCoord *refP_G, double rotation_mat[3][3], double qt[3])
{
	qt[0] = refP_G->coord.data[0] - (rotation_mat[0][0] * inP_upd_G->coord.data[0] + 
									 rotation_mat[0][1] * inP_upd_G->coord.data[1] + 
									 rotation_mat[0][2] * inP_upd_G->coord.data[2] );
	qt[1] = refP_G->coord.data[1] - (rotation_mat[1][0] * inP_upd_G->coord.data[0] + 
									 rotation_mat[1][1] * inP_upd_G->coord.data[1] + 
									 rotation_mat[1][2] * inP_upd_G->coord.data[2] );
	qt[2] = refP_G->coord.data[2] - (rotation_mat[2][0] * inP_upd_G->coord.data[0] + 
									 rotation_mat[2][1] * inP_upd_G->coord.data[1] + 
									 rotation_mat[2][2] * inP_upd_G->coord.data[2] );
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

//Rmaxの算出
void calculateRmax(eosPoint inP,eosPointCoord inP_upd_G, double* r_max, int cnt_in_point)
{
	int i,j;
	double r;
	*r_max = 0;
	eosPointTop(&inP);
	for(i=0;i<cnt_in_point; i++){
		r = sqrt(SQR(inP.current->p.coord.data[0] - inP_upd_G.coord.data[0]) +
				 SQR(inP.current->p.coord.data[1] - inP_upd_G.coord.data[1]) +
				 SQR(inP.current->p.coord.data[2] - inP_upd_G.coord.data[2]));
		
		if((*r_max) < r){
			*r_max = r;
		}
		eosPointNext(&inP);
	}
}

//SCOREの算出
double calculateScore(eosPoint *inP_upd, eosPoint *refP, int cnt_in_point, int *closest_index_pair, double r_max, double omit, int mode)
{
	int i;
	double se = 0;
    double seRobust = 0;
    double dis;
    double count;
	eosPointTop(inP_upd);
	for (i = 0, count=0; i < cnt_in_point; i++){
		moveRefAccordingToCP(closest_index_pair[i], refP);
		dis = SQR(inP_upd->current->p.coord.data[0] - refP->current->p.coord.data[0]) 
			+ SQR(inP_upd->current->p.coord.data[1] - refP->current->p.coord.data[1]) 
			+ SQR(inP_upd->current->p.coord.data[2] - refP->current->p.coord.data[2]);
        se += dis;
        if(sqrt(dis)<=omit) {
            seRobust += dis;
            count++;
        }
		eosPointNext(inP_upd);
	}
	// se = se/cnt_in_point;
	se = sqrt(se/cnt_in_point);
    if(3<=count) {
	    seRobust = sqrt(seRobust/count);
    } else {
	    seRobust = se;
    }
	// return se/r_max;
    switch(mode) {
        case 0: {
	        return se;
            break;
        } 
        case 1: {
            return seRobust;
            break;
        }
        default: {
            fprintf(stderr, "Not supported mode: %d\n", mode);
            return -1;
            break;
        }
    }
}

//SCOREの算出
double calculateScore2D(eosPoint *inP_upd, eosPoint *refP, int cnt_in_point, int *closest_index_pair, double r_max, double omit, int mode)
{
	int i;
	double se = 0;
    double seRobust = 0;
    double dis;
    double count;
	eosPointTop(inP_upd);
	for (i = 0, count=0; i < cnt_in_point; i++, count++){
		moveRefAccordingToCP(closest_index_pair[i], refP);
		dis = SQR(inP_upd->current->p.coord.data[0] - refP->current->p.coord.data[0]) 
			+ SQR(inP_upd->current->p.coord.data[1] - refP->current->p.coord.data[1]);
        se += dis;
        if(sqrt(dis)<=omit) {
            seRobust += dis;
        }
		eosPointNext(inP_upd);
	}
	// se = se/cnt_in_point;
	se = sqrt(se/cnt_in_point);
    if(3<count) {
	    seRobust = sqrt(seRobust/count);
    } else {
	    seRobust = se;
    }
	// return se/r_max;
    switch(mode) {
        case 0: {
	        return se;
            break;
        } 
        case 1: {
            return seRobust;
            break;
        }
        default: {
            fprintf(stderr, "Not supported mode: %d\n", mode);
            return -1;
            break;
        }
    }
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

// SCOREが最小の状態を記憶
void MemorizeStateOfMinimumScore(eosPointIcpResult* icp_result_set, eosPointIcpResult icp_current_set, int count)
{
	int i,j;
	if( count==1 || icp_result_set->score > icp_current_set.score){
		eosPointCopy(&icp_result_set->resultP, &icp_current_set.resultP);
		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				icp_result_set->matrix[i][j] = icp_current_set.matrix[i][j];
			}
		}	
		icp_result_set->score = icp_current_set.score;
	}
}

//ICPアルゴリズム
void icpAlgorhythm(eosPoint *inP, eosPoint *refP, double score_threshold, int iteration_limit, eosPointIcpResult* icp_result_set, double omit, int flag2D, int mode)
{
	eosPointCoord inP_upd_G, refP_G;
	eosPointIcpResult icp_current_set;
	int i, j;
	double covm[3][3];			 			//相互共分散行列(Covariance matrix)
	double symm[4][4];			 			//qR,qT算出のための行列-対称行列(Symmetric matrix)
	double qr[4];							//四元数　回転パラメータ
	double rotation_mat[3][3];   			//回転行列
	double qt[3];				 			//平行移動パラメータ
	double r_max;							//重心からの最大距離
	double score;		 					//独自スコア
	int count = 1;							//アルゴリズム反復回数カウント
	double min_score;						//反復の中での最小二乗法の最小スコア
	int cnt_in_point = countPoint(*inP);
	int cnt_ref_point = countPoint(*refP);
	int closest_index_pair[cnt_in_point]; 	//inとrefの最近傍点のindexのペア
	matrix3DInit(icp_current_set.matrix);
	eosPointCopy(&icp_current_set.resultP, inP);
	identifyCP(&icp_current_set.resultP, refP, closest_index_pair);
	inP_upd_G = calculatePointsG(&icp_current_set.resultP, cnt_in_point);
	refP_G = calculatePointsG(refP, cnt_ref_point);
	calculateRmax(icp_current_set.resultP, inP_upd_G, &r_max, cnt_in_point);

	while (1){
		inP_upd_G = calculatePointsG(&icp_current_set.resultP, cnt_in_point);
		generateCovM(covm, cnt_in_point, closest_index_pair, &icp_current_set.resultP, refP, inP_upd_G, refP_G);
		generateSymM(symm, covm);
		jacobi(symm, qr);
		generateRotationMatrix(rotation_mat, qr);
		calculateTranslation(&inP_upd_G, &refP_G, rotation_mat, qt);
		MakeAffine(&icp_current_set, rotation_mat, qt);
		applyMatrix(&icp_current_set.resultP, rotation_mat, qt, cnt_in_point);
		identifyCP(&icp_current_set.resultP, refP, closest_index_pair);
        if(flag2D) {
    		if( iteration_limit*0.5<count || icp_result_set->score < score_threshold*10){
    	    	icp_current_set.score = calculateScore2D(&icp_current_set.resultP, refP, cnt_in_point, closest_index_pair, r_max, omit, mode);
            } else {
    	    	icp_current_set.score = calculateScore2D(&icp_current_set.resultP, refP, cnt_in_point, closest_index_pair, r_max, omit, 0);
            }
        } else {
    		if( iteration_limit*0.5<count || icp_result_set->score < score_threshold*10){
    	    	icp_current_set.score = calculateScore(&icp_current_set.resultP, refP, cnt_in_point, closest_index_pair, r_max, omit, mode);
            } else {
    	    	icp_current_set.score = calculateScore(&icp_current_set.resultP, refP, cnt_in_point, closest_index_pair, r_max, omit, 0);
            }
        }
		MemorizeStateOfMinimumScore(icp_result_set, icp_current_set, count);
		if( count==iteration_limit || icp_result_set->score < score_threshold){
			break;
		}
		count++;
	}
}

//座標をピックアップする pickup_percentの割合でflagが立つ
void pickupPoint(eosPoint* inP, eosPoint* pickup_inP, int cnt_in_point, double pickup_percent)
{
	int i, j, pickup_flag;
    double p;

	eosPointTop(inP);  
	eosPointInit(pickup_inP, NULL);
	eosPointTop(pickup_inP);
	while(inP->current!=NULL){
        p = randomUniformGet(0,100,0);
		pickup_flag = (p<pickup_percent) ? 1 : 0;
		if(pickup_flag){
			eosPointAppend(pickup_inP, &(inP->current->p), 0);
		}
		eosPointNext(inP);
	}
}

//結果をファイルに出力
void writeOutput(eosPointICPInfo* info, eosPointIcpResult best_icp_result_set, eosPoint* inP, eosPoint* refP, char* euler_angle_Mode)
{
	int i, count=0;
	matrix3DParaTypeReal rot1, rot2, rot3;
	eosPoint final_inP;
	eosPointCopy(&final_inP, inP);
	fprintf(info->fptOut,"Result eosPointICP\n\n");
	fprintf(info->fptOut,"In  file: %s\ttype: %ld\n",info->In,info->InType);
	fprintf(info->fptOut,"Ref file: %s\ttype: %ld\n\n",info->Ref, info->RefType);
	
	//SCOREを表示
	if(info->flagScoreThreshold){
		fprintf(info->fptOut, "SCORE threshold: %.2f\n", info->ScoreThreshold);
	}else{
		fprintf(info->fptOut, "SCORE Threshold: Not set\n");
	}
	fprintf(info->fptOut, "SCORE: %lf\n\n", best_icp_result_set.score);
	//アフィン変換を表示
	fprintf(info->fptOut, "Affine transformation matrix: \n");
	for(i=0;i<4;i++){
		fprintf(info->fptOut, "%f\t%f\t%f\t%f\n", best_icp_result_set.matrix[0][i],
									 			  best_icp_result_set.matrix[1][i],
									 			  best_icp_result_set.matrix[2][i],
									 			  best_icp_result_set.matrix[3][i]);
	}
	//EAMODE,EulerAngleとTranslationを表示
	matrix3DEulerAngleGetFromMatrix3D( best_icp_result_set.matrix, euler_angle_Mode, &rot1, &rot2, &rot3, 1);
	fprintf(info->fptOut, "\nRotation angle(Euler Angle):\n");
	fprintf(info->fptOut, "MODE: %s\nRot1: %.2f, Rot2: %.2f, Rot3: %.2f\n\n", euler_angle_Mode, rot1*DEGREE, rot2*DEGREE, rot3*DEGREE);
	fprintf(info->fptOut, "Translation:\n");
	fprintf(info->fptOut, "\tx: %lf\ty: %lf\tz: %lf\n\n",best_icp_result_set.matrix[3][0],best_icp_result_set.matrix[3][1],best_icp_result_set.matrix[3][2]);
	fflush(info->fptOut);
	//afiine変換をinPに適用
	eosPointTop(&final_inP);
	eosPointTop(inP);
	while(inP->current != NULL){
		for(i=0;i<3;i++){
			final_inP.current->p.coord.data[i] = best_icp_result_set.matrix[0][i] * inP->current->p.coord.data[0] +
												 best_icp_result_set.matrix[1][i] * inP->current->p.coord.data[1] +
												 best_icp_result_set.matrix[2][i] * inP->current->p.coord.data[2] +
												 best_icp_result_set.matrix[3][i];
		}
		eosPointNext(&final_inP);
		eosPointNext(inP);
		count++;
	}
	int closest_index_pair[count];
	//final inPとrefを表示
	identifyCP(&final_inP, refP, closest_index_pair);
	eosPointTop(refP);
	eosPointTop(&final_inP);
	eosPointTop(&best_icp_result_set.resultP);

	fprintf(info->fptOut,"Coordinate\n");
	fprintf(info->fptOut,"ref\t\t\t\ticp_result(in)\n");
	for (i = 0; i < count; i++){
		moveRefAccordingToCP(closest_index_pair[i], refP);
		fprintf(info->fptOut, "%lf %lf %lf\t%lf %lf %lf\n", 
      refP->current->p.coord.data[0], 
      refP->current->p.coord.data[1], 
      refP->current->p.coord.data[2],
			final_inP.current->p.coord.data[0], 
      final_inP.current->p.coord.data[1], 
      final_inP.current->p.coord.data[2]);
		eosPointNext(&final_inP);
	}
}

void progressBar(int now, int end)
{
	int i;
	int count = now * 10 / end;
	printf("\r|");
	for(i=0;i<count;i++){
		printf("####");
	}
	for(i=count;i<10;i++){
		printf("----");
	}
	printf("|");
	if(now==end){
		printf("\n");
	}
	fflush(stdout);
}

void coordError()
{
	printf("\nError: The number of coordinate(in) over the number of coordinate(ref).\n");
	printf("       You must set the number of coordinate(ref) graeter than or equal to the number of coordinate(in).\n");
	printf("       in <= ref\n\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	int i;
	char input[15];
	eosPointICPInfo info;
	int icp_pattern;
	int cnt_in_point, cnt_ref_point;
	eosPoint inP, refP, pickup_inP;
	eosPointIcpResult icp_result_set, best_icp_result_set;
    Matrix3D inMat;
    Matrix3D refMat;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
    __debug_mode__ = info.Debug;

	eosPointRead(info.fptIn, &inP, info.InType);
    if(1<=__debug_mode__) {
        eosPointWrite(stderr, &inP, info.InType);
    }
    matrix3DInit(inMat); 
    if(info.flagInMat) {
        matrix3DFileRead(info.fptInMat, inMat);      
    } 
    if(info.flagRatio) {
        matrix3DScale(inMat, info.Ratio);
    }
    eosPointRotate(&inP, inMat);

    if(1<=__debug_mode__) {
        eosPointWrite(stderr, &inP, info.InType);
    }
    
	eosPointRead(info.fptRef, &refP, info.RefType);
    matrix3DInit(refMat); 
    if(info.flagRefMat) {
        matrix3DFileRead(info.fptRefMat, refMat);      
    } 
    if(info.flagRatio) {
        matrix3DScale(refMat, info.Ratio);
    }
    eosPointRotate(&refP, refMat);

	matrix3DInit(icp_result_set.matrix);
	matrix3DInit(best_icp_result_set.matrix);

	cnt_in_point = countPoint(inP);
	cnt_ref_point = countPoint(refP);
	if (cnt_in_point > cnt_ref_point){
		coordError();
	}

	for(icp_pattern=1;icp_pattern<=info.Pattern;icp_pattern++){
		progressBar(icp_pattern, info.Pattern);
		pickupPoint(&inP, &pickup_inP, cnt_in_point, info.Pickup);

		icpAlgorhythm(&pickup_inP, &refP, info.ScoreThreshold, info.IterationLimit, &icp_result_set, info.Omit, info.flag2D, info.mode);
		MemorizeStateOfMinimumScore(&best_icp_result_set, icp_result_set, icp_pattern);
	}

	writeOutput(&info, best_icp_result_set, &inP, &refP, info.EAMode);
	exit(EXIT_SUCCESS);
}

void additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "eosPointFormat\n");
	eosPointFileFormatUsage(stderr);
}
