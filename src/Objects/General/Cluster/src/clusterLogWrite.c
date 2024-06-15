/*
# clusterLogWrite : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : clusterLogWrite 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <string.h> 
#define DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "Memory.h"
#include "mrcImage.h"
#include "../inc/Cluster.h"


clusterLogOneRecord*
clusterLogWrite(clusterLog* in, FILE* fpt, int mode)
{
	char  s[1024];
	char* stmp;
	clusterLogOneRecord * cluster;

	cluster = in->current;
	return clusterLogWriteOneRecord(cluster, fpt, mode);	
}

clusterLogOneRecord*
clusterLogWriteBinary2(clusterLog* in, FILE* fpt, int mode)
{
	char  s[1024];
	char* stmp;
	clusterLogOneRecord * cluster;

	cluster = in->current;
	return clusterLogWriteOneRecordBinary2(cluster, fpt, mode);	
}

clusterLogOneRecord*
clusterLogWriteOneRecord(clusterLogOneRecord* cluster, FILE* fpt, int mode)
{
	if(NULL!=cluster) {
		switch(mode) {
			case 0: {
				fprintf(fpt, "%10d %10d %10d %10d %15.6g\n", 
					cluster->N, cluster->M, 
					cluster->prevN, cluster->prevM, 
					cluster->distance);
				break;
			}
			case 1: {
				if(NULL!=cluster->belowLayer) {
					fprintf(fpt, "%10d %10d %15.6g Number: %10d below %10d %10d <- %10d %10d\n", 
						cluster->N, cluster->M, 
						cluster->distance,
						cluster->clusterNumber,
						cluster->prevN, cluster->prevM, 
						cluster->belowLayer->N, cluster->belowLayer->M); 
				} else {
					clusterLogWriteOneRecord(cluster, fpt, 0);
				}
				break;
			}
			case 2: {
				if(NULL!=cluster->belowLayer) {
					fprintf(fpt, "%10d %10d %10d %10d %15.6g %10d %10d", 
						cluster->N, cluster->M, cluster->prevN, cluster->prevM, cluster->distance,
						cluster->belowLayer->N, cluster->belowLayer->M);
				} else {
					clusterLogWriteOneRecord(cluster, fpt, 0);
				}

				if(NULL!=cluster->belowLayerForN) {
					fprintf(fpt, "%10d %10d", cluster->belowLayerForN->N, cluster->belowLayerForN->M);
				} else {
					fprintf(fpt, "%10d %10d", -1, -1);
				}
				if(NULL!=cluster->belowLayerForM) {
					fprintf(fpt, "%10d %10d", cluster->belowLayerForM->N, cluster->belowLayerForM->M);
				} else {
					fprintf(fpt, "%10d %10d", -1, -1);
				}
				fprintf(fpt, "\n");
				break;
			}
			case 3: {
				fprintf(fpt, "%10d %10d %10d %10d %15.6g original %10d %10d first %10d %10d ", 
					cluster->N, cluster->M, cluster->prevN, cluster->prevM, cluster->distance,
					cluster->firstN, cluster->firstM,
					cluster->originalN, cluster->originalM);
				if(0<cluster->clusterSize){
					fprintf(fpt, "%10d =", cluster->clusterSize);	
				} else {
					fprintf(fpt, "%10s ", "NULL");	
				}
				if(cluster->belowLayerForN != NULL) {
					fprintf(fpt, "%10d + ", cluster->belowLayerForN->clusterSize);
				} else {
					fprintf(fpt, "%10d + ", 1);
				}
				if(cluster->belowLayerForM != NULL) {
					fprintf(fpt, "%10d ", cluster->belowLayerForM->clusterSize);
				} else {
					fprintf(fpt, "%10d ", 1);
				}
				if(0<cluster->clusterNumber){
					fprintf(fpt, "%10d ", cluster->clusterNumber);	
				}
				fprintf(fpt, "\n");
				break;
			}
			case 4: {
				clusterLogOneRecord* tmp;
				for(tmp=cluster; tmp!=NULL; tmp=tmp->belowLayer) {
					while(tmp->belowLayerForN==NULL || tmp->belowLayerForM == NULL) {
						if(tmp->prev!=NULL) {
							tmp = tmp->prev;
						} else {
							exit(EXIT_FAILURE);
						}
					}
					fprintf(fpt, "%10d %10d %10d %10d %15.6f below %10d %10d\n", 
						cluster->N, cluster->M, cluster->prevN, cluster->prevM, cluster->distance,
						tmp->belowLayerForN->N, tmp->belowLayerForN->M);
				}
				break;
			}
			default: {
				break;
			}
		}
	}	
	return cluster;
}

clusterLogOneRecord*
clusterLogWriteOneRecordBinary2(clusterLogOneRecord* cluster, FILE* fpt, int mode)
{
	clusterTypeInteger N, M;

	if(NULL!=cluster) {
		switch(mode) {
			case 0: {
				fwrite(&cluster->N, sizeof(cluster->N), 1, fpt);	
				fwrite(&cluster->M, sizeof(cluster->M), 1, fpt);	
				fwrite(&cluster->prevN, sizeof(cluster->prevN), 1, fpt);	
				fwrite(&cluster->prevM, sizeof(cluster->prevM), 1, fpt);	
				fwrite(&cluster->distance, sizeof(cluster->distance), 1, fpt);	
				break;
			}
			case 1: {
				if(NULL!=cluster->belowLayer) {

					fwrite(&cluster->N, sizeof(cluster->N), 1, fpt);	
					fwrite(&cluster->M, sizeof(cluster->M), 1, fpt);	
					fwrite(&cluster->distance, sizeof(cluster->distance), 1, fpt);	
					fwrite(&cluster->clusterNumber, sizeof(cluster->clusterNumber), 1, fpt);	
					fwrite(&cluster->prevN, sizeof(cluster->prevN), 1, fpt);	
					fwrite(&cluster->prevM, sizeof(cluster->prevM), 1, fpt);	
					fwrite(&cluster->belowLayer->N, sizeof(cluster->belowLayer->N), 1, fpt);	
					fwrite(&cluster->belowLayer->M, sizeof(cluster->belowLayer->M), 1, fpt);	
				} else {
					clusterLogWriteOneRecordBinary2(cluster, fpt, 0);
				}
				break;
			}
			case 2: {
				if(NULL!=cluster->belowLayer) {
					fwrite(&cluster->N, sizeof(cluster->N), 1, fpt);	
					fwrite(&cluster->M, sizeof(cluster->M), 1, fpt);	
					fwrite(&cluster->prevN, sizeof(cluster->prevN), 1, fpt);	
					fwrite(&cluster->prevM, sizeof(cluster->prevM), 1, fpt);	
					fwrite(&cluster->distance, sizeof(cluster->distance), 1, fpt);	
					fwrite(&cluster->belowLayer->N, sizeof(cluster->belowLayer->N), 1, fpt);	
					fwrite(&cluster->belowLayer->M, sizeof(cluster->belowLayer->M), 1, fpt);	
				} else {
					clusterLogWriteOneRecordBinary2(cluster, fpt, 0);
				}

				if(NULL!=cluster->belowLayerForN) {
					fwrite(&cluster->belowLayerForN->N, sizeof(cluster->belowLayerForN->N), 1, fpt);	
					fwrite(&cluster->belowLayerForN->M, sizeof(cluster->belowLayerForN->M), 1, fpt);	
				} else {
					N = -1;
					M = -1;
					fwrite(&N, sizeof(N), 1, fpt);	
					fwrite(&M, sizeof(M), 1, fpt);	
				}
				if(NULL!=cluster->belowLayerForM) {
					fwrite(&cluster->belowLayerForM->N, sizeof(cluster->belowLayerForM->N), 1, fpt);	
					fwrite(&cluster->belowLayerForM->M, sizeof(cluster->belowLayerForM->M), 1, fpt);	
				} else {
					N = -1;
					M = -1;
					fwrite(&N, sizeof(N), 1, fpt);	
					fwrite(&M, sizeof(M), 1, fpt);	
				}
				break;
			}
			case 3: {
				fwrite(&cluster->N, sizeof(cluster->N), 1, fpt);	
				fwrite(&cluster->M, sizeof(cluster->M), 1, fpt);	
				fwrite(&cluster->prevN, sizeof(cluster->prevN), 1, fpt);	
				fwrite(&cluster->prevM, sizeof(cluster->prevM), 1, fpt);	
				fwrite(&cluster->distance, sizeof(cluster->distance), 1, fpt);	
				fwrite(&cluster->firstN, sizeof(cluster->firstN), 1, fpt);	
				fwrite(&cluster->firstM, sizeof(cluster->firstM), 1, fpt);	
				fwrite(&cluster->originalN, sizeof(cluster->originalN), 1, fpt);	
				fwrite(&cluster->originalM, sizeof(cluster->originalM), 1, fpt);	

				if(0<cluster->clusterSize){
					fwrite(&cluster->clusterSize, sizeof(cluster->clusterSize), 1, fpt);	
				} else {
					N = -1;
					fwrite(&N, sizeof(N), 1, fpt);	
				}
				if(cluster->belowLayerForN != NULL) {
					fwrite(&cluster->belowLayerForN->clusterSize, sizeof(cluster->belowLayerForN->clusterSize), 1, fpt);	
				} else {
					N = 1;
					fwrite(&N, sizeof(N), 1, fpt);	
				}
				if(cluster->belowLayerForM != NULL) {
					fwrite(&cluster->belowLayerForM->clusterSize, sizeof(cluster->belowLayerForM->clusterSize), 1, fpt);	
				} else {
					M = 1;
					fwrite(&M, sizeof(M), 1, fpt);	
				}

				if(0<cluster->clusterNumber){
					fwrite(&cluster->clusterNumber, sizeof(cluster->clusterNumber), 1, fpt);	
				} else {
					N = -1;
					fwrite(&N, sizeof(N), 1, fpt);	
				}
				break;
			}
			case 4: {
				clusterLogOneRecord* tmp;
				for(tmp=cluster; tmp!=NULL; tmp=tmp->belowLayer) {
					while(tmp->belowLayerForN==NULL || tmp->belowLayerForM == NULL) {
						if(tmp->prev!=NULL) {
							tmp = tmp->prev;
						} else {
							exit(EXIT_FAILURE);
						}
					}

					fwrite(&cluster->N, sizeof(cluster->N), 1, fpt);	
					fwrite(&cluster->M, sizeof(cluster->M), 1, fpt);	
					fwrite(&cluster->prevN, sizeof(cluster->prevN), 1, fpt);	
					fwrite(&cluster->prevM, sizeof(cluster->prevM), 1, fpt);	
					fwrite(&cluster->distance, sizeof(cluster->distance), 1, fpt);	
					fwrite(&tmp->belowLayerForN->N, sizeof(cluster->belowLayerForN->N), 1, fpt);	
					fwrite(&tmp->belowLayerForN->M, sizeof(cluster->belowLayerForN->M), 1, fpt);	
				}
				break;
			}
			default: {
				break;
			}
		}
	}	
	return cluster;
}

clusterLogOneRecord*
clusterLogWriteAll(clusterLog* cluster, FILE* fpt, int mode)
{
	clusterLogOneRecord* last=NULL;

	cluster->current = cluster->top; 
	if(NULL==cluster->current) {
		fprintf(stderr, "No Cluster\n");
		exit(EXIT_FAILURE);
	}
	while(NULL!=clusterLogWrite(cluster, fpt, mode)) {
		last = cluster->current;
		cluster->current = cluster->current->next;
	}
	return last;
}

clusterLogOneRecord*
clusterLogWriteAllBinary2(clusterLog* cluster, FILE* fpt, int mode)
{
	clusterLogOneRecord* last=NULL;

	cluster->current = cluster->top; 
	if(NULL==cluster->current) {
		fprintf(stderr, "No Cluster\n");
		exit(EXIT_FAILURE);
	}
	while(NULL!=clusterLogWriteBinary2(cluster, fpt, mode)) {
		last = cluster->current;
		cluster->current = cluster->current->next;
	}
	return last;
}

clusterLogOneRecord*
clusterLogWriteAllBinary(clusterLog* in, char* basename, int mode)
{
	clusterLogOneRecord* last    = NULL;
	clusterLogOneRecord* cluster = NULL;
	int N, combinationN;
	int i;
	mrcImage log;
	char s[1024];
	char filename[1024];
	double data;
	float x, y;

	cluster = in->top;	
	if(NULL==cluster) {
		fprintf(stderr, "No Cluster in clusterLogWriteAllBinary\n");
		exit(EXIT_FAILURE);			
	} 

	if(cluster->prevN != cluster->prevM) {
		fprintf(stderr, "This log does not have the first line\n");
		exit(EXIT_FAILURE);
	} else { 
		N = cluster->prevN;			
	}

	i = 0;
	combinationN = N*(N-1)/2;
	while(NULL!=cluster) {
		if(0==i) { /* This layer has just started. */
			log.HeaderN.x = N;	
			log.HeaderN.y = N;	
			log.HeaderN.z = 1;	
			log.HeaderMode = mrcFloatImage;
			mrcInit(&log, NULL);
			sprintf(filename,  CLUSTERLOG_BINARY_FILENAME_FORMAT, basename, cluster->prevN, cluster->prevM, N);
			for(x=0;x<N;x++) {
			for(y=0;y<N;y++) {
				mrcPixelDataSet(&log, x, y, 0, CLUSTERLOG_BINARY_NO_CALCULATION_VALUE, mrcPixelRePart);
			}
			}
		}

		/**/
		mrcPixelDataGet(&log, cluster->N, cluster->N, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(data<cluster->distance) {
			mrcPixelDataSet(&log, cluster->N, cluster->N, 0, data, mrcPixelRePart);
		}
		mrcPixelDataGet(&log, cluster->M, cluster->M, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(data<cluster->distance) {
			mrcPixelDataSet(&log, cluster->M, cluster->M, 0, data, mrcPixelRePart);
		}
		
		mrcPixelDataSet(&log, cluster->N, cluster->M, 0, cluster->distance, mrcPixelRePart);  
		mrcPixelDataSet(&log, cluster->M, cluster->N, 0, cluster->distance, mrcPixelRePart);  

		i++; /* Next log */
		last = cluster;
		cluster = cluster->next;

		if(combinationN<=i) { /* This layer has finished. */
			mrcFileWrite(&log, filename, "in clusterLogWriteAllBinary", 0);
			
			N -= 1;
			combinationN = N*(N-1)/2;
			i = 0;
			mrcImageFree(&log, "in LogBinary");
		}
	}
	return last;
}

clusterLogOneRecord*
clusterLogWriteClusterOnly(clusterLog* cluster, FILE* fpt, int mode)
{
	clusterLogOneRecord* last=NULL;

	cluster->current = cluster->bottom; 
	if(NULL==cluster->current) {
		fprintf(stderr, "No Cluster\n");
		exit(EXIT_FAILURE);
	}
	while(NULL!=cluster->current->belowLayer) {
		cluster->current = cluster->current->belowLayer;
	}
	while(NULL!=clusterLogWrite(cluster, fpt, mode)) {
		last = cluster->current;
		DEBUGPRINT1("ClusterSize: %d\n", cluster->current->clusterSize);
		cluster->current = cluster->current->upperLayer;
	}
	return last;
}

#include "psFile.h"

void
clusterLogWritePS0(clusterLogOneRecord* cluster, psFile* ps, clusterTreeInfo* linfo, int mode)
{
	float shoulderN;
	float shoulderM;
	float armN;
	float armM;
	float tick;
	float x,y;
	float tmp;
	char s[1024];
	clusterLogOneRecord* tmpCluster;	
	int tmpN;

	if(NULL==cluster) {
		return;
	} 
	DEBUGPRINT2("N: %d M: %d\n", cluster->N, cluster->M);

	x = linfo->posX;
	y = linfo->posY;
	if(NULL==cluster->belowLayerForN) {
		shoulderN = 1;
		if(linfo->flagLog) {
			armN      = MAX(0,log10(cluster->distance)-log10(linfo->ArmOffset));
		} else {
			armN      = MAX(0,cluster->distance-linfo->ArmOffset);
		}
	} else {
		shoulderN = cluster->belowLayerForN->clusterSize;
		if(linfo->flagLog) {
			armN      = log10(cluster->distance) - log10(cluster->belowLayerForN->distance); 
		} else {
			armN      = cluster->distance - cluster->belowLayerForN->distance; 
		}
	}

	if(NULL==cluster->belowLayerForM) {
		shoulderM = 1;
		if(linfo->flagLog) {
			armM      = MAX(0,log10(cluster->distance)-log10(linfo->ArmOffset));
		} else {
			armM      = MAX(0,cluster->distance-linfo->ArmOffset);
		}
	} else {
		shoulderM = cluster->belowLayerForM->clusterSize;
		if(linfo->flagLog) {
			armM      = log10(cluster->distance) - log10(cluster->belowLayerForM->distance);
		} else {
			armM      = cluster->distance - cluster->belowLayerForM->distance;
		}
	}
	
	shoulderN /= 2.0;
	shoulderM /= 2.0;

	shoulderN *= linfo->ShoulderScale;	
	shoulderM *= linfo->ShoulderScale;	
	armN      *= linfo->ArmScale;	
	armM      *= linfo->ArmScale;	
	tick       = 1;

	tmp = shoulderN;
	shoulderN = -1.0*shoulderM;
	shoulderM = tmp;

	psFileLineDraw(ps, x-tick, y,           x,      y);           /* tick */
	psFileLineDraw(ps, x,      y+shoulderN, x,      y+shoulderM); /* shoulder */  
	psFileLineDraw(ps, x,      y+shoulderN, x+armN, y+shoulderN); /* armN */ 
	psFileLineDraw(ps, x,      y+shoulderM, x+armM, y+shoulderM); /* armM */

	tmpN = MAX(cluster->firstN, cluster->firstM);
	tmpCluster = cluster->belowLayerForN;
	while(NULL!=tmpCluster) {
		tmpN = tmpCluster->firstM;
		tmpCluster = tmpCluster->belowLayerForM;
	}
	sprintf(s, "%6d", tmpN);
	psFileString(ps, s, x-0.15*linfo->ArmScale, y+0.1*linfo->ShoulderScale, 0); 

	if(linfo->flagFPTTreeInfo) {
		fprintf(linfo->fptTreeInfo, "%06d %15.6f %15.6f %15.6f %15.6f %15.6f %15.6f\n", tmpN, x, y, shoulderM, shoulderN, armM, armN);	
	}

	/* Down Arm */
	if(NULL==cluster->belowLayerForN) {
		if(linfo->In!=NULL) {
			sprintf(s, "%6d %6d %s",       linfo->currentNo, cluster->firstN, linfo->In[cluster->firstN]);
			DEBUGPRINT2("N: %6d %s\n", cluster->firstN, linfo->In[cluster->firstN]);
		} else {
			sprintf(s, "%6d %6d", linfo->currentNo, cluster->firstN);
		}
		linfo->InPosX[cluster->firstN]        = x;
		linfo->InPosY[cluster->firstN]        = y+shoulderN-linfo->ShoulderScale*0.5;
		psFileString(ps, s, x+armN+tick, y+shoulderN-linfo->ShoulderScale*0.5, 0); 
		linfo->currentNo--;
	} else {
		linfo->InPosX[cluster->belowLayerForN->firstM] = x;  

		/* To Down */
		linfo->posX = x+armN; 
		linfo->posY = y+shoulderN; 
		clusterLogWritePS0(cluster->belowLayerForN, ps, linfo, mode);
	}

	/* Up Arm */	
	if(NULL==cluster->belowLayerForM) {
		if(linfo->In!=NULL) {
			sprintf(s, "%6d %6d %s", linfo->currentNo, cluster->firstM, linfo->In[cluster->firstM]);
			DEBUGPRINT2("M: %6d %s\n", cluster->firstM, linfo->In[cluster->firstM]);
		} else {
			sprintf(s, "%6d %6d", linfo->currentNo, cluster->firstM);
		}
		linfo->InPosX[cluster->firstM]        = x;
		linfo->InPosY[cluster->firstM]        = y+shoulderM-linfo->ShoulderScale*0.5;
		psFileString(ps, s, x+armM+tick, y+shoulderM-linfo->ShoulderScale*0.5, 0); 
		linfo->currentNo--;
	} else {
		linfo->InPosX[cluster->belowLayerForM->firstN] = x;  

		/* To Up */
		linfo->posX = x+armM; 
		linfo->posY = y+shoulderM; 
		clusterLogWritePS0(cluster->belowLayerForM, ps, linfo, mode);
	}
}

void
clusterLogWritePS1(clusterLogOneRecord* cluster, psFile* ps, clusterTreeInfo* linfo, int mode)
{
	float shoulderN;
	float shoulderM;
	float armN;
	float armM;
	float tick;
	float x,y;
	float tmp;
	char s[1024];
	clusterLogOneRecord* tmpCluster;	
	clusterLogOneRecord* current;

	int tmpN;

	if(NULL==cluster) {
		return;
	} 
	current = cluster;
	DEBUGPRINT2("N: %d M: %d\n", cluster->N, cluster->M);

	current = cluster;
	while(NULL!=current) {
		current->alreadySearchedN=0; 
		current->alreadySearchedM=0; 
		current = current->prev;
	}

	current = cluster;
	current->posX = linfo->posX;
	current->posY = linfo->posY;
	while(NULL!=current) {
		// Branch Position
		x = current->posX;
		y = current->posY;

		// -Y Arm
		if(NULL==current->belowLayerForN) {  // Last arm 
			shoulderN = 1;
			if(linfo->flagLog) {
				armN      = MAX(0,log10(current->distance)-log10(linfo->ArmOffset));
			} else {
				armN      = MAX(0,current->distance-linfo->ArmOffset);
			}
		} else {
			shoulderN = current->belowLayerForN->clusterSize;
			if(linfo->flagLog) {
				armN      = log10(current->distance) - log10(current->belowLayerForN->distance); 
			} else {
				armN      = current->distance - current->belowLayerForN->distance; 
			}
		}

		// +Y Arm
		if(NULL==current->belowLayerForM) { // Last arm
			shoulderM = 1;
			if(linfo->flagLog) {
				armM      = MAX(0,log10(current->distance)-log10(linfo->ArmOffset));
			} else {
				armM      = MAX(0,current->distance-linfo->ArmOffset);
			}
		} else {
			shoulderM = current->belowLayerForM->clusterSize;
			if(linfo->flagLog) {
				armM      = log10(current->distance) - log10(current->belowLayerForM->distance);
			} else {
				armM      = current->distance - current->belowLayerForM->distance;
			}
		}
		
		shoulderN /= 2.0;
		shoulderM /= 2.0;

		shoulderN *= linfo->ShoulderScale;	
		shoulderM *= linfo->ShoulderScale;	
		armN      *= linfo->ArmScale;	
		armM      *= linfo->ArmScale;	
		tick       = 1;

		tmp = shoulderN;
		shoulderN = -1.0*shoulderM;
		shoulderM = tmp;

		psFileLineDraw(ps, x-tick, y,           x,      y);           /* tick */
		psFileLineDraw(ps, x,      y+shoulderN, x,      y+shoulderM); /* shoulder */  
		psFileLineDraw(ps, x,      y+shoulderN, x+armN, y+shoulderN); /* armN */ 
		psFileLineDraw(ps, x,      y+shoulderM, x+armM, y+shoulderM); /* armM */

		if(NULL!=current->belowLayerForN) {
			current->belowLayerForN->posX = x+armN;
			current->belowLayerForN->posY = y+shoulderN;
			current->belowLayerForN->upperLayer->posX = x;
			current->belowLayerForN->upperLayer->posY = y;
		}
		if(NULL!=current->belowLayerForM) {
			current->belowLayerForM->posX = x+armM;
			current->belowLayerForM->posY = y+shoulderM;
			current->belowLayerForM->upperLayer->posX = x+armM;
			current->belowLayerForM->upperLayer->posY = y+shoulderM;
		}

		// Branch Mark: tmpN(Averaged Image Index 
		tmpN = MAX(current->firstN, current->firstM);
		tmpCluster = current->belowLayerForN;
		while(NULL!=tmpCluster) {
			tmpN = tmpCluster->firstM;
			tmpCluster = tmpCluster->belowLayerForM;
		}
		sprintf(s, "%6d", tmpN);
		psFileString(ps, s, x-0.15*linfo->ArmScale, y+0.1*linfo->ShoulderScale, 0); 

		// 
		if(linfo->flagFPTTreeInfo) {
			fprintf(linfo->fptTreeInfo, "%06d %15.6f %15.6f %15.6f %15.6f %15.6f %15.6f\n", tmpN, x, y, shoulderM, shoulderN, armM, armN);	
		}

		/* -Y Arm: Last Arm : Information */
		if(NULL==current->belowLayerForN) {
			if(linfo->In!=NULL) {
				sprintf(s, "%6d %6d %s",   linfo->currentNo, current->firstN, linfo->In[current->firstN]);
				DEBUGPRINT3("N: currentNo %6d firstN %6d %s\n", linfo->currentNo, current->firstN, linfo->In[current->firstN]);
			} else {
				sprintf(s, "%6d %6d", linfo->currentNo, current->firstN);
			}
			linfo->InPosX[current->firstN]        = x;
			linfo->InPosY[current->firstN]        = y+shoulderN-linfo->ShoulderScale*0.5;
			psFileString(ps, s, x+armN+tick, y+shoulderN-linfo->ShoulderScale*0.5, 0); 
			linfo->currentNo--;
			current->alreadySearchedN = 1;
		} 

		/* +Y Arm: Last Arm : Information */
		if(NULL==current->belowLayerForM) {
			if(linfo->In!=NULL) {
				sprintf(s, "%6d %6d %s", linfo->currentNo, current->firstM, linfo->In[current->firstM]);
				DEBUGPRINT3("M: currentNo %6d firstM %6d %s\n", linfo->currentNo, current->firstM, linfo->In[current->firstM]);
			} else {
				sprintf(s, "%6d %6d", linfo->currentNo, current->firstM);
			}
			linfo->InPosX[current->firstM]        = x;
			linfo->InPosY[current->firstM]        = y+shoulderM-linfo->ShoulderScale*0.5;
			psFileString(ps, s, x+armM+tick, y+shoulderM-linfo->ShoulderScale*0.5, 0); 
			linfo->currentNo--;
			current->alreadySearchedN = 1;
		}	

		DEBUGPRINT4(">>Check: upper %p current %p N %p M %p\n", current->upperLayer, current, current->belowLayerForN, current->belowLayerForM);
		DEBUGPRINT2(">>       current pos: %f %f \n", current->posX, current->posY);
		if(NULL!=current->upperLayer) {
		DEBUGPRINT2(">>       upper   pos: %f %f \n", current->upperLayer->posX, current->upperLayer->posY);
		}
		if(NULL!=current->belowLayerForN) {
		DEBUGPRINT2(">>       belowN  pos: %f %f \n", current->belowLayerForN->posX, current->belowLayerForN->posY);
		}
		if(NULL!=current->belowLayerForM) {
		DEBUGPRINT2(">>       belowM  pos: %f %f \n", current->belowLayerForM->posX, current->belowLayerForM->posY);
		}
		
		// Next Search
		if(NULL!=current->belowLayerForN && current->alreadySearchedN!=1) {         /* Down -Y Arm */
			current->alreadySearchedN = 1;
			current->belowLayerForN->upperLayer = current;
			current = current->belowLayerForN;
			DEBUGPRINT3("belowN %d %f %f\n", current->firstM, current->posX, current->posY);
		} else if(NULL!=current->belowLayerForM && current->alreadySearchedM!=1) {  /* Down +Y Arm */ 
			current->alreadySearchedM = 1;
			current->belowLayerForM->upperLayer = current;
			current = current->belowLayerForM;
			DEBUGPRINT3("belowM %d %f %f\n", current->firstM, current->posX, current->posY);
		} else if(NULL!=current->upperLayer) {                                      /* Up */
			current = current->upperLayer;
			while(NULL!=current) {
				DEBUGPRINT3("upper %d %f %f\n", current->firstM, current->posX, current->posY);
				if(current->alreadySearchedN!=1) {       /* Never go down -Y arm*/
					if(NULL!=current->belowLayerForN) {  /* Subtree */
						current->alreadySearchedN=1;
						current = current->belowLayerForN;
						DEBUGPRINT3("belowN %d %f %f\n", current->firstM, current->posX, current->posY);
						break;
					} else {                             /* Last N */
						break;	
					}
				} else if(current->alreadySearchedM!=1) { /* Never go down +Y arm */
					if(NULL!=current->belowLayerForM) {
						current->alreadySearchedM=1;
						current = current->belowLayerForM;
						DEBUGPRINT3("belowM %d %f %f\n", current->firstM, current->posX, current->posY);
						break;
					} else {                             /* Last M */
						break;
					}
				} 
				current = current->upperLayer;
			}
		} else {
			current = NULL; // finish
		}
	}	
}

void clusterLogWritePSScaling(clusterLog* cluster, clusterTreeInfo* linfo, psFile* ps, int mode)
{
	float min;
	float max;
	float tick;
	float deltaTick;
	float minTick;
	float maxTick;
	float max2;
	char s[1024];

	max = cluster->bottom->distance;  		
	if(0<linfo->ArmOffset) {
		min = linfo->ArmOffset;
	} else {
		min = 0;
	}
	if(linfo->flagLog) {
		min = MAX(min,1);
	}

	if(linfo->flagLog) {
		deltaTick = 1; 
		minTick   = (int)(log10(min));
		maxTick   = (int)(log10(max));
		max2      = log10(max);	
	} else {
		deltaTick = (int)((max - min)/(0.1*max));
		minTick   = (int)(min/deltaTick);
		maxTick   = (int)(max/deltaTick);
		max2 = max;
	}

	psFileLineDraw(ps, (max2-minTick)*linfo->ArmScale, 0, (max2-maxTick)*linfo->ArmScale, 0);
	for(tick=minTick; tick<=maxTick; tick+=deltaTick) {
			DEBUGPRINT1("Tick: %f\n", tick);
			psFileLineDraw(ps, (max2-tick)*linfo->ArmScale, -0.5*linfo->ShoulderScale, (max2-tick)*linfo->ArmScale, +0.5*linfo->ShoulderScale); 	
			sprintf(s, "%+5.1f", tick); 
			psFileString(ps, s, (max2 - tick)*linfo->ArmScale-1.0, 1.0*linfo->ShoulderScale, 0);  
	}
}

void
clusterLogWritePS(clusterLog* cluster, clusterTreeInfo* linfo, FILE* fpt, int mode)
{
	psFile ps;
	int i;
	char s[1024];

	ps.fpt = fpt;
	ps.info.page = 1;
	ps.info.label[0] = '\0';
	psFileInit(&ps, 0);

	psFilePageStart(&ps, 0);
	
	psFileStringDefaultStatusSet(&ps);
	//psFileStringStatusSet(&ps, "/Helvetica", (int)(linfo->ShoulderScale));
	psFileStringStatusSet(&ps, "/Courier", (int)(linfo->ShoulderScale));

	if(NULL==cluster->bottom) {
		fprintf(stderr, "No Cluster\n");
		exit(EXIT_FAILURE);
	} else if(NULL!=cluster->bottom->next) {
		fprintf(stderr, "Something wrong! Bottom is not bottom in WritePS\n");
		exit(EXIT_FAILURE);
	} else if(cluster->bottom->clusterSize<0){
		fprintf(stderr, "ClusterSize in WritePS : %d\n",  cluster->bottom->clusterSize);
		exit(EXIT_FAILURE);
	}

	DEBUGPRINT1("ClusterSize: %d \n", cluster->bottom->clusterSize);
	linfo->InPosY = (float*)memoryAllocate(sizeof(float)*cluster->bottom->clusterSize, "in clusterLogWritePS0");
	linfo->InPosX = (float*)memoryAllocate(sizeof(float)*cluster->bottom->clusterSize, "in clusterLogWritePS0");
	linfo->clusterSize =  (clusterTypeInteger*)memoryAllocate(sizeof(int)*cluster->bottom->clusterSize, "in clusterLogWritePS0");
	linfo->clusterNumber = (clusterTypeInteger*)memoryAllocate(sizeof(int)*cluster->bottom->clusterSize, "in clusterLogWritePS0");
	linfo->currentNo = cluster->bottom->clusterSize-1;

	clusterLogWritePS1(cluster->bottom, &ps, linfo, mode);

	if(linfo->flagScaling) {
		clusterLogWritePSScaling(cluster, linfo, &ps, mode);
	}
	
	s[0] = '\0';
	for(i=0; i<linfo->argc; i++) {
		strncat(s, linfo->argv[i], strlen(linfo->argv[i]));	
		strncat(s, " ", strlen(" "));
	}
	psFileString(&ps, s, 0, -2*linfo->ShoulderScale, 0);
	psFilePageEnd(&ps, 0);
	return ;
}

