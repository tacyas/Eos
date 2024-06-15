#ifndef CLUSTER_H
#define CLUSTER_H

#define CLUSTERLOG_BINARY_FILENAME_FORMAT      "%s.%08d.%08d.%08d"
#define CLUSTERLOG_BINARY_NO_CALCULATION_VALUE (-9999)

/* struct begin */
/*
typedef int     clusterTypeInteger;
typedef double  clusterTypeReal;
*/
typedef float clusterTypeReal;
typedef short clusterTypeInteger;

typedef struct clusterLogOneRecord clusterLogOneRecord;
struct clusterLogOneRecord {
		/* Information of this log line in the logfile */
        clusterTypeInteger N;			/* Current N (shrinked array): Definition: N > M */
        clusterTypeInteger M;      		/* Current M : */ 
        clusterTypeInteger prevN;		/* prevN:  N: the nearest pair in the below layer */
        clusterTypeInteger prevM;		/* prevM:  M: */
        clusterTypeReal    distance;	/* Distance between N and M */

		/* Original File Number */
		clusterTypeInteger originalN;
		clusterTypeInteger originalM;

		/* File Number within the below layer */
		clusterTypeInteger firstN;
		clusterTypeInteger firstM;

		clusterLogOneRecord* belowLayerStart;
		clusterLogOneRecord* belowLayer;
		clusterLogOneRecord* belowLayerEnd;

		/* Upper Layer */
		clusterLogOneRecord* upperLayer;

		/* Below Layer */
		clusterLogOneRecord* belowLayerForN;
		clusterLogOneRecord* belowLayerForM;
		/* Below Layer Search Flag */
		clusterTypeInteger alreadySearchedN;
		clusterTypeInteger alreadySearchedM;
		clusterTypeReal    posX;
		clusterTypeReal    posY;

		/* Including the below layer */
		clusterTypeInteger   clusterSize;	   /* File Number of the cluster */

		/* This Layer */
		clusterTypeInteger   clusterNumber;    /* Cluster Numer of this layer */  
		/* Set the number of the cluster where this log line attributes in a function of clusterLogClusterNumberSet or Set2 */ 

        clusterLogOneRecord* prev; /* previous record */
        clusterLogOneRecord* next; /* Next record */
};

typedef struct clusterLog {
        clusterLogOneRecord* top;
        clusterLogOneRecord* current;
		clusterLogOneRecord* bottom;
} clusterLog;

typedef struct clusterLog2OneRecord clusterLog2OneRecord;

struct clusterLog2OneRecord {
	// LogFile Information 
	clusterTypeInteger N; 
	clusterTypeInteger M; // N > M: merge N to M
	clusterTypeReal    distance;
	clusterTypeReal    linearCorrelation; 

	// After reading
	clusterTypeInteger clusterNumber; // Cluster Number

	clusterLog2OneRecord* prev;
	clusterLog2OneRecord* next;
};

typedef struct clusterLog2 {
        clusterLog2OneRecord* top;
        clusterLog2OneRecord* current;
		clusterLog2OneRecord* bottom;
} clusterLog2;

typedef struct clusterTreeInfo clusterTreeInfo;
struct clusterTreeInfo {
	clusterTypeReal posX;
	clusterTypeReal posY;
	clusterTypeReal ShoulderScale;  
	clusterTypeReal ArmScale;  

	clusterTypeReal ArmOffset;

	clusterTypeInteger flagLog;
	clusterTypeInteger flagScaling;

	char** In;
	char** argv;
	clusterTypeReal* InPosY;
	clusterTypeReal* InPosX;
	clusterTypeInteger argc;

	clusterTypeInteger*    clusterSize;	
	clusterTypeInteger*    clusterNumber;

	clusterTypeInteger	currentNo;

	clusterTypeInteger flagFPTTreeInfo;
	FILE* fptTreeInfo;
};

/* struct end */

/* prototype begin */
#ifdef __cplusplus
extern "C" {
#endif

/* in clusterLogRead.c */ 
extern clusterLogOneRecord* clusterLogRead(clusterLog* cluster, FILE* fpt, int mode);
extern clusterLog* clusterLogReadAll(clusterLog* cluster, FILE* fpt, int mode);
extern clusterLog2OneRecord* clusterLog2Read(clusterLog2* cluster, FILE* fpt, int mode);
extern clusterLog2* clusterLog2ReadAll(clusterLog2* cluster, FILE* fpt, int mode);
	extern clusterLogOneRecord* clusterLogReadBinary(clusterLog* cluster, clusterTypeInteger* prevN, clusterTypeInteger* prevM, char* filename, int mode);
extern clusterLog* clusterLogReadAllBinary(clusterLog* cluster, char* basename, int mode);

extern clusterLogOneRecord* clusterLogWriteAllBinary(clusterLog* cluster, char* basename, int mode);
extern clusterLogOneRecord* clusterLogWrite(clusterLog* cluster, FILE* fpt, int mode);
extern clusterLogOneRecord* clusterLogWriteBinary2(clusterLog* cluster, FILE* fpt, int mode);
extern clusterLogOneRecord* clusterLogWriteOneRecord(clusterLogOneRecord* cluster, FILE* fpt, int mode);
extern clusterLogOneRecord* clusterLogWriteOneRecordBinary2(clusterLogOneRecord* cluster, FILE* fpt, int mode);
extern clusterLogOneRecord* clusterLogWriteAll(clusterLog* cluster, FILE* fpt, int mode);
extern clusterLogOneRecord* clusterLogWriteAllBinary2(clusterLog* cluster, FILE* fpt, int mode);
extern clusterLogOneRecord* clusterLogWriteClusterOnly(clusterLog* cluster, FILE* fpt, int mode);
extern void clusterLogWritePS(clusterLog* cluster, clusterTreeInfo* linfo, FILE* fpt, int mode);

/* in clusterLogUtil.c */
extern void clusterLogClusterInformationSet(clusterLog* cluster, clusterTypeInteger lastNum, int mode);

extern void clusterLogClusterNumberSet(clusterLogOneRecord* bottom, clusterTypeInteger lastClusterNum, int mode); 
extern void clusterLogClusterNumberSetForLog2(clusterLog* cluster, clusterTypeInteger lastClusterNum, int mode); 
extern void clusterLogClusterNumberSet2(clusterLog* top, clusterTypeInteger firstClusterNum, int mode); 

extern clusterLogOneRecord* clusterLogGetDistance(clusterLog* cluster, clusterTypeInteger N, clusterTypeInteger M, clusterTypeInteger clusterNum, clusterTypeReal* data);

extern void clusterLogBelowLayerPointerSet(clusterLog* cluster, int mode); 
extern clusterLogOneRecord* clusterLogBottomGet(clusterLog* cluster, int mode); 
extern int clusterLogClusterSizeGet(clusterLogOneRecord* cluster, int mode); 
extern void clusterLogClusterSizeSet(clusterLog* cluster, int mode); 
extern void clusterLogBottomSet(clusterLog* cluster, int mode); 
extern clusterLog*  clusterLogTransformLog2ToLog(clusterLog2* cluster2, clusterTypeInteger lastNum, int mode);

/* in clusterLogInit.c */
extern clusterLog* clusterLogInit(clusterLog * cluster, int mode); 
extern clusterLog2* clusterLog2Init(clusterLog2 * cluster, int mode); 
extern clusterLogOneRecord* clusterLogInitOneRecord(clusterLogOneRecord * cluster, int mode); 
extern clusterLog2OneRecord* clusterLog2InitOneRecord(clusterLog2OneRecord * cluster, int mode); 

#ifdef __cplusplus
};
#endif
/* prototype end */

#endif
