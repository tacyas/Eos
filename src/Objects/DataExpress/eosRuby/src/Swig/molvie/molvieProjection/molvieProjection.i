%module molvieProjection
%{
#include <stdlib.h>
#include <GL/glut.h>
#include "lmolvie.h"
#include "pdbFile.h"


%}
//molvieProjection
extern void lmolvieProjectionKeyboard(unsigned char pushkey, int x, int y);
extern void lmolvieProjectionMouse(int button, int state, int x, int y);
extern void lmolvieProjectionMouseMotion(int x, int y);
extern void lmolvieProjectionMousePassiveMotion(int x, int y);

