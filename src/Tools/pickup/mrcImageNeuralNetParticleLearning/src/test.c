/*
# mrcImageNeuralNetParticleLearning : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageNeuralNetParticleLearning
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
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Memory.h"
#include "eosString.h"
#define Maxcounter    5000
#define EPS           0.005
#define E             0.1

/*
#include "pickup.h"
*/

typedef struct lmrcImageNeuralNetParticleLearningInfo {
	int  numOfLayer;
	int* numOfCellOfLayer; 
	int  numOfSeparation;
	int  numOfPositive;
	int  numOfNegative;
	int* bias;
} lmrcImageNeuralNetParticleLearningInfo;

typedef enum lmrcImageNeuralNetParticleLearningMode {
	a=0,
	b=1
} lmrcImageNeuralNetParticleLearningMode;

extern void lmrcImageNeuralNetParticleLearning(mrcImage* weight, double*** weight, mrcImage* positive, mrcImage* negative, lmrcImageNeuralNetParticleLearningInfo* linfo, int mode);
extern void OutputLayerCalculation(double** cell, double*** weight, mrcImage* in,  lmrcImageNeuralNetParticleLearningInfo* linfo, int mode);
extern double sigmoidalFunction(mrcImage* positive,double** cell);
extern void RandomToWeight(lmrcImageNeuralNetParticleLearningInfo* linfo, double*** weight);
extern void Back_propagation(double** cell, double*** weight, mrcImage* in, lmrcImageNeuralNetParticleLearningInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageNeuralNetParticleLearningInfo info;
	lmrcImageNeuralNetParticleLearningInfo linfo;
    mrcImage*  weightImage;
	mrcImage  in;
	mrcImage* positive;
	mrcImage* negative;
	double**    cell;
	double***    weight;
	int mode;
	int i,j;
	int counter    = 0;
	double error   = 0;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

  	// Information Set 		 	
	linfo.numOfLayer = info.flagOut + 1;		
	linfo.numOfCellOfLayer = (int*)memoryAllocate(sizeof(int)*linfo.numOfLayer, "in main");
	fseek(info.fptOutList, 0L, SEEK_SET);
	for(i=1; i<linfo.numOfLayer; i++) {
		char s[1024];			
		fgets(s, 1023, info.fptOutList);
		linfo.numOfCellOfLayer[i] = stringGetNthIntegerData(s, 2, " ,\t");
		linfo.bias[i]             = stringGetNthIntegerData(s, 3, " ,\t");
	}
	linfo.numOfCellOfLayer[0] = 0;
	linfo.bias[0]             = info.Bias;

	positive = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInPositive, "in main for positive");
	for(i=0; i<info.flagInPositive; i++) {
		mrcFileRead(&positive[i], info.InPositive[i], "in main for positive", 0);
		if(0==linfo.numOfCellOfLayer[0]) {
			linfo.numOfCellOfLayer[0] = positive[i].PixelPerImage;
		} else if(linfo.numOfCellOfLayer[0] != positive[i].PixelPerImage){
			fprintf(stderr, "The size of image %d is different from image 0\n", i);  			
			exit(EXIT_FAILURE);
		}
	}
	negative = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInNegative, "in main for negative");
	for(i=0; i<info.flagInNegative; i++) {
		mrcFileRead(&negative[i], info.InNegative[i], "in main for negative", 0);
		if(linfo.numOfCellOfLayer[0] != negative[i].PixelPerImage){
			fprintf(stderr, "The size of image %d is different from image 0\n", i);  			
			exit(EXIT_FAILURE);
		}
	}
	linfo.numOfPositive = info.flagInPositive;
	linfo.numOfNegative = info.flagInNegative;

	weightImage = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagOut, "in main for weight");


    //this is memory of weight
    
	weight = (double***)memoryAllocate(sizeof(double**)*sizeof(linfo->numOfLayer-1), "in  lmrcImageNeuralNetParticleLearning");
	for(i=0; i<linfo->numOfLayer-1; i++) {
		weight[i] = (double**)memoryAllocate(sizeof(double*)*sizeof(linfo->numOfCellOfLayer[i]+2), "in  lmrcImageNeuralNetParticleLearning");	
		for(j=0; j<linfo->numOfCellOfLayer[i]; j++) {
			weight[i][j]=(double*)memoryAllocate(sizeof(double)*sizeof(linfo->numOfCellOfLayer[i+1]+2), "lmrcImageNeuralNetParticleLearning");
		}
	}
	/*
		weight[l][m][n] : the weight between the m'th cell in the l'th layer and the n'th cell in the l+1'th layer   

			l+1      ..... n ..... 
                          /
                         / weight[l][m][n]
                        / 
			l        . m .........
 


			0        .............     : input-layer
	/*

	// main's caluclation

	RandomToWeight(&linfo,weight);

    while(counter++ < Maxcounter && ESP < error)
	{
		error = 0;
		lmrcImageNeuralNetParticleLearning( weightImage, weight, positive, negative, &linfo, mode);
                for( j=0 ; j<linfo.numOfCellOfLayer[linfo.numOfLayer-1] ; j++)
					error += pow( 1 -  cell[linfo.numOfLayer-1][j], 2.0);
	}
				

	
	for(i=0; i<info.flagOut; i++) {
		mrcFileWrite(&weightImage[i], info.Out[i], "in main for weight", 0);
	}

	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}





void 
lmrcImageNeuralNetParticleLearning(
		mrcImage* weightImage, 
		double*** weight;
		mrcImage* positive, 
		mrcImage* negative, 
		lmrcImageNeuralNetParticleLearningInfo* linfo, 
		int mode)
{
	int i, j, k;
	int l,m,n;
	double**  cell;
	double*** weight;
	int x, y, z;

	cell = (double**)memoryAllocate(sizeof(double*)*sizeof(linfo->numOfLayer), "in  lmrcImageNeuralNetParticleLearning");
	for(i=0; i<linfo->numOfLayer; i++) {	
		cell[i] = (double*)memoryAllocate(sizeof(double)*sizeof(linfo->numOfCellOfLayer[i]+2), "in  lmrcImageNeuralNetParticleLearning");
	}
	/*
		cell[l][n] : the value of the n'th cell in the l'th layer 	
			
			l		..... n .......
						  |
						cell[l][n]
	*/



    // Learning caluclation
	while(1) {
		for(k=0; k<linfo->numOfSeparation; k++) {
			for(i=k*linfo->numOfPositive/linfo->NumOfSepartion; i<(k+1)*linfo->numOfPositive/linfo->NumOfSepartion && i<linfo->numOfPositive; i++) {
				OutputLayerCalculation(cell, weight, &positive[i], linfo, mode); 	
            	Back_propagation(cell, weight, 1, &linfo, mode);
			
			}
			for(i=k*linfo->numOfNegative/linfo->NumOfSepartion; i<(k+1)*linfo->numOfNegative/linfo->NumOfSepartion &&  i<linfo->numOfNegative; i++) {
				OutputLayerCalculation(cell, weight, &negative[i], linfo, mode); 	
            	Back_propagation(cell, weight, 0, &linfo, mode);
			}
		}
	}


	for(i=0; i<linfo->numOfLayer-1; i++) {		
		weightImage[i].HeaderN.x = linfo->numOfCellOfLayer[i]; 
		weightImage[i].HeaderN.y = linfo->numOfCellOfLayer[i+1]; 
		weightImage[i].HeaderN.z = 1;
		weightImage[i].HeaderMode = mrcFloatImage;
		mrcInit(&weightImage[i], NULL);

		for(x=0; x<weightImage[i].HeaderN.x; x++) {
		for(y=0; y<weightImage[i].HeaderN.y; y++) {
			mrcPixelDataSet(&weightImage[i], x, y, 0, weight[i][x][y], mrcPixelRePart);
		}
		}
	}
	
}




void RandomToWeight(lmrcImageNeuralNetParticleLearningInfo* linfo, double*** weight)
{
	int l,m,n;
	srand((unsigned)time(NULL));

	for( l=0; l<linfo->numOfLayer-2 ; l++)
	{
		for(  m=0; m<linfo->numOfCellOfLayer[l] ; m++)
		{
			for(  n=0; n<linfo->numOfCellOfLayer[l+1] ; n++)
			{
				weight[l][m][n] = (double)rand() /(double) RAND_MAX - 0.5 ;
			}		
		}
	}
}





void
OutputLayerCalculation(double** cell, double*** weight, mrcImage* in,  lmrcImageNeuralNetParticleLearningInfo* linfo, int mode)
{
	float x, y, z;	
	int n;

	n = 0;
	for(x=0; x<in->HeaderN.x; x++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(z=0; z<in->HeaderN.z; z++) {
		mrcPixelDataGet(in, x, y, z, &cell[0][n], mrcPixelRePart, mrcPixelHowNearest);
		cell[0][n] = sigmoidalFunction(cell[0][n] - in->HeaderAMean);
		n++;
	}
	}
	}
	cell[0][linfo->numOfCellOfLayer[0]] = linfo->bias[0];
	cell[0][linfo->numOfCellOfLayer[0]+1] = in->HeaderAMean;

 	
    // Calclation

			
        for( l=0 ; l<linfo->numOfLayer-2 ; l++)
		{
			for( n=0 ; n<linfo->numOfCellOfLayer[l+1] ; n++ )
			{
				for( m=0 ; m<linfo->numOfCellOfLayer[l] ; m++ )
				{
		   		 	cell[l+1][n]+=cell[l][m]*weight[l][m][n];
				}
					cell[l+1][n]=sigmoidalFunction(cell[l+1][n]);
			}
		}		

	
}





double
sigmoidalFunction(double** cell)
{
	return (1.0/(1.0+exp(cell)));
}



/*
	Estimate weights between layers using back-propagation

	Input: cell 
		   linfo

	Output: weight
*/

void Back_propagation
(double** cell, double*** weight, double Teacher, lmrcImageNeuralNetParticleLearningInfo* linfo, int mode)
{

	int i,j,l,m,n;
	double    sum;
	double**  squarederror;
    double*** weightadjust;

	squarederror = (double**)memoryAllocate(sizeof(double**)*sizeof(linfo->numOfLayer), "in ImrcImageNeuralNetParticleLearning");
	for(i=0 ; i<linfo->numOfLayer ; i++)
	{
		squarederror[i] = (double*)memoryAllocate(sizeof(double)*sizeof(linfo->numOfCellOfLayer[i]+2), "in ImrcImageNeuralNetParticl			eLearning");
	}
	/*
	    squarederror[l][n] : the sqaurederror of n'th cell in the l'th layer

		l      . . . . n . . . .
		               |
				 squarederror[l][n]

	*/			
	
    
	weightadjust = (double***)memoryAllocate(sizeof(double**)*sizeof(linfo->numOfLayer-1), "in  lmrcImageNeuralNetParticleLearning");
	for(i=0; i<linfo->numOfLayer-1; i++) {
		weightadjust[i] = (double**)memoryAllocate(sizeof(double*)*sizeof(linfo->numOfCellOfLayer[i]+2), "in  lmrcImageNeuralNetParticleLearning");	
		for(j=0; j<linfo->numOfCellOfLayer[i]; j++) {
			weightadjust[i][j]=(double*)memoryAllocate(sizeof(double)*sizeof(linfo->numOfCellOfLayer[i+1]+2), "lmrcImageNeuralNetParticleLearning");
		}
	}
    /*
	    weightadjust[l][m][n] : the weightadjust adjust weight of l'th layer between m'th cell in the l'th layer and n'th cell in the l-1'th layer

		l+1    . . . . n . . . .
                      / 
					 /  weightadjust[l][m][n]
					/ 
		l      . . m . . . . . .
    */




    /*  OutputLayer' caluclation  */

	for(i=0 ; i<linfo->numOfCellOfLayer[linfo->numOfLayer-1] ; i++)
	{
		squarederror[linfo->numOfLayer-1][i] = pow(cell[linfo->numOfLayer-1][i] - Teacher, 2.0 );
    }
		
	for( m=0 ; m<linfo->numOfCellOfLayer[linfo->numOfLayer-2] ; m++)
	{
		for( n=0 ; n<linfo->numOfCellOfLayer[linfo->numOfLayer-1] ; n++)
	    {
			weightadjust[linfo->numOfLayer-2][m][n] = -1.0 * E * squarederror[linfo->numOfLayer-1][n] * cell[linfo->numOfLayer-2][m] ;
		}	
	}	

		
	for( l=linfo->numOfLayer-2 ; l>=0 ; l--)
	{
		for( m=0 ; m<linfo->numOfCellOfLayer[l] ; m++)
		{   
		    sum=0;
			for( n=0 ; n<linfo->numOfCellOfLayer[l+1] ; n++)
			{
	       		sum += weight[l][m][n] * squarederror[l+1][n] ;
			}	
			squarederror[l][m] = sum * (cell[l][m] * (1.0 - cell[l][m]));
		}
		
		for( m=0 ; m<linfo->numOfCellOfLayer[l-1] ; m++)
		{
			for( n=0 ; n<linfo->numOfCellOfLayer[l] ; n++)
			{
				weightadjust[l-1][m][n] = -1.0 * E * squarederror[l][n] * cell[l-1][m] ;
			}
		}
	}		


    for( l=0 ; l<linfo->numOfLayer-2 ; l++)
    {
    	for( m=0 ; m<linfo->numOfCellOfLayer[l] ; m++)
		{
			for ( n=0 ; n<linfo->numOfCellOfLayer[l+1] ; n++)
			{
				weight[l][m][n] += weightadjust[l][m][n];
			}
		}
	}
	
	/* release heap-areas */
	for(i=0 ; i<linfo->numOfLayer ; i++)
	{
		free(squarederror[i]);
	}
	free(squarederror);

	for(i=0; i<linfo->numOfLayer-1; i++) {
		for(j=0; j<linfo->numOfCellOfLayer[i]; j++) {
			free(weightadjust[i][j]);
		}
		free(weightadjust[i]);
	}
	free(weightadjust);
}



