/*
# mrcImageNLMeansFilter : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageNLMeansFilter
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
#include "mrcImage.h"


// N枠内の差の絶対値の和を計算
float get_sad(float **inPix, point i, point j, point imgSize, point nSize) {

	point sig;	// 枠内の番号
	float sad = 0;	// 差の絶対値の合計
	float diff;

	for (sig.x = -nSize.x/2; sig.x < nSize.x - nSize.x/2; sig.x++) {

		if (0 > i.x + sig.x || i.x + sig.x >= imgSize.x || 
		    0 > j.x + sig.x || j.x + sig.x >= imgSize.x ) {
			continue;
		}

		for (sig.y = -nSize.y/2; sig.y < nSize.y - nSize.y/2; sig.y++) {

			if (0 > i.y + sig.y || i.y + sig.y >= imgSize.y || 
			    0 > j.y + sig.y || j.y + sig.y >= imgSize.y ) {
				continue;
			}

			diff = (float)(inPix[i.x + sig.x][i.y + sig.y] - inPix[j.x + sig.x][j.y + sig.y]);
			sad += diff * diff;

		}
	}

	return sad;
}


void mrcImageNLmeansFilter(mrcImage *in, mrcImage *out, mrcImageNLMeansFilterInfo info) {

	float **inPix, **outPix;	// 入力・出力のピクセル値の配列
	float **w;			// 各ピクセルの重み
	float total_w;			// 重みの合計
	double datum;

	point i, j, imgSize, nSize;
	int count;
	float hParam;
	float sad, weight, pixel;	// 差の絶対値の和，重み，フィルタ適用後のピクセル値


	imgSize.x = in->HeaderN.x;
	imgSize.y = in->HeaderN.y;
	nSize.x = nSize.y = info.Nsize;


	// ヘッダのコピーと初期化
	out->Header = in->Header;
	mrcInit(out, NULL);


	// メモリ確保
	inPix  = (float**)malloc(sizeof(float*) * imgSize.x);
	outPix = (float**)malloc(sizeof(float*) * imgSize.x);
	w      = (float**)malloc(sizeof(float*) * imgSize.x);
	if (inPix == NULL || outPix == NULL || w == NULL) {
		fprintf(stderr, "mem allocation err\n");
		exit(EXIT_FAILURE);
	}
	for (i.x = 0; i.x < imgSize.x; i.x++) {
		*(inPix  + i.x) = (float*)malloc(sizeof(float) * imgSize.y);
		*(outPix + i.x) = (float*)malloc(sizeof(float) * imgSize.y);
		*(w      + i.x) = (float*)malloc(sizeof(float) * imgSize.y);
		if (*(inPix + i.x) == NULL || *(outPix + i.x) == NULL || *(w + i.x) == NULL) {
			fprintf(stderr, "mem allocation err\n");
			exit(EXIT_FAILURE);
		}
	}

	// ピクセル値の取り出しと正規化
	for (i.x = 0; i.x < imgSize.x; i.x++) {
	for (i.y = 0; i.y < imgSize.y; i.y++) {
		mrcPixelDataGet(in, i.x, i.y, 0.0, &datum, mrcPixelRePart, mrcPixelHowNearest);
		inPix[i.x][i.y] = (float)((datum - in->HeaderAMin) / in->HeaderAMax);
	}
	}

	// フィルタリングパラメータ
	hParam = info.hParam;

/*
	// ピクセル値の取り出し
	for (i.x = 0; i.x < imgSize.x; i.x++) {
	for (i.y = 0; i.y < imgSize.y; i.y++) {
		mrcPixelDataGet(in, i.x, i.y, 0.0, &datum, mrcPixelRePart, mrcPixelHowNearest);
		inPix[i.x][i.y] = (float)datum;
	}
	}

	// フィルタリングパラメータの調整
	hParam = (info.hParam * in->HeaderAMax) + in->HeaderAMin;
*/

	count = 0;

	for (i.x = 0; i.x < imgSize.x; i.x++) {
	for (i.y = 0; i.y < imgSize.y; i.y++) {

		total_w = 0;

		for (j.x = 0; j.x < imgSize.x; j.x++) {
		for (j.y = 0; j.y < imgSize.y; j.y++) {

			// 枠内の各ピクセルの差の絶対値の和
			sad = get_sad(inPix, i, j, imgSize, nSize);

			// 類似度による重みを計算
			weight = exp(-sad / (hParam * hParam));
			w[j.x][j.y] = weight;

//fprintf(stderr, "sad: %f\n", sad);
//fprintf(stderr, "weight: %f\n", weight);

			// 正規化のための重みの合計値
			total_w += weight;
		}
		}

//fprintf(stderr, "total_w: %f\n", total_w);

		pixel = 0;

		for (j.x = 0; j.x < imgSize.x; j.x++) {
		for (j.y = 0; j.y < imgSize.y; j.y++) {

			// 重みを正規化
			w[j.x][j.y] /= total_w;

			// ピクセル値を計算
			pixel += w[j.x][j.y] * inPix[j.x][j.y];

		}
		}

		// 適用後の画像にピクセル値を格納
		outPix[i.x][i.y] = pixel;

		if (++count % 1000 == 0) {
			fprintf(stdout, "%5d / %5d pixel completed (%.1f%%). total_w: %f\n", count, imgSize.x * imgSize.y, (float)count / (imgSize.x * imgSize.y) * 100, total_w);
		}

	}
	}


	// ピクセル値の格納
	for (i.x = 0; i.x < imgSize.x; i.x++) {
	for (i.y = 0; i.y < imgSize.y; i.y++) {
		mrcPixelDataSet(out, i.x, i.y, 0.0, outPix[i.x][i.y], mrcPixelRePart);
	}
	}

	mrcStatDataSet(out, 0);
}

int
main(int argc, char* argv[]) 
{
	mrcImageNLMeansFilterInfo info;
	mrcImage in, out;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "in main", 0);

	mrcImageNLmeansFilter(&in, &out, info);

	mrcFileWrite(&out, info.Out, "in main" , 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
