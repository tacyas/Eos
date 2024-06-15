/*
# calcCommonLine : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : calcCommonLine
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <bits/nan.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "../../../../Objects/General/Vector/inc/Vector.h"
//#include "Vector.h"

#define DEBUG
#include "genUtil.h"
//#include "rec3d.h"


int 
get_file_num(FILE *in)
{
	int count = 0;
	char line[256];

	fseek(in, 0L, SEEK_SET);
	while (fgets(line, sizeof(line), in) != NULL) {
		count++;
	}

	return count;
}


int
diff_vector(doubleVector *v1, doubleVector *v2)
{
	int i;

	if (v1->size != v2->size) {
		fprintf(stderr, "Two vectors have different size in diff_vector : %ld != %ld\n", v1->size, v2->size);
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < v1->size; i++) {
		if (v1->data[i] != v2->data[i]) {
			return 1;
		}
	}

	return 0;
}


void 
normalize_vector(doubleVector *v)
{
	int i;
	double norm;

	norm = ldoubleVectorLength(v);
	for (i = 0; i < v->size; i++) {
		v->data[i] /= norm;
	}
}


double
doubleVectorScalarProduct(doubleVector* v, doubleVector* w)
{
        long i;
        double sc;

	if (v->size != w->size) {
		fprintf(stderr, "Two vectors have different size in doubleVectorScalarProduct : %ld != %ld\n", v->size, w->size);
		exit(EXIT_FAILURE);
	}
	sc = 0.0;
	for (i = 0; i < v->size; i++) {
		sc += (v->data[i] * w->data[i]);
	}
	return sc;
}


void
doubleVectorVectorProduct(doubleVector *v1, doubleVector *v2, doubleVector *result)
{
	result->data[0] = v1->data[1] * v2->data[2]
	                - v1->data[2] * v2->data[1];

	result->data[1] = v1->data[2] * v2->data[0]
	                - v1->data[0] * v2->data[2];

	result->data[2] = v1->data[0] * v2->data[1]
	                - v1->data[1] * v2->data[0];

	normalize_vector(result);
}


void 
lcalcCommonLine(doubleVector *P1x, doubleVector *P2x, doubleVector *P1z, doubleVector *P2z,  doubleVector *cl, double *deg1, double *deg2, doubleVector *temp)
{
	double direct;

	if (diff_vector(P1z, P2z) == 0) {
		*deg1 = -5000;
		*deg2 = -5000;
		return;
	}

	/* コモンラインのベクトル */
	doubleVectorVectorProduct(P1z, P2z, cl);

	/* 投影像iのコモンラインの位置 (投影像iのシノグラムライン番号←つまり角度) */
	*deg1 = doubleVectorScalarProduct(P1x, cl);
	*deg1 = acos(*deg1) * 180.0 / M_PI;

	/* 投影像jのコモンラインの位置 (投影像jのシノグラムライン番号) */
	*deg2 = doubleVectorScalarProduct(P2x, cl);
	*deg2 = acos(*deg2) * 180.0 / M_PI;

	/* 投影像のx軸投影とコモンラインの外積を計算して、角度が180～360度でないかチェック */
	/* 投影像iの角度の補正 */
	doubleVectorVectorProduct(P1x, cl, temp);
	direct = doubleVectorScalarProduct(P1z, temp);
	if (direct < 0) {
		*deg1 = 360 - *deg1;
	}
	/* 投影像jの角度の補正 */
	doubleVectorVectorProduct(P2x, cl, temp);
	direct = doubleVectorScalarProduct(P2z, temp);
	if (direct < 0) {
		*deg2 = 360 - *deg2;
	}

	/* 投影像iの角度が180度以内になるようにしておく */
	if (*deg1 > 180) {
		*deg1 += (*deg1 < 180) ? 180 : -180;
		*deg2 += (*deg2 < 180) ? 180 : -180;
	}

	if (isnan(*deg1)) *deg1 = -1000;
	if (isnan(*deg2)) *deg2 = -1000;
}


void 
lcalcCommonLines(double **C, doubleVector *Px, doubleVector *Pz, int num)
{
	int i, j;
	double deg1, deg2;
	doubleVector cl, temp;

	doubleVectorInit(&cl, 3);
	doubleVectorInit(&temp, 3);

	/* calc angular degree */
	for (i = 0; i < num; i++) {
		for (j = i + 1; j < num; j++) {
			if (i == j) {
				continue;
			}

			lcalcCommonLine(&Px[i], &Px[j], &Pz[i], &Pz[j], &cl, &deg1, &deg2, &temp);

			C[i][j] = deg1;
			C[j][i] = deg2;
		}
	}
}


void 
lvectorsFromEulerAngles(doubleVector *E, doubleVector *Px, doubleVector *Pz, int num)
{
	/* 
		物体の回転行列 (YOYS)
		(  cos(phi)         	0       	 sin(phi)          )
		(  sin(phi)*sin(psi)	cos(psi)        -cos(phi)*sin(psi) )
		( -sin(phi)*cos(psi)	sin(psi)	 cos(phi)*cos(psi) )
		
		それぞれ転置行列と一致する

		カメラの回転行列 (YOYSの物体の回転行列の逆行列)
		( cos(phi)	sin(phi)*sin(psi) 	-sin(phi)*cos(psi) )
		( 0       	cos(psi)          	sin(psi)           )
		( sin(phi)	-cos(phi)*sin(psi)	cos(phi)*cos(psi)  )
	*/

	int i;
	double phi, psi;

	for (i = 0; i < num; i++) {
		/* 度からラジアンへ変換(cos()はラジアン値で処理するため) */
		phi = E[i].data[0] * M_PI / 180;
		psi = E[i].data[1] * M_PI / 180;

		Px[i].data[0] = cos(phi);  Pz[i].data[0] = -sin(phi) * cos(psi);
		Px[i].data[1] = 0;         Pz[i].data[1] =  sin(psi);
		Px[i].data[2] = sin(phi);  Pz[i].data[2] =  cos(phi) * cos(psi);

		normalize_vector(&Px[i]);
		normalize_vector(&Pz[i]);
	}
}


void 
lreadEulerAngles(FILE *in, doubleVector *E, int num)
{
	int i;
	char line[256], *tp;
	
	if (E[0].size != 3) {
		fprintf(stderr, "error: size of euler angle must be 3. In lreadEulerAngles\n");
		exit(EXIT_FAILURE);
	}

	i = 0;
	fseek(in, 0L, SEEK_SET);
	while (fgets(line, sizeof(line), in) != NULL) {

		/* ファイル名 */
		tp = strtok(line, " \t");
		/* EulerMode (YOYSのみ対応) */
		tp = strtok(NULL, " \t");

		/* EulerAngle1 */
		tp = strtok(NULL, " \t"); if (tp != NULL) E[i].data[0] = atof(tp);
		/* EulerAngle2 */
		tp = strtok(NULL, " \t"); if (tp != NULL) E[i].data[1] = atof(tp);
		/* EulerAngle3 */
		tp = strtok(NULL, " \t"); if (tp != NULL) E[i].data[2] = atof(tp);

		if (tp == NULL) {
			fprintf(stderr, "error: euler angle list format is incorrect!\n");
			exit(EXIT_FAILURE);
		}

		i++;
	}
}


void 
lprintCommonLines(FILE *out, double **C, int num)
{
	int i, j;

	for (i = 0; i < num; i++) {
		/*for (j = 0; j < num; j++) {*/
		for (j = i + 1; j < num; j++) {
			if (i == j) {
				continue;
			}
			fprintf(out, "%d\t%d\t%lf\t%lf\n", i, j, C[i][j], C[j][i]);
		}
	}
}


int
main(int argc, char* argv[]) 
{
	int num, i;
	double **C;
	doubleVector *E;	/* Euler Angle */
	doubleVector *Px, *Pz;	/* X and Z vector of projection rotation matrix */

	calcCommonLineInfo info;


	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");


	/* Get num of file */
	if (info.flagIn) {
		num = get_file_num(info.fptIn);
	} else {
		num = 2;
	}


	/* Memory allocation */

	E = (doubleVector*)malloc(sizeof(doubleVector) * num);
	if (E == NULL) {
		fprintf(stderr, "malloc error.\n");
		exit(EXIT_FAILURE);
	}

	Px = (doubleVector*)malloc(sizeof(doubleVector) * num);
	Pz = (doubleVector*)malloc(sizeof(doubleVector) * num);
	if (Px == NULL || Pz == NULL) {
		fprintf(stderr, "malloc error.\n");
		exit(EXIT_FAILURE);
	}

	C = (double**)malloc(sizeof(double*) * num);
	if (C == NULL) {
		fprintf(stderr, "malloc error.\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < num; i++) {
		C[i] = (double*)malloc(sizeof(double) * num);
		if (C == NULL) {
			fprintf(stderr, "malloc error.\n");
			exit(EXIT_FAILURE);
		}
	}

	for (i = 0; i < num; i++) {
		doubleVectorInit(&Px[i], 3);
		doubleVectorInit(&Pz[i], 3);
		doubleVectorInit(&E[i], 3);
	}

	/* Main process */
	if (info.flagIn) {
		lreadEulerAngles(info.fptIn, E, num);
	} else {
		/* R1 */
		E[0].data[0] = info.Rot1_1;
		E[0].data[1] = info.Rot1_2; 
		E[0].data[2] = info.Rot1_3;
		/* R2 */
		E[1].data[0] = info.Rot2_1;
		E[1].data[1] = info.Rot2_2;
		E[1].data[2] = info.Rot2_3;
	}
	lvectorsFromEulerAngles(E, Px, Pz, num);
	lcalcCommonLines(C, Px, Pz, num);
	lprintCommonLines(info.fptOut, C, num);


	fprintf(stderr, "Warning! This program is now for only YOYS mode and Z value was ignored.\n");


	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
