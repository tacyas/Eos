%module molvieViewer
%{
#include <stdlib.h>
#include <GL/glut.h>
#include "lmolvie.h"
#include "pdbFile.h"


%}
//molvieViewer
extern void lmolvieViewerIdle(void);
extern void lmolvieViewerKeyboard(unsigned char pushkey, int x, int y);
extern void lmolvieViewerSpecial(int pushkey, int x, int y);
extern void lmolvieViewerMouse(int button, int state, int x, int y);
extern void lmolvieViewerMouseMotion(int x, int y);
extern void lmolvieViewerMousePassiveMotion(int x, int y);
extern void lmolvieViewerDisplay(void);



