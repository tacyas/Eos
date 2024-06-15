#ifndef PVM_H
#define PVM_H

#ifdef PVM

/* prototype begin */
#include <stdio.h>
#include <pvm3.h>
extern int* pvmServerStart(char* cmd, char* argv[], FILE* fpt, int* nTask, int mode);
extern void pvmServerStartError(int numTask, int* tids, int nTask);
/* prototype end */

#endif /* PVM */

#endif /* PVM_H */
