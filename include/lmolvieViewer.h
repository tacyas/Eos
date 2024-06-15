/*
# lmolvie.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvie.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMOLVIE_H
#define LMOLVIE_H

#include <GL/glut.h>
#include "Contour.h"

#undef  IDLE_FUNCTION
#define KEYBOARD_FUNCTION 
#define MOUSE_FUNCTION 
#define MOTION_FUNCTION 
#define PASSIVEMOTION_FUNCTION 

//int mainwindow, parallelwindow;

typedef struct cameraInfo {
	GLdouble Fovy;
	GLdouble Aspect;
	GLdouble ClipNear;
	GLdouble ClipFar;
	GLdouble Eye[3];
	GLdouble Centre[3];
	GLdouble Up[3];
} cameraInfo;

typedef enum displayMode{
	none=0,
	atom=1,
	stick=2,
	serial=3,
	residue=4,
	temp=5,
	sticktemp=6,
	stickresidue=7
}displayMode;

typedef enum operationMode {
	normal=0,
	drive=1,
	parallel=2,
	surface=3,
	multi=4,
	coaster=5
} operationMode;

typedef struct Coord {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} Coord; 

extern void lmolvieInitNormal(void);
extern void lmolvieIdleNormal(void);
extern void lmolvieDisplayNormal(void);
//extern void viewerDisplay(void);
extern void lmolvieReshapeNormal(int width, int height);
extern void myCameraRotateY(GLdouble angle);
extern void lmolvieMouse(int button, int state, int x, int y);
extern void lmolvieMouseMotion(int x, int y);
extern void lmolvieMousePassiveMotion(int x, int y);
extern void lmolvieMouseParallel(int button, int state, int x, int y);
extern void lmolvieMouseMotionParallel(int x, int y);
extern void lmolvieMousePassiveMotionParallel(int x, int y);
extern void lmolvieKeyboard(unsigned char pushkey, int x, int y);
extern void lmolvieKeyboardNormal(unsigned char pushkey, int x, int y);
extern void lmolvieKeyboardDrive(unsigned char pushkey, int x, int y);
extern void lmolvieKeyboardParallel(unsigned char pushkey, int x, int y);
extern void lmolvieKeyboardSurface(unsigned char pushkey, int x, int y);
//extern void moveKeyboard(int movekey, int x, int y);
//extern void moveKeyboard0(int movekey, int x, int y);

extern void lmolvieInitParallel(void);
extern void lmolvieDisplayParallel(void);
extern void lmolvieReshapeParallel(int width, int height);

extern operationMode operationModeGet(void);
extern void operationModeSet(operationMode);

extern void myCameraRotateX(GLdouble angle);        
extern void myCameraRotateY(GLdouble angle);        
extern void myCameraRotateZ(GLdouble angle);
extern void myCameraEyeRotateX(GLdouble angle);
extern void myCameraEyeRotateY(GLdouble angle);
extern void myCameraTranslateX(GLdouble pan);        
extern void myCameraTranslateY(GLdouble pan);        
extern void myCameraTranslateZ(GLdouble pan); 
//extern void setMyCamera(pdbCenter pdbCenter, GLfloat h);
extern void resetMyCamera();
extern cameraInfo* getMyCamera(void);
extern void upCalc();
extern void moveMyCamera(double movedistance);

//extern pdbCenter getpdbCenter(int returnID);
//extern void putpdbCenter(pdbFile* putpdbfile);

extern void lmolvieLightSet(void);
extern GLfloat* getMyLightPos(int index);

//extern elementSwitch get_elementSwitch(int ID);
//extern void put_elementSwitch(int ID, char atom);
//extern void DrawAtom(void);

extern void monoSound(float amplitude, float Hz);
extern void lmolvieVoice(void);

extern void drawContour(contourLinesSet* contour);

//molvieViewer
extern void lmolvieViewerIdle(void);
extern void lmolvieViewerKeyboard(unsigned char pushkey, int x, int y);
extern void lmolvieViewerMouse(int button, int state, int x, int y);
extern void lmolvieViewerMouseMotion(int x, int y);
extern void lmolvieViewerMousePassiveMotion(int x, int y);
extern void lmolvieViewerDisplay(void);

//molvieMrcViewer
extern void lmolvieMrcViewerKeyboard(unsigned char pushkey, int x, int y);
extern void lmolvieMrcViewerMouse(int button, int state, int x, int y);
extern void lmolvieMrcViewerMouseMotion(int x, int y);
extern void lmolvieMrcViewerMousePassiveMotion(int x, int y);
extern void lmolvieMrcViewerDisplay(void);

#endif /* LMOLVIE_H */
