%module molvieDefault
%{
#include <stdlib.h>
#include <GL/glut.h>
#include "lmolvie.h"
#include "pdbFile.h"

%}
extern void lmolvieInitNormal(void);
extern void lmolvieIdleNormal(void);
extern void lmolvieDisplayNormal(void);
//extern void viewerDisplay(void);
extern void lmolvieReshapeNormal(int width, int height);
extern void myCameraRotateY(GLdouble angle);
extern void lmolvieMouse(int button, int state, int x, int y);
extern void lmolvieMouseMotion(int x, int y);
extern void lmolvieMousePassiveMotion(int x, int y);
extern void lmolvieMouseDrive(int button, int state, int x, int y);
extern void lmolvieMouseMotionDrive(int x, int y);
extern void lmolvieMousePassiveMotionDrive(int x, int y);
extern void lmolvieMouseParallel(int button, int state, int x, int y);
extern void lmolvieMouseMotionParallel(int x, int y);
extern void lmolvieMousePassiveMotionParallel(int x, int y);
extern void lmolvieMouseMulti(int button, int state, int x, int y);
extern void lmolvieMouseMotionMulti(int x, int y);
extern void lmolvieMousePassiveMotionMulti(int x, int y);
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

/****************************************************************************************************************************/
