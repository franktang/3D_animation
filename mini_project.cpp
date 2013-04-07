/********************************************/
/********************************************/
/****Name:TANG Xiaowu Student ID:51839917****/
/********************************************/
/*******************************************/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

//////////////////////////////////////////////////////////////////
// 
// Include the header file of our rotation user-interface.
// 
#include "gsrc.h"
#include "texture.h"
// 
//////////////////////////////////////////////////////////////////
double theta_arm_left=0;
double theta_arm_right=0;//for the rotation of arm
double theta_thigh_left=0;
double theta_thigh_right=0;//for the rotation of thigh
double theta_shank_left=0;
double theta_shank_right=0;
//double distance=0;
double posx=0;				
double posz=0;				//for the animation of robot
double bally=0;
double ballz=0;				//for the animation of football
double lookz=0;

int flag=0;
int kick_flag=1;			//if it is zero, it indicates the kicking animation has finished and continue the next part
int i=0;					//
int k=0;					//i and k are declared for counting, when i and k do not exceed a certain number, the robot will stop.
GLUquadricObj *body;		//declare the identity of each part of the object and the texture
GLuint bodyTexture;
GLUquadricObj *head;
GLuint headTexture;
GLUquadricObj *arm;
GLuint armTexture;
GLUquadricObj *palm;
GLuint palmTexture;
GLUquadricObj *thigh;
GLuint thighTexture;
GLUquadricObj *shank;
GLuint shankTexture;
GLUquadricObj *foot;
GLuint footTexture;
GLUquadricObj *ball;
GLuint ballTexture;
GLUquadricObj *body2;
GLUquadricObj *sun;
GLuint body2Texture;
GLuint sky_texture;
GLuint grass_texture;



void init (void){
	glClearColor (0.2, 0.52, 1.0, 1.0); 
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);                       
	glEnable(GL_TEXTURE_2D);
	head=gluNewQuadric();
	body=gluNewQuadric();
	arm=gluNewQuadric();
	palm=gluNewQuadric();
	thigh=gluNewQuadric();
	shank=gluNewQuadric();
	ball=gluNewQuadric();
	body2=gluNewQuadric();
	sun=gluNewQuadric();
	gluQuadricTexture(head,GL_TRUE);
	gluQuadricTexture(body,GL_TRUE);
	gluQuadricTexture(arm,GL_TRUE);
	gluQuadricTexture(palm,GL_TRUE);
	gluQuadricTexture(thigh,GL_TRUE);
	gluQuadricTexture(shank,GL_TRUE);
	gluQuadricTexture(ball,GL_TRUE);
	gluQuadricTexture(body2,GL_TRUE);
	loadGLTextures(sky_texture, "sky.bmp");		//load the texture
	loadGLTextures(grass_texture, "grass.bmp");
	loadGLTextures(bodyTexture, "metal.bmp");
	loadGLTextures(headTexture, "head.bmp");
	loadGLTextures(armTexture, "metal.bmp");
	//loadGLTextures(palmTexture, "metal.bmp");
	loadGLTextures(thighTexture, "metal.bmp");
	//loadGLTextures(shankTexture, "metal.bmp");
	loadGLTextures(footTexture, "metal.bmp");
	loadGLTextures(ballTexture, "football.bmp");
	loadGLTextures(body2Texture, "metal.bmp");
}

void init_render(){
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_COLOR_MATERIAL);
	glEnable ( GL_LIGHTING ) ;					//Enable lighting
	glEnable (GL_LIGHT0);						//Enable one light source 0
	glEnable (GL_LIGHT1);						//Enable another light source 1
	glEnable (GL_NORMALIZE);
}

void CreateBox(void)							//create the background box
{	
	glScalef(300,150,300);
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sky_texture);  //the top five surfaces are used for the texture mapping of the sky      
	glPushMatrix();       

    glBegin(GL_QUADS);  

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  -1.0f);			//back surface

    glTexCoord2f(1.0f, 0.0f); glVertex3f( -1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( -1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( -1.0f, -1.0f,  1.0f);			//LHS surface

    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f,  1.0f);			//top surface

    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f);			//front surface

    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f,  1.0f, -1.0f);			//RHS surface

	glEnd();

	glBindTexture(GL_TEXTURE_2D, grass_texture);						//the bottom surface is texture mapped by the grass
	glBegin(GL_QUADS); 

    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  -1.0f, -1.0f);			//bottom surface
	    
    glEnd();
	glDisable(GL_TEXTURE_2D);											
    glPopMatrix();
}
void draw_head(){
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, headTexture);  
	gluSphere(head,5.0,30,30);		//head is a sphere with radius equal to 5
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void draw_body(){
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bodyTexture);  
	glRotatef(-90.0,1.0,0.0,0.0);
	
	gluCylinder(body,6.0,6.0,12.0,30,30);//body is cylinder with rbase=rtop=6.0 and height=7
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void draw_arm(){
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, armTexture);
	glRotatef(90.0,1.0,0.0,0.0);		//let the coordinate system originate at the top of the cylinder
	
	gluCylinder(arm,2.0,2.0,10.0,30,30);// arm is cylinder with rbase=rtop=1.0 and height=9
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void draw_palm(){
	glPushMatrix();
	glColor3f(0.0,1.0,1.0);
	
	gluSphere(palm,2.0,30,30);			//palm is a sphere with radius =1
	glPopMatrix();
}

void draw_thigh(){
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, thighTexture);
	glRotatef(90.0,1.0,0.0,0.0);		//let the coordinate system originate at the top of the cylinder
	
	gluCylinder(thigh,2.5,2.5,8.0,30,30); //thigh is a cylinder with rbase=rtop=3 and height=4
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void draw_shank(){
	glPushMatrix();
	glColor3f(1.0,0.0,0.0);
	glRotatef(90.0,1.0,0.0,0.0);		//let the coordinate system originate at the top of the cylinder
	
	gluCylinder(shank,2.5,2.5,10.0,30,30); //shank is a cylinder with rbase=rtop=3 and height=6
	glPopMatrix();
}

void draw_foot(){						//draw a man's foot which is a 5*1*6 rectangle
	glPushMatrix();
	
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, footTexture);
	glTranslatef  (0, 0.5, 0);			
	glScalef(1.0,0.2,1.2);				
	glutSolidCube(5);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void draw_ball(){					//draw the football
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ballTexture); 
	gluSphere(ball,5.0,30,30);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void draw_body2(){					//draw the lower part of the body
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, body2Texture); 
	gluSphere(ball,6.0,30,30);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void draw_sun(){					//draw the sun
	glPushMatrix();
	glColor3f(5.0,5.0,0.0);
	gluSphere(sun,3.0,30,30);
	glPopMatrix();

}

void draw_object(){
	
	glPushMatrix();

	glPushMatrix();					
	glTranslatef(0,bally,ballz);	//which is used for ball animation
	glTranslatef(0,5,50);
	draw_ball();
	glPopMatrix ();					
	glTranslatef(posx,0.0,posz);	//robot's animation
	glTranslatef(0,19.0,0);
	draw_body();					//draw a man's body
	draw_body2();
	glPushMatrix();					
	glPushMatrix();					
	glPushMatrix();					
	glPushMatrix();					
	glTranslatef(0.0,17.0,0.0);
	glRotatef(-90,1.0,0.0,0.0);
	draw_head();					//draw a man's head
	
	glPopMatrix();					
	
	
	glTranslatef(-8.0,12.0,0.0);
	glRotatef(theta_arm_left,1.0,0.0,0.0); //the left arm will rotate during the animation
	draw_arm();								//draw the left arm
	glTranslatef(0.0,-12.0,0.0);
	draw_palm();							//draw the left palm

	glPopMatrix();					
	
	glTranslatef(8.0,12.0,0.0);
	glRotatef(theta_arm_right,1.0,0.0,0.0);//the right arm will rotate in the opposite direction with the left arm
	glScalef(-1.0,1.0,1.0);
	
	draw_arm();								//draw the right arm
	glTranslatef(0.0,-12.0,0.0);
	draw_palm();							//draw the right palm
	
	glPopMatrix();					
	
	
	glTranslatef(-3.0,0.0,0.0);
	glRotatef(theta_thigh_left,1.0,0.0,0.0);
	draw_thigh();							//draw the left thigh
	glTranslatef(0.0,-8.0,0.0);
	glRotatef(theta_shank_left,1.0,0.0,0.0);
	draw_shank();							//draw the left shank
	glTranslatef(0.0,-11.0,0.0);
	draw_foot();							//draw the left foot

	glPopMatrix();					
	

	glTranslatef(3.0,0.0,0.0);
	glRotatef(theta_thigh_right,1.0,0.0,0.0);
	draw_thigh();							//draw the left thigh
	glTranslatef(0.0,-8.0,0.0);
	glRotatef(theta_shank_right,1.0,0.0,0.0);
	draw_shank();							//draw the left shank
	glTranslatef(0.0,-11.0,0.0);
	draw_foot();							//draw the left foot

	glPopMatrix();
	
}

void draw_shadow(){
	glPushMatrix();

	glPushMatrix();					
	glTranslatef(0,bally,ballz);	//which is used for ball animation later
	glTranslatef(0,5,50);
	
	glPushMatrix();					//draw_ball();
	gluSphere(ball,5.0,30,30);
	glPopMatrix ();

	glPopMatrix ();					
	glTranslatef(posx,0.0,posz);
	glTranslatef(0,19.0,0);
	
	glPushMatrix();
	glRotatef(-90.0,1.0,0.0,0.0);
	gluCylinder(body,6.0,6.0,12.0,30,30);//draw_body();	draw a man's body
	glPopMatrix ();	
	glPushMatrix();
	gluSphere(ball,6.0,30,30);			//draw_body2();
	glPopMatrix ();

	glPushMatrix();					
	glPushMatrix();					
	glPushMatrix();					
	//glPushMatrix();
	glPushMatrix();					
	glTranslatef(0.0,17.0,0.0);
	glRotatef(-90,1.0,0.0,0.0);
	
	glPushMatrix();
	//glColor3f(1.0,1.0,1.0);  
	gluSphere(head,5.0,30,30);		//head is a sphere with radius equal to 5
	glPopMatrix();					//draw a man's head
	
	glPopMatrix();					
	
	
	glTranslatef(-8.0,12.0,0.0);
	glRotatef(theta_arm_left,1.0,0.0,0.0); //the left arm will rotate during the animation
	
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);		//let the coordinate system originate at the top of the cylinder
	gluCylinder(arm,2.0,2.0,10.0,30,30);// arm is cylinder with rbase=rtop=1.0 and height=9
	glPopMatrix();						//draw the left arm
	
	glTranslatef(0.0,-12.0,0.0);
	
	glPushMatrix();
	gluSphere(palm,2.0,30,30);			//palm is a sphere with radius =1
	glPopMatrix();						//draw the left palm

	glPopMatrix();					
	
	glTranslatef(8.0,12.0,0.0);
	glRotatef(theta_arm_right,1.0,0.0,0.0);//the right arm will rotate in the opposite direction with the left arm
	glScalef(-1.0,1.0,1.0);
	
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);		//let the coordinate system originate at the top of the cylinder
	gluCylinder(arm,2.0,2.0,10.0,30,30);// arm is cylinder with rbase=rtop=1.0 and height=9
	glPopMatrix();						//draw the right arm
	
	glTranslatef(0.0,-12.0,0.0);
	
	glPushMatrix();
	gluSphere(palm,2.0,30,30);			//palm is a sphere with radius =1
	glPopMatrix();						//draw the right palm
	
	glPopMatrix();					
	
	
	glTranslatef(-3.0,0.0,0.0);
	glRotatef(theta_thigh_left,1.0,0.0,0.0);
	
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);		//let the coordinate system originate at the top of the cylinder
	gluCylinder(thigh,2.5,2.5,8.0,30,30); //thigh is a cylinder with rbase=rtop=3 and height=4
	glPopMatrix();						//draw the left thigh
	
	glTranslatef(0.0,-8.0,0.0);
	glRotatef(theta_shank_left,1.0,0.0,0.0);
	
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);		//let the coordinate system originate at the top of the cylinder
	gluCylinder(shank,2.5,2.5,10.0,30,30); //shank is a cylinder with rbase=rtop=3 and height=6
	glPopMatrix();						//draw the left shank
	
	glTranslatef(0.0,-11.0,0.0);
	
	glPushMatrix();
	glTranslatef  (0, 0.5, 0);			
	glScalef(1.0,0.2,1.2);				
	glutSolidCube(5);
	glPopMatrix();						//draw the left foot

	glPopMatrix();					
	

	glTranslatef(3.0,0.0,0.0);
	glRotatef(theta_thigh_right,1.0,0.0,0.0);
	
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);		//let the coordinate system originate at the top of the cylinder
	gluCylinder(thigh,2.5,2.5,8.0,30,30); //thigh is a cylinder with rbase=rtop=3 and height=4
	glPopMatrix();						//draw the left thigh
	
	glTranslatef(0.0,-8.0,0.0);
	glRotatef(theta_shank_right,1.0,0.0,0.0);
	
	glPushMatrix();
	glRotatef(90.0,1.0,0.0,0.0);		//let the coordinate system originate at the top of the cylinder
	gluCylinder(shank,2.5,2.5,10.0,30,30); //shank is a cylinder with rbase=rtop=3 and height=6
	glPopMatrix();						//draw the left shank
	
	glTranslatef(0.0,-11.0,0.0);
	
	glPushMatrix();
	glTranslatef  (0, 0.5, 0);			
	glScalef(1.0,0.2,1.2);				
	glutSolidCube(5);					//draw the left foot
	glPopMatrix();						

	glPopMatrix();
}

void drawscene(void){					//draw the whole scene
	GLint viewport[4];
	glGetIntegerv( GL_VIEWPORT, viewport );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective( 45, double(viewport[2])/viewport[3], 0.1, 1000 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( 100,25,200,0,0,lookz, 0,1,0 );					//the PRP is at (100,25,200), looking at (0,0,lookz), VUP is (0,1,0)
	glMultMatrixf( gsrc_getmo() ); 
	
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB |  GLUT_DEPTH);	//initialize the display mode, double buffer
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);								//enable depth test
	glClear(GL_COLOR_BUFFER_BIT);

	//Add a ambient light
	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f};	 //the ambient Color is (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add directed light
	GLfloat lightColor1[] = {0.3f, 0.3f, 0.3f, 1.0f};	//Color (0.5, 0.2, 0.2)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};	//the light comes from the direction (-1, 0.5, 0.5)
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	
	//Add a point light source 
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {-20.0f, 50.0f, 70.0f, 1.0f}; //Positioned at (-20,50,70)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	////////draw the cube used for the background/////////////////////////////////////////
	glPushMatrix ( );
	glTranslatef(100,150,100);
	CreateBox();
	glPopMatrix ( );
	//////////////////////////////////////////////////////////////////

	glPushMatrix();	
	glTranslatef(-20.0f,50.0f,70.0f);
	draw_sun();										//draw a sun positioned at the point light source
	glPopMatrix ();

	GLfloat M[16]= {	1, 0, 0, 0,
						0, 1, 0, -1/(50-0.1),
						0, 0, 1, 0,
						0, 0, 0, 0 };				//perspective projection

	draw_object();									//draw the whole object

	/////////////////draw the shadow///////////////////////////
	//glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(-20,50,70);						//M wc<-s
	glMultMatrixf(M);								//perspective project
	glTranslatef(20,-50,-70);						//M s<-wc
	glColor4f(0.3f,0.3f,0.3f,0.2f);					//the color of the shadow

	draw_shadow();									//draw the shadows

	glutSwapBuffers();								//swap buffers to display
	
	glFlush();
	
}

void move(int j){
	
			
	if (posz<=37){								//the robot is walking to the ball
			posz+=1;

			if (flag==0){						//the man's walking part 1: left leg is walking forward
				theta_thigh_left-=10;
				theta_arm_right-=5;
				//theta_shank_left+=0.3;
				theta_thigh_right+=10;
				theta_arm_left+=5;
				//theta_shank_right=0;
				if (theta_thigh_right>=40.0)
					flag=1;
			}
			else{								//the man's walking part 2: right leg is walking forward
				theta_thigh_left+=10;
				theta_arm_right+=5;
				//theta_shank_left-=0.3;
				theta_thigh_right-=10;
				theta_arm_left-=5;
				//theta_shank_right+=0.3;
				if (theta_thigh_left>=40.0)
					flag=0;
			}
	}
	else{										//the robot meets the ball
		if (i<=5){								//the robot stop for 5 cycles
			theta_thigh_left=0;
			theta_arm_left=0;
			theta_thigh_right=0;
			theta_arm_right=0;
			i++;
		}
		else if (kick_flag==1){					//this section shows the animation of kicking a ball
			
			if (theta_thigh_left<=-10){			
				bally+=10;						//the ball is kicked away out of the screen
				ballz+=10;
			}
			if (theta_thigh_left>=-40)			//raise the leg to kick the ball
				theta_thigh_left-=10;
			else{
				if (k<=5)
					k++;						//afterwards, the robot stops for 5 cycles
				else{
					theta_thigh_left=0;			//leg back to the origin position
					kick_flag=0;				//set kick_flag to zero indicate there's no need to do the kick animation anymore
				}
			}
		}
		else{
			if (posz<=100){						//afterwards, the robot continues walking until it reaches the destination
					posz+=1;

				if (flag==0){				
					theta_thigh_left-=10;
					theta_arm_right-=5;
					//theta_shank_left+=0.3;
					theta_thigh_right+=10;
					theta_arm_left+=5;
					//theta_shank_right=0;
					if (theta_thigh_right>=40.0)
						flag=1;
				}
				else{
					theta_thigh_left+=10;
					theta_arm_right+=5;
					//theta_shank_left-=0.3;
					theta_thigh_right-=10;
					theta_arm_left-=5;
					//theta_shank_right+=0.3;
					if (theta_thigh_left>=40.0)
						flag=0;
				}
			}
			else{								//the robot reaches the destination and stop walking
				theta_thigh_left=0;
				theta_arm_left=0;
				theta_thigh_right=0;
				theta_arm_right=0;
			}
		}


	}
			glutPostRedisplay ( );
			glutTimerFunc(40,move,0);
	
	
	/*if (posz>=30)
		lookz+=0.1;*/
		
	
	
}
void main (int argc, char** argv)
{
	glutInit(&argc,argv);							//GLUT initialization

	glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH );	
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowPosition(50,100);					//set top-left display-window position
	glutInitWindowSize(400,300);					//set display-window width and height
	glutCreateWindow("Mini Project by TANG Xiaowu");//create the display window

	
	//////////////////////////////////////////////////////////////////
	// 
	// Register mouse-click and mouse-move glut callback functions
	// for the rotation user-interface.
	// 
	//glutMouseFunc( gsrc_mousebutton );
	//glutMotionFunc( gsrc_mousemove );
	//
	//////////////////////////////////////////////////////////////////
	init_render();									//initialize the lighting
	init();											//initialize the objects and load textures
	glutDisplayFunc (drawscene);					//display the scene
	glutTimerFunc(40,move,0);						//a timer function which is used for animation
	glutMainLoop ();
}