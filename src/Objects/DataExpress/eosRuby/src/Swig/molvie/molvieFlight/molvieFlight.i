%module molvieFlight
%{
#include <stdlib.h>
#include <GL/glut.h>
#include "lmolvie.h"
#include "pdbFile.h"


%}

//molvieFlight
extern void lmolvieFlightKeyboard(unsigned char pushkey, int x, int y);
extern void lmolvieFlightDisplay(void);
extern void lmolvieFlightIdle(void);

