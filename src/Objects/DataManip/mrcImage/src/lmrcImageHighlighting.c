/*
# lmrcImageHighlighting.c  1.3
# The latest update : 06/21/96 at 23:58:31
#
#@(#) lmrcImageHighlighting Function ver 1.3
#@(#) Created by Isao Sakane May 1, 1996.
#@(#)
#@(#) Usage : lmrcImageHighlighting(mrcImage* dst, mrcImage* src, lmrcImageCVEInfo* info)
#@(#) Attention
#@(#)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/mrcImage.h"
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"

typedef struct
{
	double min, max, mean, deviation;
}	StatData;

typedef struct
{
	float value, min, max, step;
} AxisInfo;

enum service
{
	NO_OPERATION = 0,
	ARCTAN = 1,
	OUT_OF_ORDER
};

static const double pi = 3.14159265358979323846264;
static double (*Highlight)(lmrcImageHighlightInfo* info, StatData *population, double value);
static double HighlightByArcTan(lmrcImageHighlightInfo *Info, StatData *population, double value);
static StatData getStatDataOfWhole(mrcImage* src);
static void isGoodInfo(lmrcImageHighlightInfo* info);

void 
lmrcImageHighlightingInfoPrint(FILE* fpt) 
{
	fprintf(fpt, "---- lmrcImageHighlightInfo ----");
	fprintf(fpt, "mode:");
	fprintf(fpt, "\t0:No Operation \n");
	fprintf(fpt, "\t1:ArcTan Filter\n");
	fprintf(fpt, "\t2:Histgram Equalization\n");
	fprintf(fpt, "Bias");
	fprintf(fpt, "Grad");
}

void lmrcImageHighlighting(mrcImage* dst, mrcImage* src, lmrcImageHighlightInfo* info)
{
	StatData population;
	AxisInfo x, y, z;
	double from, to;
	
	isGoodInfo(info);

	dst->Header = src->Header;
	mrcInit(dst, NULL);	
	
	/* For all data points in src. */
	x.min = y.min = z.min = 0.0;
	x.max = src->HeaderN.x - 1.0;
	y.max = src->HeaderN.y - 1.0;
	z.max = src->HeaderN.z - 1.0;
	x.step = y.step = z.step = 1.0;

	/* Get the standard mean and deviation. */
	population = getStatDataOfWhole(src);
	for(z.value = z.min; z.value <= z.max; z.value += z.step)
	{
		for(y.value = y.min; y.value <= y.max; y.value += y.step)
		{
			for(x.value = x.min; x.value <= x.max; x.value += x.step)
			{
				mrcPixelDataGet(src, x.value, y.value, z.value, &from, mrcPixelMag, mrcPixelHowNearest);
				to = Highlight(info, &population, from);
				mrcPixelDataSet(dst, x.value, y.value, z.value, to, mrcPixelMag);
			}
		}
	}
}

void isGoodInfo(lmrcImageHighlightInfo* info)
{
	switch(info->mode)
	{
	case ARCTAN:
		Highlight = &HighlightByArcTan;
		break;
	default:
		fprintf(stderr, "Not supported mode: m = %ld\n", info->mode);
		exit(EXIT_FAILURE);
	}
}

StatData getStatDataOfWhole(mrcImage* src)
{
	StatData ret;
	mrcImageInformation info;

	info.mode = meanOfAll;
	lmrcImageInformation(&info, src);
	ret.max = info.max;
	ret.min = info.min;
	ret.mean = info.mean;
	ret.deviation = info.sd;

	return ret;
}

double HighlightByArcTan(lmrcImageHighlightInfo *info, StatData *population, double value)
{
	return atan(((value - population->mean) / population->deviation - info->Bias) / info->Grad) * (population->max - population->min) / pi + population->mean;
}
