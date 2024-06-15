/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageShapePCA ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageShapePCA 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageShapePCA ver%I%; Date:%D% %Z%";

#include "./lmrcImageShapePCA.h"

int lmrcImageShapePCA(mrcImage* in, lmrcImageShapePCAInfo* linfo, int mode)
{
	if(1<in->HeaderN.z) {
		lmrcImageShapePCA3D(in, linfo, mode);
		linfo->dimension=3;
	} else {
		lmrcImageShapePCA2D(in, linfo, mode);
		linfo->dimension=2;
	}
	return 0;
}

int
lmrcImageShapePCA3D(mrcImage* in, lmrcImageShapePCAInfo* linfo, int mode)
{
        mrcImageParaTypeReal x, y, z;
        double data;
        int n, i;
        Array X;
        Array X1;

        n = in->HeaderN.x*in->HeaderN.y*in->HeaderN.z;
        X.dim  = 2;
        X.n[0] = 3;
        X.n[1] = n*linfo->nLevel;
        arrayInit(&X, "in lmrcImageShapePCA");

        n = 0;
        for(z=0; z<in->HeaderN.z; z++) {
        for(y=0; y<in->HeaderN.y; y++) {
        for(x=0; x<in->HeaderN.x; x++) {
                mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
                for(i=0; i<linfo->nLevel; i++) {
                        if(linfo->Level[i]<data) {
                                arrayDataSet2(X, 0, n, x);
                                arrayDataSet2(X, 1, n, y);
                                arrayDataSet2(X, 2, n, z);
                                n++;
                        }
                }
        }
        }
        }

        X1.dim  = 2;
        X1.n[0] = 3;
        X1.n[1] = n;
        arrayInit(&X1, "in lmrcImageShapePCA");
        DEBUGPRINT1("count: %d\n", n);

        for(i=0; i<n; i++) {
                data = arrayDataGet2(X, 0, i);
                arrayDataSet2(X1, 0, i, data);
                data = arrayDataGet2(X, 1, i);
                arrayDataSet2(X1, 1, i, data);
                data = arrayDataGet2(X, 2, i);
                arrayDataSet2(X1, 2, i, data);
        }
        arrayPCA(&linfo->u, &linfo->C, &linfo->Lambda, &X1, &linfo->Average, 0);

	return 0;
}


int
lmrcImageShapePCA2D(mrcImage* in, lmrcImageShapePCAInfo* linfo, int mode)
{
        mrcImageParaTypeReal x, y, z;
        double data;
        int n, i;
        Array X;
        Array X1;

        n = in->HeaderN.x*in->HeaderN.y*in->HeaderN.z;
        X.dim  = 2;
        X.n[0] = 2;
        X.n[1] = n*linfo->nLevel;
        arrayInit(&X, "in lmrcImageShapePCA");

        n = 0;
        for(y=0; y<in->HeaderN.y; y++) {
        for(x=0; x<in->HeaderN.x; x++) {
                mrcPixelDataGet(in, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
                for(i=0; i<linfo->nLevel; i++) {
                        if(linfo->Level[i]<data) {
                                arrayDataSet2(X, 0, n, x);
                                arrayDataSet2(X, 1, n, y);
                                n++;
                        }
                }
        }
        }

        X1.dim  = 2;
        X1.n[0] = 2;
        X1.n[1] = n;
        arrayInit(&X1, "in lmrcImageShapePCA");
        DEBUGPRINT1("count: %d\n", n);

        for(i=0; i<n; i++) {
                data = arrayDataGet2(X, 0, i);
                arrayDataSet2(X1, 0, i, data);
                data = arrayDataGet2(X, 1, i);
                arrayDataSet2(X1, 1, i, data);
        }
        arrayPCA(&linfo->u, &linfo->C, &linfo->Lambda, &X1, &linfo->Average, 0);

	return 0;
}

int
lmrcImageShapePCAResultsPrint(FILE* fpt, lmrcImageShapePCAInfo* linfo, int mode)
{
	if(3==linfo->dimension) {
		lmrcImageShapePCAResultsPrint3D(fpt, linfo, mode);
	} else {
		lmrcImageShapePCAResultsPrint2D(fpt, linfo, mode);
	}
	return 0;
}


int
lmrcImageShapePCAResultsPrint3D(FILE* fpt, lmrcImageShapePCAInfo* linfo, int mode)
{
	double sum, sum2;
	double lambda[3];
	int i;
	double L0, L1, L2;
	double Wsphere, Wdisk, Wsylinder;

    fprintf(fpt, "# PCA Results");
    fprintf(fpt, "Convariace Matrix: ");
    arrayWriteToFile(fpt, &linfo->C, "lmrcImageShapePCAResultsPrint");
    fprintf(fpt, "UnitVector: one unit vector per line, from 1st ");
    arrayWriteToFile(fpt, &linfo->u, "lmrcImageShapePCAResultsPrint");
    fprintf(fpt, "Lambda: 1st 2nd 3rd");
    arrayWriteToFile(fpt, &linfo->Lambda, "lmrcImageShapePCAResultsPrint");
    fprintf(fpt, "Average: ");
    arrayWriteToFile(fpt, &linfo->Average, "lmrcImageShapePCAResultsPrint");
    fprintf(fpt, "Normalized Lambda: 1st 2nd 3rd\n");

	lambda[0] = arrayDataGet1(linfo->Lambda, 0);
	lambda[1] = arrayDataGet1(linfo->Lambda, 1);
	lambda[2] = arrayDataGet1(linfo->Lambda, 2);
	sum = 0;
	for(i=0; i<3; i++) {
		sum += lambda[i];
	}
	sum2 = 0;
	for(i=0; i<3; i++) {
		lambda[i] /= sum;
		sum2 += SQR(lambda[i]);
	}
	for(i=0; i<3; i++) {
    	fprintf(fpt, "%15.6f ", lambda[i]);
	}
	fprintf(fpt, "\n");

	L0 = lambda[0];
	L1 = lambda[1];
	L2 = lambda[2];

    Wsphere      = 100*exp(-((L1/L0) + (L2/L1) + 0.5*(L0 - L2)/L0));
	Wdisk        = 100*exp(-((L2/L0) + (L2/L1) + 0.5*(L0 - L1)/L0));
	Wsylinder    = 100*exp(-((L1/L0) + (L2/L0) + 0.5*(L1 - L2)/L1));

	if(mode&0x1) {
		fprintf(fpt, "Wsphere: %15.6f\n", Wsphere);
		fprintf(fpt, "logS(SphereIndex): %15.6f\n", -log10(1/(lambda[0]*lambda[1] + lambda[1]*lambda[2] +lambda[2]*lambda[0] )));
		fprintf(fpt, "exp(S-1)(SphereIndex): %15.6f\n", 1.0/exp(1/(lambda[0]*lambda[1] + lambda[1]*lambda[2] +lambda[2]*lambda[0] )-1));
		fprintf(fpt, "SphereIndex(var): %15.6f\n", 1.0/(SQR(lambda[0] - lambda[1])  + SQR(lambda[1]-lambda[2]) + SQR(lambda[2]-lambda[0])));
		fprintf(fpt, "Log(SphereIndex(var)): %15.6f\n", -log10(SQR(lambda[0] - lambda[1])  + SQR(lambda[1]-lambda[2]) + SQR(lambda[2]-lambda[0])));
		fprintf(fpt, "SphereIndex(var): %15.6f\n", 1.0/(SQR(lambda[0] - lambda[1])  + SQR(lambda[1]-lambda[2]) + SQR(lambda[2]-lambda[0])));
		fprintf(fpt, "SphereIndex(0.33): %15.6f\n", 1.0/(SQR(lambda[0] - 1.0/3)  + SQR(lambda[1]-1.0/3) + SQR(lambda[2]-1.0/3)));
		fprintf(fpt, "Log(SphereIndex(0.33)): %15.6f\n", -log10(SQR(lambda[0] - 1.0/3)  + SQR(lambda[1]-1.0/3) + SQR(lambda[2]-1.0/3)));
	}
	if(mode&0x2) {
		fprintf(fpt, "Wdisk: %15.6f\n", Wdisk);
		fprintf(fpt, "DiskIndex: %15.6f\n", 1.0/(lambda[2]/lambda[0]*lambda[2]/lambda[1]));
		fprintf(fpt, "logD(DiskIndex): %15.6f\n", -log10(lambda[2]/lambda[0]*lambda[2]/lambda[1]));
		fprintf(fpt, "DiskIndex(var): %15.6f\n", 1.0/(SQR(lambda[0]-lambda[1]) + SQR(lambda[2] )));
		fprintf(fpt, "Log(DiskIndex(var)): %15.6f\n", -log10(SQR(lambda[0]-lambda[1]) + SQR(lambda[2] )));
		fprintf(fpt, "DiskIndex(0.5): %15.6f\n", 1.0/(SQR(lambda[0]-0.5) + SQR(lambda[1]-0.5) + SQR(lambda[2] )));
		fprintf(fpt, "Log(DiskIndex(0.5)): %15.6f\n", -log10(SQR(lambda[0]-0.5) + SQR(lambda[1]-0.5) + SQR(lambda[2] )));
	}
	if(mode&0x4) {
		fprintf(fpt, "Wsylinder: %15.6f\n", Wsylinder);
		fprintf(fpt, "CylinderIndex: %15.6f\n", 1.0/(lambda[1]/lambda[0]*lambda[2]/lambda[0]));
		fprintf(fpt, "logC(CylinderIndex): %15.6f\n", -log10(lambda[1]/lambda[0]*lambda[2]/lambda[0]));
		fprintf(fpt, "CylinderIndex(var) : %15.6f\n", 1.0/(SQR(lambda[0] -1) + SQR(lambda[1] - lambda[2])));
		fprintf(fpt, "Log(CylinderIndex(var) : %15.6f\n", -log10(SQR(lambda[0] -1) +SQR(lambda[1] - lambda[2])));
		fprintf(fpt, "CylinderIndex(1.0) : %15.6f\n", 1.0/(SQR(lambda[0] -1) + SQR(lambda[1]) + SQR(lambda[2])));
		fprintf(fpt, "Log(CylinderIndex(1.0)) : %15.6f\n", -log10(SQR(lambda[0] -1) +SQR(lambda[1]) + SQR(lambda[2])));
	}


	return 0;
}

int
lmrcImageShapePCAResultsPrint2D(FILE* fpt, lmrcImageShapePCAInfo* linfo, int mode)
{
	double sum, sum2;
	double lambda[3];
	int i;
	double Wcircle;

    fprintf(fpt, "# PCA Results");
    fprintf(fpt, "Convariace Matrix: ");
    arrayWriteToFile(fpt, &linfo->C, "lmrcImageShapePCAResultsPrint");
    fprintf(fpt, "UnitVector: one unit vector per line, from 1st ");
    arrayWriteToFile(fpt, &linfo->u, "lmrcImageShapePCAResultsPrint");
    fprintf(fpt, "Lambda: 1st 2nd ");
    arrayWriteToFile(fpt, &linfo->Lambda, "lmrcImageShapePCAResultsPrint");
    fprintf(fpt, "Average: ");
    arrayWriteToFile(fpt, &linfo->Average, "lmrcImageShapePCAResultsPrint");
    fprintf(fpt, "Normalized Lambda: 1st 2nd \n");

	lambda[0] = arrayDataGet1(linfo->Lambda, 0);
	lambda[1] = arrayDataGet1(linfo->Lambda, 1);
	sum = 0;
	for(i=0; i<2; i++) {
		sum += lambda[i];
	}
	sum2 = 0;
	for(i=0; i<2; i++) {
		lambda[i] /= sum;
		sum2 += SQR(lambda[i]);
	}
	for(i=0; i<2; i++) {
    	fprintf(fpt, "%15.6f ", lambda[i]);
	}
	fprintf(fpt, "\n");

	if(mode&0x1) {
		fprintf(fpt, "Wcircle: %15.6f\n", 100*(exp(-SQR(lambda[0] - lambda[1]))-exp(-1.0)));
		fprintf(fpt, "exp(S-1)(SphereIndex): %15.6f\n",   exp(-1/(lambda[0]*lambda[1]-1.0)));
		fprintf(fpt, "Log(SphereIndex(var)): %15.6f\n", -log10(SQR(lambda[0] - lambda[1])));
		fprintf(fpt, "CircleIndex(0.5): %15.6f\n",        1.0/(SQR(lambda[0] - 1.0/2)  + SQR(lambda[1]-1.0/2)));
		fprintf(fpt, "Log(CircleIndex(0.5)): %15.6f\n", -log10(SQR(lambda[0] - 1.0/2)  + SQR(lambda[1]-1.0/2)));
	}

	return 0;
}


