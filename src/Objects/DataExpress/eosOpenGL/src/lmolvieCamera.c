/*
# lmolvieCamera : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieCamera 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <math.h>
#define DEBUG
#include "genUtil.h"
#include "./lmolvie.h"
#include "./lmolvieProteinStatus.h"

static cameraInfo __camera={
		60.0,
		1.0,
		1.0,
		100.0,
		{0.0, 0.0, 50.0},/*kameraiti Eye*/
		{0.0, 0.0, 0.0},/*kameramuki Centre*/
		{0.0, 1.0, 0.0}/*kameraue Up*/
	};

static pdbCenter __pdbCenter;
static GLfloat __h;
static GLdouble speed=10.0;

void resetMyCamera()
{
	fprintf(stdout, "resetMyCamera, pdbCenter: %f, %f, %f, %f\n", __pdbCenter.xCenter, __pdbCenter.yCenter, __pdbCenter.zCenter, __h);
	__camera.Eye[0]=__pdbCenter.xCenter;
	__camera.Eye[1]=__pdbCenter.yCenter;
	__camera.Eye[2]=__pdbCenter.zCenter + __h;
	__camera.Centre[0]=__pdbCenter.xCenter;
	__camera.Centre[1]=__pdbCenter.yCenter;
	__camera.Centre[2]=__pdbCenter.zCenter;
	__camera.Up[0]=0.0;
	__camera.Up[1]=1.0;
	__camera.Up[2]=0.0;
}

void setMyCamera(pdbCenter pdbCenter, GLfloat h)
{
	fprintf(stdout, "setMyCamera, h: %f, %f\n", __h, h);
	__pdbCenter=pdbCenter;
	__h=h;

	resetMyCamera();
/*	__camera.Eye[0]=__pdbCenter.xCenter;
	__camera.Eye[1]=__pdbCenter.yCenter;
	__camera.Eye[2]=__h;
	__camera.Centre[0]=__pdbCenter.xCenter;
	__camera.Centre[1]=__pdbCenter.yCenter;
	__camera.Centre[2]=__pdbCenter.zCenter;*/
}

void setDriveMyCamera()
{
	GLdouble camera_move_x, camera_move_y, camera_move_z;

	camera_move_x=(__camera.Centre[0]-__camera.Eye[0])/100.0;
	camera_move_y=(__camera.Centre[1]-__camera.Eye[1])/100.0;
	camera_move_z=(__camera.Centre[2]-__camera.Eye[2])/100.0;

	__camera.Centre[0]=__camera.Eye[0]+camera_move_x;
	__camera.Centre[1]=__camera.Eye[1]+camera_move_y;
	__camera.Centre[2]=__camera.Eye[2]+camera_move_z;
	fprintf(stdout, "setDriveMyCamera\n");
}

void resetDriveMyCamera()
{
	resetMyCamera();
	setDriveMyCamera();
}

/*extern pdbFile* pdbIn;
static Coord current_coord;
static Coord next_coord;

void setCoasterCamera()
{
	pdbIn->current=pdbIn->top;
	while(strncmp(pdbIn->current->atomName, " CA ", 4)!=0){
		pdbIn->current=pdbIn->current->next;
	}
	current_coord.x=pdbIn->current->coord.x;
	current_coord.y=pdbIn->current->coord.y;
	current_coord.z=pdbIn->current->coord.z;
	__camera.Eye[0]=pdbIn->current->coord.x;
	__camera.Eye[1]=pdbIn->current->coord.y+0.01;
	__camera.Eye[2]=pdbIn->current->coord.z;
	pdbIn->current=pdbIn->current->next;
	while(strncmp(pdbIn->current->atomName, " CA ", 4)!=0){
		pdbIn->current=pdbIn->current->next;
	}
	next_coord.x=pdbIn->current->coord.x;
	next_coord.y=pdbIn->current->coord.y;
	next_coord.z=pdbIn->current->coord.z;
	__camera.Centre[0]=pdbIn->current->coord.x;
	__camera.Centre[1]=pdbIn->current->coord.y+0.01;
	__camera.Centre[2]=pdbIn->current->coord.z;
}

void moveCoasterCamera()
{
	GLdouble camera_move_x, camera_move_y, camera_move_z;

//	camera_move_x=(__camera.Centre[0]-__camera.Eye[0])/10.0;
//	camera_move_y=(__camera.Centre[1]-__camera.Eye[1])/10.0;
//	camera_move_z=(__camera.Centre[2]-__camera.Eye[2])/10.0;

	camera_move_x=(next_coord.x-current_coord.x)/20.0;
	camera_move_y=(next_coord.y-current_coord.y)/20.0;
	camera_move_z=(next_coord.z-current_coord.z)/20.0;

	__camera.Eye[0]+=camera_move_x;
	__camera.Eye[1]+=camera_move_y;
	__camera.Eye[2]+=camera_move_z;

	if(((__camera.Centre[0]-__camera.Eye[0])*(__camera.Centre[0]-__camera.Eye[0])+(__camera.Centre[1]-__camera.Eye[1])*(__camera.Centre[1]-__camera.Eye[1])+(__camera.Centre[2]-__camera.Eye[2])*(__camera.Centre[2]-__camera.Eye[2]))<0.1){
		sound(100.0, 784.0);
		current_coord.x=pdbIn->current->coord.x;
		current_coord.y=pdbIn->current->coord.y;
		current_coord.z=pdbIn->current->coord.z;
		__camera.Eye[0]=pdbIn->current->coord.x;
		__camera.Eye[1]=pdbIn->current->coord.y+0.01;
		__camera.Eye[2]=pdbIn->current->coord.z;
		pdbIn->current=pdbIn->current->next;
		while(strncmp(pdbIn->current->atomName, " CA ", 4)!=0){
			pdbIn->current=pdbIn->current->next;
		}
		next_coord.x=pdbIn->current->coord.x;
		next_coord.y=pdbIn->current->coord.y;
		next_coord.z=pdbIn->current->coord.z;
		__camera.Centre[0]=pdbIn->current->coord.x;
		__camera.Centre[1]=pdbIn->current->coord.y+0.01;
		__camera.Centre[2]=pdbIn->current->coord.z;
	}
}*/

void moveMyCamera(double movedistance)
{
	GLdouble camera_move_x, camera_move_y, camera_move_z;

//	__camera.Eye[2]+=movedistance;
//	__camera.Centre[2]+=movedistance;

	camera_move_x=(__camera.Centre[0]-__camera.Eye[0])/50.0;
	camera_move_y=(__camera.Centre[1]-__camera.Eye[1])/50.0;
	camera_move_z=(__camera.Centre[2]-__camera.Eye[2])/50.0;

	if(movedistance==1.0){
		__camera.Eye[0]+=camera_move_x;
		__camera.Eye[1]+=camera_move_y;
		__camera.Eye[2]+=camera_move_z;
	}
	else{
		__camera.Eye[0]-=camera_move_x;
		__camera.Eye[1]-=camera_move_y;
		__camera.Eye[2]-=camera_move_z;
	}
}

void setSpeed()
{
	speed*=10.0;
	if(speed==1000){
		speed=1;
	}
}

void moveDriveMyCamera(double movedistance)
{
	GLdouble camera_move_x, camera_move_y, camera_move_z;

//	__camera.Eye[2]+=movedistance;
//	__camera.Centre[2]+=movedistance;

	camera_move_x=(__camera.Centre[0]-__camera.Eye[0])/speed;
	camera_move_y=(__camera.Centre[1]-__camera.Eye[1])/speed;
	camera_move_z=(__camera.Centre[2]-__camera.Eye[2])/speed;

	if(movedistance==1.0){
		__camera.Eye[0]+=camera_move_x;
		__camera.Eye[1]+=camera_move_y;
		__camera.Eye[2]+=camera_move_z;
		__camera.Centre[0]+=camera_move_x;
		__camera.Centre[1]+=camera_move_y;
		__camera.Centre[2]+=camera_move_z;
	}
	else{
		__camera.Eye[0]-=camera_move_x;
		__camera.Eye[1]-=camera_move_y;
		__camera.Eye[2]-=camera_move_z;
		__camera.Centre[0]-=camera_move_x;
		__camera.Centre[1]-=camera_move_y;
		__camera.Centre[2]-=camera_move_z;
	}
}

cameraInfo*
getMyCamera()
{
	return &__camera;
}

void 
upCalc()
{
	GLdouble* up     = __camera.Up;
	GLdouble* eye    = __camera.Eye;
	GLdouble* centre = __camera.Centre;
	GLdouble v[3];
	GLdouble norm;

	int i;

	norm = up[0]*up[0] + up[1]*up[1] + up[2]*up[2];
	if(0 == norm) { 
		up[0] = 0;	
		up[1] = 1;	
		up[2] = 0;	
	} else {
		norm = sqrt(norm);
		for(i=0; i<3; i++) {
			up[i] /= norm;
		}
	}
}

void
myCameraRotateX(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLdouble  norm[3];							
	GLfloat* light; 
	int i;
	double length;

	dummy[0] = __camera.Eye[0]-__camera.Centre[0];
	dummy[1] = __camera.Eye[1]-__camera.Centre[1];
	dummy[2] = __camera.Eye[2]-__camera.Centre[2];

	norm[0] = __camera.Up[1]*dummy[2] - dummy[1]*__camera.Up[2];	
	norm[1] = __camera.Up[2]*dummy[0] - dummy[2]*__camera.Up[0];	
	norm[2] = __camera.Up[0]*dummy[1] - dummy[0]*__camera.Up[1];	

	length = sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);	
	norm[0] /= length;
	norm[1] /= length;
	norm[2] /= length;

	__camera.Eye[0] = __camera.Centre[0] 
			+ (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Eye[1] = __camera.Centre[1] 
			+ (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Eye[2] = __camera.Centre[2] 
			+ (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	dummy[0] = __camera.Up[0];
	dummy[1] = __camera.Up[1];
	dummy[2] = __camera.Up[2];

	__camera.Up[0] =  (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Up[1] =  (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Up[2] =  (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	length = sqrt(__camera.Up[0]*__camera.Up[0]+__camera.Up[1]*__camera.Up[1]+__camera.Up[2]*__camera.Up[2]);	
	__camera.Up[0] /= length;
	__camera.Up[1] /= length;
	__camera.Up[2] /= length;

	for(i=0; i<2; i++) {
		light = get_LightPos(i);	

		dummy[0] = light[0] - __camera.Centre[0];
		dummy[1] = light[1] - __camera.Centre[1];
		dummy[2] = light[2] - __camera.Centre[2];

		light[0] = __camera.Centre[0]
                        + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                        + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                        + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		light[1] = __camera.Centre[1]
                        + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                        + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                        + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
		light[2] = __camera.Centre[2]
                        + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                        + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                        + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}

	glFlush();
}

void
myCameraRotateXX(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLfloat* light; 
	int i;
	/*
		eyex     1   0      0  \  / EyeX \
		eyey =   0  cos   -sin |  | EyeY |
		eyez	 0  sin    cos /  \ EyeZ /
		
	*/	

	dummy[1] = (__camera.Eye[1]-__camera.Centre[1])*cos(angle) - (__camera.Eye[2]-__camera.Centre[2])*sin(angle) ; 
	dummy[2] = (__camera.Eye[1]-__camera.Centre[1])*sin(angle) + (__camera.Eye[2]-__camera.Centre[2])*cos(angle) ; 

	__camera.Eye[1] = dummy[1] + __camera.Centre[1];
	__camera.Eye[2] = dummy[2] + __camera.Centre[2];


	__camera.Up[1] = __camera.Up[1]*cos(angle) - __camera.Up[2]*sin(angle) ; 
	__camera.Up[2] = __camera.Up[1]*sin(angle) + __camera.Up[2]*cos(angle) ; 

	upCalc();

	for(i=0; i<2; i++) {
		light = get_LightPos(i);	

		dummy[0] =  light[0];
		dummy[1] =  (light[1]-__camera.Centre[1])*cos(angle) - (light[2]-__camera.Centre[2])*sin(angle);
		dummy[2] =  (light[1]-__camera.Centre[1])*sin(angle) + (light[2]-__camera.Centre[2])*cos(angle);

		light[0] = dummy[0];
		light[1] = dummy[1]+__camera.Centre[1];
		light[2] = dummy[2]+__camera.Centre[2];
	}
	glFlush();
}

void
myCameraRotateY(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLdouble  norm[3];							
	GLfloat* light; 
	int i,j;
	//for(j = 0; j<2; j++)
	//{
	DEBUGPRINT1("j:: %d",j);
	//light[j] = (GLfloat*)malloc(sizeof(GLfloat));
/*	if(light[j] == NULL)
	{
	fprintf(stderr,"malloc error.\n");
	}*/
	//}
	DEBUGPRINT("GLUT_LEFT_myCameraRotateY_1\n");
	dummy[0] = __camera.Eye[0]-__camera.Centre[0];
	dummy[1] = __camera.Eye[1]-__camera.Centre[1];
	dummy[2] = __camera.Eye[2]-__camera.Centre[2];

	norm[0] = __camera.Up[0];	
	norm[1] = __camera.Up[1];	
	norm[2] = __camera.Up[2];
	DEBUGPRINT("GLUT_LEFT_myCameraRotateY_2\n");	
	__camera.Eye[0] = __camera.Centre[0] 
			+ (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Eye[1] = __camera.Centre[1] 
			+ (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Eye[2] = __camera.Centre[2] 
			+ (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	DEBUGPRINT("GLUT_LEFT_myCameraRotateY_3\n");	
	for(i=0; i<2; i++) {
		light = get_LightPos(i);
		DEBUGPRINT3("light[0]::%f,light[1]::%f,light[2]::%f\n",light[0],light[1],light[2]);	
		DEBUGPRINT("GLUT_LEFT_myCameraRotateY_4\n");
		
		dummy[0] = light[0] - (__camera.Centre[0]);
		dummy[1] = light[1] - (__camera.Centre[1]);
		dummy[2] = light[2] - (__camera.Centre[2]);

		DEBUGPRINT("GLUT_LEFT_myCameraRotateY_5\n");
		light[0] = __camera.Centre[0]
                        + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                        + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                        + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		DEBUGPRINT("ok\n");
		light[1] = __camera.Centre[1]
                        + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                        + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                        + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
        DEBUGPRINT("ok\n");
		light[2] = __camera.Centre[2]
                        + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                        + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                        + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}

	glFlush();
}

void
myCameraRotateYY(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLfloat* light; 
	int i;
	/*
		eyex    cos  0   sin  \  / EyeX \
		eyey =   0   1    0    | | EyeY |
		eyez	-sin 0    cos /  \ EyeZ /
		
	*/	
	dummy[0] =  (__camera.Eye[0]-__camera.Centre[0])*cos(angle) + (__camera.Eye[2]-__camera.Centre[2])*sin(angle) ; 
	dummy[2] = -(__camera.Eye[0]-__camera.Centre[0])*sin(angle) + (__camera.Eye[2]-__camera.Centre[2])*cos(angle) ; 

	__camera.Eye[0] = dummy[0] + __camera.Centre[0];
	__camera.Eye[2] = dummy[2] + __camera.Centre[2];

	__camera.Up[0] =  __camera.Up[0]*cos(angle) + __camera.Up[2]*sin(angle) ; 
	__camera.Up[2] = -__camera.Up[0]*sin(angle) + __camera.Up[2]*cos(angle) ; 

	upCalc();

	for(i=0; i<2; i++) {
		light = get_LightPos(i);	

		dummy[0] =  (light[0]-__camera.Centre[0])*cos(angle) + (light[2]-__camera.Centre[2])*sin(angle);
		dummy[1] =  (light[1]-__camera.Centre[1]);
		dummy[2] = -(light[0]-__camera.Centre[0])*sin(angle) + (light[2]-__camera.Centre[2])*cos(angle);

		light[0] = dummy[0] + __camera.Centre[0];
		light[1] = dummy[1] + __camera.Centre[1];
		light[2] = dummy[2] + __camera.Centre[2];
	}
	glFlush();
}

void
myCameraRotateZ(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLdouble  norm[3];							
	GLfloat* light; 
	int i;
	double length;

	norm[0] = __camera.Eye[0]-__camera.Centre[0];
	norm[1] = __camera.Eye[1]-__camera.Centre[1];
	norm[2] = __camera.Eye[2]-__camera.Centre[2];
	length = sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);	
	norm[0] /= length;
	norm[1] /= length;
	norm[2] /= length;

	dummy[0] = __camera.Up[0];
	dummy[1] = __camera.Up[1];
	dummy[2] = __camera.Up[2];

	__camera.Up[0] =  (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Up[1] =  (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Up[2] =  (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	length = sqrt(__camera.Up[0]*__camera.Up[0]+__camera.Up[1]*__camera.Up[1]+__camera.Up[2]*__camera.Up[2]);	
	__camera.Up[0] /= length;
	__camera.Up[1] /= length;
	__camera.Up[2] /= length;

	for(i=0; i<2; i++) {
		light = get_LightPos(i);	

		dummy[0] = light[0] - __camera.Centre[0];
		dummy[1] = light[1] - __camera.Centre[1];
		dummy[2] = light[2] - __camera.Centre[2];

		light[0] = __camera.Centre[0]
                        + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                        + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                        + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		light[1] = __camera.Centre[1]
                        + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                        + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                        + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
		light[2] = __camera.Centre[2]
                        + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                        + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                        + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}

	glFlush();
}

void
myCameraEyeRotateX(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLdouble  norm[3];							
	GLfloat* light; 
	int i;
	double length;

	dummy[0] = __camera.Centre[0]-__camera.Eye[0];
	dummy[1] = __camera.Centre[1]-__camera.Eye[1];
	dummy[2] = __camera.Centre[2]-__camera.Eye[2];

	norm[0] = __camera.Up[1]*dummy[2] - dummy[1]*__camera.Up[2];	
	norm[1] = __camera.Up[2]*dummy[0] - dummy[2]*__camera.Up[0];	
	norm[2] = __camera.Up[0]*dummy[1] - dummy[0]*__camera.Up[1];	

	length = sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);	
	norm[0] /= length;
	norm[1] /= length;
	norm[2] /= length;

	__camera.Centre[0] = __camera.Eye[0] 
			+ (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Centre[1] = __camera.Eye[1] 
			+ (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Centre[2] = __camera.Eye[2] 
			+ (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	dummy[0] = __camera.Up[0];
	dummy[1] = __camera.Up[1];
	dummy[2] = __camera.Up[2];

	__camera.Up[0] =  (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Up[1] =  (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Up[2] =  (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	length = sqrt(__camera.Up[0]*__camera.Up[0]+__camera.Up[1]*__camera.Up[1]+__camera.Up[2]*__camera.Up[2]);	
	__camera.Up[0] /= length;
	__camera.Up[1] /= length;
	__camera.Up[2] /= length;

	for(i=0; i<2; i++) {
		light = get_LightPos(i);	

		dummy[0] = light[0] - __camera.Eye[0];
		dummy[1] = light[1] - __camera.Eye[1];
		dummy[2] = light[2] - __camera.Eye[2];

		light[0] = __camera.Eye[0]
                        + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                        + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                        + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		light[1] = __camera.Eye[1]
                        + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                        + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                        + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
		light[2] = __camera.Eye[2]
                        + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                        + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                        + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}

	glFlush();
}

void
myCameraEyeRotateY(GLdouble angle) 
{
	GLdouble  dummy[3];							
	GLdouble  norm[3];							
	GLfloat* light; 
	int i;

	dummy[0] = __camera.Centre[0]-__camera.Eye[0];
	dummy[1] = __camera.Centre[1]-__camera.Eye[1];
	dummy[2] = __camera.Centre[2]-__camera.Eye[2];

	norm[0] = __camera.Up[0];	
	norm[1] = __camera.Up[1];	
	norm[2] = __camera.Up[2];	
	__camera.Centre[0] = __camera.Eye[0] 
			+ (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Centre[1] = __camera.Eye[1] 
			+ (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Centre[2] = __camera.Eye[2] 
			+ (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	for(i=0; i<2; i++) {
		light = get_LightPos(i);	

		dummy[0] = light[0] - __camera.Eye[0];
		dummy[1] = light[1] - __camera.Eye[1];
		dummy[2] = light[2] - __camera.Eye[2];

		light[0] = __camera.Eye[0]
                        + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                        + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                        + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		light[1] = __camera.Eye[1]
                        + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                        + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                        + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
		light[2] = __camera.Eye[2]
                        + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                        + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                        + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}

	glFlush();
}

void
myCameraTranslateX(GLdouble pan) 
{
	/*
		eyex    cos  0   sin  \  / EyeX \
		eyey =   0   1    0    | | EyeY |
		eyez	-sin 0    cos /  \ EyeZ /
		
	*/	
	__camera.Centre[0] -= pan;
	upCalc();

	glFlush();
}

void
myCameraTranslateY(GLdouble pan) 
{
	/*
		eyex    cos  0   sin  \  / EyeX \
		eyey =   0   1    0    | | EyeY |
		eyez	-sin 0    cos /  \ EyeZ /
		
	*/	
	__camera.Centre[1] -= pan;
	upCalc();

	glFlush();
}
