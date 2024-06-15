/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageShapeSearch ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageShapeSearch 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageShapeSearch ver%I%; Date:%D% %Z%";

#include "../inc/mrcImageShape.h"

void
lmrcImageShapeSearch(mrcImage* out, mrcImage* in, lmrcImageShapeSearchInfo* linfo, int mode)
{
	switch(mode) {
		case lmrcImageShapeModeSylinder: {
			lmrcImageShapeSearchCalc0(out, in, linfo, mode);
			break;
		}
		case lmrcImageShapeModeDisk: {
			lmrcImageShapeSearchCalc0(out, in, linfo, mode);
			break;
		}
		case lmrcImageShapeModeSphere: {
			lmrcImageShapeSearchCalc0(out, in, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d\n", mode);
			break;
		}
	}
}

void
lmrcImageShapeContactSearch(mrcImage* contact, lmrcImageShapeSearchInfo* linfo, mrcImage* in, int mode)
{
	switch(mode) {
		case lmrcImageShapeContactModeSylinderSylinder: {
			lmrcImageShapeContactSearch0(contact, linfo, in, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d\n", mode);
			break;
		}
	}
}


void
lmrcImageShapeContactSearch0(mrcImage* contact, lmrcImageShapeSearchInfo* linfo, mrcImage* in, int mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal x0, y0, z0;
	double data;
	int* vote;

	vote = memoryAllocate(sizeof(int)*lmrcImageShapeContactModeMax, "in lmrcImageShapeContactSearch0");
	contact->Header = in->Header;
	mrcInit(contact, NULL);

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		// Sylinder-Sylinder contact 						
	}
	}
	}
//shape
//OutVectorMRC[3]

}

void
lmrcImageShapeSearchCalc0(mrcImage* out, mrcImage* in, lmrcImageShapeSearchInfo* linfo, int mode)
{
	float x, y, z;
	float srcx, srcy, srcz;
	float srcx0, srcy0, srcz0;
	float dstx, dsty, dstz;
	float theta, phi, psi, radius, length;
	int iPhi, iTheta, iPsi, iRadius, iLength;	
	int nPhi, nTheta, nPsi, nRadius, nLength;	
	float max, ave, sum, sd, zscore, min;
	double* data;
	double  d, cp, sp;
	double score;
	int nData, index;
	float r, l, p;
	Matrix3D mat;
	floatVector v;
	int i, imax;
	int k, k0, nVoxel;
	int PCAMode=0;
	int numPoint;
	Array U;
	Array C;
	Array Lambda;
	double L0, L1, L2, L;
	Array X;
	Array Ave;
	mrcImageParaTypeInteger nCube; 
	double W, Wsylinder, Wdisk, Wsphere, Waccuracy;

	nPhi   = (int)((linfo->maxPhi     - linfo->minPhi)  /linfo->delPhi)  +1;
	nTheta = (int)((linfo->maxTheta   - linfo->minTheta)/linfo->delTheta)+1;
	nPsi= (int)((linfo->maxTheta   - linfo->minTheta)/linfo->delTheta)+1;
	nRadius = (int)((linfo->maxRadius - linfo->minRadius)/linfo->delRadius) + 1;
	nLength = (int)((linfo->maxLength - linfo->minLength)/linfo->delLength) + 1;
	
	nData = nPhi*nTheta*nPsi*nRadius*nLength;
	data = (double*)memoryAllocate(sizeof(double)*nData, "in lmrcImageShapeSearchSylinder");

	floatVectorInit(&v, 4);
	v.data[3] = 1;	

	out->Header = in->Header;
	mrcInit(out, NULL);
	linfo->average.Header = in->Header;
	mrcInit(&linfo->average, NULL);
	linfo->SD.Header = in->Header;
	mrcInit(&linfo->SD, NULL);
	linfo->Zscore.Header = in->Header;
	mrcInit(&linfo->Zscore, NULL);
	linfo->Max.Header = in->Header;
	mrcInit(&linfo->Max, NULL);

	linfo->PCA.Header = in->Header;
	mrcInit(&linfo->PCA, NULL);
	linfo->shape.Header = in->Header;
	mrcInit(&linfo->shape, NULL);
	linfo->PCAaccuracy.Header = in->Header;
	mrcInit(&linfo->PCAaccuracy, NULL);

	linfo->nShapeInfo = 5;
	linfo->shapeInfo = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo->nShapeInfo, "in MFPCalc");
	for(i=0; i<linfo->nShapeInfo; i++) {
		linfo->shapeInfo[i].Header = in->Header;
		mrcInit(&linfo->shapeInfo[i], NULL);
	}

	X.dim = 2;
	X.n[0] = 3;
	if(0<linfo->nCube) {
		nCube = linfo->nCube;
	} else {
		nCube = ((int)(MAX(linfo->maxLength, 2*linfo->maxRadius+1)+3)/2)*2; 
	}
	X.n[1] = nCube*nCube*nCube; 
	arrayInit(&X, "in");
	DEBUGPRINT2("nCube: %d %lu\n", nCube, X.n[1]); 
	DEBUGPRINT1("nCube: %d\n", nCube);

	// OutVector
	if(linfo->flagOutVectorMRC) {
		for(i=0; i<3; i++) {
			linfo->OutVectorMRC[i].Header = in->Header;
			mrcInit(&linfo->OutVectorMRC[i], NULL);
		}
	}

	// avsFile
	linfo->OutVectorFLD.type = avsFileFieldTypeRectilinear;
	linfo->OutVectorFLD.dataType = avsFileFieldDataTypeFloat;
	linfo->OutVectorFLD.ndim = 3;
	linfo->OutVectorFLD.dim1 = in->HeaderN.x;
	linfo->OutVectorFLD.dim2 = in->HeaderN.y;
	linfo->OutVectorFLD.dim3 = in->HeaderN.z;
	linfo->OutVectorFLD.nspace = 3;
	linfo->OutVectorFLD.veclen = 9;
	avsFileFieldInit(&linfo->OutVectorFLD, 0);

	for(z=0; z<in->HeaderN.z; z++) {
		DEBUGPRINT1("z: %f\n", z);
		linfo->z = z;
	for(y=0; y<in->HeaderN.y; y++) {
		DEBUGPRINT1("y: %f\n", y);
		linfo->y = y;
	for(x=0; x<in->HeaderN.x; x++) { // Each voxel
		linfo->x = x;

		k0 = (int)(x + y*in->HeaderN.x + z*in->HeaderN.x*in->HeaderN.y); 
		linfo->shape.ImageFloatImage[k0] = lmrcImageShapeModeNoShape;

		//mrcPixelDataGet(in, x, y, z, &d, mrcPixelRePart, mrcPixelHowNearest);
		k = x + y*in->HeaderN.x + z*in->HeaderN.x*in->HeaderN.y;
		d = in->ImageFloatImage[k];
	if(0<d) {
		numPoint = 0;
		for(srcz=-nCube/2; srcz<=nCube/2; srcz++) {
		for(srcy=-nCube/2; srcy<=nCube/2; srcy++) {
		for(srcx=-nCube/2; srcx<=nCube/2; srcx++) {
			//mrcPixelDataGet(in, x+srcx, y+srcy, z+srcz, &d, mrcPixelRePart, mrcPixelHowNearest);	
			srcx0 = ((int)(x + srcx)+in->HeaderN.x)%in->HeaderN.x;
			srcy0 = ((int)(y + srcy)+in->HeaderN.y)%in->HeaderN.y;
			srcz0 = ((int)(z + srcz)+in->HeaderN.z)%in->HeaderN.z;
			k = srcx0 + srcy0*in->HeaderN.x + srcz0*in->HeaderN.x*in->HeaderN.y;
			d = in->ImageFloatImage[k];
			if(0<d) {
				arrayDataSet2(X, 0, numPoint, srcx0);
				arrayDataSet2(X, 1, numPoint, srcy0);
				arrayDataSet2(X, 2, numPoint, srcz0);
				numPoint++;
			}
		}
		}
		}
		DEBUGPRINT4("%f %f %f numPoint: %d\n", x, y, z, numPoint);
		if(5<numPoint) {
			X.n[1] = numPoint;
			arrayPCA(&U, &C, &Lambda, &X, &Ave, PCAMode);
			if(PCAMode==0) PCAMode=1;
			L0 = arrayDataGet1(Lambda, 0);
			L1 = arrayDataGet1(Lambda, 1);
			L2 = arrayDataGet1(Lambda, 2);

			DEBUGPRINT3("Lambda: %f %f %f\n", L0, L1, L2);
			L = L0+L1+L2;
			L0 /= L;
			L1 /= L;
			L2 /= L;
			DEBUGPRINT3("Lambda: %f %f %f\n", L0, L1, L2);

			Wsphere      = 100*exp(-((L1/L0) + (L2/L1) + 0.5*(L0 - L2)/L0));  
			Wdisk        = 100*exp(-((L2/L0) + (L2/L1) + 0.5*(L0 - L1)/L0));  
			Wsylinder    = 100*exp(-((L1/L0) + (L2/L0) + 0.5*(L1 - L2)/L1));
			DEBUGPRINT3("W: sphere %f disk %f sylinder %f\n", Wsphere, Wdisk, Wsylinder);

			if(Wsphere<Wdisk) {
				if(Wdisk<Wsylinder) {  // sphere -> disk -> sylinder
					linfo->shape.ImageFloatImage[k0] =  lmrcImageShapeModeSylinder;
					Waccuracy = Wsylinder - Wdisk;
					// Sylinder
				} else {               // sphere/sylinder -> disk
					linfo->shape.ImageFloatImage[k0] =  lmrcImageShapeModeDisk;
					if(Wsphere<Wsylinder) { // sphere -> sylinder -> disk 
						Waccuracy = Wdisk - Wsylinder;
					} else {                // sphere -> sylinder -> disk
						Waccuracy = Wdisk - Wsphere;
					}
					// Disk
				}
			} else {
				if(Wsphere<Wsylinder) { // Wdisk -> Wsphere -> Wsylinder 
					linfo->shape.ImageFloatImage[k0] =  lmrcImageShapeModeSylinder;
					Waccuracy = Wsylinder - Wsphere;
					// Sylinder
				} else { // Wdisk/Wsylinder -> Wsphere
					linfo->shape.ImageFloatImage[k0] =  lmrcImageShapeModeSphere;
					if(Wdisk<Wsylinder) { // Wdisk -> Wsylinder -> Wsphere
						Waccuracy = Wsphere - Wsylinder;
					} else {              // Wsylinder -> Wdisk -> Wsphere
						Waccuracy = Wsphere - Wdisk;
					}
					// Sphere
				}	
			}

			// BILD
			if(linfo->OutVectorBILD!=NULL) {
				float startx, starty, startz;
				float endx, endy, endz;
				float zoom;
	
				startx = (x+in->HeaderStartN.x)*in->HeaderLength.x;
				starty = (y+in->HeaderStartN.y)*in->HeaderLength.y;
				startz = (z+in->HeaderStartN.z)*in->HeaderLength.z;

				switch((int)(linfo->shape.ImageFloatImage[k0]+0.5)) {
					case lmrcImageShapeModeSylinder: {
						fprintf(linfo->OutVectorBILD, ".color %g %g %g\n", linfo->sylinderColor[0], linfo->sylinderColor[1], linfo->sylinderColor[2]);				
						endx = arrayDataGet2(U, 0, 0)*Wsylinder/100.0;
						endy = arrayDataGet2(U, 1, 0)*Wsylinder/100.0;
						endz = arrayDataGet2(U, 2, 0)*Wsylinder/100.0;
						break;
					}
					case lmrcImageShapeModeDisk: {
						fprintf(linfo->OutVectorBILD, ".color %g %g %g\n", linfo->diskColor[0], linfo->diskColor[1], linfo->diskColor[2]);
						endx = arrayDataGet2(U, 0, 2)*Wdisk/100.0;
						endy = arrayDataGet2(U, 1, 2)*Wdisk/100.0;
						endz = arrayDataGet2(U, 2, 2)*Wdisk/100.0;
						break;
					}
					case lmrcImageShapeModeSphere: {
						break;
					}
					default: {
						break;
					}
				}
				switch((int)(linfo->shape.ImageFloatImage[k0]+0.5)) {
					case lmrcImageShapeModeSylinder: 
					case lmrcImageShapeModeDisk: {
						if(linfo->flagOutVectorMRC) {
							linfo->OutVectorMRC[0].ImageFloatImage[k0] = endx;
							linfo->OutVectorMRC[1].ImageFloatImage[k0] = endy;
							linfo->OutVectorMRC[2].ImageFloatImage[k0] = endz;
						}
						fprintf(linfo->OutVectorBILD, ".arrow %g %g %g %g %g %g %g %g %g\n", 
																					startx, starty, startz,
																					startx+endx*in->HeaderLength.x*linfo->ZoomVector, 
																					starty+endy*in->HeaderLength.y*linfo->ZoomVector, 
																					startz+endz*in->HeaderLength.z*linfo->ZoomVector,
																					linfo->arrowr1, 
																					linfo->arrowr2, 
																					linfo->arrowrho);
						break;
					}
					default: {
						break;
					}
				}

			}
			switch(mode) {
				case lmrcImageShapeModeSylinder: {	
					W = Wsylinder;
					DEBUGPRINT4("W: %f %f %f %f\n", W, L0, L1, L2);
#ifdef DEBUG2
					if(0.2<W) {
						DEBUGPRINT3("%f %f %f\n", x, y, z);
						DEBUGPRINT4("W: %f %f %f %f\n", W, L0, L1, L2);
					}
#endif
					break;
				}
				case lmrcImageShapeModeDisk: {	
					W = Wdisk;
#ifdef DEBUG2
					if(0.2<W) {
						DEBUGPRINT3("%f %f %f\n", x, y, z);
						DEBUGPRINT4("W: %f %f %f %f\n", W, L0, L1, L2);
					}
#endif
					break;
				}
				case lmrcImageShapeModeSphere: {	
					W = Wsphere;
					break;
				}
				default: {
					W = 1;
					break;
				}
			}
		} else {
			W = 1;
		} // numPoint

		} else {
			W = 0;
	} // 0 < d
		//mrcPixelDataSet(&linfo->PCA, x, y, z, W, mrcPixelRePart);
		linfo->PCA.ImageFloatImage[k0] = W;
		if(linfo->shape.ImageFloatImage[k0]==mode) {
			linfo->PCAaccuracy.ImageFloatImage[k0] = W*Waccuracy/100/100;
		} else {
			linfo->PCAaccuracy.ImageFloatImage[k0] = 0;
		}

	if(1<W && linfo->flagRefine) {
		for(iPhi=0; iPhi<nPhi; iPhi++) { // Three Rotation	
			phi = linfo->minPhi + iPhi*linfo->delPhi;
		for(iTheta=0; iTheta<nTheta; iTheta++) {	
			theta = linfo->minTheta + iTheta*linfo->delTheta;
		for(iPsi=0; iPsi<nPsi; iPsi++) { 	
			psi= linfo->minPsi+ iPhi*linfo->delPsi;
			
			//DEBUGPRINT3("%f %f %f\n", phi*DEGREE, theta*DEGREE, psi*DEGREE);	
			matrix3DRotationSetFollowingEulerAngle(mat, 
				"ZENS", phi, theta, psi, MATRIX_3D_MODE_INITIALIZE); // Rotation angle set

		for(iRadius=0; iRadius<nRadius; iRadius++) {
			radius = linfo->minRadius + iRadius*linfo->delRadius; 
		for(iLength=0; iLength<nLength; iLength++) {
			length = linfo->minLength + iLength*linfo->delLength; 

			index = iPhi
				   +iTheta *nPhi
				   +iPsi   *nPhi*nTheta
				   +iRadius*nPhi*nTheta*nPsi
				   +iLength*nPhi*nTheta*nPsi*nRadius;

			linfo->radius = radius;	
			linfo->length = length;	
			switch(mode) {
				case lmrcImageShapeModeSylinder: {	
					lmrcImageShapeSearchSylinder(&(data[index]), in, mat, linfo, mode);		
#ifdef DEBUG2
					if(0<data[index]) {
						DEBUGPRINT2("%d %f\n", index, data[index]);
					}
#endif
					break;
				}
				case lmrcImageShapeModeDisk: {	
					lmrcImageShapeSearchDisk(&data[index], in, mat, linfo, mode);		
					break;
				}
				case lmrcImageShapeModeSphere: {	
					lmrcImageShapeSearchSphere(&data[index], in, mat, linfo, mode);		
					break;
				}
				default: {
					fprintf(stderr, "Not supported mode: %d\n", mode);
					exit(EXIT_FAILURE);	
					break;
				}
			}
		}
		}
		}
		}
		}
		//DEBUGPRINT1("nData: %d\n", nData);
		imax = 0;
		max = data[0]; 
		sum = data[0];	
		for(i=1; i<nData; i++) {	
#ifdef DEBUG2
			if(0<data[i]) {
				DEBUGPRINT2("data: %d %f\n", i, data[i]);
			}
#endif
			sum += data[i];
			if(max<data[i]) {
				imax = i;
				max = data[i];
			}
		}
		ave = sum/nData;
		sum = 0;
		for(i=0; i<nData; i++) {	
			sum += SQR(data[i]-ave);
		}
		sd = sqrt(sum/nData);
#ifdef DEBUG2
		if(0<max) {
		DEBUGPRINT3("%f %f %f ", x, y, z); 	
		DEBUGPRINT3("%f %f %f \n", max, ave, sd); 	
		}
#endif
	} else {
			ave = 0;
			sd  = 0;
			max = 0;
			imax = 0;
	}

		//mrcPixelDataSet(&linfo->average, x, y, z, ave, mrcPixelRePart);
		linfo->average.ImageFloatImage[k0] = ave;

		//mrcPixelDataSet(&linfo->SD,      x, y, z, sd, mrcPixelRePart);
		linfo->SD.ImageFloatImage[k0] = sd;

		//mrcPixelDataSet(&linfo->Max,     x, y, z, max, mrcPixelRePart);
		linfo->Max.ImageFloatImage[k0] = max;

		i = imax%nPhi;
		//mrcPixelDataSet(&linfo->shapeInfo[0], x, y, z, (i*linfo->delPhi + linfo->minPhi)*DEGREE, mrcPixelRePart);
		linfo->shapeInfo[0].ImageFloatImage[k0] =  (i*linfo->delPhi + linfo->minPhi)*DEGREE;

		i = (imax%(nPhi*nTheta))/nPhi;
		//mrcPixelDataSet(&linfo->shapeInfo[1], x, y, z, (i*linfo->delTheta + linfo->minTheta)*DEGREE, mrcPixelRePart);
		linfo->shapeInfo[1].ImageFloatImage[k0] =  (i*linfo->delTheta + linfo->minTheta)*DEGREE;

		i = (imax%(nPhi*nTheta*nPsi))/(nPhi*nTheta);
		//mrcPixelDataSet(&linfo->shapeInfo[2], x, y, z, (i*linfo->delPsi+ linfo->minPsi)*DEGREE, mrcPixelRePart);
		linfo->shapeInfo[2].ImageFloatImage[k0] =  (i*linfo->delPsi+ linfo->minPsi)*DEGREE;

		i = (imax%(nPhi*nTheta*nPsi*nRadius))/(nPhi*nTheta*nPsi);
		//mrcPixelDataSet(&linfo->shapeInfo[3], x, y, z, i*linfo->delRadius + linfo->minRadius, mrcPixelRePart);
		linfo->shapeInfo[3].ImageFloatImage[k0] =  i*linfo->delRadius + linfo->minRadius;

		i =  imax/(nPhi*nTheta*nPsi*nRadius);
		//mrcPixelDataSet(&linfo->shapeInfo[4], x, y, z, i*linfo->delLength + linfo->minLength, mrcPixelRePart);
		linfo->shapeInfo[4].ImageFloatImage[k0] =  i*linfo->delLength + linfo->minLength;
	}
	}
	}

	nVoxel = in->HeaderN.x*in->HeaderN.y*in->HeaderN.z;
	max = -1e30;
	min =  1e30;
	ave = 0;
	sd  = 0;
	for(k=0; k<nVoxel; k++) {
		d = linfo->Max.ImageFloatImage[k];
		ave += d;
		if(sd<linfo->SD.ImageFloatImage[k]) {
			sd = linfo->SD.ImageFloatImage[k];
		}
		if(max<d) {
			max = d;
		} 
		if(ave<min) {
			min = d;
		}
	}
	ave /= nVoxel;
	DEBUGPRINT2("aveOfmax: %f maxOfsd: %f\n", ave, sd);	
	DEBUGPRINT2("max: %f min: %f\n", max, min);	

	sum = 100./(max - min);
	for(k=0; k<nVoxel; k++) {
		d = linfo->Max.ImageFloatImage[k]; 
			
		zscore = (d-linfo->average.ImageFloatImage[k])/linfo->SD.ImageFloatImage[k];
		//zscore = (d-ave)/sd; 
		linfo->Zscore.ImageFloatImage[k] = zscore*in->ImageFloatImage[k];
		
		d = (d-min)*sum;
		out->ImageFloatImage[k] = d*in->ImageFloatImage[k];

		//DEBUGPRINT3("%d z: %f out: %f\n", k, zscore, d);
	}

	radius = linfo->radiusSmooth;
	if(linfo->flagSmooth) {
		for(z=0; z<in->HeaderN.z; z++) {
			DEBUGPRINT1("z: %f\n", z);
		for(y=0; y<in->HeaderN.y; y++) {
			DEBUGPRINT1("y: %f\n", y);
		for(x=0; x<in->HeaderN.x; x++) { // Each voxel
			mrcPixelDataGet(in, x, y, z, &d, mrcPixelRePart, mrcPixelHowNearest);			
		if(0<d) {
			sum = 0;	
			

			for(z=MAX(z-radius, 0); z<=MIN(z+radius, in->HeaderN.z-1); z++) {
			for(y=MAX(y-radius, 0); y<=MIN(y+radius, in->HeaderN.y-1); y++) {
			for(x=MAX(x-radius, 0); x<=MIN(x+radius, in->HeaderN.x-1); x++) {
				k0 = x + y*in->HeaderN.x + z*in->HeaderN.x*in->HeaderN.y;
			}
			}
			}
		}
		}
		}
		}
	}
}

void
lmrcImageShapeSearchSylinder(double* data, mrcImage* in, Matrix3D mat, lmrcImageShapeSearchInfo* linfo, int mode)
{
	double p, l, r;
	double x, y, z;
	double srcx, srcy, srcz;
	double dstx, dsty, dstz;
	double scorePos, scoreNeg;
	double cp, sp, d;
	int k, k0;
	int countPos, countNeg;

	//DEBUGPRINT("lmrcImageShapeSearchSylinder start\n");
	scorePos = 0; 
	scoreNeg = 0; 
	countPos = 0;
	countNeg = 0;
	for(p=0; p<2*M_PI;  p+=linfo->delPsi) {
		cp = cos(p);
		sp = sin(p);
	for(l=0; l<=linfo->length; l+=linfo->delLength) {
		z = l-linfo->length/2; 
	for(r=0; r<=linfo->radius; r+=linfo->delRadius) {
		x = r*cp;
		y = r*sp;

		srcx = mat[0][0]*x + mat[1][0]*y + mat[2][0]*z;
		srcy = mat[0][1]*x + mat[1][1]*y + mat[2][1]*z; 
		srcz = mat[0][2]*x + mat[1][2]*y + mat[2][2]*z;

		dstx = linfo->x + srcx; 
		dsty = linfo->y + srcy;
		dstz = linfo->z + srcz; 
		if(-0.5<dstx && dstx < in->HeaderN.x-0.5
		 &&-0.5<dsty && dsty < in->HeaderN.y-0.5
		 &&-0.5<dstz && dstz < in->HeaderN.z-0.5) {
			k = (int)(dstx+0.5) + (int)(dsty+0.5)*in->HeaderN.x + (int)(dstz+0.5)*in->HeaderN.x*in->HeaderN.y; 
			d = in->ImageFloatImage[k];
		} else {
			d = 0;
		}

		countPos++;
		scorePos += d;
	}
	// Edge Check
	x = r*cos(p);
	y = r*sin(p);
	srcx = mat[0][0]*x + mat[1][0]*y + mat[2][0]*z;
	srcy = mat[0][1]*x + mat[1][1]*y + mat[2][1]*z; 
	srcz = mat[0][2]*x + mat[1][2]*y + mat[2][2]*z;

	dstx = linfo->x + srcx;
	dsty = linfo->y + srcy;
	dstz = linfo->z + srcz; 
	if(-0.5<dstx && dstx < in->HeaderN.x-0.5
	 &&-0.5<dsty && dsty < in->HeaderN.y-0.5
	 &&-0.5<dstz && dstz < in->HeaderN.z-0.5) {
		k = (int)(dstx+0.5) + (int)(dsty+0.5)*in->HeaderN.x + (int)(dstz+0.5)*in->HeaderN.x*in->HeaderN.y; 
		d = in->ImageFloatImage[k];
	} else {
		d = 0;
	}
	scoreNeg += d;
	countNeg++;
	}
	}
	k0 =  (int)(linfo->x+0.5) + (int)(linfo->y+0.5)*in->HeaderN.x + (int)(linfo->z+0.5)*in->HeaderN.x*in->HeaderN.y; 
	*data = (0.8*scorePos/countPos - 0.2*scoreNeg/countNeg);
#ifdef DEBUG2
	//DEBUGPRINT1("data: %f\n", score);
	if(0<score) {
		DEBUGPRINT1("data: %f\n", score);
	}
#endif
}

void
lmrcImageShapeSearchDisk(double* data, mrcImage* in, Matrix3D mat, lmrcImageShapeSearchInfo* linfo, int mode)
{

	double p, l, r;
	double x, y, z;
	double zz;
	double srcx, srcy, srcz;
	double dstx, dsty, dstz;
	double scorePos, scoreNeg;
	double cp, sp, d;
	int k, k0;
	int countPos, countNeg;

	//DEBUGPRINT("lmrcImageShapeSearchSylinder start\n");
	scorePos = 0; 
	scoreNeg = 0; 
	countPos = 0;
	countNeg = 0;
	for(p=0; p<2*M_PI;  p+=linfo->delPsi) {
		cp = cos(p);
		sp = sin(p);
	for(r=0; r<=linfo->radius; r+=linfo->delRadius) {
		x = r*cp;
		y = r*sp;
	for(l=0; l<=linfo->length; l+=linfo->delLength) {
		z = l-linfo->length/2; 

		srcx = mat[0][0]*x + mat[1][0]*y + mat[2][0]*z;
		srcy = mat[0][1]*x + mat[1][1]*y + mat[2][1]*z; 
		srcz = mat[0][2]*x + mat[1][2]*y + mat[2][2]*z;

		dstx = linfo->x + srcx; 
		dsty = linfo->y + srcy;
		dstz = linfo->z + srcz; 
		if(-0.5<dstx && dstx < in->HeaderN.x-0.5
		 &&-0.5<dsty && dsty < in->HeaderN.y-0.5
		 &&-0.5<dstz && dstz < in->HeaderN.z-0.5) {
			k = (int)(dstx+0.5) + (int)(dsty+0.5)*in->HeaderN.x + (int)(dstz+0.5)*in->HeaderN.x*in->HeaderN.y; 
			d = in->ImageFloatImage[k];
		} else {
			d = 0;
		}

		countPos++;
		scorePos += d;
	}
	// Edge Check
	for(zz = -1; zz <= 1; zz+=2) {
		x = r*cos(p);
		y = r*sin(p);
		z = l - (linfo->length/2 + linfo->delLength)*zz;     
		srcx = mat[0][0]*x + mat[1][0]*y + mat[2][0]*z;
		srcy = mat[0][1]*x + mat[1][1]*y + mat[2][1]*z; 
		srcz = mat[0][2]*x + mat[1][2]*y + mat[2][2]*z;
		dstx = linfo->x + srcx;
		dsty = linfo->y + srcy;
		dstz = linfo->z + srcz; 

		if(-0.5<dstx && dstx < in->HeaderN.x-0.5
		 &&-0.5<dsty && dsty < in->HeaderN.y-0.5
		 &&-0.5<dstz && dstz < in->HeaderN.z-0.5) {
				k = (int)(dstx+0.5) + (int)(dsty+0.5)*in->HeaderN.x + (int)(dstz+0.5)*in->HeaderN.x*in->HeaderN.y; 
				d = in->ImageFloatImage[k];
		} else {
				d = 0;
		}
		scoreNeg += d;
		countNeg++;
	}

	}
	}
	k0 =  (int)(linfo->x+0.5) + (int)(linfo->y+0.5)*in->HeaderN.x + (int)(linfo->z+0.5)*in->HeaderN.x*in->HeaderN.y; 
	*data = (0.8*scorePos/countPos - 0.2*scoreNeg/countNeg);
#ifdef DEBUG2
	//DEBUGPRINT1("data: %f\n", score);
	if(0<score) {
		DEBUGPRINT1("data: %f\n", score);
	}
#endif
}


void
lmrcImageShapeSearchSphere(double* data, mrcImage* in, Matrix3D mat, lmrcImageShapeSearchInfo* linfo, int mode)
{

	double phi, psi, r;
	double x, y, z;
	double zz;
	double srcx, srcy, srcz;
	double dstx, dsty, dstz;
	double scorePos, scoreNeg;
	double cp, sp, d;
	int k, k0;
	int countPos, countNeg;

	//DEBUGPRINT("lmrcImageShapeSearchSylinder start\n");
	scorePos = 0; 
	scoreNeg = 0; 
	countPos = 0;
	countNeg = 0;
	for(phi=0; phi<2*M_PI;  phi+=linfo->delPhi) {
	for(psi=0; psi<2*M_PI;  psi+=linfo->delPsi) {
	for(r=0; r<=linfo->radius; r+=linfo->delRadius) {
		
		countPos++;
		scorePos += d;
	}
	// Edge Check
		scoreNeg += d;
		countNeg++;
	}
	}
	
	k0 =  (int)(linfo->x+0.5) + (int)(linfo->y+0.5)*in->HeaderN.x + (int)(linfo->z+0.5)*in->HeaderN.x*in->HeaderN.y; 
	*data = (0.8*scorePos/countPos - 0.2*scoreNeg/countNeg);
}


