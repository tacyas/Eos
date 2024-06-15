%module molvieMrcViewer
%{
#include <stdlib.h>
#include <GL/glut.h>
#include "lmolvie.h"
#include "pdbFile.h"
%}

//molvieMrcViewer
extern void lmolvieMrcViewerKeyboard(unsigned char pushkey, int x, int y);
extern void lmolvieMrcViewerMouse(int button, int state, int x, int y);
extern void lmolvieMrcViewerMouseMotion(int x, int y);
extern void lmolvieMrcViewerMousePassiveMotion(int x, int y);
extern void lmolvieMrcViewerDisplay(void);

