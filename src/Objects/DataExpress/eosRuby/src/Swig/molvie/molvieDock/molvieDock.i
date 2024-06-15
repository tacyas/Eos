%module molvieDock
%{
#include <stdlib.h>
#include <GL/glut.h>
#include "lmolvie.h"
#include "pdbFile.h"
%}

//molvieDock
extern void lmolvieDockKeyboard(unsigned char pushkey, int x, int y);
//extern void newPDBload(pdbFile* loadpdb);
extern void displayMultiPDB1();
extern void lmolvieDockDisplay(void);
