#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <GL/glut.h>

#define ANIM_TOTAL_N 500
#define ANIM_DELTA_T 1000	// delta t = 1000ms
#define PI 3.141592654

typedef struct point{ // define a structure for 3D point (x, y, z)
	GLfloat x;
	GLfloat y;
	GLfloat z;
} vertex;

typedef struct _image{
	GLint width, height;
	GLubyte *pixels;
}Image;

void 	bmpread(const char *imname, Image *image);
float 	sign(float x);
int 	power_of_two(int n);
bool 	loadGLTextures(GLuint& unTexture, const char* chFileName);
int		getNextInterval(int count);

#endif