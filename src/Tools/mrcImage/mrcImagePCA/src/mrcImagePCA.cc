/*
  # mrcImagePCA : $Revision$  
  # $Date$ 
  # Created by $Author$
  # Usage : mrcImagePCA
  # Attention
  #   $Loccker$
  #  	$State$ 
  #
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "File.h"

#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "../inc/mrcImagePCA.h"

typedef struct lmrcImagePCAInfo {
	float EPS; 
    int NX;
	int NY;
	int Dimension;
	int*    EigenValueOrder;           /* Original Eigen Value Order */
	double* EigenValue;           /* Sorted Eigen Value */	
	double* IntegratedEigenValue; /* Integrated Eigen Value*/	

	int numOfEigenImage; 
	mrcImage* EigenImage;

	long flagEPSOutcaletime;
	char EPSOutcaletime[1024];
	FILE* fptEPSOutcaletime;

} lmrcImagePCAInfo;

/*
  typedef enum lmrcImagePCAMode {
  a=0,
  b=1
  } lmrcImagePCAMode;
  
*/

#ifdef __cplusplus
    extern "C" {
#endif

void lmrcImagePCA(mrcImage* Out, int nOut, mrcImage* In, int nIn, lmrcImagePCAInfo* linfo, int mode);
double getMax(double** a,int& p,int& q);
void transform(double** a,double** u,int p,int q);
 
#ifdef __cplusplus
    }
#endif


static int dim;
//static int newdim;
//static float NX,NY;  
int
main(int argc, char* argv[]) 
{
	mrcImagePCAInfo info;
	lmrcImagePCAInfo linfo;
	mrcImage* In;
	mrcImage* Out;
  	int i;
	char s[1024];
  //      FILE* fpin;
  //	FILE* fpout;
	DEBUGPRINT("Program Start\n");
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
 
  	In  = (mrcImage*)MemoryAllocate(mrcImage, info.flagInList, "in main");
  	for(i=0; i<info.flagInList; i++) {
    		mrcFileRead(&In[i], info.InList[i], "in main", 0);
//   		DEBUGPRINT2("mrcFileRead %s  %d th Read\n", info.InListList,i);
			if(i%1000==0)
				DEBUGPRINT1("mrcFileRead  %d th Read\n",i);

  	}
  	Out = (mrcImage*)MemoryAllocate(mrcImage, info.flagOutList, "in main");
 
 	linfo.EPS = info.EPS;
	linfo.NX=info.NX;
	linfo.NY=info.NY;
	linfo.numOfEigenImage =info.numOfEigenImage;

	linfo.fptEPSOutcaletime=NULL;
	linfo.flagEPSOutcaletime=0;
	if(info.flagEPSOutcaletime){
	//	DEBUGPRINT("if EPS\n");
		sprintf(linfo.EPSOutcaletime, "%s", info.EPSOutcaletime);
		linfo.flagEPSOutcaletime=1;
		linfo.fptEPSOutcaletime = fileOpen(linfo.EPSOutcaletime, "w");
		linfo.fptEPSOutcaletime=info.fptEPSOutcaletime;
//		sprintf(linfo.EPSOutcaletime, "%s", info.EPSOutcaletime);
//		DEBUGPRINT("if EPS\n");
	}

	//NX=info.NX;
	//NY=info.NY;
  	lmrcImagePCA(Out, info.flagOutList, In, info.flagInList, &linfo, 0);
  
  	for(i=0; i<info.flagOutList; i++) {
    		mrcFileWrite(&Out[i], info.OutList[i], "in main", 0);
//			DEBUGPRINT2("mrcFileWrite %s  %d th Write\n", info.OutListList,i);
			 if(i%1000==0)
				DEBUGPRINT1("mrcFileWrite  %d th Write\n",i);

  	}

	if(info.flagOutvector) {
   		for(i=0; i<linfo.Dimension; i++){
	  		fprintf(info.fptOutvector,"%4d  %4d  %5.2lf  %3.2lf\n", i, 
				linfo.EigenValueOrder[i],
				linfo.EigenValue[i],
				linfo.IntegratedEigenValue[i]);
		}
	/*	for(i=0; i<linfo.Dimension; i++)
			fprintf(info.fptOutvector,"%4d\n",i);  
		for(i=0; i<linfo.Dimension; i++)
			fprintf(info.fptOutvector,"%4d\n",linfo.EigenValueOrder[i]);
		for(i=0; i<linfo.Dimension; i++)
			fprintf(info.fptOutvector,"%5.2lf\n",linfo.EigenValue[i]);
		for(i=0; i<linfo.Dimension; i++)		
			fprintf(info.fptOutvector,"%3.2lf\n",linfo.IntegratedEigenValue[i]); */
	}

	if(info.flagEigenImage) {
//		char s[1024];
		for(i=0; i<	linfo.numOfEigenImage; i++) {
			sprintf(s, "%s.%05d", info.EigenImage, i);
			mrcFileWrite(&linfo.EigenImage[i], s, "in main", 0);
			if(i%100==0)
				DEBUGPRINT1("%s\n",s);
		}
	}
  	exit(EXIT_SUCCESS);
  
  	return 0;
}

void
additionalUsage()
{
  	fprintf(stderr, "----- Additional Usage -----\n");
}

void 
lmrcImagePCA(mrcImage* Out, int nOut, mrcImage* In, int nIn, lmrcImagePCAInfo* linfo, int mode)
{
  	int count,i,j;
  	int p,q;
							       
 	float  x;
 	float  y;
 	float  z;
	
//    int x;
 // 	int y;
//	int z;
  	double data;
  	double sum;
 	
	dim = In[0].HeaderN.x*In[0].HeaderN.y*In[0].HeaderN.z;
	DEBUGPRINT1("dimension: %d\n", dim);
  	double* ave;
  	ave=new double[dim];
  
  	double** a;  
  	a = new double*[dim];
  	for(i=0;i<dim;i++)
    		a[i]=new double[dim*2];
  
  	double** b;
  	b = new double*[nIn];
  	for(i=0;i<nIn;i++)
    		b[i]=new double[dim];
  
  	double** c;
  	c=new double*[nIn];
  	for(i=0;i<nIn;i++)
    	c[i]=new double[dim];

	for(i=0; i<nOut; i++) {
		// (*Out).  <==>  Out-> 
		Out[i].HeaderN.x = linfo->NX;
		Out[i].HeaderN.y = linfo->NY;
  		Out[i].HeaderN.z = 1;
  		Out[i].HeaderLength.x = In->HeaderLength.x;
  		Out[i].HeaderLength.y = In->HeaderLength.y;
  		Out[i].HeaderLength.z = 0.0;
  		Out[i].HeaderMode =  In->HeaderMode;
  		mrcInit(&Out[i], NULL);
	}
  
  // real part data of the ith image at (x, y, z) 	
  // mrcPixelDataGet(&In[i], x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
  	for(i=0; i<nIn; i++){
    	count=0;
    	for(z=0;z<In->HeaderN.z;z++){
      	for(y=0;y<In->HeaderN.y;y++){
		for(x=0;x<In->HeaderN.x;x++){
			if(count%1000==0)
     			DEBUGPRINT2("count=%d i=%d\n",count,i);
	  		mrcPixelDataGet(&In[i], x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
	  		b[i][count]=data;
			count++;
		}
      	}
    	}
  	}
 
 	// Calculation of co-variance matrix  
	// Step 1: Calc Average of each pixel -> ave[i]
  	for(i=0;i<dim;i++){
		 if(i%1000==0)
	 		DEBUGPRINT("sumn=0\n");
    	sum=0.0;
    	for(j=0; j<nIn; j++){
      		sum=sum+b[j][i];
    	}
    	ave[i]=sum/nIn;
  	}
 
 	// Step 2: b(original data) -> c (average -> 0)   
  	for(i=0;i<dim;i++){
		if(i%1000==0)
		      DEBUGPRINT1("c i=%d\n",i);
    	for(j=0; j<nIn; j++){
      		c[j][i]=b[j][i]-ave[i];
    	}
  	}
 
 	// Step 3: Calc co-variance matrix 
  	for(i=0;i<dim;i++){
		if(i%1000==0)
			DEBUGPRINT1("a sum  i=%d\n",i);
    	for(j=i;j<dim;j++){
      		sum=0.0;
      		for(p=0;p<nIn;p++){
				sum=sum+c[p][i]*c[p][j];
      		}
      		a[i][j]=sum/nIn;
      		a[j][i]=a[i][j];
    	}
  	}
 
 	// Initialize u : eingen vectors -> Unit vector 
  	double** u = new double*[dim];
  	for(i=0;i<dim;i++)
    		u[i]=new double[dim];
  	for(i=0;i<dim;i++){
		 if(i%1000==0)
		 	DEBUGPRINT1("Initialize u i=%d\n",i);
    	for(j=0;j<dim;j++) {
      		if(i==j)
				u[i][j]=1;
      		else
				u[i][j]=0;
    	}
  	}
  
  	DEBUGPRINT("Calc eigen vector and eigen values: Start\n");
	count = 0;
	time_t start, current; 
	time(&start);
 	while(1){
    	double max;

		count++;
    	max=getMax(a, p, q);   // a:covar has the max value at (p, q), where p != q
		if(count%1000==0){
			DEBUGPRINT6("%d/%d = %f %% current %g EPS %g %g sec\n",count, dim*(dim-1)/2, 
				((float)count)/dim/(dim-1.0)*2*100, 
				(float)max, 
				linfo->EPS,
				difftime(time(&current), start));

			if(linfo->flagEPSOutcaletime==1)
				fprintf(linfo->fptEPSOutcaletime,"%d/%d = %f %% current %g EPS %g %g sec\n",count, dim*(dim-1)/2,
					((float)count)/dim/(dim-1.0)*2*100,
					(float)max,
					linfo->EPS,
					difftime(time(&current), start));
		}
		
    	transform(a,u,p,q);    // a:diagonal covar u: unit vector  
    	if(max<=linfo->EPS) {
			DEBUGPRINT("EPSbreak\n");
			if(linfo->flagEPSOutcaletime==1){
				fprintf(linfo->fptEPSOutcaletime,"EPSbreak\n");
				fprintf(linfo->fptEPSOutcaletime,"%d/%d = %f %% current %g EPS %g %g sec\n",count, dim*(dim-1)/2,
					((float)count)/dim/(dim-1.0)*2*100,
					(float)max,
					linfo->EPS,
					difftime(time(&current), start));
			}
      		break;
		}
  	}
  	DEBUGPRINT2("Calc eigen vector and eigen values: End : loop count %d num %d\n", count, linfo->numOfEigenImage);

  	double* amaxd;
  	amaxd=new double[dim];
  	int* amaxi;
  	amaxi=new int[dim];
  	double* aper;
  	aper =new double[dim];

  	double t;
  	int s;
  	double asum=0.0;
 	double asumsum=0.0;

	// Sum up the diagonal elements 
  	for(i=0;i<dim;i++){
		if(i%1000==0)
			DEBUGPRINT1("amaxd[i]f, amaxi[i], i=%d\n",i);
    	amaxd[i]=a[i][i];
    	amaxi[i]=i;
		asum=asum+a[i][i];
  	}
 
 	// Order
  	for(i=0;i<dim-1;i++){
		if(i%1000==0)
			DEBUGPRINT1("sort i=%d\n",i);
    	for(j=i;j<dim;j++){
      		if(amaxd[i]<amaxd[j]){
				t=amaxd[i];
				s=amaxi[i];
				amaxd[i]=amaxd[j]; // d: engine value  
				amaxi[i]=amaxi[j]; // i: original position 
				amaxd[j]=t;
				amaxi[j]=s;
      		}
    	}
  	}
 
 	// Weight of eigen values
	DEBUGPRINT("Weight of eigen value\n");
   	for(i=0;i<dim;i++){
		asumsum=asumsum+amaxd[i];
		aper[i]=(asumsum/asum)*100.0;
	}
 
 	// Set weights of each eigen vector for each image 
	DEBUGPRINT("Set weight of each eigen vector for each image\n");
  	for(i=0;i<nOut;i++) {
		q=0;
    	for(z=0;z<Out->HeaderN.z;z++){
      		for(y=0;y<Out->HeaderN.y;y++){
				for(x=0;x<Out->HeaderN.x;x++){
	  				sum=0.0;
	  				s=amaxi[q];           
	  				count=0;
	  				for(p=0;p<dim;p++) { // p: The index of each pixel of original image, dim = pixel Number 
										 //    the index of elements of each eigen vector  
										 // q: the index of sorted eigen values/vector 
										 // s: the index of originally-ordered eigen values/vector
	    				sum=sum+u[p][s]*(b[i][count]-ave[count]);
	    				count++;
	  				}
	  				data=sum;
	  				mrcPixelDataSet(&Out[i], x, y, z, data, mrcPixelRePart);
	  				q++;
				}
			}
      	}	
    } 

	linfo->Dimension            = dim;
	linfo->EigenValueOrder      = amaxi;
	linfo->EigenValue           = amaxd;
	linfo->IntegratedEigenValue = aper;

	linfo->EigenImage = new mrcImage[linfo->numOfEigenImage];
	for(q=0; q<linfo->numOfEigenImage; q++) {
		linfo->EigenImage[q].Header = In[0].Header;
		linfo->EigenImage[q].HeaderMode = mrcFloatImage;
		mrcInit(&(linfo->EigenImage[q]), NULL);
		s = amaxi[q];
		DEBUGPRINT2("q: %d s: %d\n", p, s);
		p = 0;
    	for(z=0; z<linfo->EigenImage[q].HeaderN.z; z++){
    	for(y=0; y<linfo->EigenImage[q].HeaderN.y; y++){
    	for(x=0; x<linfo->EigenImage[q].HeaderN.x; x++){
			data = u[p][s]; // s: Index of originally-ordered EigenValues/vectors, 
							// p: Index of each pixel   
			mrcPixelDataSet(&linfo->EigenImage[q], x, y, z, data, mrcPixelRePart);
			p++;	
			//DEBUGPRINT2("p: %d q: %d\n", p, q);
		}
		}
		}	
	}
}

double getMax(double** a, int& p, int& q){
  	double max=0.0;
  	int i,j;
  
  	for(i=0;i<dim-1;i++){
/*		if(i%1000==0)
			DEBUGPRINT1("getmax max dim=%d\n",dim);*/
    	for(j=i+1;j<dim;j++){
      		if(fabs(a[i][j])>max){
				p=i;
				q=j;
				max=fabs(a[i][j]);
      		}
    	}
  	}
  	return max;
}

void transform(double** a,double** u,int p,int q){
  	double alpha,beta,gamma;
  	double sine,cosine,w;
  	double wa,wb,wc;
  	int i,j;
  
  	wa=a[p][p];
  	wb=a[p][q];
  	wc=a[q][q];
  
  	alpha=-wb;
  	beta=(wa-wc)/2;
  	gamma=fabs(beta)/sqrt(alpha*alpha+beta*beta);
  
  	sine=sqrt((1.0-gamma)/2);
  	if(alpha*beta<0)
    		sine=-sine;
  	cosine=sqrt(1.0-sine*sine);
  
  	for(j=0;j<dim;j++){
/*		if(j%1000==0)
			DEBUGPRINT1("transform a[p][i] j=%d\n",j);*/
    	w=a[p][j]*cosine-a[q][j]*sine;
    	a[q][j]=a[p][j]*sine+a[q][j]*cosine;
    	a[p][j]=w;
  	}
  	for(j=0;j<dim;j++){
/*		if(j%1000==0)
			DEBUGPRINT1("transform a[j][q] j=%d\n",j);*/
    	a[j][p]=a[p][j];
    	a[j][q]=a[q][j];
  	}
  
  	w=2.0*wb*sine*cosine;
  	a[p][p]=wa*cosine*cosine+wc*sine*sine-w;
  	a[q][q]=wa*sine*sine+wc*cosine*cosine+w;
  	a[p][q]=a[q][p]=0;
  
  	for(i=0;i<dim;i++){
	/*	if(i%1000==0)
			DEBUGPRINT1("transform u[i][p] i=%d\n",i);*/
    	w=u[i][p]*cosine-u[i][q]*sine;
    	u[i][q]=u[i][p]*sine+u[i][q]*cosine;
    	u[i][p]=w;
  	}
}

