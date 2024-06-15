#ifndef CTF_DETERMINATION_FROM_PHASE_H
#define CTF_DETERMINATION_FROM_PHASE_H

/* struct begin */
typedef struct ctfInfoDeterminationFromPhaseComparison {
	ctfInfo val;
	ctfInfo min;
	ctfInfo max;
	ctfInfo del;
	mrcImageParaTypeReal Rmax;
	long mode;
} ctfInfoDeterminationFromPhaseComparison;
/* struct end */

/* prototype begin */
extern double ctfDeterminationFromPhaseComparison(
		     mrcImage* inFFT,	
		     mrcImage* refFFT,	
			 ctfInfoDeterminationFromPhaseComparison* DetInfo, 
		     long mode);

/* prototype end */

#endif /* CTF_DETERMINATION_FROM_PHASE_H */
