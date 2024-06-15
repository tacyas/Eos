/*
# eosPThread.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosPThread.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef EOS_PTHREAD_H
#define EOS_PTHREAD_H 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

/* constant begin */

extern int __eosPThread__;
extern int __eosPThreadNum__;

/* constant end */

/* struct begin */

typedef enum eosPThreadStatus {
	eosPThreadStatusWaiting = 0,
	eosPThreadStatusRunning = 1
} eosPThreadStatus;

typedef struct eosPThread {
	pthread_t* 			th;         /* [max] thread */
	eosPThreadStatus* 	status;     /* [max] thread status */
	long*				id;         /* [max] thread ID indicated by count */

	int 				max;		/* maximum thread number working simultaneously. */ 
	long				count;		/* count of created threads */	 
	long				latest;     /* working thread ID which started latest */
	long				oldest;     /* working thread ID which started oldest */

	pthread_mutex_t     mutex;
	pthread_mutexattr_t mutex_attr;
} eosPThread;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */
extern void eosPThreadInit   (eosPThread* t, int max, int mode);
extern int  eosPThreadCreateOnWaitingThread (eosPThread* t, void* (*start_routine)(void *), void * arg, int mode);
extern int  eosPThreadCreate (eosPThread* t, int i, void* (*start_routine)(void *), void * arg, int mode);
extern void eosPThreadJoin   (eosPThread* t, int i, int mode);
extern void eosPThreadJoinAll(eosPThread* t, int mode);

extern void eosPThreadMutexInit(eosPThread* t);
extern void eosPThreadMutexDestroy(eosPThread* t);
extern void eosPThreadMutexLock(eosPThread* t);
extern void eosPThreadMutexUnlock(eosPThread* t);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* EOS_PTHREAD_H */ 
