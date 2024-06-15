/*
# lmrcImageTfunction.c  1.1
# The latest update : 06/17/96 at 18:21:35
#
#@(#) mrcImageTfunction ver 1.1
#@(#) Created by Isao Sakane
#@(#)
#@(#) Usage : lmrcImageTfunction
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)lmrcImageTfunction ver1.1; Date:96/06/17 @(#)";

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/mrcImage.h"
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"

/* Data type to contain statical data. */
typedef struct
{
	double n, mean, deviation;
}	StatData;

/* Data type to contain axis restriction and information for axis handling. */
typedef struct
{
	float value, min, max, step;
} AxisInfo;

typedef enum {xyz, yzx, zxy} Order;

extern void lmrcImageTfunction(mrcImage* dst, mrcImage* src, lmrcImageTfunctionInfo* info, long mode);

/* Internal functions. */
static void isGoodInfo(lmrcImageTfunctionInfo* info);
static StatData getStatDataOfWhole(mrcImage* src, AxisInfo *x, AxisInfo *y, AxisInfo *z);
static StatData getLocalStatData(mrcImage* src, lmrcImageTfunctionInfo *info, AxisInfo *x, AxisInfo *y, AxisInfo *z);
static void getDataOn_yz(mrcImage* src, AxisInfo *ax, AxisInfo *ay, AxisInfo *az, int *n, double *x, double *x2);
static double Tfunction(StatData population, StatData local);
static Order Disorder(Order, lmrcImageTfunctionInfo *info, AxisInfo *x, AxisInfo *y, AxisInfo *z);
static Order Reorder(Order theOrder, lmrcImageTfunctionInfo *info, AxisInfo *x, AxisInfo *y, AxisInfo *z);
static double DataGet_xyz(mrcImage *src, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double *data, mrcPixelDataType mode, mrcPixelDataHowToGet how);
static double DataGet_yzx(mrcImage *src, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double *data, mrcPixelDataType mode, mrcPixelDataHowToGet how);
static double DataGet_zxy(mrcImage *src, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double *data, mrcPixelDataType mode, mrcPixelDataHowToGet how);
static void DataSet_xyz(mrcImage *dst, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double data, mrcPixelDataType mode);
static void DataSet_yzx(mrcImage *dst, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double data, mrcPixelDataType mode);
static void DataSet_zxy(mrcImage *dst, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double data, mrcPixelDataType mode);

/* Internal global variable */
static double (*DataGetDisorderd)(mrcImage *src, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double *data, mrcPixelDataType, mrcPixelDataHowToGet);
static void (*DataSetDisorderd)(mrcImage *dst, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double data, mrcPixelDataType);

/* 
*/

/* The 'member function' to mrcImage. */
void lmrcImageTfunction(mrcImage* dst, mrcImage* src, lmrcImageTfunctionInfo* info, long mode)
{
	StatData population, local;
	AxisInfo x, y, z;
	double t;
	Order theOrder = xyz;
		
	/* Checks if the condition mentiond in info satisfy the t-function request. If NG, it quits. This must be more smart in later virsion. */
	isGoodInfo(info);
	/* Destination data and sorce data will have same header data. */
	dst->Header = src->Header;
	mrcInit(dst, NULL);	
	
	/* For all data points in src, sets axes restriction and loop steps. */
	x.min = y.min = z.min = 0.0;
	x.max = src->HeaderN.x - 1.0;
	y.max = src->HeaderN.y - 1.0;
	z.max = src->HeaderN.z - 1.0;
	x.step = y.step = z.step = 1.0;

	/* Get the mean and deviation of the whole area. */
	population = getStatDataOfWhole(src, &x, &y, &z);
	
/* 
	From here, this program caluculates for all data points in the 
	area. First, we change the order of x, y and z, so that the sx 
	become the largest. This is confusing method. And last, we reorder
	x, y and z. (Reordering is not necessary.)
*/
	theOrder = Disorder(theOrder, info, &x, &y, &z);
	for(z.value = z.min; z.value <= z.max; z.value += z.step) {
	for(y.value = y.min; y.value <= y.max; y.value += y.step) {
	for(x.value = x.min; x.value <= x.max; x.value += x.step) {
		/* Caluculate the mean and variance of local area. */
		local = getLocalStatData(src, info, &x, &y, &z);
		t = Tfunction(population, local);
		/* Write the value. */
		DataSetDisorderd(dst, x.value, y.value, z.value, t, mrcPixelMag);
	}
	}
	}
	Reorder(theOrder, info, &x, &y, &z);
}

/*
	This function restricts sx, sy and sz to be odd.
	Exits at failure.
	(Should throw an error?)
*/
void isGoodInfo(lmrcImageTfunctionInfo* info)
{
	if(IsEven(info->sx))
	{
		fprintf(stderr, "Not supported kernel size: sx = %ld\n", info->sx);
		exit(EXIT_FAILURE);
	}
	if(IsEven(info->sy))
	{
		fprintf(stderr, "Not supported kernel size: sy = %ld\n", info->sy);
		exit(EXIT_FAILURE);
	}
	if(IsEven(info->sz))
	{
		fprintf(stderr, "Not supported kernel size: sz = %ld\n", info->sz);
		exit(EXIT_FAILURE);
	}
}

/*
	This function get statical data of src, and return the mean and
	variance.
*/
StatData getStatDataOfWhole(mrcImage* src, AxisInfo *x, AxisInfo *y, AxisInfo *z)
{
	StatData ret;
	mrcImageInformation info;

	info.mode = meanOfAll; 
	lmrcImageInformation(&info, src);
	ret.n = src->HeaderN.x * src->HeaderN.y * src->HeaderN.z;
	ret.mean = info.mean;
	ret.deviation = info.sd;

	return ret;
}

/*
	This function returns the statical information for the area sx *
	sy * sz.
	
	If x.step / pixelwidth are not always the same value, this 
	function might not work as you wish.	
*/
StatData getLocalStatData(mrcImage* src, lmrcImageTfunctionInfo *info, AxisInfo *x, AxisInfo *y, AxisInfo *z)
{
	int i, n = 0;
	double sx = 0.0, x2 = 0.0, dx, dy, dz;
	AxisInfo ax, ay, az;
	StatData ret;
	static int cache_flag = 0, cache_n;
	static double pixelstep, cache_sx, cache_x2;
	static const double pixelwidth = 1.0;

	dx = x->step * (info->sx - 1) / 2;
	dy = y->step * (info->sy - 1) / 2;
	dz = z->step * (info->sz - 1) / 2;
	ax.min = MAX(x->value - dx, x->min);
	ax.max = MIN(x->value + dx, x->max);
	ay.min = MAX(y->value - dy, y->min);
	ay.max = MIN(y->value + dy, y->max);
	az.min = MAX(z->value - dz, z->min);
	az.max = MIN(z->value + dz, z->max);
	ax.step = x->step, ay.step = y->step, az.step = z->step;	

	if(!cache_flag) cache_flag = (modf(ax.step / pixelwidth, &pixelstep) == 0.0);
	
	if(x->value == x->min || !cache_flag)
	/* If it is the first time, you cannot benefit by the cache. */
	{
		cache_n = 0;
		cache_sx = cache_x2 = 0.0;
		ax.value = ax.min;
		if(x->value - dx >= x->min)
			for(i = 0; i < (int)pixelstep; ax.value += ax.step, i++)
				getDataOn_yz(src, &ax, &ay, &az, &n, &sx, &x2);
		for(; ax.value <= ax.max; ax.value += ax.step)
			getDataOn_yz(src, &ax, &ay, &az, &cache_n, &cache_sx, &cache_x2);
		n += cache_n;
		sx += cache_sx;
		x2 += cache_x2;
	}
	else
	{
		double temp_sx, temp_x2;
		int temp_n;
		
		sx = cache_sx;
		x2 = cache_x2;
		n = cache_n;
		if(x->value - dx >= x->min)
		/* Data not used next time should be subtracted. */
		{
			temp_n = 0;
			temp_sx = temp_x2 = 0.0;			
			ax.value = ax.min;
			for(i = 0; i < (int)pixelstep; ax.value += ax.step, i++)
				getDataOn_yz(src, &ax, &ay, &az, &temp_n, &temp_sx, &temp_x2);
			cache_n -= temp_n;
			cache_sx -= temp_sx;
			cache_x2 -= temp_x2;
		}
		if(x->value + dx <= x->max)
		/* Checks if we need to get new data. */
		{
			temp_n = 0;
			temp_sx = temp_x2 = 0.0;			
			ax.value = ax.max;
			for(i = 0; i < (int)pixelstep; ax.value -= ax.step, i++)
				getDataOn_yz(src, &ax, &ay, &az, &temp_n, &temp_sx, &temp_x2);
			n += temp_n;
			sx += temp_sx;
			x2 += temp_x2;
			cache_n += temp_n;
			cache_sx += temp_sx;
			cache_x2 += temp_x2;
		}
	} /* end if */

	ret.n = n;
	ret.mean = sx / n;
	/* Unbiased deviation if there is more than one data. */
	ret.deviation = (n > 1 ? sqrt(x2 - n * ret.mean * ret.mean) : 0.0);

	return ret;
}

/*
	This function handles for data on the plane x = ax.value.
*/
void getDataOn_yz(mrcImage* src, AxisInfo *ax, AxisInfo *ay, AxisInfo *az, int *n, double *x, double *x2)
{
	double data;
	
	for(az->value = az->min; az->value <= az->max; az->value += az->step)
	{
		for(ay->value = ay->min; ay->value <= ay->max; ay->value += ay->step)
		{
			(*n)++;
			DataGetDisorderd(src, ax->value, ay->value, az->value, &data, mrcPixelMag, mrcPixelHowNearest);
			*x += data;
			*x2 += data * data;
		}
	}
}

double Tfunction(StatData population, StatData local)
/*
*/
{
	return (local.deviation != 0.0 ? (local.mean - population.mean) / sqrt(local.deviation * local.deviation / local.n) : 0.0);
}

Order Disorder(Order theOrder, lmrcImageTfunctionInfo *info, AxisInfo *x, AxisInfo *y, AxisInfo *z)
{
	AxisInfo tempAxis;
	long temps;

	if(info->sx >= info->sy && info->sx >= info->sz) /* sx biggest */
	{
		DataGetDisorderd = &DataGet_xyz;
		DataSetDisorderd = &DataSet_xyz;
		return xyz;
	}
	else
	{
		if(info->sy >= info->sz && info->sy >= info->sx) /* sy biggest */
/*
	Variable    x  y  z
	            |  |  |
	Reference   y  z  x
	            |  |  |
	ActualData  x  y  z

	      Region R/W
	Order   yzx  zxy
*/
		{
			tempAxis = *x;
			*x = *y, *y = *z, *z = tempAxis;
			temps = info->sx;
			info->sx = info->sy;
			info->sy = info->sz;
			info->sz = temps;
			DataGetDisorderd = &DataGet_zxy;
			DataSetDisorderd = &DataSet_zxy;
			return yzx;
		}
		else
		{
			if(info->sz >= info->sx && info->sz >= info->sy) /* sz biggest */
/*
	Variable    x  y  z
	            |  |  |
	Reference   z  x  y
	            |  |  |
	ActualData  x  y  z

	      Region R/W
	Order   zxy  yzx
*/
			{
				tempAxis = *x;
				*x = *z, *z = *y, *y = tempAxis;
				temps = info->sx;
				info->sx = info->sz;
				info->sz = info->sy;
				info->sy = temps;
				DataGetDisorderd = &DataGet_yzx;
				DataSetDisorderd = &DataSet_yzx;
				return zxy;
			}
		}
	}
}

Order Reorder(Order theOrder, lmrcImageTfunctionInfo *info, AxisInfo *x, AxisInfo *y, AxisInfo *z)
{
	AxisInfo tempAxis;
	long temps;

	switch(theOrder)
	{
	case xyz:
		return xyz;
	case yzx: /* yxz to xyz */
		tempAxis = *x;
		*x = *z, *z = *y, *y = tempAxis;
		temps = info->sx;
		info->sx = info->sz;
		info->sz = info->sy;
		info->sy = temps;
		DataGetDisorderd = &DataGet_xyz;
		DataSetDisorderd = &DataSet_xyz;
		return xyz;
	case zxy: /* zxy to xyz */
		tempAxis = *x;
		*x = *y, *y = *z, *z = tempAxis;
		temps = info->sx;
		info->sx = info->sy;
		info->sy = info->sz;
		info->sz = temps; 
		DataGetDisorderd = &DataGet_xyz;
		DataSetDisorderd = &DataSet_xyz;
		return xyz;
	}
}

double DataGet_xyz(mrcImage *src, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double *data, mrcPixelDataType mode, mrcPixelDataHowToGet how)
{
	return mrcPixelDataGet(src, x, y, z, data, mode, how);
}

double DataGet_yzx(mrcImage *src, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double *data, mrcPixelDataType mode, mrcPixelDataHowToGet how)
{
	return mrcPixelDataGet(src, y, z, x, data, mode, how);
}

double DataGet_zxy(mrcImage *src, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double *data, mrcPixelDataType mode, mrcPixelDataHowToGet how)
{
	return mrcPixelDataGet(src, z, x, y, data, mode, how);
}

void DataSet_xyz(mrcImage *dst, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double data, mrcPixelDataType mode)
{
	mrcPixelDataSet(dst, x, y, z, data, mode);
}

void DataSet_yzx(mrcImage *dst, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double data, mrcPixelDataType mode)
{
	mrcPixelDataSet(dst, y, z, x, data, mode);
}

void DataSet_zxy(mrcImage *dst, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double data, mrcPixelDataType mode)
{
	mrcPixelDataSet(dst, z, x, y, data, mode);
}
