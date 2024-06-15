#ifndef LL_DATA_PVM_H
#define LL_DATA_PVM_H

#include <stdio.h>
#include <math.h>
#include "llData.h"
#include "genUtil.h"

#ifdef PVM
#include "pvm3.h" 

/* prototype begin */

/* llData Sender */
extern void llDataSendByPVM(llData* ll, int tid, int mode);
extern void llDataOneLLSendByPVM(oneLLData* LL, int tid, int mode);

/* llData Reciever */
extern void llDataRecieveByPVM(llData* ll, int tid, int mode); 
extern void llDataOneLLRecieveByPVM(oneLLData* LL, int tid, int mode);

/* prototype end */

#endif

#endif /* LL_DATA_PVM_H */
