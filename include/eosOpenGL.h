#ifndef EOS_OPENGL
#define EOS_OPENGL

#ifdef X86MAC64
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

extern void __openGLAA(void);
extern void openGLKeyDefault(char c, int x, int y );
#endif /* EOS_OPENGL */
