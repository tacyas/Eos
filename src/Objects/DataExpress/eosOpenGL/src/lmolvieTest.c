#include <stdio.h>
#include "../inc/eosOpenGL.h"


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
  glTranslatef(0.0, 0.0, -3.0);
  glutSolidSphere(1.0 /* radius  */,
		  20  /* slicies */, 
		  20  /* stacks  */); /* 中心は(0,0,0) */
  glPopMatrix();
  
  glutSwapBuffers();
}

void reshape(int w, int h)
{

  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);	
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
  glMatrixMode (GL_MODELVIEW);	
  glLoadIdentity();

}

void init(void)
{

  GLfloat light_position[] = {0.0, 0.0, 1.0, 0.0}; 

/* Try this light position */
/* GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0}; */

/* How about this ? */
/* GLfloat light_position[] = {-1.0, -1.0, 1.0, 0.0}; */

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
  default :
    exit(1);
  }
}


int
lmolvieTest(int argc, char** argv)
{
  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  return 0;
}



