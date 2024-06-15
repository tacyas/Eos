/*
# commonLinesSearchByVoting  
# 2011/01/20
# Created by Takamasa ARAKAWA
# Usage : commonLinesSearchByVoting
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <bits/nan.h>
#include <time.h>
#include <ctype.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
//#include "rec3d.h"


#define	NEAR	5		/* コモンライン候補の位置の調整 */
#define	L	360		/* angle resolution */
#define T	(180 / 2)	/* Define T equally spaced angles between 0° and 180°: a_t = 180t/T, t=0,...,T-1 */

typedef struct CLine {
	int 	deg1;		/* angular degree of common line on projection image1 */
	int 	deg2;		/* angular degree of common line on projection image2 */
	double	cor;		/* correlation value of projection image 1 and 2 */
	char	*fname;		/* file name of correlation map of image 1 and 2 */
	double	peak;		/* peak of angular histgram */
	int	qualify;	/* qualification of correctly detected common line */
	int	rank;
} CLine;

typedef struct rank_info {
	int 	p1;	/* 投影像番号1 */
	int	p2;	/* 投影像番号2 */
	CLine	*cl;	/* 候補の配列へのポインタ */
	int	n;	/* どの候補か */
	struct rank_info *next;
	struct rank_info *prev;
} rank_info;


int
get_pnum(FILE *fpt)
{
	/* get number of projection */

	char line[1024], *tp;
	int temp = 0, num = 0;

	fseek(fpt, 0L, SEEK_SET);
	while (NULL != stringGetFromFile(line, "", fpt, stdout, 1)) {
		tp = strtok(line, " \t");
		tp = strtok(NULL, " \t");
		if (tp != NULL) {
			temp = atoi(tp);
		}
		num = (temp > num) ? temp : num;
	}

	return num + 1;
}


void
correct_en(FILE *fpt, long *en)
{
	/* check number of estimation in this file */

	char line[1024], *tp;
	int max_en, count = 0;

	fseek(fpt, 0L, SEEK_SET);
	while (NULL != stringGetFromFile(line, "", fpt, stdout, 1)) {

		if (!isdigit(line[0])) {
			continue;
		}

		tp = strtok(line, " \t");
		count = 1;

		while ((tp = strtok(NULL, " \t")) != NULL) {
			count++;
		}

		max_en = (count - 3) / 2;

		break;
	}

	if (*en > (long)max_en) {
		*en = (long)max_en;
	}
}



void
pickup_clines_from_cormap(mrcImage *cormap, CLine ***C, int p1, int p2, int en, CLine *Ctemp)
{
	/* detect common line from correlation map */

	int i, j, k, l, min, max;
	long store_flag, near_flag;
	long first_flag;
	double data, local_max_data;
	char *fname;

	/* initialization ("-1000" has no meaning) */
	for (k = 0; k < en; k++) {
		C[p1][p2][k].cor = -1000;
		C[p1][p2][k].deg1 = -1000;
		C[p1][p2][k].deg2 = -1000;
	}

	fname = C[p1][p2][0].fname;
	mrcFileRead(cormap, fname, "in pickup_clines_from_cormap", 0);

	for (i = 0; i < L/2; i += NEAR) {
	 for (j = 0; j < L; j += NEAR) {

		first_flag = 1;
		for (k = 0; k < NEAR && i+k < L/2; k++) {
		 for (l = 0; l < NEAR && j+l < L; l++) {

			mrcPixelDataGet(cormap, i+k, j+l, 0, &data, mrcPixelRePart, mrcPixelHowNearest);

			if (isnan(data)) {
				continue;
			}

			if (first_flag) {
				local_max_data = data;
				first_flag = 0;
				continue;
			}

			if (data > local_max_data) {
				local_max_data = data;
			}

		 }
		}
		data = local_max_data;

		// common line is estimated by the number of en(estimation number)
		store_flag = 0;
		for (k = 0; k < en; k++) {
			if (data + 1 > C[p1][p2][k].cor) {
				store_flag = 1;
				break; 
			}
		}
		if (store_flag) {
			min = 0;
			for (k = 1; k < en; k++) {
				if (C[p1][p2][min].cor > C[p1][p2][k].cor) {
					min = k;
				}
			}
			C[p1][p2][min].deg1 = C[p2][p1][min].deg2 = i;
			C[p1][p2][min].deg2 = C[p2][p1][min].deg1 = j;
			C[p1][p2][min].cor  = C[p2][p1][min].cor  = data + 1;
		}

	 }
	}
	max = 0;
	for (k = 1; k < en; k++) {
		if (C[p1][p2][k].cor > C[p1][p2][max].cor) {
			max = k;
		}
	}
	if (max != 0) {
		*Ctemp         = C[p1][p2][0];
		C[p1][p2][0]   = C[p1][p2][max];
		C[p1][p2][max] = *Ctemp;
	}
	C[p1][p2][0].fname = fname;

	mrcImageFree(cormap, "in pickup_clines_from_cormap");
}


void
read_clines_maps(FILE *fpt, CLine ***C, int pnum, int en) 
{
	char line[1024], *tp;
	int p1, p2, count;
	mrcImage cormap;
	CLine Ctemp;

	fprintf(stderr, "file reading.");

	count = 0;
	fseek(fpt, 0L, SEEK_SET);
	while (NULL != stringGetFromFile(line, "", fpt, stdout, 1)) {

		/* get projection number */
		if ((tp = strtok(line, " \t")) != NULL) p1 = atoi(tp);
		if ((tp = strtok(NULL, " \t")) != NULL) p2 = atoi(tp);
		if ((tp = strtok(NULL, " \t")) != NULL) {
			C[p1][p2][0].fname = (char*)memoryAllocate(sizeof(char)*(strlen(tp)+1), "");
			strcpy(C[p1][p2][0].fname, tp);
			C[p2][p1][0].fname = C[p1][p2][0].fname;
		} else {
			fprintf(stderr, "ERROR! Map list format is incorrect!\n");
			fprintf(stderr, "format: p1\tp2\t[deg1\tdeg2\tcor]\tmapname\n");
			exit(EXIT_FAILURE);
		}

		/* read cormap, and pick up common lines */
		pickup_clines_from_cormap(&cormap, C, p1, p2, en, &Ctemp);

		if (++count % 1000 == 0) {
			fprintf(stderr, ".");
		}
	}
}


void
read_clines_file(FILE *fpt, CLine ***C, int pnum, int en) 
{
	char line[1024], *tp;
	int i;
	int p1, p2;

	fseek(fpt, 0L, SEEK_SET);
	while (NULL != stringGetFromFile(line, "", fpt, stdout, 1)) {

		if (!isdigit(line[0])) continue;

		if ((tp = strtok(line, " \t")) != NULL) p1 = atoi(tp);
		if ((tp = strtok(NULL, " \t")) != NULL) p2 = atoi(tp);

		if (p1 >= pnum || p2 >= pnum) continue;

		for (i = 0; i < en; i++) {
			if ((tp = strtok(NULL, " \t")) != NULL) C[p1][p2][i].deg1 = C[p2][p1][i].deg2 = atoi(tp);
			if ((tp = strtok(NULL, " \t")) != NULL) C[p1][p2][i].deg2 = C[p2][p1][i].deg1 = atoi(tp);
			if ((tp = strtok(NULL, " \t")) != NULL) C[p1][p2][i].cor  = C[p2][p1][i].cor  = atof(tp);
		}

		if ((tp= strtok(NULL, " \t")) != NULL) {
			C[p1][p2][0].fname = (char*)memoryAllocate(sizeof(char)*(strlen(tp)+1), "");
			strcpy(C[p1][p2][0].fname, tp);
			for (i = 1; i < en; i++) {
				C[p1][p2][i].fname = C[p1][p2][0].fname;
			}
		}

		if (tp == NULL) {
			fprintf(stderr, "ERROR! Common lines list format is incorrect!\n");
			fprintf(stderr, "format: p1\tp2\t[deg1\tdeg2\tcor]\tmapname\n");
			exit(EXIT_FAILURE);
		}
	}
}


void
print_clines(FILE *fpt, CLine ***C, int num, int en)
{
	int i, j, k;

	fprintf(fpt, "p1\tp2\t[deg1\tdeg2\tcor]\tmapname\n");

	for (i = 0; i < num; i++) {
		for (j = i + 1; j < num; j++) {

			fprintf(fpt, "%d\t%d\t", i, j);
			for (k = 0; k < en; k++) {
				fprintf(fpt, "%d\t%d\t%lf\t", C[i][j][k].deg1, C[i][j][k].deg2, C[i][j][k].cor);
			}
			fprintf(fpt, "%s\n", C[i][j][0].fname);
		}
	}
}


void
clear_histgram(double *histgram, int n)
{
	int i;

	for (i =0 ; i < n; i++) {
		histgram[i] = 0.0;
	}
}


double
peak_of_histgram(double *histgram, int n)
{
	int i, peak = 0;

	for (i = 1; i < n; i++) {
		if (histgram[i] > histgram[peak]) {
			peak = i;
		}
	}

	return histgram[peak];
}


void 
write_histgram(FILE *fpt, double *histgram, int n, int max)
{
	int i;

	for (i = 0; i < n; i++) {
		fprintf(fpt, "%lf\t%lf\n", (double)max * i / n, histgram[i]);
	}
}


FILE*
fopen_for_histgram(char *fname, char *temp1, char *temp2)
{
	FILE* fpt;
	int i;

	strcpy(temp1, fname);
	for (i = strlen(temp1); i >= 0; i--) {
		if (temp1[i] == '.') {
			temp1[i] = '\0';
		}
	}
	sprintf(temp2, "%s.hist", temp1);

	fpt = fopen(temp2, "w");
	if (fpt == NULL) {
		fprintf(stderr, "err fopen\n");
		exit(EXIT_FAILURE);
	}

	return fpt;
}


void 
create_peak_histgram(double *peak_histgram, rank_info *rank, int N, int div, int max_peak)
{
	int p1, p2, n;
	rank_info *current;

	if (max_peak == 0) {
		return;
	}

	clear_histgram(peak_histgram, div);

	current = rank->next;
	while (current != NULL) {
		p1 = current->p1;
		p2 = current->p2;
		n  = current->n;

		if (div > (int)(div * current->cl[n].peak / max_peak)) {
			peak_histgram[(int)(div * current->cl[n].peak / max_peak)]++;
		}

		current = current->next;
	}
}


double 
create_angle_histgram(double *angle_histgram, CLine ***C, int N, int l, int k1, int k2)
{
	int k3, flag, t;
	double a, b, c, val, peak;
	double a_12, a_t, sig, cos_a_12;

	for (k3 = 0; k3 < N; k3++) {

		if (k1 == k3 || k2 == k3) {
			continue;
		}

		/* Compute a, b and c */
		a = cos(2 * M_PI * (C[k3][k2][0].deg1 - C[k3][k1][0].deg1) / l);
		b = cos(2 * M_PI * (C[k2][k3][0].deg1 - C[k2][k1][0].deg1) / l);
		c = cos(2 * M_PI * (C[k1][k3][0].deg1 - C[k1][k2][0].deg1) / l);

		/* Check of realizable on the sphere */
		if (!(1 + 2*a*b*c > a*a + b*b + c*c)) {
			continue;
		}

		/* Compute a_12 (note: acos() returns radian value. so transform to degree) */
		cos_a_12 = (a - b*c) / (sqrt(1 - b*b) * sqrt(1 - c*c));
		if (fabs(cos_a_12) > 1) {
			continue;
		}
		a_12 = acos(cos_a_12) * 180.0 / M_PI;


		/* Update the histgram (angle_histgram) using Gaussian smoothing */
		for (t = 0; t < T; t++) {
			sig = 180.0 / T;
			a_t = 180.0 * t / T;
			val = exp(-(a_t - a_12)*(a_t - a_12) / (2*sig*sig)) / sqrt(2*M_PI * sig*sig);
			if (!isnan(val)) {
				angle_histgram[t] += val;
			}
		}

	}


	/* Find and store the mode of the histgram: peaks(k1, k2) = max_t angle_histgram[t] */
	peak = peak_of_histgram(angle_histgram, T);

	return peak;
}


double
create_all_angle_histgram(CLine ***C, int N, int l, double ***angle_histgram, long histgramCreateFlag, int mode) 
{
	int i, j;
	int k1, k2, k3;
	double max_peak;
	char temp[256], fname[256];
	FILE *fpt;

	max_peak = 0;

	for (k1 = 0; k1 < N; k1++) {
		for (k2 = k1 + 1; k2 < N; k2++) {

			/* Initialize the histgram vector angle_histgram of length T to zero */
			clear_histgram(angle_histgram[k1][k2], T);


			C[k1][k2][0].peak = create_angle_histgram(angle_histgram[k1][k2], C, N, l, k1, k2);

			if (mode == 1) {
				/* self voting */
				C[k1][k2][0].peak *= C[k1][k2][0].cor;
			}

			if (histgramCreateFlag) {
				fpt = fopen_for_histgram(C[k1][k2][0].fname, temp, fname);
				write_histgram(fpt, angle_histgram[k1][k2], T, 180.0);
				fclose(fpt);
			}

			fprintf(stdout, "C(%4d,%4d)\t%lf\n", k1, k2, C[k1][k2][0].peak);

			if (C[k1][k2][0].peak > max_peak) {
				max_peak = C[k1][k2][0].peak;
			}

		}
	}

	return max_peak;
}


void 
voting_extended(CLine ***C, rank_info *rank, rank_info **middle, int N, int l, int en, long histgramCreateFlag, int mode) 
{
	/* 投票アルゴリズムの拡張 */

	int div = N/2; /* division number of peak histgram */

	int i, j, p1, p2, n, middle_num;
	double *angle_histgram, max_peak;
	CLine Ctemp;
	rank_info *current, *current2, *prev_temp;

	// for debug
	//int flag, cnt;
	//rank_info *curr;
	//cnt=0;curr=rank->next;while(curr!=NULL){curr=curr->next;cnt++;}fprintf(stderr,"< %d >",cnt);
	//cnt=0;curr=rank->prev;while(curr!=rank){curr=curr->prev;cnt++;}fprintf(stderr,"< %d >\n",cnt);


	if (en == 1) {
		return;
	}


	angle_histgram = (double*)malloc(sizeof(double) * T);
	if (angle_histgram == NULL) {
		fprintf(stderr, "malloc error: in voting_extended\n");
		exit(EXIT_FAILURE);
	}


	middle_num = 0;
	current = rank->prev;
	do {

		p1 = current->p1;
		p2 = current->p2;

		prev_temp = current->prev;

		max_peak = current->cl[0].peak;


		for (n = 1; n < en; n++) {

			// 候補を入れ替える
			Ctemp        = C[p1][p2][0];
			C[p1][p2][0] = C[p1][p2][n];
			C[p1][p2][n] = Ctemp;

			// Initialize the histgram vector angle_histgram of length T to zero
			clear_histgram(angle_histgram, T);

			current->cl[0].peak = create_angle_histgram(angle_histgram, C, N, l, p1, p2);

			if (mode == 1) {
				/* self voting */
				current->cl[0].peak *= current->cl[0].cor;
			}

			// 候補を戻す
			Ctemp        = C[p1][p2][0];
			C[p1][p2][0] = C[p1][p2][n];
			C[p1][p2][n] = Ctemp;


			//if (current->cl[n].peak > max_peak && current->cl[n].peak > middle[middle_num]->cl[0].peak) {
			if (current->cl[n].peak > max_peak && current->cl[n].peak > middle[1]->cl[0].peak) {

				current2 = current->prev;

				while (current2 != rank) {

					if (current2->cl[current2->n].peak >= current->cl[n].peak) {
						// bottomの場合の処理
						if (rank->prev == current) rank->prev = current->prev;
						// 切り離し
						if (current->prev != NULL) current->prev->next = current->next;
						if (current->next != NULL) current->next->prev = current->prev;
						// 新しいprevとnext
						current->prev = current2;
						current->next = current2->next;
						// 挿入
						if (current2->next != NULL) current2->next->prev = current;
						current2->next = current;

						break;
					}

					current2 = current2->prev;
				}
				if (current2 == rank) {
					// 切り離し
					if (current->prev != NULL) current->prev->next = current->next;
					if (current->next != NULL) current->next->prev = current->prev;
					// 新しいprevとnext
					current->prev = rank;
					current->next = rank->next;
					// 挿入
					rank->next->prev = current;
					rank->next       = current;
				}

				// ランキングの更新 
				current->n = n;
				max_peak = current->cl[n].peak;
			}
		}

		if (current == middle[middle_num]) {
			if (middle_num + 1 < (int)(log((N*N-N)/2)/log(2))) {
				middle_num++;
			}
			//if (middle_num == 1) break;
		}

		fprintf(stdout, "C(%4d,%4d)\t%lf\n", p1, p2, current->cl[current->n].peak);

		current = prev_temp;

	} while (current->prev != rank);

}


void
voting(CLine ***C, int N, int l, int en, double *_max_peak, long histgramCreateFlag, int mode) 
{
	/* C is N*N common lines matrix */
	/* L is angular resolution number of sinogram line (case of Eos: 360) */

	//int div = N/2; /* division number of peak histgram */
	
	int i, j;
	int k1, k2, k3;
	int n;
	double ***angle_histgram, max_peak;

	FILE *fpt;
	char fname[256], temp[256];


	angle_histgram = (double***)malloc(sizeof(double**) * N);
	if (angle_histgram == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < N; i++) {
		angle_histgram[i] = (double**)malloc(sizeof(double*) * N);
		if (angle_histgram[i] == NULL) {
			fprintf(stderr, "malloc error\n");
			exit(EXIT_FAILURE);
		}
		for (j = 0; j < N; j++) {
			angle_histgram[i][j] = (double*)malloc(sizeof(double) * T);
			if (angle_histgram[i][j] == NULL) {
				fprintf(stderr, "malloc error\n");
				exit(EXIT_FAILURE);
			}
		}
	}


	max_peak = create_all_angle_histgram(C, N, l, angle_histgram, histgramCreateFlag, mode);


	*_max_peak = max_peak;
}


/* qsort()のための比較関数(降順) */
int compare_peak(const void *c1, const void *c2)
{
	rank_info temp1 = *(rank_info*)c1;
	rank_info temp2 = *(rank_info*)c2;
	int ret = (temp2.cl[0].peak - temp1.cl[0].peak > 0) ? 1 : -1;

	return ret;
}


// 2011/02/04
void 
ranking_clines(CLine ***C, int num, rank_info *rank, rank_info **middle)
{
	int  i, j, max_i, max_j;
	long k;
	long flag, max_num;
	rank_info *current;
	
	int *middle_val, middle_num;
	rank_info *rank_array;

	fprintf(stderr, "commonlines ranking.");


	/* initialization */
	for (i = 0; i < num; i++) {
		for (j = 0; j < num; j++) {
			C[i][j][0].rank = -1;
		}
	}

	max_num = num * (num - 1) / 2;

	middle_num = (int)(log(max_num)/log(2));
	middle_val = (int*)malloc(sizeof(int) * middle_num);
	middle_val[middle_num - 1] = 0;
	for (i = middle_num - 2; i >= 0; i--) {
		middle_val[i] = max_num / pow(2, i + 1);
	}


	/* ソートのため1次元配列を作成 */
	rank_array = (rank_info*)malloc(sizeof(rank_info) * max_num);
	if (rank_array == NULL) {
		fprintf(stderr, "malloc error: in ranking_clines");
	}

	k = 0;
	for (i = 0; i < num; i++) {
		for (j = i + 1; j < num; j++) {
			rank_array[k].p1 = i;
			rank_array[k].p2 = j;
			rank_array[k].cl = C[i][j];
			k++;
		}
	}

	/* 全コモンラインのpeakを基準に降順にソート */
	qsort(rank_array, max_num, sizeof(rank_info), compare_peak);


	current = rank;
	for (k = 0; k < max_num; k++) {

		current->next = (rank_info*)malloc(sizeof(rank_info));
		if (current->next == NULL) {
			fprintf(stderr, "malloc error: in ranking_clines\n");
			exit(EXIT_FAILURE);
		}

		current->next->p1   = rank_array[k].p1;
		current->next->p2   = rank_array[k].p2;
		current->next->cl   = rank_array[k].cl;
		current->next->n    = 0;
		current->next->next = NULL;
		current->next->prev = current;

		current = current->next;

		if (k == middle_val[middle_num - 1]) {
			middle[middle_num - 1] = current;
			middle_num--;
		}

		if (k % 10000 == 0) {
			fprintf(stderr, ".");
		}
	}

	rank->prev = current;	/* 先頭のprevにはリストの最後の番地を格納 */

	free(rank_array);
}


void 
read_correct_clines(FILE *fpt, CLine **cC, int num)
{
	int count, i;
	int p1, p2;
	char line[256], *tp;

	count = 0;
	fseek(fpt, 0L, SEEK_SET);
	while (NULL != stringGetFromFile(line, "", fpt, stdout, 1)) {

		if (!isdigit(line[0])) continue;

		if ((tp = strtok(line, " \t")) != NULL) p1 = atoi(tp);
		if ((tp = strtok(NULL, " \t")) != NULL) p2 = atoi(tp);
		if ((tp = strtok(NULL, " \t")) != NULL) cC[p1][p2].deg1 = cC[p2][p1].deg2 = atoi(tp);
		if ((tp = strtok(NULL, " \t")) != NULL) cC[p1][p2].deg2 = cC[p2][p1].deg1 = atoi(tp);

		if (tp == NULL) {
			fprintf(stderr, "ERROR! Correct Common lines list format is incorrect!\n");
			fprintf(stderr, " format: p1\tp2\tdeg1\tdeg2\n");
			exit(EXIT_FAILURE);
		}

		count++;
		if (count > num * (num - 1)) {
			fprintf(stderr, "ERROR! Correct Common lines's number is over ");
			fprintf(stderr, "num*(num-1): %d!\n", num*(num-1));
			exit(EXIT_FAILURE);
		}
	}

	if (count != num * (num - 1) / 2) {
		fprintf(stderr, "Warning! Correct Common lines's number %d is not num*(num-1)/2=%d.\n", count, num*(num-1)/2);
	}
}


void
print_clines_by_rank(FILE *fpt, rank_info *rank, int num)
{
	int p1, p2, n;
	rank_info *current;

	fprintf(fpt, "p1\tp2\tdeg1\tdeg2\tpeak\tmapname\n");

	current = rank->next;
	while (current != NULL) {
		p1 = current->p1;
		p2 = current->p2;
		n  = current->n;

		fprintf(fpt, "%d\t%d\t", p1, p2);
		fprintf(fpt, "%d\t%d\t%lf\t", current->cl[n].deg1, current->cl[n].deg2, current->cl[n].peak);
		fprintf(fpt, "%s\n", current->cl[0].fname);

		current = current->next;
	}
}


void
calc_detecting_rate(rank_info *rank, CLine **cC, int pnum, double *detecting_rate)
{
	int err = 10;
	long i, j, p1, p2, n;
	long correct_num, total_num, range, count;
	rank_info *current;


	total_num = pnum * (pnum - 1) / 2;

	count = 0;
	correct_num = 0;
	current = rank->next;
	while (current != NULL) {

		if (count >= total_num) {
			fprintf(stderr, "list is bad. let's debug!\n");
			fprintf(stderr, "count: %ld\n", count);
			break;
		}

		p1 = current->p1;
		p2 = current->p2;
		n  = current->n;

		if (abs(cC[p1][p2].deg1 - current->cl[n].deg1) <= err && abs(cC[p1][p2].deg2 - current->cl[n].deg2) <= err) {
			correct_num++;
		}

		detecting_rate[count] = (double)correct_num / (double)(count+1) * 100;

		current = current->next;
		count++;
	}
}


void
calc_detecting_rate_all(rank_info *rank, CLine **cC, int pnum, double *detecting_rate, int en)
{
	int err = 10;
	long i, j, p1, p2, n;
	long correct_num, total_num, range;
	long count;
	rank_info *current;


	total_num = pnum * (pnum - 1) / 2;

	count = 0;
	correct_num = 0;
	current = rank->next;
	while (current != NULL) {

		if (count >= total_num) {
			fprintf(stderr, "list is bad. let's debug!\n");
			fprintf(stderr, "count: %ld\n", count);
			break;
		}

		p1 = current->p1;
		p2 = current->p2;
		n  = current->n;

		for (n = 0; n < en; n++) {
		
			if (abs(cC[p1][p2].deg1 - current->cl[n].deg1) <= err 
			 && abs(cC[p1][p2].deg2 - current->cl[n].deg2) <= err) {
				correct_num++;
				break;
			}
		}

		detecting_rate[count] = (double)correct_num / (double)(count+1) * 100;

		current = current->next;
		count++;
	}
}


void
print_detecting_rate(FILE *fpt, double *detecting_rate, int n)
{
	int i;

	fprintf(fpt, "TopPercentile[%%]\tDetectingRate[%%]\n");
	for (i = 0; i < n; i++) {
		fprintf(fpt, "%lf\t%lf\n", (double)(i+1)/(double)n * 100, detecting_rate[i]);
	}
}


void
lcommonLinesSearchByVoting(commonLinesSearchByVotingInfo* info)
{
	int div;

	CLine ***C, **cC;
	CLine Ctemp;
	rank_info rank, **middle;
	int max_value, pnum;
	int i, j;

	double	*detecting_rate;	// 各順位における検出率
	double *peak_histgram;
	double max_peak;

	int p1, p2, n;


	/* get num of projection from input list file */
	if (info->flagIn) {
		pnum = get_pnum(info->fptIn);
	} else if (info->flagInC) {
		pnum = get_pnum(info->fptInC);
	}
	if (info->flagInC) {
		correct_en(info->fptInC, &(info->en));
	}
	fprintf(stdout, "N = %d\n", pnum);

	div = pnum / 2;

	/*** memory allocation ***/
	C = (CLine***)malloc(sizeof(CLine**) * pnum);
	cC = (CLine**)malloc(sizeof(CLine*) * pnum);
	if (C == NULL || cC == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < pnum; i++) {
		C[i] = (CLine**)malloc(sizeof(CLine*) * pnum);
		cC[i] = (CLine*)malloc(sizeof(CLine) * pnum);
		if (C[i] == NULL || cC[i] == NULL) {
			fprintf(stderr, "malloc error\n");
			exit(EXIT_FAILURE);
		}
		for (j = 0; j < pnum; j++) {
			C[i][j] = (CLine*)malloc(sizeof(CLine) * info->en);
			if (C[i][j] == NULL) {
				fprintf(stderr, "malloc error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	peak_histgram = (double*)malloc(sizeof(double) * div);
	if (peak_histgram == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}
	middle = (rank_info**)malloc(sizeof(rank_info*) * (int)(log(pnum*(pnum-1)/2)/log(2)));
	if (middle == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(EXIT_FAILURE);
	}
	detecting_rate = (double*)malloc(sizeof(double) * pnum*(pnum-1)/2);


	/* read files in inputList and store into common lines matrix */
	if (info->flagInC) {
		read_clines_file(info->fptInC, C, pnum, info->en);

	} else {
		read_clines_maps(info->fptIn, C, pnum, info->en);
	}

	fprintf(stdout, "File Reading OK\n");


	/* output all common lines matrix */
	if (info->flagOutA) {
		print_clines(info->fptOutA, C, pnum, info->en);
	}


	/* create angle histgram by voting */
	voting(C, pnum, L, info->en, &max_peak, info->histgramCreateFlag, info->mode);
	fprintf(stdout,"Voting OK\n");


	/* declare pairs (k1, k2) with large values of peaks (k1, k2) as good common lines */

	ranking_clines(C, pnum, &rank, middle);
	fprintf(stdout, "Common Lines Ranking OK\n");


	/* extended voting */
	if (info->extendVotingFlag) {
		voting_extended(C, &rank, middle, pnum, L, info->en, info->histgramCreateFlag, info->mode);
		fprintf(stdout, "Extended Voting OK\n");
	}

	/* create peak histgram */
	if (info->flagOutPH) {
		create_peak_histgram(peak_histgram, &rank, pnum, div, max_peak);
		write_histgram(info->fptOutPH, peak_histgram, div, max_peak);
	}

	/* read correct common lines file, and print correctly detecting rate */
	if (info->flagInCC) {
		read_correct_clines(info->fptInCC, cC, pnum);
		print_clines_by_rank(info->fptOut, &rank, pnum);
		if (info->flagOutDR) {
			calc_detecting_rate(&rank, cC, pnum, detecting_rate);
			print_detecting_rate(info->fptOutDR, detecting_rate, pnum*(pnum-1)/2);
		}
		if (info->flagOutDRA) {
			calc_detecting_rate_all(&rank, cC, pnum, detecting_rate, info->en);
			print_detecting_rate(info->fptOutDRA, detecting_rate, pnum*(pnum-1)/2);
		}
	}	
}


int
main(int argc, char* argv[]) 
{
	commonLinesSearchByVotingInfo info;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");

	lcommonLinesSearchByVoting(&info);

	exit(EXIT_SUCCESS);
}


void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Common lines are filtered only top G*100/sqrt(N) %%, where N is the number of projections.\n");

	fprintf(stderr, "-extend Option \n");
	fprintf(stderr, "    Execute extended voting.\n");

	fprintf(stderr, "-m Option \n");
	fprintf(stderr, "    0: normal\n");
	fprintf(stderr, "    1: self voting (each angle histgram peak is multiplyed by its correlation value)\n");

	fprintf(stderr, "-th Option \n");
	fprintf(stderr, "    : \n");
	fprintf(stderr, "   -1: G = 2^(-1) \n");
	fprintf(stderr, "    0: G = 2^0 \n");
	fprintf(stderr, "    1: G = 2^1 \n");
	fprintf(stderr, "    2: G = 2^2 \n");
	fprintf(stderr, "    : \n");
	
	fprintf(stderr, "-en Option \n");
	fprintf(stderr, "    Estimation number of common line in a map. \n");
	fprintf(stderr, "    Running time is proportional to this number.\n");
	fprintf(stderr, "    Default; 1: the largest value in a correlation map is detected as common line.\n");

	fprintf(stderr, "MapList Format\n");
	fprintf(stderr, "    numOfProjection1 numOfProjection2 mapFileName\n");
	fprintf(stderr, "           :                :              :     \n");

	fprintf(stderr, "CLinesList Format\n");
	fprintf(stderr, "    numOfProjection1 numOfProjection2 [ degOfProjection1 degOfProjection2 degDiff cor ] mapFileName\n");
	fprintf(stderr, "           :                :                 :                :            :      :         :     \n");

	fprintf(stderr, "Voting Algorithm by Amit Singer et al (2010),\n");
	fprintf(stderr, "\"Detecting consistent common lines in cryo-EM by voting \" (doi:10.1016/j.jsb.2009.11.003)\n");
	fprintf(stderr, "----------------------------\n");
}
