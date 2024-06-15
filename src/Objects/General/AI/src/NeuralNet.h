#ifndef NUERALNET_H
#define NUERALNET_H

typedef struct NeuralNetInfo {
	int  numOfLayer;
	int* numOfCellOfLayer; 
	int  numOfSeparation;
	int  numOfPositive;
	int  numOfNegative;
	int* bias;
	double Lambda;
} NeuralNetInfo;

extern void neuralNetOutputLayerCalculation(double** cell, double*** weight, NeuralNetInfo* linfo, int mode);
extern double neuralNetSigmoidalFunction(double cell);
extern void neuralNetRandomToWeight(double*** weight , NeuralNetInfo* linfo);
extern void neuralNetBackPropagation(double** cell, double*** weight, double Teacher, NeuralNetInfo* linfo, int mode);

#endif
