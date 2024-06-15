/*
# StereoDisplay : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : StereoDisplay
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "File.h"
#include "String.h"
#include "tgaFile.h"


typedef struct lStereoDisplayInfo {
	int DoubleBuffer;

	int ImageNum;
	int curImageNum;

	int offsetx;
	int offsety;

	int winWidth; 
	int winHeight; 
} lStereoDisplayInfo;

static lStereoDisplayInfo disp = {1, 0, 0, 0, 0, 1024, 600} ;

typedef struct StereoDisplayImage StereoDisplayImage;
struct StereoDisplayImage {
	int Width;
	int Height;
	GLubyte* Left;
	GLubyte* Right;
	StereoDisplayImage* next;
	StereoDisplayImage* prev;
};

typedef struct lStereoDisplayImageList {
	StereoDisplayImage* Image;
	StereoDisplayImage* Top;
} StereoDisplayImageList;

static StereoDisplayImageList Image = {NULL,NULL};

extern void keyboard(unsigned char c, int x, int y);
extern void resize(int w, int h);

void
resize(int w, int h)
{
	disp.winWidth  = w;
	disp.winHeight = h;
	glutPostRedisplay();
}

StereoDisplayImageList*
StereoDisplayImageAlloc(StereoDisplayImageList* Image, int mode)
{
	Image->Image->Left  = (GLubyte*)memoryAllocate(sizeof(GLubyte)*3*Image->Image->Width*Image->Image->Height, "in StereoImageAlloc");
	Image->Image->Right = (GLubyte*)memoryAllocate(sizeof(GLubyte)*3*Image->Image->Width*Image->Image->Height, "in StereoImageAlloc");
	return Image;
}

StereoDisplayImageList*
StereoDisplayImageRead(StereoDisplayImageList* Image,  FILE* inl, FILE* inr, int mode)
{
	int i, j, dstk, srck, I, J;
	tgaFile tgal;
	tgaFile tgar;

	tgaFileInit(&tgal, NULL, 0); 
	tgaFileInit(&tgar, NULL, 0); 

	tgaFileRead(&tgal, inl, 0);
	tgaFileRead(&tgar, inr, 0);

#ifdef DEBUG
	tgaFileHeaderPrint(&tgal, stderr, 0);
	tgaFileHeaderPrint(&tgar, stderr, 0);
#endif

	if(NULL==Image->Top) {
		Image->Image = (StereoDisplayImage*)memoryAllocate(sizeof(StereoDisplayImage), "ImageRead");
		Image->Image->prev = Image->Top = Image->Image;	
	} else {
		Image->Image->next = (StereoDisplayImage*)memoryAllocate(sizeof(StereoDisplayImage), "ImageRead");
		Image->Image->next->prev = Image->Image;
		Image->Image = Image->Image->next;
	}
	Image->Image->next = Image->Top;

	if(tgal.Header.ImageSpec.Width  != tgar.Header.ImageSpec.Width
	 ||tgal.Header.ImageSpec.Height != tgar.Header.ImageSpec.Height
	 ||tgal.Header.ImageSpec.Depth  != tgar.Header.ImageSpec.Depth)  {
		fprintf(stderr, "Right Image is not the same in Size as Left one\n");
		fprintf(stderr, "Left:  %d %d %d\n", 
				tgal.Header.ImageSpec.Width, tgal.Header.ImageSpec.Height, tgal.Header.ImageSpec.Depth);
		fprintf(stderr, "Right: %d %d %d\n",
				tgar.Header.ImageSpec.Width, tgar.Header.ImageSpec.Height, tgar.Header.ImageSpec.Depth);
		exit(EXIT_FAILURE);
	} else {
		Image->Image->Width  = tgal.Header.ImageSpec.Width;
		Image->Image->Height = tgal.Header.ImageSpec.Height;
	}

	StereoDisplayImageAlloc(Image, 0);

	for(i=0; i<Image->Image->Width ;i++){
	for(j=0; j<Image->Image->Height;j++){
		dstk = 3*(i+j*Image->Image->Width);
		if(0x2&tgal.Header.ImageSpec.Descriptor.Bit.ImageOrigin) {
			J = Image->Image->Height - 1 - j;
		} else {
			J = j;
		}
		if(0x1&tgal.Header.ImageSpec.Descriptor.Bit.ImageOrigin) {
			I = Image->Image->Width - 1 - i;
		} else {
			I = i;
		}
		srck = tgal.Header.ImageSpec.Depth/8*(I+J*Image->Image->Width);

		Image->Image->Left [dstk+2] = tgal.Image[srck+0];
		Image->Image->Left [dstk+1] = tgal.Image[srck+1];
		Image->Image->Left [dstk+0] = tgal.Image[srck+2];
		Image->Image->Right[dstk+2] = tgar.Image[srck+0];
		Image->Image->Right[dstk+1] = tgar.Image[srck+1];
		Image->Image->Right[dstk+0] = tgar.Image[srck+2];
	}
	}
	return Image;
}

void
imageSet(FILE* inl, FILE* inr)
{
	glClearColor(0.0,0.0,0.0,0.0);
	StereoDisplayImageRead(&Image, inl, inr, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

void
imageSetList(FILE* fpt, int num)
{
	int i;
	char s[STRING_MAX_LENGTH];
	char* left;
	char* right;
	FILE* fptLeft;
	FILE* fptRight;

	glClearColor(0.0,0.0,0.0,0.0);
	fseek(fpt, 0, SEEK_SET);
	for(i=0; i<num; i++) {
		stringGetFromFile(s, "", fpt, stderr, 3);
		left  = stringGetNthWord(s, 1, " \n\t,");
		right = stringGetNthWord(s, 2, " \n\t,");
		fptLeft  = fileOpen(left,  "r");
		fptRight = fileOpen(right, "r");
		DEBUGPRINT3("%d : %s %s\n", i, left, right);
		StereoDisplayImageRead(&Image, fptLeft, fptRight, 0);
	}
	Image.Top->prev = Image.Image;
	Image.Image = Image.Top;

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

void
display(void)
{
	if(!disp.DoubleBuffer){
		glClear(GL_COLOR_BUFFER_BIT);
		glRasterPos2f(-1,-1);
		glDrawPixels(Image.Image->Width,Image.Image->Height,
				GL_RGB,GL_UNSIGNED_BYTE,Image.Image->Left);
		glRasterPos2f(0,-1);
		glDrawPixels(Image.Image->Width,Image.Image->Height, 
				GL_RGB,GL_UNSIGNED_BYTE,Image.Image->Right);
		glFlush();
	} else{
		glDrawBuffer(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawBuffer(GL_BACK_LEFT);
		glPixelZoom(disp.winWidth/(float)Image.Image->Width, disp.winHeight/(float)Image.Image->Height);
		glDrawPixels(Image.Image->Width,Image.Image->Height, 
				GL_RGB,GL_UNSIGNED_BYTE,Image.Image->Left);
		glutSwapBuffers();
		glDrawBuffer(GL_BACK_RIGHT);
		glPixelZoom(disp.winWidth/(float)Image.Image->Width, disp.winHeight/(float)Image.Image->Height);
		glDrawPixels(Image.Image->Width,Image.Image->Height, 
				GL_RGB,GL_UNSIGNED_BYTE,Image.Image->Right);
		glutSwapBuffers();
	}	
}

void
DisplaySetting(int WindowX,int WindowY)
{
	if(!disp.DoubleBuffer){
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowSize(disp.winWidth, disp.winHeight);
		glutInitWindowPosition(WindowX-disp.offsetx,
							   WindowY-disp.offsety);
		glutCreateWindow("StereoDisplay v1.03  NakedEyeMode");
	} else {
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STEREO);
		glutInitWindowSize(disp.winWidth,disp.winHeight);
		glutInitWindowPosition(WindowX-disp.offsetx,
							   WindowY-disp.offsety);
		glutCreateWindow("StereoDisplay v1.03  CrystalEyeMode");
	}	

}

void
DisplayRecreate(lStereoDisplayInfo* disp) 
{
	int WindowY=0,WindowX=0;

	WindowX=glutGet(GLUT_WINDOW_X);
	WindowY=glutGet(GLUT_WINDOW_Y);
	glutDestroyWindow(glutGetWindow());
	DisplaySetting(WindowX,WindowY);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
}

void
keyboard(unsigned char key,int x,int y)
{
	switch(key) {
		case 'q':
		case 'Q':
			exit(EXIT_FAILURE);
			break;
		case 'd':
			disp.DoubleBuffer=1;
			DisplayRecreate(&disp);
			break;
		case 's':
			disp.DoubleBuffer=0;
			DisplayRecreate(&disp);
			break;
		case 'j':
		case 'l':
			Image.Image = Image.Image->next;
			//disp.curImageNum = (disp.curImageNum++)%disp.ImageNum;
			break;
		case 'h':
		case 'k':
			Image.Image = Image.Image->prev;
			//disp.curImageNum = (disp.curImageNum--)%disp.ImageNum;
			break;
			
		default:
			break;
	}
	glutPostRedisplay();
}	
	
int
main(int argc, char* argv[]) 
{
	StereoDisplayInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	glutInit(&argc,argv);
	DisplaySetting(0,0);


	disp.offsetx=glutGet(GLUT_WINDOW_X);
	disp.offsety=glutGet(GLUT_WINDOW_Y);

	if(info.flagInl && info.flagInr) { 
		DEBUGPRINT2("Left %s Right %s\n", info.Inl, info.Inr);
		imageSet(info.fptInl, info.fptInr);
	} else if(info.flagIn) {
		DEBUGPRINT2("%s %d\n", info.InList, info.flagIn);
		imageSetList(info.fptInList, info.flagIn);
	} else {
		fprintf(stderr, "You need -ir/il or -I \n");
		usage(argv[0]);	
	}
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">>> -I for InFileList\n");
	fprintf(stderr, "Left1 Right1 \n");
	fprintf(stderr, "Left2 Right2 \n");
	fprintf(stderr, "..... \n");
}

