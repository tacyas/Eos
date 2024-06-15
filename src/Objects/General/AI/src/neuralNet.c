#include "genUtil.h"
#include "Memory.h"

#include "./NeuralNet.h"
#include <stdlib.h>
#include <time.h>

void 
neuralNetRandomToWeight(double*** weight , NeuralNetInfo* linfo)
{
	int i,j;
    int l,m,n;	

	//this is the memory of weight
	weight = (double***)memoryAllocate(sizeof(double**)*(linfo->numOfLayer-1), "in lmrcImageNeuralNetParticleLearning");
	for(i=0; i<linfo->numOfLayer-1; i++) {
		weight[i] = (double**)memoryAllocate(sizeof(double*)*(linfo->numOfCellOfLayer[i]+2), "in lmrcImageNeuralNetParticleLearning");
		for(j=0; j<linfo->numOfCellOfLayer[i]+2; j++) {
			weight[i][j] = (double*)memoryAllocate(sizeof(double)*(linfo->numOfCellOfLayer[i+1]+2), "lmrcImageNeuralNetParticleLearning");
		}
	}
	/*
	   weight[l][m][n] : the weight between the m'th cell in the l'th layer and the n'th cell in the l+1'th layer

	    l+1     .....n......
		            /
				   / weight[l][m][n]
				  /
		 l		.m..........  



         0      ............   :input-layer
	*/

	srand((unsigned)time(NULL));
	for( l=0; l<linfo->numOfLayer-1 ; l++)
	{
		for(  m=0; m<linfo->numOfCellOfLayer[l]+2; m++)
		{
			for(  n=0; n<linfo->numOfCellOfLayer[l+1]+2; n++)
			{
				weight[l][m][n] = (double)rand() / (double)RAND_MAX - 0.5;
				DEBUGPRINT4("firstweight[%d][%d][%d]=%f\n",l,m,n,weight[l][m][n]);
			}		
		}
	}
}

void
neuralNetOutputLayerCalculation(double** cell, double*** weight, NeuralNetInfo* linfo, int mode)
{
	int l,m,n;
	
    // Calclation
	DEBUGPRINT("Calculation start\n");
    for( l=0 ; l<linfo->numOfLayer-1 ; l++) {
		for( n=0 ; n<linfo->numOfCellOfLayer[l+1] ; n++ ) {
			cell[l+1][n] = 0;
			for( m=0 ; m<linfo->numOfCellOfLayer[l] ; m++ ) {
		   		cell[l+1][n]+=cell[l][m]*weight[l][m][n];
			}
			cell[l+1][n] = neuralNetSigmoidalFunction(cell[l+1][n]);
			DEBUGPRINT6("l=%d , m=%d , n=%d ,cell[%d][%d]=%f\n",l,m,n,l+1,n,cell[l+1][n]);
		}
	}
}

double
neuralNetSigmoidalFunction(double cell)
{
	return (1.0/(1.0+exp(cell)));
}

/*
	Estimate weights between layers using back-propagation

	Input: cell 
		   linfo

	Output: weight
*/

void neuralNetBackPropagation 
(double** cell, double*** weight, double Teacher, NeuralNetInfo* linfo, int mode)
{

	int i,j,l,m,n;
	double    sum;
	double**  squarederror;
    double*** weightadjust;
	
	DEBUGPRINT("Start Back Propagation\n");
	squarederror = (double**)memoryAllocate(sizeof(double**)*(linfo->numOfLayer), "in ImrcImageNeuralNetParticleLearning");
	for(i=0 ; i<linfo->numOfLayer ; i++) {
		squarederror[i] = (double*)memoryAllocate(sizeof(double)*(linfo->numOfCellOfLayer[i]+2), "in ImrcImageNeuralNetParticl			eLearning");
	}
	/*
	    squarederror[l][n] : the sqaurederror of n'th cell in the l'th layer

		l      . . . . n . . . .
		               |
				 squarederror[l][n]

	*/			
	
    
	weightadjust = (double***)memoryAllocate(sizeof(double**)*(linfo->numOfLayer-1), "in  lmrcImageNeuralNetParticleLearning");
	for(i=0; i<linfo->numOfLayer-1; i++) {
		weightadjust[i] = (double**)memoryAllocate(sizeof(double*)*(linfo->numOfCellOfLayer[i]+2), "in  lmrcImageNeuralNetParticleLearning");	
		for(j=0; j<linfo->numOfCellOfLayer[i]; j++) {
			weightadjust[i][j]=(double*)memoryAllocate(sizeof(double)*(linfo->numOfCellOfLayer[i+1]+2), "lmrcImageNeuralNetParticleLearning");
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

	for(i=0 ; i<linfo->numOfCellOfLayer[linfo->numOfLayer-1] ; i++) {
		squarederror[linfo->numOfLayer-1][i] = pow(cell[linfo->numOfLayer-1][i] - Teacher, 2.0 );
		DEBUGPRINT1("Top: %lf\n", squarederror[linfo->numOfLayer-1][i]);
    }
		
	for( m=0 ; m<linfo->numOfCellOfLayer[linfo->numOfLayer-2] ; m++) {
		for( n=0 ; n<linfo->numOfCellOfLayer[linfo->numOfLayer-1] ; n++) {
			weightadjust[linfo->numOfLayer-2][m][n] = -1.0 * linfo->Lambda * squarederror[linfo->numOfLayer-1][n] * cell[linfo->numOfLayer-2][m] ;
			DEBUGPRINT3("Adjust from Top: wa %lf cell %lf sqr %lf\n", 
					weightadjust[linfo->numOfLayer-2][m][n],  
					cell[linfo->numOfLayer-2][m],
					 squarederror[linfo->numOfLayer-1][n]);
		}	
	}	

		
	for( l=linfo->numOfLayer-2 ; l>0 ; l--) {
		for( m=0 ; m<linfo->numOfCellOfLayer[l] ; m++) {   
		    sum=0;
			for( n=0 ; n<linfo->numOfCellOfLayer[l+1] ; n++) {
	       		sum += weight[l][m][n] * squarederror[l+1][n] ;
			}	
			squarederror[l][m] = sum * (cell[l][m] * (1.0 - cell[l][m]));
		}
	
		for( m=0 ; m<linfo->numOfCellOfLayer[l-1] ; m++) {
			for( n=0 ; n<linfo->numOfCellOfLayer[l] ; n++) {
				weightadjust[l-1][m][n] = -1.0 * linfo->Lambda * squarederror[l][n] * cell[l-1][m] ;
			    DEBUGPRINT4("weightadjust[%d][%d][%d]=%f\n",l-1,m,n,weightadjust[l-1][m][n]);
			}
		}	
	}		

	DEBUGPRINT("weightadjust finish\n");
    for( l=0 ; l<linfo->numOfLayer-1 ; l++) {
    	for( m=0 ; m<linfo->numOfCellOfLayer[l] ; m++) {
			for ( n=0 ; n<linfo->numOfCellOfLayer[l+1] ; n++) {
				weight[l][m][n] += weightadjust[l][m][n];
				DEBUGPRINT4("weight[%d][%d][%d]=%f\n",l,m,n,weight[l][m][n]);
			}
		}
	}
	DEBUGPRINT("weight finish\n");

	/* release heap-areas */
	for(i=0 ; i<linfo->numOfLayer ; i++) {
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

	DEBUGPRINT("End Back Propagation\n");
}


