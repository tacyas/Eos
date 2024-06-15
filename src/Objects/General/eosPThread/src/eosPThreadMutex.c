/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosPThreadMutex ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosPThreadMutex 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosPThreadMutex ver%I%; Date:%D% %Z%";

#undef DEBUG 
//#define DEBUG 
#include "genUtil.h"

#include <pthread.h>
#include "../inc/eosPThread.h"

//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t* pmutex;
static pthread_mutex_t  mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutexattr_t* pmutex_attr;
static pthread_mutexattr_t  mutex_attr;
//static pthread_mutex_t mutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;

void
eosPThreadMutexInit(eosPThread* t)
{
	if(NULL!=t) {
		pthread_mutexattr_init(&(t->mutex_attr));	
#if defined(X86MAC64) || defined(ARM64MAC64)
		pthread_mutexattr_settype(&(t->mutex_attr), PTHREAD_MUTEX_ERRORCHECK);
#else
		pthread_mutexattr_settype(&(t->mutex_attr), PTHREAD_MUTEX_ERRORCHECK_NP);
#endif
		pthread_mutex_init(&(t->mutex), &(t->mutex_attr));
		pmutex = &(t->mutex); 
		pmutex_attr = &(t->mutex_attr); 
	} else {
		pthread_mutexattr_init(&mutex_attr);	
#if defined(X86MAC64) || defined(ARM64MAC64)
		pthread_mutexattr_settype(&(t->mutex_attr), PTHREAD_MUTEX_ERRORCHECK);
#else
		pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_ERRORCHECK_NP);
#endif
		pthread_mutex_init(&mutex, &mutex_attr);
	}
}

void
eosPThreadMutexDestroy(eosPThread* t)
{
	if(NULL!=t) {
		pthread_mutex_destroy(&(t->mutex));
	} else {
		pthread_mutex_destroy(&mutex);
	}
}

void
eosPThreadMutexLock(eosPThread* t)
{
	int ret;
	DEBUGPRINT("LOCK start->");
	if(NULL!=t) {
		ret = pthread_mutex_lock(&(t->mutex));
	} else {
		ret = pthread_mutex_lock(&mutex);
	}
	DEBUGPRINT("LOCK End\n");
	switch(ret) {
		case 0: {
			DEBUGPRINT("Success! MutexLock\n");
			break;
		}
		case EAGAIN: {
			DEBUGPRINT("The value specified by mutex is invalid.");
			perror("eosPThreadMutexLock");
			exit(EXIT_FAILURE);
			break;
		}
		case EDEADLK: {
			DEBUGPRINT("A deadlock would occur if the thread blocked waiting for mutex.");
			perror("eosPThreadMutexLock");
			exit(EXIT_FAILURE);
			break;
		}
	}
}


void
eosPThreadMutexUnlock(eosPThread* t)
{
	DEBUGPRINT("UNLOCK start");
	if(NULL!=t) {
		pthread_mutex_unlock(&(t->mutex));
	} else {
		pthread_mutex_unlock(&mutex);
	} 
	DEBUGPRINT("UNLOCK end\n");
}


